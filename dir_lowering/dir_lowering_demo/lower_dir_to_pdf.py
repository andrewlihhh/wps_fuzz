import json
import os
import sys
from pathlib import Path

SDK_PATH = "/home/kzl/dir_lowering_demo_sdk"
if SDK_PATH not in sys.path:
    sys.path.insert(0, SDK_PATH)

from reportlab.lib import colors
from reportlab.lib.colors import Color
from reportlab.pdfgen import canvas
from reportlab.platypus import Table, TableStyle


def as_color(rgb):
    return Color(rgb[0], rgb[1], rgb[2])


def dir_top_left_to_pdf_bottom_left(page_height, x, y, object_height=0):
    return x, page_height - y - object_height


def log(message):
    print(message)


def lower_text(pdf, page_height, obj):
    x, y = dir_top_left_to_pdf_bottom_left(page_height, obj["position"][0], obj["position"][1])
    font = obj.get("font", "Helvetica")
    font_size = obj.get("font_size", 12)
    color = as_color(obj.get("color", [0, 0, 0]))
    data = obj.get("data", "")

    log(f"  [text] DIR {obj['position']} -> PDF ({x}, {y})")
    log(f"         SDK calls: setFont({font}, {font_size}) -> setFillColor({tuple(obj.get('color', [0, 0, 0]))}) -> drawString({x}, {y}, {data!r})")

    pdf.setFont(font, font_size)
    pdf.setFillColor(color)
    pdf.drawString(x, y, data)


def lower_figure(pdf, page_height, obj):
    width, height = obj["size"]
    x, y = dir_top_left_to_pdf_bottom_left(page_height, obj["position"][0], obj["position"][1], height)
    stroke_color = as_color(obj.get("stroke_color", [0, 0, 0]))
    fill_color = as_color(obj.get("fill_color", [1, 1, 1]))
    title = obj.get("title", "")

    log(f"  [figure] DIR pos/size {obj['position']} {obj['size']} -> PDF rect({x}, {y}, {width}, {height})")
    log("           SDK calls: setStrokeColor(...) -> setFillColor(...) -> rect(...) -> drawString(...)")

    pdf.setStrokeColor(stroke_color)
    pdf.setFillColor(fill_color)
    pdf.rect(x, y, width, height, fill=1)
    pdf.setFillColor(colors.black)
    pdf.setFont("Helvetica", 10)
    pdf.drawString(x + 8, y + height - 18, title)


def lower_table(pdf, page_height, obj):
    width, height = obj["size"]
    x, y = dir_top_left_to_pdf_bottom_left(page_height, obj["position"][0], obj["position"][1], height)
    data = [obj.get("headers", [])] + obj.get("rows", [])

    log(f"  [table] DIR pos/size {obj['position']} {obj['size']} -> PDF table at ({x}, {y})")
    log("          SDK calls: Table(data, ...) -> setStyle(...) -> wrapOn(...) -> drawOn(...)")

    table = Table(data, colWidths=[95, 85, 120], rowHeights=22)
    table.setStyle(
        TableStyle(
            [
                ("BACKGROUND", (0, 0), (-1, 0), colors.HexColor("#d9e8ff")),
                ("TEXTCOLOR", (0, 0), (-1, 0), colors.black),
                ("GRID", (0, 0), (-1, -1), 0.5, colors.grey),
                ("FONTNAME", (0, 0), (-1, 0), "Helvetica-Bold"),
                ("FONTNAME", (0, 1), (-1, -1), "Helvetica"),
                ("FONTSIZE", (0, 0), (-1, -1), 9),
                ("VALIGN", (0, 0), (-1, -1), "MIDDLE"),
            ]
        )
    )
    table.wrapOn(pdf, width, height)
    table.drawOn(pdf, x, y)


def lower_object(pdf, page_height, obj):
    object_type = obj["type"]
    if object_type == "text":
        lower_text(pdf, page_height, obj)
        return
    if object_type == "figure":
        lower_figure(pdf, page_height, obj)
        return
    if object_type == "table":
        lower_table(pdf, page_height, obj)
        return
    raise ValueError(f"Unsupported DIR object type: {object_type}")


def lower_dir_to_pdf(dir_doc, output_path):
    first_page_width, first_page_height = dir_doc["pages"][0]["size"]
    pdf = canvas.Canvas(str(output_path), pagesize=(first_page_width, first_page_height))
    pdf.setTitle(dir_doc.get("title", "DIR Lowering Demo"))

    log(f"Create PDF canvas: Canvas(output={output_path}, pagesize=({first_page_width}, {first_page_height}))")

    for page_index, page in enumerate(dir_doc["pages"], start=1):
        page_width, page_height = page["size"]
        log(f"\nPage {page_index}: DIR page -> PDF page size ({page_width}, {page_height})")
        if page_index > 1:
            pdf.setPageSize((page_width, page_height))

        for obj in page.get("objects", []):
            lower_object(pdf, page_height, obj)

        if page_index != len(dir_doc["pages"]):
            log("  SDK call: showPage() -> start next PDF page")
            pdf.showPage()

    log("\nSDK call: save() -> write final PDF bytes to disk")
    pdf.save()


def main():
    base_dir = Path(__file__).resolve().parent
    input_path = Path(sys.argv[1]) if len(sys.argv) > 1 else base_dir / "sample_dir.json"
    output_path = Path(sys.argv[2]) if len(sys.argv) > 2 else base_dir / "output" / "dir_lowered_demo.pdf"
    output_path.parent.mkdir(parents=True, exist_ok=True)

    with input_path.open("r", encoding="utf-8") as handle:
        dir_doc = json.load(handle)

    log(f"Loaded DIR document from: {input_path}")
    lower_dir_to_pdf(dir_doc, output_path)
    log(f"\nDone. Generated PDF: {output_path}")


if __name__ == "__main__":
    main()