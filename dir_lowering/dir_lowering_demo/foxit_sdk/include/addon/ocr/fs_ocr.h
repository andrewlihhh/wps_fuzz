#if (defined(_WIN32) || defined(_WIN64)) || (defined(__linux__) && defined(__x86_64__) && !defined(__ANDROID__))
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
 * @file fs_ocr.h
 * @brief Header file for OCR related classes and methods.
 */

#ifndef FS_OCR_H_
#define FS_OCR_H_

#include "common/fs_common.h"
#include "pdf/fs_pdfdoc.h"
#include "pdf/fs_pdfpage.h"

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
 * @brief OCR namespace.
 */
namespace ocr {
/**
 * This class represents a callback object to cancel OCR progress.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 * An implemented @link OCRCallback @endlink object can be set by
 * function @link OCREngine::SetOCRCallback @endlink.
 */
class OCRCallback {
 public:
  /**
   * @brief A callback function used to cancel current OCR progress.
   * 
   * @details This function cannot be used to cancel OCR conversion.
   *
   * @param[in] info  A string that describes the OCR progress information.
   * 
   * @return <b>true</b> means to cancel progress, while <b>false</b> means not.
   */
  virtual bool NeedToCancelNow(const wchar_t* info) = 0;

  /**
   * @brief A callback function used to determine whether an image object should be excluded from OCR text recognition.
   *
   * @param[in] image_object  A pointer to an @link pdf::graphics::ImageObject @endlink object. 
   *
   * @return <b>true</b> means to ignore the image object during OCR processing, the image will not be processed by the OCR engine for text extraction, but the image itself remains in the output document,
   *         while <b>false</b> means not.
   */
  virtual bool IsImageIgnored(foxit::pdf::graphics::ImageObject* image_object) = 0;
};

/**
 * This class represents a callback object to notify the OCR progress.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 */
class OCRProgressCallback {
 public:
  /**
   * @brief A callback function used to update current progress state data to user in order that user can update their progress bar.
   *
   * @param[in] current_rate  Current rate. It would be between 0 and 100 (inclusive). 100 means finished.
   *
   * @return None.
   */
  virtual void ProgressNotify(int current_rate) = 0;
};

/**
 * OCR add-on module can be used to convert text content of image to searchable text or editable text
 * in a PDF page or a PDF document.
 * Before using OCR module, user should first prepare OCR resource folder as described in "Foxit PDF SDK Developer Guide.pdf" document.
 * Before initializing OCR engine and using any classes or methods in this module, please ensure
 * Foxit PDF SDK has been initialized successfully by function @link common::Library::Initialize @endlink
 * with a key including "OCR" module.<br>
 * Currently, OCR module only supports Windows and Linux64 system.
 *
 * @see @link common::Library @endlink
 */
class OCREngine FS_FINAL : public Object {
 public:
  /**
   * @brief Initialize OCR engine.
   *
   * @details This should be called successfully before any other methods in OCR add-on module.
   *
   * @param[in] ocr_resource_path  File path of ocr resource folder. It should not be an empty string.
   *                               Please refer to "Foxit PDF SDK Developer Guide.pdf" document for more details.
   *
   * @note If module "OCR" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using OCR related functions and
   *       this constructor will throw exception @link foxit::e_ErrNoOCRModuleRight @endlink.
   *
   * @return @link foxit::e_ErrSuccess @endlink means success.<br>
   *         @link foxit::e_ErrNoOCRModuleRight @endlink means Foxit PDF SDK has not been initialized with
   *         a key including "OCR" module.<br>
   *         @link foxit::e_ErrParam @endlink means parameter <i>ocrt_resource_path</i> is an empty string.<br>
   *         For more information about error code values, please refer to values starting from
   *         @link foxit::e_ErrSuccess @endlink.
   */
  static ErrorCode Initialize(const wchar_t* ocr_resource_path);

