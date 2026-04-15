// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to enumerate and modify bookmarks
// in PDF document.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_filespec.h"
#include "../../../include/pdf/fs_bookmark.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"

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

class TextDoc {
public:
  TextDoc(const String& file_name, const String& fill_mode);
  TextDoc(const WString& file_name, const WString& fill_mode);
  ~TextDoc();
  void Write(const char* format, ...);
  void Write(int count, const char* prefix, const char* format, ...);

private:
  FILE* file_;
};

TextDoc::TextDoc(const String& file_name, const String& file_mode) throw(Exception) : file_(NULL) {
#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, (const char*)file_name, (const char*)file_mode);
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

void ShowBookmarkInfo(Bookmark bookmark, TextDoc& doc, int depth) {
  if (depth > 32)
    return;
  if (bookmark.IsEmpty())
    return;
  for (int i = 0; i < depth; i++) {
    doc.Write("\t");
  }

  // Show bookmark's title.
  doc.Write("%s\t", (const char*)String::FromUnicode(bookmark.GetTitle()));

  // Show bookmark's color.
  doc.Write("color: %x\r\n", bookmark.GetColor());

  ShowBookmarkInfo(bookmark.GetFirstChild(), doc, depth + 1);
  ShowBookmarkInfo(bookmark.GetNextSibling(), doc, depth);
}

void ShowBookmarksInfo(PDFDoc doc, const WString& info_path) {
  TextDoc text_doc(info_path, L"w+b");
  Bookmark root = doc.GetRootBookmark();
  if (!root.IsEmpty()) {
    ShowBookmarkInfo(root, text_doc,0);
  } else {
    text_doc.Write("No bookmark information!\r\n");
  }
}
int main(int argc, char *argv[])
{
  int err_ret = 0;
  WString input_file = input_path + L"AboutFoxit.pdf";

  WString output_directory = output_path + L"bookmark/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  WString output_file1 = output_directory + L"bookmark_add.pdf";
  WString output_file2 = output_directory + L"bookmark_change.pdf";
  WString bookmark_info_file = output_directory + L"bookmark_info.txt";

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

    // Show original bookmark information.
    ShowBookmarksInfo(doc, bookmark_info_file);

    //Get bookmark root node or Create new bookmark root node.
    Bookmark root = doc.GetRootBookmark();
    if (root.IsEmpty())
    {
      root = doc.CreateRootBookmark();
    }
    for (int i = 0; i < doc.GetPageCount(); i += 2) {
      Destination dest = Destination::CreateFitPage(doc, i);
      CFX_WideString ws_title;
      ws_title.Format((FX_LPCWSTR)L"A bookmark to a page (index: %d)", i);
      Bookmark child = root.Insert(ws_title,
        foxit::pdf::Bookmark::e_PosLastChild);
      child.SetDestination(dest);
      child.SetColor(i * 0xF68C21);
    }
    doc.SaveAs(output_file1, PDFDoc::e_SaveFlagNoOriginal);

    // Get first bookmark and change properties.
    Bookmark first_bookmark = root.GetFirstChild();
    first_bookmark.SetStyle(foxit::pdf::Bookmark::e_StyleItalic);
    first_bookmark.SetColor(0xFF0000);
    first_bookmark.SetTitle(L"Change bookmark title, style, and color");

    // Remove next sibling bookmark
    if (!first_bookmark.GetNextSibling().IsEmpty()) {
      doc.RemoveBookmark(first_bookmark.GetNextSibling());
    }

    WString bookmark_info_file = output_directory + L"bookmark_info1.txt";
    ShowBookmarksInfo(doc, bookmark_info_file);

    doc.SaveAs(output_file2, PDFDoc::e_SaveFlagNoOriginal);
    cout << "Bookmark demo." << endl;

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

