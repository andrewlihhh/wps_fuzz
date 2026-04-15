/**
 * Copyright (C) 2003-2026, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software
 * Inc.. It is not allowed to distribute any parts of Foxit PDF SDK to third
 * party or public without permission unless an agreement is signed between
 * Foxit Software Inc. and customers to explicitly grant customers permissions.
 *
 * @file fs_xfa.h
 * @brief Header file for XFA related definitions and functions.
 */

#ifndef FS_XFA_H_
#define FS_XFA_H_

#include "common/fs_common.h"
#include "common/fs_image.h"

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
namespace common {
  class Bitmap;
}

namespace pdf{
class Signature;
class PDFDoc;
}

/**
 * @brief Add-on namespace.
 */
namespace addon {
/**
 * @brief XFA namespace.
 */
namespace xfa {
class XFADoc;
class XFAPage;
class XFAWidget;

/** This class represents the data of an option in list box or combo box. */
class WidgetChoiceOption FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  WidgetChoiceOption()
      : option_label(WString())
      , selected(false){}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] option_label  The displayed string value for the option.
   * @param[in] selected      <b>true</b> means the option is selected, and <b>false</b> means
   *                          the option is not selected.
   */
  WidgetChoiceOption(const wchar_t* option_label, bool selected)
      : option_label(option_label)
      , selected(selected){}

  /**
   * @brief Constructor, with another choice option object.
   *
   * @param[in] option  Another choice option object.
   */
  WidgetChoiceOption(const WidgetChoiceOption& option)
      : option_label(option.option_label)
      , selected(option.selected){}

  /**
   * @brief Assign operator.
   *
   * @param[in] option  Another choice option object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  WidgetChoiceOption& operator = (const WidgetChoiceOption& option) {
    option_label = option.option_label;
    selected = option.selected;
    return *this;
  }

  /**
   * @brief Set value.
   *
   * @param[in] option_label  The displayed string value for the option.
   * @param[in] selected      <b>true</b> means the option is selected, and <b>false</b> means
   *                          the option is not selected.
   *
   * @return None.
   */
  void Set( const wchar_t* option_label, bool selected) {
    this->option_label = option_label;
    this->selected = selected;
  }

  /** @brief The displayed string value for the option. */
  WString option_label;

  /** @brief Used to indicate whether the option is selected or not. */
  bool selected;
};

/** This class represents an array of choice options. */
FSDK_DEFINE_ARRAY(WidgetChoiceOptionArray, WidgetChoiceOption);

/**
 * This class represents a callback object as an XFA application provider.
 * All the functions in this class are used as callback functions. Pure virtual functions should be implemented
 * by user.
 */
class AppProviderCallback {
 public:
  /**
   * @brief Enumeration for XFA application information type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _AppInfo {
    /** @brief Application information: version. */
    e_AppInfoVersion = 0x0,
    /** @brief Application information: language. */
    e_AppInfoLanguage = 0x01,
    /** @brief Application information: platform. */
    e_AppInfoPlatform= 0x02,
    /** @brief Application information: variation. */
    e_AppInfoVariation= 0x03,
    /** @brief Application information: name. */
    e_AppInfoName = 0x04,
    /** @brief Application information: type. */
    e_AppInfoType = 0x05
  } AppInfo;
  
  /**
   * @brief Enumeration for XFA beep type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _BeepType {
    /** @brief Beep type: error. */
    e_BeepTypeError = 0,
    /** @brief Beep type: warning. */
    e_BeepTypeWarning = 1,
    /** @brief Beep type: question. */
    e_BeepTypeQuestion = 2,
    /** @brief Beep type: status. */
    e_BeepTypeStatus = 3,
    /** @brief Beep type: default. */
    e_BeepTypeDefault = 4
  } BeepType;
  
  /**
   * @brief Enumeration for string ID used to specify a case.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _StringID {
    /** @brief Sample message: "Validate failed". */
    e_StringIDValidateFailed = 1,
    /** @brief Sample message: "Calculate Override". */
    e_StringIDCalcOverride = 2,
    /** @brief String ID for case: If to modify field. Sample message: "Do you want to modify this field?". */
    e_StringIDModifyField = 3,
    /** @brief String ID for case: Not allow to modify field. Sample message: "You are not allowed to modify this field.". */
    e_StringIDNotModifyField = 4,
    /** @brief String ID for case: Application's name. Sample message: "Foxit Phantom". */
    e_StringIDAppName = 5,
    /**
     * @brief String ID for case: Filter for image files. Sample message:
     *       "Image Files(*.bmp;*.jpg;*.png;*.gif;*.tif)|*.bmp;*.jpg;*.png;*.gif;*.tif|All Files(*.*)|*.*||".
     */
    e_StringIDImageFilter = 6,
    /** @brief Sample message: "Unknown error is caught!". */
    e_StringIDUnknownCaught = 7,
    /** @brief Sample message: "Unable to set". */
    e_StringIDUnableToSet = 8,
    /** @brief Sample message: "Value!". */
    e_StringIDValueExcalmatory = 9,
    /** @brief String ID for case: Some enumerate value is invalid. Sample message: "Invalid enumerate value:". */
    e_StringIDInvalidEnumValue = 10,
    /** @brief Sample message: "Unsupported method %s.". */
    e_StringIDUnsupportMethod = 11,
    /** @brief Sample message: "Unsupported property %s.". */
    e_StringIDUnsupportProperty = 12,
    /**
     * @brief String ID for case: Some setting operation to property is invalid.
     *        Sample message: "Invalid property setting operation:".
     */
    e_StringIDInvalidPropertySetOperation = 13,
    /** @brief Sample message: "Not have a default property". */
    e_StringIDNotDefaultValue = 14,
    /** @brief Sample message: "Unable to set the value for property 'language'". */
    e_StringIDUnableSetLanguage = 15,
    /** @brief Sample message: "Unable to set the value for property 'numPages'". */
    e_StringIDUnableSetNumPages = 16,
    /** @brief Sample message: "Unable to set the value for property 'platform'". */
    e_StringIDUnableSetPlatformValue = 17,
    /** @brief Sample message: "Unable to set the value for property 'validationsEnabled'". */
    e_StringIDUnableSetValidationsEnabledValue = 18,
    /** @brief Sample message: "Unable to set the value for property 'variation'". */
    e_StringIDUnableSetValidationsValue = 19,
    /** @brief Sample message: "Unable to set the value for property 'version'". */
    e_StringIDUnableSetVersion = 20,
    /** @brief Sample message: "Unable to set the value for property 'ready'". */
    e_StringIDUnableSetReady = 21,
    /** @brief Sample message: "The element [%s] has violated its allowable number of occurrences". */
    e_StringIDNumberOfOccur = 22,
    /** @brief Sample message: "Unable to set the value for property 'className'". */
    e_StringIDUnableSetClassName = 23,
    /** @brief Sample message: "Unable to set the value for property 'length'". */
    e_StringIDUnableSetLengthValue = 24,
    /** @brief Sample message: "Unsupported character '%c'". */
    e_StringIDUnsupportChar = 25,
    /** @brief Sample message: "Bad suffix on number". */
    e_StringIDBadSuffix = 26,
    /** @brief Sample message: "Expected identifier instead of '%s'". */
    e_StringIDExpectedIdent = 27,
    /** @brief Sample message: "Expected '%s' instead of '%s'". */
    e_StringIDExpectedString = 28,
    /** @brief Sample message: "Invalidate character '%c'". */
    e_StringIDInvalidateChar = 29,
    /** @brief Sample message: "'%s' redefinition". */
    e_StringIDRedefinition = 30,
    /** @brief Sample message: "Invalidate token '%s'". */
    e_StringIDInvalidToken = 31,
    /** @brief Sample message: "Invalidate expression '%s'". */
    e_StringIDInvalidExpression = 32,
    /** @brief Sample message: "Undefined identifier '%s'". */
    e_StringIDUndefineIdentifier = 33,
    /** @brief Sample message: "Invalidate left-value '%s'". */
    e_StringIDInvalidateLeftValue = 34,
    /** @brief Sample message: "Compiler error". */
    e_StringIDCompilerError= 35,
    /** @brief Sample message: "Cannot modify the '%s' value". */
    e_StringIDCannotModifyValue = 36,
    /** @brief Sample message: "Function '%s' does not have %d parameters". */
    e_StringIDParametersError = 37,
    /** @brief Sample message: "Expected 'endif' instead of '%s'". */
    e_StringIDExpectedEndIf = 38,
    /** @brief Sample message: "Unexpected expression '%s'". */
    e_StringIDUnexpectedExpression = 39,
    /** @brief Sample message: "Condition is null". */
    e_StringIDConditionIsNull = 40,
    /** @brief Sample message: "Illegal break". */
    e_StringIDIllegalBreak = 41,
    /** @brief Sample message: "Illegal continue". */
    e_StringIDIllegalContinue = 42,
    /** @brief Sample message: "Expected operator '%s' instead of '%s'". */
    e_StringIDExpectedOperator = 43,
    /** @brief Sample message: "Divide by zero". */
    e_StringIDDivideZero = 44,
    /** @brief Sample message: "%s.%s cannot covert to object". */
    e_StringIDCannotCovertToObject = 45,
    /** @brief Sample message: "Cannot find container '%s'". */
    e_StringIDNotFoundContainer = 46,
    /** @brief Sample message: "Cannot find property '%s'". */
    e_StringIDNotFoundProperty = 47,
    /** @brief Sample message: "Cannot find method '%s'". */
    e_StringIDNotFoundMethod = 48,
    /** @brief Sample message: "Cannot find const '%s'". */
    e_StringIDNotFoundConst = 49,
    /** @brief Sample message: "Cannot directly assign the value to object". */
    e_StringIDNotAssignObject= 50,
    /** @brief Sample message: "Invalidate instruction". */
    e_StringIDInvalidateInstruction= 51,
    /** @brief Sample message: "Expected number instead of '%s'". */
    e_StringIDExpectedNumber = 52,
    /** @brief Sample message: "Validate access index '%s' out of array". */
    e_StringIDValidateOutOfArray= 53,
    /** @brief Sample message: "Cannot assign to '%s'". */
    e_StringIDCannotAssign = 54,
    /** @brief Sample message: "Cannot find function '%s'". */
    e_StringIDNotFoundFunction = 55,
    /** @brief Sample message: "'%s' is not an array". */
    e_StringIDIsNotArray = 56,
    /** @brief Sample message: "Out of the range of '%s' array". */
    e_StringIDOutOfArrayRange = 57,
    /** @brief Sample message: "'%s' operator cannot support array calculation". */
    e_StringIDNotSupportArrayCalculate = 58,
    /** @brief Sample message: "'%s' function's %d argument cannot be array". */
    e_StringIDArgumentNotArray = 59,
    /** @brief Sample message: "'%s' argument is expected to be a container". */
    e_StringIDArgumentExpectContainer = 60,
    /** @brief Sample message: "An attempt was made to reference property '%s' of a non-object in SOM expression %s". */
    e_StringIDAccessProertyInNotObject = 61,
    /** @brief Sample message: "Function '%s' is built-in. */
    e_StringIDFunctionBuildIn = 62,
    /** @brief Sample message: "%s : %s". */
    e_StringIDErrorMessage = 63,
    /** @brief Sample message: "Index value is out of bounds". */
    e_StringIDIndexValueOutOfBounds = 64,
    /** @brief Sample message: "Incorrect number of parameters are used when calling method '%s'".*/
    e_StringIDIncorrectNumberOfMethod = 65,
    /** @brief Sample message: "Argument mismatch in property or function argument". */
    e_StringIDArgumentMismatch  = 66,
    /** @brief Sample message: "Invalid enumerated value: %s". */
    e_StringIDInvalidEnumerate = 67,
    /** @brief Sample message: "Invalid append operation: %s cannot have a child element of %s". */
    e_StringIDInvalidAppend = 68,
    /** @brief Sample message: "SOM expression returned list when single result was expected". */
    e_StringIDSOMExpectedList = 69,
    /** @brief Sample message: "'%s' doesn't have property '%s'". */
    e_StringIDNotHaveProperty = 70,
    /** @brief Sample message: "Invalid node type: '%s'". */
    e_StringIDInvalidNodeType = 71,
    /** @brief Sample message: "The element [%s] has violated its allowable number of occurrences". */
    e_StringIDViolateBoundary = 72,
    /** @brief String ID for case: Server denies. Sample message: "Server does not permit". */
    e_StringIDServerDeny = 73,
    /** @brief String ID for case: Use string in local language for "Sunday". */
    e_StringIDWeekDaySun = 74,
    /** @brief String ID for case: Use string in local language for "Monday". */
    e_StringIDWeekDayMon = 75,
    /** @brief String ID for case: Use string in local language for "Tuesday". */
    e_StringIDWeekDayTue = 76,
    /** @brief String ID for case: Use string in local language for "Wednesday". */
    e_StringIDWeekDayWed = 77,
    /** @brief String ID for case: Use string in local language for "Thursday". */
    e_StringIDWeekDayThu = 78,
    /** @brief String ID for case: Use string in local language for "Friday".*/
    e_StringIDWeekDayFri = 79,
    /** @brief String ID for case: Use string in local language for "Saturday". */
    e_StringIDWeekDaySat = 80,
    /** @brief String ID for case: Use string in local language for "January". */
    e_StringIDMonthJan = 81,
    /** @brief String ID for case: Use string in local language for "February". */
    e_StringIDMonthFeb = 82,
    /** @brief String ID for case: Use string in local language for "March". */
    e_StringIDMonthMarch = 83,
    /** @brief String ID for case: Use string in local language for "April". */
    e_StringIDMonthApril = 84,
    /** @brief String ID for case: Use string in local language for "May". */
    e_StringIDMonthMay = 85,
    /** @brief String ID for case: Use string in local language for "June". */
    e_StringIDMonthJune = 86,
    /** @brief String ID for case: Use string in local language for "July". */
    e_StringIDMonthJuly = 87,
    /** @brief String ID for case: Use string in local language for "August". */
    e_StringIDMonthAug = 88,
    /** @brief String ID for case: Use string in local language for "September". */
    e_StringIDMonthSep = 89,
    /** @brief String ID for case: Use string in local language for "October". */
    e_StringIDMonthOct = 90,
    /** @brief String ID for case: Use string in local language for "November". */
    e_StringIDMonthNov = 91,
    /** @brief String ID for case: Use string in local language for "December". */
    e_StringIDMonthDec = 92,
    /** @brief String ID for case: Use string in local language for "Today". */
    e_StringIDToday = 93,
    /** @brief Sample message: "Message limit exceeded. Remaining %d validation errors not reported.". */
    e_StringIDValidateLimit = 94,
    /** @brief Sample message: "%s cannot be left blank. To ignore validations for %s, click Ignore.". */
    e_StringIDValidateNullWarning = 95,
    /** @brief Sample message: "%s cannot be left blank.". */
    e_StringIDValidateNullError = 96,
    /** @brief Sample message: "The value you entered for %s is invalid. To ignore validations for %s, click Ignore.". */
    e_StringIDValidateWarning = 97,
    /** @brief Sample message: "The value you entered for %s is invalid.". */
    e_StringIDValidateError = 98,
    /** @brief Sample message: "Illegal value:cannot assign '%s' to %s.". */
    e_StringIDValidateNumberError = 99,
    /** @brief Sample message: "Script failed(language is %s;context is %s) script=%s". */
    e_StringIDScriptFailedError = 100,
    /** @brief Sample message: "Error:Invalid enumerated value:%s". */
    e_StringIDScriptInvalidValue = 101,
    /**
     * @brief Sample message:
     *       "At least one required field was empty. Please fill in the required fields(highlighted) before continuing.".
     */
    e_StringIDSubmitValidateNullError = 102,
    /** @brief Sample message: "Invalid Barcode Value: %s is an invalid value for barcodes of type %s.". */
    e_StringIDInvalidBarcodeValue = 103,
    /** @brief Sample message: "Error:Argument mismatch in property or function argument.". */
    e_StringIDScriptArgumentMismatch = 104
  } StringID;
  
  /**
   * @brief Enumeration for icon type of XFA message box.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _MsgBoxIconType {
    /** @brief Message box icon: Error. */
    e_MsgBoxIconError = 0,
    /** @brief Message box icon: Warning. */
    e_MsgBoxIconWarning = 1,
    /** @brief Message box icon: Question. */
    e_MsgBoxIconQuestion = 2,
    /** @brief Message box icon: Status. */
    e_MsgBoxIconStatus = 3
  } MsgBoxIconType;
  
  /**
   * @brief Enumeration for button type of XFA message box.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _MsgBoxButtonType {
    /** @brief Message box button: OK. */
    e_MsgBtnTypeOK = 0,
    /** @brief Message box button: OK and Cancel. */
    e_MsgBtnTypeOKCancel = 1,
    /** @brief Message box button: Yes and No. */
    e_MsgBtnTypeYesNo = 2,
    /** @brief Message box button: Yes, No and Cancel. */
    e_MsgBtnTypeYesNoCancel = 3
  } MsgBoxButtonType;
  
  /**
   * @brief Enumeration for button ID of XFA message box.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _MsgBoxButtonID {
    /** @brief Message box button ID: OK. */
    e_MsgBtnIDOK = 1,
    /** @brief Message box button ID: Cancel. */
    e_MsgBtnIDCancel = 2,
    /** @brief Message box button ID: No. */
    e_MsgBtnIDNo = 3,
    /** @brief Message box button ID: Yes. */
    e_MsgBtnIDYes = 4
  } MsgBoxButtonID;
  

  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief A callback function used to get application information for a specified information type.
   *
   * @param[in] app_info  The type of application information, whose information is to retrieved. Please refer to
   *                      values starting from @link AppProviderCallback::e_AppInfoType @endlink and this would be
   *                      one of these values.
   *
   * @return A string of application information.
   */
  virtual WString GetAppInfo(AppInfo app_info) = 0;

  /**
   * @brief A callback function used to beep for specified beep type.
   *
   * @param[in] type  The beep type. Please refer to values starting from @link AppProviderCallback::e_BeepTypeError @endlink
   *                  and this would be one of these values.
   *
   * @return None.
   */
  virtual void Beep(BeepType type) = 0;

  /**
   * @brief A callback function used to set message box.
   *
   * @param[in] message      A message string.
   * @param[in] title        The title of message box.
   * @param[in] icon_type    The icon type for message box. Please refer to values starting from
   *                         @link AppProviderCallback::e_MsgBoxIconError @endlink and this would be one of these values.
   * @param[in] button_type  The button type for message box. Please refer to values starting from
   *                         @link AppProviderCallback::e_MsgBtnTypeOK @endlink and this would be one of these values.
   *
   * @return The button ID for message box. Please refer to values starting from @link AppProviderCallback::e_MsgBtnIDOK @endlink
   *         and this should be one of these values.
   */
  virtual MsgBoxButtonID MsgBox(const wchar_t* message, const wchar_t* title, MsgBoxIconType icon_type,
                                MsgBoxButtonType button_type) = 0;

  /**
   * @brief A callback function used to response.
   *
   * @param[in] question        A string that represents the question.
   * @param[in] title           A string that represents the title.
   * @param[in] default_answer  A string that represents the default answer. It could be an empty string
   *                            which means no default answer.
   * @param[in] is_mask         <b>true</b> means the answer should be masked by '*',
   *                            while <b>false</b> means the answer does not need to be masked by '*'.
   *
   * @return A string that represents the response answer.
   */
  virtual WString Response(const wchar_t* question, const wchar_t* title, const wchar_t* default_answer,
                           bool is_mask) = 0;

  /**
   * @brief A callback function used to download from specified URL.
   *
   * @param[in] url  A URL to be downloaded.
   *
   * @return A @link common::file::ReaderCallback @endlink object which can be used to read the downloading result.
   */
  virtual common::file::ReaderCallback* DownLoadUrl(const wchar_t* url) = 0;

  /**
   * @brief A callback function used to post data to the given URL.
   *
   * @param[in] url           A URL, to which the data will be posted.
   * @param[in] data          The data to be posted.
   * @param[in] content_type  A string that represents the content type of data. This string could be "text/html",
   *                          "text/xml", "text/plain", "multipart/form-data", "application/x-www-form-urlencoded",
   *                          "application/octet-stream", or any valid MIME type.
   * @param[in] encode        A string that represents the encoding of data. This string could be "UTF-8", "UTF-16",
   *                          "ISO8859-1", or any recognized [IANA]character encoding.
   * @param[in] header        A string that represents any additional HTTP headers to be included in the post.
   *
   * @return The response string.
   */
  virtual WString PostRequestURL(const wchar_t* url, const wchar_t* data, const wchar_t* content_type,
                                 const wchar_t* encode, const wchar_t* header) = 0;

  /**
   * @brief A callback function used to put data to the given URL.
   *
   * @param[in] url     A URL, to which the data will be put.
   * @param[in] data    The data to be put.
   * @param[in] encode  A string that represents the encoding of data. This string could be "UTF-8", "UTF-16",
   *                    ISO8859-1", or any recognized [IANA]character encoding.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool PutRequestURL(const wchar_t* url, const wchar_t* data, const wchar_t* encode) = 0;

  /**
   * @brief A callback function used to load a string in local language for a specified case.
   *
   * @details This function is very useful for user to use local language for message of specified cases.
   *          User can re-write or translate the sample message (which is defined in the comment of values
   *          starting from @link AppProviderCallback::e_StringIDValidateFailed @endlink) into local language
   *          for the specified case, and return the result string to Foxit PDF SDK.
   *          Specially, Foxit PDF SDK will add some necessary information/data to the format part in
   *          the sample message, in order to make the message more useful. User is recommended to
   *          keep these format part in the re-written or translated result string; otherwise,
   *          these information/data will not be lost and will not be added to the message offered by user.
   *
   * @param[in] string_id  A string ID to specify a case. Please refer to values starting from
   *                       @link AppProviderCallback::e_StringIDValidateFailed @endlink and this would be one of these values.
   *
   * @return A string used for the specified case.
   */
  virtual WString LoadString(StringID string_id) = 0;

  /**
   * @brief A callback function used to show file dialog.
   *
   * @param[in] string_title        A string that represents the dialog title.
   * @param[in] string_filter       A string that represents the dialog file filter.
   * @param[in] is_openfile_dialog  <b>true</b> means the dialog is an open-file-dialog,
   *                                while <b>false</b> means the dialog is a save-as-dialog.
   *
   * @return An array of file paths.
   */
  virtual WStringArray ShowFileDialog(const wchar_t* string_title, const wchar_t* string_filter,
                                      bool is_openfile_dialog) = 0;

 protected:
  ~AppProviderCallback() {}
};

