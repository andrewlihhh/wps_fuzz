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
 * @file fs_compliancecommon.h
 * @brief Header file for compliance basic classes and methods.
 */

#ifndef FS_COMPLIANCEENGINE_H_
#define FS_COMPLIANCEENGINE_H_

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
 * @brief Compliance namespace.
 */
namespace compliance {
class ResultInformation;
class ProgressCallback;
class PreflightSettingData;
class PreflightReportSettingData;
class Preflight;

/**
 * Compliance module can be used to verify if a PDF file matches a specified industry standard version (e.g. one of PDF/A version)
 * or convert a PDF file to a specified industry standard version (e.g. one of PDF/A version).
 * Before initializing compliance engine and using any class or methods in this module, please ensure
 * Foxit PDF SDK has been initialized successfully by function @link common::Library::Initialize @endlink
 * with a key including "Compliance" module.
 *
 * @see @link common::Library @endlink
 */
class ComplianceEngine FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for viewing or printing condition.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ViewOrPrintCondition {
    /** @brief Viewing or printing condition: Auto. */
    e_ViewOrPrintConditionAuto = 0,
    /** @brief Viewing or printing condition:Coated GRACoL 2006. */
    e_ViewOrPrintConditionCoatedGRACoL2006 = 1,
    /** @brief Viewing or printing condition:ISO Coated v2 (ECI). */
    e_ViewOrPrintConditionISOCoatedv2ECI = 2,
    /** @brief Viewing or printing condition:Japan Color 2001 Coated. */
    e_ViewOrPrintConditionJapanColor2001Coated = 3,
    /** @brief Viewing or printing condition: PSO Coated v3 (ECI). */
    e_ViewOrPrintConditionPSOCoatedv3ECI = 4
  } ViewOrPrintCondition;
  

  /**
   * @brief Initialize compliance engine.
   *
   * @details This should be called successfully before any other methods in compliance add-on module.
   *
   * @param[in] compliance_resource_folder_path  A complete path to compliance resource folder. This should not be an empty string.
   * @param[in] compliance_engine_unlockcode     The unlock code for compliance engine.
   *                                             <ul>
   *                                             <li> If an authorization key is used for Foxit PDF SDK, please
   *                                                  pass a valid unlock code string to initialize compliance engine.</li>
   *                                             <li> If a trial key is used for Foxit PDF SDK, this parameter will
   *                                                  be ignored. Just pass an empty string. </li>
   *                                             </ul>
   *
   * @return @link foxit::e_ErrSuccess @endlink means success.<br>
   *         @link foxit::e_ErrNoComplianceModuleRight @endlink means Foxit PDF SDK has not been initialized with
   *         a key including "Compliance" module.<br>
   *         @link foxit::e_ErrParam @endlink means parameter <i>compliance_resource_folder_path</i>is an empty string, or
   *         parameter <i>compliance_engine_unlockcode</i> is an empty string when an authorization key is used for
   *         Foxit PDF SDK.<br>
   *         @link foxit::e_ErrFilePathNotExist @endlink means parameter <i>compliance_resource_folder_path</i>
   *         does not exist or no library for compliance engine can be found under this folder.<br>
   *         @link foxit::e_ErrComplianceEngineInvalidUnlockCode @endlink means
   *         parameter <i>compliance_engine_unlockcode</i> is an invalid unlock code for compliance engine
   *         when an authorization key is used for Foxit PDF SDK.<br>
   *         For more information about error code values, please refer to values starting from
   *         @link foxit::e_ErrSuccess @endlink.
   *
   * @note If module "Compliance" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using compliance related functions and
   *       this constructor will throw exception @link foxit::e_ErrNoComplianceModuleRight @endlink.
   */
  static ErrorCode Initialize(const wchar_t* compliance_resource_folder_path, const char* compliance_engine_unlockcode);