  /**
   * @brief Initialize OCR engine.
   *
   * @details This should be called successfully before any other methods in OCR add-on module.
   *
   * @param[in] ocr_resource_path         File path of ocr resource folder. It should not be an empty string.
   *                                      Please refer to "Foxit PDF SDK Developer Guide.pdf" document for more details.
   * @param[in] is_shared_cpu_cores_mode  A boolean value specifies whether the CPU cores should be used in shared mode.<br>
   *                                      There are two modes of CPU cores usage: separate and shared. In separate mode OCR Engine
   *                                      uses no more processes than it is allowed by the license. In shared mode any number of
   *                                      processes can be run.<br>
   *                                      <b>true</b> means the CPU cores should be used in shared mode, while <b>false</b> means not.
   *                                      In muti-process mode, it is strongly recommended to set this parameter to <b>true</b>,
   *                                      such as calling the function @link OCR::OCRPDFDocuments @endlink.<br>
   *                                      In single-process mode, this parameter should be set to <b>false</b>.<br>
   *                                      Default value: <b>false</b>.
   *
   * @note If module "OCR" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using OCR related functions and
   *       this constructor will throw exception @link foxit::e_ErrNoOCRModuleRight @endlink.
   *
   * @return @link foxit::e_ErrSuccess @endlink means success.<br>
   *         @link foxit::e_ErrNoOCRModuleRight @endlink means Foxit PDF SDK has not been initialized with
   *         a key including "OCR" module.<br>
   *         @link foxit::e_ErrParam @endlink means parameter <i>ocrt_resource_path</i> is an empty string.<br>
   *         For more information about error code values, please refer to values starting from
   *         @link foxit::e_ErrSuccess @endlink.
   */
  static ErrorCode Initialize(const wchar_t* ocr_resource_path, bool is_shared_cpu_cores_mode);

  /**
   * @brief Release OCR engine.
   *
   * @details This function can be called to release OCR engine when no need to use it any more
   *          before Foxit PDF SDK is released.
   *
   * @return None.
   */
  static void Release();

  /**
   * @brief Set log file for OCR engine.
   *
   * @details This function is to set the log file for OCR engine, not for Foxit PDF SDK.
   *          If user wants to set log file for Foxit PDF SDK, please refer to function
   *          @link common::Library::SetLogFile @endlink.
   *
   * @param[in] log_file_path  A log file path. If this is an empty string, that means stop the log for OCR engine.
   *
   * @return None.
   */
  static void SetLogFile(const char* log_file_path);

  /**
   * @brief Set log file for OCR engine.
   *
   * @details This function is to set the log file for OCR engine, not for Foxit PDF SDK.
   *          If user wants to set log file for Foxit PDF SDK, please refer to function
   *          @link common::Library::SetLogFile @endlink.
   *
   * @param[in] log_file_path  A log file path. If this is an empty string, that means stop the log for OCR engine.
   *
   * @return None.
   */
  static void SetLogFile(const wchar_t* log_file_path);

  /**
   * @brief Set the name of languages which would be included in the language database for doing OCR.
   *
   * @details Current supported languages:
   *          <ul>
   *          <li>When CJK language resources are used, support Chinese-Simplified, Chinese-Traditional, Japanese, Korean.</li>
   *          <li>When other language resources are used, support Basque, Bulgarian, Catalan, Croatian, Czech, Danish,
   *              Dutch, English , Estonian, Faeroese, Finnish, French, Galician, German, Greek, Hebrew, Hungarian,
   *              Icelandic, Italian, Latvian(Lettish), Lithuanian, Macedonian, Maltese, Norwegian, Polish, Portuguese,
   *              Romanian, Russian, Serbian, Slovak, Slovenian, Spanish, Swedish, Thai, Turkish, Ukrainian, Arabic.</li>
   *          </ul>
   *          If no any language is set by this function, Foxit PDF SDK will use "English" by default.
   *
   * @param[in] languages  Language names. This should not be an empty string.
   *                       This can contain one language name or several language names separated with commas.
   *                       For example, "English" means English only, and "English,French" means English and French only.
   *
   * @return None.
   */
  static void SetLanguages(const wchar_t* languages);

  /**
   * @brief Set the callback object used to cancel OCR progress.
   * 
   * @param[in] callback  A customized ocr callback which is implemented based on callback class @link OCRCallback @endlink.
   *                      <b>NULL</b> means not use any ocr callback object. User should ensure all the callback functions
   *                      have been implemented in application level.
   * 
   * @return None.
   */
  static void SetOCRCallback(OCRCallback* callback);
};

/** This class represents config used for OCR. */
class OCRConfig FS_FINAL : public Object {
 public:
  /**
   * @brief Constructor.
   */
  OCRConfig()
  :is_detect_pictures(true)
  ,is_remove_noise(true)
  ,is_correct_skew(true)
  ,is_enable_text_extraction_mode(false)
  ,is_sequentially_process(false)
  ,is_auto_overwrite_resolution(true)
  ,resolution_to_overwrite(300)
  ,confidence(0){}

