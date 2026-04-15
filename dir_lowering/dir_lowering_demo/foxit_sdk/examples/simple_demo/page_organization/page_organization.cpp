// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to do PDF page organization,
// such as inserting, removing, and so on.

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
#include "../../../include/pdf/graphics/fs_pdfgraphicsobject.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace graphics;

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

WString output_directory = output_path + L"page_organization/";

void AddTextObjects(PDFPage page, const wchar_t* content) {
  POSITION position = page.GetLastGraphicsObjectPosition(GraphicsObject::e_TypeText);
  TextObject* text_object = TextObject::Create();

  text_object->SetFillColor(0xFFAAAAAA);
  text_object->SetStrokeColor(0xFFF68C21);

  // Prepare text state
  TextState state;
  state.font_size = 64.0f;
  state.font = Font(Font::e_StdIDTimes);
  state.textmode = TextState::e_ModeFillStrokeClip;

  text_object->SetTextState(page, state, false, 750);

  // Set content
  text_object->SetText(content);
  page.InsertGraphicsObject(position, text_object);

  // Transform to center
  RectF rect = text_object->GetRect();
  float offset_x = (page.GetWidth() - (rect.right - rect.left)) / 2;
  float offset_y = (page.GetHeight() - (rect.top - rect.bottom)) / 2;
  text_object->Transform(Matrix(1, 0, 0, 1, offset_x, offset_y), false);

  // Generator content
  page.GenerateContent();
}

bool InsertPage() {
  WString input_file = input_path + L"page_organization_123.pdf";
  PDFDoc doc = PDFDoc(input_file);
  ErrorCode code = doc.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), code);
    return false;
  }

  PDFPage page = doc.InsertPage(-1);
  AddTextObjects(page, L"insert in first");
  page = doc.InsertPage(2);
  AddTextObjects(page, L"insert in 2 (based 0)");
  page = doc.InsertPage(doc.GetPageCount());
  AddTextObjects(page, L"insert in last");
  WString output_file = output_directory + L"insert_page.pdf";
  doc.SaveAs(output_file, PDFDoc::e_SaveFlagNormal);
  cout << "Insert pages." << endl;
  return true;
}

bool RemovePage() {
  WString input_file = input_path + L"page_organization_123.pdf";
  PDFDoc doc = PDFDoc(input_file);
  ErrorCode code = doc.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), code);
    return false;
  }

  while (doc.GetPageCount() > 1) {
    doc.RemovePage(0);
  }
  WString output_file = output_directory + L"remove_all_pages_exceptt_the_last_page.pdf";
  doc.SaveAs(output_file,  PDFDoc::e_SaveFlagNormal);
  cout << "Remove pages." << endl;
  return true;
}

// You can implement the functionality of exporting pages by creating an empty document
// and importing part of the source document into the empty document.
// You can also import the target document as a source document
// to implement the copy page functionality.
bool ImportPage() {
  WString file_dest = input_path + L"page_organization_123.pdf";
  WString file_src = input_path + L"page_organization_abc.pdf";
  PDFDoc doc_dest = PDFDoc(file_dest);
  ErrorCode code = doc_dest.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(file_dest), code);
    return false;
  }
  PDFDoc doc_src = PDFDoc(file_src);
  code = doc_src.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(file_src), code);
    return false;
  }
  // Import page from PDFDoc object.
  Range import_ranges(0);
  import_ranges.AddSingle(doc_src.GetPageCount()-1);
  Progressive progressive =
    doc_dest.StartImportPages(-1,  doc_src, PDFDoc::e_ImportFlagNormal, "abc", import_ranges, NULL);
  while (progressive.Continue() != Progressive::e_Finished) {
  }
  WString output_file = output_directory + L"page_organization_abc_to_123_import_pages.pdf";
  doc_dest.SaveAs(output_file, PDFDoc::e_SaveFlagNormal);

  doc_dest = PDFDoc(file_dest);
  code = doc_dest.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(file_dest), code);
    return false;
  }
  // Import page from file path.
  progressive = doc_dest.StartImportPagesFromFilePath(-1, file_src, "", PDFDoc::e_ImportFlagNormal, "abc",
    import_ranges, NULL);
  while (progressive.Continue() != Progressive::e_Finished) {
  }
  output_file = output_directory + L"abc_to_123_import_pages_form_filepath.pdf";
  doc_dest.SaveAs(output_file,PDFDoc::e_SaveFlagNormal);
  cout << "Import pages." << endl;
  return true;
}

// This example shows how to use the use the functions StartExtractPages and InsertDocument together,
// instead of the StartImportPagesFromFilePath function. The execution efficiency of importing pages has
// been optimized in these new functions.
bool ImportPageOptimized() {
  WString file_dest = input_path + L"page_organization_123.pdf";
  WString file_src = input_path + L"page_organization_abc.pdf";
  PDFDoc doc_dest = PDFDoc(file_dest);
  ErrorCode code = doc_dest.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(file_dest), code);
    return false;
  }
  PDFDoc doc_src = PDFDoc(file_src);
  code = doc_src.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(file_src), code);
    return false;
  }
  // Extract pages to temporary document
  Range import_ranges(0);
  import_ranges.AddSingle(doc_src.GetPageCount() - 1);
  WString file_temp = output_directory + L"page_organization_import_extracted_pages.pdf";
  Progressive progressive =
    doc_src.StartExtractPages(file_temp, PDFDoc::e_ExtractPagesOptionAnnotation, import_ranges, NULL);
  while (progressive.Continue() != Progressive::e_Finished) {
  }

  PDFDoc doc_temp = PDFDoc(file_temp);
  code = doc_temp.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(file_temp), code);
    return false;
  }

  // Insert temporary document into destination
  doc_dest.InsertDocument(-1, doc_temp, PDFDoc::e_InsertDocOptionAttachments);
  WString output_file = output_directory + L"abc_to_123_insert_document.pdf";
  doc_dest.SaveAs(output_file, PDFDoc::e_SaveFlagNormal);
  cout << "Import pages optimized." << endl;
  return true;
}

bool MovePages()
{
  WString input_file = input_path + L"page_organization_123.pdf";
  WString input_file1 = input_path + L"page_organization_abc.pdf";
  // Move page
  PDFDoc doc = PDFDoc(input_file);
  ErrorCode code = doc.Load();
  if (code != foxit::e_ErrSuccess) {
    printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), code);
    return false;
  }
  int count = doc.GetPageCount();
  PDFPage page = doc.GetPage(0);
  doc.MovePageTo(page, doc.GetPageCount() - 1);
  WString output_file1 = output_directory + L"move_first_page_to_last.pdf";
  doc.SaveAs(output_file1, PDFDoc::e_SaveFlagNormal);

  doc = PDFDoc(input_file1);
  code = doc.Load();
  if (code != foxit::e_ErrSuccess) {
    return false;
  }
  Range page_set;
  for (int i = 0; i < count / 2; i++)
    page_set.AddSingle(2 * i);
  doc.MovePagesTo(page_set, doc.GetPageCount() - 1);
  WString output_file = output_directory + L"move_pages.pdf";
  doc.SaveAs(output_file, PDFDoc::e_SaveFlagNormal);
  cout << "Move pages." << endl;
  return true;
}
int main(int argc, char *argv[])
{
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file = input_path + L"page_organization_123.pdf";
  WString input_file1 = input_path + L"page_organization_abc.pdf";
  SdkLibMgr sdk_lib_mgr;
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    if (!(InsertPage() && RemovePage() && ImportPage() && ImportPageOptimized() && MovePages())) {
      return 1;
    }

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
