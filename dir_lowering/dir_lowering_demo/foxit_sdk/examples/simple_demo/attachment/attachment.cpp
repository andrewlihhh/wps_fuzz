// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to extract attached files from PDF files and
// add files as attachments to PDF files.

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
#include "../../../include/pdf/fs_filespec.h"
#include "../../../include/pdf/fs_pdfattachments.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace annots;
using foxit::pdf::annots::Line;

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

String DateTimeToString(const DateTime& datetime) {
  String s_datetime;
  s_datetime.Format((const char*)"%d/%d/%d-%d:%d:%d %s%d:%d", datetime.year, datetime.month, datetime.day, datetime.hour,
    datetime.minute, datetime.second, datetime.utc_hour_offset > 0 ? "+" : "-", datetime.utc_hour_offset,
    datetime.utc_minute_offset);
  return s_datetime;
}

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

int main(int argc, char *argv[])
{
  int err_ret = 0;
  WString input_file = input_path + L"attachment.pdf";

  WString output_directory = output_path + L"attachment/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  WString file_info = output_directory + L"attachMent_info.txt";
  SdkLibMgr sdk_lib_mgr;
  // Initialize library.
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    PDFDoc doc=PDFDoc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }

    {
      // Get information of attachments.
      Attachments attachments(doc);
      TextDoc text_doc(file_info, L"w+b");
      int count = attachments.GetCount();
      for (int i = 0; i < count; i++) {
        WString key = attachments.GetKey(i);
        text_doc.Write("key:\t\t%s\r\n", (const char*)String::FromUnicode(key));

        FileSpec file_spec = attachments.GetEmbeddedFile(key);
        if (!file_spec.IsEmpty()) {
          WString name = file_spec.GetFileName();
          text_doc.Write("Name:\t\t%s\r\n", (const char*)String::FromUnicode(name));
          text_doc.Write("Size:\t\t%d\r\n", file_spec.GetFileSize());
          text_doc.Write("Is embedded:\t%s\r\n", file_spec.IsEmbedded() ? "true" : "false");
          text_doc.Write("Creation time:\t%s\r\n", (const char*)DateTimeToString(file_spec.GetCreationDateTime()));
          text_doc.Write("Modified time:\t%s\r\n", (const char*)DateTimeToString(file_spec.GetModifiedDateTime()));
          text_doc.Write("\r\n");

          if (file_spec.IsEmbedded()) {
            WString exFilePath = output_directory + name;
            bool bExportStatus = file_spec.ExportToFile(exFilePath);
            cout << (const char*)String::FromUnicode(name) << " ExportToFile " << (bExportStatus ? "successful" : "failed") << endl;
          }
        }
      }
    }
    {
      // Remove all attachments
      Attachments attachment(doc);
      attachment.RemoveAllEmbeddedFiles();
      WString newPdf = output_directory + L"attachment_remove.pdf";
      doc.SaveAs(newPdf, PDFDoc::e_SaveFlagNoOriginal);
      cout << "Remove all attachments." << endl;

    }
    {
      WString text_path = input_path + L"AboutFoxit.pdf";
      Attachments attachment(doc);
      // Add a new attachment to PDF document.
      attachment.AddFromFilePath(L"OriginalAttachmentsInfo", text_path);
      WString newPdf = output_directory + L"attachment_add.pdf";
      doc.SaveAs(newPdf, PDFDoc::e_SaveFlagNoOriginal);
      cout << "Add a new attachment to PDF document." << endl;
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
