// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to tag a PDF document.

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
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/addon/accessibility/fs_taggedpdf.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace foxit::addon::accessibility;

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

static String GetReportCategoryString(TaggedPDFCallback::ReportCategory type) {
  String sFormat = "";
  switch (type) {
  case TaggedPDFCallback::e_ReportCategoryRegion:
    sFormat = "Region";
    break;
  case TaggedPDFCallback::e_ReportCategoryArtifact:
    sFormat = "Artifact";
    break;
  case TaggedPDFCallback::e_ReportCategoryParagraph:
    sFormat = "Paragraph";
    break;
  case TaggedPDFCallback::e_ReportCategoryListItem:
    sFormat = "List Item";
    break;
  case TaggedPDFCallback::e_ReportCategoryFigure:
    sFormat = "Figure";
    break;
  case TaggedPDFCallback::e_ReportCategoryTable:
    sFormat = "Table";
    break;
  case TaggedPDFCallback::e_ReportCategoryTableRow:
    sFormat = "Table Row";
    break;
  case TaggedPDFCallback::e_ReportCategoryTableHeader:
    sFormat = "Table Header";
    break;
  case TaggedPDFCallback::e_ReportCategoryTocItem:
    sFormat = "Toc Item";
    break;
  default:
    break;
  }
  return sFormat;
}

static String GetReportConfidenceString(TaggedPDFCallback::ReportConfidence type) {
  String sFormat = "";
  switch (type) {
  case TaggedPDFCallback::e_ReportConfidenceHigh:
    sFormat = "High";
    break;
  case TaggedPDFCallback::e_ReportConfidenceMediumHigh:
    sFormat = "Medium High";
    break;
  case TaggedPDFCallback::e_ReportConfidenceMedium:
    sFormat = "Medium";
    break;
  case TaggedPDFCallback::e_ReportConfidenceMediumLow:
    sFormat = "Medium Low";
    break;
  case TaggedPDFCallback::e_ReportConfidenceLow:
    sFormat = "Low";
    break;
  default:
    break;
  }
  return sFormat;
}

struct AutoTag_ReportElemRectCon {
  CFX_FloatRect rcRect;
  TaggedPDFCallback::ReportConfidence eConfidence;
};

typedef vector<AutoTag_ReportElemRectCon*> ReportElemRectConArray;
typedef map<TaggedPDFCallback::ReportCategory, ReportElemRectConArray*> ReportElemMap;
typedef map<int, ReportElemMap*> ReportResultPagesMap;
class TaggedPDFCallbackImpl : public TaggedPDFCallback {
public:
  TaggedPDFCallbackImpl() {}

  ~TaggedPDFCallbackImpl() {
    ResetResult();
  }
  virtual void Release() {
    delete this;
  }

  virtual void Report(ReportCategory category, ReportConfidence confidence, int page_index, const RectF& rect) {
    cout << "Page Index: " << page_index << ", ReportCategory: " << (FX_LPCSTR)GetReportCategoryString(category)
      << ", ReportConfidence: " << (FX_LPCSTR)GetReportConfidenceString(confidence) << ", Rect: [" << rect.left
      << ", " << rect.top << ", " << rect.right << ", " << rect.bottom << "]" << endl;

    AutoTag_ReportElemRectCon* pRectCon = new AutoTag_ReportElemRectCon();
    pRectCon->rcRect = rect;
    pRectCon->eConfidence = confidence;

    ReportElemMap* pElemMap = NULL;
    ReportElemRectConArray* pArray = NULL;

    ReportResultPagesMap::iterator it = result_map_.find(page_index);
    if (it == result_map_.end()) {
      pArray = new ReportElemRectConArray();
      pArray->push_back(pRectCon);
      pElemMap = new ReportElemMap();
      pElemMap->insert(ReportElemMap::value_type(category, pArray));
      result_map_.insert(ReportResultPagesMap::value_type(page_index, pElemMap));
    }
    else {
      pElemMap = it->second;
      ReportElemMap::iterator iter = pElemMap->find(category);
      if (iter != pElemMap->end()) {
        pArray = iter->second;
        pArray->push_back(pRectCon);
      }
      else {
        pArray = new ReportElemRectConArray();
        pArray->push_back(pRectCon);
        pElemMap->insert(ReportElemMap::value_type(category, pArray));
      }
    }
  }

  ReportResultPagesMap& GetResult() {
    return result_map_;
  }

  void ResetResult() {
    for (auto iter = result_map_.begin(); iter != result_map_.end(); ++iter) {
      auto item = iter->second;
      for (auto iter_category = item->begin(); iter_category != item->end(); ++iter_category) {
        delete iter_category->second;
      }
      item->clear();
      delete item;
    }
    result_map_.clear();
  }

private:
  ReportResultPagesMap result_map_;
};

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"taggedpdf/";
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
      WString output_file_path = output_directory + L"TaggedPdf_StartAutoTagged.pdf";

      PDFDoc pdfDoc(input_file);
      pdfDoc.Load();
      TaggedPDF taggedpdf(pdfDoc);
      Progressive progressive = taggedpdf.StartTagDocument(NULL);
      Progressive::State progressState = Progressive::e_ToBeContinued;
      while (Progressive::e_ToBeContinued == progressState)
        progressState = progressive.Continue();

      pdfDoc.SaveAs(output_file_path);
    }
    {//use callback
      WString output_file_path = output_directory + L"TaggedPdf_StartAutoTagged_SetCallback.pdf";

      PDFDoc pdfDoc(input_file);
      pdfDoc.Load();
      TaggedPDF taggedpdf(pdfDoc);
      TaggedPDFCallbackImpl* callback = new TaggedPDFCallbackImpl();
      taggedpdf.SetCallback(callback);
      Progressive progressive = taggedpdf.StartTagDocument(NULL);
      auto progressState = Progressive::e_ToBeContinued;
      while (Progressive::e_ToBeContinued == progressState)
        progressState = progressive.Continue();
      pdfDoc.SaveAs(output_file_path);
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

