// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to render all PDF layers of a PDF,
// and add layers in a PDF document.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/common/fs_render.h"
#include "../../../include/pdf/fs_pdflayer.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;

static const char* sn = "XQSqpYXftiFIcjaUVzEYXWVFvT86aRH+NpxaYmpzjXt+knIjbaBmMQ==";
static const char* key = "8f3g1kNstBkNAgfCSIczuioWaeXe4+c9+glonrwf6b2LMfDWf0CC92cxiF1M4Re6KUqmkA3+M4O1IRQXmfDg2WnFjr6Fy5eBqpmElth3Kch1UnDYqzIPf4PVOEZvUd51NT/a3Rp2dprVjI9p43m4BRUbHi14Ls5WJrbjiVImPsVCUGD4vLwv5KivNUlruYxBJklnVqASv/Ql2eMYs+QjkW2FF561ojrhWBbkZo+foLp7Dks6zaDFn2bjnFO0QQoD20LdUWuJc38kL+k6tcTaieNizW1FzvFVFDY8NWnaPY7k9nth2Ty5DtIdwMs2WuHrWIgd01SI/FkGZnVjdnmHMrGMNaJeiLJi64khor68iqTH+5C+3Eq48zfcsrsA8Qpe3GDEMHA1aDadhOj+wM1jFvjDQNQR4UQrgVEcS8HhoQECjJv3p/n6zpqSUEHwgoWt3MCZaOButo4qsSUf00/oFCrSaKugMwZsIZPzLilaIvyDYEyVUTDeZmnFRCri9Bnylj/uD+N2EPm2YZnsePp/ORv3FIHlNMl6kOQXmZMKsZMGQcCLc8Xxf9nSaiZzYD1jRgcytPBP0ROfN/rG3EI/1lG+ZCnax9oadtpEbEGjUvja70YRE14iVwR8QIRFVpqJVZTCMcmuFpMFfC2CKcYQORBygs+6bnobAli9qIzIoXvbk2gYI5X2WhkZHRwIrOXwk3fW9nFKjCXVpyYSFSdOrkRQdAT5u+6eEIaSD47GmIHoaDDlHH1RF6BusVsCqvfAfG8qIYJNes2q/c5nheCmBThdWjl4MKwxPH7K306MaekAKFPJAwKhBTES9nZrsseQLQ9v8WNGTZyBwJucEHMCol+Vk3lf+PpKEaD6G8TT7n36V43XJ/N09APgDcGxGB4rAAeinCbANyaYOQtZ0jb+5Jb/NKQ2grdA9KoEvafLE09J4VSloQPQOCCbIwhrvwZO0guWaEjXbiN4UPzSOnyQK7lZfFNmAIgjZtAqzIL8yeGes0I/CCI4CiRKz+pFh313WLtbKi3acqO7GrlFH9g652bkeITPg06fhkqSVjf7iHv+ZpZYXWz+K0FiTUaCinPzNKOCWbYrqNcWaM1Y6bR/uoUJkSUMoODHZ3csWhOz7VqUVZc9M4U6Qg0+0wck3w+ZbdEyVSlWnAPXkphg4UYMrMrUFUzHYSjORTdXoLYMveoIbWMhubtugl0DqD8hOEWqaGYYlJo2N2WU54mYEIaoZ8wfpWsMVOfPFyi5j754lngonq5vf36inXn3xRO5CkYFrzXKJ3n2DYiSrVV0ll/5WTkR3F/lEby4CP81UkVubm4GrvH7fBnhQuWgV9GlZbZhaCWl6FC1dnabn+sNwvh3iEP/2oWqi2013gtQQlSSFE5mCg+pCr6zFEAUTNHBqQZrXyMdIJ9tNimbX551HE+bKp5Eog1wHWP1k3orEjQUwm+R";

#if defined(_WIN32) || defined(_WIN64)
static WString output_path = WString::FromLocal("../output_files/");
static WString input_path = WString::FromLocal("../input_files/");
#else
static WString output_path = WString::FromLocal("./output_files/");
static WString input_path = WString::FromLocal("./input_files/");
#endif

