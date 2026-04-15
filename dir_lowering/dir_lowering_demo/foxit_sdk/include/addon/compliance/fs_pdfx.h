
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
 * @file fs_pdfx.h
 * @brief Header file for PDF/X compliance related classes and methods.
 */

#ifndef FS_PDFX_H_
#define FS_PDFX_H_

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
 * This class can be used for PDF/X compliance verification or converting a PDF file to a PDF/X format.
 * Please ensure @link ComplianceEngine @endlink has been initialized successfully.
 * 
 * @see @link ComplianceEngine @endlink
 */
class PDFXCompliance FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for PDF/X version.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Version {
    /** @brief PDF/X-1a. */
    e_VersionPDFX1a = 0,
    /** @brief PDF/X-3. */
    e_VersionPDFX3 = 1,
    /** @brief PDF/X-4. */
    e_VersionPDFX4 = 2,
    /** @brief PDF/X-4p. */
    e_VersionPDFX4p = 3,
    /** @brief PDF/X-1a (Coated GRACoL 2006). */
    e_VersionPDFX1aCoatedGRACoL2006 = 4,
    /** @brief PDF/X-1a (ISO Coated v2 (ECI)). */
    e_VersionPDFX1aISOCoatedv2ECI = 5,
    /** @brief PDF/X-1a (Japan Color 2001 Coated). */
    e_VersionPDFX1aJapanColor2001Coated = 6,
    /** @brief PDF/X-1a (PSO Coated v3 (ECI)). */
    e_VersionPDFX1aPSOCoatedv3ECI = 7,
    /** @brief PDF/X-3 (Coated GRACoL 2006). */
    e_VersionPDFX3CoatedGRACoL2006 = 8,
    /** @brief PDF/X-3 (ISO Coated v2 (ECI)). */
    e_VersionPDFX3ISOCoatedv2ECI = 9,
    /** @brief PDF/X-3 (Japan Color 2001 Coated). */
    e_VersionPDFX3JapanColor2001Coated = 10,
    /** @brief PDF/X-3 (PSO Coated v3 (ECI)). */
    e_VersionPDFX3PSOCoatedv3ECI = 11,
    /** @brief PDF/X-4 (Coated GRACoL 2006). */
    e_VersionPDFX4CoatedGRACoL2006 = 12,
    /** @brief PDF/X-4 (ISO Coated v2 (ECI)). */
    e_VersionPDFX4ISOCoatedv2ECI = 13,
    /** @brief PDF/X-4 (Japan Color 2001 Coated). */
    e_VersionPDFX4JapanColor2001Coated = 14,
    /** @brief PDF/X-4 (PSO Coated v3 (ECI)). */
    e_VersionPDFX4PSOCoatedv3ECI = 15,
    /** @brief PDF/X-4 and create language layer views (ISO Coated v2 (ECI))). */
    e_VersionPDFX4AndCLLVISOCoatedv2ECI = 16
  } Version;
  

  /** @brief Constructor. */
  PDFXCompliance();
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PDFXCompliance(FS_HANDLE handle);
  /** @brief Destructor. */
  ~PDFXCompliance();
  /**
   * @brief Constructor, with another PDF/X compliance object.
   *
   * @param[in] other  Another PDF/X compliance object.
   */
  PDFXCompliance(const PDFXCompliance& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another PDF/X compliance object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDFXCompliance& operator = (const PDFXCompliance& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another PDF/X compliance object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const PDFXCompliance& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another PDF/X compliance object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const PDFXCompliance& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Verify a PDF file with specified PDF/X version.
   *
   * @param[in] verify_version     PDF/X version to verify. Please refer to values starting from @link PDFXCompliance::e_VersionPDFX1a @endlink to 
   *                               @link PDFXCompliance::e_VersionPDFX4p and this should be one of these values.
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
   * @brief Convert a PDF file with specified PDF/X version.
   *
   * @param[in] src_pdf_path                 A complete path of source PDF file to be converted. This should not be an empty string.
   * @param[in] saved_pdf_path               A complete path for saving the converted PDF file. This should not be an empty string.
   * @param[in] convert_to_version           PDF/X version to convert. Please refer to values starting from @link PDFXCompliance::e_VersionPDFX1a @endlink and
   *                                         this should be one of these values.
   * @param[in] conv_profile                 Conversion profile type.
   * @param[in] view_or_print_condition      Viewing or printing condition. Please refer to values starting from @link ComplianceEngine::e_ViewOrPrintConditionAuto @endlink and
   *                                         this should be one of these values. 
   * @param[in] to_convert_rgb_or_lab        Whether to convert device independ RGB or Lab color into destination color space. <b>true</b> means to convert, <b>false</b> means not to convert.
   *                                         It only works if <i>convert_to_version</i> is not @link PDFXCompliance::e_VersionPDFX1a @endlink, @link PDFXCompliance::e_VersionPDFX1aCoatedGRACoL2006 @endlink, 
   *                                         @link PDFXCompliance::e_VersionPDFX1aISOCoatedv2ECI @endlink,
   *                                         @link PDFXCompliance::e_VersionPDFX1aJapanColor2001Coated @endlink and @link PDFXCompliance::e_VersionPDFX1aPSOCoatedv3ECI @endlink.
   * @param[in] to_decalibrate_gray_or_cmyk  Whether to decalibrate device independent Gray or CMYK. <b>true</b> means to decalibrate, <b>false</b> means not to decalibrate.
   * @param[in] progress_callback            Progress callback which is implemented by user and can be used to get progress data.
   *                                         This can be <b>NULL</b>. Default value: <b>NULL</b>.
   *
   * @return A @link ResultInformation @endlink object.
   */
  ResultInformation ConvertPDFFile(const wchar_t* src_pdf_path, const wchar_t* saved_pdf_path,
                                   Version convert_to_version,
                                   ComplianceEngine::ViewOrPrintCondition view_or_print_condition,
                                   bool to_convert_rgb_or_lab, bool to_decalibrate_gray_or_cmyk,
                                   ProgressCallback* progress_callback = NULL);

};

}  // namespace compliance
}  // namespace addon
}  // namespace foxit

#endif  // FS_PDFX_H_

