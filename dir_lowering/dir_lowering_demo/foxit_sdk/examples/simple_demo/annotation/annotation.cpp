
// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to add various annotations to PDF document.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#include <map>

#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"

#include "../../../include/pdf/actions/fs_action.h"
#include "../../../include/pdf/fs_signature.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/fs_actioncallback.h"
#include "../../../include/pdf/annots/fs_annot.h"
#include "../../../include/pdf/objects/fs_pdfobject.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/pdf/fs_psi.h"
#include "../../../include/pdf/fs_filespec.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace annots;
using foxit::pdf::annots::Line;

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

DateTime GetLocalDateTime() {
  time_t t = time(NULL);
#if (WINAPI_PARTITION_APP || WINAPI_PARTITION_PC_APP) || \
  (defined(_WIN32) || defined(_WIN64)) && _FX_COMPILER_ != _FX_VC6_
  struct tm _Tm;
  localtime_s(&_Tm, &t);
  struct tm* rime = &_Tm;
  _tzset();
  long time_zone = NULL;
  _get_timezone(&time_zone);
  int timezone_hour = time_zone / 3600 * -1;
  int timezone_minute = (abs(time_zone) % 3600) / 60;
#elif defined(__linux__)
  struct tm* rime = localtime(&t);
  tzset();
  int timezone_hour = __timezone / 3600 * -1;
  int timezone_minute = ((int)abs(__timezone) % 3600) / 60;
#elif defined(__APPLE__)
  struct tm* rime = localtime(&t);
  tzset();
  int timezone_hour = timezone / 3600 * -1;
  int timezone_minute = ((int)abs(timezone) % 3600) / 60;
#endif
  DateTime datetime;
  datetime.year = static_cast<uint16>(rime->tm_year + 1900);
  datetime.month = static_cast<uint16>(rime->tm_mon + 1);
  datetime.day = static_cast<uint16>(rime->tm_mday);
  datetime.hour = static_cast<uint16>(rime->tm_hour);
  datetime.minute = static_cast<uint16>(rime->tm_min);
  datetime.second = static_cast<uint16>(rime->tm_sec);
  datetime.utc_hour_offset = timezone_hour;
  datetime.utc_minute_offset = timezone_minute;

  return datetime;
}

String RandomUID() {
  String uuid;
  const char* c = "0123456789qwertyuiopasdfghjklzxcvbnm";

  for (int n = 0; n < 16; n++) {
    String uuid_temp;
    int b = rand() % 255;
    switch (n) {
    case 6:
      uuid_temp.Format("4%x", b % 15);
      break;
    case 8:
      uuid_temp.Format("%c%x", c[rand() % strlen(c)], b % 15);
      break;
    default:
      uuid_temp.Format("%02x", b);
      break;
    }
    uuid += uuid_temp;

    switch (n) {
    case 3:
    case 5:
    case 7:
    case 9:
      uuid += '-';
      break;
    }
  }
  return uuid;
}
class IconProvider : public IconProviderCallback {
public:
  static IconProvider* Create(string path) {
    return new IconProvider(path);
  }
  virtual void Release() {
    delete this;
  }

  // If one icon provider offers different style icon for one icon name of a kind of annotaion,
  // please use different provider ID or version in order to distinguish different style for Foxit PDF SDK.
  // Otherwise, only the first style icon for the same icon name of same kind of annotation will have effect.
  virtual String GetProviderID() {
    if (use_dynamic_stamp_)
      return "Simple Demo Dynamic IconProvider";
    else
      return "Simple Demo IconProvider";
  }

  virtual String GetProviderVersion() {
    return "1.0.0";
  }

  virtual bool HasIcon(Annot::Type annot_type, const char* icon_name) {
    std::map<string, PDFDoc>::iterator it = pdf_doc_map_.find(icon_name);

    if(it != pdf_doc_map_.end())
    {
      PDFDoc doc = (*it).second;
      return !doc.IsEmpty();
    }
    PDFDoc doc = PDFDoc();
    string path;
    if (doc.GetPageCount()==0) {
      try {
        if (use_dynamic_stamp_) {
          path = file_folder_ + "/DynamicStamps/" + icon_name + ".pdf";
        } else {
          path = file_folder_ + "/StaticStamps/" + icon_name + ".pdf";
        }
        doc = PDFDoc(path.c_str());
        ErrorCode error_code = doc.Load();
        if (foxit::e_ErrSuccess != error_code) {
          doc = PDFDoc();
        } else {
          pdf_doc_map_.insert(std::pair<string, PDFDoc>(path, doc));
        }
      } catch (const Exception& e) {
        cout << e.GetMessage() << endl;
      }
    }
    return !doc.IsEmpty();
  }

  virtual bool CanChangeColor(Annot::Type annot_type, const char* icon_name) {
    return false;
  }

  virtual PDFPage GetIcon(Annot::Type annot_type, const char* icon_name, foxit::ARGB color, foxit::pdf::objects::PDFDictionary* annot_dict) {
    string path;
    if (use_dynamic_stamp_) {
      path = file_folder_ + "/DynamicStamps/" + icon_name + ".pdf";
    } else {
      path = file_folder_ + "/StaticStamps/" + icon_name + ".pdf";
    }
    std::map<string, PDFDoc>::iterator it = pdf_doc_map_.find(path);

    PDFDoc doc = ((it != pdf_doc_map_.end()) ? (*it).second : PDFDoc());
    if (doc.IsEmpty() || doc.GetPageCount() == 0)
      return PDFPage();
    return doc.GetPage(0);
  }

  virtual bool GetShadingColor(Annot::Type annot_type, const char* icon_name, foxit::RGB referenced_color,
    int shading_index, foxit::pdf::annots::ShadingColor& shading_color) {
      return false;
  }

  virtual float GetDisplayWidth(Annot::Type annot_type, const char* icon_name) {
    return 0.0f;
  }

  virtual float GetDisplayHeight(Annot::Type annot_type, const char* icon_name) {
    return 0.0f;
  }

  void SetUseDynamicStamp(bool use_dynamic_stamp) {
    use_dynamic_stamp_ = use_dynamic_stamp;
  }

private:
  IconProvider(string file_folder)
    : file_folder_(file_folder)
    , use_dynamic_stamp_(false)
    {}
  virtual ~IconProvider() {
  }
  std::map<string, PDFDoc> pdf_doc_map_;
  string file_folder_;
  vector<string> incon_names_;
  bool use_dynamic_stamp_;
};

class ActionEvent : public foxit::ActionCallback {
public:
  ActionEvent(const PDFDoc& document) {current_doc_ = document;}
  ActionEvent() {}
  ~ActionEvent() {}
  virtual void Release() {delete this;}
  virtual bool InvalidateRect(const PDFDoc& document, int page_index, const RectF& pdf_rect) {
    return false;
  }
  virtual int GetCurrentPage(const PDFDoc& document) {
    return -1;
  }
  virtual void SetCurrentPage(const PDFDoc& document, int page_index) {}
  virtual void SetCurrentPage(const pdf::PDFDoc& document, const foxit::pdf::Destination& destination){}
  virtual foxit::common::Rotation GetPageRotation(const PDFDoc& document, int page_index) {
    return foxit::common::e_Rotation0;
  }
  virtual bool SetPageRotation(const PDFDoc& document, int page_index, foxit::common::Rotation rotation) {
    return false;
  }
  virtual bool ExecuteNamedAction(const PDFDoc& document, const char* named_action) {
    return false;
  }
  virtual bool SetDocChangeMark(const PDFDoc& document, bool change_mark) {
    return false;
  }
  virtual bool GetDocChangeMark(const PDFDoc& document) {
    return false;
  }
  virtual int GetOpenedDocCount() {
    return -1;
  }
  virtual PDFDoc GetOpenedDoc(int index) {
    return current_doc_;
  }
  PDFDoc GetCurrentDoc() {
    return current_doc_;
  }
  PDFDoc CreateBlankDoc() {
    return PDFDoc();
  }

