#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "include/fs_basictypes_c.h"
#include "include/fs_common_c.h"
#include "include/fs_pdfdoc_c.h"
#include "include/fs_pdfgraphicsobject_c.h"
#include "include/fs_pdfpage_c.h"

typedef struct {
  float red;
  float green;
  float blue;
} DirColor;

typedef struct {
  float x;
  float y;
  const wchar_t* font_name;
  float font_size;
  DirColor color;
  const wchar_t* text;
} DirTextObject;

typedef struct {
  const DirTextObject* text_objects;
  size_t text_object_count;
  float width;
  float height;
} DirPage;

typedef struct {
  const DirPage* pages;
  size_t page_count;
} DirDocument;

static int InitializeFoxit(void) {
  const char* sn = "";
  const char* key = "";
  FSErrorCode code = FSDK_Library_Initialize(sn, key);
  if (code != e_FSErrSuccess) {
    fprintf(stderr, "FSDK_Library_Initialize failed: %d\n", code);
    return 0;
  }
  return 1;
}

static FS_ARGB DirColorToArgb(const DirColor* color) {
  unsigned int red = (unsigned int)(color->red * 255.0f) & 0xFF;
  unsigned int green = (unsigned int)(color->green * 255.0f) & 0xFF;
  unsigned int blue = (unsigned int)(color->blue * 255.0f) & 0xFF;
  return 0xFF000000 | (red << 16) | (green << 8) | blue;
}

static int AddDirTextObject(FS_PDFPAGE_HANDLE page, const DirTextObject* object) {
  FS_POSITION position;
  FS_TEXTOBJECT_HANDLE text_object;
  FSTextState text_state;
  FS_FONT_HANDLE font = NULL;
  FS_BOOL result = FALSE;

  FSDK_GraphicsObjects_GetLastGraphicsObjectPosition(page, e_FSTypeText, &position);
  FSDK_TextObject_Create(&text_object);
  FSDK_GraphicsObject_SetFillColor(text_object, DirColorToArgb(&object->color));

  memset(&text_state, 0, sizeof(text_state));
  text_state.font_size = object->font_size;
  text_state.textmode = e_FSModeFill;
  text_state.origin_position.x = object->x;
  text_state.origin_position.y = object->y;
  text_state.textmatrix[0] = 1;
  text_state.textmatrix[3] = 1;

  FSDK_Font_Create(object->font_name, 0, e_FSCharsetANSI, 0, &font);
  text_state.font = font;

  FSDK_TextObject_SetTextState(text_object, page, text_state, FALSE, 0);
  FSDK_TextObject_SetText(text_object, object->text);
  FSDK_GraphicsObjects_InsertGraphicsObject(page, position, text_object, &position);
  FSDK_GraphicsObjects_GenerateContent(page, &result);

  return result == TRUE;
}

static int LowerDirToPdf(const DirDocument* document, const wchar_t* output_path) {
  FS_PDFDOC_HANDLE pdf_doc;
  FS_BOOL save_result = FALSE;
  size_t page_index;

  FSDK_PDFDoc_Create(&pdf_doc);

  for (page_index = 0; page_index < document->page_count; ++page_index) {
    const DirPage* page = &document->pages[page_index];
    FS_PDFPAGE_HANDLE pdf_page;
    size_t text_index;

    FSDK_PDFDoc_InsertPage(pdf_doc, (int)page_index, page->width, page->height, &pdf_page);
    for (text_index = 0; text_index < page->text_object_count; ++text_index) {
      if (!AddDirTextObject(pdf_page, &page->text_objects[text_index])) {
        fprintf(stderr, "Failed to lower text object %zu on page %zu\n", text_index, page_index);
        return 0;
      }
    }
  }

  FSDK_PDFDoc_SaveAs(pdf_doc, output_path, e_FSSaveFlagNoOriginal, &save_result);
  return save_result == TRUE;
}

int main(void) {
  static const DirTextObject page1_objects[] = {
      {100.0f, 700.0f, L"Helvetica", 20.0f, {0.85f, 0.0f, 0.0f}, L"Hello, World"},
      {100.0f, 660.0f, L"Helvetica", 12.0f, {0.0f, 0.0f, 0.0f}, L"This PDF is lowered from a DIR-like structure."},
  };
  static const DirTextObject page2_objects[] = {
      {100.0f, 700.0f, L"Helvetica", 16.0f, {0.1f, 0.2f, 0.6f}, L"Second page generated through Foxit C API"},
  };
  static const DirPage pages[] = {
      {page1_objects, 2, 595.0f, 842.0f},
      {page2_objects, 1, 595.0f, 842.0f},
  };
  static const DirDocument document = {pages, 2};

  setlocale(LC_ALL, "");

  if (!InitializeFoxit()) {
    return 1;
  }

  if (!LowerDirToPdf(&document, L"foxit_real_lowering_demo.pdf")) {
    fprintf(stderr, "Lowering failed\n");
    return 1;
  }

  printf("Generated foxit_real_lowering_demo.pdf\n");
  return 0;
}