class SdkLibMgr {
public:
  SdkLibMgr() : is_initialize_(false){};
  ErrorCode Initialize() {
    ErrorCode error_code = Library::Initialize(sn, key);
    if (error_code != foxit::e_ErrSuccess) {
      printf("Library Initialize Error: %d\n", error_code);
    } else {
      is_initialize_ = true;
    }
    return error_code;

  }
  ~SdkLibMgr(){
    if(is_initialize_)
      Library::Release();
  }
private:
  bool is_initialize_;
};

WString output_directory = output_path + L"pdflayer/";

class TextDoc {
public:
  TextDoc(const String& file_name, const String& fill_mode);
  TextDoc(const WString& file_name, const WString& fill_mode);
  ~TextDoc();
  void Write(const char* format, ...);
  void Write(int count, const char * prefix, const char * format, ...);

private:
  FILE* file_;
};

TextDoc::TextDoc(const String& file_name, const String& file_mode) throw(Exception) : file_(NULL) {
#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, file_name, (const char*)file_mode);
#else
  file_ = fopen((const char*)file_name, (const char*)file_mode);
#endif

  if (!file_)
    throw Exception(__FILE__, __LINE__, __FUNCTION__, foxit::e_ErrFile);
}

TextDoc::TextDoc(const WString& file_name, const WString& file_mode) throw(Exception)  : file_(NULL) {
  String s_file_name = String::FromUnicode(file_name);
  String s_file_mode = String::FromUnicode(file_mode);

#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, (const char*)s_file_name, (const char*)s_file_mode);
#else
  file_ = fopen((const char*)s_file_name, (const char*)s_file_mode);
#endif
  if (!file_)
    throw Exception(__FILE__, __LINE__, __FUNCTION__, foxit::e_ErrFile);
}

TextDoc::~TextDoc() {
  fclose(file_);
  file_ = NULL;
}

void TextDoc::Write(const char* format, ...) {
  va_list vars;
  if (file_) {
    // Get variable list
    va_start(vars, format);
    // Call vfprintf to format log data and output to log file
    vfprintf(file_, format, vars);
    // End variable list
    va_end(vars);
  }
}

void TextDoc::Write(int count, const char * prefix, const char * format, ...) {
  for (int i = 0; i < count; i++) {
    Write("%s", prefix);
  }
  va_list vars;
  if (file_) {
    // Get variable list
    va_start(vars, format);
    // Call vfprintf to format log data and output to log file
    vfprintf(file_, format, vars);
    // End variable list
    va_end(vars);
  }
}
const void RenderPageToImage(PDFPage page, LayerContext layer_content, WString bitmap_file) {
  if (!page.IsParsed()) {
    // Parse page.
    page.StartParse(PDFPage::e_ParsePageNormal, NULL, false);
  }

  int width = static_cast<int>(page.GetWidth());
  int height = static_cast<int>(page.GetHeight());
  foxit::Matrix matrix = page.GetDisplayMatrix(0, 0, width, height, page.GetRotation());

  // Prepare a bitmap for rendering.
  Bitmap bitmap(width, height, foxit::common::Bitmap::e_DIBArgb, NULL, 0);
  bitmap.FillRect(0xFFFFFFFF, NULL);

  // Render page.
  Renderer render(bitmap, false);

  if (!layer_content.IsEmpty()) {
    render.SetLayerContext(layer_content);
  }
  render.StartRender(page, matrix, NULL);
  Image image;
  image.AddFrame(bitmap);
  image.SaveAs(bitmap_file);
}

String UsgaeCodeToString(LayerTree::UsageState state) {
  switch (state) {
  case LayerTree::e_StateON:
    return "ON";
  case LayerTree::e_StateOFF:
    return "OFF";
  case LayerTree::e_StateUnchanged:
    return "Unchanged";
  case LayerTree::e_StateUndefined:
    return "Undefined";
  }
  return "Unknown";
}