class XFAWidgetModifyInfo;
/**
 * This class represents a callback object as an XFA document provider.
 * All the functions in this class are used as callback functions. Pure virtual functions should be implemented
 * by user.
 */
class DocProviderCallback {
 public:
  /**
   * @brief Enumeration for XFA invalidate flag.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _InvalidateFlag {
    /** @brief Invalidate all pages. */
    e_InvalidateFlagAllPages = 0,
    /** @brief Invalidate current page. */
    e_InvalidateFlagCurrentPage = 1
  } InvalidateFlag;
  
  /**
   * @brief Enumeration for XFA print options.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PrintOption {
    /** @brief If set, show printing dialog box. */
    e_PrintOptionShowDialog = 0x00000001,
    /** @brief If set, that means printing process can be canceled. */
    e_PrintOptionCanCancel = 0x00000002,
    /** @brief If set, shrink page to fit within content area. */
    e_PrintOptionShrinkPage = 0x00000004,
    /** @brief If set, print page as image; otherwise, as text.*/
    e_PrintOptionAsImage = 0x00000008,
    /** @brief If set, print page in reverse order; otherwise, in normal order. */
    e_PrintOptionReverseOrder = 0x00000010,
    /** @brief If set, print annotations. */
    e_PrintOptionPrintAnnot = 0x00000020
  } PrintOption;
  
  /**
   * @brief Enumeration for XFA submit format.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _SubmitFormat {
    /** @brief The submit data is packaged in XDP format, as described in XDP Specification. */
    e_SubmitInXDP = 0,
    /** @brief The submit data is packaged in PDF format as described in the PDF Reference. */
    e_SubmitInPDF = 1,
    /** @brief The submit data is packaged in URL-encoded format as described in Uniform Resource Locator(URL). */
    e_SubmitInUrlEncoded = 2,
    /** @brief The submit data is packaged in XFD format, as described in XFDF. */
    e_SubmitInXFD= 3,
    /** @brief The submit data is translated and packaged into an URL-Encoded format. */
    e_SubmitInXML = 4
  } SubmitFormat;
  
  /**
   * @brief Enumeration for text encoding for XFA submit.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _TextEncoding {
    /** @brief No text encoding. */
    e_TextEncodingNone = 0,
    /** @brief Text encoding: Big5. */
    e_TextEncodingBig5 = 1,
    /** @brief Text encoding: font specific. */
    e_TextEncodingFontSpecific = 2,
    /** @brief Text encoding: GBK. */
    e_TextEncodingGBK = 3,
    /** @brief Text encoding: GB18030. */
    e_TextEncodingGB18030 = 4,
    /** @brief Text encoding: GB2312. */
    e_TextEncodingGB2312 = 5,
    /** @brief Text encoding: ISO8859NN. */
    e_TextEncodingISO8859NN = 6,
    /** @brief Text encoding: KSC5601. */
    e_TextEncodingKSC5601 = 7,
    /** @brief Text encoding: ShiftJIS. */
    e_TextEncodingShiftJIS = 8,
    /** @brief Text encoding: UCS-2. */
    e_TextEncodingUCS2 = 9,
    /** @brief Text encoding: UTF-16. */
    e_TextEncodingUTF16 = 10,
    /** @brief Text encoding: UTF-8. */
    e_TextEncodingUTF8 = 11
  } TextEncoding;
  
  /**
   * @brief Enumeration for the event type of page view.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PageViewEventType {
    /** @brief Event type: after a page view is added. */
    e_PageViewEventTypeAdded = 0,
    /** @brief Event type: after a page view is removed. */
    e_PageViewEventTypeRemoved = 1,
    /** @brief Event type: all page views are removed. */
    e_PageViewEventTypeAllRemoved = 2
  } PageViewEventType;
  
  /**
   * @brief Enumeration for the type of XFA widget event.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _WidgetEventType {
    /** @brief Event type: after an XFA widget is added. */
    e_WidgetEventTypeAdded = 0,
    /** @brief Event type: before an XFA widget is removed. */
    e_WidgetEventTypeBeforeRemoved = 1
  } WidgetEventType;
  

  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief A callback function used to invalidate rectangle according the flag.
   *
   * @details This callback function would be used in dynamic XFA document.
   *
   * @param[in] page_index  The index of page.
   * @param[in] rect        A rectangle to be invalidate.
   * @param[in] flag        Invalidate flag. Please refer to values starting from
   *                        @link DocProviderCallback::e_InvalidateFlagAllPages @endlink and this would be one of these values.
   *
   * @return None.
   */
  virtual void InvalidateRect(int page_index, const RectF& rect, InvalidateFlag flag) = 0;

  /**
   * @brief A callback function used to display or hide caret.
   *
   * @param[in] page_index  The index of page.
   * @param[in] is_visible  Used to decide whether the caret is visible or not: <b>true</b> means visible,
   *                        while <b>false</b> means invisible.
   * @param[in] rect        A rectangle.
   *
   * @return None.
   */
  virtual void DisplayCaret(int page_index, bool is_visible, const RectF& rect) = 0;

  /**
   * @brief A callback function used to get the pop-up position.
   *
   * @param[in] page_index            The index of page.
   * @param[in] min_popup             The minimum height of drop-down box.
   * @param[in] max_popup             The maximum height of drop-down box.
   * @param[in] rect_widget           The rectangle of current widget.
   * @param[in,out] inout_rect_popup  A rectangle. When this function calls, this is used as an input parameter
   *                                  that specifies the width of drop-down box.
   *                                  When this function returns, this is used as an output parameter that receives
   *                                  the height of drop-down box.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool GetPopupPos(int page_index, float min_popup, float max_popup,
                           const RectF& rect_widget, RectF& inout_rect_popup) = 0;

  /**
   * @brief A callback function used to pop up the context menu.
   *
   * @param[in] page_index  The index of page.
   * @param[in] rect_popup  The rectangle where to pop up menu.
   *
   * @return <b>TRUE</b> means success, otherwise means failure.
   */
  virtual bool PopupMenu(int page_index, const PointF& rect_popup) = 0;

  /**
   * @brief A callback function used to get index of current page.
   *
   * @param[in] doc  Current XFA document.
   *
   * @return The index of current page.
   */
  virtual int GetCurrentPage(const XFADoc& doc) = 0;

  /**
   * @brief A callback function used to set index of current page.
   *
   * @param[in] doc                 Current XFA document.
   * @param[in] current_page_index  The index would be set.
   *
   * @return None.
   */
  virtual void SetCurrentPage(const XFADoc& doc, int current_page_index) = 0;

  /**
   * @brief A callback function used to set change mark flag to current XFA document.
   *
   * @param[in] doc  Current XFA document.
   *
   * @return None.
   */
  virtual void SetChangeMark(const XFADoc& doc) = 0;

  /**
   * @brief A callback function used to get title of current XFA document.
   *
   * @param[in] doc  Current XFA document.
   *
   * @return The title.
   */
  virtual WString GetTitle(const XFADoc& doc) = 0;

  /**
   * @brief A callback function used to set focus widget.
   *
   * @param[in] xfa_widget   An XFA widget to be set focus on.
   * @param[in] is_relayout  <b>true</b> means the layout has changed,
   *                         while <b>false</b> means the layout has not changed.
   *
   * @return None.
   */
  virtual void SetFocus(XFAWidget& xfa_widget, bool is_relayout) = 0;

  /**
   * @brief A callback function used to export data to file.
   *
   * @param[in] doc        Current XFA document.
   * @param[in] file_path  A file path, to which the data should be exported.
   *                       If this is an empty string, user should specify a path as the exported file path.
   *                       In this case, application can show a dialog to user to let user select the file manually.
   *
   * @return None.
   */
  virtual void ExportData(const XFADoc& doc, const WString& file_path) = 0;

  /**
   * @brief A callback function used to import data from file.
   *
   * @param[in] doc        Current XFA document.
   * @param[in] file_path  A file path, from which the data would be imported.
   *                       If this is an empty string, user should specify a path as the imported file path.
   *                       In this case, application can show a dialog to user to let user select the file manually.
   *
   * @return None.
   */
  virtual void ImportData(const XFADoc& doc, const WString& file_path) = 0;

  /**
   * @brief A callback function used to go to a specified URL.
   *
   * @param[in] doc  Current XFA document.
   * @param[in] url  A URL string.
   *
   * @return None.
   */
  virtual void GotoURL(const XFADoc& doc, const WString& url) = 0;

  /**
   * @brief A callback function used to print.
   *
   * @param[in] doc               Current XFA document.
   * @param[in] start_page_index  The index of start page.
   * @param[in] end_page_index    The index of end page.
   * @param[in] options           Print options. Please refer to values starting from
   *                              @link DocProviderCallback::e_PrintOptionShowDialog @endlink
   *                              and this would be one or a combination of these values.
   *
   * @return None.
   */
  virtual void Print(const XFADoc& doc, int start_page_index, int end_page_index, uint32 options) = 0;

  /**
   * @brief A callback function get the highlight color.
   *
   * @param[in] doc  Current XFA document.
   *
   * @return The highlight color.
   */
  virtual ARGB GetHighlightColor(const XFADoc& doc) = 0;

  /**
   * @brief A callback function to submit data.
   *
   * @param[in] doc            Current XFA document.
   * @param[in] target         A string that represents the target of data to be submit.
   * @param[in] format         The format of data to be submit. Please refer to values starting from
   *                           @link DocProviderCallback::e_SubmitInXDP @endlink and this would be one of these values.
   * @param[in] text_encoding  The text encoding of data to be submit. Please refer to values starting from
   *                           @link DocProviderCallback::e_TextEncodingNone @endlink and this would be one of these values.
   * @param[in] content        The content of data to be submit.
   *
   * @return <b>TRUE</b> means success, otherwise means failure.
   */
  virtual bool SubmitData(const XFADoc& doc, const WString& target, SubmitFormat format, TextEncoding text_encoding,
                          const WString& content) = 0;

  /**
   * @brief A callback function to execute page view event.
   *
   * @param[in] page_index            The page index.
   * @param[in] page_view_event_type  Page view event type. Please refer to values starting from
   *                                  @link DocProviderCallback::e_PageViewEventTypeAdded @endlink and this would be
   *                                  one of these values.
   *
   * @return None.
   */
  virtual void PageViewEvent(int page_index, PageViewEventType page_view_event_type) = 0;

  /**
   * @brief A callback function to execute XFA widget event.
   *
   * @param[in] xfa_widget         An XFA widget which sends the event.
   * @param[in] widget_event_type  Widget event type. Please refer to values starting from
   *                               @link DocProviderCallback::e_WidgetEventTypeAdded @endlink and
   *                               this would be one of these values.
   *
   * @return None.
   */
  virtual void WidgetEvent(const XFAWidget& xfa_widget,WidgetEventType widget_event_type) = 0;

  /**
   * @brief A callback function to notify XFA widget change information.
   *
   * @param[in] doc          Current XFA document.
   * @param[in] change_info  The xfa widget change information.
   *
   * @return None.
   */
  virtual void NotifyWidgetChangeInfo(const XFADoc& doc, XFAWidgetModifyInfo change_info) = 0;
 protected:
  ~DocProviderCallback() {}
};

