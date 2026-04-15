/**
 * Copyright (C) 2003-2026, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software Inc.. It is not allowed to
 * distribute any parts of Foxit PDF SDK to third party or public without permission unless an agreement
 * is signed between Foxit Software Inc. and customers to explicitly grant customers permissions.
 *
 * @file fs_office2pdf.h
 * @brief Header file for Office2PDF related definitions and classes.
 */
#ifndef FS_OFFICE2PDF_H_
#define FS_OFFICE2PDF_H_
#if defined(_WIN32) || defined(_WIN64) || (defined(__linux__) && (defined(__i386__) || defined(__x86_64__)) && !defined(__ANDROID__))
#include "common/fs_common.h"

/**
* @brief Foxit namespace.
*
* @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
*/
namespace foxit {
/**
 * @brief Add-on namespace.
 */
namespace addon {
/**
 * @brief Conversion namespace.
 */
namespace conversion {
/**
 * @brief pdf2office namespace.
 */
namespace office2pdf {
/** This class represents setting data used for converting Word format files to PDF format files. */
  class Word2PDFConfig FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  Word2PDFConfig()
    : is_generate_bookmark(false) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] is_generate_bookmark  A boolean value which indicates whether to export bookmarks to converted PDF file.
   */
  Word2PDFConfig(bool is_generate_bookmark) {
    this->is_generate_bookmark = is_generate_bookmark;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another PDF-to-Word setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Word2PDFConfig & operator = (const Word2PDFConfig & data) {
    is_generate_bookmark = data.is_generate_bookmark;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] is_generate_bookmark  A boolean value which indicates whether to export bookmarks to converted PDF file.
   * @return None.
   */
  void Set(bool is_generate_bookmark) {
    this->is_generate_bookmark = is_generate_bookmark;
  }

  /**
   * @brief A boolean value which indicates whether to export bookmarks to converted PDF file.
   *
   * @details <b>true</b> means to export bookmarks to converted PDF file, while <b>false</b> means not.
   *          Default value: <b>false</b>.
   */
  bool is_generate_bookmark;
};

/** This class represents setting data used for converting Excel format files to PDF format files. */
class Excel2PDFConfig FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  Excel2PDFConfig()
    : is_separate_workbook(false)
    , is_output_hidden_worksheets(false) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] is_separate_workbook         A boolean value which indicates whether to export worksheets to separate PDF files.
   * @param[in] is_output_hidden_worksheets  A boolean value which indicates whether to output the hidden worksheets.
   * @param[in] worksheet_names              An array of specific worksheet names to be converted to PDF files.
   */
  Excel2PDFConfig(bool is_separate_workbook, bool is_output_hidden_worksheets, foxit::WStringArray worksheet_names) {
    this->is_separate_workbook = is_separate_workbook;
    this->is_output_hidden_worksheets = is_output_hidden_worksheets;
    this->worksheet_names = worksheet_names;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another Excel-to-PDF setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Excel2PDFConfig & operator = (const Excel2PDFConfig & data) {
    is_separate_workbook = data.is_separate_workbook;
    is_output_hidden_worksheets = data.is_output_hidden_worksheets;
    worksheet_names = data.worksheet_names;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] is_separate_workbook         A boolean value which indicates whether to export worksheets to separate PDF files.
   * @param[in] is_output_hidden_worksheets  A boolean value which indicates whether to output the hidden worksheets.
   * @param[in] worksheet_names              An array of specific worksheet names to be converted to PDF files.
   *
   * @return None.
   */
  void Set(bool is_separate_workbook, bool is_output_hidden_worksheets, foxit::WStringArray worksheet_names) {
    this->is_separate_workbook = is_separate_workbook;
    this->is_output_hidden_worksheets = is_output_hidden_worksheets;
    this->worksheet_names = worksheet_names;
  }

  /**
   * @brief A boolean value which indicates whether to export worksheets to separate PDF files.
   * 
   * @details <b>true</b> means to export each worksheet to separate PDF files, while <b>false</b> means not.
   */
  bool is_separate_workbook;

  /**
   * @brief A boolean value which indicates whether to output the hidden worksheets.
   * 
   * @details <b>true</b> means to output the hidden worksheets, while <b>false</b> means not.
   */
  bool is_output_hidden_worksheets;

  /**
   * @brief An array of specific worksheet names to be converted to PDF files.
   * 
   * @details If this array is empty, all worksheets will be converted to PDF files.
   */
  foxit::WStringArray worksheet_names;
};

/** This class represents setting data used for converting Office(Word, Excel or PowerPoint) to PDF format file. */
class Office2PDFSettingData FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  Office2PDFSettingData()
    : is_embed_font(false){}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] resource_folder_path  A valid path of a folder which contains resource data files. This should not be an empty string.
   *                                  These resource data files are used to simulate the pdf format document typesetting process during conversion.
   *                                  They are offered in the "res/office2pdf" folder of the Foxit PDF Conversion SDK package.
   * @param[in] is_embed_font         <b>true</b> means to embed font in the converted file, while <b>false</b> means not.
   * @param[in] word_setting_data     A setting data object that used for converting Word format documents to PDF format documents.
   * @param[in] excel_setting_data    A setting data object that used for converting Excel format documents to PDF format documents.
   */
  Office2PDFSettingData(const wchar_t* resource_folder_path, bool is_embed_font, Word2PDFConfig word_setting_data, Excel2PDFConfig excel_setting_data) {
    this->resource_folder_path = resource_folder_path;
    this->is_embed_font = is_embed_font;
    this->word_setting_data = word_setting_data;
    this->excel_setting_data = excel_setting_data;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another Office-to-PDF setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Office2PDFSettingData &operator = (const Office2PDFSettingData& data) {
    resource_folder_path = data.resource_folder_path;
    is_embed_font = data.is_embed_font;
    word_setting_data = data.word_setting_data;
    excel_setting_data = data.excel_setting_data;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] resource_folder_path  A valid path of a folder which contains resource data files. This should not be an empty string.
   *                                  These resource data files are used to simulate the pdf format document typesetting process during conversion.
   *                                  They are offered in the "res/office2pdf" folder of the Foxit PDF Conversion SDK package.
   * @param[in] is_embed_font         <b>true</b> means to embed font in the converted file, while <b>false</b> means not.
   * @param[in] word_setting_data     A setting data object that used for converting Word format documents to PDF format documents.
   * @param[in] excel_setting_data    A setting data object that used for converting Excel format documents to PDF format documents.
   *
   * @return None.
   */
  void Set(const wchar_t* resource_folder_path, bool is_embed_font, Word2PDFConfig word_setting_data, Excel2PDFConfig excel_setting_data) {
    this->resource_folder_path = resource_folder_path;
    this->is_embed_font = is_embed_font;
    this->word_setting_data = word_setting_data;
    this->excel_setting_data = excel_setting_data;
  }

  /**
   * @brief A valid path of a folder which contains resource data files. This should not be an empty string.
   *
   * @details These resource data files are used to simulate the pdf format document typesetting process during conversion.
   *          They are offered in the "res/office2pdf" folder of the Foxit PDF Conversion SDK package.
   */
  WString resource_folder_path;

  /**
   * @brief A boolean value which indicates whether to embed font in the converted file,Default value: <b>false</b>.
   *
   * @details <b>true</b> means to embed font in the converted file, while <b>false</b> means not. 
   *
   */
  bool is_embed_font;

  /**
   * @brief A setting data object that used for converting Word format documents to PDF format documents.
   *
   * @details This setting is only vaild for the conversion of Word documents to PDF format documents.
   *          For more details, please refer to class @link Word2PDFConfig @endlink.
   */
  Word2PDFConfig word_setting_data;

  /**
   * @brief A setting data object that used for converting Excel format documents to PDF format documents.
   *
   * @details This setting is only vaild for the conversion of Excel documents to PDF format documents.
   *          For more details, please refer to class @link Excel2PDFConfig @endlink.
   */
  Excel2PDFConfig excel_setting_data;
};

/**
 * This class can be used to convert Office(Word, Excel or PowerPoint) format files to PDF files.
 * This feature is a self-developed product by Foxit and does not rely on other third-party engines.
 * Before using "Conversion" module, please ensure the resource folders named "res" and "lib" in the
 * Foxit PDF Conversion SDK package is valid.
 * Before using methods in this module, please ensure Foxit PDF SDK has been initialized successfully
 * by function @link common::Library::Initialize @endlink with a key including "Office2PDF" module.
 *
 * @see @link common::Library @endlink
 */
class Office2PDF FS_FINAL : public Base{
 public:
  /**
   * @brief Initialize Foxit PDF Conversion.
   *
   * @details During the life-cycle of "Office2PDF" module, this function can only be called once and
   *          should be called first before any other functions in "Office2PDF" module can be called.
   *
   * @param[in] library_path  Path of Foxit PDF Conversion SDK library. This should not be an empty string.
   * 
   * @return None.
   *
   * @note If module "Office2PDF" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using Office2PDF related functions and
   *       this function will throw exception @link foxit::e_ErrNoOffice2PDFModuleRight @endlink.
   */
  static void Initialize(const wchar_t* library_path);

