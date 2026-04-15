#include <QFileDialog>
#include <QMessageBox>

#include "util.h"

using namespace foxit::addon::xfa;

QString GetErrorCodeMessage(foxit::ErrorCode error_code) {
    switch(error_code) {
        case foxit::e_ErrSuccess:
            return "Success, and no error occurs.";
        case foxit::e_ErrFile:
            return "File error: file cannot be found or could not be opened.";
        case foxit::e_ErrFormat:
            return "Format error: format is invalid. For files, this may also mean that file is corrupted.";
        case foxit::e_ErrPassword:
            return "Password error: invalid password.";
        case foxit::e_ErrHandle:
            return "Error handle.";
        case foxit::e_ErrCertificate:
            return "Certificate error: PDF document is encrypted by digital certificate and current user does not have the correct certificate.";
        case foxit::e_ErrUnknown:
            return "Unknown error: any unknown error occurs.";
        case foxit::e_ErrInvalidLicense:
            return "License error: invalid license is used to initialize Foxit PDF SDK library.";
        case foxit::e_ErrParam:
            return "Parameter error: value of any input parameter for a function is invalid.";
        case foxit::e_ErrUnsupported:
            return "Unsupported error: some types are not supported.";
        case foxit::e_ErrOutOfMemory:
            return "Memory error: out-of-memory error occurs.";
        case foxit::e_ErrSecurityHandler:
            return "Security handler error: PDF document is encrypted by some unsupported security handler.";
        case foxit::e_ErrNotParsed:
            return "Not parsed error: content has not been parsed yet. Usually, this represents PDF page has not been parsed yet.";
        case foxit::e_ErrNotFound:
            return "Not found error: expected data or object is not found.";
        case foxit::e_ErrInvalidType:
            return "Invalid type error: the type of input object or current object is invalid.";
        case foxit::e_ErrConflict:
            return "Conflict error: new data conflicts with existed data.";
        case foxit::e_ErrUnknownState:
            return "Unknown state error: any unknown state occurs.";
        case foxit::e_ErrDataNotReady:
            return "Data not ready error: data is not ready yet. Usually, this may occur when the PDF document is loaded by using asynchronous loader handler and it represents application has not download enough PDF document data yet.";
        case foxit::e_ErrInvalidData:
            return "Invalid data error: data of current object is invalid.";
        case foxit::e_ErrXFALoadError:
            return "XFA loading error.";
        case foxit::e_ErrNotLoaded:
            return "Not loaded erorr: current object has not been loaded yet.";
        case foxit::e_ErrInvalidState:
            return "Invalid state error: invalid or incorrect state.";
        default:
            return "Error code:" + QString::number(error_code) + ".";
    }
}

// The implementation of class MyXFAAppProviderCallback
MyXFAAppProviderCallback::MyXFAAppProviderCallback(MainWindow* parent_window)
    : parent_window_(parent_window) {}

void MyXFAAppProviderCallback::Release() {
    delete this;
}

foxit::WString MyXFAAppProviderCallback::GetAppInfo(AppInfo app_info) {
    switch(app_info) {
        case AppProviderCallback::e_AppInfoVersion:
            return L"11.0";
        case AppProviderCallback::e_AppInfoType:
            return L"Exchange-Pro";
        case AppProviderCallback::e_AppInfoLanguage:
            return L"en-US";
        case AppProviderCallback::e_AppInfoPlatform:
            return L"Linux";
        case AppProviderCallback::e_AppInfoName:
            return L"Foxit PDF SDK";
        case AppProviderCallback::e_AppInfoVariation:
            return L"Full";
        default:
            break;
    }
    return L"";
}

void MyXFAAppProviderCallback::Beep(BeepType type) {
    QString msgbox_title = "XFA Beep";
    QString message = "XFA Beep Type:";

    switch (type) {
        case AppProviderCallback::e_BeepTypeError:
            message += "Error";
            break;
        case AppProviderCallback::e_BeepTypeWarning:
            message += "Warning";
                break;
        case AppProviderCallback::e_BeepTypeQuestion:
            message += "Question";
            break;
        case AppProviderCallback::e_BeepTypeStatus:
            message += "Status";
            break;
        case AppProviderCallback::e_BeepTypeDefault:
            message += "Default";
            break;
        default:
            message += "not defined";
            break;
    }
    QMessageBox::about(parent_window_, msgbox_title, message );
    return;
}

