import io
import zipfile


def build_settings():
    return b'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:settings xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">
  <w:zoom w:percent="100"/>
  <w:defaultTabStop w:val="720"/>
  <w:characterSpacingControl w:val="doNotCompress"/>
</w:settings>'''


def build_web_settings():
    return b'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:webSettings xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">
  <w:optimizeForBrowser/>
  <w:allowPNG/>
</w:webSettings>'''


def build_numbering():
    return b'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:numbering xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">
  <w:abstractNum w:abstractNumId="0">
    <w:multiLevelType w:val="singleLevel"/>
    <w:lvl w:ilvl="0">
      <w:start w:val="1"/>
      <w:numFmt w:val="decimal"/>
      <w:lvlText w:val="%1."/>
      <w:lvlJc w:val="left"/>
      <w:pStyle w:val="ListNumber"/>
      <w:pPr><w:ind w:left="720" w:hanging="360"/></w:pPr>
    </w:lvl>
  </w:abstractNum>
  <w:abstractNum w:abstractNumId="1">
    <w:multiLevelType w:val="singleLevel"/>
    <w:lvl w:ilvl="0">
      <w:start w:val="1"/>
      <w:numFmt w:val="bullet"/>
      <w:lvlText w:val="&#8226;"/>
      <w:lvlJc w:val="left"/>
      <w:pStyle w:val="ListBullet"/>
      <w:pPr><w:ind w:left="720" w:hanging="360"/></w:pPr>
      <w:rPr><w:rFonts w:ascii="Symbol" w:hAnsi="Symbol"/></w:rPr>
    </w:lvl>
  </w:abstractNum>
  <w:abstractNum w:abstractNumId="2">
    <w:multiLevelType w:val="singleLevel"/>
    <w:lvl w:ilvl="0">
      <w:start w:val="1"/>
      <w:numFmt w:val="lowerLetter"/>
      <w:lvlText w:val="%1)"/>
      <w:lvlJc w:val="left"/>
      <w:pStyle w:val="ListAlpha"/>
      <w:pPr><w:ind w:left="720" w:hanging="360"/></w:pPr>
    </w:lvl>
  </w:abstractNum>
  <w:num w:numId="1"><w:abstractNumId w:val="0"/></w:num>
  <w:num w:numId="2"><w:abstractNumId w:val="1"/></w:num>
  <w:num w:numId="3"><w:abstractNumId w:val="2"/></w:num>
</w:numbering>'''


def build_font_table():
    return b'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:fonts xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">
  <w:font w:name="Calibri Light">
    <w:panose1 w:val="020F0302020204030204"/>
    <w:charset w:val="00"/>
    <w:family w:val="swiss"/>
    <w:pitch w:val="variable"/>
  </w:font>
  <w:font w:name="Calibri">
    <w:panose1 w:val="020F0502020204030204"/>
    <w:charset w:val="00"/>
    <w:family w:val="swiss"/>
    <w:pitch w:val="variable"/>
  </w:font>
  <w:font w:name="Times New Roman">
    <w:panose1 w:val="02020603050405020304"/>
    <w:charset w:val="00"/>
    <w:family w:val="roman"/>
    <w:pitch w:val="variable"/>
  </w:font>
</w:fonts>'''