  /**
   * @brief Constructor, with parameters.
   * @param[in] is_detect_pictures              Decide whether to detect pictures.
   * @param[in] is_remove_noise                 Decide whether to remove noise of the image of PDF.
   * @param[in] is_correct_skew                 Decide whether to enable skew correction.
   * @param[in] is_enable_text_extraction_mode  Decide whether to enable text extraction mode.
   * @param[in] is_sequentially_process         Decide whether the OCR engine will process pages sequentially on one process.
   * @param[in] is_auto_overwrite_resolution    Decide whether to auto overwrite resolution.
   * @param[in] resolution_to_overwrite         The resolution to overwrite. This parameter is valid only when parameter <i>is_auto_overwrite_resolution</i> is set to <b>false</b>.
   * @param[in] confidence                      The confidence threshold used to determine whether the recognized text is reliable. The value range is from 0 to 100.
   */
  OCRConfig(bool is_detect_pictures, bool is_remove_noise, bool is_correct_skew, bool is_enable_text_extraction_mode, bool is_sequentially_process,
            bool is_auto_overwrite_resolution, int resolution_to_overwrite, int confidence) {
    this->is_detect_pictures = is_detect_pictures;
    this->is_remove_noise = is_remove_noise;
    this->is_correct_skew = is_correct_skew;
    this->is_enable_text_extraction_mode = is_enable_text_extraction_mode;
    this->is_sequentially_process = is_sequentially_process;
    this->is_auto_overwrite_resolution = is_auto_overwrite_resolution;
    this->resolution_to_overwrite = resolution_to_overwrite;
    this->confidence = confidence;
  }

