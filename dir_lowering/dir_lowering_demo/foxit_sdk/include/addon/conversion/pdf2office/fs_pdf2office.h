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
 * @file fs_pdf2office.h
 * @brief Header file for PDF2Office related definitions and classes.
 */
#ifndef FS_PDF2OFFICE_H_
#define FS_PDF2OFFICE_H_
#if defined(_WIN32) || defined(_WIN64) || (defined(__linux__) && !defined(__ANDROID__))
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
namespace pdf2office {
/** This class represents setting data used for converting PDF documents to Word format documents. */
class PDF2WordSettingData FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  PDF2WordSettingData()
    : enable_retain_page_layout(false)
    , enable_generate_headers_and_footers(true)
    , enable_generate_footnotes_and_endnotes(false)
    , enable_generate_page_rendered_break(false)
    , max_blank_paragraphs_per_page_bottom(-1) { }

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] enable_retain_page_layout               A boolean value which indicates whether retain page layout for the conversion of PDF documents to Word format documents. Default value: <b>false</b>.
   *                                                    <b>true</b> means to retain page layout for the conversion of PDF documents to Word format documents.
   *                                                    <b>false</b> means not to retain page layout for the conversion of PDF documents to Word format documents.
   * @param[in] enable_generate_headers_and_footers     A boolean value which indicates whether convert the recognized headers and footers from PDF documents to headers and footers of Word format documents
   *                                                    during the conversion of PDF documents to Word format documents. Default value: <b>true</b>.
   *                                                    <b>true</b> means to convert the recognized headers and footers from PDF documents to headers and footers of Word format documents.
   *                                                    <b>false</b> means to convert the recognized headers and footers from PDF documents to the main texts or text boxes of Word format documents.
   * @param[in] enable_generate_footnotes_and_endnotes  A boolean value which indicates whether convert the recognized footnotes and endnotes from PDF documents to footnotes and endnotes of Word format documents
   *                                                    during the conversion of PDF documents to Word format documents. Default value: <b>false</b>.
   *                                                    <b>true</b> means to convert the recognized footnotes and endnotes from PDF documents to footnotes and endnotes of Word format documents.
   *                                                    <b>false</b> means to convert the recognized footnotes and endnotes from PDF documents to the main texts or text boxes of Word format documents.
   *                                                    Default value:<b>false</b>.
   * @param[in] enable_generate_page_rendered_break     A boolean value which indicates whether to generate the "lastRenderedPageBreak" marker
   *                                                    in word format documents during the conversion of PDF documents to Word format documents.
   * @param[in] max_blank_paragraphs_per_page_bottom    Specifies the maximum number of blank paragraphs that can be placed at the bottom of each page when converting PDF files to Word documents.
   */
  PDF2WordSettingData(bool enable_retain_page_layout, bool enable_generate_headers_and_footers, bool enable_generate_footnotes_and_endnotes, bool enable_generate_page_rendered_break, int max_blank_paragraphs_per_page_bottom) {
    this->enable_retain_page_layout = enable_retain_page_layout;
    this->enable_generate_headers_and_footers = enable_generate_headers_and_footers;
    this->enable_generate_footnotes_and_endnotes = enable_generate_footnotes_and_endnotes;
    this->enable_generate_page_rendered_break = enable_generate_page_rendered_break;
    this->max_blank_paragraphs_per_page_bottom = max_blank_paragraphs_per_page_bottom;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another PDF-to-Word setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDF2WordSettingData & operator = (const PDF2WordSettingData & data) {
    enable_retain_page_layout = data.enable_retain_page_layout;
    enable_generate_headers_and_footers = data.enable_generate_headers_and_footers;
    enable_generate_footnotes_and_endnotes = data.enable_generate_footnotes_and_endnotes;
    enable_generate_page_rendered_break = data.enable_generate_page_rendered_break;
    max_blank_paragraphs_per_page_bottom = data.max_blank_paragraphs_per_page_bottom;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] enable_retain_page_layout               A boolean value which indicates whether retain page layout for the conversion of PDF documents to Word format documents. Default value: <b>false</b>.
   *                                                    <b>true</b> means to retain page layout for the conversion of PDF documents to Word format documents.
   *                                                    <b>false</b> means not to retain page layout for the conversion of PDF documents to Word format documents.
   * @param[in] enable_generate_headers_and_footers     A boolean value which indicates whether convert the recognized headers and footers from PDF documents to headers and footers of Word format documents
   *                                                    during the conversion of PDF documents to Word format documents. Default value: <b>true</b>.
   *                                                    <b>true</b> means to convert the recognized headers and footers from PDF documents to headers and footers of Word format documents.
   *                                                    <b>false</b> means to convert the recognized headers and footers from PDF documents to the main texts or text boxes of Word format documents.
   * @param[in] enable_generate_footnotes_and_endnotes  A boolean value which indicates whether convert the recognized footnotes and endnotes from PDF documents to footnotes and endnotes of Word format documents
   *                                                    during the conversion of PDF documents to Word format documents. Default value: <b>false</b>.
   *                                                    <b>true</b> means to convert the recognized footnotes and endnotes from PDF documents to footnotes and endnotes of Word format documents.
   *                                                    <b>false</b> means to convert the recognized footnotes and endnotes from PDF documents to the main texts or text boxes of Word format documents.
   *                                                    Default value:<b>false</b>.
   * @param[in] enable_generate_page_rendered_break     A boolean value which indicates whether to generate the "lastRenderedPageBreak" marker
   *                                                    in word format documents during the conversion of PDF documents to Word format documents.
   * @param[in] max_blank_paragraphs_per_page_bottom    Specifies the maximum number of blank paragraphs that can be placed at the bottom of each page when converting PDF files to Word documents.
   * 
   * @return None.
   */
  void Set(bool enable_retain_page_layout, bool enable_generate_headers_and_footers, bool enable_generate_footnotes_and_endnotes, bool enable_generate_page_rendered_break) {
    this->enable_retain_page_layout = enable_retain_page_layout;
    this->enable_generate_headers_and_footers = enable_generate_headers_and_footers;
    this->enable_generate_footnotes_and_endnotes = enable_generate_footnotes_and_endnotes;
    this->enable_generate_page_rendered_break = enable_generate_page_rendered_break;
    this->max_blank_paragraphs_per_page_bottom = max_blank_paragraphs_per_page_bottom;
  }

  /**
   * @brief A boolean value which indicates whether retain page layout for the conversion of PDF documents to Word format documents. Default value: <b>false</b>.
   *
   * @details <b>true</b> means to retain page layout for the conversion of PDF documents to Word format documents.
   *          <b>false</b> means not to retain page layout for the conversion of PDF documents to Word format documents.
   */
  bool enable_retain_page_layout;

  /**
   * @brief A boolean value which indicates whether convert the recognized headers and footers from PDF documents to headers and footers
   *        of word format documents during the conversion of PDF documents to word format documents. Default value: <b>true</b>.
   *
   * @details <b>true</b> means to convert the recognized headers and footers from PDF documents to headers and footers of word format documents.
   *          <b>false</b> means to convert the recognized headers and footers from PDF documents to the main texts or text boxes of word format documents.
   */
  bool enable_generate_headers_and_footers;

  /**
   * @brief A boolean value which indicates whether convert the recognized footnotes and endnotes from PDF documents to footnotes and endnotes
   *        of word format documents during the conversion of PDF documents to word format documents. Default value: <b>false</b>.
   *
   * @details <b>true</b> means to convert the recognized footnotes and endnotes from PDF documents to footnotes and endnotes of word format documents.
   *          <b>false</b> means to convert the recognized footnotes and endnotes from PDF documents to the main texts or text boxes of word format documents.
   */
  bool enable_generate_footnotes_and_endnotes;

  /**
   * @brief A boolean value which indicates whether to generate the "lastRenderedPageBreak" marker
   *        in word format documents during the conversion of PDF documents to Word format documents. Default value: <b>false</b>.
   *
   * @details If <b>true</b>, the "lastRenderedPageBreak" marker will be inserted into the Word document
   *          to denote the pagination position from the last PDF rendering. If <b>false</b>, the "lastRenderedPageBreak"
   *          marker will not be inserted. "lastRenderedPageBreak" is a marker that indicates the location of a page break 
   *          that was inserted when the document was last saved or rendered in an application. It is particularly useful 
   *          for applications that need to track where content was split across pages during the document's rendering process.
   */
  bool enable_generate_page_rendered_break;

  /**
   * @brief Specifies the maximum number of blank paragraphs that can be placed at the bottom of each page when converting PDF files to Word documents.
   *
   * @details This parameter controls the allowed number of empty paragraphs at the end of every page in the generated Word document.
   *          By setting this limit, users can prevent excessive empty space at the bottom of pages, thereby ensuring that the final
   *          document maintains a tidy and professional appearance without unnecessary blank lines that could affect layout and readability.
   *          Negative number indicates no limit on the number of blank paragraphs allowed at the bottom of each page.
   */
  int max_blank_paragraphs_per_page_bottom;
};

