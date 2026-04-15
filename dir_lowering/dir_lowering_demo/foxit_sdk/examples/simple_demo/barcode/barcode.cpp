// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to generate barcode.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/common/fs_barcode.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;

static const char* sn = "XQSqpYXftiFIcjaUVzEYXWVFvT86aRH+NpxaYmpzjXt+knIjbaBmMQ==";
static const char* key = "8f3g1kNstBkNAgfCSIczuioWaeXe4+c9+glonrwf6b2LMfDWf0CC92cxiF1M4Re6KUqmkA3+M4O1IRQXmfDg2WnFjr6Fy5eBqpmElth3Kch1UnDYqzIPf4PVOEZvUd51NT/a3Rp2dprVjI9p43m4BRUbHi14Ls5WJrbjiVImPsVCUGD4vLwv5KivNUlruYxBJklnVqASv/Ql2eMYs+QjkW2FF561ojrhWBbkZo+foLp7Dks6zaDFn2bjnFO0QQoD20LdUWuJc38kL+k6tcTaieNizW1FzvFVFDY8NWnaPY7k9nth2Ty5DtIdwMs2WuHrWIgd01SI/FkGZnVjdnmHMrGMNaJeiLJi64khor68iqTH+5C+3Eq48zfcsrsA8Qpe3GDEMHA1aDadhOj+wM1jFvjDQNQR4UQrgVEcS8HhoQECjJv3p/n6zpqSUEHwgoWt3MCZaOButo4qsSUf00/oFCrSaKugMwZsIZPzLilaIvyDYEyVUTDeZmnFRCri9Bnylj/uD+N2EPm2YZnsePp/ORv3FIHlNMl6kOQXmZMKsZMGQcCLc8Xxf9nSaiZzYD1jRgcytPBP0ROfN/rG3EI/1lG+ZCnax9oadtpEbEGjUvja70YRE14iVwR8QIRFVpqJVZTCMcmuFpMFfC2CKcYQORBygs+6bnobAli9qIzIoXvbk2gYI5X2WhkZHRwIrOXwk3fW9nFKjCXVpyYSFSdOrkRQdAT5u+6eEIaSD47GmIHoaDDlHH1RF6BusVsCqvfAfG8qIYJNes2q/c5nheCmBThdWjl4MKwxPH7K306MaekAKFPJAwKhBTES9nZrsseQLQ9v8WNGTZyBwJucEHMCol+Vk3lf+PpKEaD6G8TT7n36V43XJ/N09APgDcGxGB4rAAeinCbANyaYOQtZ0jb+5Jb/NKQ2grdA9KoEvafLE09J4VSloQPQOCCbIwhrvwZO0guWaEjXbiN4UPzSOnyQK7lZfFNmAIgjZtAqzIL8yeGes0I/CCI4CiRKz+pFh313WLtbKi3acqO7GrlFH9g652bkeITPg06fhkqSVjf7iHv+ZpZYXWz+K0FiTUaCinPzNKOCWbYrqNcWaM1Y6bR/uoUJkSUMoODHZ3csWhOz7VqUVZc9M4U6Qg0+0wck3w+ZbdEyVSlWnAPXkphg4UYMrMrUFUzHYSjORTdXoLYMveoIbWMhubtugl0DqD8hOEWqaGYYlJo2N2WU54mYEIaoZ8wfpWsMVOfPFyi5j754lngonq5vf36inXn3xRO5CkYFrzXKJ3n2DYiSrVV0ll/5WTkR3F/lEby4CP81UkVubm4GrvH7fBnhQuWgV9GlZbZhaCWl6FC1dnabn+sNwvh3iEP/2oWqi2013gtQQlSSFE5mCg+pCr6zFEAUTNHBqQZrXyMdIJ9tNimbX551HE+bKp5Eog1wHWP1k3orEjQUwm+R";

#if defined(_WIN32) || defined(_WIN64)
static WString output_path = WString::FromLocal("../output_files/");
static WString input_path = WString::FromLocal("../input_files/");
#else
static WString output_path = WString::FromLocal("./output_files/");
static WString input_path = WString::FromLocal("./input_files/");
#endif
WString output_directory = output_path + L"barcode/";

