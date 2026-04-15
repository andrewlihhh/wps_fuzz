// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to compare pdf page with the other.

#include <time.h>
#include <math.h>
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
#include "../../../include/addon/comparison/fs_compare.h"
#include "../../../include/common/fxcrt/fx_basic.h"

using namespace std;
using namespace foxit;
using namespace common;
using namespace addon;
using foxit::common::Library;
using namespace pdf;
using namespace foxit::pdf::annots;
using namespace foxit::addon::comparison;

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

DateTime GetLocalDateTime() {
  time_t t = time(NULL);
#if (WINAPI_PARTITION_APP || WINAPI_PARTITION_PC_APP) || \
  (defined(_WIN32) || defined(_WIN64)) && _FX_COMPILER_ != _FX_VC6_
  struct tm _Tm;
  localtime_s(&_Tm, &t);
  struct tm* rime = &_Tm;
  _tzset();
  long time_zone = NULL;
  _get_timezone(&time_zone);
  int timezone_hour = time_zone / 3600 * -1;
  int timezone_minute = (abs(time_zone) % 3600) / 60;
#elif defined(__linux__)
  struct tm* rime = localtime(&t);
  tzset();
  int timezone_hour = __timezone / 3600 * -1;
  int timezone_minute = ((int)abs(__timezone) % 3600) / 60;
#elif defined(__APPLE__)
  struct tm* rime = localtime(&t);
  tzset();
  int timezone_hour = timezone / 3600 * -1;
  int timezone_minute = ((int)abs(timezone) % 3600) / 60;
#endif
  DateTime datetime;
  datetime.year = static_cast<uint16>(rime->tm_year + 1900);
  datetime.month = static_cast<uint16>(rime->tm_mon + 1);
  datetime.day = static_cast<uint16>(rime->tm_mday);
  datetime.hour = static_cast<uint16>(rime->tm_hour);
  datetime.minute = static_cast<uint16>(rime->tm_min);
  datetime.second = static_cast<uint16>(rime->tm_sec);
  datetime.utc_hour_offset = timezone_hour;
  datetime.utc_minute_offset = timezone_minute;

  return datetime;
}

String RandomUID() {
  String uuid;
  const char* c = "0123456789qwertyuiopasdfghjklzxcvbnm";

  for (int n = 0; n < 16; n++) {
    String uuid_temp;
    int b = rand() % 255;
    switch (n) {
      case 6:
        uuid_temp.Format("4%x", b % 15);
      break;
      case 8:
        uuid_temp.Format("%c%x", c[rand() % strlen(c)], b % 15);
      break;
      default:
        uuid_temp.Format("%02x", b);
      break;
    }
    uuid += uuid_temp;

    switch (n) {
      case 3:
      case 5:
      case 7:
      case 9:
        uuid += '-';
      break;
    }
  }
  return uuid;
}

void CreateInsertStamp(PDFPage page, RectFArray rects, RGB color, WString ws_contents, WString ws_type, WString ws_obj_type) {
  RectF rect_stamp;
  int rect_size = rects.GetSize();
  if (rect_size > 0) {
    RectF item = rects.GetAt(0);
    rect_stamp.left = item.left;
    rect_stamp.top = item.top-4 ;
    rect_stamp.right = rect_stamp.left + 4;
    rect_stamp.bottom = rect_stamp.top - 8;
  }

  Image image = Image(input_path + L"pdfcompare/insert_stamp.png");

  annots::Stamp stamp(page.AddAnnot(Annot::e_Stamp, rect_stamp));
  stamp.SetContent(ws_contents);
  stamp.SetBorderColor(color);
  stamp.SetSubject(ws_obj_type);
  stamp.SetTitle(ws_type);
  stamp.SetCreationDateTime(GetLocalDateTime());
  stamp.SetModifiedDateTime(GetLocalDateTime());
  stamp.SetUniqueID(WString::FromLocal(RandomUID()));
  stamp.SetImage(image, 0, 0);

  stamp.ResetAppearanceStream();
}

