# 论文调研
OOXML文件又称Open XML文件，是一个意思

其遵循的国际标准是：ECMA-376 / ISO/IEC 29500
1. ISO Publicly Available Standards（部分可免费）
https://standards.iso.org/ittf/PubliclyAvailableStandards/index.html
搜：29500
有时会放旧版免费，但不保证有 29500
2. 国内标准平台（GB/T 等同采用）
OOXML 被转为中国国标：
GB/T 28458-2012 / GB/T 36345（等同 ISO/IEC 29500）
国家标准全文公开系统：
https://openstd.samr.gov.cn/
搜：GB/T 28458
可免费看全文（中文）
3. 学术 / 镜像（旧版存档）
MIT 存档（ECMA-376 1st 2006）：
http://web.mit.edu/~stevenj/www/ECMA-376.pdf



**grammar fuzzing**

或者叫structure aware fuzzing，就是一些软件的输入并不是像vim的输入，可以是无意义的字符串。而是必须依赖某种grammar的结构化的文件。针对这类软件的fuzz就称为grammar fuzzing。


**OpenXML文档格式解析**

1. 一堆 XML 文件
描述文字、表格、段落、样式、数据……
2. 资源文件
图片、视频、音频、字体等
3. 关系文件（.rels）
告诉程序：图片插在哪？样式用哪个？

### 已经调研的论文清单

直接把 OOXML 变异/fuzzing 作为主题的学术论文并不算多，更多论文是围绕 OOXML 的结构化测试、恶意文档分析、Office 攻击面研究，或者“文档格式 fuzzing”这类更泛化的方向。


**Multi-level Fuzzing for Document File Formats with Intermediate Representation**

最接近“文档格式变异/fuzzing”的论文线索。搜索结果摘要里明确提到文档文件包括 DOCX、PDF、HTML，并提出了 intermediate document representation，和现在做 OOXML/WPS 测试的思路非常接近。


**Detection of Malicious Office Open Documents (OOXML) Using Large Language Models: A Static Analysis Approach
**
这是 2025 年的 OOXML 静态分析论文。它不是 fuzzing 论文，但里面详细讲了 OOXML 的结构、Office2JSON 的提取流程，以及对文档内部 .xml、.rels、vbaProject.bin 等部件的分析，对理解“应该变异哪些部位”很有帮助。

**A Study of Office Open XML Document-Based Malicious Code Analysis and Detection**

这篇是 2020 年的 OOXML 恶意代码分析与检测工作，方向更偏结构分析和检测，不是 fuzzing，但和 Office 文档内部结构、恶意样本识别直接相关。
基于 Office Open XML 文档的恶意代码分析与检测方法研究
- 学位论文版：李德奎（Lee Deok-gyu），高丽大学信息保护学科，2020.01，指导教授：李相进（Lee Sang-jin）。
- 期刊版：李德奎（Lee Deok-gyu），李相进（Lee Sang-jin），《韩国信息安全与密码学学会论文志》30(3)，2020.06，pp.429-442，DOI 10.13089/JKIISC.2020.30.3.429。
- 核心内容：提出 OOXML 恶意文档检测方法与框架，收集恶意/正常样本后分析文档内的可疑对象要素，区分出 6 类有意义的疑似元素，并报告对恶意文件集的检测率达到 98.45%。
- 和当前工作相关性：这不是 fuzzing 论文，但它对理解 OOXML 的高风险结构、常见恶意载荷位置和变异优先级很有帮助。


**Analysis and Detection of Malicious Data Hidden in Slack Space on OOXML ...**

这篇更偏“在 OOXML 内部隐藏恶意数据”的检测。对你做变异时理解“哪些隐藏区域会影响解析器行为”很有帮助。
pdf链接：https://koreascience.or.kr/article/JAKO202310765540554.pdf

**OpenXMolar** 

也值得看，它是一个 MS OpenXML fuzzing framework，但它是项目/框架，不是论文。
仓库链接：https://github.com/debasishm89/OpenXMolar

**Office document security and privacy**

这是 WOOT 2020 的一篇 Office 文档安全论文。它不是单纯讲 fuzzing，但它非常有价值，因为它系统分析了 OOXML 和 ODF 的合法特性如何被滥用，并把攻击分成五类：DoS、隐私跟踪、信息泄露、数据篡改、代码执行。你如果要设计变异策略，这篇很有参考价值。


#  OXML software fuzz相关工作