  /**
   * @brief Release compliance engine.
   *
   * @details This function can be called to release compliance engine when no need to use it any more
   *          before Foxit PDF SDK is released.
   *
   * @return None.
   */
  static void Release();

#if !defined(_MAC_JAVA_)
  /**
   * @brief Initialize compliance context for a new thread.
   *
   * @details The compliance engine provides thread-safety per default. This should be called successfully for each thread
   *          before any other methods in compliance add-on module for multithreading. It is recommended to use a fixed amount 
   *          of SDK threads (e.g. min=4, max=system-hardware-concurrency). Creating more threads then CPU cores exist will 
   *          degrade the overall performance. The threads should be re-used as long as possible. 
   *
   * @return @link foxit::e_ErrSuccess @endlink means success.<br>
   *         @link foxit::e_ErrNoComplianceModuleRight @endlink means Foxit PDF SDK has not been initialized with
   *         a key including "Compliance" module.<br>
   *         @link foxit::e_ErrComplianceEngineInvalidUnlockCode @endlink means
   *         parameter <i>compliance_engine_unlockcode</i> is an invalid unlock code for compliance engine
   *         when an authorization key is used for Foxit PDF SDK.<br>
   *         For more information about error code values, please refer to values starting from
   *         @link foxit::e_ErrSuccess @endlink.
   *
   * @note If module "Compliance" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using compliance related functions and
   *       this function will throw exception @link foxit::e_ErrNoComplianceModuleRight @endlink.
   */
  static ErrorCode InitializeThreadContext();

  /**
   * @brief Release compliance context of the thread.
   *
   * @details This function will release compliance context of the thread when no need to use it any more 
   *          before Foxit PDF SDK is released in the thread. It should be called from the same thread that 
   *          called @link compliance::ComplianceEngine::InitializeThreadContext @endlink.
   *
   * @return None.
   */
  static void ReleaseThreadContext();
#endif

  /**
   * @brief Set the temporary folder for compliance engine.
   *
   * @details The compliance engine may generate temporary files during processing (e.g., for verification or conversion tasks).
   *          This function allows specifying a custom storage location.
   *          If not set, a default temporary folder will be created in the application's root directory and used for temporary files.
   *
   * @param[in] temp_folder_path  Complete path to the temporary directory. This should be a valid path and
   *                              should not be an empty string.
   *
   * @return None.
   */
   static void SetTempFolderPath(const wchar_t* temp_folder_path);

   /**
    * @brief Set a flag to decide whether to enable transparency handling.
    *
    * @param[in] enable_handle_transparency  <b>true</b> means that transparency handling is enabled, which detects and removes transparency
	*                                        from graphical objects during conversion. <b>false</b> means it is disabled.
    *                                        Default value: <b>false</b>.
    *
    * @return None.
    */
   static void EnableHandleTransparency(bool enable_handle_transparency);

  /**
   * @brief Set language for compliance engine.
   *
   * @details Setting a language to compliance engine will have affect on all the strings which are returned with
   *          @link compliance::ResultInformation @endlink or through callback class @link compliance::ProgressCallback @endlink.
   *          If no language name is set by this function, "English" will be used as default.
   *
   * @param[in] language  Language name. This cannot be an empty string and should be one of following language name:
   *                      "Czech", "Danish", "Dutch", "English", "French",
   *                      "Finnish", "German", "Italian", "Norwegian", "Polish",
   *                      "Portuguese", "Spanish", "Swedish",
   *                      "Chinese-Simplified", "Chinese-Traditional", "Japanese", "Korean".
   *                      For other language name, this function will do nothing.
   *
   * @return None.
   */
   static void SetLanguage(const char* language);
};

/**
 * This class represent a callback object to update the progress data to user.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 */
class ProgressCallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief A callback function used to update current progress state data to user in order that user can update their progress bar.
   *
   * @param[in] current_rate          Current rate. It would be between 0 and 100 (inclusive). 100 means finished.
   * @param[in] current_state_string  A string that describing what current state is. This may be an empty string.
   *
   * @return None.
   */
  virtual void UpdateCurrentStateData(int current_rate, const WString& current_state_string) = 0;

 protected:
  ~ProgressCallback() {}
};

