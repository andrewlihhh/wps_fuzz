// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to export data, import data and reset form for
// XFA document.

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
#include "../../../include/pdf/interform/fs_pdfform.h"
#include "../../../include/addon/xfa/fs_xfa.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace annots;
using namespace actions;
using namespace interform;
using namespace foxit::addon::xfa;

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

class CFS_XFAAppHandler : public foxit::addon::xfa::AppProviderCallback
{
public:
    CFS_XFAAppHandler() {}
    ~CFS_XFAAppHandler() {}

    virtual void Release() {
        delete this;
    }

    virtual WString GetAppInfo(AppInfo app_info) {
        return L"Foxit SDK";
    }
    virtual void Beep(BeepType type) {}
    virtual AppProviderCallback::MsgBoxButtonID MsgBox(const wchar_t* message, const wchar_t* title = NULL,
        MsgBoxIconType icon_type = e_MsgBoxIconError,
        MsgBoxButtonType button_type = e_MsgBtnTypeOK) {
            return (AppProviderCallback::MsgBoxButtonID)0;
    }
    virtual WString Response(const wchar_t* question, const wchar_t* title, const wchar_t* default_answer = NULL,
        bool is_mask = true) {
            return L"answer";
    }
    virtual common::file::ReaderCallback* DownLoadUrl(const wchar_t* url) {
        return NULL;
    }
    virtual WString PostRequestURL(const wchar_t* url, const wchar_t* data, const wchar_t* content_type, const wchar_t* encode, const wchar_t* header) {
        return L"PostRequestUrl";
    }
    virtual bool PutRequestURL(const wchar_t* url, const wchar_t* data, const wchar_t* encode) {
        return TRUE;
    }
    virtual WString LoadString(AppProviderCallback::StringID string_id) {
        return L"LoadString";
    }

    virtual WStringArray ShowFileDialog(const wchar_t* string_title, const wchar_t* string_filter, bool is_openfile_dialog = TRUE) {
        return WStringArray();
    }
};

class CFS_XFADocHandler:public foxit::addon::xfa::DocProviderCallback
{
public:
    CFS_XFADocHandler() {}
    ~CFS_XFADocHandler() {}

    virtual void Release(){
        delete this;
    }
    virtual void InvalidateRect(int page_index, const RectF &rect, InvalidateFlag flag) {}
    virtual void DisplayCaret(int page_index, bool is_visible, const RectF &rect) {}
    virtual bool GetPopupPos(int page_index, float min_popup, float max_popup,
        const RectF &rect_widget, RectF &rect_popup) {
            return TRUE;
    }
    virtual bool PopupMenu(int page_index, const PointF& rect_popup) {
        return TRUE;
    }
    virtual int GetCurrentPage(const foxit::addon::xfa::XFADoc& doc) {
        return 0;
    }
    virtual void SetCurrentPage(const foxit::addon::xfa::XFADoc& doc, int current_page_index) {}
    virtual WString GetTitle(const foxit::addon::xfa::XFADoc& doc) {
        return L"title";
    }
    virtual void ExportData(const foxit::addon::xfa::XFADoc& doc, const WString& file_path) {}
    virtual void ImportData(const foxit::addon::xfa::XFADoc& doc, const WString& file_path) {}
    virtual void GotoURL(const foxit::addon::xfa::XFADoc& doc, const WString& url) {}
    virtual void Print(const foxit::addon::xfa::XFADoc& doc, int start_page_index, int end_page_index, uint32 options) {}
    virtual ARGB GetHighlightColor(const foxit::addon::xfa::XFADoc& doc) {
        if(doc.GetType() == foxit::addon::xfa::XFADoc::e_Static) {
            return 0x50FF0000;
        }
        else {
            return 0x500000FF;
        }
    }
    virtual bool SubmitData(const foxit::addon::xfa::XFADoc& doc, const WString& target, SubmitFormat format, TextEncoding text_encoding, const WString& content) {
        return TRUE;
    }
    virtual void SetFocus(foxit::addon::xfa::XFAWidget& xfa_widget, bool is_relayout) {};
    virtual void PageViewEvent(int page_index, PageViewEventType page_view_event_type) {}
    virtual void SetChangeMark(const foxit::addon::xfa::XFADoc& doc) {}
    virtual void WidgetEvent(const foxit::addon::xfa::XFAWidget& xfa_widget,WidgetEventType widget_event_type) {}
    virtual void NotifyWidgetChangeInfo(const foxit::addon::xfa::XFADoc& doc, foxit::addon::xfa::XFAWidgetModifyInfo change_info) {}
};

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"xfa_form/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    CFS_XFAAppHandler* pXFAAppHandler = new CFS_XFAAppHandler();
    Library::RegisterXFAAppProviderCallback(pXFAAppHandler);
    WString input_file = input_path + L"xfa_dynamic.pdf";
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
    }

    CFS_XFADocHandler* pXFADocHandler = new CFS_XFADocHandler();
    XFADoc xfa_doc(doc, pXFADocHandler);
    xfa_doc.StartLoad(NULL);

    xfa_doc.ExportData(output_directory + L"xfa_form.xml", XFADoc::e_ExportDataTypeXML);
    
    xfa_doc.ResetForm();
    doc.SaveAs(output_directory + L"xfa_dynamic_resetform.pdf");

    xfa_doc.ImportData(output_directory + L"xfa_form.xml");
    doc.SaveAs(output_directory + L"xfa_dynamic_importdata.pdf");
    cout << "Xfa test." << endl;
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