  PDFDoc OpenDoc(const foxit::WString& file_path, const foxit::WString& password) {
    return PDFDoc(file_path);
  }
  virtual void CloseDoc(const pdf::PDFDoc& document, bool is_prompt_to_save) {}
  virtual bool Beep(int type) {
    return false;
  }
  virtual WString Response(const wchar_t* question, const wchar_t* title, const wchar_t* default_value, const wchar_t* label,
    bool is_password) {
      return L"";
  }
  virtual WString GetFilePath(const PDFDoc& document) {
    return L"";
  }
  virtual bool IsLocalFile(const pdf::PDFDoc& document) { return true; }
  virtual bool Print(const PDFDoc& document, bool is_ui,
    const common::Range& page_set, bool is_silent ,
    bool is_shrunk_to_fit, bool is_printed_as_image,
    bool is_reversed, bool is_to_print_annots) {
      return false;
  }
  virtual bool Print(const pdf::PDFDoc& document, const PrintParams& print_params) { return false; }
  virtual bool SubmitForm(const PDFDoc& document, void* form_data, foxit::uint32 length, const char* url, foxit::common::FileFormatType file_format_type) {
    return false;
  }
  virtual bool LaunchURL(const char* url) {
    return false;
  }
  virtual WString BrowseFile() {
    return L"";
  }
  virtual WString BrowseFile(bool is_open_dialog, const wchar_t* file_format, const wchar_t* file_filter) {
    return L"";
  }
  virtual foxit::ActionCallback::Language GetLanguage() {
    return foxit::ActionCallback::e_LanguageCHS;
  }
  virtual int Alert(const wchar_t* msg, const wchar_t* title, int type, int icon) {
    return 0;
  }
  virtual foxit::IdentityProperties GetIdentityProperties() {
    return foxit::IdentityProperties(L"foxitsoftware", L"simple_demo@foxitsoftware.cn", L"simple demo", L"Simple", L"simple", L"demo", L"developer", L"gsdk");
  }
  virtual bool SetIdentityProperties(const foxit::IdentityProperties& identity_properties) {
    return false;
  }
  virtual WString PopupMenu(const foxit::MenuListArray& menus, bool& is_selected_item) {
    return L"";
  }

  foxit::MenuItemEx PopupMenuEx(const foxit::MenuItemExArray& menus, bool& is_selected_item)
  {
    return foxit::MenuItemEx();
  }

  virtual WString GetAppInfo(foxit::ActionCallback::AppInfoType type) {
    return L"";
  }
  virtual bool MailData(void* data, MailType data_type, bool is_ui, const wchar_t* to,
    const wchar_t* subject, const wchar_t* cc, const wchar_t* bcc, const wchar_t* message) {
      return false;
  }
  virtual JsMailResult MailDoc(const pdf::PDFDoc& document,
    const wchar_t* to_address, const wchar_t* cc_address, const wchar_t* bcc_address,
    const wchar_t* subject, const wchar_t* message, bool is_ui) {
    return JsMailResult::e_JSMailResultFailed;
  }
  virtual uint32 VerifySignature(const pdf::PDFDoc& document, const pdf::Signature& pdf_signature) {
    return pdf::Signature::e_StateUnknown;
  }
  virtual WString GetUntitledBookmarkName() { return L"Untitled"; }

  virtual WStringArray GetPrinterNameList() {
    return WStringArray();
  }

  virtual bool AddToolButton(const ButtonItem& button_item) { return false; }
  virtual bool RemoveToolButtom(const wchar_t* button_name) { return false; }
  virtual MenuListArray GetMenuItemNameList() { return MenuListArray(); }
  virtual bool AddSubMenu(const MenuItemConfig& menu_item_config) { return false; }
  virtual bool AddMenuItem(const MenuItemConfig& menu_item_config, bool is_prepend) { return false; }
  virtual bool ShowDialog(const DialogDescriptionConfig& dlg_config) { return true; }
  virtual bool GetFullScreen() { return false; }
  virtual void SetFullScreen(bool is_full_screen) {}
  virtual void OnFieldValueChanged(const wchar_t* field_name, JSFieldValueChangeType type, const WStringArray &value_before_changed, const WStringArray &value_after_changed) {}
  virtual MediaPlayerCallback* OpenMediaPlayer(const PlayerArgs& player_args) { return NULL; }
  virtual WString GetAttachmentsFilePath(const pdf::PDFDoc& pdf_doc, const wchar_t* name) { return L""; }
  virtual WString GetExtractedEmbeddedFilePath(const pdf::PDFDoc& pdf_doc, const wchar_t* name) { return L""; }
  virtual void UpdateLogicalLabel() {}
  virtual WString GetTemporaryFileName(const pdf::PDFDoc& document, const wchar_t* file_name) { return L""; }
  virtual WString GetTemporaryDirectory() { return L""; }
  virtual void Scroll(const PointF& point) {}
  virtual void SelectPageNthWord(int page_index, int start_offset, int end_offset, bool is_show_selection) {}
  virtual PointF GetMousePosition() { return PointF(); }
  virtual RectF GetPageWindowRect(const pdf::PDFDoc& pdf_doc, int ) { return RectF(); }
  virtual LayoutMode GetLayoutMode() { return LayoutMode::e_LayoutModeContinuous; }
  virtual void SetLayoutMode(LayoutMode layout_mode, bool is_cover_mode) {}
  virtual float GetPageScale() { return 0; }
  virtual void SetPageScale(foxit::pdf::Destination::ZoomMode zoom_mode, const foxit::pdf::Destination& dest) {}
  virtual Destination::ZoomMode GetPageZoomMode() { return Destination::e_ZoomFitBHorz; }
  virtual void Query(const wchar_t* keywords, SearchScope search_scope, const SearchOption& search_option, const wchar_t* di_path) {}
  virtual SearchIndexConfig AddSearchIndex(const wchar_t* di_path, bool is_selected) { return SearchIndexConfig(); }
  virtual bool RemoveSearchIndex(const SearchIndexConfig& search_index_config) { return false; }
  virtual WStringArray GetSignatureAPStyleNameList() { return WStringArray(); }
  virtual SOAPResponseInfo SoapRequest(const SOAPRequestProperties& request_params) {return SOAPResponseInfo();}
  virtual void EnablePageLoop(bool is_loop) {}
  virtual bool IsPageLoop() {return true;}
  virtual void SetDefaultPageTransitionMode(const wchar_t* trans_type, const wchar_t* trans_di) {}
  virtual bool IsCurrentDocOpenedInBrowser() { return false; }
  virtual void PostMessageToHtml(WStringArray message) {}
  virtual void NotifyBeginDoJob(const pdf::PDFDoc& document, JavascriptModifyItemInfo::JavascriptEventType event_type) {}
  virtual void NotifyAfterDataChange(const pdf::PDFDoc& document, JavascriptModifyItemInfo modify_item_info) {}
  virtual void NotifyEndDoJob(const pdf::PDFDoc& document, JavascriptModifyItemInfo::JavascriptEventType event_type) {}
  virtual bool InitModifyItem(const pdf::PDFDoc &document, ModifyItemType item_type, int page_index, const WString &dict_name) {
      return true;
  }
  virtual void ResetModifyItem(const pdf::PDFDoc &document) { }
  virtual int GetVisiblePageCount(const pdf::PDFDoc& document) { return 0; }
  virtual int GetVisiblePage(const pdf::PDFDoc& document, int index) { return -1; }
  private:
    PDFDoc current_doc_;
};