/** This class represents setting data for preflight analysis and fixup operations. */
class PreflightSettingData  FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for the preflight library type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _LibraryType {
    /** @brief Preflight library type: Foxit. */
    e_LibraryTypeFoxit = 0,
    /** @brief Preflight library type: Standards. */
    e_LibraryTypePDFStandards = 1,
    /** @brief Preflight library type: Prepress,Color and Transparency. */
    e_LibraryTypePrepressColorTransparency = 2
  } LibraryType;
  
  /**
   * @brief Enumeration for the preflight operate type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _OperateType {
    /** @brief Opearte type: profiles. */
    e_OperateTypeProfiles = 0,
    /** @brief Opearte type: single checks. */
    e_OperateTypeSingleChecks = 1,
    /** @brief Opearte type: single fixups. */
    e_OperateTypeSingleFixups = 2
  } OperateType;
  

  /** @brief Constructor. */
  PreflightSettingData()
    : preflight_key(L"")
    , operate_type(e_OperateTypeProfiles)
    , src_pdf_path(L"")
    , saved_pdf_path(L"")
    , first_page_index(0)
    , last_page_index(-1) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] preflight_key     The preflight key. Retrieve available keys via @link Preflight::GetItemKeysArray @endlink.
   * @param[in] operate_type      The preflight operate type.
   *                              Please refer to values starting from @link PreflightSettingData::e_OperateTypeProfiles @endlink and
   *                              this should be one of these values.
   * @param[in] src_pdf_path      A complete path of source PDF file to be analyzed or fixed. This should not be an empty string.
   * @param[in] saved_pdf_path    A complete path for saving pdf file after analyzing and fixing. This should not be an empty string.
   * @param[in] first_page_index  Index of the first page to be analyzed or fixed, staring from 0. Default value: 0.
   * @param[in] last_page_index   Index of the last page to be analyzed or fixed. If this is -1, that means
   *                              all the pages of the source PDF file will be analyzed or fixed, and
   *                              parameter <i>first_page_index</i> will be ignored. Default value: -1.
   * @return None.
   */
  PreflightSettingData(const wchar_t* preflight_key, OperateType operate_type, const wchar_t* src_pdf_path, const wchar_t* saved_pdf_path,
    int first_page_index, int last_page_index) {
    this->preflight_key = preflight_key;
    this->operate_type = operate_type;
    this->src_pdf_path = src_pdf_path;
    this->saved_pdf_path = saved_pdf_path;
    this->first_page_index = first_page_index;
    this->last_page_index = last_page_index;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another preflight setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PreflightSettingData &operator = (const PreflightSettingData& data) {
    preflight_key = data.preflight_key;
    operate_type = data.operate_type;
    src_pdf_path = data.src_pdf_path;
    saved_pdf_path = data.saved_pdf_path;
    first_page_index = data.first_page_index;
    last_page_index = data.last_page_index;
    return (*this);
  }

  /** @brief The preflight key. Retrieve available keys via @link Preflight::GetItemKeysArray @endlink. */
  WString preflight_key;

  /**
   * @brief The preflight operate type.
   *        Please refer to values starting from @link PreflightSettingData::e_OperateTypeProfiles @endlink and
   *        this should be one of these values. 
   */
  OperateType operate_type;

  /** @brief A complete path of source PDF file to be analyze and fix. */
  WString src_pdf_path;

  /** @brief A complete path for saving the PDF file generated by the preflight analysis and fixup process. */
  WString saved_pdf_path;

  /** @brief Index of the first page to be analyzed or fixed, staring from 0. Default value: 0. */
  int first_page_index;

  /**
   * @brief Index of the last page to be analyzed or fixed. If this is -1, that means
   *        all the pages of the source PDF file will be analyze, and
   *        parameter <i>first_page_index</i> will be ignored. Default value: -1. 
   */
  int last_page_index;
};

