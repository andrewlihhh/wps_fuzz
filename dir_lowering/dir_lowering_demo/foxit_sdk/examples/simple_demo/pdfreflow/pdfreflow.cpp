// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to reflow PDF pages.

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
#include "../../../include/pdf/fs_reflowpage.h"
#include "../../../include/common/fs_render.h"

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

WString output_directory = output_path + L"pdfreflow/";

const void SaveBitmap(Bitmap bitmap, int index,WString file_name) {
  RectF margin = RectF(50,30,30,30);
  PointF size = PointF(480,800);
  RectI rect(0, 0, static_cast<int>(size.x), static_cast<int>(margin.top));
  bitmap.FillRect(0xFFFFFFFF, &rect);
  rect = RectI(0, static_cast<int>(size.y - margin.bottom), static_cast<int>(size.x), static_cast<int>(size.y));
  bitmap.FillRect(0xFFFFFFFF, &rect);
  Image image;
  image.AddFrame(bitmap);

  WString save_path;
  WString sIndex;
  sIndex.Format((FX_LPCWSTR)L"%d",index);
  save_path = output_directory + L"reflow" + file_name + sIndex + L".bmp";
  image.SaveAs(save_path);
}

// The change for the size of the picture depends on the size of the content of reflow page.
void ReflowSingle(PDFDoc doc) {
  RectF margin = RectF(50,30,30,30);
  PointF size = PointF(480,800);
  int page_count = doc.GetPageCount();
  for (int i=0;i<page_count;i++) {
    PDFPage page = doc.GetPage(i);
    // Parse PDF page.
    page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);

    ReflowPage reflow_page(page);
    // Set some arguments used for parsing the relfow page.
    reflow_page.SetLineSpace(0);
    reflow_page.SetScreenMargin(static_cast<int>(margin.left), static_cast<int>(margin.top),
      static_cast<int>(margin.right), static_cast<int>(margin.bottom));
    reflow_page.SetScreenSize(size.x, size.y);
    reflow_page.SetZoom(100);
    reflow_page.SetParseFlags(ReflowPage::e_Normal);

    // Parse reflow page.
    reflow_page.StartParse(NULL);

    // Get actual size of content of reflow page. The content size does not contain the margin.
    float content_width = reflow_page.GetContentWidth();
    float content_height = reflow_page.GetContentHeight();

    // Create a bitmap for rendering the reflow page. The bitmap size contains the margin.
    Bitmap bitmap(static_cast<int>(content_width + margin.left + margin.right),
      static_cast<int>(content_height + margin.top + margin.bottom), foxit::common::Bitmap::e_DIBArgb, NULL, 0);
    bitmap.FillRect(0xFFFFFFFF, NULL);

    // Render reflow page.
    Renderer renderer(bitmap, false);
    foxit::Matrix matrix = reflow_page.GetDisplayMatrix(0, 0,content_width,content_height,Rotation::e_Rotation0);
    renderer.StartRenderReflowPage(reflow_page, matrix, NULL);
    WString file_name = L"_single_";
    SaveBitmap(bitmap, i,file_name);
  }

}

// Fixed bitmap size, just to simulate split screen situation.
void ReflowContinuous(PDFDoc doc) {
  RectF margin = RectF(50,30,30,30);
  PointF size = PointF(480,800);
  float display_height = size.y - margin.top - margin.bottom;
  Bitmap bitmap(static_cast<int>(size.x), static_cast<int>(size.y), foxit::common::Bitmap::e_DIBArgb, NULL, 0);
  float offset_y = 0;
  int page_count = doc.GetPageCount();

  int bitmap_index = 0;

  for(int i=0;i<page_count;i++)
  {
    PDFPage page = doc.GetPage(i);

    // Parse PDF page.
    page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);

    ReflowPage reflow_page(page);
    // Set some arguments used for parsing the relfow page.
    reflow_page.SetLineSpace(0);
    reflow_page.SetScreenMargin(static_cast<int>(margin.left), static_cast<int>(margin.top),
      static_cast<int>(margin.right), static_cast<int>(margin.bottom));
    reflow_page.SetScreenSize(size.x, size.y);
    reflow_page.SetZoom(100);
    reflow_page.SetParseFlags(ReflowPage::e_WithImage);

    reflow_page.SetTopSpace(offset_y);

    // Parse reflow page.
    reflow_page.StartParse(NULL);

    // Get actual size of content of reflow page.
    // The content size does not contain the margin but contains the top space.
    float content_height = reflow_page.GetContentHeight();
    float content_width = reflow_page.GetContentWidth();
    // Render reflow page.
    Renderer renderer(bitmap, false);
    foxit::Matrix matrix = reflow_page.GetDisplayMatrix(0, 0,(int)content_width,(int)content_height,foxit::common::Rotation::e_Rotation0);
    renderer.StartRenderReflowPage(reflow_page, matrix, NULL);

    int rate_need_screen_count = static_cast<int>(ceil(max(content_height - display_height, 0.0f) / display_height));
    if (rate_need_screen_count > 0) {
      // Before do next rendering, save current bitmap first.
      WString file_name = L"_continuous_";
      SaveBitmap(bitmap, bitmap_index++,file_name);

      float has_display_height = display_height;
      for (int j = 0; j < rate_need_screen_count; j++) {
        // Clear the bitmap and used it to do next rendering.
        bitmap.FillRect(0xFFFFFFFF, NULL);
        // Render reflow page.
        Renderer renderer(bitmap, false);
        foxit::Matrix matrix = reflow_page.GetDisplayMatrix(0, -has_display_height,content_width,content_height,Rotation::e_Rotation0);
        renderer.StartRenderReflowPage(reflow_page, matrix, NULL);
        if (j != rate_need_screen_count - 1) {
          has_display_height += display_height;
          SaveBitmap(bitmap,  bitmap_index++,file_name);
        } else {
          offset_y = content_height - rate_need_screen_count * display_height;
        }
      }
    } else {
      offset_y = content_height;
    }
  }
  WString file_name = L"_continuous_";
  SaveBitmap(bitmap,  bitmap_index++,file_name);

}
int main(int argc, char *argv[])
{
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
    PDFDoc doc=PDFDoc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }
    ReflowContinuous(doc);
    ReflowSingle(doc);

    cout << "Reflow test." << endl;
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