void AddAnnotations(PDFPage &page)
{
  {
    // Add line annotation 
    // No special intent, as a common line.
    annots::Line line(page.AddAnnot(Annot::e_Line,RectF(0,650,100,750)));
    //This flag is used for printing annotations.
    line.SetFlags(4);
    line.SetStartPoint(PointF(20,650));
    line.SetEndPoint(PointF(100,740));
    // Intent, as line arrow.
    line.SetContent(L"A line arrow annotation");
    line.SetIntent("LineArrow");
    line.SetSubject(L"Arrow");
    line.SetTitle(L"Foxit SDK");
    line.SetCreationDateTime(GetLocalDateTime());
    line.SetModifiedDateTime(GetLocalDateTime());
    line.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    line.ResetAppearanceStream();

    line = annots::Line(page.AddAnnot(Annot::e_Line,RectF(0,650,100,760)));
    //This flag is used for printing annotations.
    line.SetFlags(4);
    // Set foxit RGB color
    line.SetBorderColor(0x00FF00);
    line.SetStartPoint(PointF(10,650));
    line.SetEndPoint(PointF(100,750));
    line.SetContent(L"A common line.");
    line.SetLineStartStyle(annots::Markup::e_EndingStyleSquare);
    line.SetLineEndStyle(annots::Markup::e_EndingStyleOpenArrow);
    // Show text in line
    line.EnableCaption(true);
    line.SetCaptionOffset(PointF(0,5));

    line.SetSubject(L"Line");
    line.SetTitle(L"Foxit SDK");
    line.SetCreationDateTime(GetLocalDateTime());
    line.SetModifiedDateTime(GetLocalDateTime());
    line.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    line.ResetAppearanceStream();
    cout << "Add a line annotations." << endl;
  }

  {
    // Add circle annotation
    annots::Circle circle(page.AddAnnot(Annot::e_Circle,RectF(100,650,200,750)));
    //This flag is used for printing annotations.
    circle.SetFlags(4);
    circle.SetInnerRect(RectF(120,660,160,740));
    circle.SetSubject(L"Circle");
    circle.SetTitle(L"Foxit SDK");
    circle.SetCreationDateTime(GetLocalDateTime());
    circle.SetModifiedDateTime(GetLocalDateTime());
    circle.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    circle.ResetAppearanceStream();
    cout << "Add a circle annotation." << endl;
  }

  {
    // Add square annotation
    annots::Square square(page.AddAnnot(Annot::e_Square,RectF(200,650,300,750)));
    //This flag is used for printing annotations.
    square.SetFlags(4);
    square.SetFillColor(0x00FF00);
    square.SetInnerRect(RectF(220,660,260,740));
    square.SetSubject(L"Square");
    square.SetTitle(L"Foxit SDK");
    square.SetCreationDateTime(GetLocalDateTime());
    square.SetModifiedDateTime(GetLocalDateTime());
    square.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    square.ResetAppearanceStream();
    cout << "Add a square annotation." << endl;
  }

  {
    // Add polygon annotation, as cloud.
    annots::Polygon polygon(page.AddAnnot(Annot::e_Polygon,RectF(300,650,500,750)));
    //This flag is used for printing annotations.
    polygon.SetFlags(4);
    polygon.SetIntent("PolygonCloud");
    polygon.SetFillColor(0x0000FF);
    foxit::PointFArray vertexe_array;
    vertexe_array.Add(PointF(335,665));
    vertexe_array.Add(PointF(365,665));
    vertexe_array.Add(PointF(385,705));
    vertexe_array.Add(PointF(365,740));
    vertexe_array.Add(PointF(335,740));
    vertexe_array.Add(PointF(315,705));
    polygon.SetVertexes(vertexe_array);
    polygon.SetSubject(L"Cloud");
    polygon.SetTitle(L"Foxit SDK");
    polygon.SetCreationDateTime(GetLocalDateTime());
    polygon.SetModifiedDateTime(GetLocalDateTime());
    polygon.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    polygon.ResetAppearanceStream();
    cout << "Add a polygon annotation." << endl;
  }

  {
    // Add polygon annotation, with dashed border.
    BorderInfo borderinfo;
    borderinfo.cloud_intensity = 2.0f;
    borderinfo.width = 2.0f;
    borderinfo.style = BorderInfo::e_Dashed;
    borderinfo.dash_phase = 3.f;
    borderinfo.dashes.SetSize(2);
    borderinfo.dashes.SetAt(0,2);
    borderinfo.dashes.SetAt(1,2);

    annots::Polygon polygon(page.AddAnnot(Annot::e_Polygon,RectF(400,650,500,750)));
    //This flag is used for printing annotations.
    polygon.SetFlags(4);
    polygon.SetFillColor(0x0000FF);
    polygon.SetBorderInfo(borderinfo);
    foxit::PointFArray vertexe_array;
    vertexe_array.Add(PointF(435,665));
    vertexe_array.Add(PointF(465,665));
    vertexe_array.Add(PointF(485,705));
    vertexe_array.Add(PointF(465,740));
    vertexe_array.Add(PointF(435,740));
    vertexe_array.Add(PointF(415,705));

    polygon.SetVertexes(vertexe_array);
    polygon.SetSubject(L"Polygon");
    polygon.SetTitle(L"Foxit SDK");
    polygon.SetCreationDateTime(GetLocalDateTime());
    polygon.SetModifiedDateTime(GetLocalDateTime());
    polygon.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    polygon.ResetAppearanceStream();
    cout << "Add a polygon cloud annotation." << endl;
  }

  {
    // Add polyline annotation
    annots::PolyLine polyline(page.AddAnnot(Annot::e_PolyLine,RectF(500,650,600,700)));
    //This flag is used for printing annotations.
    polyline.SetFlags(4);
    foxit::PointFArray vertexe_array;
    vertexe_array.Add(PointF(515,705));
    vertexe_array.Add(PointF(535,740));
    vertexe_array.Add(PointF(565,740));
    vertexe_array.Add(PointF(585,705));
    vertexe_array.Add(PointF(565,665));
    vertexe_array.Add(PointF(535,665));
    polyline.SetVertexes(vertexe_array);
    polyline.SetSubject(L"PolyLine");
    polyline.SetTitle(L"Foxit SDK");
    polyline.SetCreationDateTime(GetLocalDateTime());
    polyline.SetModifiedDateTime(GetLocalDateTime());
    polyline.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    polyline.ResetAppearanceStream();
    cout << "Add a polyline annotation." << endl;
  }

  {
    // Add freetext annotation, as type writer.
    annots::FreeText freetext(page.AddAnnot(Annot::e_FreeText,RectF(10,550,200,600)));
    //This flag is used for printing annotations.
    freetext.SetFlags(4);
    // Set default appearance
    foxit::pdf::DefaultAppearance default_ap;
    default_ap.flags = DefaultAppearance::e_FlagFont | DefaultAppearance::e_FlagFontSize | DefaultAppearance::e_FlagTextColor;
    default_ap.font = common::Font(common::Font::e_StdIDHelvetica);
    default_ap.text_size = 12.0f;
    default_ap.text_color = 0x000000;
    // Set default appearance for form.
    freetext.SetDefaultAppearance(default_ap);
    freetext.SetIntent("FreeTextTypewriter");
    freetext.SetContent(L"A typewriter annotation");
    freetext.SetSubject(L"FreeTextTypewriter");
    freetext.SetTitle(L"Foxit SDK");
    freetext.SetCreationDateTime(GetLocalDateTime());
    freetext.SetModifiedDateTime(GetLocalDateTime());
    freetext.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    freetext.ResetAppearanceStream();
    cout << "Add a typewriter freetext annotation." << endl;

  }
  {
    // Add freetext annotation, as call-out.
    annots::FreeText freetext(page.AddAnnot(Annot::e_FreeText,RectF(300,550,400,600)));
    //This flag is used for printing annotations.
    freetext.SetFlags(4);
    // Set default appearance
    foxit::pdf::DefaultAppearance default_ap;
    default_ap.flags = DefaultAppearance::e_FlagFont | DefaultAppearance::e_FlagFontSize | DefaultAppearance::e_FlagTextColor;
    default_ap.font = common::Font(common::Font::e_StdIDHelveticaB);
    default_ap.text_size = 12.0f;
    default_ap.text_color = 0x000000;
    // Set default appearance for form.
    freetext.SetDefaultAppearance(default_ap);
    freetext.SetIntent("FreeTextCallout");
    PointFArray callout_points;
    callout_points.Add(PointF(250,540));
    callout_points.Add(PointF(280,570));
    callout_points.Add(PointF(300,570));

    freetext.SetCalloutLinePoints(callout_points);
    freetext.SetCalloutLineEndingStyle(annots::Markup::e_EndingStyleOpenArrow);
    freetext.SetContent(L"A callout annotation.");
    freetext.SetSubject(L"FreeTextCallout");
    freetext.SetTitle(L"Foxit SDK");
    freetext.SetCreationDateTime(GetLocalDateTime());
    freetext.SetModifiedDateTime(GetLocalDateTime());
    freetext.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    freetext.ResetAppearanceStream();
    cout << "Add a callout freetext annotation." << endl;
  }
  {
    // Add freetext annotation, as text box.
    annots::FreeText freetext(page.AddAnnot(Annot::e_FreeText,RectF(450,550,550,600)));
    //This flag is used for printing annotations.
    freetext.SetFlags(4);
    // Set default appearance
    foxit::pdf::DefaultAppearance default_ap;
    default_ap.flags = DefaultAppearance::e_FlagFont | DefaultAppearance::e_FlagFontSize | DefaultAppearance::e_FlagTextColor;
    default_ap.font = common::Font(common::Font::e_StdIDHelveticaI);
    default_ap.text_size = 12.0f;
    default_ap.text_color = 0x000000;
    // Set default appearance for form.
    freetext.SetDefaultAppearance(default_ap);
    freetext.SetContent(L"A text box annotation.");
    freetext.SetSubject(L"Textbox");
    freetext.SetTitle(L"Foxit SDK");
    freetext.SetCreationDateTime(GetLocalDateTime());
    freetext.SetModifiedDateTime(GetLocalDateTime());
    freetext.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    freetext.ResetAppearanceStream();
    cout << "Add a text box freetext annotation." << endl;
  }
  {
    // Add highlight annotation.
    annots::Highlight highlight(page.AddAnnot(Annot::e_Highlight,RectF(10,450,100,550)));
    //This flag is used for printing annotations.
    highlight.SetFlags(4);
    highlight.SetContent(L"Highlight");
    annots::QuadPoints quad_points;
    quad_points.first = PointF(10, 500);
    quad_points.second = PointF(90, 500);
    quad_points.third = PointF(10, 480);
    quad_points.fourth = PointF(90, 480);
    annots::QuadPointsArray quad_points_array;
    quad_points_array.Add(quad_points);
    highlight.SetQuadPoints(quad_points_array);
    highlight.SetSubject(L"Highlight");
    highlight.SetTitle(L"Foxit SDK");
    highlight.SetCreationDateTime(GetLocalDateTime());
    highlight.SetModifiedDateTime(GetLocalDateTime());
    highlight.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    highlight.ResetAppearanceStream();
    cout << "Add a highlight annotation." << endl;
  }
  {
    // Add underline annotation.
    annots::Underline underline(page.AddAnnot(Annot::e_Underline,RectF(100,450,200,550)));
    //This flag is used for printing annotations.
    underline.SetFlags(4);
    annots::QuadPoints quad_points;
    quad_points.first = PointF(110, 500);
    quad_points.second = PointF(190, 500);
    quad_points.third = PointF(110, 480);
    quad_points.fourth = PointF(190, 480);
    annots::QuadPointsArray quad_points_array;
    quad_points_array.Add(quad_points);
    underline.SetQuadPoints(quad_points_array);
    underline.SetSubject(L"Underline");
    underline.SetTitle(L"Foxit SDK");
    underline.SetCreationDateTime(GetLocalDateTime());
    underline.SetModifiedDateTime(GetLocalDateTime());
    underline.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    underline.ResetAppearanceStream();
    cout << "Add a underline annotation." << endl;
  }
  {
    // Add squiggly annotation.
    annots::Squiggly squiggly(page.AddAnnot(Annot::e_Squiggly,RectF(200,450,300,550)));
    //This flag is used for printing annotations.
    squiggly.SetFlags(4);
    squiggly.SetIntent("Squiggly");

    annots::QuadPoints quad_points;
    quad_points.first = PointF(210, 500);
    quad_points.second = PointF(290, 500);
    quad_points.third = PointF(210, 480);
    quad_points.fourth = PointF(290, 480);
    annots::QuadPointsArray quad_points_array;
    quad_points_array.Add(quad_points);
    squiggly.SetQuadPoints(quad_points_array);
    squiggly.SetSubject(L"Squiggly");
    squiggly.SetTitle(L"Foxit SDK");
    squiggly.SetCreationDateTime(GetLocalDateTime());
    squiggly.SetModifiedDateTime(GetLocalDateTime());
    squiggly.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    squiggly.ResetAppearanceStream();
    cout << "Add a squiggly annotation." << endl;
  }
  {
    // Add strikeout annotation.
    annots::StrikeOut strikeout(page.AddAnnot(Annot::e_StrikeOut, RectF(300,450,400,550)));
    //This flag is used for printing annotations.
    strikeout.SetFlags(4);
    annots::QuadPoints quad_points;
    quad_points.first = PointF(310, 500);
    quad_points.second = PointF(390, 500);
    quad_points.third = PointF(310, 480);
    quad_points.fourth = PointF(390, 480);
    annots::QuadPointsArray quad_points_array;
    quad_points_array.Add(quad_points);
    strikeout.SetQuadPoints(quad_points_array);
    strikeout.SetSubject(L"StrikeOut");
    strikeout.SetTitle(L"Foxit SDK");
    strikeout.SetCreationDateTime(GetLocalDateTime());
    strikeout.SetModifiedDateTime(GetLocalDateTime());
    strikeout.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    strikeout.ResetAppearanceStream();
    cout << "Add a strikeout annotation." << endl;
  }
  {
    // Add caret annotation.
    annots::Caret caret(page.AddAnnot( Annot::e_Caret, RectF(400,450,420,470)));
    //This flag is used for printing annotations.
    caret.SetFlags(4);
    caret.SetInnerRect(RectF(410,450,430,470));
    caret.SetContent(L"Caret annotation");
    caret.SetSubject(L"Caret");
    caret.SetTitle(L"Foxit SDK");
    caret.SetCreationDateTime(GetLocalDateTime());
    caret.SetModifiedDateTime(GetLocalDateTime());
    caret.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    caret.ResetAppearanceStream();
    cout << "Add a caret annotation." << endl;
  }
  {
    // Add note annotation
    annots::Note note(page.AddAnnot( Annot::e_Note, RectF(10,350,50,400)));
    //This flag is used for printing annotations.
    note.SetFlags(4);
    note.SetIconName("Comment");
    note.SetSubject(L"Note");
    note.SetTitle(L"Foxit SDK");
    note.SetContent(L"Note annotation.");
    note.SetCreationDateTime(GetLocalDateTime());
    note.SetModifiedDateTime(GetLocalDateTime());
    note.SetUniqueID(WString::FromLocal(RandomUID()));
    // Add popup to note annotation
    Popup popup(page.AddAnnot(Annot::e_Popup, RectF(300,450,500,550)));
    popup.SetBorderColor(0x00FF00);
    popup.SetOpenStatus(false);
    popup.SetModifiedDateTime(GetLocalDateTime());
    note.SetPopup(popup);

    // Add reply annotation to note annotation
    Note reply = note.AddReply();
    reply.SetContent(L"reply");
    reply.SetModifiedDateTime(GetLocalDateTime());
    reply.SetTitle(L"Foxit SDK");
    reply.SetUniqueID(WString::FromLocal(RandomUID()));

    // Add state annotation to note annotation
    Note state = note.AddStateAnnot(L"Foxit SDK", Markup::e_StateModelReview, Markup::e_StateAccepted);  
    state.SetContent(L"Accepted set by Foxit SDK");
    state.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    note.ResetAppearanceStream();
    cout << "Add a note annotation." << endl;
  }
  {
    // Add ink annotation
    annots::Ink ink(page.AddAnnot( Annot::e_Ink, RectF(100,350,200,450)));
    //This flag is used for printing annotations.
    ink.SetFlags(4);
    foxit::common::Path inklist;
    float width = 100;
    float height = 100;
    float out_width = min(width, height) * 2 / 3.f;
    float inner_width = out_width * sin(18.f / 180.f * 3.14f) / sin(36.f / 180.f * 3.14f);
    PointF center(150, 400);
    float x = out_width;
    float y = 0;
    inklist.MoveTo(PointF(center.x + x, center.y + y));
    for (int i = 0; i < 5; i++) {
      x = out_width * cos(72.f * i / 180.f * 3.14f);
      y = out_width * sin(72.f * i / 180.f * 3.14f);
      inklist.LineTo(PointF(center.x + x, center.y + y));

      x = inner_width * cos((72.f * i + 36) / 180.f * 3.14f);
      y = inner_width * sin((72.f * i + 36) / 180.f * 3.14f);
      inklist.LineTo(PointF(center.x + x, center.y + y));
    }
    inklist.LineTo(PointF(center.x + out_width, center.y + 0));
    inklist.CloseFigure();
    ink.SetInkList(inklist);
    ink.SetSubject(L"Ink");
    ink.SetTitle(L"Foxit SDK");
    ink.SetContent(L"Note annotation.");
    ink.SetCreationDateTime(GetLocalDateTime());
    ink.SetModifiedDateTime(GetLocalDateTime());
    ink.SetUniqueID(WString::FromLocal(RandomUID()));
    // Appearance should be reset.
    ink.ResetAppearanceStream();
    cout << "Add an ink annotation." << endl;
  }
  {
    // Add file attachment annotation
    WString pdf_file = input_path + L"AboutFoxit.pdf";
    annots::FileAttachment file_attachment(page.AddAnnot( Annot::e_FileAttachment, RectF(280,350,300,380)));
    //This flag is used for printing annotations.
    file_attachment.SetFlags(4);
    file_attachment.SetIconName("Graph");

    foxit::pdf::FileSpec file_spec = foxit::pdf::FileSpec(page.GetDocument());
    file_spec.SetFileName(L"attachment.pdf");
    file_spec.SetCreationDateTime(GetLocalDateTime());
    file_spec.SetDescription("The original file");
    file_spec.SetModifiedDateTime(GetLocalDateTime());
    file_spec.Embed(pdf_file);
    file_attachment.SetFileSpec(file_spec);
    file_attachment.SetSubject(L"File Attachment");
    file_attachment.SetTitle(L"Foxit SDK");
    // Appearance should be reset.
    file_attachment.ResetAppearanceStream();
    cout << "Add an attachment annotation." << endl;
  }
  {
    // Add link annotation
    annots::Link link(page.AddAnnot( Annot::e_Link, RectF(350,350,380,400)));
    //This flag is used for printing annotations.
    link.SetFlags(4);
    link.SetHighlightingMode(Annot::e_HighlightingPush);

    // Add action for link annotation
    using foxit::pdf::actions::Action;
    using foxit::pdf::actions::URIAction;
    URIAction action = (URIAction)Action::Create(page.GetDocument(), Action::e_TypeURI);
    action.SetTrackPositionFlag(true);
    action.SetURI("www.foxitsoftware.com");
    link.SetAction(action);
    // Appearance should be reset.
    link.ResetAppearanceStream();
    cout << "Add a link annotation." << endl;
  }
  {
    // Set icon provider for annotation to Foxit PDF SDK.
#if defined(_WIN32) || defined(_WIN64)
    IconProvider* icon_provider = IconProvider::Create("../input_files/Stamps");
#else
    IconProvider* icon_provider = IconProvider::Create("./input_files/Stamps");
#endif

    icon_provider->SetUseDynamicStamp(false);
    Library::SetAnnotIconProviderCallback(icon_provider);

    // Add common stamp annotation.
    Library::SetActionCallback(NULL);
    Stamp static_stamp(page.AddAnnot(Annot::e_Stamp, RectF(110,150,200,250)));
    //This flag is used for printing annotations.
    static_stamp.SetFlags(4);
    static_stamp.SetIconName("Approved");
    // Appearance should be reset.
    static_stamp.ResetAppearanceStream();

    // Add dynamic stamp annotation.
    Library::SetActionCallback(new ActionEvent(page.GetDocument()));
    icon_provider->SetUseDynamicStamp(true);
    Stamp dynamic_stamp(page.AddAnnot(Annot::e_Stamp, RectF(10,150,100,250)));
    //This flag is used for printing annotations.
    dynamic_stamp.SetFlags(4);
    dynamic_stamp.SetIconName("Approved");
    // Appearance should be reset.
    dynamic_stamp.ResetAppearanceStream();
    cout << "Add stamp annotations." << endl;

  }

  {
    // Add freetext annotation with richtext, as type writer.
    annots::FreeText freetext(page.AddAnnot(Annot::e_FreeText, RectF(10, 50, 200, 100)));
    //This flag is used for printing annotations.
    freetext.SetFlags(4);
    // Set default appearance
    foxit::pdf::DefaultAppearance default_ap;
    default_ap.flags = DefaultAppearance::e_FlagFont | DefaultAppearance::e_FlagFontSize | DefaultAppearance::e_FlagTextColor;
    default_ap.font = common::Font(common::Font::e_StdIDHelvetica);
    default_ap.text_size = 12.0f;
    default_ap.text_color = 0x000000;
    // Set default appearance for form.
    freetext.SetDefaultAppearance(default_ap);
    freetext.SetIntent("FreeTextTypewriter");
    freetext.SetContent(L"A typewriter annotation");
    freetext.SetSubject(L"FreeTextTypewriter");
    freetext.SetTitle(L"Foxit SDK");
    freetext.SetCreationDateTime(GetLocalDateTime());
    freetext.SetModifiedDateTime(GetLocalDateTime());
    freetext.SetUniqueID(WString::FromLocal(RandomUID()));
    RichTextStyle richtext_style;
#if defined(__linux__)
    richtext_style.font = Font(L"FreeSerif", 0, Font::e_CharsetANSI, 0);
#else
    richtext_style.font = Font(L"Times New Roman", 0, Font::e_CharsetANSI, 0);
#endif
    richtext_style.text_color = 0xFF0000;
    richtext_style.text_size = 10;
    freetext.AddRichText(L"Typewriter annotation ", richtext_style);

    richtext_style.text_color = 0x00FF00;
    richtext_style.is_underline = true;
    freetext.AddRichText(L"1-underline ", richtext_style);

#if defined(__linux__)
    richtext_style.font = Font(L"FreeSans", 0, Font::e_CharsetANSI, 0);
#else
    richtext_style.font = Font(L"Calibri", 0, Font::e_CharsetANSI, 0);
#endif
    richtext_style.text_color = 0x0000FF;
    richtext_style.is_underline = false;
    richtext_style.is_strikethrough = true;
    int richtext_count = freetext.GetRichTextCount();
    freetext.InsertRichText(richtext_count-1, L"2_strikethrough ", richtext_style);

    // Appearance should be reset.
    freetext.ResetAppearanceStream();
    cout << "Add a typewriter freetext annotation with richtext." << endl;
  }
  {
    // Add freetext annotation with richtext, as call-out.
    annots::FreeText freetext(page.AddAnnot(Annot::e_FreeText, RectF(300, 50, 400, 100)));
    //This flag is used for printing annotations.
    freetext.SetFlags(4);
    // Set default appearance
    foxit::pdf::DefaultAppearance default_ap;
    default_ap.flags = DefaultAppearance::e_FlagFont | DefaultAppearance::e_FlagFontSize | DefaultAppearance::e_FlagTextColor;
    default_ap.font = common::Font(common::Font::e_StdIDHelveticaB);
    default_ap.text_size = 12.0f;
    default_ap.text_color = 0x000000;
    // Set default appearance for form.
    freetext.SetDefaultAppearance(default_ap);
    freetext.SetIntent("FreeTextCallout");
    PointFArray callout_points;
    callout_points.Add(PointF(250, 60));
    callout_points.Add(PointF(280, 80));
    callout_points.Add(PointF(300, 80));

    freetext.SetCalloutLinePoints(callout_points);
    freetext.SetCalloutLineEndingStyle(annots::Markup::e_EndingStyleOpenArrow);
    freetext.SetContent(L"A callout annotation.");
    freetext.SetSubject(L"FreeTextCallout");
    freetext.SetTitle(L"Foxit SDK");
    freetext.SetCreationDateTime(GetLocalDateTime());
    freetext.SetModifiedDateTime(GetLocalDateTime());
    freetext.SetUniqueID(WString::FromLocal(RandomUID()));

    RichTextStyle richtext_style;
#if defined(__linux__)
    richtext_style.font = Font(L"FreeSerif", 0, Font::e_CharsetANSI, 0);
#else
    richtext_style.font = Font(L"Times New Roman", 0, Font::e_CharsetANSI, 0);
#endif
    richtext_style.text_color = 0xFF0000;
    richtext_style.text_size = 10;
    freetext.AddRichText(L"Callout annotation ", richtext_style);

    richtext_style.text_color = 0x00FF00;
    richtext_style.is_underline = true;
    freetext.AddRichText(L"1-underline ", richtext_style);

#if defined(__linux__)
    richtext_style.font = Font(L"FreeSans", 0, Font::e_CharsetANSI, 0);
#else
    richtext_style.font = Font(L"Calibri", 0, Font::e_CharsetANSI, 0);
#endif
    richtext_style.text_color = 0x0000FF;
    richtext_style.is_underline = false;
    richtext_style.is_strikethrough = true;
    int richtext_count = freetext.GetRichTextCount();
    freetext.InsertRichText(richtext_count - 1, L"2_strikethrough ", richtext_style);

    // Appearance should be reset.
    freetext.ResetAppearanceStream();
    cout << "Add a callout freetext annotation with richtext." << endl;
  }
  {
    // Add freetext annotation with richtext, as text box.
    annots::FreeText freetext(page.AddAnnot(Annot::e_FreeText, RectF(450, 50, 550, 100)));
    //This flag is used for printing annotations.
    freetext.SetFlags(4);
    // Set default appearance
    foxit::pdf::DefaultAppearance default_ap;
    default_ap.flags = DefaultAppearance::e_FlagFont | DefaultAppearance::e_FlagFontSize | DefaultAppearance::e_FlagTextColor;
    default_ap.font = common::Font(common::Font::e_StdIDHelveticaI);
    default_ap.text_size = 12.0f;
    default_ap.text_color = 0x000000;
    // Set default appearance for form.
    freetext.SetDefaultAppearance(default_ap);
    freetext.SetContent(L"A text box annotation.");
    freetext.SetSubject(L"Textbox");
    freetext.SetTitle(L"Foxit SDK");
    freetext.SetCreationDateTime(GetLocalDateTime());
    freetext.SetModifiedDateTime(GetLocalDateTime());
    freetext.SetUniqueID(WString::FromLocal(RandomUID()));

    RichTextStyle richtext_style;
#if defined(__linux__)
    richtext_style.font = Font(L"FreeSerif", 0, Font::e_CharsetANSI, 0);
#else
    richtext_style.font = Font(L"Times New Roman", 0, Font::e_CharsetANSI, 0);
#endif
    richtext_style.text_color = 0xFF0000;
    richtext_style.text_size = 10;
    freetext.AddRichText(L"Textbox annotation ", richtext_style);

    richtext_style.text_color = 0x00FF00;
    richtext_style.is_underline = true;
    freetext.AddRichText(L"1-underline ", richtext_style);

#if defined(__linux__)
    richtext_style.font = Font(L"FreeSans", 0, Font::e_CharsetANSI, 0);
#else
    richtext_style.font = Font(L"Calibri", 0, Font::e_CharsetANSI, 0);
#endif
    richtext_style.text_color = 0x0000FF;
    richtext_style.is_underline = false;
    richtext_style.is_strikethrough = true;
    int richtext_count = freetext.GetRichTextCount();
    freetext.InsertRichText(richtext_count - 1, L"2_strikethrough ", richtext_style);

    // Appearance should be reset.
    freetext.ResetAppearanceStream();
    cout << "Add a text box freetext annotation witch richtext." << endl;
  }

  {
    //Add screen annotation
    Image image = Image(input_path+ L"FoxitLogo.jpg");
    annots::Screen screen(page.AddAnnot(Annot::e_Screen, RectF(300, 150, 400, 200)));
    //This flag is used for printing annotations.
    screen.SetFlags(4);
    screen.SetTitle(L"Foxit SDK");
    screen.SetBorderColor(0x0000FF);
    screen.SetBorderInfo(BorderInfo(2, BorderInfo::e_Solid, 0, 0, FloatArray()));
    screen.SetImage(image, 0, true);

    // Prepare rendition action
    using foxit::pdf::actions::Action;
    using foxit::pdf::actions::RenditionAction;
    RenditionAction rendition_action = RenditionAction(Action::Create(page.GetDocument(), Action::e_TypeRendition));

    rendition_action.SetOperationType(RenditionAction::e_OpTypeAssociate);
    rendition_action.SetScreenAnnot(screen);

    // Prepare rendition
    Rendition rendition(page.GetDocument());

    rendition.SetRenditionName(L"screen for rendition");
    rendition.SetMediaClipName(L"ytb210-Mopa.mp4");
    rendition.SetPermission(Rendition::e_MediaPermTempAccess);
    FileSpec video_filespec(page.GetDocument());
    video_filespec.SetFileName(L"ytb210-Mopa.mp4");
    WString video_file_path = input_path + L"ytb210-Mopa.mp4";

    video_filespec.Embed(video_file_path);
    rendition.SetMediaClipFile(video_filespec);
    rendition.SetMediaClipContentType("video/mp4");

    rendition_action.InsertRendition(rendition);

    screen.SetAction(rendition_action);

    screen.ResetAppearanceStream();
    cout << "Add a screen annotation." << endl;
  }

}

