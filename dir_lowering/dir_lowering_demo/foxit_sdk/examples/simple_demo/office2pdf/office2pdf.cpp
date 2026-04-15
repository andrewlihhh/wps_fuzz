// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to convert Word or Excel files to PDF files.

// Include Foxit SDK header files.
#if defined(_WIN32) || defined(_WIN64)
#include<string.h>
#include<direct.h>
#else
#include <sys/stat.h>
#endif  // #if defined(_WIN32) || defined(_WIN64)

#include "../../../include/common/fs_common.h"
#include "../../../include/addon/conversion/fs_convert.h"
#include "../../../include/addon/conversion/office2pdf/fs_office2pdf.h"

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
  SdkLibMgr() : is_initialize_(false) {};
  ErrorCode Initialize() {
    ErrorCode error_code = Library::Initialize(sn, key);
    if (error_code != foxit::e_ErrSuccess) {
      printf("Library Initialize Error: %d\n", error_code);
    } else {
      is_initialize_ = true;
    }
    return error_code;
  }
  ~SdkLibMgr() {
    if (is_initialize_)
      Library::Release();
  }
private:
  bool is_initialize_;
};


int main(int argc, char *argv[]) {
  int err_ret = 0;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    if (foxit::e_ErrInvalidLicense == error_code)
      cout << "[Failed] Current used Foxit PDF SDK key information is invalid." << endl;
    return 1;
  }
  WString output_directory = output_path + L"office2pdf/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  try {
    // Conver Word file to PDF file.
    WString word_file_path = input_path + L"AboutFoxit.docx";
    WString output_path = output_directory + L"word2pdf_result.pdf";

    // Use default Word2PDFSettingData values.
    foxit::addon::conversion::Word2PDFSettingData word_convert_setting_data;
#if defined(_WIN32) || defined(_WIN64)
    foxit::addon::conversion::Convert::FromWord(word_file_path, L"", output_path, word_convert_setting_data);
#else
    WString engine_path = L"";// Please fill in the correct engine path. For example, "/usr/lib/libreoffice/program".
    foxit::addon::conversion::Convert::FromWord(word_file_path, L"", output_path, engine_path, word_convert_setting_data);
#endif

    cout << "Convert Word file to PDF file." << endl;

    // Conver Excel file to PDF file.
    WString excel_file_path = input_path + L"test.xlsx";
    output_path = output_directory + L"excel2pdf_result.pdf";
    // Use default Excel2PDFSettingData values.
    foxit::addon::conversion::Excel2PDFSettingData excel_convert_setting_data;
#if defined(_WIN32) || defined(_WIN64)
    foxit::addon::conversion::Convert::FromExcel(excel_file_path, L"", output_path, excel_convert_setting_data);
#else
    foxit::addon::conversion::Convert::FromExcel(excel_file_path, L"", output_path, engine_path, excel_convert_setting_data);
#endif
    cout << "Convert Excel file to PDF file." << endl;

    // Conver PowerPoint file to PDF file.
    WString ppt_file_path = input_path + L"test.pptx";
    output_path = output_directory + L"ppt2pdf_result.pdf";
    // Use default PowerPoint2PDFSettingData values.
    foxit::addon::conversion::PowerPoint2PDFSettingData ppt_convert_setting_data;
#if defined(_WIN32) || defined(_WIN64)
    foxit::addon::conversion::Convert::FromPowerPoint(ppt_file_path, L"", output_path, ppt_convert_setting_data);
#else
    foxit::addon::conversion::Convert::FromPowerPoint(ppt_file_path, L"", output_path, engine_path, ppt_convert_setting_data);
#endif
    cout << "Convert PowerPoint file to PDF file." << endl;

#if defined(_WIN32) || defined(_WIN64) || (defined(__linux__) && (defined(__i386__) || defined(__x86_64__)))
    //If you want to convert office files to PDF whitout other third-party engines, you can use the Office2PDF module.
    WString library_path = L"";//Path of Foxit Conversion SDK library, Please ensure the path is valid.
    //Initialize the Office2PDF module.
    foxit::addon::conversion::office2pdf::Office2PDF::Initialize(library_path);
    // Use default Office2PDFSettingData values.
    foxit::addon::conversion::office2pdf::Office2PDFSettingData office2pdf_setting_data;
    //A valid path of a folder which contains resource data files.
    office2pdf_setting_data.resource_folder_path = L"";
    // Conver Excel file to PDF file.
    output_path = output_directory + L"word2pdf_result_foxit.pdf";
    foxit::addon::conversion::office2pdf::Office2PDF::ConvertFromWord(word_file_path, L"", output_path, office2pdf_setting_data);
    cout << "Convert Word file to PDF file." << endl;
    // Conver Excel file to PDF file.
    output_path = output_directory + L"excel2pdf_result_foxit.pdf";
    foxit::addon::conversion::office2pdf::Office2PDF::ConvertFromExcel(excel_file_path, L"", output_path, office2pdf_setting_data);
    cout << "Convert Excel file to PDF file." << endl;
    // Conver PowerPoint file to PDF file.
    output_path = output_directory + L"ppt2pdf_result_foxit.pdf";
    foxit::addon::conversion::office2pdf::Office2PDF::ConvertFromPowerPoint(ppt_file_path, L"", output_path, office2pdf_setting_data);
    cout << "Convert PowerPoint file to PDF file." << endl;
    //Release the Office2PDF module.
    foxit::addon::conversion::office2pdf::Office2PDF::Release();
#endif
  } catch (const Exception& e) {
    switch (e.GetErrCode()) {
      case foxit::e_ErrNoConversionModuleRight:
        cout << "[Failed] Conversion module is not contained in current Foxit PDF SDK keys." << endl;
        break;
      case foxit::e_ErrNoMicroOfficeInstalled:
        cout << "[Failed] No Microsoft Office is installed in current system, so fail to do conversion from Word/Excel/PowerPoint to PDF." << endl;
        break;
      case foxit::e_ErrNoOffice2PDFModuleRight:
        cout << "[Failed] Office2PDF module is not contained in current Foxit PDF SDK keys." << endl;
        break;
      default:
        cout << e.GetMessage() << endl;
        break;
    }
    err_ret = 1;
  } catch (...) {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}


