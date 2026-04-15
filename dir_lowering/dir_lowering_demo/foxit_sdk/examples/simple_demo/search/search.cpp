// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to search text in all pages in PDF document.

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
#include "../../../include/pdf/fs_search.h"

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

class TextOutput{
public:
  TextOutput(const String& file_name, const String& fill_mode);
  TextOutput(const WString& file_name, const WString& fill_mode);
  TextOutput() : file_(NULL){};
  ~TextOutput();

  void Write(const char* format);
  void Write(const wchar_t* text_content);

private:
  FILE* file_;
};

TextOutput::TextOutput(const String& file_name, const String& file_mode) throw(Exception) : file_(NULL) {
#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, file_name, (const char*)file_mode);
#else
  file_ = fopen((const char*)file_name, (const char*)file_mode);
#endif

  if (!file_)
    throw Exception(__FILE__, __LINE__, __FUNCTION__, foxit::e_ErrFile);

  uint8 temp[] = { 0xFF, 0xFE };
  fwrite(temp, sizeof(uint8), 2, file_);
  fseek(file_, 0, SEEK_END);
}

TextOutput::TextOutput(const WString& file_name, const WString& file_mode) throw(Exception)  : file_(NULL) {
  String s_file_name = String::FromUnicode(file_name);
  String s_file_mode = String::FromUnicode(file_mode);

#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, (const char*)s_file_name, (const char*)s_file_mode);
#else
  file_ = fopen((const char*)s_file_name, (const char*)s_file_mode);
#endif
  if (!file_)
    throw Exception(__FILE__, __LINE__, __FUNCTION__, foxit::e_ErrFile);

  uint8 temp[] = { 0xFF, 0xFE };
  fwrite(temp, sizeof(uint8), 2, file_);
  fseek(file_, 0, SEEK_END);
}

TextOutput::~TextOutput() {
  if(file_)
    fclose(file_);
  file_ = NULL;
}

void TextOutput::Write(const char* text_content) {
  WString wide_str = WString::FromLocal(text_content);
  Write((FX_LPCWSTR)wide_str);
}

void TextOutput::Write(const wchar_t* text_content) {
  WString wide_str(text_content);
  if (wide_str.IsEmpty())
    return;
  String utf16le_str = wide_str.UTF16LE_Encode(false);
  if (utf16le_str.IsEmpty())
    return;
  wcout << (FX_LPCWSTR)wide_str;
  int length = utf16le_str.GetLength();
  fwrite((const char*)utf16le_str, sizeof(char), length, file_);
}

void OutputMatchedInfo(TextOutput& text_out, TextSearch search, int matched_index) {
  int page_index = search.GetMatchPageIndex();
  WString format_str = L"";
  format_str.Format(L"Index of matched pattern:\t%d\r\n", matched_index);
  text_out.Write((FX_LPCWSTR)format_str);
  format_str.Format(L"\tpage:\t%d\r\n", page_index);
  text_out.Write((FX_LPCWSTR)format_str);
  format_str.Format(L"\tmatch char start index:\t%d\r\n", search.GetMatchStartCharIndex());
  text_out.Write((FX_LPCWSTR)format_str);
  format_str.Format(L"\tmatch char end index:\t%d\r\n", search.GetMatchEndCharIndex());
  text_out.Write((FX_LPCWSTR)format_str);
  format_str.Format(L"\tmatch sentence start index:\t%d\r\n", search.GetMatchSentenceStartIndex());
  text_out.Write((FX_LPCWSTR)format_str);
  format_str = L"\tmatch sentence:\t";
  format_str += search.GetMatchSentence();
  format_str += L"\r\n";
  text_out.Write((FX_LPCWSTR)format_str);
  RectFArray rect_array = search.GetMatchRects();
  int rect_count = rect_array.GetSize();
  format_str.Format(L"\tmatch rectangles count:\t%d\r\n", rect_count);
  text_out.Write((FX_LPCWSTR)format_str);
  for (int i = 0; i < rect_count; i++) {
    foxit::RectF rect = rect_array[i];
    format_str.Format(L"\trectangle(in PDF space) :%d\t[left = %.4f, bottom = %.4f, right = %.4f, top = %.4f]\r\n", i,
      rect.left, rect.bottom, rect.right, rect.top);
    text_out.Write((FX_LPCWSTR)format_str);
  }
}

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"search/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file = input_path + L"AboutFoxit.pdf";
  WString output_file = output_directory + L"search.txt";
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
    TextOutput text_out(output_file, L"wb+");

    // sample 1: search for all pages of doc.
    TextSearch search(doc, NULL);

    int start_index = 0, end_index = doc.GetPageCount() - 1;
    search.SetStartPage(0);
    search.SetEndPage(doc.GetPageCount() - 1);

    WString pattern = L"Foxit";
    search.SetPattern(pattern);

    foxit::uint32 flags = TextSearch::e_SearchNormal;
    // If want to specify flags, you can do as followings:
    // flags |= TextSearch::e_SearchMatchCase;
    // flags |= TextSearch::e_SearchMatchWholeWord;
    // flags |= TextSearch::e_SearchConsecutive;
    search.SetSearchFlags(flags);
    WString format_str = L"";
    format_str = L"Begin search ";
    format_str += pattern;
    format_str += L" at ";
    format_str += input_file;
    format_str += L".\n";
    text_out.Write((FX_LPCWSTR)format_str);
    format_str.Format(L"Start index:\t%d\r\n", start_index);
    text_out.Write((FX_LPCWSTR)format_str);
    format_str.Format(L"End index:\t%d\r\n", end_index);
    text_out.Write((FX_LPCWSTR)format_str);
    format_str = L"Match key:\t";
    format_str += pattern;
    format_str += L"\r\n";
    text_out.Write((FX_LPCWSTR)format_str);
    WString match_case = flags & TextSearch::e_SearchMatchCase ? L"Yes" : L"No";
    format_str = L"Match Case\t";
    format_str += match_case;
    format_str += L"\r\n";
    text_out.Write((FX_LPCWSTR)format_str);
    WString match_whole_word = flags & TextSearch::e_SearchMatchWholeWord ? L"Yes" : L"No";
    format_str = L"Match whole word:\t";
    format_str += match_whole_word;
    format_str += L"\r\n";
    text_out.Write((FX_LPCWSTR)format_str);
    WString match_consecutive = flags & TextSearch::e_SearchConsecutive ? L"Yes" : L"No";
    format_str = L"Consecutive:\t";
    format_str += match_consecutive;
    format_str += L"\r\n";
    text_out.Write((FX_LPCWSTR)format_str);
    int match_count = 0;
    while (search.FindNext()) {
      RectFArray rect_array = search.GetMatchRects();
      OutputMatchedInfo(text_out, search, match_count);
      match_count ++;
    }
    wcout << L"Marched " << match_count << L" counts." << endl;
    // end of sample 1.

    wcout << L"Search demo finished." << endl;

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

