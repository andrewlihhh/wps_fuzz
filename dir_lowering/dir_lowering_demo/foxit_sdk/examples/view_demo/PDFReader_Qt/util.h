#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include "common/fs_basictypes.h"
#include "addon/xfa/fs_xfa.h"

#include "mainwindow.h"

QString GetErrorCodeMessage(foxit::ErrorCode error_code);

class MyXFAAppProviderCallback: public foxit::addon::xfa::AppProviderCallback {
 public:
    MyXFAAppProviderCallback(MainWindow* parent_window);
    virtual ~MyXFAAppProviderCallback() {}

    virtual void Release();
    virtual foxit::WString GetAppInfo(AppInfo app_info);
    virtual void Beep(BeepType type);
    virtual MsgBoxButtonID MsgBox(const wchar_t* message, const wchar_t* title = NULL, MsgBoxIconType icon_type = e_MsgBoxIconError, MsgBoxButtonType button_type = e_MsgBtnTypeOK);
    virtual foxit::WString Response(const wchar_t* question, const wchar_t* title, const wchar_t* default_answer = NULL, bool is_mask = true);
    virtual foxit::common::file::ReaderCallback* DownLoadUrl(const wchar_t* url);
    virtual foxit::WString PostRequestURL(const wchar_t* url, const wchar_t* data, const wchar_t* content_type, const wchar_t* encode, const wchar_t* header);
     virtual bool PutRequestURL(const wchar_t* url, const wchar_t* data, const wchar_t* encode);
    virtual foxit::WString LoadString(StringID string_id);
    virtual foxit::WStringArray ShowFileDialog(const wchar_t* string_title, const wchar_t* string_filter, bool is_openfile_dialog = true);

 private:
    MainWindow* parent_window_;
};

#endif // UTIL_H