  /**
   * @brief Set value.
   *
   * @param[in] is_detect_pictures              Decide whether to detect pictures. 
   * @param[in] is_remove_noise                 Decide whether to remove noise of the image of PDF.
   * @param[in] is_correct_skew                 Decide whether to enable skew correction.
   * @param[in] is_enable_text_extraction_mode  Decide whether to enable text extraction mode.
   * @param[in] is_sequentially_process         Decide whether the OCR engine will process pages sequentially on one process.
   * @param[in] is_auto_overwrite_resolution    Decide whether to auto overwrite resolution.
   * @param[in] resolution_to_overwrite         The resolution to overwrite. This parameter is valid only when parameter <i>is_auto_overwrite_resolution</i> is set to <b>false</b>.
   * @param[in] confidence                      The confidence threshold used to determine whether the recognized text is reliable. The value range is from 0 to 100.
   *
   * @return None.
   */
  void Set(bool is_detect_pictures, bool is_remove_noise, bool is_correct_skew, bool is_enable_text_extraction_mode, bool is_sequentially_process,
           bool is_auto_overwrite_resolution, int resolution_to_overwrite, int confidence) {
    this->is_detect_pictures = is_detect_pictures;
    this->is_remove_noise = is_remove_noise;
    this->is_correct_skew = is_correct_skew;
    this->is_enable_text_extraction_mode = is_enable_text_extraction_mode;
    this->is_sequentially_process = is_sequentially_process;
    this->is_auto_overwrite_resolution = is_auto_overwrite_resolution;
    this->resolution_to_overwrite = resolution_to_overwrite;
    this->confidence = confidence;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another OCR config object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  OCRConfig& operator=(const OCRConfig& other) {
    is_detect_pictures = other.is_detect_pictures;
    is_remove_noise = other.is_remove_noise;
    is_correct_skew = other.is_correct_skew;
    is_enable_text_extraction_mode = other.is_enable_text_extraction_mode;
    is_sequentially_process = other.is_sequentially_process;
    is_auto_overwrite_resolution = other.is_auto_overwrite_resolution;
    resolution_to_overwrite = other.resolution_to_overwrite;
    confidence = other.confidence;
    return (*this);
  }

  /**
   * @brief Not equal operator.
   * 
   * @param[in] other Another OCR config object. This function will check if current object is not equal to this one.
   * 
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const OCRConfig& other) {
    if (is_detect_pictures != other.is_detect_pictures || is_remove_noise != other.is_remove_noise ||
        is_correct_skew != other.is_correct_skew || is_enable_text_extraction_mode != other.is_enable_text_extraction_mode ||
      is_sequentially_process != other.is_sequentially_process || is_auto_overwrite_resolution != other.is_auto_overwrite_resolution ||
      resolution_to_overwrite != other.resolution_to_overwrite || confidence != other.confidence)
      return true;
    return false;
  }

  /**
   * @brief Decide whether to detect pictures. <b>true</b> means the pictures will be detected during analysis process. 
   *        <b>false</b> means not to detect the picture, the picture content on the image of PDF document might be interpreted as text.
   *        If you would like to extract only text from the image, this option can be set to <b>false</b>.
   *        Default value: <b>true</b>.
   */
  bool is_detect_pictures;

  /**
   * @brief Decide whether to remove noise of the image of PDF. It can be useful if the image of the PDF contains some noise,
   *        such as random black dots or speckles. If the lines of letters on the image are thin, this option should be set to <b>false</b>,
   *        otherwise it will affect the recognition of the text.
   *        <b>true</b> means the noise in the image will not be recognized during the OCR process. Noise will not be recognized as text.
   *        <b>false</b> means not block noise.
   *        Default value: <b>true</b>.
   */
  bool is_remove_noise;

  /**
   * @brief Decide whether to enable skew correction. <b>true</b> means to enable skew correction.
   *        <b>false</b> means not to enable skew correction.
   *        Default value: <b>true</b>.
   * 
   * @note Skew can be corrected only for angles not greater than 20 degrees.
   */
  bool is_correct_skew;

  /**
   * @brief Decide whether to enable text extraction mode.
   * 
   * @details Usually, when some parts of the text are not be found as a text block such as text on a picture or handwriting,
   *          it is recommended to set this parameter to <b>true</b>.
   *          It is recommended to set this parameter to <b>false</b> in case the complete text of a picture is recognized correctly or the
   *          sample contains images or patterns that may be considered and recognized as text.
   *          To be short this parameter enables the Engine to recognize everything remotely close to letters as text.
   *          <b>true</b> means to enable text extraction mode, while <b>false</b> means not to enable text extraction mode.
   *          Default value: <b>false</b>.
   */
  bool is_enable_text_extraction_mode;

  /**
   * @brief  Decide whether the OCR engine will process pages sequentially on one process.
   *
   * @details This parameter is only used in OCR conversion. <b>true</b> means the OCR engine will process pages
   *          sequentially on one process, and the conversion time will increase.<br>
   *          <b>false</b> means the OCR engine will detecte the number of processes automatically. If only one
   *          page is processed or there is only one processor in the system, one process is used. Otherwise,
   *          parallel processing is used.<br>
   *          Default value: <b>false</b>.
   */
  bool is_sequentially_process;

  /**
   * @brief Decide whether to set the resolution automatically.
   *
   * @details <b>true</b> means the OCR engine will automatically detect and overwrite image resolution.
   *          <b>false</b> means set the resolution manually by parameter <i>resolution_to_overwrite</i>.
   */
  bool is_auto_overwrite_resolution;

  /**
   * @brief The resolution (DPI) used to overwrite the image resolution of PDF document.
   *
   * @details This parameter is valid only when parameter <i>is_auto_overwrite_resolution</i> is set to <b>false</b>.
   *          Default value: 300.
   */
  int resolution_to_overwrite;

  /**
   * @brief The confidence threshold used to determine whether the recognized text is reliable.
   *
   * @details The value range is [0, 100]. The larger the value, the higher the confidence requirement.
   *          For example, if this value is set to 30, the recognized text with confidence lower than 30
   *          will be considered as unreliable text and the recognized text will be removed.
   *          Default value: 0.
   */
  int confidence;
};

/** This class represents setting data used for OCR. */
class OCRSettingData FS_FINAL : public Object {
 public:
  /**
   * @brief Constructor.
   */
  OCRSettingData(){}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] pdf_doc      A valid PDF document.
   * @param[in] page_range   The range of pages that need to be OCR.
   * @param[in] is_editable  <b>true</b> means the OCR result is editable, <b>false</b> means the OCR result can only be searched but not be edited.
   * @param[in] ocr_config   The @link OCRConfig @endlink object.
   */
  OCRSettingData(pdf::PDFDoc pdf_doc, const common::Range& page_range, bool is_editable, const OCRConfig& ocr_config) {
    this->pdf_doc = pdf_doc;
    this->page_range = page_range;
    this->is_editable = is_editable;
    this->ocr_config = ocr_config;
  }

