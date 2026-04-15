// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to create or open a portfolio PDF file.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_filespec.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_portfolio.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace portfolio;

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

class TextDoc {
public:
  TextDoc(const String& file_name, const String& fill_mode);
  TextDoc(const WString& file_name, const WString& fill_mode);
  ~TextDoc();
  void Write(const char* format, ...);
  void Write(int count, const char* prefix, const char* format, ...);

private:
  FILE* file_;
};

TextDoc::TextDoc(const String& file_name, const String& file_mode) throw(Exception) : file_(NULL) {
#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, (const char*)file_name, (const char*)file_mode);
#else
  file_ = fopen((const char*)file_name, (const char*)file_mode);
#endif

  if (!file_)
    throw Exception(__FILE__, __LINE__, __FUNCTION__, foxit::e_ErrFile);
}

TextDoc::TextDoc(const WString& file_name, const WString& file_mode) throw(Exception)  : file_(NULL) {
  String s_file_name = String::FromUnicode(file_name);
  String s_file_mode = String::FromUnicode(file_mode);

#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&file_, (const char*)s_file_name, (const char*)s_file_mode);
#else
  file_ = fopen((const char*)s_file_name, (const char*)s_file_mode);
#endif
  if (!file_)
    throw Exception(__FILE__, __LINE__, __FUNCTION__, foxit::e_ErrFile);
}

TextDoc::~TextDoc() {
  fclose(file_);
  file_ = NULL;
}

void TextDoc::Write(const char* format, ...) {
  va_list vars;
  if (file_) {
    // Get variable list
    va_start(vars, format);
    // Call vfprintf to format log data and output to log file
    vfprintf(file_, format, vars);
    // End variable list
    va_end(vars);
  }
}

void TextDoc::Write(int count, const char * prefix, const char * format, ...) {
  for (int i = 0; i < count; i++) {
    Write("%s", prefix);
  }
  va_list vars;
  if (file_) {
    // Get variable list
    va_start(vars, format);
    // Call vfprintf to format log data and output to log file
    vfprintf(file_, format, vars);
    // End variable list
    va_end(vars);
  }
}

bool CreatPortfolioPDF(const WString& saved_portfolio_pdf_path) {
  // Create a new blank portfolio PDF.
  Portfolio new_portfolio = Portfolio::CreatePortfolio();
  if (true == new_portfolio.IsEmpty()) {
    printf("[FAILED] Fail to create a new portfolio PDF.\r\n");
    return false;
  }

  // Get the root node.
  PortfolioNode root_node = new_portfolio.GetRootNode();
  if (true == root_node.IsEmpty()) {
    printf("[FAILED] Fail to get the root node.\r\n");
    return false;
  }
  // The root node should be a folder node, so transfer to use PortfolioFolderNode.
  PortfolioFolderNode root_folder(root_node);

  // Pre-load the PDF file which is to be added to new sub folder in portfolio PDF.
  // ATTENTION: please keep the PDF document object valid until portfolio PDF is saved or ends its life-cycle.
  WString input_pdf_filename = L"AboutFoxit.pdf";
  WString input_pdf_file_path = input_path + input_pdf_filename;
  PDFDoc pdf_doc(input_pdf_file_path);
  ErrorCode error_code = pdf_doc.Load();
  if (error_code != foxit::e_ErrSuccess) {
    printf("[FAILED] Fail to load PDF file %s. Error: %d\n", (const char*)String::FromUnicode(input_pdf_file_path), error_code);
  }

  // Add a sub folder to root folder node.
  PortfolioFolderNode new_sub_foldernode = root_folder.AddSubFolder(L"Sub Folder-1");
  if (true == new_sub_foldernode.IsEmpty()) {
    printf("[FAILED] Fail to add sub folder.\r\n");
  } else {
    new_sub_foldernode.SetDescription(L"This is a sub folder added to portfolio PDF file.");

    if (false == pdf_doc.IsEmpty()) {
      // Add a valid PDF document object to current folder node.
      // ATTENTION: please keep the PDF document object valid until portfolio PDF is saved or ends its life-cycle.
      PortfolioFileNode new_filenode = new_sub_foldernode.AddPDFDoc(pdf_doc, (const wchar_t*)input_pdf_filename);
      if (true == new_filenode.IsEmpty()) {
        printf("[FAILED] Fail to add PDF file %s.\r\n", (const char*)String::FromUnicode(input_pdf_file_path));
      } else {
        FileSpec file_spec = new_filenode.GetFileSpec();
        file_spec.SetDescription("This is a common PDF file added to portfolio PDF file");
      }
    }
  }


  // Add a non-PDF file to root folder node.
  WString input_file_path = input_path + L"FoxitLogo.jpg";
  PortfolioFileNode new_sub_filenode = root_folder.AddFile((const wchar_t*)input_file_path);
  if (true == new_sub_filenode.IsEmpty()) {
    printf("[FAILED] Fail to add file %s.\r\n", (const char*)String::FromUnicode(input_file_path));
  } else {
    FileSpec file_spec = new_sub_filenode.GetFileSpec();
    file_spec.SetDescription("This is a non-PDF file added to portfolio PDF file.");
  }
  
  // User can update schema field and other properties by class Portfolio, if necessary.
  
  // Save the new portfolio PDF file.
  PDFDoc portfolio_pdf_doc = new_portfolio.GetPortfolioPDFDoc();
  if (true == portfolio_pdf_doc.IsEmpty()) {
    printf("[FAILED] Fail to get portfolio PDF document object.\r\n");
    return false;
  } else {
    return portfolio_pdf_doc.SaveAs((const wchar_t*)saved_portfolio_pdf_path, PDFDoc::e_SaveFlagNormal);
  }
}

