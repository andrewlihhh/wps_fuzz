import json


def to_text(value):
    if isinstance(value, bytes):
        return value.decode("utf-8")
    return str(value)


def to_json_bytes(obj, _json=json):
    return _json.dumps(obj, ensure_ascii=True, separators=(",", ":")).encode("utf-8")


def join_items(head, tail):
    if tail:
        return head + b"," + tail
    return head


def build_ir(title, blocks, _to_text=to_text, _to_json_bytes=to_json_bytes, _json=json):
    return _to_json_bytes({
        "title": _to_text(title),
        "blocks": _json.loads(b"[" + blocks + b"]"),
    })


def make_paragraph(style, text, _to_text=to_text, _to_json_bytes=to_json_bytes):
    return _to_json_bytes({
        "type": "paragraph",
        "style": _to_text(style),
        "text": _to_text(text),
    })


def make_list(style, num_id, item1, item2, _to_text=to_text, _to_json_bytes=to_json_bytes):
    return _to_json_bytes({
        "type": "list",
        "listStyle": _to_text(style),
        "numId": int(_to_text(num_id)),
        "items": [_to_text(item1), _to_text(item2)],
    })


def make_list3(style, num_id, item1, item2, item3, _to_text=to_text, _to_json_bytes=to_json_bytes):
    return _to_json_bytes({
        "type": "list",
        "listStyle": _to_text(style),
        "numId": int(_to_text(num_id)),
        "items": [_to_text(item1), _to_text(item2), _to_text(item3)],
    })


def make_list4(style, num_id, item1, item2, item3, item4, _to_text=to_text, _to_json_bytes=to_json_bytes):
    return _to_json_bytes({
        "type": "list",
        "listStyle": _to_text(style),
        "numId": int(_to_text(num_id)),
        "items": [_to_text(item1), _to_text(item2), _to_text(item3), _to_text(item4)],
    })


def make_table(a, b, c, d, _to_text=to_text, _to_json_bytes=to_json_bytes):
    return _to_json_bytes({
        "type": "table",
        "rows": [
            [_to_text(a), _to_text(b)],
            [_to_text(c), _to_text(d)],
        ],
    })


def make_table_3x2(a, b, c, d, e, f, _to_text=to_text, _to_json_bytes=to_json_bytes):
    return _to_json_bytes({
        "type": "table",
        "rows": [
            [_to_text(a), _to_text(b)],
            [_to_text(c), _to_text(d)],
            [_to_text(e), _to_text(f)],
        ],
    })


def make_table_3x3(a, b, c, d, e, f, g, h, i, _to_text=to_text, _to_json_bytes=to_json_bytes):
    return _to_json_bytes({
        "type": "table",
        "rows": [
            [_to_text(a), _to_text(b), _to_text(c)],
            [_to_text(d), _to_text(e), _to_text(f)],
            [_to_text(g), _to_text(h), _to_text(i)],
        ],
    })


def make_hyperlink(style, text, url, _to_text=to_text, _to_json_bytes=to_json_bytes):
    return _to_json_bytes({
        "type": "hyperlink",
        "style": _to_text(style),
        "text": _to_text(text),
        "url": _to_text(url),
    })


def make_image(alt_text, _to_text=to_text, _to_json_bytes=to_json_bytes):
    return _to_json_bytes({
        "type": "image",
        "altText": _to_text(alt_text),
    })


ctx.script(
    "START",
    ["TITLE", "BLOCK_ARRAY"],
    lambda title, blocks, _build_ir=build_ir: _build_ir(title, blocks),
)

ctx.script(
    "BLOCK_ARRAY",
    ["BLOCK", "BLOCK_TAIL"],
    lambda head, tail, _join_items=join_items: _join_items(head, tail),
)
ctx.script(
    "BLOCK_TAIL",
    ["BLOCK", "BLOCK_TAIL"],
    lambda head, tail, _join_items=join_items: _join_items(head, tail),
)
ctx.rule("BLOCK_TAIL", "")

ctx.rule("BLOCK", "{PARAGRAPH}")
ctx.rule("BLOCK", "{LIST}")
ctx.rule("BLOCK", "{TABLE}")
ctx.rule("BLOCK", "{HYPERLINK}")
ctx.rule("BLOCK", "{IMAGE}")