/** This class represents setting data used for converting PDF documents to Power Point format documents. */
class PDF2PowerPointSettingData FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  PDF2PowerPointSettingData()
    : enable_aggressively_split_sections(false)
    , enable_adapt_to_largest_page(false) { }

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] enable_aggressively_split_sections  A boolean value which indicates whether split sections aggressively for the conversion of PDF documents to Power Point format documents. Default value: <b>false</b>.
   *                                                In two paragraphs of the same text box, if the spacing between them is large enough, they will be split into two separate text boxes 
   *                                                for the conversion of PDF documents to Power Point format documents.
   *                                                <b>true</b> means to split sections aggressively for the conversion of PDF documents to Power Point format documents.
   *                                                <b>false</b> means not to split sections aggressively for the conversion of PDF documents to Power Point format documents.
   * @param[in] enable_adapt_to_largest_page        A boolean value that indicates whether adapt content of smaller pages to the largest page size during the conversion of PDF documents to PowerPoint format. Default value: <b>false</b>.
   *                                                Since all slides in a PowerPoint must have the same size, the largest page is used as the reference by default.
   *                                                When enabled, the converter identifies the largest page within the conversion range and adjusts the page matrix 
   *                                                of smaller pages accordingly, scaling their graphical objects to ensure uniform slide dimensions in the output PowerPoint file.
   *                                                All scaling operations preserve the original aspect ratio.
   *                                                <b>true</b> means to adapt content of smaller pages to the largest page size.
   *                                                <b>false</b> means not to adapt content of smaller pages to the largest page size.
   */
  PDF2PowerPointSettingData(bool enable_aggressively_split_sections, bool enable_adapt_to_largest_page) {
    this->enable_aggressively_split_sections = enable_aggressively_split_sections;
    this->enable_adapt_to_largest_page = enable_adapt_to_largest_page;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another PDF-to-Power-Point setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDF2PowerPointSettingData & operator = (const PDF2PowerPointSettingData & data) {
    enable_aggressively_split_sections = data.enable_aggressively_split_sections;
    enable_adapt_to_largest_page = data.enable_adapt_to_largest_page;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] enable_aggressively_split_sections  A boolean value which indicates whether split sections aggressively for the conversion of PDF documents to Power Point format documents. Default value: <b>false</b>.
   *                                                In two paragraphs of the same text box, if the spacing between them is large enough, they will be split into two separate text boxes 
   *                                                for the conversion of PDF documents to Power Point format documents.
   *                                                <b>true</b> means to split sections aggressively for the conversion of PDF documents to Power Point format documents.
   *                                                <b>false</b> means not to split sections aggressively for the conversion of PDF documents to Power Point format documents.
   * @param[in] enable_adapt_to_largest_page        A boolean value that indicates whether adapt content of smaller pages to the largest page size during the conversion of PDF documents to PowerPoint format. Default value: <b>false</b>.
   *                                                Since all slides in a PowerPoint must have the same size, the largest page is used as the reference by default.
   *                                                When enabled, the converter identifies the largest page within the conversion range and adjusts the page matrix 
   *                                                of smaller pages accordingly, scaling their graphical objects to ensure uniform slide dimensions in the output PowerPoint file.
   *                                                All scaling operations preserve the original aspect ratio.
   *                                                <b>true</b> means to adapt content of smaller pages to the largest page size.
   *                                                <b>false</b> means not to adapt content of smaller pages to the largest page size.
   *
   * @return None.
   */
  void Set(bool enable_aggressively_split_sections,  bool enable_adapt_to_largest_page) {
    this->enable_aggressively_split_sections = enable_aggressively_split_sections;
    this->enable_adapt_to_largest_page = enable_adapt_to_largest_page;
  }

  /**
   * @brief A boolean value which indicates whether split sections aggressively for the conversion of PDF documents to Power Point format documents. Default value: <b>false</b>.
   *
   * @details In two paragraphs of the same text box, if the spacing between them is large enough, they will be split into two separate text boxes 
   *          for the conversion of PDF documents to Power Point format documents.
   *          <b>true</b> means to split sections aggressively for the conversion of PDF documents to Power Point format documents.
   *          <b>false</b> means not to split sections aggressively for the conversion of PDF documents to Power Point format documents.
   */
  bool enable_aggressively_split_sections;

 /**
  * @brief  A boolean value that indicates whether adapt content of smaller pages to the largest page size during the conversion of PDF documents to PowerPoint format. Default value: <b>false</b>.
  *
  * @details Since all slides in a PowerPoint must have the same size, the largest page is used as the reference by default.
  *          When enabled, the converter identifies the largest page within the conversion range and adjusts the page matrix 
  *          of smaller pages accordingly, scaling their graphical objects to ensure uniform slide dimensions in the output PowerPoint file.
  *          All scaling operations preserve the original aspect ratio.
  *          <b>true</b> means to adapt content of smaller pages to the largest page size.
  *          <b>false</b> means not to adapt content of smaller pages to the largest page size.
  */
  bool enable_adapt_to_largest_page;
};