def build_theme():
    return b'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<a:theme xmlns:a="http://schemas.openxmlformats.org/drawingml/2006/main" name="Office Theme">
  <a:themeElements>
    <a:clrScheme name="Office">
      <a:dk1><a:sysClr val="windowText" lastClr="000000"/></a:dk1>
      <a:lt1><a:sysClr val="window" lastClr="FFFFFF"/></a:lt1>
      <a:accent1><a:srgbClr val="4F81BD"/></a:accent1>
      <a:accent2><a:srgbClr val="C0504D"/></a:accent2>
      <a:accent3><a:srgbClr val="9BBB59"/></a:accent3>
      <a:accent4><a:srgbClr val="8064A2"/></a:accent4>
      <a:accent5><a:srgbClr val="4BACC6"/></a:accent5>
      <a:accent6><a:srgbClr val="F79646"/></a:accent6>
      <a:hlink><a:srgbClr val="0000FF"/></a:hlink>
      <a:folHlink><a:srgbClr val="800080"/></a:folHlink>
    </a:clrScheme>
    <a:fontScheme name="Office">
      <a:majorFont>
        <a:latin typeface="Calibri Light"/>
        <a:ea typeface=""/>
        <a:cs typeface=""/>
      </a:majorFont>
      <a:minorFont>
        <a:latin typeface="Calibri"/>
        <a:ea typeface=""/>
        <a:cs typeface=""/>
      </a:minorFont>
    </a:fontScheme>
    <a:fmtScheme name="Office"><a:fillStyleLst/><a:lnStyleLst/><a:effectStyleLst/><a:bgFillStyleLst/></a:fmtScheme>
  </a:themeElements>
</a:theme>'''


def build_app_props():
    return b'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Properties xmlns="http://schemas.openxmlformats.org/officeDocument/2006/extended-properties"
 xmlns:vt="http://schemas.openxmlformats.org/officeDocument/2006/docPropsVTypes">
  <Application>Microsoft Office Word</Application>
  <DocSecurity>0</DocSecurity>
  <ScaleCrop>false</ScaleCrop>
  <HeadingPairs><vt:vector size="2" baseType="variant"><vt:variant><vt:lpstr>Title</vt:lpstr></vt:variant><vt:variant><vt:i4>1</vt:i4></vt:variant></vt:vector></HeadingPairs>
  <TitlesOfParts><vt:vector size="1" baseType="lpstr"><vt:lpstr>Document</vt:lpstr></vt:vector></TitlesOfParts>
  <Company>Nautilus</Company>
  <LinksUpToDate>false</LinksUpToDate>
  <SharedDoc>false</SharedDoc>
  <HyperlinksChanged>false</HyperlinksChanged>
  <AppVersion>1.0</AppVersion>
</Properties>'''


def build_core_props():
    return b'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<cp:coreProperties xmlns:cp="http://schemas.openxmlformats.org/package/2006/metadata/core-properties"
 xmlns:dc="http://purl.org/dc/elements/1.1/"
 xmlns:dcterms="http://purl.org/dc/terms/"
 xmlns:dcmitype="http://purl.org/dc/dcmitype/"
 xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
  <dc:title>Nautilus Generated DOCX</dc:title>
  <dc:creator>Nautilus</dc:creator>
  <cp:lastModifiedBy>Nautilus</cp:lastModifiedBy>
  <dcterms:created xsi:type="dcterms:W3CDTF">2026-04-13T00:00:00Z</dcterms:created>
  <dcterms:modified xsi:type="dcterms:W3CDTF">2026-04-13T00:00:00Z</dcterms:modified>
</cp:coreProperties>'''


def build_document_rels():
    return b'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
  <Relationship Id="rIdStyles" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles" Target="styles.xml"/>
  <Relationship Id="rIdSettings" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/settings" Target="settings.xml"/>
  <Relationship Id="rIdNumbering" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/numbering" Target="numbering.xml"/>
  <Relationship Id="rIdFontTable" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/fontTable" Target="fontTable.xml"/>
  <Relationship Id="rIdTheme" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/theme" Target="theme/theme1.xml"/>
  <Relationship Id="rIdWebSettings" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/webSettings" Target="webSettings.xml"/>
  <Relationship Id="rIdImage1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/image" Target="media/image1.png"/>
  <Relationship Id="rIdHyperlink1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/hyperlink" Target="https://example.com/nautilus-docx" TargetMode="External"/>
</Relationships>'''


def build_image_png():
    return (
        b"\x89PNG\r\n\x1a\n"
        b"\x00\x00\x00\rIHDR"
        b"\x00\x00\x00\x01\x00\x00\x00\x01\x08\x02\x00\x00\x00"
        b"\x90wS\xde"
        b"\x00\x00\x00\x0cIDATx\x9cc``\xf8\xcf\xc0\x00\x00\x03\x01\x01\x00"
        b"\xc9\xfe\x92\xef"
        b"\x00\x00\x00\x00IEND\xaeB`\x82"
    )


