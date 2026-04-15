// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to add watermarks (in different types)
// into PDF files.

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
#include "../../../include/pdf/fs_watermark.h"

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

void AddTextWatermark(PDFDoc doc, PDFPage page) {
  WatermarkSettings settings;
  settings.flags = WatermarkSettings::e_FlagASPageContents | WatermarkSettings::e_FlagOnTop;
  settings.offset_x = 0;
  settings.offset_y = 0;
  settings.opacity = 90;
  settings.position = common::e_PosTopRight;
  settings.rotation = -45.f;
  settings.scale_x = 1.f;
  settings.scale_y = 1.f;

  WatermarkTextProperties text_properties;
  text_properties.alignment = CommonDefines::e_AlignmentCenter;
  text_properties.color = 0xF68C21;
  text_properties.font_style = WatermarkTextProperties::e_FontStyleNormal;
  text_properties.line_space = 1;
  text_properties.font_size = 12.f;
  text_properties.font = Font(Font::e_StdIDTimesB);

  Watermark watermark(doc, L"Foxit PDF SDK\nwww.foxitsoftware.com", text_properties, settings);
  watermark.InsertToPage(page);

}

void AddBitmapWatermark(PDFDoc doc, PDFPage page, WString bitmap_file) {
  WatermarkSettings settings;
  settings.flags = WatermarkSettings::e_FlagASPageContents | WatermarkSettings::e_FlagOnTop;
  settings.offset_x = 0.f;
  settings.offset_y = 0.f;
  settings.opacity = 60;
  settings.position = common::e_PosCenterLeft;
  settings.rotation = 90.f;

  Image image(bitmap_file);
  Bitmap bitmap = image.GetFrameBitmap(0);
  settings.scale_x = page.GetHeight() * 1.0f / bitmap.GetWidth();
  settings.scale_y = settings.scale_x;
  Watermark watermark(doc, bitmap, settings);
  watermark.InsertToPage(page);
}

void AddImageWatermark(PDFDoc doc, PDFPage page, WString image_file) {
  WatermarkSettings settings;
  settings.flags = WatermarkSettings::e_FlagASPageContents | WatermarkSettings::e_FlagOnTop;
  settings.offset_x = 0.f;
  settings.offset_y = 0.f;
  settings.opacity = 20;
  settings.position = common::e_PosCenter;
  settings.rotation = 0.0f;

  Image image(image_file);
  Bitmap bitmap = image.GetFrameBitmap(0);
  settings.scale_x = page.GetWidth() * 0.618f / bitmap.GetWidth();
  settings.scale_y = settings.scale_x;

  Watermark watermark(doc, image, 0, settings);
  watermark.InsertToPage(page);
}

void AddSingleWatermark(PDFDoc doc, PDFPage page) {
  WatermarkSettings settings;
  settings.flags = WatermarkSettings::e_FlagASPageContents|WatermarkSettings::e_FlagOnTop;
  settings.offset_x = 0.f;
  settings.offset_y = 0.f;
  settings.opacity = 90;
  settings.position = common::e_PosBottomRight;
  settings.rotation = 0.0f;
  settings.scale_x = 0.1f;
  settings.scale_y = 0.1f;

  Watermark watermark(doc, page, settings);
  watermark.InsertToPage(page);
}

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"watermark/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file = input_path + L"AboutFoxit.pdf";
  WString output_file = output_directory + L"watermark_add.pdf";
  WString output_remove_file = output_directory + L"watermark_remove.pdf";
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
    int page_count = doc.GetPageCount();
    for(int i=0; i<page_count; i++)
    {
      PDFPage page = doc.GetPage(i);
      page.StartParse(PDFPage::e_ParsePageNormal, NULL, false);

      AddTextWatermark(doc, page);
      WString wm_bmp = input_path + L"watermark.bmp";
      AddBitmapWatermark(doc, page,wm_bmp );
      WString wm_image = input_path + L"sdk.png";
      AddImageWatermark(doc, page, wm_image);
      AddSingleWatermark(doc, page);
    }

    doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);
    cout << "Add watermarks to PDF file." << endl;

    int nCount = doc.GetPageCount();
    for (int i = 0; i < nCount; i++)
    {
      PDFPage page = doc.GetPage(i);
      page.StartParse(PDFPage::e_ParsePageNormal, NULL, false);
      if (page.HasWatermark()) {
        page.RemoveAllWatermarks();
      }
    }

    doc.SaveAs(output_remove_file, PDFDoc::e_SaveFlagNoOriginal);
    cout << "Remove watermarks from PDF file." << endl;

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