void AddAnnotsWithLowLevelAPI(PDFPage& page) {
  {
    // Add line annotation
    objects::PDFDictionary* annot_dict = objects::PDFDictionary::Create();
    annot_dict->SetAtName("Type", "Annot");
    annot_dict->SetAtName("Subtype", "Line");
    annot_dict->SetAtName("IT", "LineArrow");
    annot_dict->SetAtInteger("F", 4);
    annot_dict->SetAtString("Contents", "A line arrow annotation.");
    annot_dict->SetAtString("T", "Foxit SDK");
    annot_dict->SetAtString("Subj", "Arrow");
    annot_dict->SetAtString("NM", WString::FromLocal(RandomUID()));
    annot_dict->SetAtDateTime("CreationDate", GetLocalDateTime());
    annot_dict->SetAtDateTime("M", GetLocalDateTime());
    annot_dict->SetAtRect("Rect", RectF(0, 650, 100, 750));
    objects::PDFArray* coords_array = objects::PDFArray::Create();
    coords_array->AddFloat(20);
    coords_array->AddFloat(670);
    coords_array->AddFloat(80);
    coords_array->AddFloat(730);
    annot_dict->SetAt("L", coords_array);
    objects::PDFArray* line_style = objects::PDFArray::Create();
    line_style->AddName("None");
    line_style->AddName("OpenArrow");
    annot_dict->SetAt("LE", line_style);
    objects::PDFDictionary* border_dict = objects::PDFDictionary::Create();
    border_dict->SetAtFloat("W", 2.0f);
    border_dict->SetAtName("S", "S");
    border_dict->SetAtName("Type", "Border");
    annot_dict->SetAt("BS", border_dict);
    objects::PDFArray* color_array = objects::PDFArray::Create();
    color_array->AddFloat(1);
    color_array->AddFloat(1);
    color_array->AddFloat(0);
    annot_dict->SetAt("C", color_array);
    annots::Annot annot = page.AddAnnot(annot_dict);
    annot.ResetAppearanceStream();
    cout << "Add a line annotation by lower level API." << endl;
  }

  {
    // Add line annotation with caption
    objects::PDFDictionary* annot_dict = objects::PDFDictionary::Create();
    annot_dict->SetAtName("Type", "Annot");
    annot_dict->SetAtName("Subtype", "Line");
    annot_dict->SetAtName("IT", "LineArrow");
    annot_dict->SetAtInteger("F", 4);
    annot_dict->SetAtString("Contents", "A common line.");
    annot_dict->SetAtString("T", "Foxit SDK");
    annot_dict->SetAtString("Subj", "Line");
    annot_dict->SetAtString("NM", WString::FromLocal(RandomUID()));
    annot_dict->SetAtDateTime("CreationDate", GetLocalDateTime());
    annot_dict->SetAtDateTime("M", GetLocalDateTime());
    annot_dict->SetAtRect("Rect", RectF(0, 650, 100, 750));
    annot_dict->SetAtBoolean("Cap", true);

    objects::PDFArray* caption_offset = objects::PDFArray::Create();
    caption_offset->AddFloat(0);
    caption_offset->AddFloat(5);
    annot_dict->SetAt("CO", caption_offset);
    objects::PDFArray* coords_array = objects::PDFArray::Create();
    coords_array->AddFloat(40);
    coords_array->AddFloat(670);
    coords_array->AddFloat(100);
    coords_array->AddFloat(730);
    annot_dict->SetAt("L", coords_array);
    objects::PDFArray* line_style = objects::PDFArray::Create();
    line_style->AddName("Square");
    line_style->AddName("OpenArrow");
    annot_dict->SetAt("LE", line_style);
    objects::PDFDictionary* border_dict = objects::PDFDictionary::Create();
    border_dict->SetAtFloat("W", 2.0f);
    border_dict->SetAtName("S", "S");
    border_dict->SetAtName("Type", "Border");
    annot_dict->SetAt("BS", border_dict);
    objects::PDFArray* color_array = objects::PDFArray::Create();
    color_array->AddFloat(0);
    color_array->AddFloat(1);
    color_array->AddFloat(0);
    annot_dict->SetAt("C", color_array);
    annots::Annot annot = page.AddAnnot(annot_dict);
    annot.ResetAppearanceStream();
    cout << "Add a line annotation with caption by lower level API." << endl;
  }

  {
    // Add circle annotation
    objects::PDFDictionary* annot_dict = objects::PDFDictionary::Create();
    annot_dict->SetAtName("Type", "Annot");
    annot_dict->SetAtName("Subtype", "Circle");
    annot_dict->SetAtInteger("F", 4);
    annot_dict->SetAtString("T", "Foxit SDK");
    annot_dict->SetAtString("Subj", "Circle");
    annot_dict->SetAtString("NM", WString::FromLocal(RandomUID()));
    annot_dict->SetAtDateTime("CreationDate", GetLocalDateTime());
    annot_dict->SetAtDateTime("M", GetLocalDateTime());
    annot_dict->SetAtRect("Rect", RectF(120, 650, 180, 750));

    objects::PDFDictionary* border_dict = objects::PDFDictionary::Create();
    border_dict->SetAtFloat("W", 2.0f);
    border_dict->SetAtName("S", "S");
    border_dict->SetAtName("Type", "Border");
    annot_dict->SetAt("BS", border_dict);
    objects::PDFArray* color_array = objects::PDFArray::Create();
    color_array->AddFloat(0);
    color_array->AddFloat(1);
    color_array->AddFloat(0);
    annot_dict->SetAt("C", color_array);
    annots::Annot annot = page.AddAnnot(annot_dict);
    annot.ResetAppearanceStream();
    cout << "Add a circle annotation by lower level API." << endl;
  }

  {
    // Add square annotation
    objects::PDFDictionary* annot_dict = objects::PDFDictionary::Create();
    annot_dict->SetAtName("Type", "Annot");
    annot_dict->SetAtName("Subtype", "Square");
    annot_dict->SetAtInteger("F", 4);
    annot_dict->SetAtString("T", "Foxit SDK");
    annot_dict->SetAtString("Subj", "Square");
    annot_dict->SetAtString("NM", WString::FromLocal(RandomUID()));
    annot_dict->SetAtDateTime("CreationDate", GetLocalDateTime());
    annot_dict->SetAtDateTime("M", GetLocalDateTime());
    annot_dict->SetAtRect("Rect", RectF(200, 650, 300, 750));

    objects::PDFDictionary* border_dict = objects::PDFDictionary::Create();
    border_dict->SetAtFloat("W", 2.0f);
    border_dict->SetAtName("S", "S");
    border_dict->SetAtName("Type", "Border");
    annot_dict->SetAt("BS", border_dict);
    objects::PDFArray* interior_color_array = objects::PDFArray::Create();
    interior_color_array->AddFloat(1);
    interior_color_array->AddFloat(1);
    interior_color_array->AddFloat(0);
    annot_dict->SetAt("IC", interior_color_array);
	  objects::PDFArray* color_array = objects::PDFArray::Create();
    color_array->AddFloat(0);
    color_array->AddFloat(1);
    color_array->AddFloat(0);
    annot_dict->SetAt("C", color_array);
    annots::Annot annot = page.AddAnnot(annot_dict);
    annot.ResetAppearanceStream();
    cout << "Add a square annotation by lower level API." << endl;
  }
}

