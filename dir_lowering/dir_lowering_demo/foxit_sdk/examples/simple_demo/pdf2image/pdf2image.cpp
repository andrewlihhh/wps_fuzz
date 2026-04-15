// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file is a demo demonstrate how to convert a PDF file to one or multiple image files.

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

WString output_directory = output_path + L"pdf2image/";

void Save2Image(Bitmap& bitmap, int page_index, const char* sExt, bool from_memory) {
  // Add the bitmap to image and save the image.
  Image image;
  image.AddFrame(bitmap);
  WString s;
  if (from_memory)
    s.Format((FX_LPCWSTR)L"AboutFoxit_from_memory_%d",page_index);
  else
    s.Format((FX_LPCWSTR)L"AboutFoxit_%d",page_index);
  s = output_directory + s + WString::FromLocal(sExt);
  image.SaveAs(s);

  cout << "Save page " << page_index << " into a picture of " << sExt << " format" << (from_memory ? " from memory" : "") << "." << endl;
}

void PDF2Image(PDFDoc doc, bool from_memory) {
  const char* support_image_extends[] = {".bmp", ".jpg", ".jpeg", ".png", ".jpx", ".jp2"};

  // Get page count
  int page_count = doc.GetPageCount();
  for(int i=0;i<page_count;i++) {
    PDFPage page = doc.GetPage(i);
    // Parse page.
    page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);

    int width = static_cast<int>(page.GetWidth());
    int height = static_cast<int>(page.GetHeight());
    Matrix matrix = page.GetDisplayMatrix(0, 0, width, height, page.GetRotation());

    // Prepare a bitmap for rendering.
    Bitmap bitmap(width, height, foxit::common::Bitmap::e_DIBArgb, NULL, 0);
    bitmap.FillRect(0xFFFFFFFF, NULL);

    // Render page
    Renderer render(bitmap, false);
    render.StartRender(page, matrix, NULL);
    for(unsigned int j=0;j<sizeof(support_image_extends)/sizeof(support_image_extends[0]);j++) {
      const char* extend = support_image_extends[j];
      Save2Image(bitmap,i,extend,from_memory);
    }
  }
}

void SaveTiffImage(PDFDoc doc, bool from_memory)
{
  const char* support_multi_image[] = { ".tif", ".tiff" };
  for (int i = 0; i < sizeof(support_multi_image) / sizeof(support_multi_image[0]); i++) {
    WString s = output_directory + L"AboutFoxit";
    if (from_memory) s += L"_from_memory";
    s += WString::FromLocal(support_multi_image[i]);;
    Image image;
    int nPageCount = doc.GetPageCount();
    for (int page_index = 0; page_index < nPageCount; page_index++) {
      PDFPage page = doc.GetPage(page_index);
      // Parse page.
      page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);

      int width = static_cast<int>(page.GetWidth());
      int height = static_cast<int>(page.GetHeight());
      Matrix matrix = page.GetDisplayMatrix(0, 0, width, height, page.GetRotation());

      // Prepare a bitmap for rendering.
      Bitmap bitmap(width, height, foxit::common::Bitmap::e_DIBArgb, NULL, 0);
      bitmap.FillRect(0xFFFFFFFF, NULL);

      // Render page
      Renderer render(bitmap, false);
      render.StartRender(page, matrix, NULL);
      image.AddFrame(bitmap);
    }
    image.SaveAs(s);
    cout << "Save pdf file " << " into a picture of " << support_multi_image[i] << " format" << (from_memory ? " from memory":"") << "." <<endl;
  }
}