/** This class represents setting data used for converting PDF documents to Excel format documents. */
class PDF2ExcelSettingData FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for Excel workbook settings.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _WorkbookSettings {
    /** @brief Create single worksheet for the document. */
    e_WorkbookSettingsDocument = 0,
    /** @brief Create worksheet for each table. */
    e_WorkbookSettingsEachTable = 1,
    /** @brief Create worksheet for each page. */
    e_WorkbookSettingsEachPage = 2
  } WorkbookSettings;
  
  /** @brief Constructor. */
  PDF2ExcelSettingData()
    : decimal_symbol("")
    , workbook_settings(PDF2ExcelSettingData::e_WorkbookSettingsEachPage)
    , thousands_separator("")
    , enable_aggressive_table_repair(true)
    , include_watermarks(false) { }

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] decimal_symbol                  A string value which indicates being recognized as decimal during the conversion of PDF documents to excel format documents.
   * @param[in] thousands_separator             A string value which indicates being recognized as thousands separator during the conversion of PDF documents to excel format documents.
   * @param[in] workbook_settings               An enumeration value which indicates the setting of the workbook for the conversion of PDF documents to Excel format documents.
   * @param[in] enable_aggressive_table_repair  A boolean value that indicates whether to enabled aggressive table repair during the conversion of PDF documents to Excel format documents. Default value: <b>true</b>.
   *          <b>true</b> means to enabled aggressive table repair for the conversion of PDF documents to Excel format documents.
   *          <b>false</b> means not to enabled aggressive table repair for the conversion of PDF documents to Excel format documents.
   * @param[in] include_watermarks              A boolean value that indicates whether to include the watermarks during the conversion of PDF documents to Excel format documents. Default value: <b>false</b>.
   *          <b>true</b> means to include watermarks for the conversion of PDF documents to Excel format documents.
   *          <b>false</b> means not to include watermarks for the conversion of PDF documents to Excel format documents.
   */
  PDF2ExcelSettingData(String decimal_symbol, String thousands_separator, WorkbookSettings workbook_settings, bool enable_aggressive_table_repair, bool include_watermarks) {
    this->decimal_symbol = decimal_symbol;
    this->thousands_separator = thousands_separator;
    this->workbook_settings = workbook_settings;
    this->enable_aggressive_table_repair = enable_aggressive_table_repair;
    this->include_watermarks = include_watermarks;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another PDF-to-Excel setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDF2ExcelSettingData & operator = (const PDF2ExcelSettingData & data) {
    this->decimal_symbol = data.decimal_symbol;
    this->thousands_separator = data.thousands_separator;
    this->workbook_settings = data.workbook_settings;
    this->enable_aggressive_table_repair = data.enable_aggressive_table_repair;
    this->include_watermarks = data.include_watermarks;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] decimal_symbol                  A string value which indicates being recognized as decimal during the conversion of PDF documents to excel format documents.
   * @param[in] thousands_separator             A string value which indicates being recognized as thousands separator during the conversion of PDF documents to excel format documents.
   * @param[in] workbook_settings               An enumeration value which indicates the setting of the workbook for the conversion of PDF documents to Excel format documents.
   * @param[in] enable_aggressive_table_repair  A boolean value that indicates whether aggressive table repair is enabled during the conversion of PDF documents to Excel format documents. Default value: <b>true</b>.
   *          <b>true</b> means to enabled aggressive table repair for the conversion of PDF documents to Excel format documents.
   *          <b>false</b> means not to enabled aggressive table repair for the conversion of PDF documents to Excel format documents.
   * @param[in] include_watermark               A boolean value that indicates whether include watermarks during the conversion of PDF documents to Excel format documents. Default value: <b>false</b>.
   *          <b>true</b> means to watermarks for the conversion of PDF documents to Excel format documents.
   *          <b>false</b> means not to include watermarks for the conversion of PDF documents to Excel format documents.
   *
   * @return None.
   */
  void Set(String decimal_symbol, String thousands_separator, WorkbookSettings workbook_settings, bool enable_aggressive_table_repair, bool include_watermarks) {
    this->decimal_symbol = decimal_symbol;
    this->thousands_separator = thousands_separator;
    this->workbook_settings = workbook_settings;
    this->enable_aggressive_table_repair = enable_aggressive_table_repair;
    this->include_watermarks = include_watermarks;
  }

  /**
   * @brief A string value which indicates being recognized as decimal during the conversion of PDF documents to excel format documents.
   *
   * @details The decimal symbol is used to separate the integer part and the decimal part of a number.
   *          If this parameter is set to ".", then the number "123.456" will be recognized as 123.456.
   *          If this parameter is set to ",", then the number "123,456" will be recognized as 123.456.
   *          If this parameter is not set, the decimal symbol will be recognized automatically.
   *
   * @note Currently, this parameter is only useful for cells with only numbers and separators.
   *       The value of this parameter must be different from the value of parameter <i>thousands_separator</i>.
   *       To ensure the correct recognition of the decimal symbol, this parameter should be set together
   *       with parameter <i>thousands_separator</i>.
   */
  String decimal_symbol;

  /**
   * @brief A string value which indicates being recognized as thousands separator during the conversion of PDF documents to excel format documents.
   *
   * @details The thousands separator is used to separate the thousands part of a number.
   *          If this parameter is set to ",", then the number "123,456" will be recognized as 123456.
   *          If this parameter is set to ".", then the number "123.456" will be recognized as 123456.
   *          If this parameter is set to " ", then the number "123 456" will be recognized as 123456.
   *          If this parameter is not set, the thousands separator will be recognized automatically.
   *
   * @note Currently, this parameter is only useful for cells with only numbers and separators.
   *       The value of this parameter must be different from the value of parameter <i>decimal_symbol</i>.
   *       To ensure the correct recognition of the thousands separator, this parameter should be set together
   *       with parameter <i>decimal_symbol</i>.
   */
  String thousands_separator;

  /**
   * @brief An enumeration value which indicates the setting of the workbook for the conversion of PDF documents to Excel format documents.
   *
   * @details Please refer to values starting from @link PDF2ExcelSettingData::e_WorkbookSettingsDocument @endlink and this should be one of these values.
   *          Default value: @link PDF2ExcelSettingData::e_WorkbookSettingsEachPage @endlink.
   */
  WorkbookSettings workbook_settings;
/**
  * @brief A boolean value that indicates whether aggressive table repair is enabled during the conversion of PDF documents to Excel format documents. Default value: <b>true</b>.
  *
  * @details <b>true</b> means to enabled aggressive table repair for the conversion of PDF documents to Excel format documents.
  *          <b>false</b> means not to enabled aggressive table repair for the conversion of PDF documents to Excel format documents.
  *          When enabled, this option attempts to preserve the integrity of tables and avoid breaking the table structure.
  *          It works by moving overlapping elements to proper boundaries, ensuring that cells, rows, and columns remain correctly aligned
  *          in the resulting Excel sheet.
  */
  bool enable_aggressive_table_repair;

/**
   * @brief A boolean value that indicates whether to include watermarks during the conversion of PDF documents to Excel format documents. Default value: <b>false</b>.
   *
   * @details <b>true</b> means to include watermarks for the conversion of PDF documents to Excel format documents.
   *          <b>false</b> means not to include watermarks for the conversion of PDF documents to Excel format documents.
   *          If this option is enabled, watermarks of PDF documents will be added to the Excel worksheet during the conversion of PDF documents to Excel format documents.
   *          Note that the watermark may overlap worksheet content. Certain cells, such as headers or the region column,
   *          might be converted to text boxes and may not be directly editable until the watermark is removed or adjusted.
   */
  bool include_watermarks;
};