void GetAllLayerNodesInformation(LayerNode layer_node, int depth, TextDoc& text_doc) {

  if (depth >= 0) {
    text_doc.Write(depth, "\t", "%s", (const char*)String::FromUnicode(layer_node.GetName()));
    if (layer_node.HasLayer()) {
      LayerTree::UsageState state = layer_node.GetViewUsage();
      text_doc.Write(" %s\r\n", state == LayerTree::e_StateON ? "[*]" : "[ ]");
      text_doc.Write(depth, "\t", "View usage state:\t%s\r\n", (const char*)UsgaeCodeToString(state));
      text_doc.Write(depth, "\t", "Export usage state:\t%s\r\n", (const char*)UsgaeCodeToString(layer_node.GetExportUsage()));

      LayerPrintData print_data = layer_node.GetPrintUsage();
      text_doc.Write(depth, "\t", "Print usage state:\t%s, subtype: %s\r\n", (const char*)UsgaeCodeToString(print_data.print_state),
        (const char*)print_data.subtype);

      LayerZoomData zoom_data = layer_node.GetZoomUsage();
      text_doc.Write(depth, "\t", "Zoom usage:\tmin_factor = %.4f max_factor = %.4f\r\n\r\n", zoom_data.min_factor,
        zoom_data.max_factor);
    } else {
      text_doc.Write("\r\n");
    }
  }

  depth++;
  int count = layer_node.GetChildrenCount();
  for (int i = 0; i < count; i++) {
    LayerNode child = layer_node.GetChild(i);
    GetAllLayerNodesInformation(child, depth, text_doc);
  }
}

void SetAllLayerNodesInformation(LayerNode layer_node) {
  if (layer_node.HasLayer()) {
    layer_node.SetDefaultVisible(true);
    layer_node.SetExportUsage(LayerTree::e_StateUndefined);
    layer_node.SetViewUsage(LayerTree::e_StateOFF);
    LayerPrintData print_data("subtype_print", LayerTree::e_StateON);
    layer_node.SetPrintUsage(print_data);
    LayerZoomData zoom_data(1, 10);
    layer_node.SetZoomUsage(zoom_data);
    WString new_name = WString(L"[View_OFF_Print_ON_Export_Undefined]") + layer_node.GetName();
    layer_node.SetName(new_name);
  }
  int count = layer_node.GetChildrenCount();
  for (int i = 0; i < count; i++) {
    LayerNode child = layer_node.GetChild(i);
    SetAllLayerNodesInformation(child);
  }
}

void SetAllLayerNodesVisible(LayerContext context, LayerNode layer_node, bool visible) {
  if (layer_node.HasLayer()) {
    context.SetVisible(layer_node, false);
  }
  int count = layer_node.GetChildrenCount();
  for (int i = 0; i < count; i++) {
    LayerNode child = layer_node.GetChild(i);
    SetAllLayerNodesVisible(context, child, visible);
  }
}

void RenderAllLayerNodes(PDFDoc doc, LayerContext context, LayerNode layer_node, WString pdf_name) {
  if (layer_node.HasLayer()) {
    context.SetVisible(layer_node, true);
    int page_count = doc.GetPageCount();
    for (int i=0; i<page_count; i++) {
      PDFPage page = doc.GetPage(i);
      WString s;
      s.Format((FX_LPCWSTR)L"%d",i);
      WString layer_name = layer_node.GetName();
      layer_name.Remove(':');
      layer_name.Remove('>');
      layer_name.Remove('<');
      layer_name.Remove('=');
      WString file_name = output_directory + L"page_" + s + L"_layer_node_" + layer_name + L".bmp";
      RenderPageToImage(page, context, file_name);
    }
  }

  int count = layer_node.GetChildrenCount();
  for (int i = 0; i < count; i++) {
    LayerNode child = layer_node.GetChild(i);
    RenderAllLayerNodes(doc,context,child,pdf_name);
  }
  if (layer_node.HasLayer()) {
    // The visibility of parent layer will affect the children layers,
    // so reset the visibility of parent layer after children have been rendered.
    context.SetVisible(layer_node, false);
  }
}