ctx.script(
    "PARAGRAPH",
    ["PSTYLE", "TEXT"],
    lambda style, text, _make_paragraph=make_paragraph: _make_paragraph(style, text),
)
ctx.script(
    "LIST",
    ["LIST_STYLE", "NUM_ID", "LIST_TEXT", "LIST_TEXT"],
    lambda style, num_id, item1, item2, _make_list=make_list: _make_list(style, num_id, item1, item2),
)
ctx.script(
    "LIST",
    ["LIST_STYLE", "NUM_ID", "LIST_TEXT", "LIST_TEXT", "LIST_TEXT"],
    lambda style, num_id, item1, item2, item3, _make_list3=make_list3: _make_list3(style, num_id, item1, item2, item3),
)
ctx.script(
    "LIST",
    ["LIST_STYLE", "NUM_ID", "LIST_TEXT", "LIST_TEXT", "LIST_TEXT", "LIST_TEXT"],
    lambda style, num_id, item1, item2, item3, item4, _make_list4=make_list4: _make_list4(style, num_id, item1, item2, item3, item4),
)
ctx.script(
    "TABLE",
    ["CELL_TEXT", "CELL_TEXT", "CELL_TEXT", "CELL_TEXT"],
    lambda a, b, c, d, _make_table=make_table: _make_table(a, b, c, d),
)
ctx.script(
    "TABLE",
    ["CELL_TEXT", "CELL_TEXT", "CELL_TEXT", "CELL_TEXT", "CELL_TEXT", "CELL_TEXT"],
    lambda a, b, c, d, e, f, _make_table_3x2=make_table_3x2: _make_table_3x2(a, b, c, d, e, f),
)
ctx.script(
    "TABLE",
    [
        "CELL_TEXT", "CELL_TEXT", "CELL_TEXT",
        "CELL_TEXT", "CELL_TEXT", "CELL_TEXT",
        "CELL_TEXT", "CELL_TEXT", "CELL_TEXT",
    ],
    lambda a, b, c, d, e, f, g, h, i, _make_table_3x3=make_table_3x3: _make_table_3x3(a, b, c, d, e, f, g, h, i),
)
ctx.script(
    "HYPERLINK",
    ["PSTYLE", "TEXT", "URL"],
    lambda style, text, url, _make_hyperlink=make_hyperlink: _make_hyperlink(style, text, url),
)
ctx.script(
    "IMAGE",
    ["ALT_TEXT"],
    lambda alt_text, _make_image=make_image: _make_image(alt_text),
)

ctx.rule("TITLE", "nautilus sdk demo")
ctx.rule("TITLE", "wps ir lowering test")
ctx.rule("TITLE", "structured docx generation")
ctx.rule("TITLE", "mutation driven openxml exploration")
ctx.rule("TITLE", "seed inspired rich document layout")
ctx.rule("TITLE", "lists tables links and images")

ctx.rule("PSTYLE", "Normal")
ctx.rule("PSTYLE", "Title")
ctx.rule("PSTYLE", "Heading1")

ctx.rule("LIST_STYLE", "ListNumber")
ctx.rule("LIST_STYLE", "ListBullet")
ctx.rule("LIST_STYLE", "ListAlpha")

ctx.rule("NUM_ID", "1")
ctx.rule("NUM_ID", "2")
ctx.rule("NUM_ID", "3")

ctx.rule("TEXT", "{WORD}")
ctx.rule("TEXT", "{WORD} {WORD}")
ctx.rule("TEXT", "{WORD} {WORD} {WORD}")
ctx.rule("TEXT", "{WORD} {WORD} {WORD} {WORD}")
ctx.rule("TEXT", "{WORD}: {WORD} {WORD}")
ctx.rule("TEXT", "{WORD} - {WORD} - {WORD}")
ctx.rule("TEXT", "{WORD} {NUMBER} {WORD}")
ctx.rule("TEXT", "{SENTENCE}")
ctx.rule("TEXT", "{SENTENCE} {SENTENCE}")
ctx.rule("TEXT", "sdk lowered paragraph")
ctx.rule("TEXT", "wps parser structure test")
ctx.rule("TEXT", "section alpha contains cross referenced content")
ctx.rule("TEXT", "table driven paragraph with hyperlinks and images")

ctx.rule("LIST_TEXT", "{WORD}")
ctx.rule("LIST_TEXT", "{WORD} {WORD}")
ctx.rule("LIST_TEXT", "{WORD} {NUMBER}")
ctx.rule("LIST_TEXT", "{SENTENCE}")
ctx.rule("LIST_TEXT", "list entry")
ctx.rule("LIST_TEXT", "numbered item")
ctx.rule("LIST_TEXT", "bullet point with mixed content")

ctx.rule("CELL_TEXT", "{WORD}")
ctx.rule("CELL_TEXT", "{WORD} {WORD}")
ctx.rule("CELL_TEXT", "{WORD} {NUMBER}")
ctx.rule("CELL_TEXT", "{SHORT_SENTENCE}")
ctx.rule("CELL_TEXT", "cell value")
ctx.rule("CELL_TEXT", "table data")
ctx.rule("CELL_TEXT", "grid cell with seed like text")

ctx.rule("ALT_TEXT", "embedded image")
ctx.rule("ALT_TEXT", "wps inline picture")
ctx.rule("ALT_TEXT", "{WORD} {WORD}")
ctx.rule("ALT_TEXT", "diagram for section {NUMBER}")

ctx.rule("URL", "https://example.com")
ctx.rule("URL", "https://openxml.dev")
ctx.rule("URL", "https://wps.example/docx")
ctx.rule("URL", "https://docs.example.com/{WORD}")
ctx.rule("URL", "https://seed.example/{WORD}/{WORD}")

ctx.rule("SENTENCE", "{WORD} {WORD} {WORD} {WORD}.")
ctx.rule("SENTENCE", "{WORD} {WORD} {NUMBER} {WORD}.")
ctx.rule("SENTENCE", "{WORD} {WORD}, {WORD} {WORD}.")
ctx.rule("SHORT_SENTENCE", "{WORD} {WORD}")
ctx.rule("SHORT_SENTENCE", "{WORD} {NUMBER}")

ctx.regex("WORD", "[a-z0-9]{1,10}")
ctx.regex("NUMBER", "[0-9]{1,4}")