/** This class represents setting data used for converting PDF to Office(Word, Excel or PowerPoint) format file. */
class PDF2OfficeSettingData FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  PDF2OfficeSettingData()
    : enable_ml_recognition(false)
    , include_pdf_comments(true)
    , enable_trailing_space(true)
    , include_images(true)
    , timeout(0)
    , enable_matching_system_fonts(false) { }

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] metrics_data_folder_path      (Deprecated)A valid path of a folder which contains metrics data files. This should not be an empty string. 
   *                                          These metrics data files are used to simulate the office format document typesetting process during conversion.
   *                                          They are offered in the "res/metrics_data" folder of the Foxit PDF Conversion SDK package.
   * @param[in] enable_ml_recognition         A boolean value which indicates whether enable machine learning-based recognition functionality. Default value: <b>false</b>.
   *                                          <b>true</b> means enable machine learning-based recognition functionality to identify borderless tables in PDF documents. 
   *                                          In order to convert the tables better, it will draw a black border with a width of 1 on the recognized borderless table.
   *                                          This will be improved in subsequent versions.
   *                                          And this recognition functionality will be executed on the server side and return the relevant results when it is done. 
   *                                          <b>false</b> means disable machine learning-based recognition functionality.
   *                                          And the recognition functionality not based on machine learning will be enabled.
   * @param[in] page_range                    A range object that specifies some pages. These pages will be used to convert PDF document to office format documents.
   * @param[in] include_pdf_comments          A boolean value which indicates whether to include PDF documents comments for the conversion of PDF documents to office format documents. Default value: <b>true</b>.
   *                                          <b>true</b> means to include PDF document comments for the conversion of PDF documents to office format documents.
   *                                          <b>false</b> means not to include PDF document comments for the conversion of PDF documents to office format documents.
   * @param[in] word_setting_data             A setting data object that used for converting PDF documents to Word format documents.
   * @param[in] power_point_setting_data      A setting data object that used for converting PDF documents to Power Point format documents.
   * @param[in] excel_setting_data            A setting data object that used for converting PDF documents to Excel format documents.   
   * @param[in] enable_trailing_space         A boolean value which indicates whether to add trailing spaces from lines in paragraphs.for converting PDF documents to office format documents. Default value: <b>true</b>.
   *                                          <b>true</b> means to add trailing spaces from lines in paragraphs for converting PDF documents to office format documents.
   *                                          <b>false</b> means not to add trailing spaces from lines in paragraphs and add a property to the paragraph
   *                                          that allows for line breaks. Currently, this support is limited to paragraphs where more than 80% of the text
   *                                          involves the end of one line and the beginning of the next both being in Korean. This is only available for
   *                                          converting PDF documents to Word format documents, with support for other Office formats planned for the future.
   * @param[in] include_images                A boolean value which indicates whether to include images in PDF documents for converting PDF documents to office format documents. Default value: <b>true/b>.
   *                                          <b>true</b> means to include images in PDF documents for converting PDF documents to office format documents.
   *                                          <b>false</b> means not to include images in PDF documents PDF documents to office format documents.
   *                                          This is only available for converting PDF documents to Word format documents, with support for other Office formats planned
   *                                          for the future.
   * @param[in] timeout                       Milliseconds for timeout used for PDF Conversion. Default value: 0.
   * @param[in] enable_matching_system_fonts  A boolean value which indicates whether to enable matching system fonts for converting PDF documents to office format documents. Default value: <b>false</b>.
   *                                          This is only available for converting PDF documents to Word format documents, with support for other Office formats planned
   *                                          for the future.
   *
   * @note Our machine learning-based technology for identifying borderless tables uses HTTPS and requires a network connection to send the images of the rendered PDF pages to our server during the conversion process.
   */
  PDF2OfficeSettingData(const wchar_t* metrics_data_folder_path, bool enable_ml_recognition, const common::Range& page_range, bool include_pdf_comments,
                const PDF2WordSettingData& word_setting_data, const PDF2PowerPointSettingData& power_point_setting_data,
                const PDF2ExcelSettingData& excel_setting_data, bool enable_trailing_space, bool include_images, int timeout,
                bool enable_matching_system_fonts) {
    this->metrics_data_folder_path = metrics_data_folder_path;
    this->enable_ml_recognition = enable_ml_recognition;
    this->page_range = page_range;
    this->include_pdf_comments = include_pdf_comments;
    this->word_setting_data = word_setting_data;
    this->power_point_setting_data = power_point_setting_data;
    this->excel_setting_data = excel_setting_data;
    this->enable_trailing_space = enable_trailing_space;
    this->include_images = include_images;
    this->timeout = timeout;
    this->enable_matching_system_fonts = enable_matching_system_fonts;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another PDF-to-Office setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDF2OfficeSettingData &operator = (const PDF2OfficeSettingData& data) {
    metrics_data_folder_path = data.metrics_data_folder_path;
    enable_ml_recognition = data.enable_ml_recognition;
    page_range = data.page_range;
    include_pdf_comments = data.include_pdf_comments;
    word_setting_data = data.word_setting_data;
    power_point_setting_data = data.power_point_setting_data;
    excel_setting_data = data.excel_setting_data;
    enable_trailing_space = data.enable_trailing_space;
    include_images = data.include_images;
    timeout = data.timeout;
    enable_matching_system_fonts = data.enable_matching_system_fonts;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] metrics_data_folder_path      (Deprecated)A valid path of a folder which contains metrics data files. This should not be an empty string. 
   *                                          These metrics data files are used to simulate the office format document typesetting process during conversion.
   *                                          They are offered in the "res/metrics_data" folder of the Foxit PDF Conversion SDK package.
   * @param[in] enable_ml_recognition         A boolean value which indicates whether enable machine learning-based recognition functionality. Default value: <b>false</b>.
   *                                          <b>true</b> means enable machine learning-based recognition functionality to identify borderless tables in PDF documents. 
   *                                          In order to convert the tables better, it will draw a black border with a width of 1 on the recognized borderless table.
   *                                          This will be improved in subsequent versions.
   *                                          And this recognition functionality will be executed on the server side and return the relevant results when it is done. 
   *                                          <b>false</b> means disable machine learning-based recognition functionality.
   *                                          And the recognition functionality not based on machine learning will be enabled.
   * @param[in] page_range                    A range object that specifies some pages. These pages will be used to convert PDF documents to office format documents.
   * @param[in] include_pdf_comments          A boolean value which indicates whether to include PDF documents comments for the conversion of PDF documents to office format documents. Default value: <b>true</b>.
   *                                          <b>true</b> means to include PDF document comments for the conversion of PDF documents to office format documents.
   *                                          <b>false</b> means not to include PDF document comments for the conversion of PDF documents to office format documents.
   * @param[in] word_setting_data             A setting data object that used for converting PDF documents to Word format documents.
   * @param[in] power_point_setting_data      A setting data object that used for converting PDF documents to Power Point format documents.
   * @param[in] excel_setting_data            A setting data object that used for converting PDF documents to Excel format documents.   
   * @param[in] enable_trailing_space         A boolean value which indicates whether to add trailing spaces from lines in paragraphs.for converting PDF documents to office format documents. Default value: <b>true</b>.
   *                                          <b>true</b> means to add trailing spaces from lines in paragraphs for converting PDF documents to office format documents.
   *                                          <b>false</b> means not to add trailing spaces from lines in paragraphs and add a property to the paragraph
   *                                          that allows for line breaks. Currently, this support is limited to paragraphs where more than 80% of the text
   *                                          involves the end of one line and the beginning of the next both being in Korean. This is only available for
   *                                          converting PDF documents to Word format documents, with support for other Office formats planned for the future.
   * @param[in] include_images                A boolean value which indicates whether to include images in PDF documents for converting PDF documents to office format documents. Default value: <b>true/b>.
   *                                          <b>true</b> means to include images in PDF documents for converting PDF documents to office format documents.
   *                                          <b>false</b> means not to include images in PDF documents PDF documents to office format documents.
   *                                          This is only available for converting PDF documents to Word format documents, with support for other Office formats planned
   *                                          for the future.
   * @param[in] timeout                       Milliseconds for timeout used for PDF Conversion. Default value: 0.
   * @param[in] enable_matching_system_fonts  A boolean value which indicates whether to enable matching system fonts for converting PDF documents to office format documents. Default value: <b>false</b>.
   *                                          This is only available for converting PDF documents to Word format documents, with support for other Office formats planned
   *                                          for the future.
   * 
   * @note Our machine learning-based technology for identifying borderless tables uses HTTPS and requires a network connection to send the images of the rendered PDF pages to our server during the conversion process.   
   *
   * @return None.
   */
  void Set(const wchar_t* metrics_data_folder_path, bool enable_ml_recognition, const common::Range &page_range, bool include_pdf_comments,
                const PDF2WordSettingData& word_setting_data, const PDF2PowerPointSettingData& power_point_setting_data,
                const PDF2ExcelSettingData& excel_setting_data, bool enable_trailing_space, bool include_images, int timeout,
                bool enable_matching_system_fonts) {
    this->metrics_data_folder_path = metrics_data_folder_path;
    this->enable_ml_recognition = enable_ml_recognition;
    this->page_range = page_range;
    this->include_pdf_comments = include_pdf_comments;
    this->word_setting_data = word_setting_data;
    this->power_point_setting_data = power_point_setting_data;
    this->excel_setting_data = excel_setting_data;
    this->enable_trailing_space = enable_trailing_space;
    this->include_images = include_images;
    this->timeout = timeout;
    this->enable_matching_system_fonts = enable_matching_system_fonts;
  }

  /**
   * @deprecated Current property has been deprecated since Foxit PDF SDK 10.1. Instead, metrics data will be included in the dynamic library.
   *
   * @brief A valid path of a folder which contains metrics data files. This should not be an empty string.
   *
   * @details These metrics data files are used to simulate the office format document typesetting process during conversion.
   *          They are offered in the "res/metrics_data" folder of the Foxit PDF Conversion SDK package.
   */
  WString metrics_data_folder_path;

  /**
   * @brief A boolean value which indicates whether enable machine learning-based recognition functionality. Default value: <b>false</b>.
   *
   * @details <b>true</b> means enable machine learning-based recognition functionality to identify borderless tables in PDF documents.
   *          And this recognition functionality will be executed on the server side and return the relevant results when it is done.
   *          In order to convert the tables better, it will draw a black border with a width of 1 on the recognized borderless table.
   *          This will be improved in subsequent versions.
   *          <b>false</b> means disable machine learning-based recognition functionality.
   *          And the recognition functionality not based on machine learning will be enabled.
   *
   * @note Our machine learning-based technology for identifying borderless tables uses HTTPS and requires a network connection to send the images of the rendered PDF pages to our server during the conversion process.
   */
  bool enable_ml_recognition;

  /**
   * @brief A range object that specifies some pages. These pages will be used to convert PDF documents to office format documents.
   *
   * @details The valid page range: from 0 to (<i>count</i> - 1). <i>count</i> is returned by function @link PDFDoc::GetPageCount @endlink.
   *          If this range object is constructed by default constructor and not set any value, that means all the pages of
   *          current document will be used to convert PDF documents to office format documents.
   */
  common::Range page_range;

  /**
   * @brief A boolean value which indicates whether to include PDF documents comments
   *        for the conversion of PDF documents to office format documents. Default value: <b>true</b>.
   *
   * @details <b>true</b> means to include PDF document comments for the conversion of PDF documents to office format documents.
   *          <b>false</b> means not to include PDF document comments for the conversion of PDF documents to office format documents.
   */
  bool include_pdf_comments;

  /**
   * @brief A setting data object that used for converting PDF documents to Word format documents.
   *
   * @details This setting is only vaild for the conversion of PDF documents to word format documents.
   *          For more details, please refer to class @link PDF2WordSettingData @endlink.
   */
  PDF2WordSettingData word_setting_data;

  /**
   * @brief A setting data object that used for converting PDF documents to Power Point format documents.
   *
   * @details This setting is only vaild for the conversion of PDF documents to Power Point format documents.
   *          For more details, please refer to class @link PDF2PowerPointSettingData @endlink.
   */
  PDF2PowerPointSettingData power_point_setting_data;

  /**
   * @brief A setting data object that used for converting PDF documents to Excel format documents.
   *
   * @details This setting is only vaild for the conversion of PDF documents to Excel format documents.
   *          For more details, please refer to class @link PDF2ExcelSettingData @endlink.
   */
  PDF2ExcelSettingData excel_setting_data;

  /**
   * @brief A boolean value which indicates whether to add trailing spaces from lines in paragraphs
   *        for converting PDF documents to office format documents. Default value: <b>true</b>.
   *
   * @details <b>true</b> means to add trailing spaces from lines in paragraphs for converting
   *          PDF documents to office format documents.
   *          <b>false</b> means not to add trailing spaces from lines in paragraphs and add a property to the paragraph
   *          that allows for line breaks. Currently, this support is limited to paragraphs where more than 80% of the text
   *          involves the end of one line and the beginning of the next both being in Korean. This is only available for
   *          converting PDF documents to Word format documents, with support for other Office formats planned for the future.
   */
  bool enable_trailing_space;

  /**
   * @brief A boolean value which indicates whether to include images in PDF documents
   *        for converting PDF documents to office format documents. Default value: <b>true/b>.
   *
   * @details <b>true</b> means to include images in PDF documents for converting PDF documents to office format documents.
   *          <b>false</b> means not to include images in PDF documents PDF documents to office format documents.
   *          This is only available for converting PDF documents to Word format documents, with support for other Office formats planned
   *          for the future.
   */
  bool include_images;

  /**
   * @brief Milliseconds for timeout used for PDF Conversion.
   * 
   * @details If the conversion process is not completed within the specified time, the conversion process will be terminated.
   *          This should be a non-negative value. If the value is 0, that means no timeout processing for PDF Conversion.<br>
   *          This parameter only useful when Foxit PDF Conversion engine is set by function @link PDF2Office::Initialize @endlink.
   *          Default value: 0.
   *
   * @note Resource release may take some time, so the time spent on the entire conversion process
   *       may exceed the time set by this parameter.
   */
  int timeout;

  /**
   * @brief A boolean value that indicates whether to accurately match system fonts 
   *        when converting PDF documents to office format documents. Default value: <b>false</b>.
   *
   * @details <b>true</b> means accurately matching system fonts when converting PDF documents to office format documents.
   *          <b>false</b> means not accurately matching system fonts when converting PDF documents to office format documents.
   *          This is only available for converting PDF documents to Word format documents, with support for other Office formats planned
   *          for the future.
   */
  bool enable_matching_system_fonts;
};