int main(int argc, char *argv[])
{
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file = input_path + L"OCTest_src.pdf";
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();

    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }
    LayerTree layertree(doc);
    LayerNode root = layertree.GetRootNode();
    if (root.IsEmpty()) {
      printf("No layer information!\r\n");
      return 1;
    }

    // Get original information of all layer nodes.
    WString file_info = output_directory + L"original_layer_informations.txt";
    TextDoc original_doc(file_info, L"w+b");
    GetAllLayerNodesInformation(root, -1, original_doc);
    // Set new information.
    SetAllLayerNodesInformation(root);
    // Get new information.
    file_info = output_directory + L"new_layer_informations.txt";
    TextDoc new_info(file_info, L"w+b");
    GetAllLayerNodesInformation(root, -1, new_info);

    WString output_file = output_directory + L"new_layers.pdf";
    doc.SaveAs(output_file,  PDFDoc::e_SaveFlagNormal);
    // Render layer node.
    LayerContext context(doc, LayerContext::e_UsageView);
    SetAllLayerNodesVisible(context, root, false);

    RenderAllLayerNodes(doc, context, root, output_file);

	// Edit layer tree
    doc = PDFDoc(input_file);
    error_code = doc.Load();
    layertree = LayerTree(doc);
    root = layertree.GetRootNode();
    int children_count = root.GetChildrenCount();
    root.RemoveChild(children_count - 1);
    LayerNode child = root.GetChild(children_count - 2);
    LayerNode child0 = root.GetChild(0);
    child.MoveTo(child0, 0);
    child.AddChild(0, L"AddedLayerNode", true);
    child.AddChild(0, L"AddedNode", false);
    file_info = output_directory + L"edit_layer_informations.txt";
    TextDoc edit_info(file_info, L"w+b");
    GetAllLayerNodesInformation(root, -1, edit_info);
    output_file = output_directory + L"edit_layer_tree.pdf";
    doc.SaveAs(output_file);

	// Create layer tree
    doc = PDFDoc(input_path + L"AboutFoxit.pdf");
    error_code = doc.Load();
    bool has_layer = doc.HasLayer();
    layertree = LayerTree(doc);
    has_layer = doc.HasLayer();
    root = layertree.GetRootNode();
    int child_count = root.GetChildrenCount();
    root.AddChild(0, L"AddedLayerNode", true);
    root.AddChild(0, L"AddedNode", false);
    file_info = output_directory + L"create_layer_informations.txt";
    TextDoc create_info(file_info, L"w+b");
    GetAllLayerNodesInformation(root, -1, create_info);
    output_file = output_directory + L"create_layer_tree.pdf";
    doc.SaveAs(output_file);

    // Copy graphics objects from A PDF to B PDF
    doc = PDFDoc(input_file);
    error_code = doc.Load();
    PDFPage page = doc.GetPage(0);
    page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);

    // Create layer tree
    PDFDoc newdoc = PDFDoc(input_path + L"SamplePDF.pdf");
    error_code = newdoc.Load();
    PDFPage newpage = newdoc.GetPage(0);
    newpage.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);
    has_layer = newdoc.HasLayer();
    layertree = LayerTree(newdoc);
    has_layer = newdoc.HasLayer();
    root = layertree.GetRootNode();
    child_count = root.GetChildrenCount();
    LayerNode node1 = root.AddChild(0, L"AddedLayerNode", true);

    for (int i = 0; i < 5; i++)
    {
      graphics::GraphicsObject* graphics_object = page.GetGraphicsObject(i);
      graphics::GraphicsObject* ngraphics_object = graphics_object->Clone();
      newpage.InsertGraphicsObject(NULL, ngraphics_object);

      node1.AddGraphicsObject(newpage, ngraphics_object);
    }
    newpage.GenerateContent();

    output_file = output_directory + L"copy_graphics_objects.pdf";
    newdoc.SaveAs(output_file);
    cout << "PDFLayer test." << endl;

  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }
  catch(...)
  {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}
