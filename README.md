# 测试前准备

### wps linux 安装

https://www.wps.cn/product/wpslinux# 这个网页可以下载 x64架构版本12.1.2.25882的deb安装包。
可以在宿主机下载，之后复制到wsl中即可。

# 测试步骤
**WPS Fuzz 工具执行链手册**

这套链路的核心思路不是“直接随机生成 DOCX”，而是：

1. 先让 Nautilus 根据 grammar 生成结构化语法树。
2. 再把语法树反序列化成中间表示 IR。
3. 最后通过 OOXML lowerer 把 IR lowering 成真实 DOCX，交给 WPS 执行。

也就是说，当前这套 WPS fuzz 工具本质上是一条：

`Nautilus grammar -> IR -> OOXML lowerer -> DOCX -> afl-qemu-trace -> WPS`

**各组件职责**

- `Nautilus`：负责语法生成、变异、调度、覆盖反馈和 corpus 管理。
- `grammar`：定义允许生成哪些文档结构，例如 paragraph、list、table、hyperlink、image 等。
- `IR`：grammar 生成出的中间表示，不直接给 WPS，而是作为 lowerer 的输入。
- `OOXML lowerer`：把 IR 转成格式更规范的 DOCX ZIP 包。
- `afl-qemu-trace`：负责提供 AFL 风格 forkserver/QEMU 插桩执行能力。
- `WPS`：真实被测目标，最终解析并打开 DOCX。

**执行链详解**

1. `Nautilus` 根据 grammar 生成 derivation tree。
  这一步生成的是语法层面的树结构，还不是最终的 DOCX 文件。

2. `tree.unparse_to_vec(ctx)` 把 derivation tree 展开成 IR。
  这里产出的内容一般是 grammar 所定义的结构化文本或 JSON 风格中间表示。它描述的是“文档应该包含什么结构”，而不是 OOXML 压缩包本身。

3. `Nautilus` 检查当前配置里是否启用了 input lowerer。
  如果没有配置 lowerer，那么 IR 本身就会被当成最终输入；如果配置了 lowerer，Nautilus 会在内部调用 lowerer，继续做一次 IR -> DOCX 的转换。

4. `OOXML lowerer` 读取 IR，并生成真实 DOCX。
  这一步通常由外部 lowerer 程序完成，例如：
  `dotnet openxml_sdk_demo.dll @@INPUT@@ @@OUTPUT@@`

  它的含义是：

  - Nautilus 先把 IR 写到 `@@INPUT@@`
  - 调用 lowerer 读取 `@@INPUT@@`
  - lowerer 生成规范化的 DOCX 到 `@@OUTPUT@@`
  - Nautilus 再把 `@@OUTPUT@@` 读回内存，作为最终 fuzz 输入

5. `Nautilus` 把 materialized 后的 DOCX bytes 写入 forkserver 输入文件。
  到这里，输入已经不再是 IR，而是真实的 DOCX 字节流。当前主跑流程里，timeout、signaled、queue 等目录里落盘保存的也应该是这个最终 materialize 后的 DOCX，而不是原始 IR。

6. `Nautilus` 自己启动并驱动 `afl-qemu-trace`。
  这里不是外面再套一层 AFL/AFL++ 去驱动 Nautilus，而是 Nautilus 自己负责 forkserver 协议交互，并把目标程序设置为：

  `afl-qemu-trace /opt/kingsoft/wps-office/office6/wps @@`

7. `afl-qemu-trace` 再去执行真实 WPS。
  WPS 读取 Nautilus 写入的 DOCX 输入文件，进入实际的文档解析、关系加载、样式处理、布局、恢复修复、错误处理等代码路径。

8. 执行结果和覆盖反馈再回流给 Nautilus。
  Nautilus 根据 bitmap 是否增长、是否超时、是否崩溃、是否需要入队等条件，决定这个样本是否应该加入 corpus，以及后续是否继续围绕它做变异。

**一句话理解整条链**

可以把它理解成：

- Nautilus 负责“生成和进化文档结构”；
- lowerer 负责“把结构翻译成真正的 DOCX”；
- afl-qemu-trace 负责“把 DOCX 喂给 WPS 并返回覆盖反馈”；
- WPS 负责“真正解析文档并暴露目标代码路径”。

**为什么要走 IR + lowerer，而不是直接生成 DOCX**

这样做的好处主要有三个：

1. grammar 层更容易表达高层文档结构，而不是直接手写大量 OOXML/XML 细节。
2. lowerer 可以先生成更规范的 DOCX，让样本更容易深入 WPS 的正常解析路径，而不是一上来就卡在最外层格式损坏。
3. 后续如果需要，也可以在 lowerer 之后继续做二次 mutation，用“高规范度样本 + 局部破坏”的方式去打更深的边界。

**当前链路里的关键注意点**

1. `afl-qemu-trace` 是由 Nautilus 内部启动和管理的，不是外部额外再包一层。
2. WPS 目标应尽量使用真实 ELF：`/opt/kingsoft/wps-office/office6/wps`，而不是 `/usr/bin/wps` 这种 wrapper。
3. Nautilus 这边走的是 vanilla AFL 风格 forkserver，因此和 AFL++ qemu mode 配合时需要 `AFL_OLD_FORKSERVER=1`。
4. 当前真正进入 WPS 的输入是 lower 后的 DOCX bytes，不是 grammar 直接吐出来的 IR。

**最简版执行链总结**

你的理解基本是对的，可以收敛成下面这版：

1. Nautilus 根据 grammar 生成 derivation tree。
2. `tree.unparse_to_vec(ctx)` 先产出 IR。
3. 使用配置好的 lowerer，Nautilus 内部调用 lowerer，把 IR 变成 DOCX。
4. Nautilus 把 DOCX bytes 写进 forkserver 输入文件。
5. `afl-qemu-trace` 由 Nautilus 自己启动和驱动，`afl-qemu-trace` 再去跑 WPS。
6. WPS 的执行结果和覆盖反馈返回给 Nautilus，用于后续入队和变异。