/**
 * This class represents a callback object used to pause and notify the conversion progress during the converting process.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 */
class ConvertCallback {
 public:
  /**
   * @brief A callback function used to pause the current conversion progress.
   *
   * @return <b>true</b> means to pause now, while <b>false</b> means not to pause now.
   */
  virtual bool NeedToPause() = 0;
  
  /**
   * @brief A callback function used to notify the current conversion progress.
   *
   * @param[in] converted_count  The converted page count.
   * @param[in] total_count      The total page count.
   *
   * @return None.
   */
  virtual void ProgressNotify(int converted_count, int total_count) = 0;
};

/**
* This class represents a callback object used to check the convert condition for the PDF to Office conversion.
* All the pure virtual functions in this class are used as callback functions and should be implemented by user.
* This is called when the required permissions for converting the PDF documents are not met.
*/
class ConvertCheckCallback {
 public:
  /**
   * @brief Check user permissions to decide whether to proceed with the PDF to Office conversion.
   *
   * @param user_permissions The user permissions. Please refer to values starting from
   *                         @link pdf::PDFDoc::UserPermissions @endlink and this should be one or combination of these values.
   *
   * @return <b>true</b> means the PDF to Office conversion will continue,
   *         while <b>false</b> the PDF to Office conversion will not continue.
   */
  virtual bool CheckUserPermissions(uint32 user_permissions) = 0;
};