void OutputTab(TextDoc& output_txt_doc, int nTabCount) {
  for (int i = 0; i<nTabCount; i++)
    output_txt_doc.Write("\t");
}

void OutputFileNodeInfo(TextDoc& output_txt_doc, const PortfolioFileNode& node, int tab_count) {
  if (tab_count>0)
    OutputTab(output_txt_doc, tab_count);
  output_txt_doc.Write("Type:File\r\n");

  PortfolioFileNode temp_node(node);
  WString key_name = temp_node.GetKeyName();
  if (tab_count>0)
    OutputTab(output_txt_doc, tab_count);
  output_txt_doc.Write("Key Name:%s\r\n", (const char*)String::FromUnicode(key_name));

  FileSpec file_spec = temp_node.GetFileSpec();
  WString file_name = file_spec.GetFileName();
  if (tab_count>0)
      OutputTab(output_txt_doc, tab_count);
  output_txt_doc.Write("File Name:%s\r\n", (const char*)String::FromUnicode(file_name));

  String description = file_spec.GetDescription();
  if (tab_count>0)
    OutputTab(output_txt_doc, tab_count);
  output_txt_doc.Write("Description:%s\r\n", (const char*)description);
}

void OutputSubNodesInfo(TextDoc& output_txt_doc, const PortfolioNodeArray& sub_nodes, int tab_count);

void OutputFolderNodeInfo(TextDoc& output_txt_doc, const PortfolioFolderNode& node, int tab_count) {
  if (tab_count>0)
    OutputTab(output_txt_doc, tab_count);
  output_txt_doc.Write("Type:Folder\r\n");

  PortfolioFolderNode temp_node(node);
  WString name = temp_node.GetName();
  if (tab_count>0)
    OutputTab(output_txt_doc, tab_count);
  output_txt_doc.Write("Name:%s\r\n", (const char*)String::FromUnicode(name));

  WString description = temp_node.GetDescription();
  if (tab_count>0)
    OutputTab(output_txt_doc, tab_count);
  output_txt_doc.Write("Description:%s\r\n", (const char*)String::FromUnicode(description));

  PortfolioNodeArray sub_nodes = temp_node.GetSortedSubNodes();
  OutputSubNodesInfo(output_txt_doc, sub_nodes, tab_count + 1);
}

void OutputNodeInfo(TextDoc& output_txt_doc, const PortfolioNode& node, int tab_count) {
  switch (PortfolioNode(node).GetNodeType()) {
    case PortfolioNode::e_TypeFolder:
      OutputFolderNodeInfo(output_txt_doc, PortfolioFolderNode(node), tab_count);
      break;
    case PortfolioNode::e_TypeFile:
      OutputFileNodeInfo(output_txt_doc, PortfolioFileNode(node), tab_count);
      break;
    default:
      break;
  }
}

void OutputSubNodesInfo(TextDoc& output_txt_doc, const PortfolioNodeArray& sub_nodes, int tab_count) {
  for (size_t index = 0; index < sub_nodes.GetSize(); index++) {
    if (tab_count > 0)
      OutputTab(output_txt_doc, tab_count);
    output_txt_doc.Write("Sorted Index (under current folder):%d\r\n", index);
    OutputNodeInfo(output_txt_doc, sub_nodes[index], tab_count);
    output_txt_doc.Write("========\r\n");
  }
}

