// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to get preflight keys and analyze or fixup PDF file.

#include <time.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/addon/compliance/fs_compliancecommon.h"
#include "../../../include/addon/compliance/fs_pdfa.h"
#include "../../../include/addon/compliance/fs_pdfcompliance.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace addon;
using namespace compliance;

static const char* sn = "XQSqpYXftiFIcjaUVzEYXWVFvT86aRH+NpxaYmpzjXt+knIjbaBmMQ==";
static const char* key = "8f3g1kNstBkNAgfCSIczuioWaeXe4+c9+glonrwf6b2LMfDWf0CC92cxiF1M4Re6KUqmkA3+M4O1IRQXmfDg2WnFjr6Fy5eBqpmElth3Kch1UnDYqzIPf4PVOEZvUd51NT/a3Rp2dprVjI9p43m4BRUbHi14Ls5WJrbjiVImPsVCUGD4vLwv5KivNUlruYxBJklnVqASv/Ql2eMYs+QjkW2FF561ojrhWBbkZo+foLp7Dks6zaDFn2bjnFO0QQoD20LdUWuJc38kL+k6tcTaieNizW1FzvFVFDY8NWnaPY7k9nth2Ty5DtIdwMs2WuHrWIgd01SI/FkGZnVjdnmHMrGMNaJeiLJi64khor68iqTH+5C+3Eq48zfcsrsA8Qpe3GDEMHA1aDadhOj+wM1jFvjDQNQR4UQrgVEcS8HhoQECjJv3p/n6zpqSUEHwgoWt3MCZaOButo4qsSUf00/oFCrSaKugMwZsIZPzLilaIvyDYEyVUTDeZmnFRCri9Bnylj/uD+N2EPm2YZnsePp/ORv3FIHlNMl6kOQXmZMKsZMGQcCLc8Xxf9nSaiZzYD1jRgcytPBP0ROfN/rG3EI/1lG+ZCnax9oadtpEbEGjUvja70YRE14iVwR8QIRFVpqJVZTCMcmuFpMFfC2CKcYQORBygs+6bnobAli9qIzIoXvbk2gYI5X2WhkZHRwIrOXwk3fW9nFKjCXVpyYSFSdOrkRQdAT5u+6eEIaSD47GmIHoaDDlHH1RF6BusVsCqvfAfG8qIYJNes2q/c5nheCmBThdWjl4MKwxPH7K306MaekAKFPJAwKhBTES9nZrsseQLQ9v8WNGTZyBwJucEHMCol+Vk3lf+PpKEaD6G8TT7n36V43XJ/N09APgDcGxGB4rAAeinCbANyaYOQtZ0jb+5Jb/NKQ2grdA9KoEvafLE09J4VSloQPQOCCbIwhrvwZO0guWaEjXbiN4UPzSOnyQK7lZfFNmAIgjZtAqzIL8yeGes0I/CCI4CiRKz+pFh313WLtbKi3acqO7GrlFH9g652bkeITPg06fhkqSVjf7iHv+ZpZYXWz+K0FiTUaCinPzNKOCWbYrqNcWaM1Y6bR/uoUJkSUMoODHZ3csWhOz7VqUVZc9M4U6Qg0+0wck3w+ZbdEyVSlWnAPXkphg4UYMrMrUFUzHYSjORTdXoLYMveoIbWMhubtugl0DqD8hOEWqaGYYlJo2N2WU54mYEIaoZ8wfpWsMVOfPFyi5j754lngonq5vf36inXn3xRO5CkYFrzXKJ3n2DYiSrVV0ll/5WTkR3F/lEby4CP81UkVubm4GrvH7fBnhQuWgV9GlZbZhaCWl6FC1dnabn+sNwvh3iEP/2oWqi2013gtQQlSSFE5mCg+pCr6zFEAUTNHBqQZrXyMdIJ9tNimbX551HE+bKp5Eog1wHWP1k3orEjQUwm+R";