/**
 * This class can be used to convert PDF files to Office(Word, Excel or PowerPoint) format files.
 * Before using "Conversion" module, please ensure the resource folders named "res" and "lib" in the Foxit PDF Conversion SDK package is valid.
 * Before using methods in this module, please ensure Foxit PDF SDK has been initialized successfully
 * by function @link common::Library::Initialize @endlink with a key including "PDF2Office" module.
 *
 * @see @link common::Library @endlink
 */
class PDF2Office FS_FINAL : public Base {
 public:
  /**
   * @brief Initialize Foxit PDF Conversion.
   *
   * @details During the life-cycle of "PDF2Office" module, this function can only be called once and
   *          should be called first before any other functions in "PDF2Office" module can be called.
   *
   * @param[in] library_path    Path of Foxit PDF Conversion SDK library. This should not be an empty string.
   * @param[in] fx_engine_path  Path of Foxit PDF Conversion engine. It can be an empty string. If the parameter 
   *                            is empty, PDF Conversion SDK library will be called directly for PDF to Office conversion,
   *                            otherwise Foxit PDF Conversion SDK library will be called through the Foxit PDF Conversion engine for PDF to Office conversion.
   * @return None.
   *
   * @note If module "PDF2Office" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using PDF2Office related functions and
   *       this function will throw exception @link foxit::e_ErrNoPDF2OfficeModuleRight @endlink.
   */
  static void Initialize(const wchar_t* library_path, const wchar_t* fx_engine_path = L"");