#if defined(_WIN32) || defined(_WIN64)
void SaveHDC2BMPFile(HDC hdc_display, int page_index) {
  // Get HBITMAP from HDC.
  HBITMAP hBitmap = (HBITMAP)::GetCurrentObject(hdc_display, OBJ_BITMAP);
  if (!hBitmap) {
    printf("[Failed] Cannot get OBJ_BITMAP of the HDC for rendering page (page index = %d).\r\n", page_index);
    return;
  }

  // Get BITMAP for HBTIMAP.
  BITMAP bitmap;
  ::GetObject(hBitmap, sizeof(BITMAP), &bitmap);
  unsigned int bitmap_byte_per_line = (bitmap.bmWidth * bitmap.bmBitsPixel + 7) / 8;
  bitmap_byte_per_line = (bitmap_byte_per_line + 3) / 4 * 4;
  auto bitmap_byte_size = bitmap_byte_per_line * bitmap.bmHeight;

  // Get data of HBITMAP
  unsigned char* hbitmap_data = new unsigned char[bitmap_byte_size];
  ::GetBitmapBits(hBitmap, bitmap_byte_size, hbitmap_data);
  if (!hbitmap_data) {
    printf("[Failed] Cannot get data of HBITMAP for the HDC for rendering page (page index = %d).\r\n", page_index);
    return;
  }

  String save_bmp_path;
  save_bmp_path.Format("%srender_by_hdc_page%d.bmp", (FX_LPCSTR)String::FromUnicode(output_directory), page_index);
  FILE* save_file = NULL;
  fopen_s(&save_file, (const char*)(FX_LPCSTR)save_bmp_path, "wb");

  if (!save_file) {
    printf("[Failed] Cannot open the save file %s.\r\n", (FX_LPCSTR)save_bmp_path);
    return;
  }

  // Save to a .bmp file.
  int file_size = 14 + 40 + bitmap_byte_size;
  // Prepare file header buffer
  unsigned char fileHeadBuf[14];
  memset(fileHeadBuf, 0, 14);
  fileHeadBuf[0] = 'B';
  fileHeadBuf[1] = 'M';
  fileHeadBuf[2] = (unsigned char)file_size;
  fileHeadBuf[3] = (unsigned char)(file_size >> 8);
  fileHeadBuf[4] = (unsigned char)(file_size >> 16);
  fileHeadBuf[5] = (unsigned char)(file_size >> 24);
  fileHeadBuf[6] = fileHeadBuf[7] = fileHeadBuf[8] = fileHeadBuf[9] = 0;
  fileHeadBuf[10] = 54;
  fileHeadBuf[11] = fileHeadBuf[12] = fileHeadBuf[13] = 0;

  // Write file header buffer to file.
  fwrite(fileHeadBuf, 14, 1, save_file);

  // Prepare bmp header buffer
  unsigned char bmpHeadBuf[40];
  memset(bmpHeadBuf, 0, 40);
  int bitmapwidth = bitmap.bmWidth;
  int bitmapheight = bitmap.bmHeight;
  memset(bmpHeadBuf, 0, 40);
  bmpHeadBuf[0] = 40;
  bmpHeadBuf[4] = (unsigned char)bitmapwidth;
  bmpHeadBuf[5] = (unsigned char)(bitmapwidth >> 8);
  bmpHeadBuf[6] = (unsigned char)(bitmapwidth >> 16);
  bmpHeadBuf[7] = (unsigned char)(bitmapwidth >> 24);
  bmpHeadBuf[8] = (unsigned char)(-1 * bitmapheight);
  bmpHeadBuf[9] = (unsigned char)((-1 * bitmapheight) >> 8);
  bmpHeadBuf[10] = (unsigned char)((-1 * bitmapheight) >> 16);
  bmpHeadBuf[11] = (unsigned char)((-1 * bitmapheight) >> 24);
  bmpHeadBuf[12] = 1; //plane always 1
  bmpHeadBuf[14] = (char)bitmap.bmBitsPixel;
  // Write bmp header buffer to file.
  fwrite(bmpHeadBuf, 40, 1, save_file);

  // Write HBITMAP data to file.
  fwrite(hbitmap_data, 1, bitmap_byte_size, save_file);

  // Close file
  fclose(save_file);
  // Release resources.
  delete[] hbitmap_data;
}