class SdkLibMgr {
public:
  SdkLibMgr() : isInitialize(false){};
  ErrorCode Initialize() {
    ErrorCode error_code = Library::Initialize(sn, key);
    if (error_code != foxit::e_ErrSuccess) {
      printf("Library Initialize Error: %d\n", error_code);
    } else {
      isInitialize = true;
    }
    return error_code;

  }
  ~SdkLibMgr(){
    if(isInitialize)
      Library::Release();
  }
private:
  bool isInitialize;
};

void Save2Image(Bitmap& bitmap, WString bmp_name)
{
  // Add the bitmap to image and save the image.
  Image image;
  image.AddFrame(bitmap);

  WString filepath = output_directory + bmp_name;
  image.SaveAs(filepath);
}

// Generate barcode in different type and save each of them as an image file.
void Barcode_GenerateEachType(WString code_string, Barcode::Format code_format, int unit_width, int unit_height, Barcode::QRErrorCorrectionLevel qr_level, WString bmp_name)
{
  Barcode barcode;
  Bitmap bitmap = barcode.GenerateBitmap(code_string, code_format, unit_width, unit_height, qr_level);

  Save2Image(bitmap, bmp_name);
}

// Generate all types of barcode and save each of them as an image file.
void Barcode_GenerateAll( )
{
  // Strings used as barcode content.
  WString sz_code_string[8] = {L"TEST-SHEET", L"102030405060708090", L"80674313", L"890444000335", L"9780804816632", L"070429", L"Unknown - change me!", L"TestForBarcodeQrCode"};
  // Barcode format types
  Barcode::Format code_format[8] = {Barcode::e_FormatCode39, Barcode::e_FormatCode128,
    Barcode::e_FormatEAN8, Barcode::e_FormatUPCA, 
    Barcode::e_FormatEAN13, Barcode::e_FormatITF, 
    Barcode::e_FormatPDF417, Barcode::e_FormatQRCode};

  // Image names for the saved image files.(except QR code)
  WString sz_bmp_name[7] = {L"/code39_TEST-SHEET.bmp", L"/CODE_128_102030405060708090.bmp",
    L"/EAN_8_80674313.bmp", L"/UPC_A_890444000335.bmp", L"/EAN_13_9780804816632.bmp",
    L"/ITF_070429.bmp", L"/PDF_417_Unknown.bmp"};

  //Format error correction level of QR code.
  Barcode::QRErrorCorrectionLevel sz_qr_level[4] = {Barcode::e_QRCorrectionLevelLow, Barcode::e_QRCorrectionLevelMedium, 
    Barcode::e_QRCorrectionLevelQuater, Barcode::e_QRCorrectionLevelHigh};
  //Image names for the saved image files for QR code.
  WString bmp_qr_name[4] = {L"/QR_CODE_TestForBarcodeQrCode_L.bmp", L"/QR_CODE_TestForBarcodeQrCode_M.bmp",
    L"/QR_CODE_TestForBarcodeQrCode_Q.bmp", L"/QR_CODE_TestForBarcodeQrCode_H.bmp"};

  // Unit width for barcode in pixels, preferred value is 1-5 pixels.
  int unit_width = 2;
  // Unit height for barcode in pixels, preferred value is >= 20 pixels.
  int unit_height = 120;

  // Generate barcode for different types.
  for (int i = 0; i < 8; i++)
  {
    if (code_format[i] != Barcode::e_FormatQRCode) {
      // Not QR code
      Barcode_GenerateEachType(sz_code_string[i], code_format[i], unit_width, unit_height, (Barcode::QRErrorCorrectionLevel)0, sz_bmp_name[i]);
    } else {
      // QR code
      //Generate for each format error correction level.
      for (int j = 0; j < 4; j++)
        Barcode_GenerateEachType(sz_code_string[i], code_format[i], unit_width, unit_height, sz_qr_level[j], bmp_qr_name[j]);
    }
  }

}
int main(int argc, char *argv[])
{
  int err_ret = 0;

#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  SdkLibMgr spSdkLibMgr;
  // Initialize library.
  ErrorCode error_code = spSdkLibMgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    // Generate all types of barcode
    Barcode_GenerateAll();
    cout << "Barcode demo." << endl;

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