  /**
   * @brief Release all resource allocated by Foxit PDF Conversion.
   *
   * @details When the user does not use "pdf2office" module, this function should be called to release all memory blocks allocated by the library.
   *
   * @return None.
   */
  static void Release();

  /**
   * @brief Get the version of Foxit PDF Conversion SDK.
   *
   * @details This function should be called after the function @link PDF2Office::Initialize @endlink has been called successfully.
   *
   * @return A string which contains the version information of Foxit PDF Conversion SDK.
   */
  static String GetVersion();

  /**
 * @brief Set the callback object to check the PDF to Office conversion conditions.
 *
 * @details This method allows you to specify a custom convert check callback that will be called
 *        to evaluate whether the conversion from PDF to Office should proceed, based on user-defined logic
 *        , when the required permissions for converting the PDF documents are not met.
 *
 * @param[in] convert_check_callback A customized convert check callback which is implemented based on callback
 *                                   class @link ConvertCheckCallback @endlink. If this is <b>NULL</b>, customized convert
 *                                   check callback will be removed and default convert check will be used instead.
 *
 * @note When Foxit PDF Conversion engine is set by function @link PDF2Office::Initialize @endlink, the ConvertCheckCallback will be not work, 
 *       and it will use the internal ConvertCheckcallbacks to allow conversion.
 *
 * @return <b>true</b> means success, while <b>false</b> means failure.
 */
  static bool SetConvertCheckCallback(ConvertCheckCallback* convert_check_callback);

  /**
   * @brief Start to convert a PDF file to a Word format file. Function @link PDF2Office::Initialize @endlink must be called 
   *        before calling this function.
   *
   * @details Currently only support converting to DOCX format file.
   *
   * @param[in] src_pdf_path          Path of a PDF file. This should not be an empty string.
   * @param[in] src_pdf_password      Password for the input PDF file. If no password is needed for the file, please pass an empty string.
   * @param[in] saved_word_file_path  Path of the saved Word format file as conversion result. This should not be an empty string.
   *                                  If the suffix name of the saved Word format file is not "docx", a new suffix named "docx" will be added to the original file name.
   * @param[in] setting_data          Setting data used for converting.If the parameter <i>page_range</i> of @link PDF2OfficeSettingData @endlink 
   *                                  object is empty, that means convert each page of the PDF file to Word format file.
   * @param[in] convert_callback      A @link conversion::pdf2office::ConvertCallback @endlink object which is implemented by user
   *                                  to pause and notify the conversion progress during the converting process.
   *                                  This can be <b>NULL</b> which means not to pause and notify the conversion progress.
   *                                  If this is not <b>NULL</b>, it should be a valid @link conversion::pdf2office::ConvertCallback @endlink 
   *                                  object implemented by user.<br>
   *                                  Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   *
   * @note When Foxit PDF Conversion engine is set by function @link PDF2Office::Initialize @endlink, the ConvertCallback will be not work.
   */
  static common::Progressive StartConvertToWord(const wchar_t* src_pdf_path, const wchar_t* src_pdf_password, const wchar_t* saved_word_file_path, 
                            const PDF2OfficeSettingData& setting_data, ConvertCallback* convert_callback = NULL);
   
  /**
   * @brief Start to convert a PDF file to a Word format file. Function @link PDF2Office::Initialize @endlink must be called 
   *        before calling this function.
   *
   * @details Currently only support converting to DOCX format file.
   *
   * @param[in] src_pdf_reader          A @link ReaderCallback @endlink object which is implemented by user to
   *                                    load a PDF document. It should not be <b>NULL</b>.
   * @param[in] src_pdf_password        Password for the input PDF file. If no password is needed for the file, please pass an empty string.
   * @param[in] saved_word_file_stream  A @link foxit::common::file::StreamCallback @endlink object which is implemented by user 
   *                                    to read the contents of the converted Word format file. It should not be <b>NULL</b>.
   * @param[in] setting_data            Setting data used for converting.If the parameter <i>page_range</i> of @link PDF2OfficeSettingData @endlink 
   *                                    object is empty, that means convert each page of the PDF file to Word format file.
   * @param[in] convert_callback        A @link conversion::pdf2office::ConvertCallback @endlink object which is implemented by user
   *                                    to pause and notify the conversion progress during the converting process.
   *                                    This can be <b>NULL</b> which means not to pause and notify the conversion progress.
   *                                    If this is not <b>NULL</b>, it should be a valid @link conversion::pdf2office::ConvertCallback @endlink 
   *                                    object implemented by user.<br>
   *                                    Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   *
   * @note When Foxit PDF Conversion engine is set by function @link PDF2Office::Initialize @endlink, the ConvertCallback will be not work.
   */
  static common::Progressive StartConvertToWord(common::file::ReaderCallback* src_pdf_reader, const wchar_t* src_pdf_password, common::file::StreamCallback* saved_word_file_stream, 
                            const PDF2OfficeSettingData& setting_data, ConvertCallback* convert_callback = NULL);
  
