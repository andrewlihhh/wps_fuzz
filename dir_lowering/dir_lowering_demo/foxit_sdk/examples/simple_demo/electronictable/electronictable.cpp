
// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to add table to PDF document.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#include <map>

#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/annots/fs_annot.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/addon/tablegenerator/fs_tablegenerator.h"

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

WString DateTimeToString(const DateTime& datetime) {
  WString ws_datetime;
  ws_datetime.Format((FX_LPCWSTR)L"%d/%d/%d-%d:%d:%d %s%d:%d", datetime.year, datetime.month, datetime.day, datetime.hour,
    datetime.minute, datetime.second, datetime.utc_hour_offset > 0 ? L"+" : L"-", datetime.utc_hour_offset,
    datetime.utc_minute_offset);
  return ws_datetime;
}


foxit::pdf::RichTextStyle GetTableTextStyle(int index) {
  foxit::pdf::RichTextStyle style = foxit::pdf::RichTextStyle();
  style.font = common::Font(common::Font::e_StdIDHelvetica);
  style.text_size = 10;
  style.text_alignment = common::Alignment::e_AlignmentLeft;
  style.text_color = 0x000000;
  style.is_bold = false;
  style.is_italic = false;
  style.is_underline = false;
  style.is_strikethrough = false;
  style.mark_style = foxit::pdf::RichTextStyle::CornerMarkStyle::e_CornerMarkNone;

  switch (index) {
  case 1:
    style.text_alignment = common::Alignment::e_AlignmentCenter;
    break;
  case 2: {
    style.text_alignment = common::Alignment::e_AlignmentRight;
    style.text_color = 0x00FF00;
    break;
  }
  case 3:
    style.text_size = 15;
    break;
  case 4: {
#if defined(__linux__)
    style.font = Font(L"FreeSerif", 0, Font::e_CharsetANSI, 0);
#else
    style.font = common::Font(L"Times New Roman", 0, Font::e_CharsetANSI, 0);
#endif
    style.text_color = 0xFF0000;
    style.text_alignment = common::Alignment::e_AlignmentRight;
    break;
  }
  case 5: {
#if defined(__linux__)
    style.font = Font(L"FreeSerif", 0, Font::e_CharsetANSI, 0);
#else
    style.font = common::Font(L"Times New Roman", 0, Font::e_CharsetANSI, 0);
#endif
    style.is_bold = true;
    style.text_alignment = common::Alignment::e_AlignmentRight;
    break;
  }
  case 6: {
    style.is_bold = true;
    style.is_italic = true;
    break;
  }
  case 7: {
    style.is_bold = true;
    style.is_italic = true;
    style.text_alignment = common::Alignment::e_AlignmentCenter;
    break;
  }
  case 8: {
    style.is_underline = true;
    style.text_alignment = common::Alignment::e_AlignmentRight;
    break;
  }
  case 9:
    style.is_strikethrough = true;
    break;
  case 10:
    style.mark_style = foxit::pdf::RichTextStyle::CornerMarkStyle::e_CornerMarkSubscript;
    break;
  case 11:
    style.mark_style = foxit::pdf::RichTextStyle::CornerMarkStyle::e_CornerMarkSuperscript;
    break;
  default:
    break;
  }
  return style;
}

WString GetTableCellText(int index) {
  WString cell_text = L"";
  switch (index) {
  case 0:
    cell_text = L"Reference style";
    break;
  case 1:
    cell_text = L"Alignment center";
    break;
  case 2:
    cell_text = L"Green text color and alignment right";
    break;
  case 3:
    cell_text = L"Text font size 15";
    break;
  case 4: {
#if defined(__linux__)
    cell_text = L"Red text color, FreeSerif font and alignment right";
#else
    cell_text = L"Red text color, Times New Roman font and alignment right";
#endif
    break;
  }
  case 5: {
#if defined(__linux__)
    cell_text = L"Bold, FreeSerif font and alignment right";
#else
    cell_text = L"Bold, Times New Roman font and alignment right";
#endif
    break;
  }
  case 6:
    cell_text = L"Bold and italic";
    break;
  case 7:
    cell_text = L"Bold, italic and alignment center";
    break;
  case 8:
    cell_text = L"Underline and alignment right";
    break;
  case 9:
    cell_text = L"Strikethrough";
    break;
  case 10:
    cell_text = L"CornerMarkSubscript";
    break;
  case 11:
    cell_text = L"CornerMarkSuperscript";
    break;
  default:
    cell_text = L" ";
    break;
  }

  return cell_text;
}

