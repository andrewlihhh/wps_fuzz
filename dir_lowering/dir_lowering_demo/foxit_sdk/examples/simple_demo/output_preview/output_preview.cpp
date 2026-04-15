// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to do output preview.


// Include Foxit SDK header files.
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

// Include Foxit SDK header files.
#include "../../../include/common/fs_image.h"
#include "../../../include/common/fs_render.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/pdf/fs_outputpreview.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;


// sn and key information from Foxit PDF SDK's key files are used to initialize Foxit PDF SDK library. 
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

WString output_directory = output_path + L"output_preview/";

int main(int argc, char *argv[]) {
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file_name = L"page_organization_123.pdf";
  WString input_file_path = input_path + input_file_name;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library.
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  printf("Input file path: %s\r\n", (const char*)String::FromUnicode(input_file_path));

  // "default_icc_folder_path" is the path of the folder which contains default icc profile files. Please refer to Developer Guide for more details.
  WString default_icc_folder_path = L"";
  if (default_icc_folder_path.IsEmpty()) {
    std::cout << "default_icc_folder_path is still empty. Please set it with a valid path to the folder which contains default icc profile files." << std::endl;
    return 1;
  }
  // Set folder path which contains default icc profile files.
  try {
    Library::SetDefaultICCProfilesPath(default_icc_folder_path);
  } catch (Exception e) {
    if (foxit::e_ErrFilePathNotExist == e.GetErrCode()) {
      std::cout << "default_icc_folder_path does not exist. Please set it with a valid path to the folder which contains default icc profile files." << std::endl;
      return 1;
    } else {
      cout << e.GetMessage() << endl;
      return 1;
    }
  }

  try {
    PDFDoc pdf_doc(input_file_path);
    pdf_doc.StartLoad();
    PDFPage pdf_page = pdf_doc.GetPage(0);
    pdf_page.StartParse(PDFPage::e_ParsePageNormal);
    float page_width = pdf_page.GetWidth();
    float page_height = pdf_page.GetHeight();
    int bitmap_width = (int)page_width;
    int bitmap_height = (int)page_height;
    Bitmap::DIBFormat bitmap_format = Bitmap::e_DIBInvalid;
    uint32 background_color = 0x000000;
    if (pdf_page.HasTransparency()) {
      background_color = 0x000000;
      bitmap_format = Bitmap::e_DIBArgb;
    }
    else {
      background_color = 0xFFFFFF;
      bitmap_format = Bitmap::e_DIBRgb32;
    }
    Matrix display_matrix = pdf_page.GetDisplayMatrix(0, 0, bitmap_width, bitmap_height, common::e_Rotation0);

    Bitmap render_bitmap(bitmap_width, bitmap_height, bitmap_format);
    render_bitmap.FillRect(background_color);
    Renderer renderer(render_bitmap, false);

    OutputPreview output_preview(pdf_doc);
    WString simulation_icc_file_path = input_path + L"icc_profile/USWebCoatedSWOP.icc";
    output_preview.SetSimulationProfile(simulation_icc_file_path);
    output_preview.SetShowType(OutputPreview::e_ShowAll);
    StringArray process_plates = output_preview.GetPlates(OutputPreview::e_ColorantTypeProcess);
    StringArray spot_plates = output_preview.GetPlates(OutputPreview::e_ColorantTypeSpot);

    // Set check status of spot plate to be true, if there's any spot plate.
    for (int i = 0; i < (int)spot_plates.GetSize(); i++) {
      output_preview.SetCheckStatus(spot_plates[i], true);
    }

    // Only set one process plate to be checked each time and generate the preview bitmap.
    for (int i = 0; i < (int)process_plates.GetSize(); i++) {
      if (0 != i)
        output_preview.SetCheckStatus(process_plates[i - 1], false);
      output_preview.SetCheckStatus(process_plates[i], true);

      Bitmap preview_bitmap = output_preview.GeneratePreviewBitmap(pdf_page, display_matrix, renderer);

      Image result_image;
      result_image.AddFrame(preview_bitmap);
      WString temp_wide_str;
      temp_wide_str.Format((FX_LPCWSTR)L"preview_result_ProcessPlate[%d]_true.bmp", i);
      WString saved_file_path = output_directory + temp_wide_str;
      result_image.SaveAs(saved_file_path);
    }

    cout << "[END] demo output_preview." << endl;
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  } catch(...) {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}