/**
 * Class @link XFADoc @endlink is constructed from a loaded PDF document object, in order to access XFA content more clearly.
 * User must call @link common::Library::RegisterXFAAppProviderCallback @endlink before using XFA moudle.
 * For a newly constructed XFA object, please remember to call function @link XFADoc::StartLoad @endlink before
 * using other functions in class XFA.<br>
 * To search among an XFA document, please construct a @link pdf::TextSearch @endlink object with @link XFADoc @endlink object.
 *
 * @see @link pdf::TextSearch @endlink
 */
class XFADoc FS_FINAL : public Base{
 public:
  /**
   * @brief Enumeration for XFA event type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _EventType {
    /** @brief Event type: Unknown. */
    e_EventTypeUnknown = 0,
    /**
     * @brief This kind of event is triggered just after the rendered form has been sent to the printer, spooler,
     *        or output destination.
     */
    e_EventTypePostPrint = 1,
    /** @brief This kind of event is triggered just before the rendering for printing begins. */
    e_EventTypePrePrint = 2,
    /** @brief This kind of event is triggered when the user clicks in the field. */
    e_EventTypeClick = 3,
    /** @brief This kind of event is triggered when the user changes the field value. */
    e_EventTypeChange = 4,
    /** @brief This kind of event is triggered at the very end of processing if and only if all validations succeeded. */
    e_EventTypeDocClose = 5,
    /** @brief This kind of event is triggered before the document is rendered but after data binding. */
    e_EventTypeDocReady = 6,
    /** 
     * @brief This kind of event is triggered when the field gains keyboard focus, whether caused by a user action
     *        (tabbing into the field or clicking on it with the mouse) or by a script programmatically setting
     *        the preSubmit event applies only to the Form DOM ($form). 
     */
    e_EventTypeEnter = 7,
    /** 
     * @brief This kind of event is triggered when keyboard focus is yielded from a field directly or indirectly within the
     *        subform to a field or other object outside the subform. 
     */
    e_EventTypeExit = 8,
    /** 
     * @brief This kind of event is triggered when the user has entered the maximum allowed amount of content into the field
     *        and tries to enter more content. 
     */
    e_EventTypeFull = 9,
    /** 
     * @brief This kind of event is triggered to tell an object that it has just been added to an array or that its position in
     *        the array (its subscript) has changed. 
     */
    e_EventTypeIndexChange = 10,
    /** @brief This kind of event is triggered after data binding is complete. */
    e_EventTypeInitialize = 11,
    /** 
     * @brief This kind of event is triggered when the mouse button is depressed at a moment and the mouse pointer is
     *        within the region. 
     */
    e_EventTypeMouseDown = 12,
    /** @brief This kind of event is triggered when the user moves the mouse pointer into the region of the field,
     *         without necessarily pressing the mouse button. 
     */
    e_EventTypeMouseEnter = 13,
    /** 
     * @brief This kind of event is triggered when user moves the mouse pointer out of the field, whether the mouse
     *        button is depressed or not. 
     */
    e_EventTypeMouseExit = 14,
    /** 
     * @brief This kind of event is triggered when the mouse button is released at a moment and the mouse pointer is
     *        within the region. 
     */
    e_EventTypeMouseUp = 15,
    /** 
     * @brief This kind of event is triggered after a successful WSDL transaction, just after the reply to the
     *        request has been received and the received data is marshalled in the Connection Data DOM. 
     */
    e_EventTypePostExecute = 16,
    /** @brief This kind of event is related to pre-open event for drop-down choice lists. */
    e_EventTypePostOpen = 17,
    /** @brief This kind of event is triggered just after the form has been written out in PDF or XDP format. */
    e_EventTypePostSave = 18,
    /** @brief This kind of event is triggered after successfully applying a signature. */
    e_EventTypePostSign = 19,
    /** @brief This kind of event is triggered just after the returned data has been marshalled in the Connection Data DOM. */
    e_EventTypePostSubmit = 20,
    /** 
     * @brief This kind of event is triggered when a request is sent to a web service via WSDL, just after the data
     *        has been marshalled in the Connection Data DOM but before the request has been sent. 
     */
    e_EventTypePreExecute = 21,
    /** 
     * @brief This kind of event applies only to drop-down choice lists for which open="userControl" or open="onEntry".
     *        The event is intended to trigger scripts that add choices to and remove choices from the choice list. 
     */
    e_EventTypePreOpen = 22,
    /** @brief This kind of event is triggered just before the form data is written out in PDF or XDP format. */
    e_EventTypePreSave = 23,
    /** @brief This kind of event is triggered when a signature is about to be applied. */
    e_EventTypePreSign = 24,
    /** 
     * @brief This kind of event is triggered just after the data has been marshalled in the Connection Data DOM but before
     *        validation and before the data is submitted to the host. 
     */
    e_EventTypePreSubmit = 25,
    /** @brief This kind of event is triggered after an XFA DOM has finished loading. */
    e_EventTypeReady = 26,
    /** @brief This kind of event is triggered whenever the validation state of the target changes. */
    e_EventTypeValidationState = 27,
    /** @brief This kind of event represents the first run calculate. */
    e_EventTypeInitCalculate = 28,
    /** @brief This kind of event is not a real event activity, just sign script in variables. */
    e_EventTypeInitVariables = 29,
    /** @brief This kind of event represents a calculate operation. */
    e_EventTypeCalculate = 30,
    /** @brief This kind of event represents a validate operation. */
    e_EventTypeValidate = 31
  } EventType;
  
  /**
   * @brief Enumeration for XFA document type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Type {
    /** @brief XFA document type: Dynamic. */
    e_Dynamic = 0,
    /** @brief XFA document type: Static. */
    e_Static = 1,
    /** @brief XFA document type: XDP, as Raw XML data. */
    e_XDP = 2
  } Type;
  
  /**
   * @brief Enumeration for the type of exported data.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ExportDataType {
    /** @brief Type of exported data: XML. */
    e_ExportDataTypeXML = 0,
    /** @brief Type of exported data: Static XDP. */
    e_ExportDataTypeStaticXDP = 1,
    /** @brief Type of exported data: XDP. */
    e_ExportDataTypeXDP = 2
  } ExportDataType;
  

  /**
   * @brief Constructor.
   *
   * @param[in] document                  A valid PDF document. It should has been loaded successfully.
   * @param[in] xfa_doc_provider_handler  An XFA document provider callback object which is implemented by user
   *                                      and based on callback class @link DocProviderCallback @endlink. It should not be
   *                                      <b>NULL</b>. User should ensure this callback object is kept valid until
   *                                      related PDF document is released.
   *
   * @note If module "XFA" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using XFA related functions and
   *       this constructor will throw exception @link foxit::e_ErrNoXFAModuleRight @endlink.
   */
  XFADoc(const pdf::PDFDoc& document, DocProviderCallback* xfa_doc_provider_handler);

  /**
   * @brief Constructor.
   *
   * @details When constructing an XFADoc by this constructor successfully, user must set XFA document provider callback
   *          by function @link XFADoc::SetDocProviderCallback @endlink.
   *
   * @param[in] document  A valid PDF document. It should has been loaded successfully.
   *
   * @note If module "XFA" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using XFA related functions and
   *       this constructor will throw exception @link foxit::e_ErrNoXFAModuleRight @endlink.
   */
  XFADoc(const foxit::pdf::PDFDoc& document);

  /**
   * @brief Constructor, with another XFA document object.
   *
   * @param[in] other  Another XFA document object
   */
  XFADoc(const XFADoc& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another XFA document object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  XFADoc& operator = (const XFADoc& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another XFA document object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const XFADoc& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another XFA document object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const XFADoc& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /** @brief Destructor. */
  ~XFADoc();

  /**
   * @brief Start to load content for current XFA document.
   *
   * @details It may take a long time to loading XFA content, so this function uses a progressive process to
   *          do this.<br>
   *          The related PDF document object has been loaded, but only PDF related contents have been loaded.
   *          So, in order to access XFA content, this function should be called to load XFA content.
   *
   * @param[in] pause  Pause object which decides if the importing process needs to be paused.
   *                   This can be <b>NULL</b> which means not to pause during the parsing process.
   *                   If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                   Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  common::Progressive StartLoad(common::PauseCallback* pause = NULL);

  /**
   * @brief Set XFA document provider callback.
   *
   * @param[in] doc_provider_callback  An XFA document provider callback object which is implemented by user
   *                                   and based on callback class @link DocProviderCallback @endlink. It should not be
   *                                   <b>NULL</b>. User should ensure this callback object is kept valid until
   *                                   related PDF document is released.
   *
   * @return None.
   */
  void SetDocProviderCallback(foxit::addon::xfa::DocProviderCallback* doc_provider_callback);

  /**
   * @brief Get the XFA document type.
   *
   * @return The type of XFA document. Please refer to values starting from @link XFADoc::e_Dynamic @endlink and
   *         this would be one of these values.
   */
  Type GetType() const;

  /**
   * @brief Get XFA page count.
   *
   * @return Page count.
   */
  int GetPageCount() const;

  /**
   * @brief Get XFA page by index.
   *
   * @param[in] page_index  The page index. Valid range: from 0 to (<i>count</i>-1).
   *                        <i>count</i> is returned by function @link XFADoc::GetPageCount @endlink.
   *
   * @return The XFA page.
   */
  XFAPage GetPage(int page_index);

  /**
   * @brief Export data to a file.
   *
   * @param[in] output_file_path  A file path, to which data will be exported to.
   * @param[in] export_type       Export type. Please refer to values starting from @link XFADoc::e_ExportDataTypeXML @endlink
   *                              and this should be one of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ExportData(const char* output_file_path, ExportDataType export_type);

  /**
   * @brief Export data to a file.
   *
   * @param[in] output_file_path  A file path, to which data will be exported to.
   * @param[in] export_type       Export type. Please refer to values starting from @link XFADoc::e_ExportDataTypeXML @endlink
   *                              and this should be one of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ExportData(const wchar_t* output_file_path, ExportDataType export_type);
  
  /**
   * @brief Export data to a @link common::file::WriterCallback @endlink object.
   *
   * @param[in] stream       A @link foxit::common::file::WriterCallback @endlink object which is implemented by user to save the exported data.
   * @param[in] export_type  Export type. Please refer to values starting from @link XFADoc::e_ExportDataTypeXML @endlink
   *                         and this should be one of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ExportData(foxit::common::file::WriterCallback* stream, ExportDataType export_type);

  /**
   * @brief Set the path of related PDF document.
   *
   * @details The PDF path will be used in function @link XFADoc::ExportData @endlink, to be a part of exported data.
   *
   * @param[in] pdf_file_path  The file path of related PDF document. It can be either an absolute path or
   *                           a relative path. It should not be an empty string.
   *
   * @return None.
   */
  void SetPDFPath(const char* pdf_file_path);

  /**
   * @brief Set the path of related PDF document.
   *
   * @details The PDF path will be used in function @link XFADoc::ExportData @endlink, to be a part of exported data.
   *
   * @param[in] pdf_file_path  The file path of related PDF document. It can be either an absolute path or
   *                           a relative path. It should not be an empty string.
   *
   * @return None.
   */
  void SetPDFPath(const wchar_t* pdf_file_path);

  /**
   * @brief Import data from an XML or XDP file.
   *
   * @param[in] file_path  A path of a source file, whose data will be imported to current XFA document.
   *                       It should be XML or XDP file and the file extension should be ".xml" or ".xdp".
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ImportData(const char* file_path);

  /**
   * @brief Import data from an XML or XDP file.
   *
   * @param[in] file_path  A path of a source file, whose data will be imported to current XFA document.
   *                       It should be XML or XDP file and the file extension should be ".xml" or ".xdp".
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ImportData(const wchar_t* file_path);

  /**
   * @brief Import data from a @link common::file::ReaderCallback @endlink object.
   *
   * @param[in] file_reader   A @link common::file::ReaderCallback @endlink object, whose data will be imported to current XFA document.
   *                          It should be XML or XDP file.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ImportData(foxit::common::file::ReaderCallback* file_reader);

  /**
   * @brief Reset form.
   *
   * @return None.
   */
  void ResetForm();

  /**
   * @brief Flatten current XFA document to a file.
   *
   * @param[in] output_file_path  A file path, to which the flattening result will be saved.
   *
   * @return None.
   */
  void FlattenTo(const char* output_file_path);

  /**
   * @brief Flatten current XFA document to a file.
   *
   * @param[in] output_file_path  A file path, to which the flattening result will be saved.
   *
   * @return None.
   */
  void FlattenTo(const wchar_t* output_file_path);

  /**
   * @brief Flatten current XFA document to a file stream.
   *
   * @param[in] stream  A @link foxit::common::file::StreamCallback @endlink object which is implemented by user to save the flattened result.
   *
   * @return None.
   */
  void FlattenTo(foxit::common::file::StreamCallback* stream);

  /**
   * @brief Process a kind of event for all the XFA widgets in current XFA document.
   *
   * @param[in] event_type  An event type. Please refer to values starting from @link XFADoc::e_EventTypePostPrint @endlink
   *                        and this should be one of these values except @link XFADoc::e_EventTypeUnknown @endlink. Currently, 
   *                        only @link XFADoc::e_EventTypePostPrint @endlink and @link XFADoc::e_EventTypePrePrint @endlink are supported.
   *
   * @return None.
   */
  void ProcessEvent(EventType event_type);

  /**
   * @brief Set the focus of XFA widget.
   *
   * @param[in] xfa_widget  An XFA widget which would be focused.
   *
   * @return None.
   */
  void SetFocus(XFAWidget xfa_widget);

  /**
   * @brief Kill the focus of XFA widget.
   *
   * @return None.
   */
  void KillFocus();

  /**
   * @brief Get the XFA widget which matches the specified full name.
   *
   * @details Some XFA widgets may cover serveral XFA pages. In this case, this function can only be used to
   *          get the first matched XFA widget in XFA document. User can also use function @link XFAPage::GetWidgetByFullName @endlink
   *          to get the matched XFA widget in an XFA page.
   *
   * @param[in] full_name  An XFA widget's full name. It should not be an empty string.
   *                       XFA widget's full name can be retrieved by function @link XFAWidget::GetName @endlink
   *                       with type @link XFAWidget::e_WidgetNameTypeFullName @endlink in previous process.
   *
   * @return An XFA Widget object.
   */
  XFAWidget GetWidgetByFullName(const WString& full_name);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit XFADoc(FS_HANDLE handle =  NULL);

};

/**
 * Class @link XFAPage @endlink represents the XFA page which is retrieved from XFA document object.<br>
 * To render an XFA page, please use function @link common::Renderer::StartRenderXFAPage @endlink.
 *
 * @see @link common::Renderer @endlink
 */
class XFAPage FS_FINAL : public Base{
 public:
  /**
   * @brief Constructor, with another XFA page object.
   *
   * @param[in] other  Another XFA page object.
   */
  XFAPage(const XFAPage& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another XFA page object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  XFAPage& operator = (const XFAPage& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another XFA page object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const XFAPage& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another XFA page object. This function will check if current object is bot equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const XFAPage& other) const;

  /** @brief Destructor. */
  ~XFAPage();

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the display matrix, from PDF coordinate system to targeted device coordinate system.
   *
   * @param[in] left    Left position of the transformation area in device coordinate system, commonly in pixels.
   * @param[in] top     Top position of the transformation area in device coordinate system, commonly in pixels.
   * @param[in] width   Width of the transformation area in device coordinate system, commonly in pixels.
   * @param[in] height  Height of the transformation area in device coordinate system, commonly in pixels.
   * @param[in] rotate  Rotation value. Please refer to values starting from @link common::e_Rotation0 @endlink and
   *                    this should be one of these values.
   *
   * @return A Matrix object that receives the display matrix used for current XFA page.
   *         If there is any error, a Matrix with all value 0 will be returned.
   */
  Matrix GetDisplayMatrix(int left, int top, int width, int height, common::Rotation rotate);

  /**
   * @brief Get the width.
   *
   * @return A float value that receives the width of current XFA page.
   */
  float GetWidth() const;

  /**
   * @brief Get the height of the XFA page.
   *
   * @return A float value that receives the height of current XFA page.
   */
  float GetHeight() const;

  /**
   * @brief Get the XFA widget at a specified point, in device coordinate system.
   *
   * @param[in] matrix        The transformation matrix. Usually this is returned by function
   *                          @link XFAPage::GetDisplayMatrix @endlink.
   * @param[in] device_point  A point in device coordinate system.
   * @param[in] tolerance     Tolerance value. Valid range: 0.0f to 30.0f.
   *
   * @return An XFA Widget object.
   */
  XFAWidget GetWidgetAtDevicePoint(const Matrix& matrix, const PointF& device_point, float tolerance);

  /**
   * @brief Get index of the XFA page.
   *
   * @return The index of XFA page.
   */
  int GetIndex() const;

  /**
   * @brief Get the count of XFA widget.
   *
   * @return The count of XFA widget.
   */
  int GetWidgetCount() const;

  /**
   * @brief Get XFA widget by index.
   *
   * @param[in] widget_index  The XFA widget index. Valid range: from 0 to (<i>count</i>-1).
   *                          <i>count</i> is returned by function @link XFAPage::GetWidgetCount @endlink.
   *
   * @return The XFA widget.
   */
  XFAWidget GetWidget(int widget_index) const;

  /**
   * @brief Get the XFA widget which matches the specified full name in current XFA page.
   *
   * @param[in] full_name  An XFA widget's full name. It should not be an empty string.
   *                       XFA widget's full name can be retrieved by function @link XFAWidget::GetName @endlink
   *                       with type @link XFAWidget::e_WidgetNameTypeFullName @endlink in previous process.
   *
   * @return An XFA Widget object.
   */
  XFAWidget GetWidgetByFullName(const WString& full_name);

  /**
   * @brief Get the first XFA widget in current tab order.
   *
   * @return The first XFA widget. If the return value of function @link XFAWidget::IsEmpty @endlink for
   *         the returned XFA widget object is <b>true</b>, that means there is no XFA widget.
   */
  XFAWidget GetFirstWidget();

  /**
   * @brief Get the last XFA widget in current tab order.
   *
   * @return The last XFA widget. If the return value of function @link XFAWidget::IsEmpty @endlink for
   *         the returned XFA widget object is <b>true</b>, that means there is no XFA widget.
   */
  XFAWidget GetLastWidget();

  /**
   * @brief Get the next XFA widget of a specified XFA widget in current tab order.
   *
   * @param[in] widget  A valid specified  XFA widget.
   *
   * @return The next XFA widget. If the return value of function @link XFAWidget::IsEmpty @endlink for
   *         the returned XFA widget object is <b>true</b>, that means the specified XFA widget is the last XFA widget
   *         in current tab order.
   */
  XFAWidget GetNextWidget(const XFAWidget& widget);

  /**
   * @brief Get the previous XFA widget of a specified  XFA widget in current tab order.
   *
   * @param[in] widget  A valid specified  XFA widget.
   *
   * @return The previous XFA widget. If the return value of function @link XFAWidget::IsEmpty @endlink for
   *         the returned XFA widget object is <b>true</b>, that means the specified XFA widget is the previous XFA widget
   *         in current tab order.
   */
  XFAWidget GetPrevWidget(const XFAWidget& widget);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit XFAPage(FS_HANDLE handle =  NULL);
};

/** This class represents the xfa widget modify information */
class XFAWidgetModifyInfo : public Object {
 public:
  /**
   * @brief Enumeration for the positon of XFA widget element.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _WidgetElement {
    /** @brief XFA widget element: Ps.*/
    e_WidgetElementPs = 0,
    /** @brief XFA widget element: To.*/
    e_WidgetElementTo = 1,
    /** @brief XFA widget element: Ui.*/
    e_WidgetElementUi = 2,
    /** @brief XFA widget element: Record set.*/
    e_WidgetElementRecordSet = 3,
    /** @brief XFA widget element: Subset below.*/
    e_WidgetElementSubsetBelow = 4,
    /** @brief XFA widget element: Subform set.*/
    e_WidgetElementSubformSet = 5,
    /** @brief XFA widget element: Adobe extension level.*/
    e_WidgetElementAdobeExtensionLevel = 6,
    /** @brief XFA widget element: Type face.*/
    e_WidgetElementTypeface = 7,
    /** @brief XFA widget element: Break.*/
    e_WidgetElementBreak = 8,
    /** @brief XFA widget element: Font info.*/
    e_WidgetElementFontInfo = 9,
    /** @brief XFA widget element: Number pattern.*/
    e_WidgetElementNumberPattern = 10,
    /** @brief XFA widget element: Dynamic render.*/
    e_WidgetElementDynamicRender = 11,
    /** @brief XFA widget element: Print scaling.*/
    e_WidgetElementPrintScaling = 12,
    /** @brief XFA widget element: Check button.*/
    e_WidgetElementCheckButton = 13,
    /** @brief XFA widget element: Date patterns.*/
    e_WidgetElementDatePatterns = 14,
    /** @brief XFA widget element: Source set.*/
    e_WidgetElementSourceSet = 15,
    /** @brief XFA widget element: Amd.*/
    e_WidgetElementAmd = 16,
    /** @brief XFA widget element: Arc.*/
    e_WidgetElementArc = 17,
    /** @brief XFA widget element: Day.*/
    e_WidgetElementDay = 18,
    /** @brief XFA widget element: Era.*/
    e_WidgetElementEra = 19,
    /** @brief XFA widget element: Jog.*/
    e_WidgetElementJog= 20,
    /** @brief XFA widget element: Log.*/
    e_WidgetElementLog = 21,
    /** @brief XFA widget element: Map.*/
    e_WidgetElementMap = 22,
    /** @brief XFA widget element: Mdp.*/
    e_WidgetElementMdp = 23,
    /** @brief XFA widget element: Break before.*/
    e_WidgetElementBreakBefore = 24,
    /** @brief XFA widget element: Oid.*/
    e_WidgetElementOid = 25,
    /** @brief XFA widget element: Pcl.*/
    e_WidgetElementPcl = 26,
    /** @brief XFA widget element: Pdf.*/
    e_WidgetElementPdf = 27,
    /** @brief XFA widget element: Ref.*/
    e_WidgetElementRef = 28,
    /** @brief XFA widget element: Uri.*/
    e_WidgetElementUri = 29,
    /** @brief XFA widget element: Xdc.*/
    e_WidgetElementXdc = 30,
    /** @brief XFA widget element: Xdp.*/
    e_WidgetElementXdp = 31,
    /** @brief XFA widget element: Xfa.*/
    e_WidgetElementXfa = 32,
    /** @brief XFA widget element: Xsl.*/
    e_WidgetElementXsl = 33,
    /** @brief XFA widget element: Zpl.*/
    e_WidgetElementZpl = 34,
    /** @brief XFA widget element: Cache.*/
    e_WidgetElementCache = 35,
    /** @brief XFA widget element: Margin.*/
    e_WidgetElementMargin = 36,
    /** @brief XFA widget element: Key usage.*/
    e_WidgetElementKeyUsage = 37,
    /** @brief XFA widget element: Exclude.*/
    e_WidgetElementExclude = 38,
    /** @brief XFA widget element: Choice list.*/
    e_WidgetElementChoiceList = 39,
    /** @brief XFA widget element: Level.*/
    e_WidgetElementLevel = 40,
    /** @brief XFA widget element: Label printer.*/
    e_WidgetElementLabelPrinter = 41,
    /** @brief XFA widget element: Calendar symbols.*/
    e_WidgetElementCalendarSymbols = 42,
    /** @brief XFA widget element: Para.*/
    e_WidgetElementPara = 43,
    /** @brief XFA widget element: Part.*/
    e_WidgetElementPart = 44,
    /** @brief XFA widget element: Pdfa.*/
    e_WidgetElementPdfa = 45,
    /** @brief XFA widget element: Filter.*/
    e_WidgetElementFilter = 46,
    /** @brief XFA widget element: Present.*/
    e_WidgetElementPresent = 47,
    /** @brief XFA widget element: Pagination.*/
    e_WidgetElementPagination = 48,
    /** @brief XFA widget element: Encoding.*/
    e_WidgetElementEncoding = 49,
    /** @brief XFA widget element: Event.*/
    e_WidgetElementEvent = 50,
    /** @brief XFA widget element: Whitespace.*/
    e_WidgetElementWhitespace = 51,
    /** @brief XFA widget element: Default Ui.*/
    e_WidgetElementDefaultUi = 52,
    /** @brief XFA widget element: Data model.*/
    e_WidgetElementDataModel = 53,
    /** @brief XFA widget element: Barcode.*/
    e_WidgetElementBarcode = 54,
    /** @brief XFA widget element: Time pattern.*/
    e_WidgetElementTimePattern = 55,
    /** @brief XFA widget element: Batch output.*/
    e_WidgetElementBatchOutput = 56,
    /** @brief XFA widget element: Enforce.*/
    e_WidgetElementEnforce = 57,
    /** @brief XFA widget element: Currency symbols.*/
    e_WidgetElementCurrencySymbols = 58,
    /** @brief XFA widget element: Add silent print.*/
    e_WidgetElementAddSilentPrint = 59,
    /** @brief XFA widget element: Rename.*/
    e_WidgetElementRename = 60,
    /** @brief XFA widget element: Operation.*/
    e_WidgetElementOperation = 61,
    /** @brief XFA widget element: Typefaces.*/
    e_WidgetElementTypefaces = 62,
    /** @brief XFA widget element: DNs.*/
    e_WidgetElementSubjectDNs = 63,
    /** @brief XFA widget element: Issuers.*/
    e_WidgetElementIssuers = 64,
    /** @brief XFA widget element: Signature pseudo model.*/
    e_WidgetElementSignaturePseudoModel = 65,
    /** @brief XFA widget element: Wsdl connection.*/
    e_WidgetElementWsdlConnection = 66,
    /** @brief XFA widget element: Debug.*/
    e_WidgetElementDebug = 67,
    /** @brief XFA widget element: Delta.*/
    e_WidgetElementDelta = 68,
    /** @brief XFA widget element: Era names.*/
    e_WidgetElementEraNames = 69,
    /** @brief XFA widget element: Modify annots.*/
    e_WidgetElementModifyAnnots = 70,
    /** @brief XFA widget element: Start node.*/
    e_WidgetElementStartNode = 71,
    /** @brief XFA widget element: Button.*/
    e_WidgetElementButton = 72,
    /** @brief XFA widget element: Format.*/
    e_WidgetElementFormat = 73,
    /** @brief XFA widget element: Border.*/
    e_WidgetElementBorder = 74,
    /** @brief XFA widget element: Area.*/
    e_WidgetElementArea = 75,
    /** @brief XFA widget element: Hyphenation.*/
    e_WidgetElementHyphenation = 76,
    /** @brief XFA widget element: Text.*/
    e_WidgetElementText = 77,
    /** @brief XFA widget element: Time.*/
    e_WidgetElementTime = 78,
    /** @brief XFA widget element: Type.*/
    e_WidgetElementType = 79,
    /** @brief XFA widget element: Overprint.*/
    e_WidgetElementOverprint = 80,
    /** @brief XFA widget element: Certificates.*/
    e_WidgetElementCertificates = 81,
    /** @brief XFA widget element: Encrypt methods.*/
    e_WidgetElementEncryptionMethods = 82,
    /** @brief XFA widget element: Set property.*/
    e_WidgetElementSetProperty = 83,
    /** @brief XFA widget element: Printer name.*/
    e_WidgetElementPrinterName = 84,
    /** @brief XFA widget element: Start page.*/
    e_WidgetElementStartPage = 85,
    /** @brief XFA widget element: Page offset.*/
    e_WidgetElementPageOffset = 86,
    /** @brief XFA widget element: DateTime.*/
    e_WidgetElementDateTime = 87,
    /** @brief XFA widget element: Comb.*/
    e_WidgetElementComb = 88,
    /** @brief XFA widget element: Pattern.*/
    e_WidgetElementPattern = 89,
    /** @brief XFA widget element: If empty.*/
    e_WidgetElementIfEmpty = 90,
    /** @brief XFA widget element: Suppress banner.*/
    e_WidgetElementSuppressBanner = 91,
    /** @brief XFA widget element: Output bin.*/
    e_WidgetElementOutputBin = 92,
    /** @brief XFA widget element: Field.*/
    e_WidgetElementField = 93,
    /** @brief XFA widget element: Agent.*/
    e_WidgetElementAgent = 94,
    /** @brief XFA widget element: Output XSL.*/
    e_WidgetElementOutputXSL = 95,
    /** @brief XFA widget element: Adjust data.*/
    e_WidgetElementAdjustData = 96,
    /** @brief XFA widget element: Auto save.*/
    e_WidgetElementAutoSave = 97,
    /** @brief XFA widget element: Content area.*/
    e_WidgetElementContentArea = 98,
    /** @brief XFA widget element: Event pseudo model.*/
    e_WidgetElementEventPseudoModel = 99,
    /** @brief XFA widget element: Wsdl address.*/
    e_WidgetElementWsdlAddress = 100,
    /** @brief XFA widget element: Solid.*/
    e_WidgetElementSolid = 101,
    /** @brief XFA widget element: Date time symbols.*/
    e_WidgetElementDateTimeSymbols = 102,
    /** @brief XFA widget element: Encryption level.*/
    e_WidgetElementEncryptionLevel = 103,
    /** @brief XFA widget element: Edge.*/
    e_WidgetElementEdge = 104,
    /** @brief XFA widget element: Stipple.*/
    e_WidgetElementStipple = 105,
    /** @brief XFA widget element: Attributes.*/
    e_WidgetElementAttributes = 106,
    /** @brief XFA widget element: Version control.*/
    e_WidgetElementVersionControl = 107,
    /** @brief XFA widget element: Meridiem.*/
    e_WidgetElementMeridiem = 108,
    /** @brief XFA widget element: Excl group.*/
    e_WidgetElementExclGroup = 109,
    /** @brief XFA widget element: Tool tip.*/
    e_WidgetElementToolTip = 110,
    /** @brief XFA widget element: Compress.*/
    e_WidgetElementCompress = 111,
    /** @brief XFA widget element: Reason.*/
    e_WidgetElementReason = 112,
    /** @brief XFA widget element: Execute.*/
    e_WidgetElementExecute = 113,
    /** @brief XFA widget element: Content copy.*/
    e_WidgetElementContentCopy = 114,
    /** @brief XFA widget element: Date time edit.*/
    e_WidgetElementDateTimeEdit = 115,
    /** @brief XFA widget element: Config.*/
    e_WidgetElementConfig = 116,
    /** @brief XFA widget element: Image.*/
    e_WidgetElementImage = 117,
    /** @brief XFA widget element: Sharpx HTML.*/
    e_WidgetElementSharpxHTML = 118,
    /** @brief XFA widget element: Number of copies.*/
    e_WidgetElementNumberOfCopies = 119,
    /** @brief XFA widget element: Behavior override.*/
    e_WidgetElementBehaviorOverride = 120,
    /** @brief XFA widget element: Time stamp.*/
    e_WidgetElementTimeStamp = 121,
    /** @brief XFA widget element: Month.*/
    e_WidgetElementMonth = 122,
    /** @brief XFA widget element: Viewer preferences.*/
    e_WidgetElementViewerPreferences = 123,
    /** @brief XFA widget element: Script model.*/
    e_WidgetElementScriptModel = 124,
    /** @brief XFA widget element: Decimal.*/
    e_WidgetElementDecimal = 125,
    /** @brief XFA widget element: Subform.*/
    e_WidgetElementSubform = 126,
    /** @brief XFA widget element: Select.*/
    e_WidgetElementSelect = 127,
    /** @brief XFA widget element: Window.*/
    e_WidgetElementWindow = 128,
    /** @brief XFA widget element: Locale set.*/
    e_WidgetElementLocaleSet = 129,
    /** @brief XFA widget element: Handler.*/
    e_WidgetElementHandler = 130,
    /** @brief XFA widget element: Host pseudo model.*/
    e_WidgetElementHostPseudoModel = 131,
    /** @brief XFA widget element: Presence.*/
    e_WidgetElementPresence = 132,
    /** @brief XFA widget element: Record.*/
    e_WidgetElementRecord = 133,
    /** @brief XFA widget element: Embed.*/
    e_WidgetElementEmbed = 134,
    /** @brief XFA widget element: Version.*/
    e_WidgetElementVersion = 135,
    /** @brief XFA widget element: Command.*/
    e_WidgetElementCommand = 136,
    /** @brief XFA widget element: Copies.*/
    e_WidgetElementCopies = 137,
    /** @brief XFA widget element: Staple.*/
    e_WidgetElementStaple = 138,
    /** @brief XFA widget element: Submit format.*/
    e_WidgetElementSubmitFormat = 139,
    /** @brief XFA widget element: Boolean.*/
    e_WidgetElementBoolean = 140,
    /** @brief XFA widget element: Message.*/
    e_WidgetElementMessage = 141,
    /** @brief XFA widget element: Output.*/
    e_WidgetElementOutput = 142,
    /** @brief XFA widget element: Ps Map.*/
    e_WidgetElementPsMap = 143,
    /** @brief XFA widget element: Exclude NS.*/
    e_WidgetElementExcludeNS = 144,
    /** @brief XFA widget element: Assist.*/
    e_WidgetElementAssist = 145,
    /** @brief XFA widget element: Picture.*/
    e_WidgetElementPicture = 146,
    /** @brief XFA widget element: traversal.*/
    e_WidgetElementTraversal = 147,
    /** @brief XFA widget element: slient print.*/
    e_WidgetElementSilentPrint = 148,
    /** @brief XFA widget element: Web client.*/
    e_WidgetElementWebClient = 149,
    /** @brief XFA widget element: Layout pseudo model.*/
    e_WidgetElementLayoutPseudoModel = 150,
    /** @brief XFA widget element: Producer.*/
    e_WidgetElementProducer =151,
    /** @brief XFA widget element: Corner.*/
    e_WidgetElementCorner = 152,
    /** @brief XFA widget element: Msg Id.*/
    e_WidgetElementMsgId = 153,
    /** @brief XFA widget element: Color.*/
    e_WidgetElementColor = 154,
    /** @brief XFA widget element: Keep.*/
    e_WidgetElementKeep = 155,
    /** @brief XFA widget element: Query.*/
    e_WidgetElementQuery = 156,
    /** @brief XFA widget element: Insert.*/
    e_WidgetElementInsert = 157,
    /** @brief XFA widget element: Image edit.*/
    e_WidgetElementImageEdit = 158,
    /** @brief XFA widget element: Validate.*/
    e_WidgetElementValidate = 159,
    /** @brief XFA widget element: Digest methods.*/
    e_WidgetElementDigestMethods = 160,
    /** @brief XFA widget element: Number patterns.*/
    e_WidgetElementNumberPatterns = 161,
    /** @brief XFA widget element: Page set.*/
    e_WidgetElementPageSet = 162,
    /** @brief XFA widget element: Integer.*/
    e_WidgetElementInteger = 163,
    /** @brief XFA widget element: Soap address.*/
    e_WidgetElementSoapAddress = 164,
    /** @brief XFA widget element: Equate.*/
    e_WidgetElementEquate = 165,
    /** @brief XFA widget element: Form field filling.*/
    e_WidgetElementFormFieldFilling = 166,
    /** @brief XFA widget element: Page range.*/
    e_WidgetElementPageRange = 167,
    /** @brief XFA widget element: Update.*/
    e_WidgetElementUpdate = 168,
    /** @brief XFA widget element: Connect string.*/
    e_WidgetElementConnectString = 169,
    /** @brief XFA widget element: Mode.*/
    e_WidgetElementMode = 170,
    /** @brief XFA widget element: Layout.*/
    e_WidgetElementLayout = 171,
    /** @brief XFA widget element: Sharpxml.*/
    e_WidgetElementSharpxml = 172,
    /** @brief XFA widget element: Xsd connection.*/
    e_WidgetElementXsdConnection = 173,
    /** @brief XFA widget element: Traverse.*/
    e_WidgetElementTraverse = 174,
    /** @brief XFA widget element: Encodings.*/
    e_WidgetElementEncodings = 175,
    /** @brief XFA widget element: Template.*/
    e_WidgetElementTemplate = 176,
    /** @brief XFA widget element: Acrobat.*/
    e_WidgetElementAcrobat = 177,
    /** @brief XFA widget element: Validation messaging.*/
    e_WidgetElementValidationMessaging = 178,
    /** @brief XFA widget element: Signing.*/
    e_WidgetElementSigning = 179,
    /** @brief XFA widget element: Data window.*/
    e_WidgetElementDataWindow = 180,
    /** @brief XFA widget element: Script.*/
    e_WidgetElementScript = 181,
    /** @brief XFA widget element: Add viewer preferences.*/
    e_WidgetElementAddViewerPreferences = 182,
    /** @brief XFA widget element: Always embed.*/
    e_WidgetElementAlwaysEmbed = 183,
    /** @brief XFA widget element: Password edit .*/
    e_WidgetElementPasswordEdit = 184,
    /** @brief XFA widget element: Numeric edit.*/
    e_WidgetElementNumericEdit = 185,
    /** @brief XFA widget element: Encryption method.*/
    e_WidgetElementEncryptionMethod = 186,
    /** @brief XFA widget element: Change.*/
    e_WidgetElementChange = 187,
    /** @brief XFA widget element: Page area.*/
    e_WidgetElementPageArea = 188,
    /** @brief XFA widget element: Submit Url.*/
    e_WidgetElementSubmitUrl = 189,
    /** @brief XFA widget element: Oids.*/
    e_WidgetElementOids = 190,
    /** @brief XFA widget element: Signature.*/
    e_WidgetElementSignature = 191,
    /** @brief XFA widget element: ADBE_JSConsole.*/
    e_WidgetElementADBE_JSConsole = 192,
    /** @brief XFA widget element: Caption.*/
    e_WidgetElementCaption = 193,
    /** @brief XFA widget element: Relevant.*/
    e_WidgetElementRelevant = 194,
    /** @brief XFA widget element: Flip label.*/
    e_WidgetElementFlipLabel = 195,
    /** @brief XFA widget element: Ex data.*/
    e_WidgetElementExData = 196,
    /** @brief XFA widget element: Day names.*/
    e_WidgetElementDayNames = 197,
    /** @brief XFA widget element: Soap action */
    e_WidgetElementSoapAction = 198,
    /** @brief XFA widget element: Default typeface.*/
    e_WidgetElementDefaultTypeface = 199,
    /** @brief XFA widget element: Manifest.*/
    e_WidgetElementManifest = 200,
    /** @brief XFA widget element: Overflow.*/
    e_WidgetElementOverflow = 201,
    /** @brief XFA widget element: Linear.*/
    e_WidgetElementLinear = 202,
    /** @brief XFA widget element: Currency symbol.*/
    e_WidgetElementCurrencySymbol = 203,
    /** @brief XFA widget element: Delete.*/
    e_WidgetElementDelete = 204,
    /** @brief XFA widget element: Deltas.*/
    e_WidgetElementDeltas = 205,
    /** @brief XFA widget element: Digest method.*/
    e_WidgetElementDigestMethod = 206,
    /** @brief XFA widget element: Instance manager.*/
    e_WidgetElementInstanceManager = 207,
    /** @brief XFA widget element: Equate range.*/
    e_WidgetElementEquateRange = 208,
    /** @brief XFA widget element: Medium.*/
    e_WidgetElementMedium = 209,
    /** @brief XFA widget element: Text edit.*/
    e_WidgetElementTextEdit = 210,
    /** @brief XFA widget element: Template cache.*/
    e_WidgetElementTemplateCache = 211,
    /** @brief XFA widget element: Compress object stream.*/
    e_WidgetElementCompressObjectStream = 212,
    /** @brief XFA widget element: Data value.*/
    e_WidgetElementDataValue = 213,
    /** @brief XFA widget element: Accessible content.*/
    e_WidgetElementAccessibleContent = 214,
    /** @brief XFA widget element: Node list.*/
    e_WidgetElementNodeList = 215,
    /** @brief XFA widget element: XDP content.*/
    e_WidgetElementIncludeXDPContent = 216,
    /** @brief XFA widget element: Xml connection .*/
    e_WidgetElementXmlConnection = 217,
    /** @brief XFA widget element: Validate approval signatures.*/
    e_WidgetElementValidateApprovalSignatures = 218,
    /** @brief XFA widget element: Sign data.*/
    e_WidgetElementSignData = 219,
    /** @brief XFA widget element: Packets.*/
    e_WidgetElementPackets = 220,
    /** @brief XFA widget element: Pattern.*/
    e_WidgetElementDatePattern = 221,
    /** @brief XFA widget element: Duplex option.*/
    e_WidgetElementDuplexOption = 222,
    /** @brief XFA widget element: Base.*/
    e_WidgetElementBase = 223,
    /** @brief XFA widget element: bind.*/
    e_WidgetElementBind = 224,
    /** @brief XFA widget element: compression.*/
    e_WidgetElementCompression = 225,
    /** @brief XFA widget element: user.*/
    e_WidgetElementUser = 226,
    /** @brief XFA widget element: rectangle.*/
    e_WidgetElementRectangle = 227,
    /** @brief XFA widget element: Effective output policy.*/
    e_WidgetElementEffectiveOutputPolicy = 228,
    /** @brief XFA widget element: ADBE JS Debugger.*/
    e_WidgetElementADBE_JSDebugger = 229,
    /** @brief XFA widget element: Acrobat7.*/
    e_WidgetElementAcrobat7 = 230,
    /** @brief XFA widget element: Interactive.*/
    e_WidgetElementInteractive = 231,
    /** @brief XFA widget element: Locale.*/
    e_WidgetElementLocale = 232,
    /** @brief XFA widget element: Current page.*/
    e_WidgetElementCurrentPage = 233,
    /** @brief XFA widget element: Data.*/
    e_WidgetElementData = 234,
    /** @brief XFA widget element: Date.*/
    e_WidgetElementDate = 235,
    /** @brief XFA widget element: Desc.*/
    e_WidgetElementDesc = 236,
    /** @brief XFA widget element: Encrypt.*/
    e_WidgetElementEncrypt = 237,
    /** @brief XFA widget element: Draw.*/
    e_WidgetElementDraw = 238,
    /** @brief XFA widget element: Encryption.*/
    e_WidgetElementEncryption = 239,
    /** @brief XFA widget element: Meridiem Names.*/
    e_WidgetElementMeridiemNames = 240,
    /** @brief XFA widget element: Messaging.*/
    e_WidgetElementMessaging = 241,
    /** @brief XFA widget element: Speak.*/
    e_WidgetElementSpeak = 242,
    /** @brief XFA widget element: Data group.*/
    e_WidgetElementDataGroup = 243,
    /** @brief XFA widget element: Common.*/
    e_WidgetElementCommon = 244,
    /** @brief XFA widget element: Sharptext.*/
    e_WidgetElementSharptext = 245,
    /** @brief XFA widget element: Pagination override.*/
    e_WidgetElementPaginationOverride = 246,
    /** @brief XFA widget element: Reasons.*/
    e_WidgetElementReasons = 247,
    /** @brief XFA widget element: Signature properties.*/
    e_WidgetElementSignatureProperties = 248,
    /** @brief XFA widget element: Threshold.*/
    e_WidgetElementThreshold = 249,
    /** @brief XFA widget element: Appearance filter.*/
    e_WidgetElementAppearanceFilter = 250,
    /** @brief XFA widget element: Fill.*/
    e_WidgetElementFill = 251,
    /** @brief XFA widget element: Font.*/
    e_WidgetElementFont = 252,
    /** @brief XFA widget element: Form.*/
    e_WidgetElementForm = 253,
    /** @brief XFA widget element: Medium info.*/
    e_WidgetElementMediumInfo = 254,
    /** @brief XFA widget element: Certificate.*/
    e_WidgetElementCertificate = 255,
    /** @brief XFA widget element: Password.*/
    e_WidgetElementPassword = 256,
    /** @brief XFA widget element: Run scripts.*/
    e_WidgetElementRunScripts = 257,
    /** @brief XFA widget element: Trace.*/
    e_WidgetElementTrace = 258,
    /** @brief XFA widget element: Float.*/
    e_WidgetElementFloat = 259,
    /** @brief XFA widget element: Render policy.*/
    e_WidgetElementRenderPolicy = 260,
    /** @brief XFA widget element: Log pseudo model.*/
    e_WidgetElementLogPseudoModel = 261,
    /** @brief XFA widget element: Destination.*/
    e_WidgetElementDestination = 262,
    /** @brief XFA widget element: Value.*/
    e_WidgetElementValue = 263,
    /** @brief XFA widget element: Bookend.*/
    e_WidgetElementBookend = 264,
    /** @brief XFA widget element: Ex object.*/
    e_WidgetElementExObject = 265,
    /** @brief XFA widget element: XML data.*/
    e_WidgetElementXMLData = 266,
    /** @brief XFA widget element: Open action.*/
    e_WidgetElementOpenAction = 267,
    /** @brief XFA widget element: Never embed.*/
    e_WidgetElementNeverEmbed = 268,
    /** @brief XFA widget element: Bind items.*/
    e_WidgetElementBindItems = 269,
    /** @brief XFA widget element: Calculate.*/
    e_WidgetElementCalculate = 270,
    /** @brief XFA widget element: Print.*/
    e_WidgetElementPrint = 271,
    /** @brief XFA widget element: Extras.*/
    e_WidgetElementExtras = 272,
    /** @brief XFA widget element: Proto.*/
    e_WidgetElementProto = 273,
    /** @brief XFA widget element: D sig data.*/
    e_WidgetElementDSigData = 274,
    /** @brief XFA widget element: Creator.*/
    e_WidgetElementCreator = 275,
    /** @brief XFA widget element: Connect.*/
    e_WidgetElementConnect = 276,
    /** @brief XFA widget element: Permissions.*/
    e_WidgetElementPermissions = 277,
    /** @brief XFA widget element: Connection set.*/
    e_WidgetElementConnectionSet = 278,
    /** @brief XFA widget element: Submit.*/
    e_WidgetElementSubmit = 279,
    /** @brief XFA widget element: Range.*/
    e_WidgetElementRange = 280,
    /** @brief XFA widget element: Linearized.*/
    e_WidgetElementLinearized = 281,
    /** @brief XFA widget element: Packet.*/
    e_WidgetElementPacket = 282,
    /** @brief XFA widget element: Root element.*/
    e_WidgetElementRootElement = 283,
    /** @brief XFA widget element: Plain text metadata.*/
    e_WidgetElementPlaintextMetadata = 284,
    /** @brief XFA widget element: Number symbols.*/
    e_WidgetElementNumberSymbols = 285,
    /** @brief XFA widget element: Print high quality.*/
    e_WidgetElementPrintHighQuality = 286,
    /** @brief XFA widget element: Driver.*/
    e_WidgetElementDriver = 287,
    /** @brief XFA widget element: Incremental load.*/
    e_WidgetElementIncrementalLoad = 288,
    /** @brief XFA widget element: DN.*/
    e_WidgetElementSubjectDN = 289,
    /** @brief XFA widget element: Compress logical structure.*/
    e_WidgetElementCompressLogicalStructure = 290,
    /** @brief XFA widget element: Incremental merge.*/
    e_WidgetElementIncrementalMerge = 291,
    /** @brief XFA widget element: Radial.*/
    e_WidgetElementRadial = 292,
    /** @brief XFA widget element: Variables.*/
    e_WidgetElementVariables = 293,
    /** @brief XFA widget element: Time patterns.*/
    e_WidgetElementTimePatterns = 294,
    /** @brief XFA widget element: Effective input policy.*/
    e_WidgetElementEffectiveInputPolicy = 295,
    /** @brief XFA widget element: Name attr.*/
    e_WidgetElementNameAttr = 296,
    /** @brief XFA widget element: Conformance.*/
    e_WidgetElementConformance = 297,
    /** @brief XFA widget element: Transform.*/
    e_WidgetElementTransform = 298,
    /** @brief XFA widget element: Lock document.*/
    e_WidgetElementLockDocument = 299,
    /** @brief XFA widget element: Break after.*/
    e_WidgetElementBreakAfter = 300,
    /** @brief XFA widget element: Line.*/
    e_WidgetElementLine = 301,
    /** @brief XFA widget element: List.*/
    e_WidgetElementList = 302,
    /** @brief XFA widget element: Source.*/
    e_WidgetElementSource = 303,
    /** @brief XFA widget element: Occur.*/
    e_WidgetElementOccur = 304,
    /** @brief XFA widget element: Pick tray by PDF size.*/
    e_WidgetElementPickTrayByPDFSize = 305,
    /** @brief XFA widget element: Month mames.*/
    e_WidgetElementMonthNames = 306,
    /** @brief XFA widget element: Severity.*/
    e_WidgetElementSeverity = 307,
    /** @brief XFA widget element: Group parent.*/
    e_WidgetElementGroupParent = 308,
    /** @brief XFA widget element: Encrypt data.*/
    e_WidgetElementEncryptData = 309,
    /** @brief XFA widget element: Document assembly.*/
    e_WidgetElementDocumentAssembly = 310,
    /** @brief XFA widget element: Number symbol.*/
    e_WidgetElementNumberSymbol = 311,
    /** @brief XFA widget element: Tagged.*/
    e_WidgetElementTagged = 312,
    /** @brief XFA widget element: Items.*/
    e_WidgetElementItems = 313
  } WidgetElement;
  
  /**
   * @brief Enumeration for XFA attribute type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _WidgetAttributeType {
    /** @brief Widget attribute type: H. Height for layout purposes.*/
    e_WidgetAttributeTypeH = 0,
    /** @brief Widget attribute type: W. Width for layout purposes.*/
    e_WidgetAttributeTypeW = 1,
    /**
     * @brief Widget attribute type: X.
     *        X coordinate of the container's anchor point relative to the top-left corner of the
     *        parent container's nominal content region when placed with positioned layout.
     */
    e_WidgetAttributeTypeX = 2,
    /**
     * @brief Widget attribute type: Y.
     *        Y coordinate of the container's anchor point relative to the top-left corner of the
     *        parent container's nominal content region when placed with positioned layout.
     */
    e_WidgetAttributeTypeY = 3,
    /** @brief Widget attribute type: Line through.*/
    e_WidgetAttributeTypeLineThrough = 4,
    /** @brief Widget attribute type: Horizontal text alignment control.*/
    e_WidgetAttributeTypeLineHAlign = 5,
    /** @brief Widget attribute type: Type face.*/
    e_WidgetAttributeTypeTypeface = 6,
    /** @brief Widget attribute type: Font horizontal scale.*/
    e_WidgetAttributeTypeFontHorizontalScale = 7,
    /** @brief Widget attribute type: Text intent.*/
    e_WidgetAttributeTypeTextIndent = 8,
    /** @brief Widget attribute type: Left inset.*/
    e_WidgetAttributeTypeLeftInset = 9,
    /** @brief Widget attribute type: Bottom inset.*/
    e_WidgetAttributeTypeBottomInset = 10,
    /** @brief Widget attribute type: Allow rich text.*/
    e_WidgetAttributeTypeAllowRichText = 11,
    /** @brief Widget attribute type: Top inset.*/
    e_WidgetAttributeTypeTopInset = 12,
    /** @brief Widget attribute type: Access.*/
    e_WidgetAttributeTypeAccess = 13,
    /** @brief Widget attribute type: Margin right.*/
    e_WidgetAttributeTypeMarginRight = 14,
    /** @brief Widget attribute type: Rotate.*/
    e_WidgetAttributeTypeRotate = 15,
    /** @brief Widget attribute type: Underline.*/
    e_WidgetAttributeTypeUnderline = 16,
    /** @brief Widget attribute type: Baseline shift.*/
    e_WidgetAttributeTypeBaselineShift = 17,
    /** @brief Widget attribute type: Overline period.*/
    e_WidgetAttributeTypeOverlinePeriod = 18,
    /** @brief Widget attribute type: Frac digits.*/
    e_WidgetAttributeTypeFracDigits = 19,
    /** @brief Widget attribute type: Margin left digits.*/
    e_WidgetAttributeTypeMarginLeft = 20,
    /** @brief Widget attribute type: Stroke.*/
    e_WidgetAttributeTypeStroke = 21,
    /** @brief Widget attribute type: Presence.*/
    e_WidgetAttributeTypePresence = 22,
    /** @brief Widget attribute type: Multiline.*/
    e_WidgetAttributeTypeMultiLine = 23,
    /** @brief Widget attribute type: Space below.*/
    e_WidgetAttributeTypeSpaceBelow = 24,
    /** @brief Widget attribute type: Number of cells.*/
    e_WidgetAttributeTypeNumberOfCells = 25,
    /** @brief Widget attribute type: Letter spacing.*/
    e_WidgetAttributeTypeLetterSpacing = 26,
    /** @brief Widget attribute type: Password char.*/
    e_WidgetAttributeTypePasswordChar = 27,
    /** @brief Widget attribute type: Vertical text alignment control.*/
    e_WidgetAttributeTypeVAlign = 28,
    /** @brief Widget attribute type: Max H.*/
    e_WidgetAttributeTypeMaxH = 29,
    /** @brief Widget attribute type: Max W.*/
    e_WidgetAttributeTypeMaxW = 30,
    /** @brief Widget attribute type: Min H.*/
    e_WidgetAttributeTypeMinH = 31,
    /** @brief Widget attribute type: Min W.*/
    e_WidgetAttributeTypeMinW = 32,
    /** @brief Widget attribute type: Layout.*/
    e_WidgetAttributeTypeLayout = 33,
    /** @brief Widget attribute type: Right inset.*/
    e_WidgetAttributeTypeRightInset = 34,
    /** @brief Widget attribute type: Line through period.*/
    e_WidgetAttributeTypeLineThroughPeriod = 35,
    /** @brief Widget attribute type: Shape.*/
    e_WidgetAttributeTypeShape = 36,
    /** @brief Widget attribute type: Border width.*/
    e_WidgetAttributeTypeBorderWidth = 37,
    /** @brief Widget attribute type: Locale.*/
    e_WidgetAttributeTypeLocale = 38,
    /** @brief Widget attribute type: Weight.*/
    e_WidgetAttributeTypeWeight = 39,
    /** @brief Widget attribute type: Underline period.*/
    e_WidgetAttributeTypeUnderlinePeriod = 40,
    /** @brief Widget attribute type: Overline.*/
    e_WidgetAttributeTypeOverline = 42,
    /** @brief Widget attribute type: Line height.*/
    e_WidgetAttributeTypeLineHeight = 43,
    /** @brief Widget attribute type: Value.*/
    e_WidgetAttributeTypeValue = 44,
    /** @brief Widget attribute type: Text encoding.*/
    e_WidgetAttributeTypeTextEncoding = 45,
    /** @brief Widget attribute type: Lead digits.*/
    e_WidgetAttributeTypeLeadDigits = 46,
    /** @brief Widget attribute type: Space above.*/
    e_WidgetAttributeTypeSpaceAbove = 47,
    /** @brief Widget attribute type: Placement.*/
    e_WidgetAttributeTypePlacement = 48,
    /** @brief Widget attribute type: Border color.*/
    e_WidgetAttributeTypeBorderColor = 49,
    /** @brief Widget attribute type: Fill color.*/
    e_WidgetAttributeTypeFillColor = 50,
    /** @brief Widget attribute type: Font color.*/
    e_WidgetAttributeTypeFontColor = 51,
    /** @brief Widget attribute type: Unknown.*/
    e_WidgetAttributeTypeUnknown = 52
  } WidgetAttributeType;
  

  /** @brief Constructor. */
  XFAWidgetModifyInfo() 
    : event_type(XFADoc::e_EventTypeUnknown)
    , page_index(-1)
    , element(e_WidgetElementPs)
    , attribute_type(e_WidgetAttributeTypeUnknown)
    , old_value(L"")
    , new_value(L"")
    , widget_name(L"") {}

  /**
   * @brief Constructor, with another xfa widget modify information object.
   *
   * @param[in] other  Another xfa widget modify information object.
   */
  XFAWidgetModifyInfo(const XFAWidgetModifyInfo& other) {
    event_type = other.event_type;
    page_index = other.page_index;
    element = other.element;
    attribute_type = other.attribute_type;
    old_value = other.old_value;
    new_value = other.new_value;
    widget_name = other.widget_name;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another xfa widget modify information object.
   *
   * @return Reference to current object itself.
   */
  XFAWidgetModifyInfo& operator=(const XFAWidgetModifyInfo& other) {
    if (this != &other) {
      event_type = other.event_type;
      page_index = other.page_index;
      element = other.element;
      attribute_type = other.attribute_type;
      old_value = other.old_value;
      new_value = other.new_value;
      widget_name = other.widget_name;
    }
    return *this;
  }

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] event_type      The XFA event type. 
   * @param[in] page_index      The modify page index.
   * @param[in] element         The xfa widget element.
   * @param[in] attribute_type  The xfa widget attribute type.
   * @param[in] old_value       The old value.
   * @param[in] new_value       The new value.
   * @param[in] widget_name     The widget name.
   */
  XFAWidgetModifyInfo(XFADoc::EventType event_type,
      int page_index, WidgetElement element, 
      WidgetAttributeType attribute_type, WString old_value,
      WString new_value, WString widget_name)
      : event_type(event_type)
      , page_index(page_index)
      , element(element)
      , attribute_type(attribute_type)
      , old_value(old_value)
      , new_value(new_value)
      , widget_name(widget_name) 
     {}

  /** 
   * @brief The XFA event type. 
   *        Please refer to values starting from @link XFADoc::e_EventTypeUnknown @endlink and this would be one of these values.
   */
  XFADoc::EventType event_type;

  /** @brief The page index. */
  int page_index;

  /** 
   * @brief The XFA widget element. 
   *        Please refer to values starting from @link XFAWidgetModifyInfo::e_WidgetElementPs @endlink and this would be one of these values.
   */
  WidgetElement element;

  /** 
   * @brief The attribute type. Please refer to values starting from @link XFAWidgetModifyInfo::e_WidgetAttributeTypeH @endlink and this would be one of these values.
   */
  WidgetAttributeType attribute_type;

  /** @brief The old value.*/
  WString old_value;

  /** @brief The new value.*/
  WString new_value;

  /** @brief The xfa widget name.*/
  WString widget_name;
};