void AddElectronicTable(PDFPage &page) {

  // Add a spreadsheet with 4 rows and 3 columns
  {
    int index = 0;
    foxit::addon::tablegenerator::TableCellDataArray cell_array;
    
    for (int row = 0; row < 4; row++) {
      foxit::addon::tablegenerator::TableCellDataColArray col_array;
      for (int col = 0; col < 3; col++) {
        foxit::pdf::RichTextStyle style = GetTableTextStyle(index);
        WString cell_text = GetTableCellText(index++);
        foxit::addon::tablegenerator::TableCellData cell_data(style, 0xFFFFFFFF, cell_text, foxit::common::Image((FS_HANDLE)NULL), RectF());
        col_array.Add(cell_data);
      }
      cell_array.Add(col_array);
    }
    FX_FLOAT page_width = page.GetWidth();
    FX_FLOAT page_height = page.GetHeight();
 
    foxit::addon::tablegenerator::TableBorderInfo outside_border_left;
    outside_border_left.line_width = 1;
    foxit::addon::tablegenerator::TableBorderInfo outside_border_right;
    outside_border_right.line_width = 1;
    foxit::addon::tablegenerator::TableBorderInfo outside_border_top;
    outside_border_top.line_width = 1;
    foxit::addon::tablegenerator::TableBorderInfo outside_border_bottom;
    outside_border_bottom.line_width = 1;
    foxit::addon::tablegenerator::TableBorderInfo inside_border_row;
    inside_border_row.line_width = 1;
    foxit::addon::tablegenerator::TableBorderInfo inside_border_col;
    inside_border_col.line_width = 1;
    foxit::addon::tablegenerator::TableData data(RectF(100, 550, page_width - 100, page_height - 100), 4, 3, outside_border_left, outside_border_right, outside_border_top, outside_border_bottom, inside_border_row, inside_border_col, foxit::addon::tablegenerator::TableCellIndexArray(), FloatArray(), FloatArray());
    foxit::addon::tablegenerator::TableGenerator::AddTableToPage(page, data, cell_array);
  }

  //Add a spreadsheet with 5 rows and 6 columns
  {
    foxit::addon::tablegenerator::TableCellDataArray cell_array;
    WString cell_text = L" ";
    for (int row = 0; row < 5; row++) {
      foxit::addon::tablegenerator::TableCellDataColArray col_array;
      for (int col = 0; col < 6; col++) {
        foxit::pdf::RichTextStyle style = GetTableTextStyle(row);
        switch (col) {
        case 0:
          cell_text.Format(L"First column");
          break;
        case 1:
          cell_text.Format(L"Second column");
          break;
        case 2:
          cell_text.Format(L"Third column");
          break;
        case 3:
          cell_text.Format(L"Fourth column");
          break;
        case 4:
          cell_text.Format(L"Fifth column");
          break;
        case 5:
          cell_text = DateTimeToString(GetLocalDateTime());
          break;
        default:
          cell_text = L" ";
          break;
        }
        foxit::addon::tablegenerator::TableCellData cell_data(style, 0xFFFFFFFF, cell_text, foxit::common::Image((FS_HANDLE)NULL), RectF());
        col_array.Add(cell_data);
      }
      cell_array.Add(col_array);
    }

    FX_FLOAT page_width = page.GetWidth();
    FX_FLOAT page_height = page.GetHeight();
    foxit::addon::tablegenerator::TableBorderInfo outside_border_left;
    outside_border_left.line_width = 2;
    foxit::addon::tablegenerator::TableBorderInfo outside_border_right;
    outside_border_right.line_width = 2;
    foxit::addon::tablegenerator::TableBorderInfo outside_border_top;
    outside_border_top.line_width = 2;
    foxit::addon::tablegenerator::TableBorderInfo outside_border_bottom;
    outside_border_bottom.line_width = 2;

    foxit::addon::tablegenerator::TableBorderInfo inside_border_row;
    inside_border_row.line_width = 2;
    foxit::addon::tablegenerator::TableBorderInfo inside_border_col;
    inside_border_col.line_width = 2;
    foxit::addon::tablegenerator::TableData data(RectF(10, 200, page_width - 10, page_height - 350), 5, 6, outside_border_left, outside_border_right, outside_border_top, outside_border_bottom, inside_border_row, inside_border_col, foxit::addon::tablegenerator::TableCellIndexArray(), FloatArray(), FloatArray());
    foxit::addon::tablegenerator::TableGenerator::AddTableToPage(page, data, cell_array);
  }
}


int main(int argc, char *argv[]) {
  int err_ret = 0;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    WString output_directory = output_path + L"electronictable/";
#if defined(_WIN32) || defined(_WIN64)
    _mkdir(String::FromUnicode(output_directory));
#else
    mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

    PDFDoc doc = PDFDoc();
    PDFPage page = doc.InsertPage(0);
    AddElectronicTable(page);
    // Save PDF file
    WString new_pdf = output_directory + L"electronictable_result.pdf";
    doc.SaveAs(new_pdf, PDFDoc::e_SaveFlagNoOriginal);
    std::cout << "electronictable demo." << std::endl;
  }
  catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }

  return err_ret;
}
