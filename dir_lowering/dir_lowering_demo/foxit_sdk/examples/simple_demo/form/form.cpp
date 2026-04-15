// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to add form field and
// get form field information.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/pdf/interform/fs_pdfform.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace annots;
using namespace actions;
using namespace interform;

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

void AddInteractiveForms(PDFPage & page,interform::Form &form)
{
  {
    // Add push button field.
    Control btn_submit = form.AddControl(page, L"Push Button Submit", Field::e_TypePushButton, RectF(50, 750, 150, 780));

    // Set default appearance
    foxit::pdf::DefaultAppearance default_ap;
    default_ap.flags = DefaultAppearance::e_FlagFont | DefaultAppearance::e_FlagFontSize | DefaultAppearance::e_FlagTextColor;
    default_ap.font = Font(Font::e_StdIDHelveticaB);
    default_ap.text_size = 12.0f;
    default_ap.text_color = 0x000000;
    form.SetDefaultAppearance(default_ap);

    // Set push button appearance.
    Widget widget = btn_submit.GetWidget();
    widget.SetHighlightingMode(foxit::pdf::annots::Annot::e_HighlightingPush);
    widget.SetMKBorderColor(0xFF0000);
    widget.SetMKBackgroundColor(0xF0F0F0);
    widget.SetMKNormalCaption(L"Submit");
    widget.ResetAppearanceStream();

    // Set submit form action.
    actions::SubmitFormAction submit_action = (actions::SubmitFormAction)Action::Create(form.GetDocument(), Action::e_TypeSubmitForm);
    int count = form.GetFieldCount(NULL);
    WStringArray name_array;
    for (int i = 0; i < count; i++) {
      name_array.Add(form.GetField(i,NULL).GetName());
    }

    submit_action.SetFieldNames(name_array);
    submit_action.SetURL("http://www.foxitsoftware.com");
    widget.SetAction(submit_action);
    cout << "Add button field." << endl;
  }
  {
    // Add radio button group
    Control control = form.AddControl(page, L"Radio Button0", Field::e_TypeRadioButton, RectF(50.0, 700, 90, 740));
    Control control1 = form.AddControl(page, L"Radio Button0", Field::e_TypeRadioButton, RectF(100.0, 700, 140, 740));
    control.SetExportValue(L"YES");
    control.SetChecked(true);
    // Update radio button's appearance.
    control.GetWidget().ResetAppearanceStream();

    control1.SetExportValue(L"NO");
    control1.SetChecked(false);
    // Update radio button's appearance.
    control1.GetWidget().ResetAppearanceStream();

    cout << "Add radio button." << endl;
  }
  {
    // Add check box
    Control control = form.AddControl(page, L"Check Box0", Field::e_TypeCheckBox, RectF(50.0, 650, 90, 690));
    control.SetChecked(true);

    Widget widget = control.GetWidget();
    widget.SetMKBorderColor(0x000000);
    widget.SetMKBackgroundColor(0xFFFFFF);
    widget.ResetAppearanceStream();
    cout << "Add check box." << endl;
  }
  {
    // Add text field
    Control control = form.AddControl(page, L"Text Field0", Field::e_TypeTextField, RectF(50, 600, 90, 640));
    control.GetField().SetValue(L"3");
    // Update text field's appearance.
    control.GetWidget().ResetAppearanceStream();

    Control control1 = form.AddControl(page, L"Text Field1", Field::e_TypeTextField, RectF(100, 600, 140, 640));
    control1.GetField().SetValue(L"23");
    // Update text field's appearance.
    control1.GetWidget().ResetAppearanceStream();

    Control control2 = form.AddControl(page, L"Text Field2", Field::e_TypeTextField, RectF(150, 600, 190, 640));
    actions::JavaScriptAction javascipt_action = (actions::JavaScriptAction)Action::Create(form.GetDocument(), Action::e_TypeJavaScript);
    javascipt_action.SetScript(L"AFSimple_Calculate(\"SUM\", new Array (\"Text Field0\", \"Text Field1\"));" );
    Field field2 = control2.GetField();
    AdditionalAction additional_act(field2);
    additional_act.SetAction(AdditionalAction::e_TriggerFieldRecalculateValue,javascipt_action);
    field2.SetValue(L"333333");
    // Update text field's appearance.
    control2.GetWidget().ResetAppearanceStream();

    cout << "Add text field." << endl;

  }
  {
    // Add text field with flag comb
    Control control = form.AddControl(page, L"Text Field3", Field::e_TypeTextField, RectF(50, 570, 100, 590));
    Field field = control.GetField();
    uint32 flag = Field::e_FlagTextComb;
    field.SetFlags(flag);
    field.SetValue(L"94538");
    field.SetMaxLength(5);
    // Update text field's appearance.
    control.GetWidget().ResetAppearanceStream();

  }
  {
    // Add text field, with flag multiline.
    Control control = form.AddControl(page, L"Text Field4", Field::e_TypeTextField, RectF(110, 550, 190, 590));
    Field field = control.GetField();
    uint32 flag = Field::e_FlagTextMultiline;
    field.SetFlags(flag);
    field.SetValue(L"Text fields are boxes or spaces in which the user can enter text from the keyboard.");
    // Update text field's appearance.
    control.GetWidget().ResetAppearanceStream();
  }
  {
    // Add text field, with flag password.
    Control control = form.AddControl(page, L"Text Field5", Field::e_TypeTextField, RectF(200, 570, 240, 590));
    Field field = control.GetField();
    uint32 flag = Field::e_FlagTextPassword;
    field.SetFlags(flag);
    field.SetValue(L"Password");
    // Update text field's appearance.
    control.GetWidget().ResetAppearanceStream();
  }
  {
    // Add list box
    Control control = form.AddControl(page, L"List Box0",  Field::e_TypeListBox,RectF(50, 450, 350, 500));

    Field field = control.GetField();
    ChoiceOptionArray options;
    options.Add(interform::ChoiceOption(L"Foxit SDK", L"Foxit SDK",true,true));
    options.Add(interform::ChoiceOption(L"Foxit Reader", L"Foxit Reader",true,true));
    options.Add(interform::ChoiceOption(L"Foxit Phantom", L"Foxit Phantom",true,true));
    field.SetOptions(options);

    Widget widget = control.GetWidget();
    widget.SetMKBorderColor(0x000000);
    widget.SetMKBackgroundColor(0xFFFFFF);
    widget.ResetAppearanceStream();
  }
  {
    // Add combo box
    Control control = form.AddControl(page, L"Combo Box0",  Field::e_TypeComboBox,RectF(50, 350, 350, 400));

    Field field = control.GetField();
    ChoiceOptionArray options;
    options.Add(interform::ChoiceOption(L"Foxit SDK", L"Foxit SDK",true,true));
    options.Add(interform::ChoiceOption(L"Foxit Reader", L"Foxit Reader",true,true));
    options.Add(interform::ChoiceOption(L"Foxit Phantom", L"Foxit Phantom",true,true));
    field.SetOptions(options);

    Widget widget = control.GetWidget();
    widget.SetMKBorderColor(0x000000);
    widget.SetMKBackgroundColor(0xFFFFFF);
    widget.ResetAppearanceStream();
  }
}
int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"form/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    PDFDoc doc;
    interform::Form form(doc);
     // Create a blank new page and add some form fields.
    PDFPage page = doc.InsertPage(0);
    AddInteractiveForms(page,form);

    WString newPdf = output_directory + L"form.pdf";

    doc.SaveAs(newPdf, PDFDoc::e_SaveFlagNoOriginal);
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
