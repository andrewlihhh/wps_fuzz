// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to operate PDF objects directly.

// Include header files.
#include <iostream>
// Include  Foxit SDK header files.
#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/objects/fs_pdfobject.h"
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace objects;

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

#if (defined(__linux__) && defined(__x86_64__)) || defined(__APPLE__) || defined(_WIN64)
#define FORMAT_UINT32 "%u"
#else
#define FORMAT_UINT32 "%lu"
#endif

// This function is to do some operation to PDF object.
void ObjectOperation(PDFDoc document) {
  PDFObject* boolean_object = PDFObject::CreateFromBoolean(true);
  uint32 boolean_object_number= document.AddIndirectObject(boolean_object);

  printf("Object number of new boolean object: " FORMAT_UINT32 "\r\n", boolean_object_number);

  bool boolean_object_value = boolean_object->GetBoolean();
  printf("\tValue of new boolean object: %s\r\n", boolean_object_value?"true":"false");

  PDFObject* float_object = PDFObject::CreateFromFloat(0.1f);
  uint32 float_object_number= document.AddIndirectObject(float_object);
  printf("Object number of new number object (as float): " FORMAT_UINT32 "\r\n", float_object_number);
  float float_object_value = float_object->GetFloat();
  printf("\tValue of new number object (as float): %f\r\n", float_object_value);

  PDFObject* integer_object = PDFObject::CreateFromInteger(1);
  uint32 integer_object_number= document.AddIndirectObject(integer_object);
  printf("Object number of new number object (as integer):" FORMAT_UINT32 "\r\n", integer_object_number);
  int integer_object_value = integer_object->GetInteger();
  printf("\tValue of new number object (as integer): %d\r\n", integer_object_value);

  PDFObject* string_object = PDFObject::CreateFromString(L"foxit");
  uint32 string_object_number= document.AddIndirectObject(string_object);
  printf("Object number of new string object:" FORMAT_UINT32 "\r\n", string_object_number);
  WString string_object_value = string_object->GetWideString();
  wprintf(L"\tValue of new string object: %ls\r\n", (const wchar_t*)string_object_value);

  PDFObject* name_object = PDFObject::CreateFromName("sdk");
  uint32 name_object_number= document.AddIndirectObject(name_object);
  printf("Object number of new name object:" FORMAT_UINT32 "\r\n", name_object_number);
  String name_object_value = name_object->GetName();
  printf("\tValue of new name object: %s\r\n", (const char*)name_object_value);

  DateTime date_time(2017, 9, 27, 19, 36, 6, 0, 8, 0);
  PDFObject* datetime_object = PDFObject::CreateFromDateTime(date_time);
  uint32 datetime_object_number= document.AddIndirectObject(datetime_object);
  printf("Object number of new string object (as date-time): " FORMAT_UINT32 "\r\n", datetime_object_number);
  WString datetime_object_value = datetime_object->GetWideString();
  wprintf(L"\tValue of new string object (as date-time): %ls\r\n", (const wchar_t*)datetime_object_value);

  PDFArray* array = PDFArray::Create();
  PDFObject* boolean_object_reference = PDFObject::CreateReference(document, boolean_object_number);
  uint32 boolean_object_reference_number = boolean_object_reference->GetObjNum();
  printf("Object number of a new reference object to a boolean object:" FORMAT_UINT32 "\r\n", boolean_object_reference_number);
  PDFObject* float_object_reference = PDFObject::CreateReference(document, float_object_number);
  PDFObject* integer_object_reference = PDFObject::CreateReference(document, integer_object_number);
  PDFObject* integer_object_direct = integer_object_reference->GetDirectObject();
  printf("Object number of the direct number object: " FORMAT_UINT32 "\r\n", integer_object_direct->GetObjNum());
  PDFObject* string_object_reference = PDFObject::CreateReference(document, string_object_number);
  PDFObject* name_object_reference = PDFObject::CreateReference(document, name_object_number);
  PDFObject* datetime_object_reference = PDFObject::CreateReference(document, datetime_object_number);

  array->AddElement(boolean_object_reference);
  array->AddElement(float_object_reference);
  array->AddElement(integer_object_reference);
  array->AddElement(string_object_reference);
  array->AddElement(name_object_reference);
  array->AddElement(datetime_object_reference);
  array->AddElement(boolean_object->CloneObject());

  uint32 array_object_number = document.AddIndirectObject(array);
  printf("Object number of array object: " FORMAT_UINT32 "\r\n", array_object_number);
}

// This function is to remove some properties from catalog dictionary.
void RemoveCatalogKey(PDFDoc document) {
  if (document.IsEmpty()) return;

  PDFDictionary* catalog = document.GetCatalog();
  if (NULL == catalog) return;

  const char* key_strings[] = { "Type", "Boolean", "Name", "String", "Array", "Dict"};
  int count = sizeof(key_strings)/sizeof(key_strings[0]);
  for (int i = 0; i < count; i ++) {
    if (catalog->HasKey(key_strings[i]))
      catalog->RemoveAt(key_strings[i]);
  }
}

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"pdfobjects/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file = input_path + L"pdfobjects.pdf";
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    PDFDoc doc(input_file);
    doc.StartLoad(NULL, false, NULL);

    // Do some operation about PDF object.
    ObjectOperation(doc);
    WString save_pdf_patth = output_directory + L"pdfobjects_addnewobjects.pdf";
    doc.StartSaveAs((const wchar_t*)save_pdf_patth, PDFDoc::e_SaveFlagNoOriginal, NULL);

    // To remove some properties from catalog dictionary.
    RemoveCatalogKey(doc);
    save_pdf_patth = output_directory + L"pdfobjects_removekeyfromcatalog.pdf";
    doc.StartSaveAs((const wchar_t*)save_pdf_patth, PDFDoc::e_SaveFlagNoOriginal, NULL);

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

