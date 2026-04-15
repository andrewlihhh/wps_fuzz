// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF Conversion SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to convert PDF files to Office(Word,
// Excel or PowerPoint) format files.

#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#else
#include <sys/stat.h>
#endif
#include <iostream>
#include <string>

#include "../../../include/common/fs_common.h"
#include "../../../include/addon/conversion/pdf2office/fs_pdf2office.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using namespace foxit::common::file;
using foxit::common::Library;
using namespace addon::conversion::pdf2office;

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
  SdkLibMgr()
      : is_initialize_(false){};
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

class CustomConvertCallback : public ConvertCallback {
 public:
  CustomConvertCallback() {}
  ~CustomConvertCallback() {}
  virtual bool NeedToPause() {
    return true;
  }

  virtual void ProgressNotify(int converted_count, int total_count) {}
};

class FileReader : public ReaderCallback {
 public:
  FileReader()
      : file_(NULL){}
  ~FileReader() {}

  bool LoadFile(const char* file_path) {
#if defined(_WIN32) || defined(_WIN64)
    fopen_s(&file_, file_path, "rb");
#else
    file_ = fopen(file_path, "rb");
#endif
    if (!file_)
      return false;
    return true;
  }

  FX_FILESIZE GetSize() {
    if (!file_)
      return 0;
    fseek(file_, 0, SEEK_END);
    return (FX_FILESIZE)ftell(file_);
  }

  FX_BOOL ReadBlock(void* buffer, FX_FILESIZE offset, size_t size) {
    if (!file_)
      return 0;
    if (0 != fseek(file_, (long)offset, 0))
      return 0;
    if (0 == fread(buffer, size, 1, file_))
      return 0;
    return 1;
  }

  size_t ReadBlock(void* buffer, size_t size) {
    if (!file_)
      return false;
    if (0 != fseek(file_, 0, 0))
      return 0;
    return fread(buffer, size, 1, file_);
  }

  void Release() {
    if (file_)
      fclose(file_);
    file_ = NULL;
    delete this;
  }

 private:
  FILE* file_;
};

class FileStream : public StreamCallback {
 public:
  FileStream()
      : file_(NULL)
      , ref_(1)
      , cur_pos_(SEEK_SET) {}

  ~FileStream() {}

  bool LoadFile(const char* file_path) {
#if defined(_WIN32) || defined(_WIN64)
    fopen_s(&file_, file_path, "wb");
#else
    file_ = fopen(file_path, "wb");
#endif
    if (!file_)
      return false;
    return true;
  }

  FX_FILESIZE GetSize() {
    if (!file_)
      return 0;
    fseek(file_, 0, SEEK_END);
    return (FX_FILESIZE)ftell(file_);
  }

  FX_BOOL Flush() {
    fflush(file_);
    return true;
  }

  FX_FILESIZE GetPosition() {
    return cur_pos_;
  }

  FX_BOOL ReadBlock(void* buffer, FX_FILESIZE offset, size_t size) {
    if (!file_)
      return false;
    if (0 != fseek(file_, (long)offset, 0))
        return false;
    if (0 == fread(buffer, size, sizeof(char), file_))
        return false;

    cur_pos_ = offset + size;
    return true;
  }

  size_t ReadBlock(void* buffer, size_t size) {
    if (ReadBlock(buffer, GetSize(), size))
      return size;
    else
      return 0;
  }

  FX_BOOL WriteBlock(const void* buffer, FX_FILESIZE offset, size_t size) {
    if (!file_)
      return false;
    fseek(file_, (long)offset, SEEK_SET);
    uint64 write_size = fwrite(buffer, sizeof(char), size, file_);
    if (write_size == size) {
      cur_pos_ = offset + size;
      return true;
    }
    return false;
  }

  FX_BOOL WriteBlock(const void* data, size_t size) {
    return WriteBlock(data, GetSize(), size);
  }

  FileStream* Retain() {
    ref_++;
    return this;
  }

  FX_BOOL IsEOF() {
    if (!file_)
      return 0;
    fseek(file_, 0, SEEK_END);
    if (cur_pos_ < (FX_FILESIZE)ftell(file_))
      return false;
    return true;
  }

  void Release() {
    ref_--;
    if (ref_ == 0) {
      if (file_)
        fclose(file_);
      file_ = NULL;
      delete this;
    }
  }

 private:
  FILE* file_;
  int ref_;
  FX_FILESIZE cur_pos_;
};

int main(int argc, char* argv[]) {
  int err_ret = 0;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    if (foxit::e_ErrInvalidLicense == error_code)
      cout << "[Failed] Current used Foxit PDF Conversion SDK key information is invalid." << endl;
    return 1;
  }
  WString output_directory = output_path + L"pdf2office/";
#if defined(_WIN32) || defined(_WIN64)
    _mkdir(String::FromUnicode(output_directory));