/** This class represents setting data used for generating preflight report file. */
class PreflightReportSettingData  FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for the preflight report file format type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ReportFileFormatType {
    /** @brief Report file format type: PDF. */
    e_ReportFileFormatTypePdf = 0,
    /** @brief Report file format type: XML. */
    e_ReportFileFormatTypeXml = 1,
    /** @brief Report file format type: TXT & TEXT. */
    e_ReportFileFormatTypeTxt = 2,
    /** @brief Report file format type: HTML. */
    e_ReportFileFormatTypeHtml = 3
  } ReportFileFormatType;
  
  /**
   * @brief Enumeration for the highlight method for preflight problems.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ProblemsHighlightMethod {
    /** @brief Problems highlighted by transparent masks. */
    e_ProblemsHighlightMethodTransparentMasks = 0,
    /** @brief Problems highlighted by layers. */
    e_ProblemsHighlightMethodLayers = 1
  } ProblemsHighlightMethod;
  
    
  /** @brief Constructor. */
  PreflightReportSettingData()
    : report_file_format_type(e_ReportFileFormatTypePdf)
    , to_generate_overview(true)
    , to_highlight_problems(true)
    , problems_highlight_method(e_ProblemsHighlightMethodTransparentMasks)
    , report_file_path(L"") {}

  /**
  * @brief Constructor, with parameters.
  *
  * @param[in] report_file_format_type    The report file format type.
  *                                       Please refer to values starting from @link PreflightReportSettingData::e_ReportFileFormatTypePdf @endlink and
  *                                       this should be one of these values.
  * @param[in] to_generate_overview       Whether to generate overview or not. <b>true</b> menas to generate overview, <b>false</b> means not.
  * @param[in] to_highlight_problems      Whether to highlight problems or not.<b>true</b> menas to highlight problems, <b>false</b> means not.
  * @param[in] problems_highlight_method  The method highlight problems. Only effective when <i>to_highlight_problems</i> is <b>true</b> and <i>report_file_format_type</i>
  *                                       is @link PreflightReportSettingData::e_ReportFileFormatTypePdf @endlink.<br>
  *                                       Please refer to values starting from @link PreflightReportSettingData::e_ProblemsHighlightMethodTransparentMasks @endlink and
  *                                       this should be one of these values.
  * @param[in] report_file_path           A complete path for the report file. This should not be an empty string.
  * @return None.
  */
  PreflightReportSettingData(ReportFileFormatType report_file_format_type, bool to_generate_overview, bool to_highlight_problems,
    ProblemsHighlightMethod problem_highlight_method, const wchar_t* report_file_path) {
    this->report_file_format_type = report_file_format_type;
    this->to_generate_overview = to_generate_overview;
    this->to_highlight_problems = to_highlight_problems;
    this->problems_highlight_method = problem_highlight_method;
    this->report_file_path = report_file_path;
  }

  /**
  * @brief Assign operator.
  *
  * @param[in] data  Another preflight export setting data object, whose value would be assigned to current object.
  *
  * @return Reference to current object itself.
  */
  PreflightReportSettingData &operator = (const PreflightReportSettingData& data) {
    report_file_format_type = data.report_file_format_type;
    to_generate_overview = data.to_generate_overview;
    to_highlight_problems = data.to_highlight_problems;
    problems_highlight_method = data.problems_highlight_method;
    report_file_path = data.report_file_path;
    return (*this);
  }

  /** @brief The report file format type.
   *         Please refer to values starting from @link PreflightReportSettingData::e_ReportFileFormatTypePdf @endlink and
   *         this should be one of these values. 
   */
  ReportFileFormatType report_file_format_type;

  /** @brief Whether to generate overview or not. <b>true</b> menas to generate overview, <b>false</b> means not. */
  bool to_generate_overview;

  /** @brief Whether to highlight problems or not. <b>true</b> menas to highlight problems, <b>false</b> means not. */
  bool to_highlight_problems;

  /** @brief The method highlight problems. Only effective when <i>to_highlight_problems</i> is <b>true</b> and <i>report_file_format_type</i>
   *         is @link PreflightReportSettingData::e_ReportFileFormatTypePdf @endlink.
   *         Please refer to values starting from @link PreflightReportSettingData::e_ProblemsHighlightMethodTransparentMasks @endlink and
   *         this should be one of these values. 
   */
  ProblemsHighlightMethod problems_highlight_method;

  /** @brief A complete path for the report file. This should not be an empty string. */
  WString report_file_path;
};

/**
 * This class represents the analysis and fix-up functions that match a specified industry profile and performs checks or fix-ups.
 */
class Preflight FS_FINAL : public Base {
 public:
  /** @brief Constructor. */
  Preflight();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Preflight(FS_HANDLE handle);

  /** @brief Destructor. */
  ~Preflight();

