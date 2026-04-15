
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
 * @file fs_pdfa.h
 * @brief Header file for PDF/A compliance related classes and methods.
 */

#ifndef FS_PDFA_H_
#define FS_PDFA_H_

#include "fs_compliancecommon.h"

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
 * @brief Compliance namespace.
 */
namespace compliance {
/**
 * This class can be used for PDF/A compliance verification or converting a PDF file to a PDF/A format.
 * Please ensure @link ComplianceEngine @endlink has been initialized successfully.
 * 
 * @see @link ComplianceEngine @endlink
 */
class PDFACompliance FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for PDF/A version.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Version {
    /** @brief PDF/A-1a. */
    e_VersionPDFA1a = 1,
    /** @brief PDF/A-1b. */
    e_VersionPDFA1b = 2,
    /** @brief PDF/A-2a. */
    e_VersionPDFA2a = 3,
    /** @brief PDF/A-2b. */
    e_VersionPDFA2b = 4,
    /** @brief PDF/A-2u. */
    e_VersionPDFA2u = 5,
    /** @brief PDF/A-3a. */
    e_VersionPDFA3a = 6,
    /** @brief PDF/A-3b. */
    e_VersionPDFA3b = 7,
    /** @brief PDF/A-3u. */
    e_VersionPDFA3u = 8,
    /** @brief PDF/A-1b (without fallback conversion), just only for converting. */
    e_VersionPDFA1bWithoutFBC = 9,
    /** @brief PDF/A-2b (without fallback conversion), just only for converting. */
    e_VersionPDFA2bWithoutFBC = 10,
    /** @brief PDF/A-3b (without fallback conversion), just only for converting.*/
    e_VersionPDFA3bWithoutFBC = 11
  } Version;
  

  /** @brief Constructor. */
  PDFACompliance();
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PDFACompliance(FS_HANDLE handle);
  /** @brief Destructor. */
  ~PDFACompliance();
  /**
   * @brief Constructor, with another PDF/A compliance object.
   *
   * @param[in] other  Another PDF/A compliance object.
   */
  PDFACompliance(const PDFACompliance& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another PDF/A compliance object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDFACompliance& operator = (const PDFACompliance& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another PDF/A compliance object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const PDFACompliance& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another PDF/A compliance object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const PDFACompliance& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Verify a PDF file with specified PDF/A version.
   *
   * @param[in] verify_version     PDF/A version to verify.
   *                               Please refer to values starting from @link PDFACompliance::e_VersionPDFA1a @endlink and
   *                               this should be one of these values.
   * @param[in] src_pdf_path       A complete path of source PDF file to be verified. This should not be an empty string.
   * @param[in] first_page_index   Index of the first page to be verified, staring from 0. Default value: 0.
   * @param[in] last_page_index    Index of the last page to be verified. If this is -1, that means
   *                               all the pages of the source PDF file will be verified(ignores <i>first_page_index</i>).
   *                               Default value: -1.
   * @param[in] progress_callback  Progress callback which is implemented by user and can be used to get progress data.
   *                               This can be <b>NULL</b>. Default value: <b>NULL</b>.
   *
   * @return A @link ResultInformation @endlink object.
   */
  ResultInformation Verify(Version verify_version, const wchar_t* src_pdf_path, 
                           int first_page_index = 0, int last_page_index = -1,
                           ProgressCallback* progress_callback = NULL);

  /**
   * @brief Convert a PDF file with specified PDF/A version.
   *
   * @param[in] src_pdf_path        A complete path of source PDF file to be converted. This should not be an empty string.
   * @param[in] saved_pdf_path      A complete path for saving the converted PDF file. This should not be an empty string.
   * @param[in] convert_to_version  PDF/A version to convert. Please refer to values starting from @link PDFACompliance::e_VersionPDFA1a @endlink
   *                                and this should be one of these values.
   * @param[in] progress_callback   Progress callback which is implemented by user and can be used to get progress data.
   *                                This can be <b>NULL</b>. Default value: <b>NULL</b>.
   *
   * @return A @link ResultInformation @endlink object.
   */
  ResultInformation ConvertPDFFile(const wchar_t* src_pdf_path, const wchar_t* saved_pdf_path,
                                   Version convert_to_version, ProgressCallback* progress_callback = NULL);

  /**
   * @brief Convert a PDF file with specified PDF/A version.
   *
   * @param[in] src_pdf_path                         A complete path of source PDF file to be converted. This should not be an empty string.
   * @param[in] saved_pdf_path                       A complete path for saving the converted PDF file. This should not be an empty string.
   * @param[in] convert_to_version                   PDF/A version to convert. Please refer to values starting from @link PDFACompliance::e_VersionPDFA1a @endlink and
   *                                                 this should be one of these values.
   * @param[in] view_or_print_condition              Viewing or printing condition. Please refer to values starting from @link ComplianceEngine::e_ViewOrPrintConditionAuto @endlink and
   *                                                 this should be one of these values. 
   * @param[in] to_convert_problem_pages_into_image  Whether to convert pages with problems into images on conversion failure.
   *                                                 <b>true</b> means to convert, <b>false</b> means not.
   *                                                 Only effective if <i>convert_to_version</i> is not @link PDFACompliance::e_VersionPDFA1a @endlink, @link PDFACompliance::e_VersionPDFA2a @endlink and @link PDFACompliance::e_VersionPDFA3a @endlink.
   * @param[in] to_convert_all_pages_into_image      Whether to convert all pages into images on conversion failure. <b>true</b> means to convert, <b>false</b> means not to convert.
   *                                                 Only effective if <i>convert_to_version</i> is not @link PDFACompliance::e_VersionPDFA1a @endlink, @link PDFACompliance::e_VersionPDFA2a @endlink and @link PDFACompliance::e_VersionPDFA3a @endlink.
   * @param[in] image_resolution                     Resolution (PPI) for converted images.Valid range: 60-1200.
   *                                                 Only effective if <i>convert_to_version</i> is not @link PDFACompliance::e_VersionPDFA1a @endlink, @link PDFACompliance::e_VersionPDFA2a @endlink and @link PDFACompliance::e_VersionPDFA3a @endlink.
   * @param[in] progress_callback                    Progress callback which is implemented by user and can be used to get progress data.
   *                                                 This can be <b>NULL</b>. Default value: <b>NULL</b>.
   *
   * @return A @link ResultInformation @endlink object.
   */
  ResultInformation ConvertPDFFile(const wchar_t* src_pdf_path, const wchar_t* saved_pdf_path, Version convert_to_version,
    ComplianceEngine::ViewOrPrintCondition view_or_print_condition,
    bool convert_problem_pages_into_image, bool convert_all_pages_into_image,
    int32 image_resolution, ProgressCallback* progress_callback = NULL);
};

}  // namespace compliance
}  // namespace addon
}  // namespace foxit

#endif  // FS_PDFA_H_

