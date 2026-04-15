// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to do optimize in PDF documents under a folder.

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
#include "../../../include/addon/optimization/fs_optimization.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace foxit::addon;

static const char* sn = "XQSqpYXftiFIcjaUVzEYXWVFvT86aRH+NpxaYmpzjXt+knIjbaBmMQ==";
static const char* key = "8f3g1kNstBkNAgfCSIczuioWaeXe4+c9+glonrwf6b2LMfDWf0CC92cxiF1M4Re6KUqmkA3+M4O1IRQXmfDg2WnFjr6Fy5eBqpmElth3Kch1UnDYqzIPf4PVOEZvUd51NT/a3Rp2dprVjI9p43m4BRUbHi14Ls5WJrbjiVImPsVCUGD4vLwv5KivNUlruYxBJklnVqASv/Ql2eMYs+QjkW2FF561ojrhWBbkZo+foLp7Dks6zaDFn2bjnFO0QQoD20LdUWuJc38kL+k6tcTaieNizW1FzvFVFDY8NWnaPY7k9nth2Ty5DtIdwMs2WuHrWIgd01SI/FkGZnVjdnmHMrGMNaJeiLJi64khor68iqTH+5C+3Eq48zfcsrsA8Qpe3GDEMHA1aDadhOj+wM1jFvjDQNQR4UQrgVEcS8HhoQECjJv3p/n6zpqSUEHwgoWt3MCZaOButo4qsSUf00/oFCrSaKugMwZsIZPzLilaIvyDYEyVUTDeZmnFRCri9Bnylj/uD+N2EPm2YZnsePp/ORv3FIHlNMl6kOQXmZMKsZMGQcCLc8Xxf9nSaiZzYD1jRgcytPBP0ROfN/rG3EI/1lG+ZCnax9oadtpEbEGjUvja70YRE14iVwR8QIRFVpqJVZTCMcmuFpMFfC2CKcYQORBygs+6bnobAli9qIzIoXvbk2gYI5X2WhkZHRwIrOXwk3fW9nFKjCXVpyYSFSdOrkRQdAT5u+6eEIaSD47GmIHoaDDlHH1RF6BusVsCqvfAfG8qIYJNes2q/c5nheCmBThdWjl4MKwxPH7K306MaekAKFPJAwKhBTES9nZrsseQLQ9v8WNGTZyBwJucEHMCol+Vk3lf+PpKEaD6G8TT7n36V43XJ/N09APgDcGxGB4rAAeinCbANyaYOQtZ0jb+5Jb/NKQ2grdA9KoEvafLE09J4VSloQPQOCCbIwhrvwZO0guWaEjXbiN4UPzSOnyQK7lZfFNmAIgjZtAqzIL8yeGes0I/CCI4CiRKz+pFh313WLtbKi3acqO7GrlFH9g652bkeITPg06fhkqSVjf7iHv+ZpZYXWz+K0FiTUaCinPzNKOCWbYrqNcWaM1Y6bR/uoUJkSUMoODHZ3csWhOz7VqUVZc9M4U6Qg0+0wck3w+ZbdEyVSlWnAPXkphg4UYMrMrUFUzHYSjORTdXoLYMveoIbWMhubtugl0DqD8hOEWqaGYYlJo2N2WU54mYEIaoZ8wfpWsMVOfPFyi5j754lngonq5vf36inXn3xRO5CkYFrzXKJ3n2DYiSrVV0ll/5WTkR3F/lEby4CP81UkVubm4GrvH7fBnhQuWgV9GlZbZhaCWl6FC1dnabn+sNwvh3iEP/2oWqi2013gtQQlSSFE5mCg+pCr6zFEAUTNHBqQZrXyMdIJ9tNimbX551HE+bKp5Eog1wHWP1k3orEjQUwm+R";

#if defined(_WIN32) || defined(_WIN64)
static WString output_path = WString::FromLocal("../output_files/");
static WString input_path = WString::FromLocal("../input_files/optimization/");
#else
static WString output_path = WString::FromLocal("./output_files/");
static WString input_path = WString::FromLocal("./input_files/optimization/");
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

class Optimization_Pause : public PauseCallback
{
public:
    Optimization_Pause(int pause_count_limit = 0, bool always_pause = false)
        :pause_count_(0)
        ,pause_count_limit_(pause_count_limit)
        ,always_pause_(always_pause)
    {

    }

    virtual FX_BOOL NeedToPauseNow()
    {
        if (always_pause_) return true;
        if (pause_count_< pause_count_limit_)
        {
            pause_count_ ++;
            return 1;
        }
        else{
            pause_count_ = 0;
            return 0; // This is to test a case: valid PauseCallback but needParseNow() will always return FALSE.
        }
    }

    void  ClearCount()
    {
        pause_count_ = 0;
    }

private:
    int pause_count_limit_;
    int pause_count_;
    bool always_pause_;
};