#else
    mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  try {
    WString library_path = L"";   //Please ensure the path is valid.
    WString engine_path = L"";     //If you use engine to convert PDF to Office, please ensure the path is valid.
    PDF2Office::Initialize(library_path, engine_path); //Please ensure the path is valid.
    // Convert PDF file to Word format file.
    PDF2OfficeSettingData setting_data;
    CustomConvertCallback callback;
    Progressive progressive = PDF2Office::StartConvertToWord(input_path + L"word.pdf", NULL, output_directory + L"pdf2word_result.docx", setting_data, &callback);
    if (progressive.GetRateOfProgress() != 100) {
      Progressive::State state = Progressive::e_ToBeContinued;
      while (Progressive::e_ToBeContinued == state) {
        state = progressive.Continue();
      }
    }
    cout << "Convert PDF file to Word format file with path." << endl;

    CustomConvertCallback custom_callback_word_stream;
    FileReader* custom_readercallback_word = new FileReader();
    FileStream* custom_streamcallback_word = new FileStream();
    custom_readercallback_word->LoadFile(String::FromUnicode(input_path + L"word.pdf"));
    custom_streamcallback_word->LoadFile(String::FromUnicode(output_directory + L"pdf2word_withstream_result.docx"));
    progressive = PDF2Office::StartConvertToWord(custom_readercallback_word, L"", custom_streamcallback_word,
                                                 setting_data, &custom_callback_word_stream);
    if (progressive.GetRateOfProgress() != 100) {
      Progressive::State state = Progressive::e_ToBeContinued;
      while (Progressive::e_ToBeContinued == state) {
        state = progressive.Continue();
      }
    }
    cout << "Convert PDF file to Word format file with stream." << endl;

    // Convert PDF file to Excel format file.
    progressive = PDF2Office::StartConvertToExcel(input_path + L"excel.pdf", NULL, output_directory + L"pdf2excel_result.xlsx", setting_data);
    if (progressive.GetRateOfProgress() != 100) {
      Progressive::State state = Progressive::e_ToBeContinued;
      while (Progressive::e_ToBeContinued == state) {
        state = progressive.Continue();
      }
    }
    cout << "Convert PDF file to Excel format file with path." << endl;

    CustomConvertCallback custom_callback_excel_stream;
    FileReader* custom_readercallback_excel = new FileReader();
    FileStream* custom_streamcallback_excel = new FileStream();
    custom_readercallback_excel->LoadFile(String::FromUnicode(input_path + L"excel.pdf"));
    custom_streamcallback_excel->LoadFile(String::FromUnicode(output_directory + L"pdf2excel_withstream_result.xlsx"));
    progressive = PDF2Office::StartConvertToExcel(custom_readercallback_excel, L"", custom_streamcallback_excel,
                                                 setting_data, &custom_callback_excel_stream);
    if (progressive.GetRateOfProgress() != 100) {
      Progressive::State state = Progressive::e_ToBeContinued;
      while (Progressive::e_ToBeContinued == state) {
        state = progressive.Continue();
      }
    }
    cout << "Convert PDF file to Excel format file with stream." << endl;

    // Convert PDF file to PowerPoint format file.
    progressive = PDF2Office::StartConvertToPowerPoint(input_path + L"powerpoint.pdf", NULL, output_directory + L"pdf2powerpoint_result.pptx", setting_data);
    if (progressive.GetRateOfProgress() != 100) {
      Progressive::State state = Progressive::e_ToBeContinued;
      while (Progressive::e_ToBeContinued == state) {
        state = progressive.Continue();
      }
    }
    cout << "Convert PDF file to PowerPoint format file with path." << endl;

    CustomConvertCallback custom_callback_ppt_stream;
    FileReader* custom_readercallback_ppt = new FileReader();
    FileStream* custom_streamcallback_ppt = new FileStream();
    custom_readercallback_ppt->LoadFile(String::FromUnicode(input_path + L"powerpoint.pdf"));
    custom_streamcallback_ppt->LoadFile(
        String::FromUnicode(output_directory + L"pdf2powerpoint_withstream_result.pptx"));
    progressive = PDF2Office::StartConvertToPowerPoint(custom_readercallback_ppt, L"", custom_streamcallback_ppt,
                                                       setting_data, &custom_callback_ppt_stream);
    if (progressive.GetRateOfProgress() != 100) {
      Progressive::State state = Progressive::e_ToBeContinued;
      while (Progressive::e_ToBeContinued == state) {
        state = progressive.Continue();
      }
    }
    cout << "Convert PDF file to PowerPoint format file with stream." << endl;

  } catch (const Exception& e) {
    switch (e.GetErrCode()) {
      case foxit::e_ErrNoPDF2OfficeModuleRight:
        cout << "[Failed] Conversion module is not contained in current Foxit PDF Conversion SDK keys." << endl;
        break;
      default:
        cout << (FX_LPCSTR)e.GetMessage() << endl;
        break;
    }
    err_ret = 1;
  } catch (...) {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }
  PDF2Office::Release();
  return err_ret;
}
#endif  // #if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
