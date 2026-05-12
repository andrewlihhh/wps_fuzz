# WPS Fuzz 测试说明

本仓库用于探索 WPS/Office 文档解析相关的 fuzz 测试。当前主要有两条路线：

1. `Nautilus grammar -> IR -> OOXML lowerer -> DOCX -> afl-qemu-trace -> WPS`
2. `OpenXMolar -> 解包 OpenXML -> 变异内部 XML/二进制部件 -> 重打包 DOCX/XLSX/PPTX -> 启动目标程序`

从工具定位上看，Nautilus 更适合“有清晰语言 grammar、执行速度较快、目标能在 forkserver 模式下高频启动”的解释器/编译器类程序；OpenXMolar 则是专门围绕 Microsoft Open XML / OOXML 文档包设计的文件格式 fuzz 框架，更贴近 DOCX/XLSX/PPTX 这类 WPS 输入。

## 测试前准备

### WPS Linux 安装

可以从 WPS Linux 官网下载 x64 架构版本的 deb 安装包：

https://www.wps.cn/product/wpslinux

当前测试中使用过的版本为 `12.1.2.25882`。可以在宿主机下载后复制到 WSL/Linux 环境中安装。

## 工具选择建议

### Nautilus 的适用性

根据 Nautilus 论文 `related_papers/OOXML software testing/2019-NDSS(A)-Nautilus-Aschermann.pdf`，Nautilus 的核心强项是把 grammar-based generation 和 coverage feedback 结合起来，用于测试需要高度结构化输入的程序。论文实验目标主要是脚本语言解释器/编译器类程序，例如 `mruby`、`PHP`、`Lua`、`ChakraCore`。

这类目标通常有几个特点：

- 输入语言有相对明确的 grammar，例如 Ruby、PHP、JavaScript、Lua。
- 测试样本是可直接执行或解释的文本程序。
- 目标程序启动和执行成本较低，适合覆盖率反馈驱动的高频 fuzz。
- 通过 grammar 生成语法正确的程序后，容易越过 lexer/parser，进入语义分析、解释执行、JIT 或编译相关代码。

WPS 这类 Office 文档解析程序不完全符合这个模型：

- DOCX/XLSX/PPTX 是 ZIP/OPC 容器，内部包含大量 XML、关系文件、媒体文件、属性文件和内容类型声明。
- 仅有 grammar 很难完整表达 OOXML 包级约束，例如 `[Content_Types].xml`、`_rels/.rels`、part name、relationship id、样式引用、编号引用、图片引用等跨文件一致性。
- WPS 是 GUI 应用，冷启动、弹窗、恢复模式、字体加载和桌面环境都会显著影响执行速度。
- 如果样本只是“语法上像 DOCX”，但包内关系不一致，目标很容易卡在修复/恢复路径，而不是深入正文排版、对象加载、样式计算等更有价值的路径。

因此，Nautilus 可以继续作为结构生成和探索路线使用，但它不是最贴合 WPS/OOXML 的唯一方案。针对 WPS，建议重点关注“合法 Office 样本 + 内部部件定向变异 + 弹窗/进程生命周期控制”的路线，OpenXMolar 正好提供了这种工作流。

## Nautilus 路线

**WPS Fuzz 工具执行链手册**

这套链路的核心思路不是“直接随机生成 DOCX”，而是：

1. 先让 Nautilus 根据 grammar 生成结构化语法树。
2. 再把语法树反序列化成中间表示 IR。
3. 最后通过 OOXML lowerer 把 IR lowering 成真实 DOCX，交给 WPS 执行。

也就是说，当前这套 WPS fuzz 工具本质上是一条：

```text
Nautilus grammar -> IR -> OOXML lowerer -> DOCX -> afl-qemu-trace -> WPS
```

### 各组件职责

- `Nautilus`：负责语法生成、变异、调度、覆盖反馈和 corpus 管理。
- `grammar`：定义允许生成哪些文档结构，例如 paragraph、list、table、hyperlink、image 等。
- `IR`：grammar 生成出的中间表示，不直接给 WPS，而是作为 lowerer 的输入。
- `OOXML lowerer`：把 IR 转成格式更规范的 DOCX ZIP 包。
- `afl-qemu-trace`：负责提供 AFL 风格 forkserver/QEMU 插桩执行能力。
- `WPS`：真实被测目标，最终解析并打开 DOCX。

### 执行链详解

1. `Nautilus` 根据 grammar 生成 derivation tree。
   这一步生成的是语法层面的树结构，还不是最终的 DOCX 文件。