int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"optimization/";
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
  cout << "Optimized Start : Image Compression." << endl;
  WString input_file = input_path +  L"[Optimize]ImageCompression.pdf";
  try
  {
      PDFDoc doc(input_file);
      ErrorCode error_code = doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
          printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_path), error_code);
          return 1;
      }
      Optimization_Pause pause(0, true);
      addon::optimization::OptimizerSettings settings;
      settings.SetOptimizerOptions(foxit::addon::optimization::OptimizerSettings::e_OptimizerCompressImages);
      common::Progressive progressive = addon::optimization::Optimizer::Optimize(doc, settings, &pause);
      Progressive::State progress_state = Progressive::e_ToBeContinued;
      while (Progressive::e_ToBeContinued == progress_state) {
          progress_state = progressive.Continue();
          int percent = progressive.GetRateOfProgress();
          String res_string;
          res_string.Format("Optimize progress percent: %d %", percent);
          std::cout << res_string << std::endl;
      }
      if (Progressive::e_Finished == progress_state)
      {
          doc.SaveAs(output_directory + L"ImageCompression_Optimized.pdf", foxit::pdf::PDFDoc::e_SaveFlagRemoveRedundantObjects);
      }
  } catch (...) {
    cout << "Unknown Exception" << endl;
    return 1;
  }
  cout << "Optimized Finsih : Image Compression." << endl;

  cout << "Optimized Start : Clean up." << endl;
  input_file = input_path + L"[Optimize]Cleanup.pdf";
  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_path), error_code);
      return 1;
    }
    Optimization_Pause pause(0, true);
    addon::optimization::OptimizerSettings settings;
    settings.SetOptimizerOptions(foxit::addon::optimization::OptimizerSettings::e_OptimizerCleanUp);
    settings.SetCleanUpOptions(optimization::OptimizerSettings::e_CleanUpRemoveInvalidBookmarks | optimization::OptimizerSettings::e_CleanUpRemoveInvalidLinks
      | optimization::OptimizerSettings::e_CleanUpUseFlateForNonEncodedStream | optimization::OptimizerSettings::e_CleanUpUseFlateInsteadOfLZW);
    common::Progressive progressive = addon::optimization::Optimizer::Optimize(doc, settings, &pause);
    Progressive::State progress_state = Progressive::e_ToBeContinued;
    while (Progressive::e_ToBeContinued == progress_state) {
      progress_state = progressive.Continue();
      int percent = progressive.GetRateOfProgress();
      String res_string;
      res_string.Format("Optimize progress percent: %d %", percent);
      std::cout << res_string << std::endl;
    }
    if (Progressive::e_Finished == progress_state) {
      doc.SaveAs(output_directory + L"Cleanup_Optimized.pdf", foxit::pdf::PDFDoc::e_SaveFlagRemoveRedundantObjects);
    }
  } catch (...) {
    cout << "Unknown Exception" << endl;
    return 1;
  }
  cout << "Optimized Finsih : Clean up." << endl;

  cout << "Optimized Start : Discard Objects." << endl;
  input_file = input_path + L"[Optimize]DiscardObjects.pdf";
  try {
      PDFDoc doc(input_file);
      ErrorCode error_code = doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
          printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_path), error_code);
          return 1;
      }
      Optimization_Pause pause(0, true);
      addon::optimization::OptimizerSettings settings;
      settings.SetOptimizerOptions(foxit::addon::optimization::OptimizerSettings::e_OptimizerDiscardObjects);
      settings.SetDiscardObjectsOptions(optimization::OptimizerSettings::e_DiscardObjectsBookmarks | optimization::OptimizerSettings::e_DiscardObjectsEmbeddedPageThumbnails
          | optimization::OptimizerSettings::e_DiscardObjectsEmbeddedPrintSettings | optimization::OptimizerSettings::e_DiscardObjectsFlattenFormFields 
          | optimization::OptimizerSettings::e_DiscardObjectsFormActions | optimization::OptimizerSettings::e_DiscardObjectsJavaScriptActions);

      common::Progressive progressive = addon::optimization::Optimizer::Optimize(doc, settings, &pause);
      Progressive::State progress_state = Progressive::e_ToBeContinued;
      while (Progressive::e_ToBeContinued == progress_state) {
          progress_state = progressive.Continue();
          int percent = progressive.GetRateOfProgress();
          String res_string;
          res_string.Format("Optimize progress percent: %d %", percent);
          std::cout << res_string << std::endl;
      }
      if (Progressive::e_Finished == progress_state) {
          doc.SaveAs(output_directory + L"DiscardObjects_Optimized.pdf", foxit::pdf::PDFDoc::e_SaveFlagRemoveRedundantObjects);
      }
  }
  catch (...) {
      cout << "Unknown Exception" << endl;
      return 1;
  }
  cout << "Optimized Finsih : Discard Objects." << endl;
  return err_ret;
}