  /**
   * @brief Release all resource allocated by Foxit PDF Conversion.
   *
   * @details When the user does not use "Office2PDF" module, this function should be called to release all memory blocks allocated by the library.
   *
   * @return None.
   */
  static void Release();

  /**
   * @brief Get the version of Foxit PDF Conversion SDK.
   * 
   * @details This function should be called after the function @link Office2PDF::Initialize @endlink has been called successfully.
   * 
   * @return A string which contains the version information of Foxit PDF Conversion SDK.
   */
  static String GetVersion();

  /**
   * @brief Convert a Word format file to a PDF file.
   *
   * @details Currently,this function is only available for Windows and Linux (32 bit and 64 bit), and it supports conversion from DOCX/DOC format files.
   *
   * @param[in] src_word_file_path  Path of a Word format file. This should not be an empty string.
   * @param[in] src_file_password   (Reserved,encrypted files are unsupported yet)Password for the input Word format file. If no password is needed for the file,
   *                                please pass an empty string.
   * @param[in] saved_pdf_path      Path of the saved PDF file as conversion result. This should not be an empty string.
   * @param[in] setting_data        A @link conversion::office2pdf::Office2PDFSettingData @endlink object which is used for converting.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool ConvertFromWord(const wchar_t* src_word_file_path, const wchar_t* src_file_password, const wchar_t* saved_pdf_path, const Office2PDFSettingData& setting_data);

  /**
   * @brief Convert a Word format file to a PDF file.
   *
   * @details Currently,this function is only available for Windows and Linux (32 bit and 64 bit), and it supports conversion from DOCX/DOC format files.
   *                 The file is read all at once, rather than progressively.
   *
   * @param[in] src_word_reader        A @link ReaderCallback @endlink object which is implemented by user to
   *                                   load a word document. It should not be <b>NULL</b>.
   *
   * @param[in] src_file_password      (Reserved,encrypted files are unsupported yet)Password for the input Word format file. If no password is needed for the file,
   *                                   please pass an empty string.
   * @param[in] saved_pdf_file_stream  A @link foxit::common::file::StreamCallback @endlink object which is implemented by user
   *                                   to read the contents of the converted PDF file. It should not be <b>NULL</b>.
   * @param[in] setting_data           A @link conversion::office2pdf::Office2PDFSettingData @endlink object which is used for converting.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool ConvertFromWord(common::file::ReaderCallback* src_word_reader, const wchar_t* src_file_password, common::file::StreamCallback* saved_pdf_file_stream, const Office2PDFSettingData& setting_data);

  /**
   * @brief Convert an Excel format file to a PDF file.
   *
   * @details Currently,this function is only available for Windows and Linux (32 bit and 64 bit), and it supports conversion only from XLSX format files.
   *
   * @param[in] src_excel_file_path  Path of an Excel format file. This should not be an empty string.
   * @param[in] src_file_password    (Reserved,encrypted files are unsupported yet)Password for the input Excel format file. If no password is needed for the file,
   *                                 please pass an empty string.
   * @param[in] saved_pdf_path       Path of the saved PDF file as conversion result. This should not be an empty string.
   * @param[in] setting_data         A @link conversion::office2pdf::Office2PDFSettingData @endlink object which is used for converting.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool ConvertFromExcel(const wchar_t* src_excel_file_path, const wchar_t* src_file_password, const wchar_t* saved_pdf_path, const Office2PDFSettingData& setting_data);

  /**
   * @brief Convert an Excel format file to a PDF file.
   *
   * @details Currently,this function is only available for Windows and Linux (32 bit and 64 bit), and it supports conversion only from XLSX format files.
   *                The file is read all at once, rather than progressively.
   *
   * @param[in] src_excel_reader       A @link ReaderCallback @endlink object which is implemented by user to
   *                                   load an excel document. It should not be <b>NULL</b>.
   * @param[in] src_file_password     (Reserved,encrypted files are unsupported yet)Password for the input Excel format file. If no password is needed for the file,
   *                                   please pass an empty string.
   * @param[in] saved_pdf_file_stream  A @link foxit::common::file::StreamCallback @endlink object which is implemented by user
   *                                   to read the contents of the converted PDF file. It should not be <b>NULL</b>.
   * @param[in] setting_data           A @link conversion::office2pdf::Office2PDFSettingData @endlink object which is used for converting.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool ConvertFromExcel(common::file::ReaderCallback* src_excel_reader, const wchar_t* src_file_password, common::file::StreamCallback* saved_pdf_file_stream, const Office2PDFSettingData& setting_data);

  /**
   * @brief Convert a PowerPoint format file to a PDF file.
   *
   * @details Currently,this function is only available for Windows and Linux (32 bit and 64 bit), and it supports conversion only from PPTX format files.
   *
   * @param[in] src_ppt_file_path  Path of a PowerPoint format file. This should not be an empty string.
   * @param[in] src_file_password  (Reserved,encrypted files are unsupported yet)Password for the input PowerPoint format file. If no password is needed for the file,
   *                               please pass an empty string.
   * @param[in] saved_pdf_path     Path of the saved PDF file as conversion result. This should not be an empty string.
   * @param[in] setting_data       A @link conversion::office2pdf::Office2PDFSettingData @endlink object which is used for converting.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool ConvertFromPowerPoint(const wchar_t* src_ppt_file_path, const wchar_t* src_file_password, const wchar_t* saved_pdf_path, const Office2PDFSettingData& setting_data);

  /**
   * @brief Convert a PowerPoint format file to a PDF file.
   *
   * @details Currently,this function is only available for Windows and Linux (32 bit and 64 bit), and it supports conversion only from PPTX format files.
   *                The file is read all at once, rather than progressively.
   *
   * @param[in] src_ppt_reader         A @link ReaderCallback @endlink object which is implemented by user to
   *                                   load a PowerPoint document. It should not be <b>NULL</b>.
   * @param[in] src_file_password     (Reserved,encrypted files are unsupported yet)Password for the input PowerPoint format file. If no password is needed for the file,
   *                                   please pass an empty string.
   * @param[in] saved_pdf_file_stream  A @link foxit::common::file::StreamCallback @endlink object which is implemented by user
   *                                   to read the contents of the converted PDF file. It should not be <b>NULL</b>.
   * @param[in] setting_data           A @link conversion::office2pdf::Office2PDFSettingData @endlink object which is used for converting.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool ConvertFromPowerPoint(common::file::ReaderCallback* src_ppt_reader, const wchar_t* src_file_password, common::file::StreamCallback* saved_pdf_file_stream, const Office2PDFSettingData& setting_data);
};
}  // namespace office2pdf
}  // namespace conversion
}  // namespace addon
}  // namespace foxit

#endif //defined(_WIN32) || defined(_WIN64)
#endif