  /**
   * @brief Start to convert a PDF file to a Excel format file. Function @link PDF2Office::Initialize @endlink must be called 
   *        before calling this function.
   *
   * @details Currently only support converting to XLSX format file.
   *
   * @param[in] src_pdf_path           Path of a PDF file. This should not be an empty string.
   * @param[in] src_pdf_password       Password for the input PDF file. If no password is needed for the file, please pass an empty string.
   * @param[in] saved_excel_file_path  Path of the saved Excel format file as conversion result. This should not be an empty string.
   *                                   If the suffix name of the saved Excel format file is not "xlsx", a new suffix named "xlsx" will be added to the original file name.
   * @param[in] setting_data           Setting data used for converting.If the parameter <i>page_range</i> of @link PDF2OfficeSettingData @endlink 
   *                                   object is empty, that means convert each page of the PDF file to Excel format file.
   * @param[in] convert_callback       A @link conversion::pdf2office::ConvertCallback @endlink object which is implemented by user
   *                                   to pause and notify the conversion progress during the converting process.
   *                                   This can be <b>NULL</b> which means not to pause and notify the conversion progress.
   *                                   If this is not <b>NULL</b>, it should be a valid @link conversion::pdf2office::ConvertCallback @endlink 
   *                                   object implemented by user.<br>
   *                                   Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   *
   * @note When Foxit PDF Conversion engine is set by function @link PDF2Office::Initialize @endlink, the ConvertCallback will be not work.
   */
  static common::Progressive StartConvertToExcel(const wchar_t* src_pdf_path, const wchar_t* src_pdf_password, const wchar_t* saved_excel_file_path, 
                             const PDF2OfficeSettingData& setting_data, ConvertCallback* convert_callback = NULL);
   
  /**
   * @brief Start to convert a PDF file to a Excel format file. Function @link PDF2Office::Initialize @endlink must be called 
   *        before calling this function.
   *
   * @details Currently only support converting to XLSX format file.
   *
   * @param[in] src_pdf_reader           A @link ReaderCallback @endlink object which is implemented by user to
   *                                     load a PDF document. It should not be <b>NULL</b>.
   * @param[in] src_pdf_password         Password for the input PDF file. If no password is needed for the file, please pass an empty string.
   * @param[in] saved_excel_file_stream  A @link foxit::common::file::StreamCallback @endlink object which is implemented by user 
   *                                     to read the contents of the converted Excel format file. It should not be <b>NULL</b>.
   * @param[in] setting_data             Setting data used for converting.If the parameter <i>page_range</i> of @link PDF2OfficeSettingData @endlink 
   *                                     object is empty, that means convert each page of the PDF file to Excel format file.
   * @param[in] convert_callback         A @link conversion::pdf2office::ConvertCallback @endlink object which is implemented by user
   *                                     to pause and notify the conversion progress during the converting process.
   *                                     This can be <b>NULL</b> which means not to pause and notify the conversion progress.
   *                                     If this is not <b>NULL</b>, it should be a valid @link conversion::pdf2office::ConvertCallback @endlink 
   *                                     object implemented by user.<br>
   *                                     Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   *
   * @note When Foxit PDF Conversion engine is set by function @link PDF2Office::Initialize @endlink, the ConvertCallback will be not work.
   */
  static common::Progressive StartConvertToExcel(common::file::ReaderCallback* src_pdf_reader, const wchar_t* src_pdf_password, common::file::StreamCallback* saved_excel_file_stream, 
                             const PDF2OfficeSettingData& setting_data, ConvertCallback* convert_callback = NULL);
  
  /**
   * @brief Start to convert a PDF file to a PowerPoint format file. Function @link PDF2Office::Initialize @endlink must be called 
   *        before calling this function.
   *
   * @details Currently only support converting to PPTX format file.
   *
   * @param[in] src_pdf_path         Path of a PDF file. This should not be an empty string.
   * @param[in] src_pdf_password     Password for the input PDF file. If no password is needed for the file, please pass an empty string.
   * @param[in] saved_ppt_file_path  Path of the saved PowerPoint format file as conversion result. This should not be an empty string.
   *                                 If the suffix name of the saved PowerPoint format file is not "pptx", a new suffix named "pptx" will be added to the original file name.
   * @param[in] setting_data         Setting data used for converting.If the parameter <i>page_range</i> of @link PDF2OfficeSettingData @endlink 
   *                                 object is empty, that means convert each page of the PDF file to Power Point format file.
   * @param[in] convert_callback     A @link conversion::pdf2office::ConvertCallback @endlink object which is implemented by user
   *                                 to pause and notify the conversion progress during the converting process.
   *                                 This can be <b>NULL</b> which means not to pause and notify the conversion progress.
   *                                 If this is not <b>NULL</b>, it should be a valid @link conversion::pdf2office::ConvertCallback @endlink 
   *                                 object implemented by user.<br>
   *                                 Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   *
   * @note When Foxit PDF Conversion engine is set by function @link PDF2Office::Initialize @endlink, the ConvertCallback will be not work.
   */
  static common::Progressive StartConvertToPowerPoint(const wchar_t* src_pdf_path, const wchar_t* src_pdf_password, const wchar_t* saved_ppt_file_path, 
                                  const PDF2OfficeSettingData& setting_data, ConvertCallback* convert_callback = NULL);
  
  /**
   * @brief Start to convert a PDF file to a PowerPoint format file. Function @link PDF2Office::Initialize @endlink must be called 
   *        before calling this function.
   *
   * @details Currently only support converting to PPTX format file.
   *
   * @param[in] src_pdf_reader         A @link ReaderCallback @endlink object which is implemented by user to
   *                                   load a PDF document. It should not be <b>NULL</b>.
   * @param[in] src_pdf_password       Password for the input PDF file. If no password is needed for the file, please pass an empty string.
   * @param[in] saved_ppt_file_stream  A @link foxit::common::file::StreamCallback @endlink object which is implemented by user 
   *                                   to read the contents of the converted PowerPoint format file. It should not be <b>NULL</b>.
   * @param[in] setting_data           Setting data used for converting.If the parameter <i>page_range</i> of @link PDF2OfficeSettingData @endlink 
   *                                   object is empty, that means convert each page of the PDF file to Power Point format file.
   * @param[in] convert_callback       A @link conversion::pdf2office::ConvertCallback @endlink object which is implemented by user
   *                                   to pause and notify the conversion progress during the converting process.
   *                                   This can be <b>NULL</b> which means not to pause and notify the conversion progress.
   *                                   If this is not <b>NULL</b>, it should be a valid @link conversion::pdf2office::ConvertCallback @endlink 
   *                                   object implemented by user.<br>
   *                                   Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   *
   * @note When Foxit PDF Conversion engine is set by function @link PDF2Office::Initialize @endlink, the ConvertCallback will be not work.
   */
  static common::Progressive StartConvertToPowerPoint(common::file::ReaderCallback* src_pdf_reader, const wchar_t* src_pdf_password, common::file::StreamCallback* saved_ppt_file_stream, 
                                  const PDF2OfficeSettingData& setting_data, ConvertCallback* convert_callback = NULL);

};

}  // namespace pdf2office
}  // namespace conversion
}  // namespace addon
}  // namespace foxit

#endif //defined(WIN32) 
#endif