AppProviderCallback::MsgBoxButtonID MyXFAAppProviderCallback::MsgBox(const wchar_t* message, const wchar_t* title /* = NULL */, MsgBoxIconType icon_type /* = e_MsgBoxIconError */, MsgBoxButtonType button_type /* = e_MsgBtnTypeOK */) {

    QMessageBox::StandardButtons need_btns = QMessageBox::Ok;
    switch(button_type) {
    case AppProviderCallback::e_MsgBtnTypeOKCancel:
        need_btns = QMessageBox::Ok | QMessageBox::Cancel;
        break;
    case AppProviderCallback::e_MsgBtnTypeYesNo:
        need_btns = QMessageBox::Yes | QMessageBox::No;
        break;
    case AppProviderCallback::e_MsgBtnTypeYesNoCancel:
        need_btns = QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel;
        break;
    case AppProviderCallback::e_MsgBtnTypeOK:
    default:
        need_btns = QMessageBox::Ok;
        break;

    }

    QString msgbox_title = QString::fromWCharArray(title);
    QString msgbox_text = QString::fromWCharArray(message);
    QMessageBox::StandardButton clicked_btn = QMessageBox::Ok;
    switch(icon_type) {
        case AppProviderCallback::e_MsgBoxIconError:
            QMessageBox::critical(parent_window_, msgbox_title, msgbox_text, need_btns);
            break;
        case AppProviderCallback::e_MsgBoxIconStatus:
            QMessageBox::information(parent_window_, msgbox_title, msgbox_text, need_btns);
            break;
        case AppProviderCallback::e_MsgBoxIconQuestion:
            clicked_btn = QMessageBox::question(parent_window_, msgbox_title, msgbox_text, need_btns);
            break;
        case AppProviderCallback::e_MsgBoxIconWarning:
            clicked_btn = QMessageBox::warning(parent_window_, msgbox_title, msgbox_text, need_btns);
            break;
    }

    switch(clicked_btn) {
        case QMessageBox::Yes:
            return AppProviderCallback::e_MsgBtnIDYes;
        case QMessageBox::No:
            return AppProviderCallback::e_MsgBtnIDNo;
        case QMessageBox::Cancel:
            return AppProviderCallback::e_MsgBtnIDCancel;
        case QMessageBox::Ok:
        default:
            return AppProviderCallback::e_MsgBtnIDOK;
    }
}

foxit::WString MyXFAAppProviderCallback::Response(const wchar_t* question, const wchar_t* title, const wchar_t* default_answer /* = NULL */, bool is_mask /* = TRUE */) {
    // Here, just output the input parameters value, not doing anything with input parameters.
    QString msgbox_title = title?QString::fromWCharArray(title):"";
    QString msgbox_text = "question:";
    msgbox_text += question?QString::fromWCharArray(question):"(empty string)";
    msgbox_text += "\r\ndefault answer:";
    msgbox_text += default_answer?QString::fromWCharArray(default_answer):"(empty string)";
    msgbox_text += "\r\nis_mask:";
    msgbox_text += is_mask?"true":"false";
    QMessageBox::about(parent_window_, msgbox_title, msgbox_text);

    return L"answer";
}

foxit::common::file::ReaderCallback* MyXFAAppProviderCallback::DownLoadUrl(const wchar_t* url) {
    // Here, just output the input parameters value, not doing anything with input parameters.
    QString msgbox_title = "Info";
    QString msgbox_text = "Download url:";
    msgbox_text += url?QString::fromWCharArray(url):"(empty string)";
    QMessageBox::about(parent_window_, msgbox_title, msgbox_text);
    return NULL;
}

foxit::WString MyXFAAppProviderCallback::PostRequestURL(const wchar_t* url, const wchar_t* data, const wchar_t* content_type, const wchar_t* encode, const wchar_t* header) {
    // Here, not doing anything with input parameters.
    return L"PostRequestUrl";
}

bool MyXFAAppProviderCallback::PutRequestURL(const wchar_t* url, const wchar_t* data, const wchar_t* encode) {
    // Here, not doing anything with input parameters.
    return true;
}