void AddIntToByteArray(size_t value, unsigned char* dest_char_array) {
  unsigned char temp_array[4] = {
    (unsigned char)(value & 0xFF),
    (unsigned char)((value >> 8) & 0xFF),
    (unsigned char)((value >> 16) & 0xFF),
    (unsigned char)((value >> 24) & 0xFF)
  };
  memcpy(dest_char_array, temp_array, 4 * sizeof(unsigned char));
}

void AddShortToByteArray(short value, unsigned char* dest_char_array) {
  unsigned char temp_array[2] = {
    (unsigned char)(value & 0xFF),
    (unsigned char)((value >> 8) & 0xFF)
  };
  memcpy(dest_char_array, temp_array, 2 * sizeof(unsigned char));
}

void AddStringToByteArray(const char* str, unsigned char* dest_char_array) {
  memcpy(dest_char_array, str, strlen(str));
}

bool SaveSoundToFile(const Sound& sound, const wchar_t* file_path)
{
  if (sound.IsEmpty())
  {
    return false;
  }
#if defined(_WIN32) || defined(_WIN64) || defined(_WIN_STORE)
  FILE* file;
  _wfopen_s(&file, file_path, L"wb");

#else
  FILE* file = fopen(String::FromUnicode(file_path), "wb");
#endif
  if (file == NULL) return FALSE;

  objects::PDFStream* sound_stream = sound.GetSoundStream();
  size_t stream_size = static_cast<size_t>(sound_stream->GetDataSize(false));
  unsigned char* data = new unsigned char[stream_size];
  sound_stream->GetData(false, stream_size, (void*)data);
  int bit = sound.GetBits();
  size_t riff_size = stream_size + 36;

  //write file header:
  unsigned char wav_file_header[44];
  memset(wav_file_header, 0, 44);
  int i = 0;
  AddStringToByteArray("RIFF", &wav_file_header[i]);
  i += 4;

  AddIntToByteArray(riff_size, &wav_file_header[i]);
  i += 4;

  AddStringToByteArray("WAVEfmt ", &wav_file_header[i]);
  i += 8;

  size_t chunk_size = 16;
  AddIntToByteArray(chunk_size, &wav_file_header[i]);
  i += 4;

  short format = 1;
  AddShortToByteArray(format, &wav_file_header[i]);
  i += 2;

  int channel_count = sound.GetChannelCount();
  AddShortToByteArray((short)channel_count, &wav_file_header[i]);
  i += 2;

  int rate = (int)sound.GetSamplingRate();
  AddIntToByteArray((size_t)rate, &wav_file_header[i]);
  i += 4;

  int byte_per_sec = rate * channel_count * bit / 8;
  AddIntToByteArray((size_t)byte_per_sec, &wav_file_header[i]);
  i += 4;

  short block_align = (short)(bit * channel_count / 8);
  AddShortToByteArray(block_align, &wav_file_header[i]);
  i += 2;

  AddShortToByteArray((short)bit, &wav_file_header[i]);
  i += 2;

  AddStringToByteArray("data", &wav_file_header[i]);
  i += 4;

  AddIntToByteArray(stream_size, &wav_file_header[i]);
  fwrite(wav_file_header, 44, 1, file);

  //write file data:
  int encoding_format = sound.GetSampleEncodingFormat();
  switch (encoding_format)
  {
  case Sound::e_SampleEncodingFormatALaw:
    break;
  case Sound::e_SampleEncodingFormatMuLaw:
    break;
  case Sound::e_SampleEncodingFormatSigned:
  {
    unsigned char* buffer = new unsigned char[stream_size + 1];
    size_t j = 0, k = 0;
    for (size_t i = 0; i < stream_size; i += 2) {
      unsigned char low = data[j++];
      unsigned char high;
      if (j == stream_size) {
        high = 0;
      }
      else {
        high = data[j++];
      }
      buffer[k++] = high;
      buffer[k++] = low;
    }
    fwrite(buffer, sizeof(unsigned char), stream_size, file);
    delete buffer;
  }
  break;
  case Sound::e_SampleEncodingFormatRaw:
  default:
    fwrite(data, sizeof(unsigned char), stream_size, file);
    break;
  }

  delete data;
  fclose(file);
  return TRUE;
}

