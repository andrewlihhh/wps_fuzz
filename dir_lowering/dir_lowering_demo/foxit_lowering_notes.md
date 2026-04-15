# DIR -> Foxit SDK -> PDF

这个目录现在已经不是概念示意，而是一个真实可编译、可运行的 Foxit Linux SDK lowering 实验。

## 1. 这个 demo 现在做了什么

当前实现文件是 [dir_to_foxit_pdf_example.cpp](/home/kzl/dir_lowering_demo/dir_to_foxit_pdf_example.cpp)。它会：

- 从 `foxit_sdk/lib/gsdk_sn.txt` 读取 `SN=`
- 从 `foxit_sdk/lib/gsdk_key.txt` 读取 `Sign=`
- 调用 `Library::Initialize(sn, key)` 初始化 Foxit SDK
- 从 [foxit_dir_sample.json](/home/kzl/dir_lowering_demo/foxit_dir_sample.json) 读取 DIR
- 支持 `document -> page -> object` 结构，其中 object 目前包含 `text`、`image`、`path`、`table`
- 对每一页调用 `PDFDoc::InsertPage(...)`
- 对文本对象调用 `TextObject::Create()`、`SetTextState()`、`SetText()`、`Transform()`
- 对图片对象调用 `ImageObject::Create()`、`SetImage()`、`SetMatrix()`
- 对路径对象调用 `PathObject::Create()`、`SetPathData()`、`SetStrokeColor()`、`SetFillMode()`
- 对表格对象把它 lower 成“网格路径 + 单元格文本”的组合
- 最后调用 `PDFDoc::SaveAs(...)` 输出 PDF

输出文件是 [output/foxit_dir_output.pdf](/home/kzl/dir_lowering_demo/output/foxit_dir_output.pdf)。

## 2. 这份 lowering 和论文里的关系

论文里的 lowering，本质上就是把 DIR 中的抽象文档对象翻译成目标格式 SDK 的具体调用序列。

在当前这个真实 Foxit 实验里，映射关系已经落到了具体 API：

- `DIR page` -> `PDFDoc::InsertPage(...)`
- `DIR text.font_name` -> `Font(...)`
- `DIR text.font_size` -> `TextState.font_size`
- `DIR text.color` -> `TextObject::SetFillColor(...)`
- `DIR text.text` -> `TextObject::SetText(...)`
- `DIR top-left (x, y)` -> 先换算成 PDF bottom-left 坐标，再 `Transform(...)`
- `DIR image.path + size` -> `ImageObject::SetImage(...) + SetMatrix(...)`
- `DIR path.points` -> `Path::MoveTo/LineTo/CloseFigure + PathObject::SetPathData(...)`
- `DIR table` -> Foxit 没有直接的 table graphics object，所以这里 lower 成边框路径和单元格文本
- 全部页面完成后 -> `PDFDoc::SaveAs(...)`

所以这里已经能直观看到：DIR 不直接操作 PDF 底层对象流，而是借 SDK 作为“后端生成器”把抽象结构落地成合法 PDF。

## 3. 编译和运行结果

当前环境下已经验证通过：

- 编译命令使用 `g++ -std=c++11 -Ifoxit_sdk/include ... foxit_sdk/lib/libfsdk_linux64.so`
- 运行后成功生成 2 页 PDF
- `file output/foxit_dir_output.pdf` 识别结果为 `PDF document, version 1.7, 2 pages`
- `pdfinfo` 显示页数为 2，页面大小为 `595 x 842 pts (A4)`

这说明当前 WSL Ubuntu 22.04 环境下，这个 Foxit Linux SDK 至少已经能完成最小的 `DIR -> Foxit SDK -> PDF` 闭环。

## 4. 当前示例的边界

这个 demo 现在已经能 lower 文本、图片、路径和表格，但仍然是一个最小实验版本。

如果后续要更贴近论文里的多层 DIR，可以继续沿着 Foxit 自带示例扩展：

- `graphics_objects.cpp`：扩展 path/image/shading object
- `page_organization.cpp`：扩展页面插入、移动、导入
- 再往前一步可以继续补充更复杂对象类型，例如 form、annotation、复杂 path 或真实图片资源池