2. `tree.unparse_to_vec(ctx)` 把 derivation tree 展开成 IR。
   这里产出的内容一般是 grammar 所定义的结构化文本或 JSON 风格中间表示。它描述的是“文档应该包含什么结构”，而不是 OOXML 压缩包本身。

3. `Nautilus` 检查当前配置里是否启用了 input lowerer。
   如果没有配置 lowerer，那么 IR 本身就会被当成最终输入；如果配置了 lowerer，Nautilus 会在内部调用 lowerer，继续做一次 IR -> DOCX 的转换。

4. `OOXML lowerer` 读取 IR，并生成真实 DOCX。
   这一步通常由外部 lowerer 程序完成，例如：

   ```sh
   dotnet openxml_sdk_demo.dll @@INPUT@@ @@OUTPUT@@
   ```

   它的含义是：

   - Nautilus 先把 IR 写到 `@@INPUT@@`
   - 调用 lowerer 读取 `@@INPUT@@`
   - lowerer 生成规范化的 DOCX 到 `@@OUTPUT@@`
   - Nautilus 再把 `@@OUTPUT@@` 读回内存，作为最终 fuzz 输入

5. `Nautilus` 把 materialized 后的 DOCX bytes 写入 forkserver 输入文件。
   到这里，输入已经不再是 IR，而是真实的 DOCX 字节流。当前主跑流程里，timeout、signaled、queue 等目录里落盘保存的也应该是这个最终 materialize 后的 DOCX，而不是原始 IR。

6. `Nautilus` 自己启动并驱动 `afl-qemu-trace`。
   这里不是外面再套一层 AFL/AFL++ 去驱动 Nautilus，而是 Nautilus 自己负责 forkserver 协议交互，并把目标程序设置为：

   ```sh
   afl-qemu-trace /opt/kingsoft/wps-office/office6/wps @@
   ```

7. `afl-qemu-trace` 再去执行真实 WPS。
   WPS 读取 Nautilus 写入的 DOCX 输入文件，进入实际的文档解析、关系加载、样式处理、布局、恢复修复、错误处理等代码路径。

8. 执行结果和覆盖反馈再回流给 Nautilus。
   Nautilus 根据 bitmap 是否增长、是否超时、是否崩溃、是否需要入队等条件，决定这个样本是否应该加入 corpus，以及后续是否继续围绕它做变异。

### Nautilus 路线注意点

1. `afl-qemu-trace` 是由 Nautilus 内部启动和管理的，不是外部额外再包一层。
2. WPS 目标应尽量使用真实 ELF：`/opt/kingsoft/wps-office/office6/wps`，而不是 `/usr/bin/wps` 这种 wrapper。
3. Nautilus 这边走的是 vanilla AFL 风格 forkserver，因此和 AFL++ qemu mode 配合时需要 `AFL_OLD_FORKSERVER=1`。
4. 当前真正进入 WPS 的输入是 lower 后的 DOCX bytes，不是 grammar 直接吐出来的 IR。
5. 如果长时间只看到 timeout 或修复提示，而覆盖率没有明显增长，需要优先检查 WPS 启动成本、弹窗处理、样本规范度和 lowerer 生成的 OOXML 关系完整性。

## OpenXMolar 路线

### OpenXMolar 是什么

`OpenXMolar/` 是一个 Microsoft Open XML 文件格式 fuzzing 框架，原版由 Python 2.7 编写，主要面向 Windows 平台上的 Office/OpenXML 应用测试。它的优势不是从零生成一个 OOXML 文档，而是基于合法种子文档做内部部件级变异：

```text
合法 DOCX/XLSX/PPTX 种子
  -> 解包 OpenXML ZIP
  -> 选择内部 XML/rels/bin/vml 等文件
  -> 调用 FileFormatHandlers 里的 mutation handler
  -> 重打包为 Office 文档
  -> 启动 WPS/Office/XPS Viewer
  -> 监控 crash、保存样本、清理弹窗
```

这条路线更适合 WPS 测试，因为它天然保留了大部分真实文档结构，只对内部高风险部件做局部扰动，通常比完全手写 DOCX 更容易通过外层格式校验。

### 重要限制

原版 OpenXMolar 是 Windows-only 工作流：

- 依赖 `winappdbg` 或 `pydbg` 做 Windows 进程调试和 crash 捕获。
- 依赖 `pyautoit`/AutoIt 处理 Windows 弹窗。
- 路径分隔符、`taskkill`、`%temp%` 清理等逻辑也按 Windows 编写。