Annot GetAnnotWithType(PDFPage pdf_page, Annot::Type annot_type, const int annot_index_with_type, int& annot_index_with_all)
{
  if (pdf_page.IsEmpty() || annot_type < (Annot::Type) - 1) return Annot();

  Annot ret_annot;
  int annot_count = pdf_page.GetAnnotCount();
  int spec_annot_index = -1;
  for (int i = 0; i < annot_count; i++)
  {
    Annot annot_i = pdf_page.GetAnnot(i);
    int cmp_index = -1;

    if ((Annot::Type) - 1 == annot_type)
    {
      cmp_index = i;
    }
    else if (annot_i.GetType() == annot_type)
    {
      spec_annot_index++;
      cmp_index = spec_annot_index;
    }
    if (cmp_index == annot_index_with_type)
    {
      annot_index_with_all = i;
      ret_annot = annot_i;
      break;
    }
  }
  return ret_annot;
}

Sound GetSoundAnnot(WString input_pdf_path, int page_index)
{
  PDFDoc doc = PDFDoc(input_pdf_path);
  doc.Load();
  PDFPage pdf_page = doc.GetPage(page_index);
  if (pdf_page.IsEmpty())
  {
    return (Sound)NULL;
  }

  int annot_index_with_type = 0;
  int annot_index_with_all = 0;
  Annot annot = GetAnnotWithType(pdf_page, Annot::e_Sound, annot_index_with_type, annot_index_with_all);
  if (annot.IsEmpty())
  {
    return (Sound)NULL;
  }
  if (annot.GetType() != Annot::e_Sound)
  {
    return (Sound)NULL;
  }

  return (Sound)annot;
}