/**
 * Class @link XFAWidget @endlink represents the XFA widget which is retrieved from XFA page object.<br>
 * To access the menu of XFA widget, please construct a @link xfa::WidgetMenu @endlink object with @link XFAWidget @endlink object.
 *
 * @see @link WidgetMenu @endlink
 */
class XFAWidget FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for hit test area of XFA widget.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _HitTestArea {
    /** @brief Hit test area: Unknown. */
    e_HitTestAreaUnknown = 0,
    /** @brief Hit test area: Client. */
    e_HitTestAreaClient = 1,
    /** @brief Hit test area: Title Bar. */
    e_HitTestAreaTitleBar = 2,
    /** @brief Hit test area: HyperLink. */
    e_HitTestAreaHyperLink = 3
  } HitTestArea;
  
  /**
   * @brief Enumeration for the type of XFA widget.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _WidgetType {
    /** @brief XFA widget type: barcode. */
    e_WidgetTypeBarcode = 0,
    /** @brief XFA widget type: push button. */
    e_WidgetTypePushButton = 1,
    /** @brief XFA widget type: check button. */
    e_WidgetTypeCheckButton = 2,
    /** @brief XFA widget type: arc. */
    e_WidgetTypeArc = 3,
    /** @brief XFA widget type: date time edit. */
    e_WidgetTypeDateTimeEdit = 4,
    /** @brief XFA widget type: numeric edit. */
    e_WidgetTypeNumericEdit = 5,
    /** @brief XFA widget type: signature. */
    e_WidgetTypeSignature = 6,
    /** @brief XFA widget type: choice list. */
    e_WidgetTypeChoiceList = 7,
    /** @brief XFA widget type: image edit. */
    e_WidgetTypeImageEdit = 8,
    /** @brief XFA widget type: line. */
    e_WidgetTypeLine = 9,
    /** @brief XFA widget type: password edit. */
    e_WidgetTypePasswordEdit = 10,
    /** @brief XFA widget type: radio button. */
    e_WidgetTypeRadioButton = 11,
    /** @brief XFA widget type: rectangle. */
    e_WidgetTypeRectangle = 12,
    /** @brief XFA widget type: text edit. */
    e_WidgetTypeTextEdit = 13,
    /** @brief XFA widget type: unknown. */
    e_WidgetTypeUnknown = 14,
    /** @brief XFA widget type: Exclusion Group for radio button only. */
    e_WidgetTypeExclGroup = 15,
    /** @brief XFA widget type: image. */
    e_WidgetTypeImage = 16
  } WidgetType;
  
  /**
   * @brief Enumeration for presence attribute of XFA widget.
   *
   * @details Values of this enumeration should be used alone.<br>
   *          The presence property controls the participation of the associated object in different phases of processing.
   */
  typedef enum _PresenceProperty {
    /** @brief Presence property: Unknown. */
    e_PresenceUnknown = 0,
    /** @brief Presence property: Visible. Participate in interaction, layout, and rendering.*/
    e_PresenceVisible = 1,
    /** @brief Presence property: Hidden. Participate in interaction but not layout or rendering.*/
    e_PresenceHidden = 2,
    /** @brief Presence property: Inactive. Do not participate in interaction, layout, or rendering.*/
    e_PresenceInactive = 3,
    /** @brief Presence property: Invisible. Participate in interaction and layout but not rendering.*/
    e_PresenceInvisible = 4
  } PresenceProperty;
  
  /**
   * @brief Enumeration for the type of XFA widget name.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _WidgetNameType {
    /** @brief Name type: field name. Name in this type will be retrieved from XFA widget's name entry and this may an empty string.*/
    e_WidgetNameTypeField = 0,
    /** @brief Name type: caption name. Name in this type will be retrieved from caption entry.*/
    e_WidgetNameTypeCaption = 1,
    /** @brief Name type: full name.*/
    e_WidgetNameTypeFullName = 2
  } WidgetNameType;
  
  /**
   * @brief Enumeration for the type of text horizontal alignment of XFA widget.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _WidgetHAlignType {
    /** @brief Center the text horizontally within the available region.*/
    e_WidgethAlignTypeCenter = 128,
    /** @brief Left-align the last line and spread-justify the rest.*/
    e_WidgethAlignTypeJustify = 156,
    /** @brief Spread-justify all lines to fill the available region.*/
    e_WidgethAlignTypeJustifyAll = 61,
    /** @brief Align the text to the left edge of the available region.*/
    e_WidgethAlignTypeLeft = 252,
    /** @brief Align the radix indicator.*/
    e_WidgethAlignTypeRadix = 231,
    /** @brief Align the text to the right edge of the available region.*/
    e_WidgethAlignTypeRight = 54
  } WidgetHAlignType;
  
  /**
   * @brief Enumeration for the type of text vertical alignment of XFA widget.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _WidgetVAlignType {
    /** @brief Align the text to the top of the available region.*/
    e_WidgetvAlignTypeTop = 33,
    /** @brief Align the text to the bottom of the available region.*/
    e_WidgetvAlignTypeBottom = 85,
    /** @brief Align the text so that it is centered between the top and bottom of the available region.*/
    e_WidgetvAlignTypeMiddle = 161
  } WidgetVAlignType;
  
  /**
   * @brief Enumeration for the positon of XFA widget edge position.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _WidgetEdgePosition {
    /** @brief Edge position: top.*/
    e_WidgetEdgePositionTop = 0,
    /** @brief Edge position: right.*/
    e_WidgetEdgePositionRight = 1,
    /** @brief Edge position: bottom.*/
    e_WidgetEdgePositionBottom = 2,
    /** @brief Edge position: left.*/
    e_WidgetEdgePositionLeft = 3
  } WidgetEdgePosition;
  

  /**
   * @brief Constructor, with another XFA widget object.
   *
   * @param[in] other  Another XFA widget object.
   */
  XFAWidget(const XFAWidget& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another XFA widget object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  XFAWidget& operator = (const XFAWidget& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another XFA widget object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const XFAWidget& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another XFA widget object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const XFAWidget& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /** @brief Destructor. */
  ~XFAWidget();

  /**
   * @brief Get the related XFA page, to which current XFA widget belongs.
   *
   * @return An XFA page object.
   */
  XFAPage GetXFAPage();

  /**
   * @brief Get the index of XFA Widget in related XFA page.
   *
   * @return The index of XFA Widget in related XFA page.
   */
  int GetIndex() const;

  /**
   * @brief Reset XFA Widget Data.
   *
   * @return None.
   */
  void ResetData();

  /**
   * @brief Get rectangle of XFA widget.
   *
   * @details Widget rectangle is defined in XFA coordinate. XFA coordinate is defined as original point in left top,
   *          x-axis pointing to right and y-axis pointing down.
   *
   * @return The rectangle of XFA widget.
   */
  RectF GetRect();

  /**
   * @brief Get the value string.
   *
   * @return The value string.
   */
  WString GetValue();

  /**
   * @brief Set the value string.
   *
   * @details It is only useful for the XFA widget which type is @link XFAWidget::e_WidgetTypeTextEdit @endlink, @link XFAWidget::e_WidgetTypeNumericEdit @endlink, 
   *          @link XFAWidget::e_WidgetTypePasswordEdit @endlink or @link XFAWidget::e_WidgetTypeDateTimeEdit @endlink.
   *
   * @param[in] value  A string as value to be set. It can be an empty string.
   *
   * @return None.
   */
  void SetValue(const wchar_t* value);

  /**
   * @brief Get the default value string.
   *
   * @return The default value string.
   */
  WString GetDefaultValue();

  /**
   * @brief Set the default value string.
   * 
   * @details It is only useful for the XFA widget which type is @link XFAWidget::e_WidgetTypeTextEdit @endlink, @link XFAWidget::e_WidgetTypeNumericEdit @endlink, 
   *          @link XFAWidget::e_WidgetTypePasswordEdit @endlink or @link XFAWidget::e_WidgetTypeDateTimeEdit @endlink.
   *
   * @param[in] value  A string as default value to be set. It can be an empty string.
   *
   * @return None.
   */
  void SetDefaultValue(const wchar_t* value);

  /**
   * @brief Get Widget name.
   *
   * @param[in] type  Name type. Please refer to values starting from @link XFAWidget::e_WidgetNameTypeField @endlink and
   *                  this should be one of these values.
   *
   * @return Widget name string.
   */
  WString GetName(WidgetNameType type);

  /**
   * @brief Get options of a choice list or an Exclusion Group (for radio button only).
   *
   * @details Applicable for choice list and Exclusion Group (for radio button only).
   *          For types that are not applicable, this function will return an empty array.
   *
   * @return A choice option array.
   */
  addon::xfa::WidgetChoiceOptionArray GetOptions() const;

  /**
   * @brief Set options of a choice list or an Exclusion Group (for radio button only).
   * 
   * @details Applicable for choice list and Exclusion Group (for radio button only).
   *          For types that are not applicable, this function will return <b>false</b>.
   * 
   * @param[in] option_array  An array of choice options to be set.
   * 
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SetOptions(const addon::xfa::WidgetChoiceOptionArray& option_array);

  /**
   * @brief Check if current XFA widget is checked.
   *
   * @details Applicable for check box or radio button as related XFA widget. 
   *          For types that are not applicable, this function will return <b>false</b>.
   *
   * @return <b>true</b> means checked, while <b>false</b> means unchecked or failure.
   */
  bool IsChecked() const;

  /**
   * @brief Set the checked state of the current XFA widget.
   *
   * @details Applicable for check box or radio button as related XFA widget.
   *          For types that are not applicable, this function will throw exception @link foxit::e_ErrUnsupported @endlink.
   *
   * @param[in] is_checked  <b>true</b> means the current XFA widget will be checked,
   *                        while <b>false</b> means it will not be checked.
   *
   * @return None.
   */
  void SetCheckState(bool is_checked);

  /**
   * @brief  Check whether the widget is listbox or not.
   *
   * @return <b>true</b> means the widget is listbox, while <b>false</b> means not.
   */
  bool IsListBox();

  /**
   * @brief  Check whether the widget supports multiple lines.
   *
   * @details Only text edit widget which type is @link XFAWidget::e_WidgetTypeTextEdit @endlink supports multiple lines.
   *
   * @return <b>true</b> means the widget supports multiple lines, while <b>false</b> means not.
   */
  bool IsSupportMultiline();

  /**
   * @brief  Check whether the widget supports multiple selections.
   *
   * @details Only the list box widget supports multiline selections, whose type is @link XFAWidget::e_WidgetTypeChoiceList @endlink and
   *          the return value of function @link xfa::XFAWidget::IsListBox @endlink is <b>true</b>.
   *
   * @return <b>true</b> means the widget support multiple selections, while <b>false</b> means not.
   */
  bool IsSupportMultiSelect();

  /**
   * @brief Get the presence property of the XFA widget.
   *
   * @details The presence property controls the participation of the associated object in different phases of processing.
   *
   * @return The presence property of the XFA widget.
   */
  PresenceProperty GetPresence();

  /**
   * @brief Call this function when mouse enters current XFA widget.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnMouseEnter();

  /**
   * @brief Call this function when mouse exits.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnMouseExit();

  /**
   * @brief Call this function when left mouse button is down.
   *
   * @param[in] point  A point where left mouse button is down in XFA page, in PDF coordinate system.
   * @param[in] flags  Event flags. Please refer to values starting from
   *                   @link pdf::interform::Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnLButtonDown(const PointF& point, uint32 flags);

  /**
   * @brief Call this function when left mouse button is up.
   *
   * @param[in] point  A point where left mouse button is up in XFA page, in PDF coordinate system.
   * @param[in] flags  Event flags. Please refer to values starting from
   *                   @link pdf::interform::Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnLButtonUp(const PointF& point, uint32 flags);

  /**
   * @brief Call this function when left mouse button is double-clicked .
   *
   * @param[in] point  A point where left mouse button is double-clicked in XFA page, in PDF coordinate system.
   * @param[in] flags  Event flags. Please refer to values starting from
   *                   @link pdf::interform::Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnLButtonDoubleClick(const PointF& point, uint32 flags);

  /**
   * @brief Call this function when mouse moves.
   *
   * @param[in] point  A point where left mouse button moves in XFA page, in PDF coordinate system.
   * @param[in] flags  Event flags. Please refer to values starting from
   *                   @link pdf::interform::Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnMouseMove(const PointF& point, uint32 flags);

  /**
   * @brief Call this function when right mouse is down.
   *
   * @param[in] point  A point where right mouse button is down in XFA page, in PDF coordinate system.
   * @param[in] flags  Event flags. Please refer to values starting from
   *                   @link pdf::interform::Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnRButtonDown(const PointF& point, uint32 flags);

  /**
   * @brief Call this function when right button is up.
   *
   * @param[in] point  A point where right mouse button is up in XFA page, in PDF coordinate system.
   * @param[in] flags  Event flags. Please refer to values starting from
   *                   @link pdf::interform::Filler::e_EventFlagShiftKey @endlink and
   *                   this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnRButtonUp(const PointF& point, uint32 flags);

  /**
   * @brief Call this function when key on the keyboard is down.
   *
   * @param[in] key_code  The key code. Please refer to values starting from
   *                      @link pdf::interform::Filler::e_VkeyUnknown @endlink and
   *                      this should be one of these values.
   * @param[in] flags     Event flags. Please refer to values starting from
   *                      @link pdf::interform::Filler::e_EventFlagShiftKey @endlink and
   *                      this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnKeyDown(uint32 key_code, uint32 flags);

  /**
   * @brief Call this function when key on the keyboard is up.
   *
   * @param[in] key_code  The key code. Please refer to values starting from
   *                      @link pdf::interform::Filler::e_VkeyUnknown @endlink and
   *                      this should be one of these values.
   * @param[in] flags     Event flags. Please refer to values starting from
   *                      @link pdf::interform::Filler::e_EventFlagShiftKey @endlink and
   *                      this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnKeyUp(uint32 key_code, uint32 flags);

  /**
   * @brief Call this function when a character code is being input.
   *
   * @param[in] input_char  A character code, in UTF16-LE encoding.
   * @param[in] flags       Event flags. Please refer to values starting from
   *                        @link pdf::interform::Filler::e_EventFlagShiftKey @endlink and
   *                        this should be one or a combination of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnChar(int input_char, uint32 flags);

  /**
   * @brief Call this function to do hit test for a specified point.
   *
   * @param[in] point  A point to be tested.
   *
   * @return The hit test area. Please refer to values starting from @link XFAWidget::e_HitTestAreaUnknown @endlink and
   *         this would be one of these values.
   */
  HitTestArea OnHitTest(const PointF& point);

  /**
   * @brief Get type of XFA widget.
   *
   * @return The XFA widget type. Please refer to values starting from @link XFAWidget::e_WidgetTypeBarcode @endlink and
   *         this would be one of these values.
   */
  WidgetType GetType();

  /**
   * @brief Get text horizontal alignment.
   *
   * @return Text horizontal alignment. Please refer to values starting from @link XFAWidget::e_WidgethAlignTypeLeft @endlink and
   *         this would be one of these values.
   */
  WidgetHAlignType GetHAlign();

  /**
   * @brief Get text vertical alignment.
   *
   * @return Text vertical alignment. Please refer to values starting from @link XFAWidget::e_WidgetvAlignTypeTop @endlink and
   *         this would be one of these values.
   */
  WidgetVAlignType GetVAlign();

  /**
   * @brief Check if the edge for specified position exists.
   *
   * @param[in] edge_pos  Edge position to specify which edge will be checked. Please refer to values starting from
   *                      @link XFAWidget::e_WidgetEdgePositionTop @endlink and this should be one of these values.
   *
   * @return <b>true</b> means that the edge for specified position exists, while <b>false</b> means that no such edge exist.
   */
  bool HasEdge(WidgetEdgePosition edge_pos);

  /**
   * @brief Get the signature object from current XFA widget.
   *
   * @details Applicable only when current XFA widget represents a signature.
   *          For types that are not applicable, this function will throw exception @link foxit::e_ErrUnsupported @endlink.
   *
   * @return A signature object.
   */
  foxit::pdf::Signature GetSignature();

  /**
   * @brief Get tooltip string.
   *
   * @return Tooltip string.
   */
  WString GetToolTip();

  /**
   * @brief Get the bitmap of current XFA widget.
   *
   * @details Applicable only when the type of current XFA widget is @link XFAWidget::e_WidgetTypeImageEdit @endlink
   *          or @link XFAWidget::e_WidgetTypeImage @endlink. For types that are not applicable, this function will
   *          throw exception @link foxit::e_ErrUnsupported @endlink.
   *
   * @return The bitmap of current XFA widget.
   */
  foxit::common::Bitmap GetBitmap();

  /**
   * @brief Set the image for current XFA widget.
   *
   * @details Applicable only when the type of current XFA widget is @link XFAWidget::e_WidgetTypeImageEdit @endlink.
   *          For types that are not applicable, this function will throw exception @link foxit::e_ErrUnsupported @endlink.
   *
   * @param[in] image An image will be set to current XFA widget.
   *                  Currently, this function only supports the following image types:
   *                  <ul>
   *                  <li>@link Image::e_BMP @endlink</li>
   *                  <li>@link Image::e_PNG @endlink</li>
   *                  <li>@link Image::e_JPG @endlink</li>
   *                  <li>@link Image::e_GIF @endlink</li>
   *                  <li>@link Image::e_TIF @endlink</li>
   *                  </ul>
   *                  If try to set rest unsupported image types, exception @link foxit::e_ErrUnsupported @endlink will be thrown.
   *
   * @return None.
   */
  void SetImage(const foxit::common::Image& image);

  /**
   * @brief Check whether the widget allows rich text formatting.
   * 
   * @details Only text edit widget which type is @link XFAWidget::e_WidgetTypeTextEdit @endlink supports rich text.
   * 
   * @return <b>true</b> means the widget allows rich text formatting, while <b>false</b> means not.
   */
  bool IsAllowRichText();

  /**
   * @brief Check whether the widget is read only.
   * 
   * @return <b>true</b> means the value of the field can not be changed, while <b>false</b> means it can be changed.
   */
  bool IsReadOnly();

  /**
   * @brief Check whether the widget requires a value at the time it is exported by a submit-form
   *        action.
   * 
   * @return <b>true</b> means the field must have a value at the time it is exported by a submit-form
   *         action, while <b>false</b> means not.
   */
  bool IsRequired();

  /**
   * @brief Validate whether the value conforms to the format of current XFA widget.
   * 
   * @details This function can be called before the function @link XFAWidget::SetValue @endlink to check whether
   *          the value conforms to the format of current XFA widget.
   * 
   * @param[in]  value   A string value to be validated.
   * @param[out] format  A string value that receives the format of current XFA widget. It will be an empty string
   *                     if current XFA widget has no format.
   * 
   * @return <b>true</b> means the value conforms to the format of current XFA widget, while <b>false</b> means not.
   */
  bool ValidateValue(const wchar_t* value, WString& format);

  /**
   * @brief Get the JavaScript of validation for current XFA widget.
   * 
   * @return The JavaScript of validation for current XFA widget.
   */
  WString GetJavaScript();

  /**
   * @brief Get the xml content of current XFA widget.
   * 
   * @return The xml content of current XFA widget.
   */
  String GetXMLContent();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit XFAWidget(FS_HANDLE handle =  NULL);
};

/**
 * Class @link WidgetMenu @endlink represents the menu of an XFA widget.
 */
class WidgetMenu FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, from XFA widget object.
   *
   * @param[in] xfa_widget  A valid XFA widget object.
   */
  explicit WidgetMenu(const XFAWidget& xfa_widget);

  /**
   * @brief Constructor, with another widget menu object.
   *
   * @param[in] other  Another widget menu object.
   */
  WidgetMenu(const WidgetMenu& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another widget menu object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  WidgetMenu& operator = (const WidgetMenu& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another widget menu object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const WidgetMenu& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another widget menu object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const WidgetMenu& other) const;

  /** @brief Destructor. */
  ~WidgetMenu();

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Check if the text of related XFA widget can be copied.
   *
   * @return <b>true</b> means the text can be copied, while <b>false</b> means the text cannot be copied.
   */
  bool CanCopy();

  /**
   * @brief Check if the text of related XFA widget can be cut.
   *
   * @return <b>true</b> means the text can be cut, while <b>false</b> means the text cannot be cut.
   */
  bool CanCut();

  /**
   * @brief Check if the text of related XFA widget can be pasted.
   *
   * @return <b>true</b> means the text can be pasted, while <b>false</b> means the text cannot be pasted.
   */
  bool CanPaste();

  /**
   * @brief Check if the text of related XFA widget can be selected all.
   *
   * @return <b>true</b> means the text can be selected all, while <b>false</b> means the text cannot be selected all.
   */
  bool CanSelectAll();

  /**
   * @brief Check if the text of related XFA widget can be deleted.
   *
   * @return <b>true</b> means the text can be deleted, while <b>false</b> means the text cannot be deleted.
   */
  bool CanDelete();

  /**
   * @brief Check if the selection of the text in related XFA widget can be canceled.
   *
   * @return <b>true</b> means the selection can be canceled, while <b>false</b> means the selection cannot
   *         be canceled.
   */
  bool CanDeSelect();

  /**
   * @brief Copy the text of related XFA widget.
   *
   * @return The copied text.
   */
  WString Copy();

  /**
   * @brief Cut the text of related XFA widget.
   *
   * @return The cut text.
   */
  WString Cut();

  /**
   * @brief Paste the text to related XFA widget.
   *
   * @param[in] text  A text string to be pasted.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Paste(const wchar_t* text);

  /**
   * @brief Select all the text of related XFA widget.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SelectAll();

  /**
   * @brief Delete all the text of related XFA widget.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Delete();

  /**
   * @brief Cancel the selection of the text in related XFA widget.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool DeSelect();

  /**
   * @brief Check if the operation of related XFA widget can be undone.
   *
   * @return <b>true</b> means the operation can be undone, while <b>false</b> means the operation cannot
   *         be undone.
   */
  bool CanUndo();

  /**
   * @brief Check if the operation of related XFA widget can be redone.
   *
   * @return <b>true</b> means the operation can be redone, while <b>false</b> means the operation cannot
   *         be redone.
   */
  bool CanRedo();

  /**
   * @brief Undo the operation of related XFA widget. (No effect for rich text)
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Undo();

  /**
   * @brief Redo the operation of related XFA widget. (No effect for rich text)
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Redo();

  /**
   * @brief (Only useful for rich text) Make the rich text bold.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Bold();

  /**
   * @brief (Only useful for rich text) Make the rich text italic.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Italic();

  /**
   * @brief (Only useful for rich text) Underline the rich text.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Underline();

  /**
   * @brief (Only useful for rich text) Make the rich text as superscript.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Superscript();

  /**
   * @brief (Only useful for rich text) Make the rich text as subscript.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Subscript();

  /**
   * @brief (Only useful for rich text) Clear the style of the rich text.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool ClearStyle();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit WidgetMenu(FS_HANDLE handle =  NULL);
};

}  // namespace XFA
}  // namespace addon
}  // namespace foxit
#endif  // namespace foxit