因此，仓库里的原版 OpenXMolar 不能直接拿来测试 Linux 版 WPS。如果测试目标是 Linux WPS，OpenXMolar 更适合作为“OOXML 内部变异框架参考”或“在 Windows WPS/Office 上跑的对照工具”。如果要接入 Linux WPS，需要替换进程监控、弹窗处理、路径处理和 crash 收集逻辑。

### 目录结构

OpenXMolar 的关键文件如下：

- `OpenXMolar/OpenXMolar.py`：主 fuzz loop，负责加载配置、生成样本、启动目标、监控 crash。
- `OpenXMolar/config.py`：配置文件，设置种子目录、目标程序、handler、运行时间等。
- `OpenXMolar/OfficeFileProcessor.py`：负责 OpenXML 文件解包、加载、重打包。
- `OpenXMolar/Mutator.py`：负责选择内部文件并调用 mutation handler。
- `OpenXMolar/FileFormatHandlers/`：内部文件变异脚本目录。
- `OpenXMolar/PopUpKiller.py`：Windows 弹窗处理逻辑。
- `OpenXMolar/OXDumper.py`：列出 OpenXML 包内部文件，辅助选择定向 fuzz 目标。
- `OpenXMolar/crashSummary.py`：汇总 crash 结果。
- `OpenXMolar/BaseOfficeDocs/OpenXMLFiles/`：放置 `.docx`、`.xlsx`、`.pptx`、`.xps`、`.oxps` 等 OpenXML 种子文件。
- `OpenXMolar/FuzzTemp/`：运行时生成的变异样本目录。
- `OpenXMolar/crashes/`：crash 样本和 crash 报告输出目录。

### 环境准备

原版建议在 Windows 环境中准备：

1. 安装 Python 2.7。
2. 安装或确认可导入 `winappdbg`。仓库中 `ExtDepLibs/` 已带一份依赖，但仍建议先用一次空跑确认环境。
3. 安装 `pyautoit`/AutoItX，用于处理 Office/WPS 弹窗。
4. 准备被测程序，例如 Windows 版 WPS Writer、Microsoft Word、XPS Viewer 等。
5. 准备一批能被目标正常打开的 `.docx`/`.xlsx`/`.pptx` 种子文档。

### 最小运行流程

进入 OpenXMolar 目录：

```bat
cd C:\path\to\wps_fuzz\OpenXMolar
```

把种子文件放入：

```text
OpenXMolar\BaseOfficeDocs\OpenXMLFiles\
```

注意：同一次运行里最好只放同一种扩展名，例如只放 `.docx`。原版配置检查要求 OpenXML 种子目录里的扩展名不要混用。

修改 `OpenXMolar/config.py`：

```python
OpenXMLFormat = True

APP_LIST = {
    'docx': r'C:\path\to\wps.exe',
}

COMMAND_LINE_ARGUMENT = []

AUTO_IDENTIFY_INTERNAL_FILE_FORAMT = True

ALL_MUTATION_SCRIPTS = {
    'xml': 'SampleHandler.py',
    'rels': 'SampleHandler.py',
    'bin': 'binaryHandler.py',
    'vml': 'SampleHandler.py',
}

NUMBER_OF_FILES_TO_MUTATE = 2
APP_RUN_TIME = 3
DEBUGGER = 'winappdbg'
FILES_TO_BE_FUZZED = []
```

然后启动：

```bat
python OpenXMolar.py config.py
```

运行后，OpenXMolar 会循环执行：

1. 从 `BaseOfficeDocs\OpenXMLFiles` 读取合法种子。
2. 解包并加载包内文件到内存。
3. 随机选择种子和若干内部文件。
4. 根据扩展名选择 `FileFormatHandlers` 里的 handler。
5. 生成变异后的 OpenXML 包，写入 `FuzzTemp`。
6. 使用配置的目标程序打开样本。
7. 监控 `APP_RUN_TIME` 秒。
8. 如果触发访问违规等 crash，把样本和报告复制到 `crashes`。
9. 如果没有 crash，到时后杀掉进程并进入下一轮。

### 定向选择内部文件

如果想只 fuzz 某些内部文件，例如 `word/document.xml`、`word/_rels/document.xml.rels`、`word/styles.xml`，可以先用 `OXDumper.py` 列出种子包内部文件。

列出所有内部文件：

```bat
python OXDumper.py
```

只列出指定扩展名：

```bat
python OXDumper.py xml,rels,vml,bin
```

