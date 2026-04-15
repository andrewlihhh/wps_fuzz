
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
 * @file fs_pdfe.h
 * @brief Header file for PDF/E compliance related classes and methods.
 */

#ifndef FS_PDFE_H_
#define FS_PDFE_H_

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
 * This class can be used for PDF/E compliance verification or converting a PDF file to a PDF/E format.
 * Please ensure @link ComplianceEngine @endlink has been initialized successfully.
 * 
 * @see @link ComplianceEngine @endlink
 */
class PDFECompliance FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for PDF/E version.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Version {
    /** @brief PDF/E-1. */
    e_VersionPDFE1 = 1
  } Version;
  

  /** @brief Constructor. */
  PDFECompliance();
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PDFECompliance(FS_HANDLE handle);
  /** @brief Destructor. */
  ~PDFECompliance();
  /**
   * @brief Constructor, with another PDF/E compliance object.
   *
   * @param[in] other  Another PDF/E compliance object.
   */
  PDFECompliance(const PDFECompliance& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another PDF/E compliance object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDFECompliance& operator = (const PDFECompliance& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another PDF/E compliance object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const PDFECompliance& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another PDF/E compliance object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const PDFECompliance& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Verify a PDF file with specified PDF/E version.
   *
   * @param[in] src_pdf_path       A complete path of source PDF file to be verified. This should not be an empty string.
   * @param[in] first_page_index   Index of the first page to be verified, staring from 0. Default value: 0.
   * @param[in] last_page_index    Index of the last page to be verified. If this is -1, that means
   *                               all the pages of the source PDF file will be verified(ignores <i>first_page_index</i>).
   *                               Default value: -1.
   * @param[in] verify_version     PDF/E version to verify.
   * @param[in] progress_callback  Progress callback which is implemented by user and can be used to get progress data.
   *                               This can be <b>NULL</b>. Default value: <b>NULL</b>.
   *
   * @return A @link ResultInformation @endlink object.
   */
  ResultInformation Verify(const wchar_t* src_pdf_path, int first_page_index = 0, int last_page_index = -1, 
                           Version verify_version = e_VersionPDFE1, ProgressCallback* progress_callback = NULL);

  /**
   * @brief Convert a PDF file with specified PDF/E version.
   *
   * @param[in] src_pdf_path        A complete path of source PDF file to be converted. This should not be an empty string.
   * @param[in] saved_pdf_path      A complete path for saving the converted PDF file. This should not be an empty string.
   * @param[in] convert_to_version  PDF/E version to convert. Please refer to values starting from @link PDFECompliance::e_VersionPDFE1 @endlink and
   *                                this should be one of these values.
   *                                Default value: @link PDFECompliance::e_VersionPDFE1 @endlink.
   * @param[in] progress_callback   Progress callback which is implemented by user and can be used to get progress data.
   *                                This can be <b>NULL</b>. Default value: <b>NULL</b>.
   *
   * @return A @link ResultInformation @endlink object.
   */
  ResultInformation ConvertPDFFile(const wchar_t* src_pdf_path, const wchar_t* saved_pdf_path,
                                   Version convert_to_version = e_VersionPDFE1, ProgressCallback* progress_callback = NULL);
};

}  // namespace compliance
}  // namespace addon
}  // namespace foxit

#endif  // FS_PDFE_H_