  /**
   * @brief Set value.
   *
   * @param[in] pdf_doc      A valid PDF document.
   * @param[in] page_range   The range of pages that need to be OCR.
   * @param[in] is_editable  <b>true</b> means the OCR result is editable, <b>false</b> means the OCR result can only be searched but not be edited.
   * @param[in] ocr_config   The @link OCRConfig @endlink object.
   *
   * @return None.
   */
  void Set(pdf::PDFDoc pdf_doc, const common::Range& page_range, bool is_editable, const OCRConfig& ocr_config) {
    this->pdf_doc = pdf_doc;
    this->page_range = page_range;
    this->is_editable = is_editable;
    this->ocr_config = ocr_config;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another OCR setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  OCRSettingData& operator=(const OCRSettingData& data) {
    pdf_doc = data.pdf_doc;
    page_range = data.page_range;
    is_editable = data.is_editable;
    ocr_config = data.ocr_config;
    return (*this);
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] data  Another OCR setting data object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const OCRSettingData& data) {
    if (pdf_doc != data.pdf_doc || page_range != data.page_range || is_editable != data.is_editable || ocr_config != data.ocr_config)
      return true;
    return false;
  }

  /** @brief A valid PDF document that need to be OCR. */
  pdf::PDFDoc pdf_doc;

  /** @brief The range of pages that need to be OCR. */
  common::Range page_range;

  /**
   * @brief Decide whether the OCR result is editable. <b>true</b> means the OCR result is editable.
   *        <b>false</b> means the OCR result can only be searched but not be edited.
   */
  bool is_editable;

  /** @brief The @link OCRConfig @endlink object. */
  OCRConfig ocr_config;
};

/** This class represents an array of @link OCRSettingData @endlink objects. */
FSDK_DEFINE_ARRAY(OCRSettingDataArray, OCRSettingData)

/**
 * This class indicates that it is used to collect the information set of suspicious results that exist after OCR
 * recognition is completed. Use this information to quickly locate the page and coordinate position of the suspicious
 * information.
 */
class OCRSuspectInfo FS_FINAL : public Object {
 public:
  /** @brief The index of page. */
  int page_index;

  /** @brief The box rectangle, in [PDF coordinate system] (@ref PDFPage) for suspicious words */
  foxit::RectF words_rect;

  /** @brief Suspicious words after OCR recognition. */
  WString suspect_words;
};

/** This class represents an array of OCR suspicious information. */
FSDK_DEFINE_ARRAY(OCRSuspectInfoArray, OCRSuspectInfo)

/**
 * This class is used to do OCR for a PDF page or a PDF document.
 * Please ensure OCR engine has been initialized before using this class.
 *
 * @see @link OCREngine @endlink
 */
class OCR FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for format used for OCR converting.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _OCRConvertFormat {
    /** @brief OCR convert format: DOCX.*/
    e_OCRConvertFormatDOCX  = 0,
    /** @brief OCR convert format: DOC.*/
    e_OCRConvertFormatDOC = 1,
    /** @brief OCR convert format: RTF. */
    e_OCRConvertFormatRTF = 2,
    /** @brief OCR convert format: XLSX. */
    e_OCRConvertFormatXLSX = 3,
    /** @brief OCR convert format: XLS. */
    e_OCRConvertFormatXLS = 4,
    /** @brief OCR convert format: PPTX. */
    e_OCRConvertFormatPPTX = 5,
    /** @brief OCR convert format: HTML. */
    e_OCRConvertFormatHTML = 6
  } OCRConvertFormat;
  
  /**
   * @brief Constructor.
   */
  OCR();