  /**
   * @brief Constructor, with another preflight object.
   *
   * @param[in] other  Another preflight object.
   */
  Preflight(const Preflight& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another preflight object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Preflight& operator = (const Preflight& other);

  /**
  * @brief Equal operator.
  *
  * @param[in] other  Another preflight object. This function will check if current object is equal to this one.
  *
  * @return <b>true</b> means equal, while <b>false</b> means not equal.
  */
  bool operator == (const Preflight& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another preflight object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Preflight& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get all group names array corresponding to the library type and operation type.
   *
   * @param[in] library_type  The library type. Please refer to values starting from @link PreflightSettingData::e_LibraryTypeFoxit @endlink and
   *                          this should be one of these values. 
   * @param[in] operate_type  The operate type. Please refer to values starting from @link PreflightSettingData::e_OperateTypeProfiles @endlink and
   *                          this should be one of these values.
   *
   * @return The group names array.
   */
  StringArray GetGroupNamesArray(const PreflightSettingData::LibraryType& library_type, const PreflightSettingData::OperateType& operate_type);

  /**
   * @brief Get item keys array with the specific group name.
   *
   * @param[in] group_name  The group name which can obtain from the function @link Preflight::GetGroupNamesArray @endlink.
   *
   * @return The item keys array.
   */
  StringArray GetItemKeysArray(const String& group_name);

  /**
   * @brief Analyze a PDF file.
   *
   * @param[in] preflight_setting_data  The preflight setting data.
   * @param[in] progress_callback       A @link ProgressCallback @endlink object which is implemented by user and can be used to get progress data.
   *
   * @return None.
   */
  void Analyze(const PreflightSettingData& preflight_setting_data, ProgressCallback* progress_callback = NULL);
  
  /**
   * @brief Analyze and fixup a PDF file.
   *
   * @param[in] preflight_setting_data  The preflight setting data.
   * @param[in] progress_callback       A @link ProgressCallback @endlink object which is implemented by user and can be used to get progress data.
   *
   * @return None.
   */
  void AnalyzeAndFixup(const PreflightSettingData& preflight_setting_data, ProgressCallback* progress_callback = NULL);

  /**
   * @brief Generate report after analyzing or fixing.
   *
   * @param[in] preflight_report_setting_data  The preflight report setting data.
   * @param[in] progress_callback              A @link ProgressCallback @endlink object which is implemented by user and can be used to get progress data.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool GenerateReport(const PreflightReportSettingData& preflight_report_setting_data, ProgressCallback* progress_callback = NULL);

  /**
   * @brief Check whether the item key can be fixuped or not.
   *
   * @param[in] item_key  The item key. It can be retrieved by @link Preflight::GetItemKeysArray @endlink.
   *
   * @return <b>true</b> means can be fixuped, while <b>false</b> means can not be fixuped.
   */
  bool CanFixup(const String& item_key);
};

/**
 * This class represents a fixup data. Fixup data represents the data for a kind of fixup operation triggered during converting process.
 */
class FixupData : public Object {
 public:
  /**
   * @brief Enumeration for the state of a fixup data.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _FixupState {
    /** @brief A fixup succeeded. */
    e_FixupStateSuccess = 0,
    /** @brief A fixup failed. */
    e_FixupStateFailure = 1,
    /** @brief A fixup was not required. */
    e_FixupStateNotRequired = 2
  } FixupState;
  

  /** @brief Constructor. */
  FixupData()
    : used_count(0)
    , state(e_FixupStateNotRequired) {}

  /**
   * @brief Constructor, with another fixup data object.
   *
   * @param[in] other  Another fixup data object.
   */
  FixupData(const FixupData& other)
      : used_count(other.used_count)
      , state(other.state)
      , name(other.name)
      , comment(other.comment)
      , reasons(other.reasons) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another fixup data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  FixupData& operator = (const FixupData& other) {
    used_count = other.used_count;
    state = other.state;
    name = other.name;
    comment = other.comment;
    reasons = other.reasons;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another fixup data object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const FixupData& other) const {
    bool is_equal = (used_count == other.used_count && state == other.state &&
                     name == other.name && comment == other.comment);
    if (is_equal) {
      for (int i=0; i<(int)reasons.GetSize(); i++) {
        if (reasons[i] != other.reasons[i]) {
          is_equal = false;
          break;
        }
      }
    }
    return is_equal;
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another fixup data object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const FixupData& other) const  {
    return !((*this) == other);
  }

  /** @brief Represents the count of fixup operation invocations for current data during the conversion. */
  uint32 used_count;
  /**
   * @brief Fixup state. Please refer to values starting from @link FixupData::e_FixupStateSuccess @endlink and
   *        this should be one of these values.
   */
  FixupState state;
  /** @brief Fixup rule name.*/
  WString name;
  /** @brief Fixup rule comment to explain more details about the rule. */
  WString comment;
  /** @brief Fixup reasons. This may be an empty array. The count of reasons will not exceed <i>used_times</i>. */
  WStringArray reasons;
};

/**
 * This class represents a hit data. Hit data represents the data for a hit operation triggered during document verification or conversion process.
 */
class HitData : public Object {
 public:
  /**
   * @brief Enumeration for check severity of a hit data.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _CheckSeverity {
    /** @brief Info severity. */
    e_CheckSeverityInfo = 1,
    /** @brief Warning severity. */
    e_CheckSeverityWarning = 2,
    /** @brief Error severity. */
    e_CheckSeverityError = 3
  } CheckSeverity;
  