void CreateSquigglyRect(PDFPage page, RectFArray rects, RGB color, WString ws_contents, WString ws_type, WString ws_obj_type) {
  annots::Squiggly squiggly(page.AddAnnot(Annot::e_Squiggly, RectF()));
  squiggly.SetContent(ws_contents);

  annots::QuadPointsArray quad_points_array;
  int rect_size = rects.GetSize();
  for (int i=0; i<rect_size; i++) {
    CFX_FloatRect item = rects.GetAt(i);
    annots::QuadPoints quad_points;
    quad_points.first = PointF(item.left, item.top);
    quad_points.second = PointF(item.right, item.top);
    quad_points.third = PointF(item.left, item.bottom);
    quad_points.fourth = PointF(item.right, item.bottom);
    quad_points_array.Add(quad_points);
  }
  squiggly.SetQuadPoints(quad_points_array);

  squiggly.SetBorderColor(color);
  squiggly.SetSubject(ws_obj_type);
  squiggly.SetTitle(ws_type);
  squiggly.SetCreationDateTime(GetLocalDateTime());
  squiggly.SetModifiedDateTime(GetLocalDateTime());
  squiggly.SetUniqueID(WString::FromLocal(RandomUID()));

  squiggly.ResetAppearanceStream();
}

void CreateDeleteTextStamp(PDFPage page, RectFArray rects, RGB color, WString ws_contents, WString ws_type, WString ws_obj_type) {
  RectF rect_stamp;
  int rect_size = rects.GetSize();
  if (rect_size > 0) {
    RectF item = rects.GetAt(0);
    rect_stamp.left = item.left;
    rect_stamp.top = item.top + 12;
    rect_stamp.right = rect_stamp.left + 9;
    rect_stamp.bottom = rect_stamp.top - 12;
  }

  Image image = Image(input_path + L"pdfcompare/delete_stamp.png");

  annots::Stamp stamp(page.AddAnnot(Annot::e_Stamp, rect_stamp));
  stamp.SetContent(ws_contents);
  stamp.SetBorderColor(color);
  stamp.SetSubject(ws_obj_type);
  stamp.SetTitle(ws_type);
  stamp.SetCreationDateTime(GetLocalDateTime());
  stamp.SetModifiedDateTime(GetLocalDateTime());
  stamp.SetUniqueID(WString::FromLocal(RandomUID()));
  stamp.SetImage(image, 0, 0);

  stamp.ResetAppearanceStream();
}

void CreateDeleteText(PDFPage page, RectFArray rects, RGB color, WString ws_contents, WString ws_type, WString ws_obj_type) {
  annots::StrikeOut strikeout(page.AddAnnot(Annot::e_StrikeOut, RectF()));
  strikeout.SetContent(ws_contents);

  annots::QuadPointsArray quad_points_array;
  int rect_size = rects.GetSize();
  for (int i = 0; i<rect_size; i++) {
    CFX_FloatRect item = rects.GetAt(i);
    annots::QuadPoints quad_points;
    quad_points.first = PointF(item.left, item.top);
    quad_points.second = PointF(item.right, item.top);
    quad_points.third = PointF(item.left, item.bottom);
    quad_points.fourth = PointF(item.right, item.bottom);
    quad_points_array.Add(quad_points);
  }
  strikeout.SetQuadPoints(quad_points_array);

  strikeout.SetBorderColor(color);
  strikeout.SetSubject(ws_obj_type);
  strikeout.SetTitle(ws_type);
  strikeout.SetCreationDateTime(GetLocalDateTime());
  strikeout.SetModifiedDateTime(GetLocalDateTime());
  strikeout.SetUniqueID(WString::FromLocal(RandomUID()));

  strikeout.ResetAppearanceStream();
}

WString output_directory = output_path + L"pdfcompare/";