  /**
   * @brief Constructor, with another ocr object.
   *
   * @param[in] other  Another ocr object.
   */
  OCR(const OCR& other);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit OCR(FS_HANDLE handle);
  /** @brief Destructor. */
  ~OCR();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another ocr object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  OCR& operator = (const OCR& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another ocr object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const OCR& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another ocr object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const OCR& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief OCR a PDF page.
   *
   * @details After this function succeeds, the PDF page content may be changed and
   *          the input PDF page is recommended to be re-parsed.
   *
   * @param[in] pdf_page     A valid PDF page object. This PDF page should have been parsed.
   * @param[in] is_editable  <b>true</b> means the OCR result is editable.
   *                         <b>false</b> means the OCR result can only be searched but not be edit.
   * @param[in] callback     A customized progress callback which is implemented based on callback class @link OCRProgressCallback @endlink.
   *                         <b>NULL</b> means not to receive progress notification.
   *
   * @return None.
   */
  void OCRPDFPage(pdf::PDFPage pdf_page, bool is_editable, OCRProgressCallback* callback = NULL);

  /**
   * @brief OCR a PDF page.
   * 
   * @details After this function succeeds, the PDF page content may be changed and
   *          the input PDF page is recommended to be re-parsed.
   * 
    * @param[in] pdf_page     A valid PDF page object. This PDF page should have been parsed.
   * @param[in] is_editable  <b>true</b> means the OCR result is editable.
   *                         <b>false</b> means the OCR result can only be searched but not be edited.
   * @param[in] config       The @link OCRConfig @endlink.
   * @param[in] callback     A customized progress callback which is implemented based on callback class @link OCRProgressCallback @endlink.
   *                         <b>NULL</b> means not to receive progress notification.
   * 
   * @return None.
   */
  void OCRPDFPage(pdf::PDFPage pdf_page, bool is_editable, const OCRConfig& config, OCRProgressCallback* callback = NULL);

  /**
   * @brief OCR each page of a PDF document.
   *
   * @details After this function succeeds, the PDF page content may be changed. It is better to parse or re-parse
   *          PDF pages in the input PDF document before using these pages.
   *
   * @param[in] pdf_doc      A valid PDF document object.
   * @param[in] is_editable  <b>true</b> means the OCR result is editable.
   *                         <b>false</b> means the OCR result can only be searched but not be edited.
   * @param[in] callback     A customized progress callback which is implemented based on callback class @link OCRProgressCallback @endlink.
   *                         <b>NULL</b> means not to receive progress notification.
   *
   * @return None.
   */
  void OCRPDFDocument(pdf::PDFDoc pdf_doc, bool is_editable, OCRProgressCallback* callback = NULL);

  /**
   * @brief OCR each page of a PDF document.
   * 
   * @details After this function succeeds, the PDF page content may be changed. It is better to parse or re-parse
   *          PDF pages in the input PDF document before using these pages.
   * 
   * @param[in] pdf_doc      A valid PDF document object.
   * @param[in] is_editable  <b>true</b> means the OCR result is editable.
   *                         <b>false</b> means the OCR result can only be searched but not be edited.
   * @param[in] config       The @link OCRConfig @endlink.
   * @param[in] callback     A customized progress callback which is implemented based on callback class @link OCRProgressCallback @endlink.
   *                         <b>NULL</b> means not to receive progress notification.
   * 
   * @return None.
   */
  void OCRPDFDocument(pdf::PDFDoc pdf_doc, bool is_editable, const OCRConfig& config, OCRProgressCallback* callback = NULL);

  /**
   * @brief OCR the PDF document and convert it to a specified format document.
   *
   * @param[in] format                  The format of the document to convert. Please refer to values starting from @link OCR::e_OCRConvertFormatDOCX @endlink and
   *                                    this should be one of these values.
   * @param[in] src_pdf_path            The source PDF file path.This should not be an empty string.
   * @param[in] password                The password of the source PDF file. If the PDF file is not encrypted, this should be an empty string.
   * @param[in] saved_file_path         The path of the file to save. This should not be an empty string.
   * @param[in] page_range              The range of pages that need to be converted. If this is an empty range, that means to convert each page of the PDF document.
   * @param[in] is_retain_flowing_text  <b>true</b> means the generated document will retain flowing text, the text may be reformatted and page breaks
   *                                    cannot be guaranteed to be retained. <b>false</b> means the generated document will retain original page layout.<br>
   *                                    This parameter is only useful for the following format types:<br>
   *                                    @link OCR::e_OCRConvertFormatRTF @endlink, @link OCR::e_OCRConvertFormatDOC @endlink, @link OCR::e_OCRConvertFormatDOCX @endlink.<br>
   *                                    Default value: <b>true</b>.
   * @param[in] callback                A customized progress callback which is implemented based on callback class @link OCRProgressCallback @endlink.
   *                                    <b>NULL</b> means not to receive progress notification.
   *
   * @return None.
   */
  void OCRConvertTo(OCRConvertFormat format, const wchar_t* src_pdf_path, const wchar_t* password, const wchar_t* saved_file_path, common::Range page_range, bool is_retain_flowing_text, OCRProgressCallback* callback = NULL);

  /**
   * @brief OCR the PDF document and convert it to a specified format document.
   *
   * @param[in] format                  The format of the document to convert. Please refer to values starting from @link OCR::e_OCRConvertFormatDOCX @endlink and
   *                                    this should be one of these values.
   * @param[in] src_pdf_path            The source PDF file path.This should not be an empty string.
   * @param[in] password                The password of the source PDF file. If the PDF file is not encrypted, this should be an empty string.
   * @param[in] saved_file_path         The path of the file to save. This should not be an empty string.
   * @param[in] page_range              The range of pages that need to be converted. If this is an empty range, that means to convert each page of the PDF document.
   * @param[in] is_retain_flowing_text  <b>true</b> means the generated document will retain flowing text, the text may be reformatted and page breaks
   *                                    cannot be guaranteed to be retained. <b>false</b> means the generated document will retain original page layout.<br>
   *                                    This parameter is only useful for the following format types:<br>
   *                                    @link OCR::e_OCRConvertFormatRTF @endlink, @link OCR::e_OCRConvertFormatDOC @endlink, @link OCR::e_OCRConvertFormatDOCX @endlink.<br>
   *                                    Default value: <b>true</b>.
   * @param[in] config                  The @link OCRConfig @endlink object.
   * @param[in] callback                A customized progress callback which is implemented based on callback class @link OCRProgressCallback @endlink.
   *                                    <b>NULL</b> means not to receive progress notification.
   *
   * @return None.
   */
  void OCRConvertTo(OCRConvertFormat format, const wchar_t* src_pdf_path, const wchar_t* password, const wchar_t* saved_file_path, common::Range page_range, bool is_retain_flowing_text, const OCRConfig& config, OCRProgressCallback* callback = NULL);

#if (defined(_WIN32) || defined(_WIN64)) || (defined(__linux__) && defined(__x86_64__) && !defined(__ANDROID__))
  /**
   * @brief OCR multiple pages of multiple PDF documents.
   *
   * @details This function can be used to batch process multiple documents or pages.
   *          Users can set documents and page ranges via @link OCRSettingDataArray @endlink.
   *          The time performance of this function will be better than calling @link OCR::OCRPDFDocument @endlink or
   *          @link OCR::OCRPDFPage @endlink multiple times when dealing with a large number of documents or pages. After
   *          successful execution, the page content may be changed, it is better to parse or re-parse the PDF pages before
   *          using these pages.
   *
   * @param[in] settingdata_array  An array of @link OCRSettingData @endlink objects, if the parameter
   *                               <i>page_range</i> of @link OCRSettingData @endlink object is empty, that
   *                               means OCR each page of the PDF document.
   * @param[in] callback           A customized progress callback which is implemented based on callback class @link OCRProgressCallback @endlink.
   *                               <b>NULL</b> means not to receive progress notification.
   *
   * @return None.
   */
  void OCRPDFDocuments(const ocr::OCRSettingDataArray& settingdata_array, OCRProgressCallback* callback = NULL);
#endif

  /**
   * @brief Get OCR suspicious information.
   *
   * @details  The parameter <i>ocred_pdf_doc</i> is a valid PDF document that should have been ocred.
   *
   * @param[in] ocred_pdf_doc   A valid PDF document object. 
   *
   * @return An array of @link OCRSuspectInfo @endlink objects, If its value is empty, that means the document OCR has no suspicious information.
   */
  OCRSuspectInfoArray GetOCRSuspectsInfo(pdf::PDFDoc ocred_pdf_doc);
};

}  // namespace ocr
}  // namespace addon
}  // namespace foxit

#endif  // FS_OCR_H_

#endif  // #if (defined(_WIN32) || defined(_WIN64)) || (defined(__linux__) && defined(__x86_64__) && !defined(__ANDROID__))