int main(int argc, char *argv[])
{
  int err_ret = 0;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    WString input_file = input_path + L"annotation_input.pdf";
    WString output_directory = output_path + L"annotation/";
#if defined(_WIN32) || defined(_WIN64)
    _mkdir(String::FromUnicode(output_directory));
#else
    mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

    // Load a document
    PDFDoc doc = PDFDoc(input_file);
    doc.Load();
    // Get first page with index 0
    PDFPage page = doc.GetPage(0);
    AddAnnotations(page);
    // Save PDF file
    WString newPdf = output_directory + L"annotation.pdf";
    doc.SaveAs(newPdf, PDFDoc::e_SaveFlagNoOriginal);
  }
  catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }

  try {
    WString input_file = input_path + L"annotation_input.pdf";
    WString output_directory = output_path + L"annotation/";
#if defined(_WIN32) || defined(_WIN64)
    _mkdir(String::FromUnicode(output_directory));
#else
    mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

    // Load a document
    PDFDoc doc = PDFDoc(input_file);
    doc.Load();
    // Get first page with index 0
    PDFPage page = doc.GetPage(0);
    AddAnnotsWithLowLevelAPI(page);
    // Save PDF file
    WString newPdf = output_directory + L"annotation_lower_level_API.pdf";
    doc.SaveAs(newPdf, PDFDoc::e_SaveFlagNoOriginal);
  }
  catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }

  catch (...)
  {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  //save sound to file:
  try
  {
    WString output_directory = output_path + L"annotation/";
#if defined(_WIN32) || defined(_WIN64)
    _mkdir(String::FromUnicode(output_directory));
#else
    mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
    WString output_sound_file = output_directory + L"sound.wav";
    WString input_sound_pdf_file = input_path + L"sound.pdf";
    Sound sound = GetSoundAnnot(input_sound_pdf_file, 0);
    if (SaveSoundToFile(sound, (FX_LPCWSTR)output_sound_file))
    {
      wcout << L"Save sound annotation to file, saved file path:" << output_sound_file << endl;
    }
  }
  catch (const Exception& e)
  {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }

  return err_ret;
}