  /** @brief Constructor. */
  HitData()
    : triggered_count(0)
    , severity(e_CheckSeverityInfo)
    , page_index(-1){}

  /**
   * @brief Constructor, with another hit data object.
   *
   * @param[in] other  Another hit data object.
   */
  HitData(const HitData& other)
      : triggered_count(other.triggered_count)
      , severity(other.severity)
      , name(other.name)
      , comment(other.comment)
      , trigger_values(other.trigger_values)
      , page_index(other.page_index) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another hit data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  HitData& operator = (const HitData& other) {
    triggered_count = other.triggered_count;
    severity = other.severity;
    name = other.name;
    comment = other.comment;
    trigger_values = other.trigger_values;
    page_index = other.page_index;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another hit data object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const HitData& other) const {
    bool is_equal = (triggered_count == other.triggered_count && severity == other.severity &&
                     name == other.name && comment == other.comment && page_index == other.page_index);
    if (is_equal) {
      for (int i=0; i<(int)trigger_values.GetSize(); i++) {
        if (trigger_values[i] != other.trigger_values[i]) {
          is_equal = false;
          break;
        }
      }
    }
    return is_equal;
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another hit data object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const HitData& other) const  {
    return !((*this) == other);
  }

  /** @brief Represents the count of hit operation for current data has been triggered during document verification or conversion process. */
  uint32 triggered_count;
  /**
   * @brief The check severity of current hit data. Please refer to values starting from @link HitData::e_CheckSeverityInfo @endlink and
   *        this should be one of these values.
   */
  CheckSeverity severity;
  /** @brief Hit rule name. */
  WString name;
  /** @brief Hit rule comment to explain more details about the rule. */
  WString comment;
  /** @brief Array of trigger values. The count of triggered values is no more then <i>triggered_count</i>.*/
  WStringArray trigger_values;
  /** @brief Page index, starting from 0. -1 means current hit data was hit in document level. */
  int page_index;
};

/**
 * This class represents the set of result information for verification or conversion process.
 * Fixup data or hit data can be retrieved from the result information.
 */
class ResultInformation FS_FINAL : public Base {
 public:
  /** @brief Constructor. */
  ResultInformation();
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit ResultInformation(FS_HANDLE handle);
  /** @brief Destructor. */
  ~ResultInformation();
  /**
   * @brief Constructor, with another result information object.
   *
   * @param[in] other  Another ResultInformation object.
   */
  ResultInformation(const ResultInformation& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another result information object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  ResultInformation& operator = (const ResultInformation& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another result information object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const ResultInformation& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another result information object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const ResultInformation& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get count of fixup data.
   *
   * @return Count of fixup data.
   */
  int GetFixupDataCount() const;
  /**
   * @brief Get a fixup data.
   *
   * @param[in] index  Index of fixup data to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link ResultInformation::GetFixupDataCount @endlink.
   *
   * @return Fixup data.
   */
  FixupData GetFixupData(int index) const;

  /**
   * @brief Get count of hit data.
   *
   * @return Count of hit data.
   */
  int GetHitDataCount() const;

  /**
   * @brief Get a hit data.
   *
   * @param[in] index  Index of hit data to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link ResultInformation::GetHitDataCount @endlink.
   *
   * @return Hit data.
   */
  HitData GetHitData(int index) const;
};
}  // namespace compliance/**
}  // namespace addon
}  // namespace foxit

#endif  // FS_COMPLIANCEENGINE_H_