def build_styles():
    return b'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<w:styles xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">
  <w:docDefaults>
    <w:rPrDefault>
      <w:rPr>
        <w:rFonts w:asciiTheme="minorHAnsi" w:hAnsiTheme="minorHAnsi" w:eastAsiaTheme="minorEastAsia" w:cstheme="minorBidi"/>
        <w:sz w:val="22"/>
        <w:szCs w:val="22"/>
        <w:lang w:val="en-US" w:eastAsia="zh-CN" w:bidi="ar-SA"/>
      </w:rPr>
    </w:rPrDefault>
    <w:pPrDefault/>
  </w:docDefaults>
  <w:style w:type="paragraph" w:default="1" w:styleId="Normal">
    <w:name w:val="Normal"/>
    <w:rPr>
      <w:rFonts w:asciiTheme="minorHAnsi" w:hAnsiTheme="minorHAnsi"/>
    </w:rPr>
    <w:qFormat/>
  </w:style>
  <w:style w:type="paragraph" w:styleId="Title">
    <w:name w:val="Title"/>
    <w:basedOn w:val="Normal"/>
    <w:qFormat/>
    <w:rPr>
      <w:rFonts w:asciiTheme="majorHAnsi" w:hAnsiTheme="majorHAnsi"/>
      <w:b/>
      <w:color w:themeColor="accent1"/>
      <w:sz w:val="40"/>
    </w:rPr>
  </w:style>
  <w:style w:type="paragraph" w:styleId="Heading1">
    <w:name w:val="heading 1"/>
    <w:basedOn w:val="Normal"/>
    <w:qFormat/>
    <w:rPr>
      <w:rFonts w:asciiTheme="majorHAnsi" w:hAnsiTheme="majorHAnsi"/>
      <w:b/>
      <w:color w:themeColor="accent2"/>
      <w:sz w:val="32"/>
    </w:rPr>
  </w:style>
  <w:style w:type="paragraph" w:styleId="ListNumber">
    <w:name w:val="List Number"/>
    <w:basedOn w:val="Normal"/>
    <w:qFormat/>
    <w:pPr><w:ind w:left="720"/></w:pPr>
  </w:style>
  <w:style w:type="paragraph" w:styleId="ListBullet">
    <w:name w:val="List Bullet"/>
    <w:basedOn w:val="Normal"/>
    <w:qFormat/>
    <w:pPr><w:ind w:left="720"/></w:pPr>
  </w:style>
  <w:style w:type="paragraph" w:styleId="ListAlpha">
    <w:name w:val="List Alpha"/>
    <w:basedOn w:val="Normal"/>
    <w:qFormat/>
    <w:pPr><w:ind w:left="720"/></w:pPr>
  </w:style>
  <w:style w:type="character" w:styleId="Hyperlink">
    <w:name w:val="Hyperlink"/>
    <w:basedOn w:val="DefaultParagraphFont"/>
    <w:uiPriority w:val="99"/>
    <w:unhideWhenUsed/>
    <w:rPr>
      <w:color w:themeColor="hyperlink"/>
      <w:u w:val="single"/>
    </w:rPr>
  </w:style>
  <w:style w:type="character" w:default="1" w:styleId="DefaultParagraphFont">
    <w:name w:val="Default Paragraph Font"/>
    <w:semiHidden/>
    <w:unhideWhenUsed/>
  </w:style>
  <w:style w:type="table" w:styleId="TableGrid">
    <w:name w:val="Table Grid"/>
    <w:tblPr>
      <w:tblBorders>
        <w:top w:val="single" w:sz="4" w:space="0" w:color="000000"/>
        <w:left w:val="single" w:sz="4" w:space="0" w:color="000000"/>
        <w:bottom w:val="single" w:sz="4" w:space="0" w:color="000000"/>
        <w:right w:val="single" w:sz="4" w:space="0" w:color="000000"/>
        <w:insideH w:val="single" w:sz="4" w:space="0" w:color="000000"/>
        <w:insideV w:val="single" w:sz="4" w:space="0" w:color="000000"/>
      </w:tblBorders>
    </w:tblPr>
  </w:style>
