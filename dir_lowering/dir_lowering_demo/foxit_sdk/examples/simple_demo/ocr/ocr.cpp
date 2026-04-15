// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to do OCR for a PDF page or PDF document.
// Windows platform supports 32-bit and 64-bit,Linux platform only supports 64-bit.

#if (defined(_WIN32) || defined(_WIN64)) || (defined(__linux__) && defined(__x86_64__))

// Include Foxit SDK header files.
//#include <time.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/addon/ocr/fs_ocr.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace addon::ocr;

static const char* sn = "XQSqpYXftiFIcjaUVzEYXWVFvT86aRH+NpxaYmpzjXt+knIjbaBmMQ==";
static const char* key = "8f3g1kNstBkNAgfCSIczuioWaeXe4+c9+glonrwf6b2LMfDWf0CC92cxiF1M4Re6KUqmkA3+M4O1IRQXmfDg2WnFjr6Fy5eBqpmElth3Kch1UnDYqzIPf4PVOEZvUd51NT/a3Rp2dprVjI9p43m4BRUbHi14Ls5WJrbjiVImPsVCUGD4vLwv5KivNUlruYxBJklnVqASv/Ql2eMYs+QjkW2FF561ojrhWBbkZo+foLp7Dks6zaDFn2bjnFO0QQoD20LdUWuJc38kL+k6tcTaieNizW1FzvFVFDY8NWnaPY7k9nth2Ty5DtIdwMs2WuHrWIgd01SI/FkGZnVjdnmHMrGMNaJeiLJi64khor68iqTH+5C+3Eq48zfcsrsA8Qpe3GDEMHA1aDadhOj+wM1jFvjDQNQR4UQrgVEcS8HhoQECjJv3p/n6zpqSUEHwgoWt3MCZaOButo4qsSUf00/oFCrSaKugMwZsIZPzLilaIvyDYEyVUTDeZmnFRCri9Bnylj/uD+N2EPm2YZnsePp/ORv3FIHlNMl6kOQXmZMKsZMGQcCLc8Xxf9nSaiZzYD1jRgcytPBP0ROfN/rG3EI/1lG+ZCnax9oadtpEbEGjUvja70YRE14iVwR8QIRFVpqJVZTCMcmuFpMFfC2CKcYQORBygs+6bnobAli9qIzIoXvbk2gYI5X2WhkZHRwIrOXwk3fW9nFKjCXVpyYSFSdOrkRQdAT5u+6eEIaSD47GmIHoaDDlHH1RF6BusVsCqvfAfG8qIYJNes2q/c5nheCmBThdWjl4MKwxPH7K306MaekAKFPJAwKhBTES9nZrsseQLQ9v8WNGTZyBwJucEHMCol+Vk3lf+PpKEaD6G8TT7n36V43XJ/N09APgDcGxGB4rAAeinCbANyaYOQtZ0jb+5Jb/NKQ2grdA9KoEvafLE09J4VSloQPQOCCbIwhrvwZO0guWaEjXbiN4UPzSOnyQK7lZfFNmAIgjZtAqzIL8yeGes0I/CCI4CiRKz+pFh313WLtbKi3acqO7GrlFH9g652bkeITPg06fhkqSVjf7iHv+ZpZYXWz+K0FiTUaCinPzNKOCWbYrqNcWaM1Y6bR/uoUJkSUMoODHZ3csWhOz7VqUVZc9M4U6Qg0+0wck3w+ZbdEyVSlWnAPXkphg4UYMrMrUFUzHYSjORTdXoLYMveoIbWMhubtugl0DqD8hOEWqaGYYlJo2N2WU54mYEIaoZ8wfpWsMVOfPFyi5j754lngonq5vf36inXn3xRO5CkYFrzXKJ3n2DYiSrVV0ll/5WTkR3F/lEby4CP81UkVubm4GrvH7fBnhQuWgV9GlZbZhaCWl6FC1dnabn+sNwvh3iEP/2oWqi2013gtQQlSSFE5mCg+pCr6zFEAUTNHBqQZrXyMdIJ9tNimbX551HE+bKp5Eog1wHWP1k3orEjQUwm+R";

