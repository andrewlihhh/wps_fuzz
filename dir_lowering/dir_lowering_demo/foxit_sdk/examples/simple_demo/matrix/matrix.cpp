// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file is a demo to demonstrate how to use matrix to translate, scale... objects.

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
#include "../../../include/pdf/objects/fs_pdfobject.h"

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
WString output_directory = output_path + L"matrix/";

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
int main(int argc, char *argv[])
{
  int err_ret = 0;
  WString input_file = input_path + L"SamplePDF.pdf";
  WString output_directory = output_path + L"matrix/";
  WString file_info = output_directory + L"matrix_info.txt";

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
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }
    // Get and parse page.
    PDFPage page = doc.GetPage(0);
    page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);
    POSITION pos = page.GetFirstGraphicsObjectPosition();
    int flag = 0;
    while(pos) {
      if(flag == (2 | 4))
        break;
      graphics::GraphicsObject* obj = page.GetGraphicsObject(pos);
      pos = page.GetNextGraphicsObjectPosition(pos);
      graphics::GraphicsObject::Type type = obj->GetType();
      float start_x = 0;
      // Get one TextObject or one ImageObject.
      if(type == graphics::GraphicsObject::e_TypeText && !(flag & 2)) {
        graphics::TextObject* text_obj = (graphics::TextObject*)obj;
        WString text = text_obj->GetText();
        if(text.Compare(L"Foxit Software Incorporated") != 0){
          continue;
        }
        start_x = 400.0f;
        flag |= 2;
      } else if(type == graphics::GraphicsObject::e_TypeImage && !(flag & 4)) {
        start_x = 150.0f;
        flag |= 4;
      }else{
        continue;
      }

      // Now we have found the TextObject or the ImageObject, transform them.
      graphics::GraphicsObject* clone_obj1 = obj->Clone();
      Matrix matrix = clone_obj1->GetMatrix();
      // Translate the matrix in vertical direction.
      matrix.Translate(0, 150);
      clone_obj1->SetMatrix(matrix);
      page.InsertGraphicsObject(NULL, clone_obj1);

      graphics::GraphicsObject* clone_obj2 = obj->Clone();
      matrix = clone_obj2->GetMatrix();
      float d = matrix.d;
      float e = matrix.e;
      float f = matrix.f;
      // Translate it to the original point(0,0) first
      matrix.Translate(-e, -f);
      // Rotate the matrix 90 degree in anticlockwise direction.
      matrix.Rotate(1.57f);
      //Page rotation should be considered, assume that the current page rotation is 0.
      float distance = d;
      if(type == graphics::GraphicsObject::e_TypeText)
      {
        RectF obj_rect = obj->GetRect();
        distance = obj_rect.top - obj_rect.bottom;
      }
      // Translate it to the specific coordinate(start_x,400)
      matrix.Translate(distance + start_x , 400);
      clone_obj2->SetMatrix(matrix);
      page.InsertGraphicsObject(NULL, clone_obj2);

      graphics::GraphicsObject* clone_obj3 = obj->Clone();
      matrix = clone_obj3->GetMatrix();
      // Translate it to the original point(0,0) first
      matrix.Translate(-e, -f);
      // Magnify the matrix 1.5 times in both horizontal and vertical directions.
      matrix.Scale(1.5, 1.5);
      // Translate it to the specific coordinate(start_x,600)
      matrix.Translate(start_x, 600.0f);
      clone_obj3->SetMatrix(matrix);
      page.InsertGraphicsObject(NULL, clone_obj3);

      graphics::GraphicsObject* clone_obj4 = obj->Clone();
      matrix = clone_obj4->GetMatrix();
      // Translate it to the original point(0,0) first
      matrix.Translate(-e, -f);
      // Skews the x axis by an angle 0.5 and the y axis by an angle 0.5.
      matrix.Shear(0.5, 0.5);
      // Translate it to the specific coordinate(start_x,800)
      matrix.Translate(start_x, 800.0f);
      clone_obj4->SetMatrix(matrix);
      page.InsertGraphicsObject(NULL, clone_obj4);
    }
    // Generate the page content
    page.GenerateContent();

    // Save the pdf document
    doc.SaveAs(output_directory + L"/MatrixTransformResult.pdf");
    cout << "Matrix demo." << endl;

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