</w:styles>'''


def build_docx(
    document_xml,
    _io=io,
    _zipfile=zipfile,
    _build_styles=build_styles,
    _build_settings=build_settings,
  _build_web_settings=build_web_settings,
    _build_numbering=build_numbering,
  _build_font_table=build_font_table,
  _build_theme=build_theme,
  _build_app_props=build_app_props,
  _build_core_props=build_core_props,
    _build_document_rels=build_document_rels,
    _build_image_png=build_image_png,
):
    buf = _io.BytesIO()
    with _zipfile.ZipFile(buf, "w", _zipfile.ZIP_DEFLATED) as zf:
        zf.writestr(
            "[Content_Types].xml",
            b'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Types xmlns="http://schemas.openxmlformats.org/package/2006/content-types">
  <Default Extension="rels" ContentType="application/vnd.openxmlformats-package.relationships+xml"/>
  <Default Extension="xml" ContentType="application/xml"/>
  <Default Extension="png" ContentType="image/png"/>
  <Override PartName="/docProps/core.xml" ContentType="application/vnd.openxmlformats-package.core-properties+xml"/>
  <Override PartName="/docProps/app.xml" ContentType="application/vnd.openxmlformats-officedocument.extended-properties+xml"/>
  <Override PartName="/word/document.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml"/>
  <Override PartName="/word/styles.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.styles+xml"/>
  <Override PartName="/word/settings.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.settings+xml"/>
  <Override PartName="/word/numbering.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.numbering+xml"/>
  <Override PartName="/word/fontTable.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.fontTable+xml"/>
  <Override PartName="/word/webSettings.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.webSettings+xml"/>
  <Override PartName="/word/theme/theme1.xml" ContentType="application/vnd.openxmlformats-officedocument.theme+xml"/>
</Types>''',
        )
        zf.writestr(
            "_rels/.rels",
            b'''<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
  <Relationship Id="rId1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument" Target="word/document.xml"/>
  <Relationship Id="rId2" Type="http://schemas.openxmlformats.org/package/2006/relationships/metadata/core-properties" Target="docProps/core.xml"/>
  <Relationship Id="rId3" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/extended-properties" Target="docProps/app.xml"/>
</Relationships>''',
        )
        zf.writestr(
            "word/_rels/document.xml.rels",
          _build_document_rels(),
        )
        zf.writestr("docProps/app.xml", _build_app_props())
        zf.writestr("docProps/core.xml", _build_core_props())
        zf.writestr("word/styles.xml", _build_styles())
        zf.writestr("word/settings.xml", _build_settings())
        zf.writestr("word/webSettings.xml", _build_web_settings())
        zf.writestr("word/numbering.xml", _build_numbering())
        zf.writestr("word/fontTable.xml", _build_font_table())
        zf.writestr("word/theme/theme1.xml", _build_theme())
        zf.writestr("word/media/image1.png", _build_image_png())
        zf.writestr("word/document.xml", document_xml)
    return buf.getvalue()


def build_document(body):
    return (
        b'<?xml version="1.0" encoding="UTF-8" standalone="yes"?>'
        b'<w:document xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" '
        b'xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships" '
        b'xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing" '
        b'xmlns:a="http://schemas.openxmlformats.org/drawingml/2006/main" '
        b'xmlns:pic="http://schemas.openxmlformats.org/drawingml/2006/picture">'
        b'<w:body>'
        + body
        + b'<w:sectPr><w:pgSz w:w="11906" w:h="16838"/><w:pgMar w:top="1440" w:right="1440" w:bottom="1440" w:left="1440" w:header="708" w:footer="708" w:gutter="0"/></w:sectPr>'
        b'</w:body></w:document>'
    )