### **openXMolar Fuzz Framework**
config.py文件是项目的配置文件。作用是：自动生成大量畸形的 .xps/.oxps 文档，用 Windows 自带的 xpsrchvw.exe 打开，监控程序是否崩溃，从而挖掘 XPS 查看器的漏洞。使用的调试器是：winappdbg。

**xps文件介绍**

XPS / OXPS 就是微软自己做的 “PDF 替代品”。
详细说
XPS = XML Paper Specification
微软在 Vista、Win7 时代推出的固定版式文档格式。
作用和 PDF 一模一样：
打开后排版不会乱
适合打印、传阅、存档
别人不能随便改内容
OXPS = Open XPS
是 XPS 的标准化升级版，Win8 以后开始用。
本质还是一样，只是后缀变成 .oxps。

**借鉴意义**

不能直接拿来用，不过有借鉴意义

OpenXMolar 是 Windows -only 工具
依赖 Windows 调试器（winappdbg）
依赖 Windows 路径、Office 路径
Linux 上无法运行
所以 不能直接拿来测 Linux 版 WPS。


**定义了openXML测试流程**

1. 解压 OpenXML 文档（docx/xlsx/pptx/xps）
2. 随机修改内部文件
3. 重新打包
4. 启动程序打开
5. 监控崩溃


测试流程：
解压 → 变异 → 打包 → 启动 → 监控 → 杀掉 → 循环

OpenXMolar 不是等 XPS 解析完成后自动关闭，而是把一次测试定义成一个固定时间窗口。对默认 XPS/OXPS 配置来说，它启动的是 xpsrchvw.exe，先观察是否崩溃；如果没崩，就在超时后强制结束。

1. 入口在 OpenXMolar.py:225。启动时会先开两个后台线程：一个做弹窗清理，一个做临时目录清理。样本先被解包并加载进内存，相关逻辑在 OfficeFileProcessor.py:31 和 OfficeFileProcessor.py:91。
2. 变异逻辑在 Mutator.py:47 和 Mutator.py:79。它先识别内部文件类型，再加载对应 handler，然后随机挑内部文件做变异。默认配置里，XPS/OXPS 映射到 xpsrchvw.exe，APP_RUN_TIME 是 1.5 秒，见 config.py:45 和 config.py:84。
3. 每一轮循环里，它先随机选一个基文件，再把变异后的内容重打包到临时目录，然后把这个临时文件传给被测程序。对应步骤在 OpenXMolar.py:242 和 OpenXMolar.py:244。
4. 启动后，winappdbg 会进入 debug.loop()，同时 PopUpKiller.py:29 持续扫描窗口弹窗。它对 XPS Viewer 的处理在 PopUpKiller.py:106，作用是把会卡住测试的对话框点掉，不是负责关闭主程序。
5. 结束主要有两条路径：如果触发访问冲突， OpenXMolar.py:111 的异常处理会记录 crash、复制样本、写报告，然后 kill 进程；如果没崩， OpenXMolar.py:150 的看门狗线程会在 APP_RUN_TIME 后主动 kill。正常退出只是附带情况，不是框架依赖的主要信号。