void OutputSchemaFields(TextDoc& output_txt_doc, const SchemaFieldArray& field_array) {
  if (field_array.GetSize() <= 0) return;
  output_txt_doc.Write("==== Schema Fields ====\r\n");

  for (size_t i = 0; i < field_array.GetSize(); i++) {
    output_txt_doc.Write("Field index:%d\r\n", i);
    SchemaField field = field_array[i];
    if (true == field.IsEmpty()) continue;
    foxit::String key_name = field.GetKeyName();
    output_txt_doc.Write("Key name: %s\r\n", (const char*)key_name);

    foxit::String subtype_name = field.GetSubtypeName();
    output_txt_doc.Write("Subtype name: %s\r\n", (const char*)subtype_name);

    foxit::WString display_name = field.GetDisplayName();
    output_txt_doc.Write("Display name: %s\r\n", (const char*)String::FromUnicode(display_name));

    bool is_visible = field.IsVisible();
    output_txt_doc.Write("Visibility: %s\r\n", is_visible ? "true" : "false");

    output_txt_doc.Write("========\r\n");
  }
}

void OutputPortfolioProperties(TextDoc& output_txt_doc, const Portfolio& portfolio) {
  output_txt_doc.Write("==== Portfolio Properties ====\r\n");
  WString initial_filespec_keyname = portfolio.GetInitialFileSpecKeyName();
  output_txt_doc.Write("Initial FileSpec Key Name:%s\r\n", (const char*)String::FromUnicode(initial_filespec_keyname));

  Portfolio::InitialViewMode view_mode = portfolio.GetInitialViewMode();
  String view_mode_str = "";
  switch (view_mode) {
    case Portfolio::e_InitialViewUnknownMode:
      view_mode_str = "Unknown";
      break;
    case Portfolio::e_InitialViewDetailMode:
      view_mode_str = "Detail";
      break;
    case Portfolio::e_InitialViewTileMode:
      view_mode_str = "Tile";
      break;
    case Portfolio::e_InitialViewHidden:
      view_mode_str = "Hidden";
      break;
  }
  output_txt_doc.Write("Initial View Mode:%s\r\n", (const char*)view_mode_str);


  bool is_ascending = portfolio.IsSortedInAscending();
  output_txt_doc.Write("Sorting Order:%s\r\n", is_ascending? "Ascending" : "Descending" );

  String sorting_field_name = portfolio.GetSortingFieldKeyName();
  output_txt_doc.Write("Sorting Field Key Name:%s\r\n", (const char*)sorting_field_name);


  SchemaFieldArray field_array = portfolio.GetSchemaFields();
  OutputSchemaFields(output_txt_doc, field_array);
}

void OutputPortfolioPDFInfo(const WString& portfolio_file_path, TextDoc& output_txt_doc) {
  PDFDoc pdf_doc((const wchar_t*)portfolio_file_path);
  ErrorCode error_code = pdf_doc.Load();
  if (error_code != foxit::e_ErrSuccess) {
    printf("[FAILED] Fail to load Portfolio PDF file %s. Error: %d\n", (const char*)String::FromUnicode(portfolio_file_path), error_code);
    return;
  }

  if (false == pdf_doc.IsPortfolio()) {
    printf("[FAILED] Fail to output portfolio information for PDF file %s, because it is not a portfolio PDF file.\r\n", (const char*)String::FromUnicode(portfolio_file_path));
    return;
  }

  Portfolio exist_portfolio = Portfolio::CreatePortfolio(pdf_doc);
  if (true == exist_portfolio.IsEmpty()) {
    printf("[FAILED] Fail to create a portfolio object based an existed portfolio PDF document.\r\n");
    return;
  }

  // Output portfolio properties.
  OutputPortfolioProperties(output_txt_doc, exist_portfolio);
  output_txt_doc.Write("======================================================================\r\n");

  // Output all nodes.
  output_txt_doc.Write("==== Nodes Information ====\r\n");
  PortfolioNode root_node = exist_portfolio.GetRootNode();
  PortfolioFolderNode root_folder(root_node);
  PortfolioNodeArray sub_nodes = root_folder.GetSortedSubNodes();
  OutputSubNodesInfo(output_txt_doc, sub_nodes, 0);
}

int main(int argc, char *argv[])
{
  int err_ret = 0;

  WString output_directory = output_path + L"portfolio/";
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
    WString saved_portfolio_pdf_path = output_directory + L"new_portfolio.pdf";
    // Create a new portfolio PDF file
    if (CreatPortfolioPDF(saved_portfolio_pdf_path)) {
      WString output_info_file_path = output_directory + L"new_portfolio_info.txt";
      TextDoc text_doc(output_info_file_path, L"w+b");
      // Show information of the new portfolio PDF file.
      OutputPortfolioPDFInfo(saved_portfolio_pdf_path, text_doc);
    }

    printf("END: Portfolio demo.\r\n");

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