def make_paragraph(style, text):
    return (
        b"<w:p><w:pPr><w:pStyle w:val=\""
        + style
        + b"\"/></w:pPr><w:r><w:t>"
        + text
        + b"</w:t></w:r></w:p>"
    )


def make_cell(text):
    return b"<w:tc><w:p><w:r><w:t>" + text + b"</w:t></w:r></w:p></w:tc>"


def make_row(cell1, cell2, _make_cell=make_cell):
    return b"<w:tr>" + _make_cell(cell1) + _make_cell(cell2) + b"</w:tr>"


def make_table(row1_col1, row1_col2, row2_col1, row2_col2, _make_row=make_row):
    return (
        b"<w:tbl>"
        b"<w:tblPr><w:tblStyle w:val=\"TableGrid\"/><w:tblW w:w=\"0\" w:type=\"auto\"/></w:tblPr>"
        b"<w:tblGrid><w:gridCol w:w=\"4500\"/><w:gridCol w:w=\"4500\"/></w:tblGrid>"
        + _make_row(row1_col1, row1_col2)
        + _make_row(row2_col1, row2_col2)
        + b"</w:tbl>"
    )


def make_hyperlink_paragraph(style, text):
    return (
        b"<w:p><w:pPr><w:pStyle w:val=\""
        + style
    + b"\"/></w:pPr><w:hyperlink r:id=\"rIdHyperlink1\"><w:r><w:rPr><w:rStyle w:val=\"Hyperlink\"/></w:rPr><w:t>"
        + text
        + b"</w:t></w:r></w:hyperlink></w:p>"
    )


def make_numbered_item(style, numid, text):
    return (
    b"<w:p><w:pPr><w:pStyle w:val=\""
    + style
    + b"\"/><w:numPr><w:ilvl w:val=\"0\"/><w:numId w:val=\""
    + numid
    + b"\"/></w:numPr></w:pPr>"
        b"<w:r><w:t>"
        + text
        + b"</w:t></w:r></w:p>"
    )


def make_image_paragraph(alt_text):
    return (
        b"<w:p><w:r><w:drawing><wp:inline distT=\"0\" distB=\"0\" distL=\"0\" distR=\"0\">"
        b"<wp:extent cx=\"9525\" cy=\"9525\"/><wp:docPr id=\"1\" name=\"Picture 1\" descr=\""
        + alt_text
        + b"\"/>"
        b"<a:graphic><a:graphicData uri=\"http://schemas.openxmlformats.org/drawingml/2006/picture\">"
        b"<pic:pic><pic:nvPicPr><pic:cNvPr id=\"0\" name=\"image1.png\"/><pic:cNvPicPr/></pic:nvPicPr>"
        b"<pic:blipFill><a:blip r:embed=\"rIdImage1\"/><a:stretch><a:fillRect/></a:stretch></pic:blipFill>"
        b"<pic:spPr><a:xfrm><a:off x=\"0\" y=\"0\"/><a:ext cx=\"9525\" cy=\"9525\"/></a:xfrm>"
        b"<a:prstGeom prst=\"rect\"><a:avLst/></a:prstGeom></pic:spPr></pic:pic>"
        b"</a:graphicData></a:graphic></wp:inline></w:drawing></w:r></w:p>"
    )


# 整体思路：
# 1. 先在 grammar 里生成一个简化的“文档 body”结构。
# 2. 再用 script 规则把 body 包进 document.xml。
# 3. 最后再把 document.xml 打包成一个最小合法 docx(zip) 文件。

ctx.script(
    "START",
    ["DOC_BODY"],
    lambda body, _build_docx=build_docx, _build_document=build_document: _build_docx(
        _build_document(body)
    ),
)

# 让示例文档稳定覆盖更多 OOXML 部件：样式段落、表格、超链接、三种编号、图片。
ctx.rule("DOC_BODY", "{PARAGRAPH}{TABLE}{HYPERLINK_BLOCK}{NUMBERED_DECIMAL_BLOCK}{NUMBERED_BULLET_BLOCK}{NUMBERED_ALPHA_BLOCK}{IMAGE_BLOCK}{TAIL_BLOCKS}")

