// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to do full text search in PDF documents under a folder.

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
#include "../../../include/fts/fs_fulltextsearch.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace foxit::fts;

static const char* sn = "XQSqpYXftiFIcjaUVzEYXWVFvT86aRH+NpxaYmpzjXt+knIjbaBmMQ==";
static const char* key = "8f3g1kNstBkNAgfCSIczuioWaeXe4+c9+glonrwf6b2LMfDWf0CC92cxiF1M4Re6KUqmkA3+M4O1IRQXmfDg2WnFjr6Fy5eBqpmElth3Kch1UnDYqzIPf4PVOEZvUd51NT/a3Rp2dprVjI9p43m4BRUbHi14Ls5WJrbjiVImPsVCUGD4vLwv5KivNUlruYxBJklnVqASv/Ql2eMYs+QjkW2FF561ojrhWBbkZo+foLp7Dks6zaDFn2bjnFO0QQoD20LdUWuJc38kL+k6tcTaieNizW1FzvFVFDY8NWnaPY7k9nth2Ty5DtIdwMs2WuHrWIgd01SI/FkGZnVjdnmHMrGMNaJeiLJi64khor68iqTH+5C+3Eq48zfcsrsA8Qpe3GDEMHA1aDadhOj+wM1jFvjDQNQR4UQrgVEcS8HhoQECjJv3p/n6zpqSUEHwgoWt3MCZaOButo4qsSUf00/oFCrSaKugMwZsIZPzLilaIvyDYEyVUTDeZmnFRCri9Bnylj/uD+N2EPm2YZnsePp/ORv3FIHlNMl6kOQXmZMKsZMGQcCLc8Xxf9nSaiZzYD1jRgcytPBP0ROfN/rG3EI/1lG+ZCnax9oadtpEbEGjUvja70YRE14iVwR8QIRFVpqJVZTCMcmuFpMFfC2CKcYQORBygs+6bnobAli9qIzIoXvbk2gYI5X2WhkZHRwIrOXwk3fW9nFKjCXVpyYSFSdOrkRQdAT5u+6eEIaSD47GmIHoaDDlHH1RF6BusVsCqvfAfG8qIYJNes2q/c5nheCmBThdWjl4MKwxPH7K306MaekAKFPJAwKhBTES9nZrsseQLQ9v8WNGTZyBwJucEHMCol+Vk3lf+PpKEaD6G8TT7n36V43XJ/N09APgDcGxGB4rAAeinCbANyaYOQtZ0jb+5Jb/NKQ2grdA9KoEvafLE09J4VSloQPQOCCbIwhrvwZO0guWaEjXbiN4UPzSOnyQK7lZfFNmAIgjZtAqzIL8yeGes0I/CCI4CiRKz+pFh313WLtbKi3acqO7GrlFH9g652bkeITPg06fhkqSVjf7iHv+ZpZYXWz+K0FiTUaCinPzNKOCWbYrqNcWaM1Y6bR/uoUJkSUMoODHZ3csWhOz7VqUVZc9M4U6Qg0+0wck3w+ZbdEyVSlWnAPXkphg4UYMrMrUFUzHYSjORTdXoLYMveoIbWMhubtugl0DqD8hOEWqaGYYlJo2N2WU54mYEIaoZ8wfpWsMVOfPFyi5j754lngonq5vf36inXn3xRO5CkYFrzXKJ3n2DYiSrVV0ll/5WTkR3F/lEby4CP81UkVubm4GrvH7fBnhQuWgV9GlZbZhaCWl6FC1dnabn+sNwvh3iEP/2oWqi2013gtQQlSSFE5mCg+pCr6zFEAUTNHBqQZrXyMdIJ9tNimbX551HE+bKp5Eog1wHWP1k3orEjQUwm+R";

#if defined(_WIN32) || defined(_WIN64)
static WString output_path = WString::FromLocal("../output_files/");
static WString input_path = WString::FromLocal("../input_files/fulltextsearch/");
#else
static WString output_path = WString::FromLocal("./output_files/");
static WString input_path = WString::FromLocal("./input_files/fulltextsearch/");
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

  void Write(const char* text_content);
  void Write(const wchar_t* text_content);

 private:
  FILE* file_;
};