int main(int argc, char *argv[]) {
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_base_file = input_path + L"pdfcompare/test_base.pdf";
  WString input_compared_file = input_path + L"pdfcompare/test_compared.pdf";
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  if(sdk_lib_mgr.Initialize() != foxit::e_ErrSuccess) {
  return 1;
  }

  try {
    PDFDoc base_doc(input_base_file);
    ErrorCode error_code = base_doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_base_file), error_code);
      return 1;
    }

    PDFDoc compared_doc(input_compared_file);
    error_code = compared_doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_compared_file), error_code);
      return 1;
    }

    Comparison comparison(base_doc, compared_doc);
    CompareResults result = comparison.DoCompare(0, 0, Comparison::e_CompareTypeText);
    CompareResultInfoArray& old_info = result.base_doc_results;
    CompareResultInfoArray& new_info = result.compared_doc_results;
    int old_info_size = old_info.GetSize();
    int new_info_size = new_info.GetSize();
    PDFPage page_base = base_doc.GetPage(0);
    PDFPage page = compared_doc.GetPage(0);
    for (int i = 0; i < old_info_size; i++) {
      const CompareResultInfo& item = old_info.GetAt(i);
      CompareResultInfo::CompareResultType type = item.type;
      if (type == CompareResultInfo::e_CompareResultTypeDeleteText) {
        String res_string;
        res_string.Format((FX_LPCSTR)"\"%s\"", (FX_LPCSTR)String::FromUnicode(item.diff_contents));
        CreateDeleteText(page_base, item.rect_array, 0xff0000, WString::FromLocal(res_string), L"Compare : Delete", L"Text");
      } else if (type == CompareResultInfo::e_CompareResultTypeInsertText) {
        String res_string;
        res_string.Format((FX_LPCSTR)"\"%s\"", (FX_LPCSTR)String::FromUnicode(item.diff_contents));
        CreateInsertStamp(page_base, item.rect_array, 0x0000ff, WString::FromLocal(res_string), L"Compare : Insert", L"Text");
      } else if (type == CompareResultInfo::e_CompareResultTypeReplaceText) {
        String res_string;
        res_string.Format("[New]: \"%s\"\r\n[Old]: \"%s\"", (FX_LPCSTR)String::FromUnicode(new_info.GetAt(i).diff_contents), (FX_LPCSTR)String::FromUnicode(item.diff_contents));
        CreateSquigglyRect(page_base, item.rect_array, 0xe7651a, WString::FromLocal(res_string), L"Compare : Replace", L"Text");
      }
    }
    for (int i=0; i<new_info_size; i++) {
      const CompareResultInfo& item = new_info.GetAt(i);
      CompareResultInfo::CompareResultType type = item.type;
      if (type == CompareResultInfo::e_CompareResultTypeDeleteText) {
        String res_string;
        res_string.Format((FX_LPCSTR)"\"%s\"", (FX_LPCSTR)String::FromUnicode(item.diff_contents));
        CreateDeleteTextStamp(page, item.rect_array, 0xff0000, WString::FromLocal(res_string), L"Compare : Delete", L"Text");
      } else if (type == CompareResultInfo::e_CompareResultTypeInsertText) {
        String res_string;
        res_string.Format((FX_LPCSTR)"\"%s\"", (FX_LPCSTR)String::FromUnicode(item.diff_contents));
        CreateDeleteText(page, item.rect_array, 0x0000ff, WString::FromLocal(res_string), L"Compare : Insert", L"Text");
      } else if (type == CompareResultInfo::e_CompareResultTypeReplaceText) {
        String res_string;
        res_string.Format("[Old]: \"%s\"\r\n[New]: \"%s\"", (FX_LPCSTR)String::FromUnicode(old_info.GetAt(i).diff_contents), (FX_LPCSTR)String::FromUnicode(item.diff_contents));
        CreateSquigglyRect(page, item.rect_array, 0xe7651a, WString::FromLocal(res_string), L"Compare : Replace", L"Text");
      }
    }
    base_doc.SaveAs(output_directory + L"old.pdf");
    compared_doc.SaveAs(output_directory + L"new.pdf");

    PDFDoc new_doc = comparison.GenerateComparedDoc(Comparison::e_CompareTypeAll);
    new_doc.SaveAs(output_directory + L"generate_result.pdf", PDFDoc::e_SaveFlagNormal);

    cout << "Pdf compare test." << endl;
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }
  catch(...) {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}