#if defined(_WIN32) || defined(_WIN64)
static WString output_path = WString::FromLocal("../output_files/");
static WString input_path = WString::FromLocal("../input_files/");
#else
static WString output_path = WString::FromLocal("./output_files/");
static WString input_path = WString::FromLocal("./input_files/");
#endif
static WString output_directory = output_path + L"preflight/";

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

  void Write(const char* text_content);
  void Write(const wchar_t* text_content);

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

  uint8 temp[] = {0xFF,0xFE};
  fwrite(temp, sizeof(uint8), 2, file_);
  fseek(file_, 0, SEEK_END);

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

  uint8 temp[] = {0xFF,0xFE};
  fwrite(temp, sizeof(uint8), 2, file_);
  fseek(file_, 0, SEEK_END);

}

TextDoc::~TextDoc() {
  fclose(file_);
  file_ = NULL;
}

void TextDoc::Write(const char* text_content) {
  WString wide_str = WString::FromLocal(text_content);
  Write(wide_str);
}

void TextDoc::Write(const wchar_t* text_content) {
  WString wide_str(text_content);
  if (wide_str.IsEmpty()) return ;
  String utf16le_str = wide_str.UTF16LE_Encode(false);
  if (utf16le_str.IsEmpty()) return;
  int length = utf16le_str.GetLength();
  fwrite((const char*)utf16le_str, sizeof(char), length, file_);
}

class MyComplianceProgressCallback : public ProgressCallback {
public:
  MyComplianceProgressCallback(const WString& output_txt_file_path);
  ~MyComplianceProgressCallback();

  virtual void Release();
  virtual void UpdateCurrentStateData(int current_rate, const WString& current_state_string);

private:
  TextDoc text_doc_;
};

MyComplianceProgressCallback::MyComplianceProgressCallback(const WString& output_txt_file_path)
  : text_doc_(output_txt_file_path, L"w+b") {}

MyComplianceProgressCallback::~MyComplianceProgressCallback() {}

void MyComplianceProgressCallback::Release() {

}

void MyComplianceProgressCallback::UpdateCurrentStateData(int current_rate, const WString& current_state_string) {
  std::cout << "Current rate:" << current_rate << std::endl;

  char temp_string[32];
#if defined(_WIN32) || defined(_WIN64)
  sprintf_s(temp_string, 32, "Current rate:%d, state str:", current_rate);
#else
  sprintf(temp_string, "Current rate:%d, state str:", current_rate);
#endif  // defined(_WIN32) || defined(_WIN64)
  text_doc_.Write(temp_string);
  text_doc_.Write(current_state_string);
  text_doc_.Write("\r\n");
}

void ListPreflightKeys(Preflight preflight, const PreflightSettingData::LibraryType& library_type, const PreflightSettingData::OperateType& operate_type) {
  StringArray group_arr = preflight.GetGroupNamesArray(library_type, operate_type);
  for (int i = 0; i < group_arr.GetSize(); i++) {
    cout << "Group name: " << group_arr[i] << endl;
    StringArray item_array = preflight.GetItemKeysArray(group_arr[i]);
    cout << "    Item count: " << item_array.GetSize() << endl;
    for (int j = 0; j < item_array.GetSize(); j++) {
      cout << "    Item name: " << item_array[j] << endl;
    }
  }
}

void AnalyzeAndFixup(Preflight preflight, const PreflightSettingData::OperateType& operate_type, const WString& preflight_key, bool is_fixed) {
  PreflightSettingData setting_data;
  setting_data.operate_type = operate_type;
  setting_data.preflight_key = preflight_key;
  setting_data.first_page_index = 0;
  setting_data.src_pdf_path = input_path + L"AboutFoxit.pdf";
  WString fixpath = output_directory + L"AboutFoxit_" + preflight_key + L"_fixed.pdf";
  setting_data.saved_pdf_path = fixpath;
  MyComplianceProgressCallback* progress_callback = new MyComplianceProgressCallback(output_directory + L"AboutFoxit_" + preflight_key + L"_progress.txt");
  if(is_fixed)
    preflight.AnalyzeAndFixup(setting_data, progress_callback);
  else
    preflight.Analyze(setting_data, progress_callback);
}