TextDoc::TextDoc(const String& file_name, const String& file_mode) throw(Exception)
    : file_(NULL) {
#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, file_name, (const char*)file_mode);
#else
  file_ = fopen((const char*)file_name, (const char*)file_mode);
#endif

  if (!file_)
    throw Exception(__FILE__, __LINE__, __FUNCTION__, foxit::e_ErrFile);

  uint8 temp[] = {0xFF, 0xFE};
  fwrite(temp, sizeof(uint8), 2, file_);
  fseek(file_, 0, SEEK_END);
}

TextDoc::TextDoc(const WString& file_name, const WString& file_mode) throw(Exception)
    : file_(NULL) {
  String s_file_name = String::FromUnicode(file_name);
  String s_file_mode = String::FromUnicode(file_mode);

#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, (const char*)s_file_name, (const char*)s_file_mode);
#else
  file_ = fopen((const char*)s_file_name, (const char*)s_file_mode);
#endif
  if (!file_)
    throw Exception(__FILE__, __LINE__, __FUNCTION__, foxit::e_ErrFile);

  uint8 temp[] = {0xFF, 0xFE};
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
  if (wide_str.IsEmpty())
    return;
  String utf16le_str = wide_str.UTF16LE_Encode(false);
  if (utf16le_str.IsEmpty())
    return;
  int length = utf16le_str.GetLength();
  fwrite((const char*)utf16le_str, sizeof(char), length, file_);
}

class SearchCallbackImp:public SearchCallback
{
public:
  SearchCallbackImp(const WString& output_txt_file_path)
    : text_doc_(output_txt_file_path, L"w+b") {
  }

  virtual void Release() {delete this;}
  virtual int RetrieveSearchResult(const wchar_t* filePath, int pageIndex, const WString& matchResult, int matchStartTextIndex, int matchEndTextIndex, const WString& sentence, int sentenceStartTextIndex, int sentenceEndTextIndex);

private:
  TextDoc text_doc_;
};

int SearchCallbackImp::RetrieveSearchResult(const wchar_t* filePath, int pageIndex, const WString& matchResult, int matchStartTextIndex, int matchEndTextIndex, const WString& sentence, int sentenceStartTextIndex, int sentenceEndTextIndex) {
  String result_str;
  result_str.Format("RetrieveSearchResult:\nFound file is: %ls\nPage index is: %d\nStart text index: %d\nEnd text index: %d\nMatch is: %ls\nSentence start index:%d\nSentence end index:%d\nSentence is: %ls\n", filePath, pageIndex, matchStartTextIndex, matchEndTextIndex, (const wchar_t*)matchResult, sentenceStartTextIndex, sentenceEndTextIndex, (const wchar_t*)sentence);
  text_doc_.Write((FX_LPCSTR)result_str);
  text_doc_.Write("\r\n");

  return 0;
}

class Search_Pause : public PauseCallback
{
public:
  Search_Pause(int pause_count_limit = 0, bool always_pause = false)
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
  WString output_directory = output_path + L"fulltextsearch/";
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
  try
  {
    FullTextSearch full_text_search;
    //The path of data base to store the indexed data...
    String dbPath = String::FromUnicode(output_directory) + "search.db";
    full_text_search.SetDataBasePath(dbPath);
    // Get document source information.
    DocumentsSource docs_source(String::FromUnicode(input_path));
    // Create a Pause callback object implemented by users to pause the updating process.
    Search_Pause pause(5);
    Progressive search_progress = full_text_search.StartUpdateIndex(docs_source, &pause, false);
    int state = Progressive::e_ToBeContinued;
    while(state == Progressive::e_ToBeContinued)
    {
      state = search_progress.Continue();
    }
    // Create a callback object which will be invoked when a matched one is found.
    SearchCallbackImp* searchCallback = new SearchCallbackImp(output_directory + L"result.txt");
    // Search the specified keyword from the indexed data source.
    full_text_search.SearchOf("Foxit", FullTextSearch::e_RankHitCountASC, searchCallback);

	cout << "FullTextSearch demo." << endl;
  }
   catch(...)
  {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}