### **NAUTILUS: Fishing for Deep Bugs with Grammars** （CCFA NDSS19）
PDF下载网址是 [NDSS 论文 PDF 镜像](https://wcventure.github.io/FuzzingPaper/Paper/NDSS19_Nautilus.pdf)（论文页见 [NDSS Symposium](https://www.ndss-symposium.org/ndss-paper/nautilus-fishing-for-deep-bugs-with-grammars/)）。

这篇论文的核心问题是：**传统 coverage-guided mutational fuzzer 很难深入解释器/脚本引擎这类目标，因为输入先要过语法检查，再要过更高层的语义检查，普通 bit flip 很容易在前几层就被挡住。** NAUTILUS 的思路就是把 grammar fuzzing 和 coverage feedback 真的结合起来：一方面用文法保证生成出来的输入大体上还能过 parser，另一方面像 AFL 一样根据覆盖率保留“有价值”的输入，并继续重组这些有价值输入的结构片段。

论文里的整体工作流可以按下面 6 步理解：

1. **先准备 grammar，并把目标程序做成可反馈覆盖率的版本。** NAUTILUS 假设用户能提供输入语言的 grammar，或者直接复用现成 ANTLR grammar。然后它像 AFL 一样给目标程序加插桩，运行时把 basic block transition 记到共享 bitmap 里，再配合 forkserver 提高执行速度。也就是说，它不是一个纯生成器，而是一个真正依赖 coverage feedback 的 grammar fuzzer。

2. **把输入内部表示成 derivation tree，而不是单纯字符串。** 这是它和普通 grammar generator 很不一样的地方。NAUTILUS 在内部主要操作的是 derivation tree，字符串只是最后 unparse 出来的结果。这样做的好处是后面所有 mutation 都可以直接在语法树层级上操作，比如替换子树、复制递归结构、把一个“有趣输入”的某棵子树拼到另一个输入上，而不是在原始字节上瞎改。

3. **先从 grammar 随机生成一批初始样本，并用 coverage 筛一遍。** 论文里会先从 grammar 生成大约 1000 个初始输入。这里作者还专门讨论了生成策略：如果只是按规则天真随机，会因为 grammar 结构偏置而过度生成某些形状的树，所以它还用了更均匀的 tree generation 思路，尽量让不同规则/不同长度的树都能被抽到。初始样本跑过目标程序后，只有触发了新 coverage 的输入才会留下来。

4. **对“新覆盖样本”先做 minimization，再放进队列。** 这一步和 AFL 的 testcase cmin/tmin 思想很像，但它做的是 grammar/tree-aware 的最小化。论文用了两类最小化：
	- **Subtree minimization**：把某个子树替换成从同一 non-terminal 能生成的最小子树，只要新 coverage 还在，就保留更小版本。
	- **Recursive minimization**：专门识别递归结构，尽量把递归层数压短。

	这样得到的样本更短、执行更快、后续 mutation 空间也更容易控制。

5. **进入 coverage-guided queue，按不同状态做 grammar-aware mutation。** 这是 NAUTILUS 最核心的一步。它的队列条目不是简单只有“保留/丢弃”，而是分阶段处理：`init -> det -> detafl -> random`。不同阶段用的 mutation 也不同：
	- **Rules mutation**：对树中节点，尝试把当前 rule 换成同一 non-terminal 的其他 rule，看能不能打开新路径。
	- **Random mutation**：随机选一个节点，用同一 non-terminal 下新生成的随机子树替换它。
	- **Random recursive mutation**：专门针对递归非终结符，把递归结构重复多次，快速制造更深层嵌套。
	- **Splicing mutation**：把一个有趣输入中的子树，拼接到另一个有趣输入的相同 non-terminal 位置上，这本质上是 grammar-aware 的结构化 splice。
	- **AFL mutation**：在终结符字符串层面再做 bit flip、算术变异、interesting values 等经典 AFL 变异。论文这里的做法很巧：即便这样改出来的字符串不再严格符合 grammar，它也把这段内容封装成该 non-terminal 的一个 custom rule，局部挂回原树里，所以既保留了树结构，也允许出现“略带畸形”的终端片段。

6. **把 derivation tree unparse 成真实输入，运行目标程序，根据结果决定保存、丢弃或记 crash。** 如果执行崩溃，就把触发崩溃的输入单独保存；如果没有崩，但带来了新 coverage，就把对应 tree 加回队列继续迭代；如果既不崩也没有新 coverage，就直接丢弃。论文还特别强调，真实世界里的很多语言并不完全是严格 CFG，所以它支持给 grammar 规则加 Turing-complete 的 unparse script，在最终输出时做语义修正，例如让 XML 的开始标签和结束标签名字保持一致。这使得 NAUTILUS 不只是在“过语法”，而是在尽量保持更高层的语义正确性。

如果把这篇论文的方法压缩成一句话，它的工作流就是：**给目标插桩并导入 grammar -> 生成 derivation tree 初始样本 -> 用 coverage 选出有价值样本 -> 做 tree-aware minimization -> 在 rule/subtree/recursion/splice/AFL 多种 mutation 下继续演化 -> unparse 成真实输入并根据 coverage/crash 更新队列**。

这篇论文最值得借鉴的地方在于，它证明了 **“grammar 并不一定意味着只能做静态生成，feedback 也不一定只能和字节级 mutator 绑定”**。对结构化格式而言，更有效的路线往往是：先在抽象结构层保证输入能深入解析，再在结构层和终端字节层之间来回切换，兼顾“能过 parser”和“能打到深层代码”这两个目标。

如果进一步和更早的 grammar fuzzing 工作对比，NAUTILUS 的**真正创新点并不是“首次提出 grammar fuzzing”**，因为在它之前已经有 LangFuzz、IFuzzer、Skyfire，甚至更早还有 Grammar-based Whitebox Fuzzing 这类工作。NAUTILUS 的推进主要体现在下面几件事被放进了同一套框架里：

1. **把 grammar fuzzing 和 coverage-guided greybox fuzzing 真正绑在一起。** 前面的很多 grammar fuzzing 工作更偏向“按 grammar 生成输入”或者“按 grammar 重组已有样本片段”，但 NAUTILUS 会像 AFL 一样根据覆盖率筛选输入，只保留能带来新 path 的 derivation tree，再继续做后续 mutation。也就是说，它把 grammar fuzzing 从“盲生成”推进成了“反馈驱动的结构化搜索”。

2. **不强依赖现成 corpus 才能起步。** LangFuzz、IFuzzer、Skyfire 这类方法大多和 corpus 关系较强，要么从语料中抽片段重组，要么从 corpus 学规则概率、生成 seed。NAUTILUS 则可以从 grammar 直接生成一批初始样本，自举启动，再靠 coverage feedback 和队列迭代逐步积累“有价值输入”。这一点让它不再只是 corpus-assisted grammar fuzzer，而更像一个真正独立的 grammar-based greybox fuzzer。

3. **把 derivation tree 作为主数据结构，而不是把 grammar 只当成前端生成器。** 在 NAUTILUS 里，字符串只是最终 unparse 的结果，真正被操作的是 derivation tree。本质上，它围绕树设计了完整的 subtree mutation、recursive mutation、splicing mutation、subtree minimization、recursive minimization。这说明 grammar 在这里不只是“帮助生成一份合法输入”，而是成了整个 fuzzing 过程的核心表示层。

4. **把 AFL 风格的终端变异纳入 grammar tree 框架，而不是完全二选一。** 这也是一个比较巧的点。普通做法往往是要么严格 grammar-based，要么直接字节级 mutation。NAUTILUS 则允许对终结符字符串做 bit flip、interesting values、算术变异等 AFL 风格操作，然后把变异后的结果作为 local custom rule 挂回原树。这样既保留了大体结构，又允许局部输入脱离严格 grammar 约束，获得更强的异常性。

5. **目标不只是“过语法”，而是尽量保留更高层的语义正确性。** 解释器、编译器、DOM 引擎之类目标通常不只做 syntax check，还会做 semantic check。NAUTILUS 一方面通过 coverage feedback 去保留那些更有语义价值的输入片段，另一方面又通过可脚本化的 unparse 机制去表达一些超出纯 CFG 的约束，例如 XML 开始标签和结束标签配对。这让它相比许多只停留在“语法正确输入生成”的前作更进一步。

如果把 NAUTILUS 相对前作的创新点压缩成一句话，可以概括成：**它不是发明了 grammar fuzzing，而是把 derivation-tree-based grammar generation/mutation、coverage-guided greybox feedback、tree-aware minimization，以及局部 AFL 式终端变异，整合成了一套统一的 fuzzing 工作流。**

### Modifier **Multi-level Fuzzing for Document File Formats with Intermediate Representation**：（CCFB ISSRE 2024）

 
这篇论文的核心不是“直接为 PDF、HTML、DOCX 分别写 grammar 和 mutator”，而是先定义一个和具体格式解耦的中间表示 **DIR（Document Intermediate Representation）**，再把 fuzzing 的大部分工作放到 DIR 上完成。作者把一个文档统一抽象成：**document = pages + objects + attributes**。也就是说，不管底层是 PDF、HTML 还是其他文档格式，在 DIR 里都先表示成“若干页面”，每个页面上有文本、图片、表格、表单等对象，每个对象再带位置、大小、字体、颜色、数据、事件等属性。这样做的直接好处是：生成器和大部分变异器只需要围绕 DIR 写一套，就不必为每一种文档格式单独重做一遍。

论文里的整体工作流程可以按下面 6 步理解：

1. **先准备 seed DIR 文档**。作者不是只靠从零生成，而是同时用了两条路：
	- 一条路是按照 DIR 的 grammar 随机生成文档；
	- 另一条路是把已有真实文档先转换成 DIR，再拿这些 DIR 当 seed。论文里已经实现了 PDF 和 HTML 到 DIR 的 converter。PDF 这边因为本身就接近“页-对象-属性”的组织方式，所以比较容易映射；HTML 因为原生没有 page 概念，作者就把整个 HTML 文件先视为一个 DIR page，再把其中元素布局到这一个 page 上。

2. **在 DIR 层做多级变异，而不是只做单一粒度的变异**。这是论文第二个关键点。作者认为已有工作通常只在一个层级上 mutation，比如只换子树或者只改属性，这会限制搜索空间，所以它把变异拆成三层：
	- **Page-level mutation**：复制页面、删除页面、重排页面、从其他文档借页面（类似 splice）。
	- **Object-level mutation**：在单页内部对对象做复制、删除、重排、跨文档借对象，以及插入新对象；如果对象之间有依赖关系，还会尽量保持依赖不被完全破坏。
	- **Attribute-level mutation**：给对象增删替换属性，或者直接改属性值，比如把文本内容改长、替换颜色/字体/位置等。论文这里还特意放宽了约束，不完全死守 DIR grammar，这样可以故意制造“不太合理但仍可能触发深层解析路径”的输入。

3. **把变异后的 DIR lowering 成目标格式文档**。DIR 不是最终给程序喂的输入，还要落回具体格式。论文这里的做法很实用：不是手写一整套复杂格式生成器，而是尽量复用现成 SDK。比如 PDF 用 Foxit PDF SDK，HTML 用 WebToolKit。也就是说，DIR 里有 page/object/attribute，lowering 时就调用 SDK 提供的接口去建 page、插对象、设属性，最后导出成 PDF/HTML 文件。这一步体现了作者的一个重要观点：真正困难的底层格式细节，不一定要自己完全理解并手写，只要 SDK 已经帮你封装好了，就可以借它把 DIR 落地。

4. **为了避免“每次都跑真实目标程序拿 coverage 太慢”，作者把反馈前移到 API sequence 层**。这是论文里很值得注意的一点。DIR 被 lowering 时，本质上会对应成一串 SDK API 调用序列；于是作者把这串 API sequence 看成 DIR 的另一种表示形式。随后不一定每轮都先生成最终 PDF/HTML 再跑目标程序，而是先对 API sequence 做 coverage-guided mutation，用 AFL++ 的 FRIDA mode 只收集 SDK 相关代码的覆盖率。这样可以更快筛出有价值的 DIR/API seed，减少“生成文档 -> 启动重型解析器 -> 才知道没价值”的成本。

5. **再做一层 post-DIR mutation，专门突破 SDK 的限制**。作者发现如果只靠 SDK 来 lowering，生成出来的文档往往还是“太规矩”了，因为 SDK 自己会做很多合法性约束，比如只允许特定旋转角度、只允许合法对象组合、不给你构造明显畸形的细粒度结构。为了解决这个问题，论文在 lowering 之后又加了一层针对目标文档本体的变异：
	- 对 PDF，直接改内部 PDF object；
	- 对 HTML，直接改 HTML element；
	- 变异方式包括 same-type、cross-type、type-independent 三类；
	- 最底层再叠加 AFL++ 这种经典字节级随机 mutation。

	这一层的作用很关键：DIR + SDK 负责高层结构正确性和跨格式复用，**post-DIR mutation 负责打破 SDK 带来的“过于合法、过于保守”的限制，让输入重新获得异常性和攻击性。**

6. **把有价值的样本重新放回队列，持续迭代**。如果某个 DIR 文档对应的 API sequence 或最终文档带来了新的覆盖率，它就会被保留下来继续做后续 mutation。论文里还设计了 seed 排序策略：优先考虑那些能覆盖较少见 API、而且执行时间较短的样本，因为这类 seed 更可能带来高收益、低成本的探索。对单个 seed，如果连续一段时间没有新覆盖，再切换到下一个 seed。

如果把这篇论文的方法压缩成一句话，它的工作流就是：**真实文档/随机生成 -> 转成统一 DIR -> 在 page/object/attribute 三层做结构化变异 -> 用 SDK lowering 到目标格式 -> 再做 post-DIR 与 AFL++ 式底层变异 -> 根据 coverage 保留高价值样本继续迭代**。

这篇论文最有借鉴意义的地方在于，它把“结构保持能力”和“异常输入制造能力”分成了两层来做：DIR 负责把文档维持在一个可组织、可迁移、可跨格式复用的抽象层；post-DIR mutation 负责把样本推向更激进、更容易触发解析边界条件的状态。对于 OOXML/WPS 这类目标，这个思路很有参考价值，因为你也可以先设计自己的统一文档 IR，再把 OOXML 内部部件、页面对象、样式对象、关系对象等放到不同层级上做 mutation，而不是一开始就直接在 zip 包和 XML 文本上盲改。



### 直接拿恶意代码去攻击WPS解析程序？

根据上一节“其他”中相关论文的介绍，我想可以使用包含恶意代码的 **恶意文档**去攻击WPS解析程序，造成crash？
如果wps解析程序无法应对恶意代码，那么马上就会产生crash。

**Analysis and Detection of Malicious Data Hidden in Slack Space on OOXML-based Corrupted MS-Office Digital Files **

主要工作在于研究如何在OOXML文件中注入恶意数据，对于fuzz流程来说意义不是特别大。不过可以拿来检测wps处理OOXML文件中恶意代码能力。

主要工作是研究被篡改或损坏的 OOXML Office 文件中，如何在 slack space 里隐藏恶意数据，以及如何检测这类隐藏载荷。创新点在于它关注文件内部的隐藏空隙和附加数据，而不是只看宏或显式脚本，这对理解文档容器里那些不显眼但高风险的区域很有帮助。对应 PDF 链接是：https://koreascience.or.kr/article/JAKO202310765540554.pdf。

**A Study of Office Open XML Document-Based Malicious Code Analysis and Detection / 基于 Office Open XML 文档的恶意代码分析与检测方法研究**：

主要工作是收集恶意与正常的 OOXML 样本，分析文档内部的可疑对象要素，并提出一套恶意文档检测方法。创新点在于它把 OOXML 的内部对象当作核心分析单位，归纳出 6 类有意义的疑似元素，并给出了较高的检测率，说明对象级特征对 OOXML 恶意文档识别很有效。


**Detection of Malicious Office Open Documents (OOXML) Using Large Language Models: A Static Analysis Approach**：

主要工作是把 OOXML 文档的结构提取出来，再结合大语言模型做静态恶意文档识别。创新点在于把 LLM 引入 OOXML 安全分析流程，同时强调先做结构化抽取，再基于 .xml、.rels、vbaProject.bin 等部件建模，这比直接处理原始压缩包更可解释，也更容易定位可疑区域。


**Office document security and privacy**

主要工作是系统分析 OOXML 和 ODF 文档中哪些“合法特性”会被滥用，并把攻击面归纳为 DoS、隐私跟踪、信息泄露、数据篡改和代码执行五类。创新点在于它不是只盯着恶意宏或单个漏洞，而是从文档格式本身出发做攻击面分类，这对设计变异策略和防御策略都很有参考价值。

### 其他


**Grammar-based Whitebox Fuzzing**：（PLDI 2008）

主要工作是把 whitebox fuzzing / symbolic execution 和 grammar 结合起来，专门解决编译器、解释器这类“输入必须高度结构化”的目标。传统 whitebox fuzzing 很容易卡死在 lexer / parser 早期阶段，而这篇论文的做法是：让 symbolic execution 直接生成 grammar-aware 的约束，再交给自定义的 grammar-based constraint solver 求解，确保新输入既能满足路径约束，又仍然符合 grammar。论文用 IE7 的 JavaScript 解释器做实验，结果显示相比普通 whitebox fuzzing，它能更深地进入代码生成模块，并且用更少测试用例拿到更高 coverage。创新点在于它不是只用 grammar 来“生成合法输入”，而是把 grammar 放进约束求解过程里，成为 symbolic test generation 的一部分。

如果把这篇论文的方法按工作过程展开，可以理解成下面 6 步：

1. **先从一个合法 seed 输入开始执行目标程序，并做 symbolic execution。** 普通 whitebox fuzzing 会把输入字节看成符号变量，沿程序执行路径收集 path constraint，然后把其中某个条件取反，求解出一个新输入。但对解释器、编译器这类目标来说，输入首先要通过 lexer 和 parser；如果只在字节层求解，生成出来的输入往往连语法检查都过不了，所以执行会反复卡在前端，难以进入后面的语义分析、优化或代码生成模块。

2. **把“符号变量”的粒度从字节提升到 grammar token。** 这是论文最关键的改动之一。它不再只把原始字符当成符号，而是把 lexer 返回的 token 也当成符号对象来跟踪。这样路径约束里出现的就不只是“第几个字节等于某个值”，而更像是“第 0 个 token 必须是 function”“第 1 个 token 必须是 id”“第 2 个 token 必须是左括号”这种约束。换句话说，程序路径需求被表达成了**与 grammar 单元对齐的约束**，而不是零散的字节约束。

3. **沿当前执行路径收集 token-level path constraint，然后系统地取反。** 这一步和传统 whitebox fuzzing 的大框架是一致的：先跑出一条路径，记录沿途条件；然后依次选取某个分支条件，把它取反，尝试构造能走向新路径的新测试用例。区别在于，这里被取反和求解的对象已经是 token 级约束。例如，原路径可能要求某个位置是 `}`，那么新一轮就尝试令它不是 `}`，再看看是否还能构造出一份整体上合法的程序输入。

4. **把取反后的路径约束交给 grammar-based constraint solver，而不是普通约束求解器。** 论文指出，单靠通用求解器并不能保证结果仍属于目标语言；因此它设计了一个 grammar-based constraint solver，专门求“路径约束”和“输入 grammar”两者的交集。更具体地说，它会把当前路径约束转成一个正则语言近似，再与上下文无关文法逐步做交集逼近；在这个过程中不断展开 grammar 产生式，并把与 token 约束矛盾的分支剪掉。最后如果剩余 grammar 非空，就从中生成一个新的具体字符串。这样得到的新输入不只是“满足某条分支条件”，而是“满足分支条件且仍然语法合法”。

5. **通过 unroll-and-prune 机制控制求解复杂度。** 因为“上下文无关语言与路径约束求交”本身很难精确求解，论文采用的是实用主义策略：一边展开 grammar，一边剪枝。哪些产生式一看就不可能满足当前 token constraint，就立即删除；哪些递归结构还不够具体，就继续展开若干层。这个过程本质上是在用 grammar 引导搜索空间收缩，让求解器避免枚举大量显然不合法的输入。它不是在所有情况下都做完全精确的语言求交，而是在可接受成本下尽量保留“可能通向新路径的合法输入”。

6. **用新生成的合法输入重新执行程序，并持续迭代。** 只要 grammar-based solver 成功生成了新输入，就把它喂回目标程序，再收集新的执行路径与约束，继续做下一轮分支翻转和求解。这样一来，fuzzer 不会总是在 parser 前面打转，而是能逐步穿过语法前端，进入更深的解释、优化、代码生成等模块。论文实验里，正是因为这套流程能持续产生“满足路径需求且保持结构合法”的输入，所以相比普通 whitebox fuzzing，它明显更容易到达深层代码。

如果把这篇论文压缩成一句话，它的核心工作流就是：**对结构化语言输入做 symbolic execution，但约束不再停留在字节层，而是提升到 token/grammar 层；然后用 grammar-based constraint solver 求“路径约束 + grammar”的交集，从而持续生成既合法又能探索新路径的测试输入。**


**LangFuzz: Fuzzing with Code Fragments**：（USENIX Security 2012）

借鉴意义不大，因为我们手里缺少已有失败测试集。

主要工作是把 grammar-based generation 和已有 bug 相关代码片段重组结合起来，用于黑盒 fuzzing JavaScript / PHP 解释器。LangFuzz 的输入有三部分：语言 grammar、样例代码、以及已有失败测试集；它会先按 grammar 保证生成结果在语法上可执行，再从历史上“出过问题”的代码片段里抽取 fragment，重组到新程序里。这样做的核心思想是：完全随机生成虽然合法，但不一定足够“危险”；如果把已有问题代码片段重新拼接到新上下文里，更容易触发新漏洞。论文在 Mozilla JavaScript engine 和 PHP 上找到了大量新缺陷。创新点在于它提出了一条很典型的 interpreter grammar fuzzing 路线：**grammar 保证结构正确，fragment reuse 提高触发 bug 的概率**。


**IFuzzer: An Evolutionary Interpreter Fuzzer using Genetic Programming**：（ESORICS 2016 B会）

主要工作是把 genetic programming / evolutionary fuzzing 引入解释器 fuzzing。IFuzzer 同样以 grammar 为基础，先把程序解析成 parse tree / AST，再围绕这些树做 crossover 和 mutation，而不是直接在原始字符串上改。它会从 grammar 和 sample code 中构建 fragment pool，然后通过 fitness function 去指导哪些输入更值得保留和继续进化。论文针对 JavaScript 解释器做实验，发现了多批 bug，并且把自己的效果和 LangFuzz 做了对比。创新点在于它把“解释器 fuzzing”明确建模成一个进化搜索问题：输入不仅要 syntactically valid，还要在 evolutionary 过程中逐步长成更 uncommon、更可能触发异常行为的代码。


**Skyfire: Data-Driven Seed Generation for Fuzzing**：（IEEE S&P 2017 4大顶会）

主要工作不是做一个完整 grammar fuzzer，而是做一个**高质量 seed 生成器**，专门给 AFL 这类 mutation-based fuzzer 提供更适合结构化输入的初始样本。Skyfire 的输入是 grammar 和 corpus，它先把样本解析成 AST，再学习一个 probabilistic context-sensitive grammar（PCSG），不仅建模语法特征，还尽量把一些语义约束也编码进去。随后它偏向低概率 production rule 去生成“不常见但仍合理”的 seed，再通过 seed selection 去重，最后还会做保持结构的 seed mutation。创新点在于它不满足于只生成“合法输入”，而是试图生成**正确、少见、结构多样、能推动覆盖率的 seed**，从而把 grammar learning 和 coverage-guided mutation fuzzing 衔接起来。


**Erroneous Kubernetes Object Generation using Structure-aware Fuzzing**：（Master Thesis 2024）

这篇虽然不是传统 grammar fuzzing 论文，而是一篇学位论文，但它很值得放进 related_papers，因为它讨论的是更广义的 structure-aware fuzzing。主要工作是面向 Kubernetes 自定义配置对象，设计一个 erroneous object generator，用结构感知方式生成“真实世界里可能出现的错误配置对象”，并比较 structure-aware fuzzer 与 string-based fuzzer 的效果。论文的目标不是解释器 grammar，而是依赖对象结构、字段关系和 schema 约束去生成错误对象，从而帮助 Kubernetes 更快暴露配置处理和错误定位问题。创新点在于它把 fuzzing 的重点从“随机字符串”转移到“对象结构级错误配置生成”，这和 grammar fuzzing 的思想本质相通：都在利用输入的结构模型，而不是直接盲改字节。



**Learn&Fuzz: Machine Learning for Input Fuzzing**：PDF下载网址是 [Microsoft Research 版](https://www.microsoft.com/en-us/research/wp-content/uploads/2017/01/main-public.pdf)（也有 arXiv 预印本 [1701.07232](https://arxiv.org/pdf/1701.07232)）。

主要工作是把样本输入交给神经网络做统计学习，自动生成适合 fuzz 的输入语法，并把学习到的输入概率分布用于指导后续 mutation；论文以 PDF 解析器为案例，讨论了“学习输入结构”和“打破结构覆盖新路径”之间的张力。创新点在于把机器学习直接用于 grammar 生成，并提出了用 learnt distribution 来决定哪里更值得 fuzz，这让 grammar-based fuzzing 更自动化。


**FreeDom: Engineering a State-of-the-Art DOM Fuzzer**：（CCFA CCS20）

PDF下载网址是 [作者页 PDF](https://taesoo.kim/pubs/2020/xu:freedom.pdf)（也可见 [ACM DOI 页面](https://doi.org/10.1145/3372297.3423340)）。

主要工作是做一个同时支持生成式和 coverage-guided 的 DOM fuzz 框架，用 FD-IR 这种 context-aware 中间表示描述 HTML，并通过浏览器自终止提升吞吐量，专门面向浏览器 DOM 引擎这类复杂目标。创新点在于它把 HTML 的数据依赖、结构信息和 fuzz 操作放进同一个中间表示里，既能做高质量生成，也能做覆盖率驱动 mutation；论文还明确展示了生成式与覆盖驱动两条路线各自的优势和局限。



**Domato**：它没有找到单独的论文 PDF，更接近 Project Zero 的公开 fuzz 工具；原始资料是 [The Great DOM Fuzz-off of 2017](https://projectzero.google/2017/09/the-great-dom-fuzz-off-of-2017.html) 和 [GitHub 仓库](https://github.com/googleprojectzero/domato)。主要工作是生成式 DOM fuzzer，使用 HTML/CSS/JavaScript 语法规则从零生成页面，并通过从 Chrome 的 .idl 和 layout tests 提取再人工修订的 grammar 来提高样本质量。创新点在于它把 DOM fuzz 变成了一个可复用、可扩展的 grammar engine，并支持多种 DOM API、事件处理和脚本回调；后来 FreeDom 也把它当作对照基线来比较。

