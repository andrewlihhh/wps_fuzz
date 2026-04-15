// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to import annotations from FDF/XFDF files
// and export annotations to FDF/XFDF files.

#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/pdf/annots/fs_annot.h"
#include "../../../include/pdf/interform/fs_pdfform.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace annots;
using namespace actions;

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

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"fdf/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library.
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    {
      // Import FDF file
      WString input_file = input_path + L"AboutFoxit.pdf";
      WString fdf_file = input_path + L"AnnotationData.fdf";
      pdf::PDFDoc pdf_doc(input_file);
      ErrorCode error_code = pdf_doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
      }

      fdf::FDFDoc fdf_doc(fdf_file);
      pdf_doc.ImportFromFDF(fdf_doc, PDFDoc::e_Annots);
      cout << "Import annotations from fdf with file." << endl;
      WString output_file = output_directory + L"AboutFoxit_importFDF.pdf";
      pdf_doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);
    }

    {
       // Import FDF file
       WString input_file = input_path + L"AboutFoxit.pdf";
       WString fdf_file = input_path + L"AnnotationData.fdf";
       pdf::PDFDoc pdf_doc(input_file); 
       ErrorCode error_code = pdf_doc.Load();
       if (error_code != foxit::e_ErrSuccess) {
         printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
         return 1;
       }

       FILE* file = NULL;
#if defined(_WIN32) || defined(_WIN64)
       fopen_s(&file, (const char*)(const char*)String::FromUnicode(fdf_file), "rb+");
#else
       file = fopen((const char*)(const char*)String::FromUnicode(fdf_file), "rb+");
#endif
       fseek(file, 0, SEEK_END);
       size_t file_size = (size_t)ftell(file);
       char* buffer = (char*)malloc(file_size * sizeof(char));
       memset(buffer, 0 , file_size);

       fseek(file, 0, SEEK_SET);
       fread(buffer, sizeof(char), file_size, file);
       fclose(file);

       fdf::FDFDoc fdf_doc(buffer, file_size);
       pdf_doc.ImportFromFDF(fdf_doc, PDFDoc::e_Annots);
       cout << "Import annotations from fdf with memory buffer." << endl;
       WString output_file = output_directory + L"AboutFoxit_importFDF_FromMemory.pdf";
       pdf_doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);
       free(buffer);
    }

    {
      // Export FDF file
      WString input_file = input_path + L"AnnotationDataExport.pdf";
      WString output_fdf = output_directory + L"AnnotationDataExport_fdf.fdf";

      pdf::PDFDoc pdf_doc(input_file);
      ErrorCode error_code = pdf_doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
      }

      fdf::FDFDoc fdf_doc(foxit::fdf::FDFDoc::e_FDF);
      pdf_doc.ExportToFDF(fdf_doc, pdf::PDFDoc::e_Annots);

      fdf_doc.SaveAs(output_fdf);
      cout << "Export a fdf file." << endl;

    }
    {
      // Export XFDF file
      WString input_file = input_path + L"AnnotationDataExport.pdf";
      WString output_xfdf = output_directory + L"AnnotationDataExport_xfdf.xfdf";

      pdf::PDFDoc pdf_doc(input_file);
      ErrorCode error_code = pdf_doc.Load();
      if (error_code != foxit::e_ErrSuccess) {
        printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
        return 1;
      }

      fdf::FDFDoc fdf_doc(foxit::fdf::FDFDoc::e_XFDF);
      pdf_doc.ExportToFDF(fdf_doc, pdf::PDFDoc::e_Annots);
      cout << "Export an xfdf file." << endl;
      fdf_doc.SaveAs(output_xfdf);
    }

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