#if defined(_WIN32) || defined(_WIN64)
static WString output_path = WString::FromLocal("../output_files/");
static WString input_path = WString::FromLocal("../input_files/ocr/");
#else
static WString output_path = WString::FromLocal("./output_files/");
static WString input_path = WString::FromLocal("./input_files/ocr/");
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

int main(int argc, char *argv[]) {
  int err_ret = 0;
  WString input_file = input_path + L"AboutFoxit_ocr.pdf";

  WString output_directory = output_path + L"ocr/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    // "ocr_resource_path" is the path of ocr resources. Please refer to Developer Guide for more details.
    WString ocr_resource_path = L"";

    if (ocr_resource_path.IsEmpty()) {
      std::cout<<"ocr_resource_path is still empty. Please set it with a valid path to OCR resource path."<<std::endl;
      return 1;
    }

    // Initialize OCR engine.
    error_code = OCREngine::Initialize(ocr_resource_path);
    if (error_code != foxit::e_ErrSuccess) {
      switch(error_code){
        case foxit::e_ErrInvalidLicense:
          printf("[Failed] OCR module is not contained in current Foxit PDF SDK keys.\n");
          break;
        default:
          printf("Fail to initialize OCR engine. Error: %d\n", error_code);
          break;
      }
      return 1;
    }
    cout << "OCREngine is initialized." << endl;

    // Set log for OCREngine. (This can be opened to set log file if necessary)
    //OCREngine::SetLogFile(output_directory+L"ocr.log");
    // Set languages.
    OCREngine::SetLanguages(L"English");

    // OCR PDF document, only for search, not editable.
    {
      PDFDoc doc(input_file);
      ErrorCode error_code = doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
      }
      OCR ocr_operator;
      ocr_operator.OCRPDFDocument(doc, false);

      WString save_pdf_path = output_directory + L"ocr_doc_searchable.pdf";
      doc.SaveAs(save_pdf_path, PDFDoc::e_SaveFlagNoOriginal);
    }
    // OCR PDF document, editable.
    {
      PDFDoc doc(input_file);
      ErrorCode error_code = doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
      }
      OCR ocr_operator;
      ocr_operator.OCRPDFDocument(doc, true);

      WString save_pdf_path = output_directory + L"ocr_doc_editable.pdf";
      doc.SaveAs(save_pdf_path, PDFDoc::e_SaveFlagNoOriginal);
    }
    // OCR PDF page, only for search, not editable.
    {
      PDFDoc doc(input_file);
      ErrorCode error_code = doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
      }
      PDFPage page = doc.GetPage(0);
      page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);

      OCR ocr_operator;
      ocr_operator.OCRPDFPage(page, false);

      WString save_pdf_path = output_directory + L"ocr_page_searchable.pdf";
      doc.SaveAs(save_pdf_path, PDFDoc::e_SaveFlagNoOriginal);
    }
    // OCR PDF page, editable.
    {
      PDFDoc doc(input_file);
      ErrorCode error_code = doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
      }
      PDFPage page = doc.GetPage(0);
      page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);

      OCR ocr_operator;
      ocr_operator.OCRPDFPage(page, true);

      WString save_pdf_path = output_directory + L"ocr_page_editable.pdf";
      doc.SaveAs(save_pdf_path, PDFDoc::e_SaveFlagNoOriginal);
    }

    OCREngine::Release();

    cout << "END: OCR demo." << endl;
  } catch (const Exception& e) {
    switch(e.GetErrCode()){
      case foxit::e_ErrInvalidLicense:
        printf("[Failed] OCR module is not contained in current Foxit PDF SDK keys.\n");
        break;
      default:
        printf("%s\n", (const char*)e.GetMessage());
        break;
    }
    err_ret = 1;
  }
  catch(...)
  {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}

#endif  // (defined(_WIN32) || defined(_WIN64)) || (defined(__linux__) && defined(__x86_64__))