void GenerateReport(Preflight preflight, const PreflightReportSettingData::ReportFileFormatType& format_type, const WString& preflight_key) {
  PreflightReportSettingData report_setting_data;
  report_setting_data.report_file_format_type = format_type;
  WString path = output_directory + L"AboutFoxit_" + preflight_key + L"_report.pdf";
  report_setting_data.report_file_path = path;
  report_setting_data.to_generate_overview = true;
  report_setting_data.to_highlight_problems = true;
  report_setting_data.problems_highlight_method = PreflightReportSettingData::e_ProblemsHighlightMethodTransparentMasks;
  preflight.GenerateReport(report_setting_data, NULL);
}

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"preflight/";
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
    // "compliance_resource_folder_path" is the path of compliance resource folder. Please refer to Developer Guide for more details.
    WString compliance_resource_folder_path = L"";
    // If you use an authorization key for Foxit PDF SDK, please set a valid unlock code string to compliance_engine_unlockcode for ComplianceEngine.
    // If you use an trial key for Foxit PDF SDK, just keep compliance_engine_unlockcode as an empty string.
    const char* compliance_engine_unlockcode = "";

    if (compliance_resource_folder_path.IsEmpty()) {
      std::cout << "compliance_resource_folder_path is still empty. Please set it with a valid path to compliance resource folder path." << std::endl;
      return 1;
    }
    // Initialize compliance engine.
    ErrorCode error_code = ComplianceEngine::Initialize(compliance_resource_folder_path, compliance_engine_unlockcode);
    if (error_code != foxit::e_ErrSuccess) {
      switch (error_code) {
      case foxit::e_ErrInvalidLicense:
        printf("[Failed] Compliance module is not contained in current Foxit PDF SDK keys.\n");
        break;
      default:
        printf("[Failed] Fail to initialize compliance engine. Error: %d\n", error_code);
        break;
      }
      return 1;
    }
    cout << "ComplianceEngine is initialized." << endl;
    {
      Preflight preflight;
      // List all Foxit preflight keys.
      cout << "Library Type: Foxit, Operate Type: Profiles" << endl;
      ListPreflightKeys(preflight, PreflightSettingData::e_LibraryTypeFoxit, PreflightSettingData::e_OperateTypeProfiles);
      cout << "Library Type: Foxit, Operate Type: Checks" << endl;
      ListPreflightKeys(preflight, PreflightSettingData::e_LibraryTypeFoxit, PreflightSettingData::e_OperateTypeSingleChecks);
      cout << "Library Type: Foxit, Operate Type: Fixups" << endl;
      ListPreflightKeys(preflight, PreflightSettingData::e_LibraryTypeFoxit, PreflightSettingData::e_OperateTypeSingleFixups);
      
      bool is_fixup = false;
      // Analyze and fixup a PDF file.
      cout << "== Profiles. ==" << endl;
      is_fixup = preflight.CanFixup("pppp_ConverttoPDFA1a");
      AnalyzeAndFixup(preflight, PreflightSettingData::e_OperateTypeProfiles, L"pppp_ConverttoPDFA1a", is_fixup);
      GenerateReport(preflight, PreflightReportSettingData::e_ReportFileFormatTypePdf, L"pppp_ConverttoPDFA1a");
    
      // Analyze a PDF file.
      cout << "== Single Checks.==" << endl;
      AnalyzeAndFixup(preflight, PreflightSettingData::e_OperateTypeSingleChecks, L"R_6_Annotationinsidepagearea", false);
      GenerateReport(preflight, PreflightReportSettingData::e_ReportFileFormatTypePdf, L"R_6_Annotationinsidepagearea");
    
      //Fixup a PDF file.
      cout << "== Single Fixups. ==" << endl;
      AnalyzeAndFixup(preflight, PreflightSettingData::e_OperateTypeSingleFixups, L"F_9_RemoveXMPMetadataifnotcompliantwithPDFA1", true);
      GenerateReport(preflight, PreflightReportSettingData::e_ReportFileFormatTypePdf, L"F_9_RemoveXMPMetadataifnotcompliantwithPDFA1");
    }
    // Release compliance engine.
    ComplianceEngine::Release();

    cout << "== End: Preflight demo. ==" << endl;

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

