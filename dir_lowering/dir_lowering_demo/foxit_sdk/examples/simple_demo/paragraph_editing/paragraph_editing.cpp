// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to edit paragraph in a PDF document.


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
#include "../../../include/addon/pageeditor/fs_paragraphediting.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace foxit::addon::pageeditor;

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

class FxParagraphEditingProviderCallback : public foxit::addon::pageeditor::ParagraphEditingProviderCallback {
public:

  FxParagraphEditingProviderCallback(int page_index ) {
    this->current_page_index_ = page_index;
  }
  virtual ~FxParagraphEditingProviderCallback() {}

  virtual void Release() { delete this; }

  virtual foxit::Matrix GetRenderMatrix( const pdf::PDFDoc& document, int page_index) {
    PDFPage page = (PDFDoc(document)).GetPage(page_index);
    int width = static_cast<int>(page.GetWidth());
    int height = static_cast<int>(page.GetHeight());
    Matrix matrix = page.GetDisplayMatrix(0, 0, width, height, e_Rotation0);
    return matrix;
  }
  virtual void* GetPageViewHandle(const pdf::PDFDoc& document, int page_index) {
    return NULL;
  }
  virtual foxit::RectF GetClientRect(const pdf::PDFDoc& document) {
    return foxit::RectF();
  }
  virtual float GetScale(const pdf::PDFDoc& document, int page_index) {
    return 1.0f;
  }
  virtual bool GotoPageView(const pdf::PDFDoc& document, int page_index, float left, float top) {
    return true;
  }
  virtual Int32Array GetVisiblePageIndexArray(const pdf::PDFDoc& document) {
    Int32Array page_array;
    int pageindex = this->current_page_index_;
    page_array.Add(pageindex);
    return page_array;
  }
  virtual RectF GetPageVisibleRect(const pdf::PDFDoc& document, int page_index) {
    return foxit::RectF();
  }
  virtual foxit::RectF GetPageRect(const pdf::PDFDoc& document, int page_index) {
    PDFDoc doc = document;
    PDFPage page = doc.GetPage(page_index);
    float width = page.GetWidth();
    float height = page.GetHeight();
    RectF rect;
    rect.left = 0;
    rect.bottom = height;
    rect.right = width;
    rect.top = 0;
    return rect;
  }
  virtual int GetCurrentPageIndex(const pdf::PDFDoc& document) {
    return this->current_page_index_;
  }
  virtual common::Rotation GetRotation(const pdf::PDFDoc& document, int page_index) {
    PDFPage page = (PDFDoc(document)).GetPage(page_index);
    Rotation rotation = page.GetRotation();
    return rotation;
  }
  virtual void InvalidateRect(const pdf::PDFDoc& document, int page_index, const RectFArray& invalid_rects) {

  }
  virtual void AddUndoItem(const ParagraphEditingUndoItem& undo_item) {
  }
  virtual void SetDocChangeMark(const pdf::PDFDoc& document) {
  }
  virtual void NotifyTextInputReachLimit(const pdf::PDFDoc& document, int page_index) {
  }

private:
  int current_page_index_;
};

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"paragraph_editing/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file = input_path + L"AboutFoxit.pdf";
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    PDFDoc doc(input_file);
    ErrorCode code = doc.Load();
    if (code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }
    PDFPage page = doc.GetPage(0);
    page.StartParse();
    float height = page.GetHeight();

    FxParagraphEditingProviderCallback *callback = new FxParagraphEditingProviderCallback(page.GetIndex());
    ParagraphEditingMgr touchup_mgr = ParagraphEditingMgr(callback, doc);
    //Paragraph_editing
    {
      ParagraphEditing paragraphEditing = touchup_mgr.GetParagraphEditing();
      paragraphEditing.Activate();
      //insert
      paragraphEditing.StartEditing(0,PointF(95, height - 728), PointF(95, height - 728));
      paragraphEditing.SetFontSize(24);
      paragraphEditing.SetUnderline(true);
      paragraphEditing.InsertText(L"InsertText_Paragraph_editing");
      //delete
      paragraphEditing.OnLButtonDown(0, PointF(95, height - 728));
      paragraphEditing.OnMouseMove(0, PointF(99, height - 728));
      paragraphEditing.OnLButtonUp(0, PointF(99, height - 728));
      paragraphEditing.DeleteSelected();

      paragraphEditing.Deactivate();
      WString save_pdf_path = output_directory + L"Paragraph_editing.pdf";
      doc.SaveAs(save_pdf_path, PDFDoc::e_SaveFlagNoOriginal);
    }
    //Join&split
    {
      JoinSplit joinSplit = touchup_mgr.GetJoinSplit();
      joinSplit.Activate();
      joinSplit.OnLButtonDown(0, PointF(289, 659));
      joinSplit.OnLButtonUp(0, PointF(289, 659));
      joinSplit.SplitBoxes();
      joinSplit.Deactivate();
      WString save_pdf_path = output_directory + L"Split_Boxes.pdf";
      doc.SaveAs(save_pdf_path, PDFDoc::e_SaveFlagNoOriginal);

      joinSplit.Activate();
      joinSplit.OnLButtonDown(0, PointF(307, height - 637));
      joinSplit.OnLButtonUp(0, PointF(307, height - 637));
      joinSplit.OnLButtonDown(0, PointF(307, height - 453));
      joinSplit.OnLButtonUp(0, PointF(307, height - 453));
      joinSplit.JoinBoxes();
      joinSplit.Deactivate();
      save_pdf_path = output_directory + L"Join_Boxes.pdf";
      doc.SaveAs(save_pdf_path, PDFDoc::e_SaveFlagNoOriginal);
    }
    cout << "Paragraph editing successfully." << endl;

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

