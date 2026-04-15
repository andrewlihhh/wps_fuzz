// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to implement the conversion between OFD
// file and PDF file and to render OFD page.
// Windows platform supports 32-bit and 64-bit,Linux platform only supports 64-bit.

#if (defined(_WIN32) || defined(_WIN64)) || defined(__linux__)

// Include Foxit SDK header files.
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/addon/conversion/fs_convert.h"
#include "../../../include/addon/ofd/fs_ofddoc.h"
#include "../../../include/addon/ofd/fs_ofdpage.h"
#include "../../../include/addon/ofd/fs_ofdrenderer.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace addon::ofd;
using namespace addon::conversion;

static const char* sn = "XQSqpYXftiFIcjaUVzEYXWVFvT86aRH+NpxaYmpzjXt+knIjbaBmMQ==";
static const char* key = "8f3g1kNstBkNAgfCSIczuioWaeXe4+c9+glonrwf6b2LMfDWf0CC92cxiF1M4Re6KUqmkA3+M4O1IRQXmfDg2WnFjr6Fy5eBqpmElth3Kch1UnDYqzIPf4PVOEZvUd51NT/a3Rp2dprVjI9p43m4BRUbHi14Ls5WJrbjiVImPsVCUGD4vLwv5KivNUlruYxBJklnVqASv/Ql2eMYs+QjkW2FF561ojrhWBbkZo+foLp7Dks6zaDFn2bjnFO0QQoD20LdUWuJc38kL+k6tcTaieNizW1FzvFVFDY8NWnaPY7k9nth2Ty5DtIdwMs2WuHrWIgd01SI/FkGZnVjdnmHMrGMNaJeiLJi64khor68iqTH+5C+3Eq48zfcsrsA8Qpe3GDEMHA1aDadhOj+wM1jFvjDQNQR4UQrgVEcS8HhoQECjJv3p/n6zpqSUEHwgoWt3MCZaOButo4qsSUf00/oFCrSaKugMwZsIZPzLilaIvyDYEyVUTDeZmnFRCri9Bnylj/uD+N2EPm2YZnsePp/ORv3FIHlNMl6kOQXmZMKsZMGQcCLc8Xxf9nSaiZzYD1jRgcytPBP0ROfN/rG3EI/1lG+ZCnax9oadtpEbEGjUvja70YRE14iVwR8QIRFVpqJVZTCMcmuFpMFfC2CKcYQORBygs+6bnobAli9qIzIoXvbk2gYI5X2WhkZHRwIrOXwk3fW9nFKjCXVpyYSFSdOrkRQdAT5u+6eEIaSD47GmIHoaDDlHH1RF6BusVsCqvfAfG8qIYJNes2q/c5nheCmBThdWjl4MKwxPH7K306MaekAKFPJAwKhBTES9nZrsseQLQ9v8WNGTZyBwJucEHMCol+Vk3lf+PpKEaD6G8TT7n36V43XJ/N09APgDcGxGB4rAAeinCbANyaYOQtZ0jb+5Jb/NKQ2grdA9KoEvafLE09J4VSloQPQOCCbIwhrvwZO0guWaEjXbiN4UPzSOnyQK7lZfFNmAIgjZtAqzIL8yeGes0I/CCI4CiRKz+pFh313WLtbKi3acqO7GrlFH9g652bkeITPg06fhkqSVjf7iHv+ZpZYXWz+K0FiTUaCinPzNKOCWbYrqNcWaM1Y6bR/uoUJkSUMoODHZ3csWhOz7VqUVZc9M4U6Qg0+0wck3w+ZbdEyVSlWnAPXkphg4UYMrMrUFUzHYSjORTdXoLYMveoIbWMhubtugl0DqD8hOEWqaGYYlJo2N2WU54mYEIaoZ8wfpWsMVOfPFyi5j754lngonq5vf36inXn3xRO5CkYFrzXKJ3n2DYiSrVV0ll/5WTkR3F/lEby4CP81UkVubm4GrvH7fBnhQuWgV9GlZbZhaCWl6FC1dnabn+sNwvh3iEP/2oWqi2013gtQQlSSFE5mCg+pCr6zFEAUTNHBqQZrXyMdIJ9tNimbX551HE+bKp5Eog1wHWP1k3orEjQUwm+R";

#if defined(_WIN32) || defined(_WIN64)
static WString output_path = WString::FromLocal("../output_files/");
static WString input_path = WString::FromLocal("../input_files/ofd/");

#else
static WString output_path = WString::FromLocal("./output_files/");
static WString input_path = WString::FromLocal("./input_files/ofd/");
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

int main(int argc, char *argv[]) {
  int err_ret = 0;
  WString output_directory = output_path + L"ofd/";

#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {

    // Initialize OFD engine. "engine_path" is the path of ofd engine file. Please refer to Developer Guide for more details.
    String engine_path = "";
    error_code = Library::InitializeOFDEngine(engine_path);
    if (error_code != foxit::e_ErrSuccess) {
      switch(error_code){
        case foxit::e_ErrInvalidLicense:
          printf("[Failed] OFD module is not contained in current Foxit PDF SDK keys.\n");
          break;
        default:
          printf("Fail to initialize OFD engine. Error: %d\n", error_code);
          break;
      }
      return 1;
    }
    cout << "OFD Engine is initialized." << endl;

    WString src_ofd_path = input_path + L"wm_txttiled.ofd";
    WString src_pdf_path = input_path + L"test.pdf";
    WString render_file_path = input_path + L"content_flag.ofd";
    // Convert PDF document to OFD document, and convert OFD document to PDF document.
    {
      OFDConvertParam convert_param;
      // Convert OFD document to PDF document.
      Convert::FromOFD(src_ofd_path, L"", output_directory + L"ofd2pdf.pdf", convert_param);
      // Convert PDF document to OFD document.
      Convert::ToOFD(src_pdf_path, L"", output_directory + L"pdf2ofd.ofd", convert_param);
    }

    // Render OFD document to bitmap.
    {
      OFDDoc doc(render_file_path, L"");
      OFDPage ofd_page = doc.GetPage(0);
      // Get the size of the page.
      float w = ofd_page.GetWidth();
      float h = ofd_page.GetHeight();
      Bitmap bitmap = Bitmap((int)w, (int)h, Bitmap::e_DIBArgb, NULL, 0);
      RectI fRect(0, (int)h, (int)w, 0);
      bitmap.FillRect(0xFFFFFFFF, &fRect);
      // Get the display matrix of the page.
      Matrix matrix_1 = ofd_page.GetDisplayMatrix(0, 0, (int)w, (int)h, CommonDefines::e_Rotation0);

      OFDRenderer ofd_render(bitmap);

      Progressive progressive = ofd_render.StartRender(ofd_page, matrix_1);
      WString sSaveFilePath = output_directory + L"renderBitmap.bmp";
      // Add the bitmap to image and save the image.
      Image image;
      image.AddFrame(bitmap);
      image.SaveAs(sSaveFilePath);
      ofd_page.Release();
      doc.Release();
    }
    Library::ReleaseOFDEngine();

    cout << "END: OFD demo." << endl;
  } catch (const Exception& e) {
    switch(e.GetErrCode()){
      case foxit::e_ErrInvalidLicense:
        printf("[Failed] OFD module is not contained in current Foxit PDF SDK keys.\n");
        break;
      default:
        printf("%s\n", (const char*)e.GetMessage());
        break;
    }
    err_ret = 1;
  }
  catch(...)
  {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}

#endif  // (defined(_WIN32) || defined(_WIN64)) || defined(__linux__)