把输出中的 `FILES_TO_BE_FUZZED = [...]` 复制到 `config.py`。注意：当 `FILES_TO_BE_FUZZED` 非空时，种子目录里应只放一个 OpenXML 文件，避免不同种子的内部路径不一致。

适合优先关注的 DOCX 内部部件包括：

- `[Content_Types].xml`
- `_rels/.rels`
- `word/document.xml`
- `word/_rels/document.xml.rels`
- `word/styles.xml`
- `word/numbering.xml`
- `word/settings.xml`
- `word/fontTable.xml`
- `word/theme/theme1.xml`
- `word/media/*`
- `word/vbaProject.bin`

### 编写 mutation handler

OpenXMolar 的核心扩展点是 `OpenXMolar/FileFormatHandlers/`。每个 handler 必须提供名为 `Handler` 的类，并实现 `Fuzzit` 方法：

```python
class Handler():
    def __init__(self):
        pass

    def Fuzzit(self, actual_data_stream):
        data_after_mutation = actual_data_stream
        return data_after_mutation
```

约束：

- 类名必须是 `Handler`。
- 方法名必须是 `Fuzzit`。
- 入参和返回值的数据类型应保持一致。
- XML handler 应返回变异后的 XML 字符串。
- binary handler 应返回变异后的二进制字符串。

写好 handler 后，把文件放入：

```text
OpenXMolar\FileFormatHandlers\
```

然后在 `config.py` 中配置扩展名到 handler 的映射：

```python
FILE_FORMAT_HANDLERS = {
    'xml': 'myXmlHandler.py',
    'rels': 'myXmlHandler.py',
    'bin': 'binaryHandler.py',
}
```

如果 `AUTO_IDENTIFY_INTERNAL_FILE_FORAMT = True`，则主要使用 `ALL_MUTATION_SCRIPTS`：

```python
ALL_MUTATION_SCRIPTS = {
    'xml': 'myXmlHandler.py',
    'rels': 'myXmlHandler.py',
    'bin': 'binaryHandler.py',
}
```

### 弹窗处理

Office/WPS 打开异常文档时，经常会弹出“发现无法读取的内容”“是否修复”“程序无响应”等窗口。原版 OpenXMolar 使用 `PopUpKiller.py` 轮询并点击这些窗口。

如果测试 Windows 版 WPS，需要根据 WPS 实际弹窗补充匹配逻辑。方法是：

1. 用 AutoIt Window Info 工具查看弹窗标题、文本和按钮。
2. 在 `PopUpKiller.py` 中加入对应窗口判断。
3. 使用 `autoit.control_click(...)` 点击“确定”“关闭”“恢复”等按钮。

这一步非常关键。弹窗如果没有处理好，fuzz loop 会卡住，样本吞吐会迅速下降。

### Crash 汇总

OpenXMolar 把 crash 样本和报告写入 `crashes/`。运行一段时间后，可以使用：

```bat
python crashSummary.py
```

对 crash 结果做表格化汇总。后续复现时优先检查：

- crash 样本文件。
- crash 地址或异常类型。
- 对应目标程序版本。
- 是否能稳定复现。
- 是否只是 WPS 自身恢复/弹窗导致的假阳性。

## 面向 WPS 的推荐策略

短期建议把 OpenXMolar 当成 OOXML 定向变异路线来用：

1. 收集能被 WPS 稳定打开的真实 DOCX/XLSX/PPTX 样本。
2. 优先对 `document.xml`、`.rels`、`styles.xml`、`numbering.xml`、媒体引用、OLE/VBA 相关 part 做小范围变异。
3. 避免一开始就大面积破坏 `[Content_Types].xml` 和顶层 relationship，否则样本容易停在外层格式校验。
4. 先在 Windows WPS/Office 上验证 OpenXMolar 原版流程是否能稳定跑通。
5. 如果目标必须是 Linux WPS，再把 OpenXMolar 的“解包-变异-重打包”部分抽出来，接到 Linux 侧的 WPS 启动器、timeout 控制、crash/日志收集流程中。
6. Nautilus 路线可以保留，用于生成高层结构 IR；但更推荐让 lowerer 负责生成规范 OOXML，再做局部内部变异，而不是直接依赖 grammar 手写完整 DOCX 包。

一句话总结：

- Nautilus 更适合作为“结构生成 + 覆盖反馈”的探索工具。
- OpenXMolar 更适合作为“合法 Office 文档 + 内部部件变异”的 WPS/OOXML 测试工具。
- 对 WPS 这类目标，样本规范度、进程生命周期控制、弹窗处理和定向部件选择，通常比单纯提高 grammar 复杂度更重要。