void PDF2ImageByDC(PDFDoc doc) {
  // (Only for Windows) Show how to use HDC to render PDF page and then save the rendering result of HDC to .bmp file.
  int page_count = doc.GetPageCount();
  for (int i = 0; i<page_count; i++) {
    PDFPage page = doc.GetPage(i);
    // Parse page.
    page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);

    int page_width = static_cast<int>(page.GetWidth());
    int page_height = static_cast<int>(page.GetHeight());

    // Create HDC for rendering PDF page.
    HDC hdc_display = CreateDCA("DISPLAY", NULL, NULL, NULL);
    if (!hdc_display) {
      printf("[Failed] Cannot create HDC for rendering a PDF page.\r\n");
      return ;
    }

    // Calculate the size of render area.
    int device_width = GetDeviceCaps(hdc_display, HORZRES);
    int device_height = GetDeviceCaps(hdc_display, VERTRES);
    float x_scale = ((float)device_width) / page_width;
    float y_scale = ((float)device_height) / page_height;
    float scale = x_scale < y_scale ? x_scale : y_scale;
    int actual_render_width = 0;
    int actual_render_height = 0;
    if (x_scale < y_scale) {
      actual_render_width = device_width;
      actual_render_height = (int)(scale * page_height + 0.5);
    } else {
      actual_render_width = (int)(scale * page_width + 0.5);
      actual_render_height = device_height;
    }
    int x_offset = 0;
    int y_offset = 0;
    // Prepare display_matrix for displaying the page.
    Matrix display_matrix = page.GetDisplayMatrix(x_offset, y_offset, actual_render_width, actual_render_height, page.GetRotation());

    // Fill the HDC with white brush.
    HBRUSH hBrush = CreateSolidBrush(RGB(0xff, 0xff, 0xff));
    if (hBrush) {
      RECT rect = { (LONG)x_offset, (LONG)y_offset, (LONG)(actual_render_width + x_offset), (LONG)(actual_render_height + y_offset) };
      FillRect(hdc_display, &rect, hBrush);
      DeleteObject(hBrush);
    }

    // Render PDF page by HDC.
    Renderer render(hdc_display);
    render.StartRender(page, display_matrix, NULL);
    SaveHDC2BMPFile(hdc_display, i);

    // Release resources.
    DeleteDC(hdc_display);
  }
}

#endif  // #if defined(_WIN32) || defined(_WIN64)

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
    {
       PDFDoc doc = PDFDoc(input_file);
       ErrorCode error_code = doc.Load();
       if (error_code != foxit::e_ErrSuccess) {
         printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
         return 1;
       }
       PDF2Image(doc, false);
       SaveTiffImage(doc, false);

#if defined(_WIN32) || defined(_WIN64)
       // Following code is about how to use HDC (in Windows) to render PDF page by Foxit PDF SDK,
       // and try to save the result in HDC to .bmp file by Windows API.
       // This sampl will not be triggered when the demo runs in a remote desktop,
       // because "save the result in HDC to .bmp file by Windows API" may not do as expected.
       // User can improve "save the result in HDC to .bmp file by Windows API" if necessary.
       DEVMODEA new_screen_settings;
       memset(&new_screen_settings, 0, sizeof(new_screen_settings));
       new_screen_settings.dmSize = sizeof(new_screen_settings);
       EnumDisplaySettingsA(NULL, ENUM_CURRENT_SETTINGS, &new_screen_settings);
       if (0 != strcmp((char*)new_screen_settings.dmDeviceName, "RDPUDD"))
         PDF2ImageByDC(doc);
#endif  // #if defined(_WIN32) || defined(_WIN64)
    }

    {
       cout << "Load document from memory." << endl;

       FILE* file = NULL;
#if defined(_WIN32) || defined(_WIN64)
       fopen_s(&file, (const char*)(const char*)String::FromUnicode(input_file), "rb+");
#else
       file = fopen((const char*)(const char*)String::FromUnicode(input_file), "rb+");
#endif
       fseek(file, 0, SEEK_END);
       size_t file_size = (size_t)ftell(file);
       char* buffer = (char*)malloc(file_size * sizeof(char));
       memset(buffer, 0 , file_size);

       fseek(file, 0, SEEK_SET);
       fread(buffer, sizeof(char), file_size, file);
       fclose(file);

       PDFDoc doc_memory = PDFDoc(buffer, file_size);
       error_code = doc_memory.Load();
       if (error_code != foxit::e_ErrSuccess) {
         printf("The Doc [%s] Error from memory: %d\n", (const char*)String::FromUnicode(input_file), error_code);
         return 1;
       }
       PDF2Image(doc_memory, true);
       SaveTiffImage(doc_memory, true);
       free(buffer);
    }
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