foxit::WString MyXFAAppProviderCallback::LoadString(StringID string_id) {
      const wchar_t* wsString = L"";
      switch (string_id)
      {
      case AppProviderCallback::e_StringIDValidateFailed:
        wsString = L"%s validate failed";
        break;
      case AppProviderCallback::e_StringIDCalcOverride:
        wsString = L"Calculate Override";
        break;
      case AppProviderCallback::e_StringIDModifyField:
        wsString = L"Are you sure you want to modify this field?";
        break;
      case AppProviderCallback::e_StringIDNotModifyField:
        wsString = L"You are not allowed to modify this field.";
        break;
      case AppProviderCallback::e_StringIDAppName:
        wsString = L"Foxit SDK";
        break;
      case AppProviderCallback::e_StringIDImageFilter:
        wsString = L"Image Files(*.bmp;*.jpg;*.png;*.gif;*.tif)|*.bmp;*.jpg;*.png;*.gif;*.tif|All Files(*.*)|*.*||";
        break;
      case AppProviderCallback::e_StringIDUnknownCaught:
        wsString = L"unknown error is catched!";
        break;
      case AppProviderCallback::e_StringIDUnableToSet:
        wsString = L"Unable to set ";
        break;
      case AppProviderCallback::e_StringIDValueExcalmatory:
        wsString = L" value!";
        break;
      case AppProviderCallback::e_StringIDInvalidEnumValue:
        wsString = L"Invalid enumerated value: ";
        break;
      case AppProviderCallback::e_StringIDUnsupportMethod:
        wsString = L"Unsupport %s method.";
        break;
      case AppProviderCallback::e_StringIDUnsupportProperty:
        wsString = L"Usupport %s property.";
        break;
      case AppProviderCallback::e_StringIDInvalidPropertySetOperation:
        wsString = L"Invalid property set operation;";
        break;
      case AppProviderCallback::e_StringIDNotDefaultValue:
        wsString = L" doesn't have a default property";
        break;
      case AppProviderCallback::e_StringIDUnableSetLanguage:
        wsString = L"Unable to set language value!";
        break;
      case AppProviderCallback::e_StringIDUnableSetNumPages:
        wsString = L"Unable to set numPages value!";
        break;
      case AppProviderCallback::e_StringIDUnableSetPlatformValue:
        wsString = L"Unable to set platform value!";
        break;
      case AppProviderCallback::e_StringIDUnableSetValidationsEnabledValue:
        wsString = L"Unable to set validationsEnabled value!";
        break;
      case AppProviderCallback::e_StringIDUnableSetValidationsValue:
        wsString = L"Unable to set variation value!";
        break;
      case AppProviderCallback::e_StringIDUnableSetVersion:
        wsString = L"Unable to set version value!";
        break;
      case AppProviderCallback::e_StringIDUnableSetReady:
        wsString = L"Unable to set ready value!";
        break;
      case AppProviderCallback::e_StringIDNumberOfOccur:
        wsString = L"The element [%s] has violated its allowable number of occurrences";
        break;
      case AppProviderCallback::e_StringIDUnableSetClassName:
        wsString = L"Unable to set className value!";
        break;
      case AppProviderCallback::e_StringIDUnableSetLengthValue:
        wsString = L"Unable to set length value!";
        break;
      case AppProviderCallback::e_StringIDUnsupportChar:
        wsString = L"unsupported char '%c'";
        break;
      case AppProviderCallback::e_StringIDBadSuffix:
        wsString = L"bad suffix on number";
        break;
      case AppProviderCallback::e_StringIDExpectedIdent:
        wsString = L"expected identifier instead of '%s'";
        break;
      case AppProviderCallback::e_StringIDExpectedString:
        wsString = L"expected '%s' instead of '%s'";
        break;
      case AppProviderCallback::e_StringIDInvalidateChar:
        wsString = L"invalidate char '%c'";
        break;
      case AppProviderCallback::e_StringIDRedefinition:
        wsString = L"'%s' redefinition ";
        break;
      case AppProviderCallback::e_StringIDInvalidToken:
        wsString = L"invalidate token '%s'";
        break;
      case AppProviderCallback::e_StringIDInvalidExpression:
        wsString = L"invalidate expression '%s'";
        break;
      case AppProviderCallback::e_StringIDUndefineIdentifier:
        wsString = L"undefined identifier '%s'";
        break;
      case AppProviderCallback::e_StringIDInvalidateLeftValue:
        wsString = L"invalidate left-value '%s'";
        break;
      case AppProviderCallback::e_StringIDCompilerError:
        wsString = L"compiler error";
        break;
      case AppProviderCallback::e_StringIDCannotModifyValue:
        wsString = L"can't modify the '%s' value";
        break;
      case AppProviderCallback::e_StringIDParametersError:
        wsString = L"function '%s' has not %d parameters";
        break;
      case AppProviderCallback::e_StringIDExpectedEndIf:
        wsString = L"expected 'endif' instead of '%s'";
        break;
      case AppProviderCallback::e_StringIDUnexpectedExpression:
        wsString = L"unexpected expression '%s'";
        break;
      case AppProviderCallback::e_StringIDConditionIsNull:
        wsString = L"condition is null";
        break;
      case AppProviderCallback::e_StringIDIllegalBreak:
        wsString = L"illegal break";
        break;
      case AppProviderCallback::e_StringIDIllegalContinue:
        wsString = L"illegal continue";
        break;
      case AppProviderCallback::e_StringIDExpectedOperator:
        wsString = L"expected operator '%s' instead of '%s'";
        break;
      case AppProviderCallback::e_StringIDDivideZero:
        wsString = L"divide by zero";
        break;
      case AppProviderCallback::e_StringIDCannotCovertToObject:
        wsString = L"%s.%s can not covert to object";
        break;
      case AppProviderCallback::e_StringIDNotFoundContainer:
        wsString = L"can not found container '%s'";
        break;
      case AppProviderCallback::e_StringIDNotFoundProperty:
        wsString = L"can not found property '%s'";
        break;
      case AppProviderCallback::e_StringIDNotFoundMethod:
        wsString = L"can not found method '%s'";
        break;
      case AppProviderCallback::e_StringIDNotFoundConst:
        wsString = L"can not found const '%s'";
        break;
      case AppProviderCallback::e_StringIDNotAssignObject:
        wsString = L"can not direct assign value to object";
        break;
      case AppProviderCallback::e_StringIDInvalidateInstruction:
        wsString = L"invalidate instruction";
        break;
      case AppProviderCallback::e_StringIDExpectedNumber:
        wsString = L"expected number instead of '%s'";
        break;
      case AppProviderCallback::e_StringIDValidateOutOfArray:
        wsString = L"validate access index '%s' out of array";
        break;
      case AppProviderCallback::e_StringIDCannotAssign:
        wsString = L"can not assign to %s";
        break;
      case AppProviderCallback::e_StringIDNotFoundFunction:
        wsString = L"can not found '%s' function";
        break;
      case AppProviderCallback::e_StringIDIsNotArray:
        wsString = L"'%s' doesn't an array";
        break;
      case AppProviderCallback::e_StringIDOutOfArrayRange:
        wsString = L"out of range of '%s' array";
        break;
      case AppProviderCallback::e_StringIDNotSupportArrayCalculate:
        wsString = L"'%s' operator can not support array calculate";
        break;
      case AppProviderCallback::e_StringIDArgumentNotArray:
        wsString = L"'%s' function's %d argument can not be array";
        break;
      case AppProviderCallback::e_StringIDArgumentExpectContainer:
        wsString = L"'%s' argument expected a container";
        break;
      case AppProviderCallback::e_StringIDAccessProertyInNotObject:
        wsString = L"an attempt was made to reference property '%s' of a non-object in SOM expression %s";
        break;
      case AppProviderCallback::e_StringIDFunctionBuildIn:
        wsString = L"function '%s' is buildin";
        break;
      case AppProviderCallback::e_StringIDErrorMessage:
        wsString = L"%s : %s";
        break;
      case AppProviderCallback::e_StringIDIndexValueOutOfBounds:
        wsString = L"Index value is out of bounds";
        break;
      case AppProviderCallback::e_StringIDIncorrectNumberOfMethod:
        wsString = L"Incorrect number of parameters calling method '%s'";
        break;
      case AppProviderCallback::e_StringIDArgumentMismatch:
        wsString = L"Argument mismatch in property or function argument";
        break;
      case AppProviderCallback::e_StringIDInvalidEnumerate:
        wsString = L"Invalid enumerated value: %s";
        break;
      case AppProviderCallback::e_StringIDInvalidAppend:
        wsString = L"Invalid append operation: %s cannot have a child element of %s";
        break;
      case AppProviderCallback::e_StringIDSOMExpectedList:
        wsString = L"SOM expression breaked list when single result was expected";
        break;
      case AppProviderCallback::e_StringIDNotHaveProperty:
        wsString = L"'%s' doesn't have property '%s'";
        break;
      case AppProviderCallback::e_StringIDInvalidNodeType:
        wsString = L"Invalid node type : '%s'";
        break;
      case AppProviderCallback::e_StringIDViolateBoundary:
        wsString = L"The element [%s] has violated its allowable number of occurrences";
        break;
      case AppProviderCallback::e_StringIDServerDeny:
        wsString = L"Server does not permit";
        break;
      case AppProviderCallback::e_StringIDWeekDaySun:
        wsString = L"Sunday";
        break;
      case AppProviderCallback::e_StringIDWeekDayMon:
        wsString = L"Monday";
        break;
      case AppProviderCallback::e_StringIDWeekDayTue:
        wsString = L"Tuesday";
        break;
      case AppProviderCallback::e_StringIDWeekDayWed:
        wsString = L"Wednesday";
        break;
      case AppProviderCallback::e_StringIDWeekDayThu:
        wsString = L"Thursday";
        break;
      case AppProviderCallback::e_StringIDWeekDayFri:
        wsString = L"Friday";
        break;
      case AppProviderCallback::e_StringIDWeekDaySat:
        wsString = L"Saturday";
        break;
      case AppProviderCallback::e_StringIDMonthJan:
        wsString = L"January";
        break;
      case AppProviderCallback::e_StringIDMonthFeb:
        wsString = L"February";
        break;
      case AppProviderCallback::e_StringIDMonthMarch:
        wsString = L"March";
        break;
      case AppProviderCallback::e_StringIDMonthApril:
        wsString = L"April";
        break;
      case AppProviderCallback::e_StringIDMonthMay:
        wsString = L"May";
        break;
      case AppProviderCallback::e_StringIDMonthJune:
        wsString = L"June";
        break;
      case AppProviderCallback::e_StringIDMonthJuly:
        wsString = L"July";
        break;
      case AppProviderCallback::e_StringIDMonthAug:
        wsString = L"August";
        break;
      case AppProviderCallback::e_StringIDMonthSep:
        wsString = L"September";
        break;
      case AppProviderCallback::e_StringIDMonthOct:
        wsString = L"October";
        break;
      case AppProviderCallback::e_StringIDMonthNov:
        wsString = L"November";
        break;
      case AppProviderCallback::e_StringIDMonthDec:
        wsString = L"December";
        break;
      case AppProviderCallback::e_StringIDToday:
        wsString = L"Today";
        break;
      case AppProviderCallback::e_StringIDValidateLimit:
        wsString = L"Message limit exceeded. Remaining %d validation errors not reported.";
        break;
      case AppProviderCallback::e_StringIDValidateNullWarning:
        wsString = L"%s cannot be left blank. To ignore validations for %s, click Ignore.";
        break;
      case AppProviderCallback::e_StringIDValidateNullError:
        wsString = L"%s cannot be left blank.";
        break;
      case AppProviderCallback::e_StringIDValidateWarning:
        wsString = L"The value you entered for %s is invalid. To ignore validations for %s, click Ignore.";
        break;
      case AppProviderCallback::e_StringIDValidateError:
        wsString = L"The value you entered for %s is invalid.";
        break;
      case AppProviderCallback::e_StringIDValidateNumberError:
        wsString = L"Illegal value:cannot assign '%s' to %s.";
        break;
      case AppProviderCallback::e_StringIDScriptFailedError:
        wsString = L"Script failed(language is %s;context is %s) script=%s ";
        break;
      case AppProviderCallback::e_StringIDScriptInvalidValue:
        wsString = L"Error:Invalid enumerated value:%s";
        break;
      case AppProviderCallback::e_StringIDSubmitValidateNullError:
        wsString = L"At least one required field was empty.Please fill in the required fields(highlighted) before continuing.";
        break;
      case AppProviderCallback::e_StringIDInvalidBarcodeValue:
        wsString = L"Invalid Barcode Value: %s is an invalid value for barcodes of type %s.";
          break;
      case AppProviderCallback::e_StringIDScriptArgumentMismatch:
          wsString = L"Error:Argument mismatch in property or function argument.";
          break;
      }

      return wsString;
}

foxit::WStringArray MyXFAAppProviderCallback::ShowFileDialog(const wchar_t* string_title, const wchar_t* string_filter, bool is_openfile_dialog) {
    foxit::WStringArray wide_str_array;
    QString dialog_title = is_openfile_dialog?"Open":"Save as";
    QString file_ext_filter = QString::fromWCharArray(string_filter);
    QString file_path;
    if (is_openfile_dialog)
        file_path = QFileDialog::getOpenFileName( parent_window_, dialog_title, "", file_ext_filter ) ;
    else
        file_path = QFileDialog::getSaveFileName(parent_window_, dialog_title, "", file_ext_filter);
    wide_str_array.Add(file_path.toStdWString().c_str());

    return wide_str_array;
}
