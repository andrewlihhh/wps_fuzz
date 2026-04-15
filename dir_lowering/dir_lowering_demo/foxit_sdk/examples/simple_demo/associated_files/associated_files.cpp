
// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to associate files with PDF.

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
#include "../../../include/pdf/fs_filespec.h"
#include "../../../include/pdf/fs_pdfassociatefiles.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace pdf::graphics;
using namespace pdf::objects;
using namespace annots;

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
  int err_ret = 0;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  WString output_directory = output_path + L"associated_files/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  // Get information about associated files from PDF document.
  WString input_file = input_path + L"AF_Catalog_Page_Annot.pdf";
  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }

    AssociatedFiles associated_files(doc);
    
    PDFDictionary* doc_catalog_dict = doc.GetCatalog();
    int count = associated_files.GetAssociatedFilesCount(doc_catalog_dict);
    printf("The catalog dictionary of \"AF_Catalog_Page_Annot.pdf\" has %d associated files.\n", count);
    FileSpec filespec = associated_files.GetAssociatedFile(doc_catalog_dict, 0);
    printf("The file name is \"%s\".\n\n", (const char*)String::FromUnicode(filespec.GetFileName()));
    filespec.ExportToFile(output_directory + L"af_1.txt");

    PDFPage page = doc.GetPage(0);
    PDFDictionary* page_dict = page.GetDict();
    count = associated_files.GetAssociatedFilesCount(page_dict);
    printf("The page dictionary of \"AF_Catalog_Page_Annot.pdf\" has %d associated files.\n", count);
    filespec = associated_files.GetAssociatedFile(page_dict, 0);
    printf("The file name is \"%s\".\n\n", (const char*)String::FromUnicode(filespec.GetFileName()));
    filespec.ExportToFile(output_directory + L"af_2.txt");

    Annot annot = page.GetAnnot(0);
    PDFDictionary* annot_dict = annot.GetDict();
    count = associated_files.GetAssociatedFilesCount(annot_dict);
    printf("The annot dictionary of \"AF_Catalog_Page_Annot.pdf\" has %d associated files.\n", count);
    filespec = associated_files.GetAssociatedFile(annot_dict, 0);
    printf("The file name is \"%s\".\n\n", (const char*)String::FromUnicode(filespec.GetFileName()));
    filespec.ExportToFile(output_directory + L"af_4.txt");
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }
  catch(...) {
    cout << "Unknown Exception" << endl;
     err_ret = 1;
  }

  input_file = input_path + L"AF_ImageXObject_FormXObject.pdf";
  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }

    AssociatedFiles associated_files(doc);

    PDFPage page = doc.GetPage(0);
    page.StartParse(PDFPage::e_ParsePageNormal, NULL, false);
    
    POSITION pos = page.GetFirstGraphicsObjectPosition(GraphicsObject::e_TypeImage);
    GraphicsObject* image_x_object = page.GetGraphicsObject(pos);
    PDFDictionary* image_x_object_dict = ((ImageObject*)image_x_object)->GetStream()->GetDictionary();
    int count = associated_files.GetAssociatedFilesCount(image_x_object_dict);
    printf("The image x object of \"AF_ImageXObject_FormXObject.pdf\" has %d associated files.\n", count);
    FileSpec filespec = associated_files.GetAssociatedFile(image_x_object_dict, 0);
    printf("The file name is \"%s\".\n\n", (const char*)String::FromUnicode(filespec.GetFileName()));
    filespec.ExportToFile(output_directory + L"2.jpg");

    pos = page.GetFirstGraphicsObjectPosition(GraphicsObject::e_TypeFormXObject);
    GraphicsObject* form_x_object = page.GetGraphicsObject(pos);
    PDFDictionary* form_x_object_dict = ((FormXObject*)form_x_object)->GetStream()->GetDictionary();
    count = associated_files.GetAssociatedFilesCount(form_x_object_dict);
    printf("The form x object of \"AF_ImageXObject_FormXObject.pdf\" has %d associated files.\n", count);
    filespec = associated_files.GetAssociatedFile(form_x_object_dict, 0);
    printf("The file name is \"%s\".\n\n", (const char*)String::FromUnicode(filespec.GetFileName()));
    filespec.ExportToFile(output_directory + L"af_6.txt");
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
   err_ret = 1;
  }
  catch(...) {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  input_file = input_path + L"AF_MarkedContent.pdf";
  try {
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }

    AssociatedFiles associated_files(doc);

    PDFPage page = doc.GetPage(0);
    page.StartParse(PDFPage::e_ParsePageNormal, NULL, false);

    POSITION pos = page.GetFirstGraphicsObjectPosition(GraphicsObject::e_TypeText);
    GraphicsObject* text_object = page.GetGraphicsObject(pos);
    int count = associated_files.GetAssociatedFilesCount(text_object);
    printf("The text object of \"AF_MarkedContent.pdf\" has %d associated files.\n", count);
    FileSpec filespec = associated_files.GetAssociatedFile(text_object, 0);
    printf("The first file name is \"%s\".\n", (const char*)String::FromUnicode(filespec.GetFileName()));
    filespec.ExportToFile(output_directory + L"bitmap.bmp");

    filespec = associated_files.GetAssociatedFile(text_object, 1);
    printf("The second file name is \"%s\".\n\n", (const char*)String::FromUnicode(filespec.GetFileName()));
    filespec.ExportToFile(output_directory + L"text.txt");
  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }
  catch(...) {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  // Associate files with objects in PDF document.
  input_file = input_path + L"AssociateTestFile.pdf";
  try{
    PDFDoc doc(input_file);
    ErrorCode error_code = doc.Load();
    if (error_code != foxit::e_ErrSuccess) {
      printf("The Doc [%s] Error: %d\n", (const char*)String::FromUnicode(input_file), error_code);
      return 1;
    }

    AssociatedFiles associated_files(doc);

    //Create filespec with 1.txt
    FileSpec filespec_txt(doc);
    filespec_txt.SetAssociteFileRelationship(AssociatedFiles::e_RelationshipSource);
    filespec_txt.SetFileName(L"1.txt");
    DateTime dateTime(2017, 9, 15, 17, 20, 20, 0, 8, 0);
    filespec_txt.SetDescription("text");
    filespec_txt.Embed(input_path +  L"1.txt");
    filespec_txt.SetCreationDateTime(dateTime);
    filespec_txt.SetModifiedDateTime(dateTime);
    filespec_txt.SetSubtype();

    //Associate 1.txt with catalog dictionary.
    {
      PDFObject* catalog_dict = doc.GetCatalog();
      associated_files.AssociateFile(catalog_dict, filespec_txt);
      printf("Associate a text file with catalog dictionary.\n");
      FileSpec filespec_catalog = associated_files.GetAssociatedFile(catalog_dict, 0);
      filespec_catalog.ExportToFile(output_directory + L"catalog.txt");
    }

    PDFPage page = doc.GetPage(0);
    page.StartParse();

    //Associate 1.txt with page dictionary.
    {
      associated_files.AssociateFile(page, filespec_txt);
      printf("Associate a text file with page.\n");

      FileSpec filespec_page = associated_files.GetAssociatedFile(page.GetDict(), 0);
      filespec_page.ExportToFile(output_directory + L"page.txt");
    }

    //Associate 1.txt with annotation dictionary.
    {
      RectF rect(100, 50, 220, 100);
      Annot annot = page.AddAnnot(Annot::e_Note, rect);
      annot.ResetAppearanceStream();
      associated_files.AssociateFile(annot, filespec_txt);
      printf("Associate a text file with annotation.\n");
      FileSpec filespec_annot = associated_files.GetAssociatedFile(annot.GetDict(), 0);
      filespec_annot.ExportToFile(output_directory + L"annotation.txt");
    }

    //Create filespec with 2.jpg image.
    FileSpec filespec_jpg(doc);
    filespec_jpg.SetAssociteFileRelationship(AssociatedFiles::e_RelationshipSource);
    filespec_jpg.SetFileName(L"2.jpg");
    filespec_jpg.SetDescription("jpeg");
    filespec_jpg.Embed(input_path +  L"2.jpg");
    filespec_jpg.SetCreationDateTime(dateTime);
    filespec_jpg.SetModifiedDateTime(dateTime);
    filespec_jpg.SetSubtype();

    //Associate 2.jpg with marked content.
    {
      PDFDictionary* page_dict = page.GetDict();
      PDFDictionary* resource_dict = (PDFDictionary*)page_dict->GetElement("Resources");
      if (!resource_dict) return 1;

      POSITION position = page.GetFirstGraphicsObjectPosition(GraphicsObject::e_TypeText);
      GraphicsObject* text_object = page.GetGraphicsObject(position);
      if (text_object) {
        MarkedContent* markcontent = text_object->GetMarkedContent();
        if (!markcontent) return 1;

        if (markcontent->GetItemCount() == 0) {
          markcontent->AddItem("Associated");
        }
        associated_files.AssociateFile(text_object, 0, resource_dict, "textobject", filespec_jpg);
        page.GenerateContent();

        printf("Associate a jpeg file with markcontent.\n");

        FileSpec filespec_text_object = associated_files.GetAssociatedFile(text_object, 0);
        filespec_text_object.ExportToFile(output_directory + L"textobject.jpg");
      }
    }

    //Associate 2.jpg with image object.
    {
      POSITION position = page.GetFirstGraphicsObjectPosition(GraphicsObject::e_TypeImage);
      ImageObject* image_oject = (ImageObject*)page.GetGraphicsObject(position);
      if (image_oject) {
        associated_files.AssociateFile(image_oject, filespec_jpg);
        printf("Associate a jpeg file with image xobject.\n");

        FileSpec filespec_image_oject = associated_files.GetAssociatedFile(image_oject->GetStream()->GetDictionary(), 0);
        filespec_image_oject.ExportToFile(output_directory + L"image_x_object.jpg");
      }
    }

    //Associate 2.jpg with form XObject.
    {
      POSITION position = page.GetFirstGraphicsObjectPosition(GraphicsObject::e_TypeFormXObject);
      FormXObject* form_x_object = (FormXObject*)page.GetGraphicsObject(position);
      if (form_x_object) {
        associated_files.AssociateFile(form_x_object, filespec_jpg);
        printf("Associate a jpeg file with form xobject.\n");

        FileSpec filespec_form_x_object = associated_files.GetAssociatedFile(form_x_object->GetStream()->GetDictionary(), 0);
        filespec_form_x_object.ExportToFile(output_directory + L"form_x_object.jpg");
      }
    }

    // Save PDF file
    WString newPdf = output_directory + L"associated_files.pdf";
    doc.SaveAs(newPdf, PDFDoc::e_SaveFlagNoOriginal);
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