ctx.rule("BLOCK", "{PARAGRAPH}")
ctx.rule("BLOCK", "{TABLE}")
ctx.rule("BLOCK", "{HYPERLINK_BLOCK}")
ctx.rule("BLOCK", "{NUMBERED_DECIMAL_BLOCK}")
ctx.rule("BLOCK", "{NUMBERED_BULLET_BLOCK}")
ctx.rule("BLOCK", "{NUMBERED_ALPHA_BLOCK}")
ctx.rule("BLOCK", "{IMAGE_BLOCK}")
ctx.rule("TAIL_BLOCKS", "{BLOCK}{TAIL_BLOCKS}")
ctx.rule("TAIL_BLOCKS", "")

# 一个更接近真实 DOCX 的 WordprocessingML block 模型。
ctx.script(
    "PARAGRAPH",
    ["PSTYLE", "TEXT"],
    lambda style, text, _make_paragraph=make_paragraph: _make_paragraph(style, text),
)
ctx.script(
    "TABLE",
    ["CELL_TEXT", "CELL_TEXT", "CELL_TEXT", "CELL_TEXT"],
    lambda a, b, c, d, _make_table=make_table: _make_table(a, b, c, d),
)
ctx.script(
  "HYPERLINK_BLOCK",
  ["PSTYLE", "LINK_TEXT"],
  lambda style, text, _make_hyperlink_paragraph=make_hyperlink_paragraph: _make_hyperlink_paragraph(style, text),
)
ctx.script(
  "NUMBERED_DECIMAL_BLOCK",
  ["LIST_TEXT"],
  lambda text, _make_numbered_item=make_numbered_item: _make_numbered_item(b"ListNumber", b"1", text),
)
ctx.script(
  "NUMBERED_BULLET_BLOCK",
  ["LIST_TEXT"],
  lambda text, _make_numbered_item=make_numbered_item: _make_numbered_item(b"ListBullet", b"2", text),
)
ctx.script(
  "NUMBERED_ALPHA_BLOCK",
  ["LIST_TEXT"],
  lambda text, _make_numbered_item=make_numbered_item: _make_numbered_item(b"ListAlpha", b"3", text),
)
ctx.script(
  "IMAGE_BLOCK",
  ["ALT_TEXT"],
  lambda alt, _make_image_paragraph=make_image_paragraph: _make_image_paragraph(alt),
)

ctx.rule("PSTYLE", "Normal")
ctx.rule("PSTYLE", "Title")
ctx.rule("PSTYLE", "Heading1")

# 这里故意把文本字符集限制得很小，避免 XML 转义问题。
ctx.rule("TEXT", "{WORD}")
ctx.rule("TEXT", "{WORD} {WORD}")
ctx.rule("TEXT", "{WORD} {WORD} {WORD}")
ctx.rule("TEXT", "{WORD} {WORD} {WORD} {WORD}")
ctx.rule("TEXT", "nautilus docx fuzz")
ctx.rule("TEXT", "wps parser test")
ctx.rule("TEXT", "styled paragraph example")

ctx.rule("LINK_TEXT", "open nautilus repo")
ctx.rule("LINK_TEXT", "follow hyperlink")
ctx.rule("LINK_TEXT", "{WORD} {WORD}")

ctx.rule("LIST_TEXT", "numbered item")
ctx.rule("LIST_TEXT", "list entry example")
ctx.rule("LIST_TEXT", "{WORD} {WORD} {WORD}")

ctx.rule("ALT_TEXT", "tiny embedded image")
ctx.rule("ALT_TEXT", "docx picture")
ctx.rule("ALT_TEXT", "{WORD} {WORD}")

ctx.rule("CELL_TEXT", "{WORD}")
ctx.rule("CELL_TEXT", "{WORD} {WORD}")
ctx.rule("CELL_TEXT", "cell data")
ctx.rule("CELL_TEXT", "table value")

ctx.regex("WORD", "[a-z]{1,8}")