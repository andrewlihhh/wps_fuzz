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
 * @file fs_actioncallback.h
 * @brief Header file for action callback related definitions and classes.
 */

#ifndef FS_ACTIONCALLBACK_H_
#define FS_ACTIONCALLBACK_H_

#include "common/fs_common.h"
#include "pdf/fs_pdfdoc.h"

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
class MenuList;
class MenuItemEx;
/** This class represents an array of menu list objects. */
FSDK_DEFINE_ARRAY(MenuListArray, MenuList)
FSDK_DEFINE_ARRAY(MenuItemExArray, MenuItemEx)

/** This class represents menu list. */
class MenuList FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  MenuList() : level(0) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] level               Level of menu.
   * @param[in] name                Title of menu.
   * @param[in] sub_menu_list_array The sub menu list array.
   */
  MenuList(int level, const wchar_t* name, MenuListArray sub_menu_list_array) {
    this->level = level;
    if (name)
      this->name = name;
    this->sub_menu_list_array = sub_menu_list_array;
  }

  /**
   * @brief Constructor, with another menu list object.
   *
   * @param[in] menu_list Another menu list object.
   */
  MenuList(const MenuList& menu_list) {
    level = menu_list.level;
    name = menu_list.name;
    sub_menu_list_array = menu_list.sub_menu_list_array;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] menu_list Another menu list object.
   *
   * @return Reference to current object itself.
   */
  MenuList& operator = (const MenuList& menu_list) {
    this->level = menu_list.level;
    this->name = menu_list.name;
    this->sub_menu_list_array = menu_list.sub_menu_list_array;
    return *this;
  }

  /**
   * @brief Set values.
   *
   * @param[in] level  Level of menu.
   * @param[in] name   Title of menu.
   * @param[in] sub_menu_list_array The sub menu list array.
   *
   * @return None.
   */
  void Set(int level, const wchar_t* name, MenuListArray sub_menu_list_array) {
    this->level = level;
    if (name)
      this->name = name;
    this->sub_menu_list_array = sub_menu_list_array;
  }

  /**
   * @deprecated Current member variable has been deprecated since Foxit PDF SDK 8.3.
   *
   * @brief The level of menu.
   */
  int level;
  /** @brief The title of menu. */
  WString name;
  /** @brief The sub menu array. */
  MenuListArray sub_menu_list_array;
};

/** This class represents menu item. */
class MenuItemEx FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  MenuItemEx() {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] item_name            The menu item name, which is the string to appear on the menu item.
   * @param[in] return_name          A string to be returned when the menu item is selected.
   * @param[in] is_checked           A boolean value which indicates whether the menu item is to be marked as checked.
   * @param[in] is_enabled           A boolean value which indicates whether the menu item is to appear enabled or grayed out.
   * @param[in] sub_menu_item_array  The sub menu item array.
   */
  MenuItemEx(const wchar_t* item_name, const wchar_t* return_name, bool is_checked, bool is_enabled, MenuItemExArray sub_menu_item_array) {
    if (item_name)
      this->item_name = item_name;
    if (return_name)
      this->return_name = return_name;
    this->is_checked = is_checked;
    this->is_enabled = is_enabled;
    this->sub_menu_item_array = sub_menu_item_array;
  }

  /**
   * @brief Constructor, with another menu item object.
   *
   * @param[in] menu_item Another menu item object.
   */
  MenuItemEx(const MenuItemEx& menu_item) {
    item_name = menu_item.item_name;
    return_name = menu_item.return_name;
    is_checked = menu_item.is_checked;
    is_enabled = menu_item.is_enabled;
    sub_menu_item_array = menu_item.sub_menu_item_array;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] menu_item Another menu item object.
   *
   * @return Reference to current object itself.
   */
  MenuItemEx& operator = (const MenuItemEx& menu_item) {
    this->item_name = menu_item.item_name;
    this->return_name = menu_item.return_name;
    this->is_checked = menu_item.is_checked;
    this->is_enabled = menu_item.is_enabled;
    this->sub_menu_item_array = menu_item.sub_menu_item_array;
    return *this;
  }

  /**
   * @brief Set values.
   *
   * @param[in] item_name            The menu item name, which is the string to appear on the menu item.
   * @param[in] return_name          A string to be returned when the menu item is selected.
   * @param[in] is_checked           A boolean value which indicates whether the menu item is to be marked as checked.
   * @param[in] is_enabled           A boolean value which indicates whether the menu item is to appear enabled or grayed out.
   * @param[in] sub_menu_item_array  The sub menu item array.
   *
   * @return None.
   */
  void Set(const wchar_t* item_name, const wchar_t* return_name, bool is_checked, bool is_enabled, MenuItemExArray sub_menu_item_array) {
    if (item_name)
      this->item_name = item_name;
    if (return_name)
      this->return_name = return_name;
    this->is_checked = is_checked;
    this->is_enabled = is_enabled;
    this->sub_menu_item_array = sub_menu_item_array;
  }

  /** @brief The menu item name, which is the string to appear on the menu item. The value of "-" is reserved to draw a separator line in the menu. */
  WString item_name;

  /** @brief A string to be returned when the menu item is selected. The default is the value of item name. */
  WString return_name;

  /** 
   * @brief A boolean value which indicates whether the menu item is to be marked as checked. 
   *
   * @details <b>true</b> means that the menu item is to be marked as checked, 
   *          while <b>false</b> means that the menu item is not to be marked as checked.
   */
  bool is_checked;

  /**
   * @brief A boolean value which indicates whether the menu item is to appear enabled or grayed out. 
   *
   * @details <b>true</b> means that the menu item is to appear enabled, 
   *          while <b>false</b> means that the menu item is to appear grayed out.
   */
  bool is_enabled;

  /** @brief The sub menu item array. */
  MenuItemExArray sub_menu_item_array;
};

/**
 * This class represents identity properties of current user, and is used for callback function
 * @link ActionCallback::GetIdentityProperties @endlink.
 */
class IdentityProperties FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  IdentityProperties() {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] corporation  The corporation name.
   * @param[in] email        The email address.
   * @param[in] login_name   The login name. Usually, this is the name used to log in current operating system.
   * @param[in] name         The user name.
   * @param[in] first_name   The user first name.
   * @param[in] last_name    The user last name.
   * @param[in] title        The user title.
   * @param[in] department   The department name.
   */
  IdentityProperties(const wchar_t* corporation, const wchar_t* email, const wchar_t* login_name, const wchar_t* name, const wchar_t* first_name,
                     const wchar_t* last_name, const wchar_t* title, const wchar_t* department)
      : corporation(corporation)
      , email(email)
      , login_name(login_name)
      , name(name)
      , first_name(first_name)
      , last_name(last_name)
      , title(title)
      , department(department){}

  /**
   * @brief Constructor, with another identity properties object.
   *
   * @param[in] id_properities  Another identity properties object.
   */
  IdentityProperties(const IdentityProperties& id_properities)
      : corporation(id_properities.corporation)
      , email(id_properities.email)
      , login_name(id_properities.login_name)
      , name(id_properities.name)
      , first_name(id_properities.first_name)
      , last_name(id_properities.last_name)
      , title(id_properities.title)
      , department(id_properities.department) {}

  /**
   * @brief Set values.
   *
   * @param[in] corporation  The corporation name.
   * @param[in] email        The email address.
   * @param[in] login_name   The login name. Usually, this is the name used to log in current operating system.
   * @param[in] name         The user name.
   * @param[in] first_name   The user first name.
   * @param[in] last_name    The uesr last name.
   * @param[in] title        The user title.
   * @param[in] department   The department name.
   *
   * @return None.
   */
  void Set(const wchar_t* corporation, const wchar_t* email, const wchar_t* login_name, const wchar_t* name, const wchar_t* first_name,
    const wchar_t* last_name, const wchar_t* title, const wchar_t* department) {
    this->corporation = corporation;
    this->email = email;
    this->login_name = login_name;
    this->name = name;
    this->first_name = first_name;
    this->last_name = last_name;
    this->title = title;
    this->department = department;
  }

  /** @brief The corporation name. */
  WString corporation;
  /** @brief The email address. */
  WString email;
  /** @brief The login name. Usually, this is the name used to log in current operating system. */
  WString login_name;
  /** @brief The user name. */
  WString name;
  /** @brief The user first name. */
  WString first_name;
  /** @brief The user last name. */
  WString last_name;
  /** @brief The user title. */
  WString title;
  /** @brief The department name. */
  WString department;
};

/** This class represents button item. */
class ButtonItem FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  ButtonItem() {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] name     A unique language-independent identifier for the button.
   * @param[in] pos      The button number to place the added button in the toolbar.
   * @param[in] exec     The expression string to evaluate when the button is selected.
   * @param[in] enable   An expression string that determines whether to enable the toolbutton.
   * @param[in] marked   An expression string that determines whether the toolbutton is marked.
   * @param[in] tooltip  The text to display in the button help text when the mouse is over the toolbutton.
   * @param[in] label    A text label to be displayed on the button to the right of the icon.
   * @param[in] bitmap   A bitmap object of button.
   */
  ButtonItem(const wchar_t* name, int pos,const wchar_t* exec, const wchar_t* enable,
    const wchar_t* marked,  const wchar_t* tooltip,  const wchar_t* label, const common::Bitmap& bitmap)
    : name(name)
    , pos(pos)
    , exec(exec)
    , enable(enable)
    , marked(marked)
    , tooltip(tooltip)
    , label(label)
    , bitmap(bitmap){}

  /**
  * @brief Constructor, with another button item object.
  *
  * @param[in] button_item  Another button item object.
  */
  ButtonItem(const ButtonItem& button_item)
    : name(button_item.name)
    , pos(button_item.pos)
    , exec(button_item.exec)
    , enable(button_item.enable)
    , marked(button_item.marked)
    , tooltip(button_item.tooltip)
    , label(button_item.label)
    , bitmap(button_item.bitmap){}

  /**
  * @brief Set values.
  *
  * @param[in] name     A unique language-independent identifier for the button.
  * @param[in] pos      The button number to place the added button in the toolbar.
  * @param[in] exec     The expression string to evaluate when the button is selected.
  * @param[in] enable   An expression string that determines whether to enable the toolbutton.
  * @param[in] marked   An expression string that determines whether the toolbutton is marked.
  * @param[in] tooltip  The text to display in the button help text when the mouse is over the toolbutton.
  * @param[in] label    A text label to be displayed on the button to the right of the icon.
  * @param[in] bitmap   A bitmap object of button.
  *
  * @return None.
  */
  void Set(const wchar_t* name, int pos, const wchar_t* exec, const wchar_t* enable,
    const wchar_t* marked,  const wchar_t* tooltip,  const wchar_t* label, const common::Bitmap& bitmap) {
    this->name = name;
    this->pos = pos;
    this->exec = exec;
    this->enable = enable;
    this->marked = marked;
    this->tooltip = tooltip;
    this->label = label;
    this->bitmap = bitmap;
  }

  /** @brief A unique language-independent identifier for the button.*/
  WString name;
  /** @brief The button number to place the added button in the toolbar.*/
  int pos;
  /** @brief The expression string to evaluate when the button is selected.*/
  WString exec;
  /** @brief An expression string that determines whether to enable the toolbutton.*/
  WString enable;
  /** @brief An expression string that determines whether the toolbutton is marked.*/
  WString marked;
  /** @brief The text to display in the button help text when the mouse is over the toolbutton.*/
  WString tooltip;
  /** @brief A text label to be displayed on the button to the right of the icon. */
  WString label;
  /** @brief A bitmap object of button.*/
  common::Bitmap bitmap;
};

/** This class represents menu item config. */
class MenuItemConfig FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  MenuItemConfig() {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] name     The language-independent name of the menu item.
   * @param[in] user     The user string (language-dependent name) to display as the menu item name.
   * @param[in] parent   The name of the parent menu item. Its submenu will have the new menu item added to it.
   * @param[in] pos      The position within the submenu to locate the new menu item.
   * @param[in] pos_str  The string is a named item in the menu (a language-independent name of a menu item).
   * @param[in] exec     An expression string to evaluate when the menu item is selected by the user.
   * @param[in] enable   An expression string that is evaluated to determine whether to enable the menu item.
   * @param[in] marked   An expression string that determines whether the menu item has a check mark
   *                     next to it.
   */
  MenuItemConfig(const wchar_t* name, const wchar_t* user, const wchar_t* parent, int pos, const char* pos_str,
    const wchar_t* exec, const wchar_t* enable, const wchar_t* marked)
    : name(name)
    , user(user)
    , parent(parent)
    , pos(pos)
    , pos_str(pos_str)
    , exec(exec)
    , enable(enable)
    , marked(marked) {}

  /**
  * @brief Constructor, with another menu item config object.
  *
  * @param[in] menu_item_config  Another menu item config object.
  */
  MenuItemConfig(const MenuItemConfig& menu_item_config)
    : name(menu_item_config.name)
    , user(menu_item_config.user)
    , parent(menu_item_config.parent)
    , pos(menu_item_config.pos)
    , pos_str(menu_item_config.pos_str)
    , exec(menu_item_config.exec)
    , enable(menu_item_config.enable)
    , marked(menu_item_config.marked) {}

  /**
   * @brief Set values.
   *
   * @param[in] name     The language-independent name of the menu item.
   * @param[in] user     The user string (language-dependent name) to display as the menu item name.
   * @param[in] parent   The name of the parent menu item. Its submenu will have the new menu item added to it.
   * @param[in] pos      The position within the submenu to locate the new menu item.
   * @param[in] pos_str  The string is a named item in the menu (a language-independent name of a menu item). 
   * @param[in] exec     An expression string to evaluate when the menu item is selected by the user.
   * @param[in] enable   An expression string that is evaluated to determine whether to enable the menu item.
   * @param[in] marked   An expression string that determines whether the menu item has a check mark
   *                     next to it.
   *
   * @return None.
   */
  void Set(const wchar_t* name, const wchar_t* user, const wchar_t* parent, int pos, const char* pos_str,
    const wchar_t* exec, const wchar_t* enable, const wchar_t* marked) {
    this->name = name;
    this->user = user;
    this->parent = parent;
    this->pos = pos;
    this->pos_str = pos_str;
    this->exec = exec;
    this->enable = enable;
    this->marked = marked;
  }
  /** @brief The language-independent name of the menu item.*/
  WString name;
  /** @brief The user string (language-dependent name) to display as the menu item name. */
  WString user;
  /** @brief The name of the parent menu item. Its submenu will have the new menu item added to it.*/
  WString parent;
  /** @brief The position within the submenu to locate the new menu item. */
  int pos;
  /** @brief (Only used by @link ActionCallback::AddMenuItem) The string is a named item in the menu (a language-independent name of a menu item). */
  String pos_str;
  /** @brief (Only used by @link ActionCallback::AddMenuItem) An expression string to evaluate when the menu item is selected by the user. */
  WString exec;
  /** @brief (Only used by @link ActionCallback::AddMenuItem) An expression string that is evaluated to determine whether to enable the menu item. */
  WString enable;
  /** 
   * @brief (Only used by @link ActionCallback::AddMenuItem) An expression string that determines whether the menu item has a check mark
   *        next to it. The expression should set event.rc to false to uncheck the menu item and
   *        true to check it. The default is that the menu item is not marked.
   */
  WString marked;
};

class DialogDescriptionElement;
/** This class represents an array of dialog description element array.*/
FSDK_DEFINE_ARRAY(DialogDescriptionElementArray, DialogDescriptionElement)

/** This class represents a dialog box elements property specifies an object literal with the following set of properties. */
class DialogDescriptionElement FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  DialogDescriptionElement() {}

  /**
  * @brief Constructor, with parameters.
  *
  * @param[in] name            The displayed name of the dialog box element.
  * @param[in] item_id         An ItemID for this dialog box.
  * @param[in] type            The type of this dialog box element.
  * @param[in] next_tab        An ItemID for the dialog box item that should be first in the tab order.
  * @param[in] width           Specifies the width of the element in pixels.
  * @param[in] height          Specifies the height of the element in pixels.
  * @param[in] char_width      Specifies the width of the element in characters.
  * @param[in] char_height     Specifies the height of the element in characters.
  * @param[in] font            The font to use for this element.
  * @param[in] bold            Specify if the font is bold.
  * @param[in] italic          Specify if the font is italic.
  * @param[in] alignment       The alignment for this element.
  * @param[in] align_children  The alignment for all descendants.
  * @param[in] element_array   An array of object literals that describe the subelements of this dialog box element.
  */
  DialogDescriptionElement(const char* name, const char* item_id, const char* type, const char* next_tab, int width, int height, int char_width, int char_height,
     const char* font, bool bold, bool italic, const char* alignment, const char* align_children,  DialogDescriptionElementArray element_array)
    : name(name)
    , item_id(item_id)
    , type(type)
    , next_tab(next_tab)
    , width(width)
    , height(height)
    , char_width(char_width)
    , char_height(char_height)
    , font(font)
    , bold(bold)
    , italic(italic)
    , alignment(alignment)
    , align_children(align_children)
    , element_array(element_array) {}

  /**
  * @brief Constructor, with another dialog description element object.
  *
  * @param[in] dlg_des_element  Another dialog description element object.
  */
  DialogDescriptionElement(const DialogDescriptionElement& dlg_des_element)
    : name(dlg_des_element.name)
    , item_id(dlg_des_element.item_id)
    , type(dlg_des_element.type)
    , next_tab(dlg_des_element.next_tab)
    , width(dlg_des_element.width)
    , height(dlg_des_element.height)
    , char_width(dlg_des_element.char_width)
    , char_height(dlg_des_element.char_height)
    , font(dlg_des_element.font)
    , bold(dlg_des_element.bold)
    , italic(dlg_des_element.italic)
    , alignment(dlg_des_element.alignment)
    , align_children(dlg_des_element.align_children)
    , element_array(dlg_des_element.element_array) {}

  /**
  * @brief Assign operator.
  *
  * @param[in] dlg_des_element Another dialog description element object.
  *
  * @return Reference to current object itself.
  */
  DialogDescriptionElement& operator = (const DialogDescriptionElement& dlg_des_element) {
    this->name = dlg_des_element.name;
    this->item_id = dlg_des_element.item_id;
    this->type = dlg_des_element.type;
    this->next_tab = dlg_des_element.next_tab;
    this->width = dlg_des_element.width;
    this->height = dlg_des_element.height;
    this->char_width = dlg_des_element.char_width;
    this->char_height = dlg_des_element.char_height;
    this->font = dlg_des_element.font;
    this->bold = dlg_des_element.bold;
    this->italic = dlg_des_element.italic;
    this->alignment = dlg_des_element.alignment;
    this->align_children = dlg_des_element.align_children;
    this->element_array = dlg_des_element.element_array;
    return *this;
  }

  /**
   * @brief Set values.
   *
   * @param[in] name            The displayed name of the dialog box element.
   * @param[in] item_id         An ItemID for this dialog box.
   * @param[in] type            The type of this dialog box element.
   * @param[in] next_tab        An ItemID for the dialog box item that should be first in the tab order.
   * @param[in] width           Specifies the width of the element in pixels.
   * @param[in] height          Specifies the height of the element in pixels.
   * @param[in] char_width      Specifies the width of the element in characters.
   * @param[in] char_height     Specifies the height of the element in characters.
   * @param[in] font            The font to use for this element.
   * @param[in] bold            Specify if the font is bold.
   * @param[in] italic          Specify if the font is italic.
   * @param[in] alignment       The alignment for this element.
   * @param[in] align_children  The alignment for all descendants.
   * @param[in] element_array   An array of object literals that describe the subelements of this dialog box element.
   *
   * @return None.
   */
  void Set(const char* name, const char* item_id, const char* type, const char* next_tab, int width, int height, int char_width, int char_height,
     const char* font, bool bold, bool italic, const char* alignment, const char* align_children,  DialogDescriptionElementArray element_array) {
    this->name = name;
    this->item_id = item_id;
    this->type = type;
    this->next_tab = next_tab;
    this->width = width;
    this->height = height;
    this->char_width = char_width;
    this->char_height = char_height;
    this->font = font;
    this->bold = bold;
    this->italic = italic;
    this->alignment = alignment;
    this->align_children = align_children;
    this->element_array = element_array;
  }

  /** @brief The displayed name of the dialog box element.*/
  String name;
  /** @brief An ItemID for this dialog box.*/
  String item_id;
  /** @brief The type of this dialog box element.*/
  String type;
  /** @brief An ItemID for the next dialog box item in the tab order.*/
  String next_tab;
  /**
   * @brief Specifies the width of the element in pixels.
   *
   * @details If no width is specified, the combined width of the contents is used.
   */
  int width;

  /**
   * @brief Specifies the height of the element in pixels. 
   *
   * @details If no height is specified, the combined height of the contents is used.
   */
  int height;
  /**
   * @brief Specifies the width of the element in characters.
   *
   * @details  If no width is specified, the combined width of the contents is used.
   */
  int char_width;
  /**
   * @brief Specifies the height of the element in characters.
   *
   * @details  If no height is specified, the combined height of the contents is used.
   */
  int char_height;
  /**
   * @brief The font to use for this element.
   *
   * @details It will be one of the following strings:
   *          <ul>
   *          <li>"default" - Default font</li>
   *          <li>"dialog"  - Dialog box font</li>
   *          <li>"palette" - Palette (small) Font</li>
   *          </ul>
   */
  String font;
  /** @brief Specify if the font is bold.*/
  bool bold;
  /** @brief Specify if the font is italic.*/
  bool italic;
  /** @brief The alignment for this element. */
  String alignment;
  /** @brief The alignment for all descendants. */
  String align_children;
  /** @brief An array of object literals that describe the subelements of this dialog box element. */
  DialogDescriptionElementArray element_array;
};

/** This class represents dialog config. */
class DialogDescriptionConfig FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  DialogDescriptionConfig() {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] name            The title bar of the dialog box.
   * @param[in] first_tab       An ItemID for the dialog box item that should be first in the tab order.
   * @param[in] width           The width of the dialog box in pixels.
   * @param[in] height          The height of the dialog box in pixels.
   * @param[in] char_width      The width of the dialog box in characters.
   * @param[in] char_height     The height of the dialog box in characters.
   * @param[in] align_children  The alignment for all descendants.
   * @param[in] element_array   An array of dialog description element array object.
   */
  DialogDescriptionConfig(const char* name, const char* first_tab, int width, int height,
    int char_width, int char_height, const char* align_children,  DialogDescriptionElementArray element_array)
    : name(name)
    , first_tab(first_tab)
    , width(width)
    , height(height)
    , char_width(char_width)
    , char_height(char_height)
    , align_children(align_children)
    , element_array(element_array) {}

  /**
   * @brief Constructor, with another dialog description config object.
   *
   * @param[in] dlg_des_config  Another dialog description config object.
   */
  DialogDescriptionConfig(const DialogDescriptionConfig& dlg_des_config)
    : name(dlg_des_config.name)
    , first_tab(dlg_des_config.first_tab)
    , width(dlg_des_config.width)
    , height(dlg_des_config.height)
    , char_width(dlg_des_config.char_width)
    , char_height(dlg_des_config.char_height)
    , align_children(dlg_des_config.align_children)
    , element_array(dlg_des_config.element_array) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] dlg_des_config Another dialog description config object.
   *
   * @return Reference to current object itself.
   */
  DialogDescriptionConfig& operator = (const DialogDescriptionConfig& dlg_des_config) {
    this->name = dlg_des_config.name;
    this->first_tab = dlg_des_config.first_tab;
    this->width = dlg_des_config.width;
    this->height = dlg_des_config.height;
    this->char_width = dlg_des_config.char_width;
    this->char_height = dlg_des_config.char_height;
    this->align_children = dlg_des_config.align_children;
    this->element_array = dlg_des_config.element_array;
    return *this;
  }

  /**
   * @brief Set values.
   *
   * @param[in] name            The title bar of the dialog box.
   * @param[in] first_tab       An ItemID for the dialog box item that should be first in the tab order.
   * @param[in] width           The width of the dialog box in pixels.
   * @param[in] height          The height of the dialog box in pixels.
   * @param[in] char_width      The width of the dialog box in characters.
   * @param[in] char_height     The height of the dialog box in characters.
   * @param[in] align_children  The alignment for all descendants.
   * @param[in] element_array   An array of dialog description element array object.
   *
   * @return None.
   */
  void Set(const char* name, const char* first_tab, int width, int height, int char_width, int char_height,
    const char* align_children,  DialogDescriptionElementArray element_array) {
    this->name = name;
    this->first_tab = first_tab;
    this->width = width;
    this->height = height;
    this->char_width = char_width;
    this->char_height = char_height;
    this->align_children = align_children;
    this->element_array = element_array;
  }

  /** @brief The title bar of the dialog box.*/
  String name;

  /**
   * @brief An ItemID for the dialog box item that should be first in the tab order.
   *
   * @details If no width is specified, the combined width of the contents is used.
   */
  String first_tab;

  /**
   * @brief The width of the dialog box in pixels.
   *
   * @details If no width is specified, the combined width of the contents is used.
   */
  int width;

  /**
   * @brief The height of the dialog box in pixels.
   *
   * @details If no height is specified, the combined height of the contents is used.
   */
  int height;

  /**
   * @brief The width of the dialog box in characters.
   *
   * @details If no width is specified, the combined width of the contents is used.
   */
  int char_width;

  /**
   * @brief The height of the dialog box in characters.
   *
   * @details If no height is specified, the combined height of the contents is used.
   */
  int char_height;

  /** @brief The alignment for all descendants.*/
  String align_children;

  /** @brief An array of dialog description element array object.*/
  DialogDescriptionElementArray element_array;
};

/** This class represents SOAP authenticate. */
class SOAPAuthenticateInfo FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  SOAPAuthenticateInfo() {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] username              A string containing the user name to use for authentication.
   * @param[in] password              A string containing the password to use for authentication.
   * @param[in] is_use_platform_auth  A Boolean value indicating that platform authentication should be used.                                     
   */
  SOAPAuthenticateInfo(const wchar_t* username, const wchar_t* password, bool is_use_platform_auth)
      : username(username)
      , password(password)
      , is_use_platform_auth(is_use_platform_auth){}

  /**
   * @brief Constructor, with another SOAP authenticate object.
   *
   * @param[in] soap_authenticate  Another SOAP authenticate object.
   */
  SOAPAuthenticateInfo(const SOAPAuthenticateInfo& soap_authenticate)
      : username(soap_authenticate.username)
      , password(soap_authenticate.password)
      , is_use_platform_auth(soap_authenticate.is_use_platform_auth) {}

  /**
   * @brief Set values.
   *
   * @param[in] username              A string containing the user name to use for authentication.
   * @param[in] password              A string containing the password to use for authentication.
   * @param[in] is_use_platform_auth  A Boolean value indicating that platform authentication should be used.  
   *
   * @return None.
   */
  void Set(const wchar_t* username, const wchar_t* password, bool is_use_platform_auth) {
    this->username = username;
    this->password = password;
    this->is_use_platform_auth = is_use_platform_auth;
  }

  /** @brief A string containing the user name to use for authentication. */
  WString username;
  /** @brief A string containing the password to use for authentication. */
  WString password;
  /**
   * @brief A Boolean value indicating that platform authentication should be used.
   *
   * @details If <b>true</b>, <i>username</i> and <i>password</i> are ignored and the underlying platform
   *          networking code is used.This may cause an authentication UI to be shown
   *          to the user and/or the credentials of the currently logged in user to be used.
   *          The default is <b>false</b> and is only supported on the Windows platform.  
  */
  bool is_use_platform_auth;
};

/** This class represents SOAP request properties. */
class SOAPRequestProperties FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  SOAPRequestProperties() {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] request_url      The URL for a SOAP HTTP endpoint.
   * @param[in] request_content  An object that specifies the remote procedure name and parameters or the XML message to send.
   * @param[in] soap_action      The SOAP action is a URN written to an HTTP header used by firewalls and servers to filter SOAP requests.
   * @param[in] soap_namespace   A namespace for the message schema when the request does not use the SOAP Encoding.
   * @param[in] soap_version     The version of the SOAP protocol to use when generating the XML Message.
   * @param[in] content_type     Allows the HTTP content-type header to be specified. The default is to use the SOAP 
   *                             messaging HTTP content-type.
   * @param[in] is_encode        Encoded the request using the SOAP Encoding described in the SOAP Specification. 
   *                             Otherwise, the literal encoding is used.
   * @param[in] is_wiredump      Whether to output debug information for SOAP requests and responses, defaults to true.
   * @param[in] request_header   An object that specifies a SOAP header to be included with the request. The default is to 
   *                             send a request with only a SOAP Body
   * @param[in] authenticate     An object that specifies how to handle HTTP authentication or credentials to use for Web Service Security.
   */
  SOAPRequestProperties(const wchar_t* request_url, const char* request_content, const wchar_t* soap_action,
                        const wchar_t* soap_namespace, const wchar_t* soap_version, const wchar_t* content_type, bool is_encode,
                        bool is_wiredump, const char* request_header, const SOAPAuthenticateInfo& authenticate)
      : request_url(request_url)
      , request_content(request_content)
      , soap_action(soap_action)
      , soap_namespace(soap_namespace)
      , soap_version(soap_version)
      , content_type(content_type)
      , is_encode(is_encode)
      , is_wiredump(is_wiredump)
      , request_header(request_header) 
      , authenticate(authenticate) {}

  /**
   * @brief Constructor, with another SOAP request properties object.
   *
   * @param[in] request_properties  Another SOAP request properties object.
   */
  SOAPRequestProperties(const SOAPRequestProperties& request_properties)
      : request_url(request_properties.request_url)
      , request_content(request_properties.request_content)
      , soap_action(request_properties.soap_action)
      , soap_namespace(request_properties.soap_namespace)
      , soap_version(request_properties.soap_version)
      , content_type(request_properties.content_type)
      , is_encode(request_properties.is_encode)
      , is_wiredump(request_properties.is_wiredump) 
      , request_header(request_properties.request_header) 
      , authenticate(request_properties.authenticate) {}

  /**
   * @brief Set values.
   *
   * @param[in] request_url      The URL for a SOAP HTTP endpoint.
   * @param[in] request_content  An object that specifies the remote procedure name and parameters or the XML message
   * to send.
   * @param[in] soap_action      The SOAP action is a URN written to an HTTP header used by firewalls and servers
   *                             to filter SOAP requests.
   * @param[in] soap_namespace   A namespace for the message schema when the request does not use the SOAP Encoding.
   * @param[in] soap_version     The version of the SOAP protocol to use when generating the XML Message.
   * @param[in] content_type     Allows the HTTP content-type header to be specified. The default is to use the SOAP
   *                             messaging HTTP content-type.
   * @param[in] is_encode        Encoded the request using the SOAP Encoding described in the SOAP Specification.
   *                             Otherwise, the literal encoding is used.
   * @param[in] is_wiredump      Whether to output debug information for SOAP requests and responses, defaults to true.
   * @param[in] request_header   An object that specifies a SOAP header to be included with the request. The default is to 
   *                             send a request with only a SOAP Body
   * @param[in] authenticate     An object that specifies how to handle HTTP authentication or credentials to use for Web Service Security.
   *
   * @return None.
   */
  void Set(const wchar_t* request_url, const char* request_content, const wchar_t* soap_action, const wchar_t* soap_namespace,
           const wchar_t* soap_version, const wchar_t* content_type, bool is_encode, bool is_wiredump, const char* request_header,
           const SOAPAuthenticateInfo& authenticate) {
    this->request_url = request_url;
    this->request_content = request_content;
    this->soap_action = soap_action;
    this->soap_namespace = soap_namespace;
    this->soap_version = soap_version;
    this->content_type = content_type;
    this->is_encode = is_encode;
    this->is_wiredump = is_wiredump;
    this->request_header = request_header;
    this->authenticate = authenticate;
  }

  /** @brief The URL for a SOAP HTTP endpoint.*/
  WString request_url;
  /** @brief An object that specifies the remote procedure name and parameters or the XML message to send.*/
  String request_content;
  /** @brief The SOAP action is a URN written to an HTTP header used by firewalls and servers to filter SOAP requests.*/
  WString soap_action;
  /**
   * @brief A namespace for the message schema when the request does not use the SOAP Encoding.
   *
   * @details The default is to omit the schema declaration.
   *
   */
  WString soap_namespace;
  /** @brief The version of the SOAP protocol to use when generating the XML Message.*/
  WString soap_version;
  /** @brief Allows the HTTP content-type header to be specified. The default is to use the SOAP messaging HTTP content-type.*/
  WString content_type;
  /**
   * @brief Encoded the request using the SOAP Encoding described in the SOAP Specification.
   *        Otherwise, the literal encoding is used.
   */
  bool is_encode;
  /** @brief Whether to output debug information for SOAP requests and responses, defaults to true.*/
  bool is_wiredump;
  /**
   * @brief An object that specifies a SOAP header to be included with the request. The default
   *        is to send a request with only a SOAP Body
   */
  String request_header;
  /** @brief  An object that specifies how to handle HTTP authentication or credentials to use for Web Service Security.*/
  SOAPAuthenticateInfo authenticate;
};

/** This class represents SOAP response. */
class SOAPResponseInfo FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  SOAPResponseInfo() {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] response_header  Header of the SOAP response.
   * @param[in] response_body     Body of the SOAP response.
   * @param[in] network_error    Network error information of the SOAP response.
   * @param[in] status_code      Status code of the response.
   * 
   */
  SOAPResponseInfo(const wchar_t* response_header, const wchar_t* response_body, const wchar_t* network_error, uint32 status_code)
      : response_header(response_header)
      , response_body(response_body)
      , network_error(network_error) 
      , status_code(status_code) {}

  /**
   * @brief Constructor, with another SOAP response object.
   *
   * @param[in] soap_response  Another SOAP response object.
   */
  SOAPResponseInfo(const SOAPResponseInfo& soap_response)
      : response_header(soap_response.response_header)
      , response_body(soap_response.response_body)
      , network_error(soap_response.network_error) 
      , status_code(soap_response.status_code) {}

  /**
   * @brief Set values.
   *
   * @param[in] response_header  Header of the SOAP response.
   * @param[in] response_body    Body of the SOAP response.
   * @param[in] network_error    Network error information of the SOAP response.
   * @param[in] status_code      Status code of the response.
   *
   * @return None.
   */
  void Set(const wchar_t* response_header, const wchar_t* response_body, const wchar_t* network_error, uint32 status_code) {
    this->response_header = response_header;
    this->response_body = response_body;
    this->network_error = network_error;
    this->status_code = status_code;
  }

  /** @brief Header of the SOAP response. */
  WString response_header;
  /** @brief Body of the SOAP response. */
  WString response_body;
  /** @brief Network error information of the SOAP response. */
  WString network_error;
  /** @brief Status code of the response.*/
  uint32 status_code;
};

/** This class represents print parameters. */
class PrintParams FS_FINAL: public Object{
 public:
  /**
  * @brief Enumeration for the values used to set the contents of the print job.
  *
  * @details Values of this enumeration should be used alone.
  */
  typedef enum _PrintContent {
    /** @brief Print Content: print the document contents, not comments. */
    e_PrintContentDocument = 0,
    /** @brief Print Content: print the document contents and comments. */
    e_PrintContentDocAndAnnots = 1,
    /** @brief Print Content: print the contents of form fields only. Useful for printing onto pre-preprinted forms. */
    e_PrintContentFormFieldsOnly = 2
  } PrintContent;
  
  /**
   * @brief Enumeration for the values used to set the printing duplex mode.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _DuplexType {
    /** @brief Duplex type: prints on one side of the paper. */
    e_DuplexTypeSimplex = 0,
    /** @brief Duplex type: prints on both sides of the paper; the paper flips along the long edge. */
    e_DuplexTypeDuplexFlipLongEdge = 1,
      /** @brief Duplex type: prints on both sides of the paper; the paper flips along the short edge. */
    e_DuplexTypeDuplexFlipShortEdge = 2
  } DuplexType;
  
  /**
   * @brief Enumeration for the values used to determine the duplex printing mode when printing a booklet.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _BookletDuplexMode {
    /** @brief Booklet Duplex Mode: automatically prints both sides of the paper. */
    e_BookletDuplexModeBothSides = 0,
    /** @brief Booklet Duplex Mode: only prints all pages that appear on the front side of the paper. */
    e_BookletDuplexModeFrontSideOnly = 1,
    /** @brief Booklet Duplex Mode: only prints all pages that appear on the back side of the paper. */
    e_BookletDuplexModeBackSideOnly = 2
  } BookletDuplexMode;
  
  /**
   * @brief Enumeration for the values used to determine the duplex printing mode when printing a booklet.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _BookletBinding {
    /** @brief Booklet Binding: Left-side binding for Western-style left-to-right reading direction. The paper is folded on the short side. */
    e_BookletBindingRight = 0,
    /**
     * @brief Booklet Binding: Right-side binding for text with right-to-left reading direction or Japanese-style vertical writing.
     *        The paper is folded on the short side.
     */
    e_BookletBindingLeft = 1,
    /**
     * @brief Booklet Binding: Left-side binding for Western-style left-to-right reading direction. The paper is 
     *        folded on the long side producing long and narrow pages.
     */
    e_BookletBindingLeftTall = 2,
    /**
     * @brief Booklet Binding: Right-side binding for text with right-to-left reading direction or Japanese-style 
     *        vertical writing. The paper is folded on the long side producing long and narrow pages.
     */
    e_BookletBindingRightTall = 3
  } BookletBinding;
  
  /**
   * @brief Enumeration for the values used to determine how the multiple pages are laid out on the sheet.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PageOrder {
    /** @brief Page Order type: pages are placed from left to right, from top to bottom. */
    e_PageOrderHorizontal = 0,
    /** @brief Page Order type: pages are placed from right to left, from top to bottom. */
    e_PageOrderHorizontalReversed = 1,
    /** @brief Page Order type: pages are placed from top to bottom, from left to right. */
    e_PageOrderVertical = 2
  } PageOrder;
  
  /**
  * @brief Enumeration for the values used to determine how the multiple pages are laid out on the sheet.
  *
  * @details Values of this enumeration should be used alone.
  */
  typedef enum _PrintHandling {
    /** @brief Print Handling: No page scaling is applied. */
    e_PrintHandlingNone = 0,
    /** @brief Print Handling: Pages are enlarged or shrunk to fit the printe's paper. */
    e_PrintHandlingFitPaper = 1,
    /** @brief Print Handling: Small pages are printed small, and large pages are shrunk to fit on the printer's paper. */
    e_PrintHandlingReducePaper = 2,
    /** @brief Print Handling: Pages are rescaled to print multiple pages on each printer page. */
    e_PrintHandlingMultiplePages = 3,
    /**
     * @brief Print Handling: Small or normal pages are printed in the original size and large pages are
     *        printed on multiple sheets of paper.
     */
    e_PrintHandlingTileLargePages = 4,
    /** @brief Print Handling: Prints multiple pages on the same sheet of paper in the order required to read correctly when folded. */
    e_PrintHandlingBooklet = 5
  } PrintHandling;
  

  /** @brief Constructor. */
  PrintParams()
  : is_show_ui(false)
  , is_reverse(false)
  , is_print_as_image(false)
  , is_print_auto_center(false)
  , is_print_auto_rotate(false)
  , is_simulate_overprinting(false)
  , is_print_page_border(false)
  , page_range(common::Range()) 
  , print_content(PrintParams::e_PrintContentDocument)
  , printer_name(L"")
  , output_file_name(L"")
  , num_copies(0)
  , duplex_type(PrintParams::e_DuplexTypeSimplex)
  , is_tile_label(false)
  , tile_mark(false)
  , tile_overlap(0)
  , tile_scale(0)
  , handling(PrintParams::e_PrintHandlingNone)
  , binding(PrintParams::e_BookletBindingRight)
  , booklet_duplex_mode(PrintParams::e_BookletDuplexModeBothSides)
  , num_pages_h(0)
  , num_pages_v(0)
  , page_order(PrintParams::e_PageOrderHorizontal)
  {}

  /**
   * @brief Constructor, with another print parameters object.
   *
   * @param[in] print_params  Another print parameters object.
   */
  PrintParams(const PrintParams& print_params)
    : is_show_ui(print_params.is_show_ui)
    , is_reverse(print_params.is_reverse)
    , is_print_as_image(print_params.is_print_as_image)
    , is_print_auto_center(print_params.is_print_auto_center)
    , is_print_auto_rotate(print_params.is_print_auto_rotate)
    , is_simulate_overprinting(print_params.is_simulate_overprinting)
    , is_print_page_border(print_params.is_print_page_border)
    , page_range(print_params.page_range)
    , print_content(print_params.print_content)
    , printer_name(print_params.printer_name)
    , output_file_name(print_params.output_file_name)
    , num_copies(print_params.num_copies)
    , duplex_type(print_params.duplex_type)
    , is_tile_label(print_params.is_tile_label)
    , tile_mark(print_params.tile_mark)
    , tile_overlap(print_params.tile_overlap)
    , tile_scale(print_params.tile_scale)
    , handling(print_params.handling)
    , binding(print_params.binding)
    , booklet_duplex_mode(print_params.booklet_duplex_mode)
    , num_pages_h(print_params.num_pages_h)
    , num_pages_v(print_params.num_pages_v)
    , page_order(print_params.page_order) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] print_params Another print parameters object.
   *
   * @return Reference to current object itself.
   */
  PrintParams& operator=(const PrintParams& print_params) {
    this->is_show_ui = print_params.is_show_ui;
    this->is_reverse = print_params.is_reverse;
    this->is_print_as_image = print_params.is_print_as_image;
    this->is_print_auto_center = print_params.is_print_auto_center;
    this->is_print_auto_rotate = print_params.is_print_auto_rotate;
    this->is_simulate_overprinting = print_params.is_simulate_overprinting;
    this->is_print_page_border = print_params.is_print_page_border;
    this->page_range = print_params.page_range;
    this->print_content = print_params.print_content;
    this->printer_name = print_params.printer_name;
    this->output_file_name = print_params.output_file_name;
    this->num_copies = print_params.num_copies;
    this->duplex_type = print_params.duplex_type;
    this->is_tile_label = print_params.is_tile_label;
    this->tile_mark = print_params.tile_mark;
    this->tile_overlap = print_params.tile_overlap;
    this->tile_scale = print_params.tile_scale;
    this->handling = print_params.handling;
    this->binding = print_params.binding;
    this->booklet_duplex_mode = print_params.booklet_duplex_mode;
    this->num_pages_h = print_params.num_pages_h;
    this->num_pages_v = print_params.num_pages_v;
    this->page_order = print_params.page_order;
    return *this;
  }

  /**
   * @brief <b>true</b> means that a UI should be presented to the user
   *        to obtain printing information and confirm the action.
   */
  bool is_show_ui;
  /**
   * @brief <b>true</b> means that the printing order should be from parameter <i>end</i> to
   *        parameter <i>start</i>.
   */
  bool is_reverse;
  /** @brief <b>true</b> means that pages should be printed as image.*/
  bool is_print_as_image;
  /** @brief <b>true</b> means that each page is automatically centered relative to the paper.*/
  bool is_print_auto_center;
  /**
   * @brief <b>true</b> means that automatically rotates each page to match the page orientation
   *        to the available paper area during Multiple Pages Per Sheet printing. <b>false</b> means not.
   */
  bool is_print_auto_rotate;
  /** @brief <b>true</b> means to do overprint preview when printing. <b>false</b> means not.*/
  bool is_simulate_overprinting;
  /** @brief A boolean value that if true, draws and prints a page boundary around each of the pages during Multiple Pages Per Sheet printing. */
  bool is_print_page_border;
  /**
   * @brief A range object to specify the page range for printing.
   *        All the indexes represented in this range would start from 0 and
   *        less than page count of the specified document.
   */
  common::Range page_range;
  /** @brief Specif content for printing. Please refer to values starting from
   *         @link PrintParams::e_PrintContentDocument @endlink and this should
   *         be one of these values.
   */
  PrintContent print_content;
  /** @brief The default printer name for printing.*/
  WString printer_name;
  /** @brief The device-independent path for a file name to be used instead of sending the print job to the printer (Print to File).*/
  WString output_file_name;
  /** @brief The number of copies to be printed.*/
  int num_copies;
  /** @brief Sets the printing duplex mode to simplex, duplex long edge, or duplex short edge feed.
   *         Please refer to values starting from @link PrintParams::e_DuplexTypeSimplex @endlink
   *         and this should be one of these values.
   */
  DuplexType duplex_type;
  /** @brief Label each page of tiled output. Labeled pages indicate row and column, file name, and print date.*/
  bool is_tile_label;
  /** @brief <b>true</b> means to cut the page, and <b>false</b> means not.*/
  bool tile_mark;
  /** @brief The number of points that tiled pages have in common.*/
  float tile_overlap;
  /** @brief The amount that tiled pages are scaled.*/
  float tile_scale;
  /** @brief The print handling type.Please refer to values starting from @link PrintParams::e_PrintHandlingNone @endlink
   *         and this should be one of these values.
   */
  PrintHandling handling;
  /** @brief The value determines the paper binding direction and the page arrange order. Please refer to values starting
   *         from @link PrintParams::e_BookletBindingRight @endlink and this should be one of these values.
   */
  BookletBinding binding;
  /** 
   * @brief The value determines the duplex printing mode when printing a booklet.Please refer to values starting
   *       from @link PrintParams::e_BookletDuplexModeBothSides @endlink and this should be one of these values.
   */
  BookletDuplexMode booklet_duplex_mode;
  /** @brief The number of pages to lay out in the horizontal direction when printing Multiple Pages Per Sheet.*/
  int num_pages_h;
  /** @brief The number of pages to lay out in the vertical direction when printing Multiple Pages Per Sheet.*/
  int num_pages_v;
  /**
   * @brief The value determines how the multiple pages are laid out on the sheet. Please refer to values starting
   *        from @link PrintParams::e_PageOrderHorizontal @endlink and this should be one of these values.
   */
  PageOrder page_order;
};

/** This class represents floating imformation. */
class FloatingInfo FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for the window position used for media player.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _WindowPosition {
    /** @brief Window position: at the top left corner. */
    e_WindowPositionTopLeft = 0,
    /** @brief Window position: at the top center. */
    e_WindowPositionTopCenter = 1,
    /** @brief Window position: at the top right corner. */
    e_WindowPositionTopRight = 2,
    /** @brief Window position: at the center left. */
    e_WindowPositionCenterLeft = 3,
    /** @brief Window position: at the center. */
    e_WindowPositionCenter = 4,
    /** @brief Window position: at the center right. */
    e_WindowPositionCenterRight = 5,
    /** @brief Window position: at the bottom left corner. */
    e_WindowPositionBottomLeft = 6,
    /** @brief Window position: at the bottom center. */
    e_WindowPositionBottomCenter = 7,
    /** @brief Window position: at the bottom right corner. */
    e_WindowPositionBottomRight = 8
  } WindowPosition;
  
  /**
   * @brief Enumeration for the values used to set relative position of floating window.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _RelativeTarget {
    /** @brief Relative type: align the floating window relative to the document (page) window. */
    e_RelativeTargetPageWindow = 0,
    /** @brief Relative type: align the floating window relative to the application window. */
    e_RelativeTargetAppWindow = 1,
    /** @brief Relative type: align the floating window relative to the full virtual desktop. */
    e_RelativeTargetDesktop = 2,
    /** @brief Relative type: align the floating window relative to the (selected) monitor display screen. */
    e_RelativeTargetMonitor = 3
  } RelativeTarget;
  
  /**
   * @brief Enumeration for the resize type, which specifies whether a floating window may be resized by the user.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ResizeType {
    /** @brief Resize type: may not be resized. */
    e_ResizeTypeNo = 0,
    /** @brief Resize type: may be resized only if the aspect ratio is preserved. */
    e_ResizeTypeKeepRatio = 1,
    /** @brief Resize type: may be resized without preserving the aspect ratio. */
    e_ResizeTypeYes = 2
  } ResizeType;
  
  /**
   * @brief Enumeration for the action can be taken if the floating window is positioned totally or partially offscreen.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _OffScreenAction {
    /** @brief Off screen action: take no action. */
    e_OffScreenAllow = 0,
    /** @brief Off screen action: move or resize the window so that it is on-screen. */
    e_OffScreenForceOnScreen = 1,
    /** @brief Off screen action: cancel playing the media clip. */
    e_OffScreenCancel = 2
  } OffScreenAction;
  

  /** @brief Constructor. */
  FloatingInfo() {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] window_pos       Specify how the floating window is to be positioned relative to the window specified by the <i> relative_target </i>.
   * @param[in] relative_target  Specify the window to which the floating window is to be aligned.
   * @param[in] resize_type      Specify whether the floating window may be resized by the user.
   * @param[in] has_close        <b>true</b> means the floating window should have a close window control button, while <b>false</b> means not.
   * @param[in] has_title        <b>true</b> means a title should be displayed in the title bar, while <b>false</b> means not.
   * @param[in] title            This title to be displayed if <i> has_title </i> is true.
   * @param[in] off_screen       Specify what action should be taken if the floating window is positioned totally or partially offscreen.
   * @param[in] rect             A rectangle specifies the location and size of the floating window in device coordinate system.
   */
  FloatingInfo(WindowPosition window_pos, RelativeTarget relative_target, ResizeType resize_type,
    bool has_close, bool has_title, const wchar_t* title, OffScreenAction off_screen, const RectF& rect)
    : window_pos(window_pos)
    , relative_target(relative_target)
    , resize_type(resize_type)
    , has_close(has_close)
    , has_title(has_title)
    , title(title)
    , off_screen(off_screen)
    , rect(rect) {}

  /**
   * @brief Constructor, with another floating infomation object.
   *
   * @param[in] floating_info  Another floating infomation object.
   */
  FloatingInfo(const FloatingInfo& floating_info)
    : window_pos(floating_info.window_pos)
    , relative_target(floating_info.relative_target)
    , resize_type(floating_info.resize_type)
    , has_close(floating_info.has_close)
    , has_title(floating_info.has_title)
    , title(floating_info.title)
    , off_screen(floating_info.off_screen)
    , rect(floating_info.rect) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] floating_info Another floating infomation object.
   *
   * @return Reference to current object itself.
   */
  FloatingInfo& operator = (const FloatingInfo& floating_info) {
    this->window_pos = floating_info.window_pos;
    this->relative_target = floating_info.relative_target;
    this->resize_type = floating_info.resize_type;
    this->has_close = floating_info.has_close;
    this->has_title = floating_info.has_title;
    this->title = floating_info.title;
    this->off_screen = floating_info.off_screen;
    this->rect = floating_info.rect;
    return *this;
  }

  /**
   * @brief Set values.
   *
   * @param[in] window_pos       Specify how the floating window is to be positioned relative to the window specified by the <i> relative_target </i>.
   * @param[in] relative_target  Specify the window to which the floating window is to be aligned.
   * @param[in] resize_type      Specify whether the floating window may be resized by the user.
   * @param[in] has_close        <b>true</b> means the floating window should have a close window control button, while <b>false</b> means not.
   * @param[in] has_title        <b>true</b> means a title should be displayed in the title bar, while <b>false</b> means not.
   * @param[in] title            This title to be displayed if <i> has_title </i> is true.
   * @param[in] off_screen       Specify what action should be taken if the floating window is positioned totally or partially offscreen.
   * @param[in] rect             A rectangle specifies the location and size of the floating window in device coordinate system.
   *
   * @return None.
   */
  void Set(WindowPosition window_pos, RelativeTarget relative_target, ResizeType resize_type,
    bool has_close, bool has_title, const wchar_t* title, OffScreenAction off_screen, const RectF& rect) {
    this->window_pos = window_pos;
    this->relative_target = relative_target;
    this->resize_type = resize_type;
    this->has_close = has_close;
    this->has_title = has_title;
    this->title = title;
    this->off_screen = off_screen;
    this->rect = rect;
  }
  
  /**
   * @brief Specify how the floating window is to be positioned relative to the window specified by the <i> relative_target </i>.
   *        Please refer to values starting from @link FloatingInfo::e_WindowPositionTopLeft @endlink and this should be one of these values.
   */
  WindowPosition window_pos;

  /**
   * @brief Specify the target to which the floating window is to be aligned. Please refer to values starting from
   *         @link FloatingInfo::e_RelativeTargetPageWindow @endlink and this should be one of these values.
   */
  RelativeTarget relative_target;

  /** 
   * @brief Specify whether the floating window may be resized by the user. Please refer to values starting from
   *         @link FloatingInfo::e_ResizeTypeNo @endlink and this should be one of these values.
   */
  ResizeType resize_type;

  /** @brief <b>true</b> means the floating window should have a close window control button, while <b>false</b> means not. */
  bool has_close;

  /** @brief <b>true</b> means a title should be displayed in the title bar, while <b>false</b> means not. */
  bool has_title;

  /** @brief This title to be displayed if <i> has_title </i> is true.*/
  WString title;

  /**
   * @brief Specify what action should be taken if the floating window is positioned totally or partially offscreen.
   *         Please refer to values starting from @link FloatingInfo::e_OffScreenAllow @endlink and this should be one of these values.
   */
  OffScreenAction off_screen;

  /** @brief A rectangle specifies the location and size of the floating window in device coordinate system. */
  RectF rect;
};

/** This class represents media settings. */
class MediaSettings FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for the type of window that the media should play in.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PlayerWindowType {
    /** @brief Window type: a docked page window. */
    e_PlayerWindowTypeDockedPage = 1,
    /** @brief Window type: a floating window. */
    e_PlayerWindowTypeFloating = 2,
    /** @brief Window type: a full-screen window that obscures all other windows. */
    e_PlayerWindowTypeFullScreen = 4
  } PlayerWindowType;
  

  /** @brief Constructor. */
  MediaSettings(){}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] auto_play          Specify whether the media clip should begin playing automatically after the player is opened.
   * @param[in] base_url           The base URL to be used to resolve any relative URLs used in the media clip.
   * @param[in] bg_color           The background color for the media player window.
   * @param[in] bg_opacity         The background opacity for the media player window.
   * @param[in] duration           The amount of time in seconds that playback will take.
   * @param[in] page               The number of the page on which the player should be docked.
   * @param[in] repeat             The number of times the media playback should automatically repeat.
   * @param[in] show_ui            A boolean value that specifies whether the controls of the media player should be visible or not.
   * @param[in] is_visible         A boolean value that specifies whether the player should be visible.
   * @param[in] volume             Specify the playback volume. A value of 0 is muted, a value of 100 is normal (full) volume.
   * @param[in] window_type        That defines which type of window the media player should be created in.
   * @param[in] floating_wnd_info  A @link FloatingInfo @endlink object containing properties (listed below) that define the location and style of a floating window.
   */
  MediaSettings(bool auto_play, const wchar_t* base_url, foxit::RGB bg_color, float bg_opacity,
    int duration, int page, int repeat, bool show_ui, bool is_visible, int volume,
    PlayerWindowType window_type,const FloatingInfo& floating_wnd_info)
    : auto_play(auto_play)
    , base_url(base_url)
    , bg_color(bg_color)
    , bg_opacity(bg_opacity)
    , duration(duration)
    , page(page)
    , repeat(repeat)
    , show_ui(show_ui)
    , is_visible(is_visible)
    , volume(volume)
    , window_type(window_type)
    , floating_wnd_info(floating_wnd_info) {}

  /**
   * @brief Constructor, with another media settings object.
   *
   * @param[in] media_settings  Another media settings object.
   */
  MediaSettings(const MediaSettings& media_settings)
    : auto_play(media_settings.auto_play)
    , base_url(media_settings.base_url)
    , bg_color(media_settings.bg_color)
    , bg_opacity(media_settings.bg_opacity)
    , duration(media_settings.duration)
    , page(media_settings.page)
    , repeat(media_settings.repeat)
    , show_ui(media_settings.show_ui)
    , is_visible(media_settings.is_visible)
    , volume(media_settings.volume)
    , window_type(media_settings.window_type)
    , floating_wnd_info(media_settings.floating_wnd_info) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] media_settings Another media settings object.
   *
   * @return Reference to current object itself.
   */
  MediaSettings& operator = (const MediaSettings& media_settings) {
    this->auto_play = media_settings.auto_play;
    this->base_url = media_settings.base_url;
    this->bg_color = media_settings.bg_color;
    this->bg_opacity = media_settings.bg_opacity;
    this->duration = media_settings.duration;
    this->page = media_settings.page;
    this->repeat = media_settings.repeat;
    this->show_ui = media_settings.show_ui;
    this->is_visible = media_settings.is_visible;
    this->volume = media_settings.volume;
    this->window_type = media_settings.window_type;
    this->floating_wnd_info = media_settings.floating_wnd_info;
    return *this;
  }

  /**
   * @brief Set values.
   *
   * @param[in] auto_play          Specify whether the media clip should begin playing automatically after the player is opened.
   * @param[in] base_url           The base URL to be used to resolve any relative URLs used in the media clip.
   * @param[in] bg_color           The background color for the media player window.
   * @param[in] bg_opacity         The background opacity for the media player window.
   * @param[in] duration           The amount of time in seconds that playback will take.
   * @param[in] page               The number of the page on which the player should be docked.
   * @param[in] repeat             The number of times the media playback should automatically repeat.
   * @param[in] show_ui            A boolean value that specifies whether the controls of the media player should be visible or not.
   * @param[in] is_visible         A boolean value that specifies whether the player should be visible.
   * @param[in] volume             Specify the playback volume. A value of 0 is muted, a value of 100 is normal (full) volume.
   * @param[in] window_type        That defines which type of window the media player should be created in.
   * @param[in] floating_wnd_info  A @link FloatingInfo @endlink object containing properties (listed below) that define the location and style of a floating window.
   *
   * @return None.
   */
  void Set(bool auto_play, const wchar_t* base_url, foxit::RGB bg_color, float bg_opacity,
    int duration, int page, int repeat, bool show_ui, bool is_visible, int volume,
    PlayerWindowType window_type, const FloatingInfo& floating_wnd_info) {
    this->auto_play = auto_play;
    this->base_url = base_url;
    this->bg_color = bg_color;
    this->bg_opacity = bg_opacity;
    this->duration = duration;
    this->page = page;
    this->repeat = repeat;
    this->show_ui = show_ui;
    this->is_visible = is_visible;
    this->volume = volume;
    this->window_type = window_type;
    this->floating_wnd_info = floating_wnd_info;
  }

  /**
   * @brief Specify whether the media clip should begin playing automatically after the player is opened.
   *
   * @details <b>true</b> means auto play, while <b>false</b> means not.
   */
  bool auto_play;

  /**
   * @brief The base URL to be used to resolve any relative URLs used in the media clip.
   *
   * @details For example, if the media opens a web page. There is no default value; if this is not specified,
   *          the interpretation of a relative URL will vary depending the media player, but in most cases will not work.
   */
  WString base_url;

  /** @brief The background color for the media player window. Format: 0xRRGGBB */
  foxit::RGB bg_color;

  /** @brief The background opacity for the media player window. */
  float bg_opacity;

  /** @brief The amount of time in seconds that playback will take. */
  int duration;

  /**
   * @brief For a docked media player, this property is the number of the page on which the player should be docked.
   *        For other types of media players, this property is ignored.
   */
  int page;

  /**
   * @brief The number of times the media playback should automatically repeat.
   *
   * @details The default value of 1 causes the media to be played once.
   */
  int repeat;

  /** @brief A boolean value that specifies whether the controls of the media player should be visible or not. */
  bool show_ui;

  /** @brief A boolean value that specifies whether the player should be visible. */
  bool is_visible;

  /** @brief Specify the playback volume. A value of 0 is muted, a value of 100 is normal (full) volume. */
  int volume;

  /**
   * @brief That defines which type of window the media player should be created in. Please refer to values starting from
   *         @link MediaSettings::e_PlayerWindowTypeDockedPage @endlink and this should be one of these values.
   */
  PlayerWindowType window_type;

  /** @brief A @link FloatingInfo @endlink containing properties (listed below) that define the location and style of a floating window. */
  FloatingInfo floating_wnd_info;

};

/** This class represents player args. */
class PlayerArgs FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  PlayerArgs() {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] doc              The @link PDFDoc @endlink object of the document. Required if both annot and rendition are omitted, for example, for URL playback.
   * @param[in] screen_annot     A @link pdf::annots::Screen @endlink object. Required for docked playback unless it is found in the event object or MediaSettings.
   * @param[in] rendition        A pdf::Rendition object (either a MediaRendition or a RenditionList). Required unless rendition is found in the event object or URL is present.
   * @param[in] URL              Either URL or rendition is required, with URL taking precedence.
   * @param[in] audio_format     The audio format, such as "audio/wav".
   * @param[in] player_settings  A @link MediaSettings @endlink object.
   */
  PlayerArgs(const pdf::PDFDoc& doc, const pdf::annots::Screen& screen_annot, const pdf::Rendition& rendition, const wchar_t* URL,
    const wchar_t* audio_format, const MediaSettings& player_settings)
    : doc(doc)
    , screen_annot(screen_annot)
    , rendition(rendition)
    , URL(URL)
    , audio_format(audio_format)
    , player_settings(player_settings) {}

  /**
   * @brief Constructor, with another player args object.
   *
   * @param[in] player_args  Another player args object.
   */
  PlayerArgs(const PlayerArgs& player_args)
    : doc(player_args.doc)
    , screen_annot(player_args.screen_annot)
    , rendition(player_args.rendition)
    , URL(player_args.URL)
    , audio_format(player_args.audio_format)
    , player_settings(player_args.player_settings) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] player_args Another player args object.
   *
   * @return Reference to current object itself.
   */
  PlayerArgs& operator = (const PlayerArgs& player_args) {
    this->doc = player_args.doc;
    this->screen_annot = player_args.screen_annot;
    this->rendition = player_args.rendition;
    this->URL = player_args.URL;
    this->audio_format = player_args.audio_format;
    this->player_settings = player_args.player_settings;
    return *this;
  }

  /**
   * @brief Set values.
   *
   * @param[in] doc              The @link PDFDoc @endlink object of the document. Required if both annot and rendition are omitted, for example, for URL playback.
   * @param[in] screen_annot     A @link pdf::annots::Screen @endlink object. Required for docked playback unless it is found in the event object or MediaSettings.
   * @param[in] rendition        A @link pdf::Rendition @endlink object (either a MediaRendition or a RenditionList). Required unless rendition is found in the event object or URL is present.
   * @param[in] URL              Either URL or rendition is required, with URL taking precedence.
   * @param[in] audio_format     The audio format, such as "audio/wav".
   * @param[in] player_settings  A @link MediaSettings @endlink object.
   *
   * @return None.
   */
  void Set(const pdf::PDFDoc& doc, const pdf::annots::Screen& screen_annot, const pdf::Rendition& rendition, const wchar_t* URL,
    const wchar_t* audio_format, const MediaSettings& player_settings) {
    this->doc = doc;
    this->screen_annot = screen_annot;
    this->rendition = rendition;
    this->URL = URL;
    this->audio_format = audio_format;
    this->player_settings = player_settings;
  }

  /** 
   * @brief  The @link PDFDoc @endlink object of the document.
   * 
   * @details Required if both annot and rendition are omitted, for example, for URL playback.
   */
  pdf::PDFDoc doc;

  /**
   * @brief A @link pdf::annots::Screen @endlink object.
   *
   * @details Required for docked playback unless it is found in the "event" or "MediaSettings" of javascript.
   */
  pdf::annots::Screen screen_annot;

  /**
   * @brief A @link pdf::Rendition @endlink object (either a MediaRendition or a RenditionList).
   *
   * @details Required unless rendition is found in the event object or URL is present.
   */
  pdf::Rendition rendition;

  /** @brief Either URL or rendition is required, with URL taking precedence.*/
  WString URL;

  /** @brief The audio format, such as "audio/wav". */
  WString audio_format;

  /** @brief A @link MediaSettings @endlink object. */
  MediaSettings player_settings;
};

/** This class represents search option. */
class SearchOption FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for word matching.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _WordMatching {
    /** @brief Word matching: match phrase. */
    e_WordMatchingMatchPhrase = 0,
    /** @brief Word matching: match all words. */
    e_WordMatchingMatchAllWords = 1,
    /** @brief Word matching: match any word. */
    e_WordMatchingMatchAnyWord = 2
  } WordMatching;
  

  /** @brief Constructor. */
  SearchOption() {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] is_whole_word             Specifies whether search finds only occurrences of complete words that are specified in the query.
   * @param[in] is_case_sensitive         Specifies whether the search query is case sensitive.
   * @param[in] is_search_bookmarks       Specifies whether bookmarks are searched for the query.
   * @param[in] is_search_in_markup       Specifies whether markup (annotations) are searched for the query.
   * @param[in] is_search_in_attachments  Specifies whether any PDF file attachments should be searched along with the base document.
   * @param[in] is_ignore_accents         Specifies whether accents and diacriticals are ignored while searching the query term.
   * @param[in] is_proximity              Specifies whether the search query will reflect the proximity of words in the results ranking when performing the
   *                                      search that contains AND Boolean clauses.
   * @param[in] is_stemming               Specifies whether the search query will take the stemming of words (for example, run, runs, running) into account when
   *                                      performing the search.
   * @param[in] is_ignore_full_width      Specifies whether full width and half width characters in the document exactly match the search query. 
   * @param[in] max_docs                  The maximum number of documents that will be returned as part of the search query.
   * @param[in] word_matching             How individual words in the query will be matched to words in the document.
   * @param[in] is_search_doc_text        Specifies whether the document text is searched for the query.
   */
  SearchOption(bool is_whole_word, bool is_case_sensitive, bool is_search_bookmarks, bool is_search_in_marup,
    bool is_search_in_attachments, bool is_ignore_accents, bool is_proximity, bool is_stemming, bool is_ignore_full_width,
    int max_docs, WordMatching word_matching, bool is_search_doc_text)
    : is_whole_word(is_whole_word)
    , is_case_sensitive(is_case_sensitive)
    , is_search_bookmarks(is_search_bookmarks)
    , is_search_in_markup(is_search_in_marup)
    , is_search_in_attachments(is_search_in_attachments)
    , is_ignore_accents(is_ignore_accents)
    , is_proximity(is_proximity)
    , is_stemming(is_stemming)
    , is_ignore_full_width(is_ignore_full_width)
    , max_docs(max_docs)
    , word_matching(word_matching)
    , is_search_doc_text(is_search_doc_text) {}

  /**
   * @brief Constructor, with another search option object.
   *
   * @param[in] search_option  Another search option object.
   */
  SearchOption(const SearchOption& search_option)
    : is_whole_word(search_option.is_whole_word)
    , is_case_sensitive(search_option.is_case_sensitive)
    , is_search_bookmarks(search_option.is_search_bookmarks)
    , is_search_in_markup(search_option.is_search_in_markup)
    , is_search_in_attachments(search_option.is_search_in_attachments)
    , is_ignore_accents(search_option.is_ignore_accents)
    , is_proximity(search_option.is_proximity)
    , is_stemming(search_option.is_stemming)
    , is_ignore_full_width(search_option.is_ignore_full_width)
    , max_docs(search_option.max_docs)
    , word_matching(search_option.word_matching)
    , is_search_doc_text(search_option.is_search_doc_text) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] search_option Another search option object.
   *
   * @return Reference to current object itself.
   */
  SearchOption& operator = (const SearchOption& search_option) {
    this->is_whole_word = search_option.is_whole_word;
    this->is_case_sensitive = search_option.is_case_sensitive;
    this->is_search_bookmarks = search_option.is_search_bookmarks;
    this->is_search_in_markup = search_option.is_search_in_markup;
    this->is_search_in_attachments = search_option.is_search_in_attachments;
    this->is_ignore_accents = search_option.is_ignore_accents;
    this->is_proximity = search_option.is_proximity;
    this->is_stemming = search_option.is_stemming;
    this->is_ignore_full_width = search_option.is_ignore_full_width;
    this->max_docs = search_option.max_docs;
    this->word_matching = search_option.word_matching;
    this->is_search_doc_text = search_option.is_search_doc_text;
    return *this;
  }

  /**
   * @brief Set values.
   *
   * @param[in] is_whole_word             Specifies whether search finds only occurrences of complete words that are specified in the query.
   * @param[in] is_case_sensitive         Specifies whether the search query is case sensitive.
   * @param[in] is_search_bookmarks       Specifies whether bookmarks are searched for the query.
   * @param[in] is_search_in_markup       Specifies whether markup (annotations) are searched for the query.
   * @param[in] is_search_in_attachments  Specifies whether any PDF file attachments should be searched along with the base document.
   * @param[in] is_ignore_accents         Specifies whether accents and diacriticals are ignored while searching the query term.
   * @param[in] is_proximity              Specifies whether the search query will reflect the proximity of words in the results ranking when performing the
   *                                      search that contains AND Boolean clauses.
   * @param[in] is_stemming               Specifies whether the search query will take the stemming of words (for example, run, runs, running) into account when
   *                                      performing the search.
   * @param[in] is_ignore_full_width      Specifies whether full width and half width characters in the document exactly match the search query. 
   * @param[in] max_docs                  The maximum number of documents that will be returned as part of the search query.
   * @param[in] word_matching             How individual words in the query will be matched to words in the document.
   * @param[in] is_search_doc_text        Specifies whether the document text is searched for the query.
   *
   * @return None.
   */
  void Set(bool is_whole_word, bool is_case_sensitive, bool is_search_bookmarks, bool is_search_in_marup,
    bool is_search_in_attachments, bool is_ignore_accents, bool is_proximity, bool is_stemming, bool is_ignore_full_width,
    int max_docs, WordMatching word_matching, bool is_search_doc_text) {
    this->is_whole_word = is_whole_word;
    this->is_case_sensitive = is_case_sensitive;
    this->is_search_bookmarks = is_search_bookmarks;
    this->is_search_in_markup = is_search_in_marup;
    this->is_search_in_attachments = is_search_in_attachments;
    this->is_ignore_accents = is_ignore_accents;
    this->is_proximity = is_proximity;
    this->is_stemming = is_stemming;
    this->is_ignore_full_width = is_ignore_full_width;
    this->max_docs = max_docs;
    this->word_matching = word_matching;
    this->is_search_doc_text = is_search_doc_text;
  }

  /** @brief Specifies whether search finds only occurrences of complete words that are specified in the query. Defaule value: <b>false</b>.*/
  bool is_whole_word;
  /** @brief Specifies whether the search query is case sensitive. Defaule value: <b>false</b>.*/
  bool is_case_sensitive;
  /** @brief Specifies whether bookmarks are searched for the query. Defaule value: <b>false</b>.*/
  bool is_search_bookmarks;
  /** @brief Specifies whether markup (annotations) are searched for the query. Defaule value: <b>false</b>.*/
  bool is_search_in_markup;
  /** @brief Specifies whether any PDF file attachments should be searched along with the base document. Defaule value: <b>false</b>.*/
  bool is_search_in_attachments;
  /** @brief Specifies whether accents and diacriticals are ignored while searching the query term. Defaule value: <b>false</b>.*/
  bool is_ignore_accents;
  /**
   * @brief Specifies whether the search query will reflect the proximity of words in the results ranking when performing the
   *        search that contains AND Boolean clauses. Defaule value: <b>false</b>.
   */
  bool is_proximity;
  /**
   * @brief Specifies whether the search query will take the stemming of words (for example, run, runs, running) into account when
   *        performing the search. Defaule value: <b>false</b>.
   */
  bool is_stemming;
  /**
   * @brief Specifies whether full width and half width characters in the document exactly match the search query. <b>true</b> means
   *        ignore full width and half width matching, while <b>false</b> means exactly match the search query.
   *        Defaule value: <b>false</b>.
   */
  bool is_ignore_full_width;
  /** @brief The maximum number of documents that will be returned as part of the search query. Defaule value: 100.*/
  int max_docs;
  /**
   * @brief How individual words in the query will be matched to words in the document. This property is relevant only when a query
   *        has more than one word. Please refer to values starting from @link SearchOption::e_WordMatchingMatchPhrase @endlink and
   *        this should be one of these values.
   */
  WordMatching word_matching;
  /** @brief Specifies whether the document text is searched for the query. Defaule value: <b>true</b>.*/
  bool is_search_doc_text;
};

/** This class represents search index config. */
class SearchIndexConfig FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  SearchIndexConfig() {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] name          The name of search index.
   * @param[in] is_available  Specifies whether the serch index is available for selection and searching.
   * @param[in] path          The path of the search index.
   * @param[in] is_selected   Specifies whether the search index participates in the search.
   */
  SearchIndexConfig(WString name, bool is_available, WString path, bool is_selected)
    : name(name)
    , is_available(is_available)
    , path(path)
    , is_selected(is_selected) {}

  /**
   * @brief Constructor, with another search index config object.
   *
   * @param[in] search_index_config  Another search index config object.
   */
  SearchIndexConfig(const SearchIndexConfig& search_index_config)
    : name(search_index_config.name)
    , is_available(search_index_config.is_available)
    , path(search_index_config.path)
    , is_selected(search_index_config.is_selected) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] search_index_config  Another search index config object.
   *
   * @return Reference to current object itself.
   */
  SearchIndexConfig& operator = (const SearchIndexConfig& search_index_config) {
    this->name = search_index_config.name;
    this->is_available = search_index_config.is_available;
    this->path = search_index_config.path;
    this->is_selected = search_index_config.is_selected;
    return *this;
  }

  /**
   * @brief Set values.
   *
   * @param[in] name          The name of search index.
   * @param[in] is_available  Specifies whether the serch index is available for selection and searching.
   * @param[in] path          The path of the search index.
   * @param[in] is_selected   Specifies whether the search index participates in the search.
   *
   * @return None.
   */
  void Set(WString name, bool is_available, WString path, bool is_selected) {
    this->name = name;
    this->is_available = is_available;
    this->path = path;
    this->is_selected = is_selected;
  }
  /** @brief The name of search index.*/
  WString name;

  /**
   * @brief Specifies whether the serch index is available for selection and searching. <b>true</b> means
   *        the index is available, while <b>false</b> means not.
   */
  bool is_available;

  /** @brief The path of the search index.*/
  WString path;

  /**
   * @brief Specifies whether the search index participates in the search. <b>true</b> means
   *        the index is searched as part of the query, while <b>false</b> means it is not searched.
   */
  bool is_selected;
};

/**
 * This class represents a callback object for performing media player actions.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 */
class MediaPlayerCallback {
 public:
  /**
   * @brief Enumeration for media player state.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _JSMediaPlayerState {
    /** @brief media player state: Open. */
    e_JSMediaPlayerStateOpen = 0,
    /** @brief media player state: Close. */
    e_JSMediaPlayerStateClose = 1,
    /** @brief media player state: Playing. */
    e_JSMediaPlayerStatePlaying = 2,
    /** @brief media player state: Stop. */
    e_JSMediaPlayerStateStop = 3,
    /** @brief media player state: Suspend. */
    e_JSMediaPlayerStateSuspend = 4
  } JSMediaPlayerState;
  

  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief A callback function to play the media player.
   *
   * @details This callback function will be triggered by the javascript method "MediaPlayer.play".
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool Play() = 0;

  /**
   * @brief A callback function to close the media player.
   *
   * @details This callback function will be triggered by the javascript method "MediaPlayer.close".
   *
   * @return None.
   */
  virtual void Close() = 0;

  /**
   * @brief A callback function to stop the media player.
   *
   * @details This callback function will be triggered by the javascript method "MediaPlayer.stop".
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool Stop() = 0;

  /**
   * @brief A callback function to seek the media player.
   *
   * @details This callback function will be triggered by the javascript method "MediaPlayer.seek".
   *
   * @param[in] current_pos  Indicate the playback location.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool Seek(int current_pos) = 0;

  /**
   * @brief A callback function to get the media player state.
   *
   * @details This callback function will be triggered by the javascript property "MediaPlayer.isOpen".
   *
   * @return The media player state.
   */
  virtual JSMediaPlayerState GetState() = 0;

  /**
   * @brief A callback function to get the media player settings.
   *
   * @details This callback function will be triggered by the javascript property "MediaPlayer.visible".
   *
   * @return A @link MediaSettings @endlink object.
   */
  virtual MediaSettings GetPlayerSettings() = 0;

 protected:
  ~MediaPlayerCallback() {}
};

/** This class represents the javascript modify item information */
class JavascriptModifyItemInfo FS_FINAL : public Object {
 public:
  /**
   * @brief Enumeration for javascript event type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _JavascriptEventType {
    /** @brief Javascript event: unknown. */
    e_JavascriptEventTypeUnknown = 0,
    /** @brief Javascript event: App initialize. */
    e_JavascriptEventTypeAppInit = 1,
    /** @brief Javascript event: Html callback. */
    e_JavascriptEventTypeHtmlCallback = 2,
    /** @brief Javascript event: Document open. */
    e_JavascriptEventTypeDocOpen = 3,
    /** @brief Javascript event: Document will print. */
    e_JavascriptEventTypeDocWillPrint = 4,
    /** @brief Javascript event: Document did print. */
    e_JavascriptEventTypeDocDidprint = 5,
    /** @brief Javascript event: Document will save. */
    e_JavascriptEventTypeDocWillSave = 6,
    /** @brief Javascript event: Document did save. */
    e_JavascriptEventTypeDocDidSave = 7,
    /** @brief Javascript event: Document will close. */
    e_JavascriptEventTypeDocWillClose = 8,
    /** @brief Javascript event: Page open. */
    e_JavascriptEventTypePageOpen = 9,
    /** @brief Javascript event: Page close. */
    e_JavascriptEventTypePageClose = 10,
    /** @brief Javascript event: Page inview. */
    e_JavascriptEventTypePageInView = 11,
    /** @brief Javascript event: Page outview. */
    e_JavascriptEventTypePageOutView = 12,
    /** @brief Javascript event: Form field mouse down. */
    e_JavascriptEventTypeFieldMouseDown = 13,
    /** @brief Javascript event: Form field mouse up. */
    e_JavascriptEventTypeFieldMouseUp = 14,
    /** @brief Javascript event: Form field mouse enter. */
    e_JavascriptEventTypeFieldMouseEnter = 15,
    /** @brief Javascript event: Form field mouse exit. */
    e_JavascriptEventTypeFieldMouseExit = 16,
    /** @brief Javascript event: Form field focus. */
    e_JavascriptEventTypeFieldFocus = 17,
    /** @brief Javascript event: Form field blur. */
    e_JavascriptEventTypeFieldBlur= 18,
    /** @brief Javascript event: Form field key stroke. */
    e_JavascriptEventTypeFieldKeyStroke= 19,
    /** @brief Javascript event: Form field validate. */
    e_JavascriptEventTypeFieldValidate= 21,
    /** @brief Javascript event: Form field calculate. */
    e_JavascriptEventTypeFieldCalculate= 22,
    /** @brief Javascript event: Form field format. */
    e_JavascriptEventTypeFieldFormat= 23,
    /** @brief Javascript event: Screen focus. */
    e_JavascriptEventTypeScreenFocus = 24,
    /** @brief Javascript event: Screen blur. */
    e_JavascriptEventTypeScreenBlur = 25,
    /** @brief Javascript event: Screen open. */
    e_JavascriptEventTypeScreenOpen = 26,
    /** @brief Javascript event: Screen close. */
    e_JavascriptEventTypeScreenClose = 27,
    /** @brief Javascript event: Screen mouse down. */
    e_JavascriptEventTypeScreenMouseDown = 28,
    /** @brief Javascript event: Screen mouse up. */
    e_JavascriptEventTypeScreenMouseUp = 29,
    /** @brief Javascript event: Screen mouse enter. */
    e_JavascriptEventTypeScreenMouseEnter = 30,
    /** @brief Javascript event: Screen mouse exit. */
    e_JavascriptEventTypeScreenMouseExit = 31,
    /** @brief Javascript event: Screen in view. */
    e_JavascriptEventTypeScreenInview = 32,
    /** @brief Javascript event: Screen out view. */
    e_JavascriptEventTypeScreenOutview = 33,
    /** @brief Javascript event: Batch execute. */
    e_JavascriptEventTypeBatchExec = 34,
    /** @brief Javascript event: Menu execute. */
    e_JavascriptEventTypeMenuExec = 35,
    /** @brief Javascript event: Console execute. */
    e_JavascriptEventTypeConsoleExec = 36,
    /** @brief Javascript event: External execute. */
    e_JavascriptEventTypeExternalExec = 37,
    /** @brief Javascript event: Bookmark mouse up. */
    e_JavascriptEventTypeBookmarkMouseUp = 38,
    /** @brief Javascript event: Link mouse up. */
    e_JavascriptEventTypeLinkMouseUp = 39,
    /** @brief Javascript event: Media blur. */
    e_JavascriptEventTypeMediaBlur = 40,
    /** @brief Javascript event: Media close. */
    e_JavascriptEventTypeMediaClose = 41,
    /** @brief Javascript event: Media done. */
    e_JavascriptEventTypeMediaDone = 42,
    /** @brief Javascript event: Media play. */
    e_JavascriptEventTypeMediaPlay = 43,
    /** @brief Javascript event: Media ready. */
    e_JavascriptEventTypeMediaReady = 44,
    /** @brief Javascript event: Media seek. */
    e_JavascriptEventTypeMediaSeek = 45,
    /** @brief Javascript event: Media stop. */
    e_JavascriptEventTypeMediaStop = 46
  } JavascriptEventType;
  
  /**
   * @brief Enumeration for javascript modify item type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _JavascriptModifyItemType {
    /** @brief Javascript modify item type: none. */
    e_JavascriptModifyItemTypeNone = 0,
    /** @brief Javascript modify item type: field. */
    e_JavascriptModifyItemTypeField = 1,
    /** @brief Javascript modify item type: Annot. */
    e_JavascriptModifyItemTypeAnnot = 2,
    /** @brief Javascript modify item type: Page. */
    e_JavascriptModifyItemTypePage = 3,
    /** @brief Javascript modify item type: Doc. */
    e_JavascriptModifyItemTypeDoc= 4
  } JavascriptModifyItemType;
  
  /**
   * @brief Enumeration for javascript pre-sign item type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _JavascriptModifyPropertyType {
    /** @brief Javascript pre-sign item type: none. */
    e_JavascriptModifyPropertyTypeNone = 0,
    /** @brief Javascript pre-sign item type: border color. */
    e_JavascriptModifyPropertyTypeBorderColor = 1,
    /** @brief Javascript pre-sign item type: fill color. */
    e_JavascriptModifyPropertyTypeFillColor = 2,
    /** @brief Javascript event item type: text color. */
    e_JavascriptModifyPropertyTypeTextColor = 3,
    /** @brief Javascript event item type: value. */
    e_JavascriptModifyPropertyTypeValue = 4,
    /** @brief Javascript event item type: char limit. */
    e_JavascriptModifyPropertyTypeCharLimit = 5,
    /** @brief Javascript event item type: button position. */
    e_JavascriptModifyPropertyTypeButtonPosition = 6,
    /** @brief Javascript event item type: select change. */
    e_JavascriptModifyPropertyTypeSelectChange = 7,
    /** @brief Javascript event item type: alignment. */
    e_JavascriptModifyPropertyTypeAlignment = 8,
    /** @brief Javascript event item type: border style. */
    e_JavascriptModifyPropertyTypeBorderStyle = 9,
    /** @brief Javascript event item type: button align x. */
    e_JavascriptModifyPropertyTypeButtonAlignX = 10,
    /** @brief Javascript event item type: button align Y. */
    e_JavascriptModifyPropertyTypeButtonAlignY = 11,
    /** @brief Javascript event item type: button fit bounds. */
    e_JavascriptModifyPropertyTypeButtonFitBounds = 12,
    /** @brief Javascript event item type: button scale how. */
    e_JavascriptModifyPropertyTypeButtonScaleHow = 13,
    /** @brief Javascript event item type: button scale when. */
    e_JavascriptModifyPropertyTypeButtonScaleWhen = 14,
    /** @brief Javascript event item type: Comb. */
    e_JavascriptModifyPropertyTypeComb = 15,
    /** @brief Javascript event item type: default style. */
    e_JavascriptModifyPropertyTypeDefaultStyle = 16,
    /** @brief Javascript event item type: default value. */
    e_JavascriptModifyPropertyTypeDefaultValue = 17,
    /** @brief Javascript event item type: do not scroll. */
    e_JavascriptModifyPropertyTypeDoNotScroll = 18,
    /** @brief Javascript event item type: delay. */
    e_JavascriptModifyPropertyTypeDelay= 19,
    /** @brief Javascript event item type: display. */
    e_JavascriptModifyPropertyTypeDisplay = 20,
    /** @brief Javascript event item type: editable. */
    e_JavascriptModifyPropertyTypeEditable = 21,
    /** @brief Javascript event item type: not spell check. */
    e_JavascriptModifyPropertyTypeNotSpellCheck = 22,
    /** @brief Javascript event item type: hidden. */
    e_JavascriptModifyPropertyTypeHidden = 23,
    /** @brief Javascript event item type: highlight. */
    e_JavascriptModifyPropertyTypeHighlight= 24,
    /** @brief Javascript event item type: line width. */
    e_JavascriptModifyPropertyTypeLineWidth = 25,
    /** @brief Javascript event item type: multiline. */
    e_JavascriptModifyPropertyTypeMultiline = 26,
    /** @brief Javascript event item type: password. */
    e_JavascriptModifyPropertyTypePassword = 27,
    /** @brief Javascript event item type: rect. */
    e_JavascriptModifyPropertyTypeRect = 28,
    /** @brief Javascript event item type: required. */
    e_JavascriptModifyPropertyTypeRequired = 29,
    /** @brief Javascript event item type: rich text. */
    e_JavascriptModifyPropertyTypeRichText = 30,
    /** @brief Javascript event item type: rich value. */
    e_JavascriptModifyPropertyTypeRichValue = 31,
    /** @brief Javascript event item type: rotation. */
    e_JavascriptModifyPropertyTypeRotation = 32,
    /** @brief Javascript event item type: normal caption. */
    e_JavascriptModifyPropertyTypeNormalCaption = 33,
    /** @brief Javascript event item type: down caption. */
    e_JavascriptModifyPropertyTypeDownCaption = 34,
    /** @brief Javascript event item type: rollover caption. */
    e_JavascriptModifyPropertyTypeRolloverCaption = 35,
    /** @brief Javascript event item type: text font. */
    e_JavascriptModifyPropertyTypeTextFont = 36,
    /** @brief Javascript event item type: user name. */
    e_JavascriptModifyPropertyTypeUserName = 37,
    /** @brief Javascript event item type: set button icon. */
    e_JavascriptModifyPropertyTypeButtonSetIcon = 38,
    /** @brief Javascript event item type: check this box. */
    e_JavascriptModifyPropertyTypeCheckThisBox = 39,
    /** @brief Javascript event item type: clear items. */
    e_JavascriptModifyPropertyTypeClearItems = 40,
    /** @brief Javascript event item type: default is checked. */
    e_JavascriptModifyPropertyTypeDefaultIsChecked = 41,
    /** @brief Javascript event item type: delete item at. */
    e_JavascriptModifyPropertyTypeDeleteItemAt = 42,
    /** @brief Javascript event item type: insert item at. */
    e_JavascriptModifyPropertyTypeInsertItemAt = 43,
    /** @brief Javascript event item type: set items. */
    e_JavascriptModifyPropertyTypeSetItems = 44,
    /** @brief Javascript event item type: activated. */
    e_JavascriptModifyPropertyTypeActivated = 45,
    /** @brief Javascript event item type: arrow begin. */
    e_JavascriptModifyPropertyTypeArrowBegin = 46,
    /** @brief Javascript event item type: arrow end. */
    e_JavascriptModifyPropertyTypeArrowEnd = 47,
    /** @brief Javascript event item type: attach icon. */
    e_JavascriptModifyPropertyTypeAttachIcon = 48,
    /** @brief Javascript event item type: border effect intensity. */
    e_JavascriptModifyPropertyTypeBorderEffectIntensity = 49,
    /** @brief Javascript event item type: border effect style. */
    e_JavascriptModifyPropertyTypeBorderEffectStyle = 50,
    /** @brief Javascript event item type: callout. */
    e_JavascriptModifyPropertyTypeCallout = 51,
    /** @brief Javascript event item type: caret symbol. */
    e_JavascriptModifyPropertyTypeCaretSymbol = 52,
    /** @brief Javascript event item type: contents. */
    e_JavascriptModifyPropertyTypeContents = 53,
    /** @brief Javascript event item type: dash. */
    e_JavascriptModifyPropertyTypeDash = 54,
    /** @brief Javascript event item type: do caption. */
    e_JavascriptModifyPropertyTypeDoCaption = 55,
    /** @brief Javascript event item type: gestures. */
    e_JavascriptModifyPropertyTypeGestures = 56,
    /** @brief Javascript event item type: intent. */
    e_JavascriptModifyPropertyTypeIntent = 57,
    /** @brief Javascript event item type: leader extend. */
    e_JavascriptModifyPropertyTypeLeaderExtend = 58,
    /** @brief Javascript event item type: leader length. */
    e_JavascriptModifyPropertyTypeLeaderLength = 59,
    /** @brief Javascript event item type: line ending. */
    e_JavascriptModifyPropertyTypeLineEnding = 60,
    /** @brief Javascript event item type: note icon. */
    e_JavascriptModifyPropertyTypeNoteIcon = 61,
    /** @brief Javascript event item type: toggle no view. */
    e_JavascriptModifyPropertyTypeToggleNoView = 62,
    /** @brief Javascript event item type: opacity. */
    e_JavascriptModifyPropertyTypeOpacity = 63,
    /** @brief Javascript event item type: points. */
    e_JavascriptModifyPropertyTypePoints = 64,
    /** @brief Javascript event item type: quadspoints. */
    e_JavascriptModifyPropertyTypeQuads = 65,
    /** @brief Javascript event item type: text size. */
    e_JavascriptModifyPropertyTypeTextSize = 66,
    /** @brief Javascript event item type: rich contents. */
    e_JavascriptModifyPropertyTypeRichContents = 67,
    /** @brief Javascript event item type: rich defaults. */
    e_JavascriptModifyPropertyTypeRichDefaults = 68,
    /** @brief Javascript event item type: sound icon. */
    e_JavascriptModifyPropertyTypeSoundIcon = 69,
    /** @brief Javascript event item type: subject. */
    e_JavascriptModifyPropertyTypeSubject = 70,
    /** @brief Javascript event item type: vertices. */
    e_JavascriptModifyPropertyTypeVertices = 71,
    /** @brief Javascript event item type: import. */
    e_JavascriptModifyPropertyTypeImport = 72,
    /** @brief Javascript event item type: remove data object. */
    e_JavascriptModifyPropertyTypeRemoveDataObject = 73,
    /** @brief Javascript event item type: import data object. */
    e_JavascriptModifyPropertyTypeImportDataObject = 74,
    /** @brief Javascript event item type: remove template. */
    e_JavascriptModifyPropertyTypeRemoveTemplate = 75,
    /** @brief Javascript event item type: add page template. */
    e_JavascriptModifyPropertyTypeAddPageTemplate = 76,
    /** @brief Javascript event item type: reset forms. */
    e_JavascriptModifyPropertyTypeRsetForms = 77,
    /** @brief Javascript event item type: reset all forms. */
    e_JavascriptModifyPropertyTypeRsetAllForms = 78,
    /** @brief Javascript event item type: title. */
    e_JavascriptModifyPropertyTypeTitle = 79,
    /** @brief Javascript event item type: resize page. */
    e_JavascriptModifyPropertyTypeResizePage = 80,
    /** @brief Javascript event item type: spawn page from template. */
    e_JavascriptModifyPropertyTypeSpawnPageFromTemplate = 81,
    /** @brief Javascript event item type: add web links. */
    e_JavascriptModifyPropertyTypeAddWeblinks = 82,
    /** @brief Javascript event item type: remove web links. */
    e_JavascriptModifyPropertyTypeRemoveWeblinks = 83,
    /** @brief Javascript event item type: remove links. */
    e_JavascriptModifyPropertyTypeRemoveLinks = 84,
    /** @brief Javascript event item type: page rotations. */
    e_JavascriptModifyPropertyTypePageRotations = 85,
    /** @brief Javascript event item type: new page. */
    e_JavascriptModifyPropertyTypeNewPage = 86,
    /** @brief Javascript event item type: move page. */
    e_JavascriptModifyPropertyTypeMovePage = 87,
    /** @brief Javascript event item type: insert pages. */
    e_JavascriptModifyPropertyTypeInsertPages = 88,
    /** @brief Javascript event item type: replace pages. */
    e_JavascriptModifyPropertyTypeReplacePages = 89,
    /** @brief Javascript event item type: import annot from xfdf. */
    e_JavascriptModifyPropertyTypeImportAnnotFromXFDF = 90,
    /** @brief Javascript event item type: delete annot. */
    e_JavascriptModifyPropertyTypeDeleteAnnot = 91,
    /** @brief Javascript event item type: add watermark. */
    e_JavascriptModifyPropertyTypeAddWatermark = 92,
    /** @brief Javascript event item type: flat document. */
    e_JavascriptModifyPropertyTypeFlatDocument = 93,
    /** @brief Javascript event item type: add fileattachment. */
    e_JavascriptModifyPropertyTypeAddFileAttachment = 94,
    /** @brief Javascript event item type: runtime highlight. */
    e_JavascriptModifyPropertyTypeRuntimeHighlight = 95,
    /** @brief Javascript event item type: runtime highlight color. */
    e_JavascriptModifyPropertyTypeRuntimeHighlightColor = 96,
    /** @brief Javascript event item type: insert from templates. */
    e_JavascriptModifyPropertyTypeInsertFromTemplates = 97,
    /** @brief Javascript event item type: add link. */
    e_JavascriptModifyPropertyTypeAddLink = 98,
    /** @brief Javascript event item type: multiple selection. */
    e_JavascriptModifyPropertyTypeMultipleSelection = 99,
    /** @brief Javascript event item type: set page template visible. */
    e_JavascriptModifyPropertyTypeSetPageTemplateVisible = 100
  } JavascriptModifyPropertyType;
  
  /**
   * @brief Enumeration for javascript modify type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _JavascriptModifyType {
    /** @brief Javascript modify type: none. */
    e_JavascriptModifyTypeNone = 0,
    /** @brief Javascript modify type: add. */
    e_JavascriptModifyTypeAdd = 1,
    /** @brief Javascript modify type: modify. */
    e_JavascriptModifyTypeModify = 2,
    /** @brief Javascript modify type: Delete. */
    e_JavascriptModifyTypeDelete = 3
  } JavascriptModifyType;
  

  /** @brief Constructor. */
  JavascriptModifyItemInfo()
    : event_type(JavascriptModifyItemInfo::e_JavascriptEventTypeUnknown)
    , page_index(-1)
    , field_control_index(-1)
    , modify_item_type(JavascriptModifyItemInfo::e_JavascriptModifyItemTypeNone)
    , modify_type(JavascriptModifyItemInfo::e_JavascriptModifyTypeNone)
    , modify_property_type(JavascriptModifyItemInfo::e_JavascriptModifyPropertyTypeNone)
    , field_or_annot_name(L"")
    , new_value(L"")
    , old_value(L"") {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] event_type               The javascript event type.
   * @param[in] page_index               The modify page index.
   * @param[in] field_control_index The  control index of form field.
   * @param[in] modify_item_type         The modify item type.
   * @param[in] modify_type              The modify type.
   * @param[in] modify_property_type     The modify property type.
   * @param[in] field_or_annot_name      The form field full name or annot subtype name.
   * @param[in] new_value                The new value.
   * @param[in] old_value                The old value.
   */
  JavascriptModifyItemInfo(JavascriptEventType event_type, 
      int page_index, int field_control_index, JavascriptModifyItemType modify_item_type,
      JavascriptModifyType modify_type, JavascriptModifyPropertyType modify_property_type, 
      WString field_or_annot_name, WString new_value, WString old_value)
      : event_type(JavascriptModifyItemInfo::e_JavascriptEventTypeUnknown)
      , page_index(page_index)
      , field_control_index(field_control_index)
      , modify_item_type(modify_item_type)
      , modify_type(modify_type)
      , modify_property_type(modify_property_type)
      , field_or_annot_name(field_or_annot_name)
      , new_value(new_value)
      , old_value(old_value) { }

  /**
   * @brief Constructor, with another  javascript modify item information object.
   *
   * @param[in] other  Another javascript modify item information object.
   */
  JavascriptModifyItemInfo (const JavascriptModifyItemInfo& other)
    : event_type(other.event_type)
    , page_index(other.page_index)
    , field_control_index(other.field_control_index)
    , modify_item_type(other.modify_item_type)
    , modify_type(other.modify_type)
    , modify_property_type(other.modify_property_type)
    , field_or_annot_name(other.field_or_annot_name)
    , new_value(other.new_value)
   , old_value(other.old_value) {
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another javascript modify item information object.
   *
   * @return Reference to current object itself.
   */
  JavascriptModifyItemInfo& operator = (const JavascriptModifyItemInfo& other) {
    if (this != &other) {
      event_type = other.event_type;
      page_index = other.page_index;
      field_control_index = other.field_control_index;
      modify_item_type = other.modify_item_type;
      modify_type = other.modify_type;
      modify_property_type = other.modify_property_type;
      field_or_annot_name = other.field_or_annot_name;
      new_value = other.new_value;
      old_value = other.old_value;
    }
    return *this;
  }

  /**
   * @brief The javascript event type. Please refer to values starting from @link JavascriptModifyItemInfo::e_JavascriptEventTypeUnknown @endlink and
   *        this should be one of these values.
   */
  JavascriptEventType event_type;

  /** @brief The page index. */
  int page_index;

  /** @brief The control index of form field. */
  int field_control_index;
  
  /** 
   * @brief The modify item type. Please refer to values starting from @link JavascriptModifyItemInfo::e_JavascriptModifyItemTypeNone @endlink and
   *        this should be one of these values.
   */
  JavascriptModifyItemType modify_item_type;

  /**
   * @brief The modify type. Please refer to values starting from @link JavascriptModifyItemInfo::e_JavascriptModifyTypeNone @endlink and
   *        this should be one of these values.
   */
  JavascriptModifyType modify_type;

  /**
   * @brief The modify property type. Please refer to values starting from @link JavascriptModifyItemInfo::e_JavascriptModifyPropertyTypeNone @endlink and
   *        this should be one of these values.
   */
  JavascriptModifyPropertyType modify_property_type;

  /** @brief The form field full name or annot subtype name. */
  WString field_or_annot_name;

  /** @brief The new value. */
  WString new_value;

  /** @brief The old value. */
  WString old_value;
};

/**
 * This class represents a callback object for performing PDF actions.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user,
 * to perform PDF actions, such as javascript actions.
 */
class ActionCallback {
 public:
  /**
   * @brief Enumeration for language.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Language {
    /** @brief Unknown language. */
    e_LanguageUnknown = 0,
    /** @brief Chinese Simplified. */
    e_LanguageCHS = 1,
    /** @brief Chinese Traditional. */
    e_LanguageCHT = 2,
    /** @brief Danish. */
    e_LanguageDAN = 3,
    /** @brief German. */
    e_LanguageDEU = 4,
    /** @brief English. */
    e_LanguageENU = 5,
    /** @brief Spanish. */
    e_LanguageESP = 6,
    /** @brief French. */
    e_LanguageFRA = 7,
    /** @brief Italian. */
    e_LanguageITA = 8,
    /** @brief Korean. */
    e_LanguageKOR = 9,
    /** @brief Japanese. */
    e_LanguageJPN = 10,
    /** @brief Dutch. */
    e_LanguageNLD = 11,
    /** @brief Norwegian. */
    e_LanguageNOR = 12,
    /** @brief Brazilian Portuguese. */
    e_LanguagePTB = 13,
    /** @brief Finnish. */
    e_LanguageSUO = 14,
    /** @brief Swedish. */
    e_LanguageSVE = 15
  } Language;
  
  /**
   * @brief Enumeration for application's information type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _AppInfoType {
    /** @brief Application's forms version information. */
    e_AppInfoTypeFormsVersion = 0x0,
    /** @brief Application's viewer type information. */
    e_AppInfoTypeViewerType = 0x01,
    /** @brief Application's viewer variation information. */
    e_AppInfoTypeViewerVariation = 0x02,
    /** @brief Application's viewer version information. */
    e_AppInfoTypeViewerVersion = 0x03,
    /** @brief Application's app version information. */
    e_AppInfoTypeAppVersion = 0x04
  } AppInfoType;
  
  /**
   * @brief Enumeration for data type to be mailed.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _MailType {
    /** @brief Mailed data type: document. */
    e_MailTypeDoc = 0,
    /** @brief Mailed data type: form. */
    e_MailTypeForm = 1,
    /** @brief Mailed data type: string message. */
    e_MailTypeMsg = 2
  } MailType;
  
  /**
   * @brief Enumeration for javascript field value change type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _JSFieldValueChangeType {
    /** @brief javascript field value changed type: format. */
    e_JSFieldValueChangedByFormat = 0,
    /** @brief javascript field value changed type : calculation. */
    e_JSFieldValueChangedByCalculation = 1,
    /** @brief javascript field value changed type: field set value. */
    e_JSFieldValueChangedBySetValue = 2,
    /** @brief javascript field value changed type: field set read-only property. */
    e_JSFieldValueChangedBySetReadOnly = 3,
    /** @brief javascript field value changed type: field fill color. */
    e_JSFieldValueChangedByFillColor = 4
  } JSFieldValueChangeType;
  
  /**
   * @brief Enumeration for media player state.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _JSMediaPlayerState {
    /** @brief media player state: Open. */
    e_JSMediaPlayerStateOpen = 0,
    /** @brief media player state: Close. */
    e_JSMediaPlayerStateClose = 1,
    /** @brief media player state: Playing. */
    e_JSMediaPlayerStatePlaying = 2,
    /** @brief media player state: Stop. */
    e_JSMediaPlayerStateStop = 3,
    /** @brief media player state: Suspend. */
    e_JSMediaPlayerStateSuspend = 4
  } JSMediaPlayerState;
  
  /**
   * @brief Enumeration for layout mode.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _LayoutMode {
    /** @brief Layout mode: single page. */
    e_LayoutModeSinglePage = 0,
    /** @brief Layout mode: continuous page. */
    e_LayoutModeContinuous = 1,
    /** @brief Layout mode: two pages. */
    e_LayoutModeFacing = 2,
    /** @brief Layout mode: continuous two pages. */
    e_LayoutModeContinuousFacing = 3
  } LayoutMode;
  
  /**
   * @brief Enumeration for result of the mail.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _JsMailResult {
    /** @brief Mailed result: mail failed. */
    e_JSMailResultFailed = 0,
    /** @brief Mailed result: mail success. */
    e_JSMailResultSuccess = 1,
    /** @brief Mailed result: user abort. */
    e_JSMailResultUserAbort = 2
  } JsMailResult;
  
  /**
   * @brief Enumeration for search scope.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _SearchScope {
    /** @brief Search scope: active document. */
    e_SearchScopeActiveDoc = 0,
    /** @brief Search scope: folder. */
    e_SearchScopeFolder = 1,
    /** @brief Search scope: index. */
    e_SearchScopeIndex = 2,
    /** @brief Search scope: active indexes. */
    e_SearchScopeActiveIndexes = 3
  } SearchScope;
  
  /**
   * @brief Enumeration for modify item type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ModifyItemType {
    /** @brief Modify item type: none. */
    e_ModifyItemTypeNone = 0,
    /** @brief Modify item type: Field. */
    e_ModifyItemTypeField = 1,
    /** @brief Modify item type: Annot. */
    e_ModifyItemTypeAnnot = 2,
    /** @brief Modify item type: Page. */
    e_ModifyItemTypePage = 3,
    /** @brief Modify item type: Doc. */
    e_ModifyItemTypeDoc = 4
  } ModifyItemType;
  

  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief A callback function to invalidate the client area within the specified rectangle.
   *
   * @details All positions are measured in PDF "user space". Implementation should call function
   *          @link common::Renderer::StartRender @endlink for repainting a specified page area.
   *
   * @param[in] document    A PDF document object. It would be valid.
   * @param[in] page_index  A page index. It would start from 0 and less than page count of the specified document.
   * @param[in] pdf_rect    A rectangle that specifies the page area in [PDF coordinate system] (@ref pdf::PDFPage).
   *                        If this is an empty rectangle, that means to refresh the whole page.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool InvalidateRect(const pdf::PDFDoc& document, int page_index, const RectF& pdf_rect) = 0;

  /**
   * @brief A callback function used to receive current page index.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document  A PDF document object. It would be valid.
   *
   * @return Current page index. The value should be stared from 0 and less than page count of the specified document.
   */
  virtual int GetCurrentPage(const pdf::PDFDoc& document) = 0;

  /**
   * @brief A callback function used to set the current page by index.
   *
   * @details This callback function is optional, so it can be implemented to do nothing.
   *
   * @param[in] document    A PDF document object. It would be valid.
   * @param[in] page_index  A page index which is used to change current page.
   *                        The index would start from 0 and less than page count of the specified document.
   *
   * @return None.
   */
  virtual void SetCurrentPage(const pdf::PDFDoc& document, int page_index) = 0;

  /**
   * @brief A callback function used to set the current page by destination.
   *
   * @details This callback function is optional, so it can be implemented to do nothing.
   *
   * @param[in] document     A PDF document object. It would be valid.
   * @param[in] destination  A @link pdf::Destination @link object.
   *
   * @return None.
   */
  virtual void SetCurrentPage(const pdf::PDFDoc& document, const foxit::pdf::Destination& destination) = 0;

  /**
   * @brief A callback function used to receive current displaying rotation of a page on PDF viewer.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document    A PDF document object. It would be valid.
   * @param[in] page_index  A page index, used to specify which page's rotation is to be retrieved.
   *                        The index would start from 0 and less than page count of the specified document.
   *
   * @return The rotation of specified page. Please refer to values starting from @link common::e_Rotation0 @endlink
   *         and this should be one of these values.
   */
  virtual common::Rotation GetPageRotation(const pdf::PDFDoc& document, int page_index) = 0;

  /**
   * @brief A callback function used to set the rotation value of a page on PDF viewer.
   *
   * @details This callback function is optional, so it can be implemented to do nothing.
   *
   * @param[in] document    A PDF document object. It would be valid.
   * @param[in] page_index  A page index, used to specify which page's rotation is to be changed.
   *                        The index would start from 0 and less than page count of the specified document.
   * @param[in] rotation    New rotation value. Please refer to values starting from @link common::e_Rotation0 @endlink
   *                        and this should be one of these values except @link common::e_RotationUnknown @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool SetPageRotation(const pdf::PDFDoc& document, int page_index, common::Rotation rotation) = 0;

  /**
   * @brief A callback function to execute a named action.
   *
   * @details Please refer to description of "Named Actions" in Section 8.5.3 of <PDF Reference 1.7> for more details.
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document      A PDF document object. It would be valid.
   * @param[in] named_action  A string to specify a named action.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool ExecuteNamedAction(const pdf::PDFDoc& document, const char* named_action) = 0;

  /**
   * @brief A callback function to set the change mark which indicates whether the content of document is
   *        changed or not.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document     A PDF document object. It would be valid.
   * @param[in] change_mark  A boolean value that indicates whether the content of document is changed or not.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool SetDocChangeMark(const pdf::PDFDoc& document, bool change_mark) = 0;

  /**
   * @brief A callback function to receive the change mark which indicates whether the content of document is
   *        changed or not.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document  A PDF document object. It would be valid.
   *
   * @return <b>true</b> means the PDF document is changed, while <b>false</b> means not.
  */
  virtual bool GetDocChangeMark(const pdf::PDFDoc& document) = 0;

  /**
   * @brief A callback function to receive the count of opened documents.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return The count of opened documents.
   */
  virtual int GetOpenedDocCount() = 0;

  /**
   * @brief A callback function to receive an opened PDF document object by index.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] index  The index of an opened PDF documents. Valid range: from 0 to <i>count</i>-1.
   *                   <i>count</i> is returned by callback function @link ActionCallback::GetOpenedDocCount @endlink;
   *
   * @return A opened PDF document object.
   */
  virtual pdf::PDFDoc GetOpenedDoc(int index) = 0;

  /**
   * @brief A callback function to receive current PDF document object.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return Current PDF document object.
   */
  virtual pdf::PDFDoc GetCurrentDoc() = 0;

  /**
   * @brief A callback function to create a blank PDF document object.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return The newly created blank PDF document object.
   */
  virtual pdf::PDFDoc CreateBlankDoc() = 0;
  
  /**
   * @brief A callback function to close document.
   *
   * @details This callback function will be triggered by the javascript method "Doc.closeDoc".
   *          This callback function is optional, so it can be implemented to do nothing.
   *
   * @param[in] document           A PDF document object. It would be valid.
   * @param[in] is_prompt_to_save  <b>true</b> means show save prompt, while <b>false</b> means not.
   *
   * @return None.
   */
  virtual void CloseDoc(const pdf::PDFDoc& document, bool is_prompt_to_save) = 0;
  
  /**
   * @brief A callback function to open a PDF file.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] file_path  A full path of an existing PDF file.
   * @param[in] password   Password for input PDF file. This may be an empty string.
   *
   * @return An opened PDF document object.
   */
  virtual pdf::PDFDoc OpenDoc(const WString& file_path, const WString& password) = 0;

  /**
   * @brief A callback function to cause the system to play a sound.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] type    Sound type. The value would be on of following values:<br>
   *                    <ul>
   *                    <li>0: Error</li>
   *                    <li>1: Warning</li>
   *                    <li>2: Question</li>
   *                    <li>3: Status</li>
   *                    <li>4: Default (default value)</li>
   *                    </ul>
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool Beep(int type) = 0;

  /**
   * @brief A callback function to display a dialog box containing a question and an entry field for the user to
   *        reply to the question.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] question       A string that specifies the question to be posed to the user.
   * @param[in] title          A string that specifies the title of the dialog box.
   * @param[in] default_value  A string that specifies a default value as the answer to the question.
   *                           If the answer is not specified, no default value is presented.
   * @param[in] label          A string that specifies a short string to appear in front of the edit text field.
   * @param[in] is_password    A boolean value that indicates whether user's response should be masked to show:<br>
   *                           <b>true</b> means that the user's response should show as asterisks (*) or bullets (?)
   *                           to mask the response, which might be sensitive information.
   *
   * @return User's response. It can be an empty string.
   */
  virtual WString Response(const wchar_t* question, const wchar_t* title, const wchar_t* default_value,
                                const wchar_t* label, bool is_password) = 0;

  /**
   * @brief A callback function to get the file path of current PDF document.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document  A PDF document object. It would be valid.
   *
   * @return The file path.
   */
  virtual WString GetFilePath(const pdf::PDFDoc& document) = 0;

  /**
   * @brief A callback function to check whether the file is local file.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document  A PDF document object. It would be valid.
   *
   * @return <b>true</b> means the PDF file is loacl file.
   */
  virtual bool IsLocalFile(const pdf::PDFDoc& document) = 0;

  /**
   * @brief A callback function to get the file path of attachments file.
   *
   * @details This callback function will be triggered by the javascript method "Doc.importDataObject".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] pdf_doc  A PDF document object. It will embed with a data object.
   * @param[in] name     The name to associate with the data object. It's the parameter "cName" of the method "Doc.importDataObject".
   *
   * @return The path of the file which will be embedded as a data object.
   */
  virtual WString GetAttachmentsFilePath(const pdf::PDFDoc& pdf_doc, const wchar_t* name) = 0;

  /**
   * @brief A callback function to get the file path of extracted embedded file.
   *
   * @details This callback function will be triggered by the javascript method "Doc.exportDataObject".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] pdf_doc  A PDF document object. It will be embedded as a data object to the file .
   * @param[in] name     The name of the data object to extract. It's the parameter "cName" of the method "Doc.exportDataObject".
   *
   * @return The path of the file which will embed with a data object.
   */
  virtual WString GetExtractedEmbeddedFilePath(const pdf::PDFDoc& pdf_doc, const wchar_t* name) = 0;

  /**
   * @brief A callback function to print pages within a specified index range.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document             A PDF document object. It would be valid.
   * @param[in] is_ui                <b>true</b> means that a UI should be presented to the user
   *                                 to obtain printing information and confirm the action.
   * @param[in] page_range           A range object to specify the page range for printing.
   *                                 All the indexes represented in this range would start from 0 and
   *                                 less than page count of the specified document.
   * @param[in] is_silent            <b>true</b> means that the cancel dialog box should be suppressed
   *                                 while the document is printing.
   * @param[in] is_shrunk_to_fit     <b>true</b> means that the page should be shrunk (if necessary)
   *                                 to fit within the area of the printed page.
   * @param[in] is_printed_as_image  <b>true</b> means that pages should be printed as image.
   * @param[in] is_reversed          <b>true</b> means that the printing order should be from parameter <i>end</i> to
   *                                 parameter <i>start</i>.
   * @param[in] is_to_print_annots   <b>true</b> means that annotations should be printed with page.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool Print(const pdf::PDFDoc& document, bool is_ui,
                     const common::Range& page_range, bool is_silent ,
                     bool is_shrunk_to_fit, bool is_printed_as_image,
                     bool is_reversed, bool is_to_print_annots) = 0;

  /**
   * @brief A callback function to print document with print parameters.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document      A PDF document object. It would be valid.
   * @param[in] print_params  A @link PrintParams @endlink object.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool Print(const pdf::PDFDoc& document, const PrintParams& print_params) = 0;

  /**
   * @brief A callback function to submit the form data to a specified URL.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document           A PDF document object. It would be valid.
   * @param[in] form_data          A form data buffer which is to be submitted.
   * @param[in] length             The size (in bytes) of the buffer parameter<i>form_data</i>.
   * @param[in] url                A URL, to which the form data will be submitted.
   * @param[in] file_format_type   File format type for submission form. Please refer to values starting from @link foxit::common::e_FileFormatTypeFDF @endlink
   *                               and this would be one of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool SubmitForm(const pdf::PDFDoc& document, void* form_data, uint32 length, const char* url, common::FileFormatType file_format_type) = 0;

  /**
   * @brief A callback function to launch to a specified URL.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] url  A URL.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool LaunchURL(const char* url) = 0;

  /**
   * @brief A callback function to show a file selection dialog, and the selected file path should be returned.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return The file path. It can be an empty string.
   */
  virtual WString BrowseFile() = 0;

  /**
   * @brief A callback function to show a file selection dialog.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in]  is_open_dialog  A boolean value to specify whether the dialog is for opening file or saving file.
   *                             <b>true</b> means the dialog should be used to open file, while <b>false</b> means
   *                             the dialog should be used to save file.
   * @param[in]  file_format     The file format string.
   * @param[in]  file_filter     The file filter string.
   *
   * @return The file path. It can be an empty string.
   */
  virtual WString BrowseFile(bool is_open_dialog, const wchar_t* file_format, const wchar_t* file_filter) = 0;

  /**
   * @brief A callback function to get the language of the running viewer application.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return The language type. Please refer to values starting from @link ActionCallback::e_LanguageUnknown @endlink
   *         and this should be one of these values.
   */
  virtual Language GetLanguage() = 0;

  /**
   * @brief A callback function used to pop up a dialog to show warnings or hints.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] msg    The message string to be displayed in the dialog.
   * @param[in] title  The title of the dialog.
   * @param[in] type   Type of button group. It would be one of following values:
   *                   <ul>
   *                   <li>0: OK;(default value.)</li>
   *                   <li>1: OK, Cancel;</li>
   *                   <li>2: Yes, NO; </li>
   *                   <li>3: Yes, NO, Cancel.</li>
   *                   </ul>
   * @param[in] icon   Icon type. It would be one of following values:
   *                   <ul>
   *                   <li>0: Error;(default value.)</li>
   *                   <li>1: Warning;</li>
   *                   <li>2: Question;</li>
   *                   <li>3: Status.</li>
   *                   </ul>
   *
   * @return The return value should be one of following values:<br>
   *         <ul>
   *         <li>1: OK;</li>
   *         <li>2: Cancel; </li>
   *         <li>3: NO;</li>
   *         <li>4: Yes;</li>
   *         </ul>
   */
  virtual int Alert(const wchar_t* msg, const wchar_t* title, int type, int icon) = 0;

  /**
   * @brief A callback function used to get identity properties of current user.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return An identity properties object that specifies the identity properties of current user.
   */
  virtual IdentityProperties GetIdentityProperties() = 0;

  /**
   * @brief A callback function used to set identity properties of current user.
   *
   * @details This callback function is optional, so it can be implemented to do nothing.
   *
   * @param[in] identity_properties  An identity properties object used to be set.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool SetIdentityProperties(const IdentityProperties& identity_properties) = 0;

  /**
   * @brief A callback function to pop up a menu window.
   *
   * @details The position of menu window is the same as cursor's.
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] menus               An array of menu list objects.
   * @param[out] is_selected_item   Output parameter that receives the value of whether a menu item is selected or not.
   *                                <b>true</b> means that the menu item is selected, while <b>false</b> means that the menu item is not selected.
   *
   * @return The name of the menu item that was selected.
   */
  virtual WString PopupMenu(const MenuListArray& menus, bool& is_selected_item) = 0;

  /**
   * @brief A callback function to pop up a menu window.
   *
   * @details The position of menu window is the same as cursor's.
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] menus               An array of @link MenuItemEx @endlink objects.
   * @param[out] is_selected_item   Output parameter that receives the value of whether a menu item is selected or not.
   *                                <b>true</b> means that the menu item is selected, while <b>false</b> means that the menu item is not selected.
   * @return The @link MenuItemEx @endlink object of the menu item that was selected.
   */
  virtual MenuItemEx PopupMenuEx(const MenuItemExArray& menus, bool& is_selected_item) = 0;

  /**
   * @brief A callback function to get application information.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.<br>
   *          For the digital information like
   *          @link ActionCallback::e_AppInfoTypeViewerVersion @endlink, @link ActionCallback::e_AppInfoTypeAppVersion @endlink
   *          and @link ActionCallback::e_AppInfoTypeFormsVersion @endlink, please use string to represent it.
   *
   * @param[in] type  Type of information. Please refer to values starting from 
   *                  @link ActionCallback::e_AppInfoTypeFormsVersion @endlink and this would be one of these values.
   *
   * @return The application information.
   */
  virtual WString GetAppInfo(AppInfoType type) = 0;

  /**
   * @brief A callback function to mail data or message, with or without user interaction.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] data       A data which is to be mailed.
   *                       The value and type of the data depends on parameter <i>data_type</i>:
   *                       <ul>
   *                       <li>This should be <b>NULL</b> when parameter <i>data_type</i> is
   *                           @link ActionCallback::e_MailTypeMsg @endlink.</li>
   *                       <li>This should represents a WString object when parameter <i>data_type</i> is
   *                           @link ActionCallback::e_MailTypeForm @endlink.</li>
   *                       <li>This should represents a @link pdf::PDFDoc @endlink object when parameter <i>data_type</i> is
   *                           @link ActionCallback::e_MailTypeDoc @endlink.</li>
   *                       </ul>
   * @param[in] data_type  Mail type. Please refer to values starting from @link ActionCallback::e_MailTypeDoc @endlink
   *                       and this would be one of these values.
   * @param[in] is_ui      <b>true</b> means that the remaining parameters are used to
   *                       seed the compose-new-message window which is displayed to the user.<br>
   *                       <b>false</b> means that the parameter <i>to</i> is required and all other parameters
   *                       are optional.
   * @param[in] to         A string that specifies a semicolon-delimited list of recipients for the message.
   * @param[in] subject    A string that specifies the subject of the message.
   *                       The limit of this string's length is 64 KB.
   * @param[in] cc         A string that specifies a semicolon-delimited list of CC recipients for the message.
   * @param[in] bcc        A string that specifies a semicolon-delimited list of BCC recipients for the message.
   * @param[in] message    A string that specifies the content of the message.
   *                       The limit of this string's length is 64 KB.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool MailData(void* data, MailType data_type, bool is_ui, const wchar_t* to,
                        const wchar_t* subject, const wchar_t* cc, const wchar_t* bcc, const wchar_t* message) = 0;

  /**
   * @brief A callback function to verify specified signature..
   *
   * @details This callback function will be triggered when a signature is to be verified by an action.
   *          If user does not want to verify the signature, just implement this function to do nothing and
   *          just return @link pdf::Signature::e_StateUnknown @endlink.
   *          User is recommended to use class @link pdf::LTVVerifier @endlink to verify if a signed signature is valid or not.
   *
   * @param[in] document       A PDF document object. It would be valid.
   * @param[in] pdf_signature  A PDF signature which is signed. This signature belongs to input parameter <i>document</i>.
   *
   * @return The signature verified state. Please refer to values starting from @link pdf::Signature::e_StateUnknown @endlink and
   *         this would be one or combination of them.
   */
  virtual uint32 VerifySignature(const pdf::PDFDoc& document, const pdf::Signature& pdf_signature) = 0;
  
  /**
   * @brief A callback function to get the new name for an untitled bookmark.
   *
   * @details This callback function will be triggered by the javascript mothod "bookmark.createChild"
   *          when the parameter "cName" of the method is an empty string.
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return A new name for an untitled bookmark.
   */
  virtual WString GetUntitledBookmarkName() = 0;

  /**
   * @brief A callback function to get the printer name list.
   *
   * @details This callback function will be triggered by the javascript property "app.printerNames".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return An array of the printer name.
   */
  virtual WStringArray GetPrinterNameList() = 0;

  /**
   * @brief A callback function to add a tool button.
   *
   * @details This callback function will be triggered by the javascript method "app.addToolButton".
   *
   * @param[in] button_item  The @link ButtonItem @endlink object of the tool button.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool AddToolButton(const ButtonItem& button_item) = 0;

  /**
   * @brief A callback function to remove a tool button added by the function @link ActionCallback::AddToolButton @endlink.
   *
   * @details This callback function will be triggered by the javascript method "app.removeToolButton".
   *
   * @param[in] button_name  The name of the tool button.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool RemoveToolButtom(const wchar_t* button_name) = 0;

  /**
   * @brief A callback function to get the menu item name list.
   *
   * @details This callback function will be triggered by the javascript method "app.listMenuItems".
   *
   * @return An array of menu list objects.
   */
  virtual MenuListArray GetMenuItemNameList() = 0;

  /**
   * @brief A callback function to adds a menu item to a menu.
   *
   * @details This callback function will be triggered by the javascript method "app.addMenuItem".
   *
   * @param[in] menu_item_config  The config of the menu item.
   * @param[in] is_prepend        Determines the position of the new menu item relative to the position specified by
   *                              @link MenuItemConfig::pos @endlink or @link MenuItemConfig::pos_str @endlink.
   *                              The default value is false. If this parameter is true, the rules for insertion are as follows:
   *                              <ul>
   *                              <li> If @link MenuItemConfig::pos_str @endlink is used, the new item is placed before the named item.</li>
   *                              <li> If @link MenuItemConfig::pos @endlink is used, the new item is placed before the numbered item.</li>
   *                              <li> If the named item cannot be found or position is not between zero and the number of
   *                                   items in the list, inclusive, the new item is inserted as the first item in the
   *                                   menu (rather than at the end of the menu). </li>
   *                              <ul>
   *                              This parameter is useful when the named item is the first item in a group.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool AddMenuItem(const MenuItemConfig& menu_item_config, bool is_prepend) = 0;

  /**
   * @brief A callback function to add a menu item with a submenu to the application.
   *
   * @details This callback function will be triggered by the javascript method "app.addSubMenu".
   *
   * @param[in] menu_item_config  The config of the menu item.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool AddSubMenu(const MenuItemConfig& menu_item_config) = 0;

  /**
   * @brief A callback function to show the dialog.
   *
   * @details This callback function will be triggered by the javascript method "app.execDialog".
   *
   * @param[in] dlg_config The @link DialogDescriptionConfig @endlink object.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool ShowDialog(const DialogDescriptionConfig& dlg_config) = 0;

  /**
   * @brief A callback function to get whether the full screen mode is set.
   *
   * @details This callback function will be triggered by the javascript property "app.fullScreen" or "app.fs.isFullScreen".
   *
   * @return <b>true</b> means the full screen mode is set, while <b>false</b> means not.
   */
  virtual bool GetFullScreen() = 0;

  /**
   * @brief A callback function to set full screen mode.
   *
   * @details This callback function will be triggered when the javascript property "app.fullScreen" or "app.fs.isFullScreen" is to be set.
   *
   * @param[in] is_full_screen  <b>true</b> means to set full screen mode, while <b>false</b> means not.
   *
   * @return None.
   */
  virtual void SetFullScreen(bool is_full_screen) = 0;

  /**
   * @brief A callback function to notify the value change of the field.
   *
   * @details This callback function will be triggered when the field's value is changed via JavaScript.
   *
   * @param[in] field_name            A string that specifies the field name.
   * @param[in] type                  Field value change type. Please refer to values starting from @link ActionCallback::e_JSFieldValueChangedByFormat @endlink 
   *                                  and this would be one of these values.
   * @param[in] value_before_changed  A string array that specifies the field's value before the change.  
   *                                  For a list box, the parameter represent one or more than one of the field's items which be selected simultaneously.
   * @param[in] value_after_changed   A string array that specifies the field's value after the change. 
   *                                  For a list box, the parameter represent one or more than one of the field's items which be selected simultaneously.
   *
   * @return None.
   */
  virtual void OnFieldValueChanged(const wchar_t* field_name, JSFieldValueChangeType type, const WStringArray &value_before_changed, const WStringArray &value_after_changed) = 0;

  /**
   * @brief A callback function to update logical label.
   *
   * @details This callback function will be triggered by the javascript method "Doc.setPageLabels".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return None.
   */
  virtual void UpdateLogicalLabel() = 0;

  /**
   * @brief A callback function to mails a document as an attachment.
   *
   * @details This callback function will be triggered by the javascript method "Doc.mailDoc".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document     A PDF document object. It would be valid.
   * @param[in] to_address   To address.
   * @param[in] cc_address   Cc address.
   * @param[in] bcc_address  Bcc address.
   * @param[in] subject      Mail subject.
   * @param[in] message      Mail message.
   * @param[in] is_ui        <b>true</b> means to show mail dialog, while <b>false</b> means not.
   *
   * @return The mail result. Please refer to values starting from @link ActionCallback::e_JSMailResultFailed @endlink
   *         and this should be one of these values.
   */
  virtual JsMailResult MailDoc(const pdf::PDFDoc& document,
    const wchar_t* to_address, const wchar_t* cc_address, const wchar_t* bcc_address,
    const wchar_t* subject, const wchar_t* message, bool is_ui) = 0;

  /**
   * @brief A callback function to get the temporary file path. The temporary file name combine the document name with the file suffix name.
   *
   * @details This callback function will be triggered by the javascript method "Doc.mailForm".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document          A PDF document object. It would be valid.
   * @param[in] file_suffix_name  File suffix name.
   *
   * @return The temporary file path.
   */
  virtual WString GetTemporaryFileName(const pdf::PDFDoc& document, const wchar_t* file_suffix_name)  = 0;

  /**
   * @brief A callback function to open media player.
   *
   * @details This callback function will be triggered by the javascript method "app.media.openPlayer" or "app.media.createPlayer".
   *
   * @param[in] player_args  The @link PlayerArgs @endlink object.
   *
   * @return A @link MediaPlayerCallback @endlink object.
   */
  virtual MediaPlayerCallback* OpenMediaPlayer(const PlayerArgs& player_args) = 0;
 
  /**
   * @brief A callback function to get temporary directory.
   *
   * @details This callback function will be triggered by the javascript method "Doc.extractpages".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return The temporary directory.
   */
  virtual WString GetTemporaryDirectory() = 0;

  /**
   * @brief A callback function to scroll the specified point on the current page into the middle of the current view.
   *
   * @details This callback function will be triggered by the javascript method "Doc.scroll".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] point  The specified point[PDF coordinate system].
   *
   * @return None.
   */
  virtual void Scroll(const PointF& point) = 0;

  /**
   * @brief A callback function to change the current page number and selects the specified word on the page.
   *
   * @details This callback function will be triggered by the javascript method "Doc.selectPageNthWord".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] page_index         The page index.
   * @param[in] start_offset       The start word offset.
   * @param[in] end_offset         The end word offset.
   * @param[in] is_show_selection  <b>true</b> means to show selection, while <b>false</b> means not.
   *
   * @return None.
   */
  virtual void SelectPageNthWord(int page_index, int start_offset, int end_offset, bool is_show_selection) = 0;

  /**
   * @brief A callback function to get current mouse position.
   *
   * @details This callback function will be triggered by the javascript properties "doc.mouseX" or "doc.mouseY".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return A position in device coordinate system.
   */
  virtual PointF GetMousePosition() = 0;

  /**
   * @brief A callback function to get the rectangle for the page view window. The page view window is
   *        the area inside the inner document window in which the PDF content is displayed.
   *
   * @param[in] document          A PDF document object. It would be valid.
   * @param[in] page_index        The page index.
   *
   * @details This callback function will be triggered by the javascript property "Doc.pageWindowRect".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return A rectangle for the page view window.
   */
  virtual RectF GetPageWindowRect(const foxit::pdf::PDFDoc& document, int page_index) = 0;

  /**
   * @brief A callback function to get the page layout of the current document.
   *
   * @details This callback function will be triggered by the javascript properties "Doc.layout".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return The layout mode. Please refer to values starting from @link ActionCallback::e_LayoutModeSinglePage @endlink
   *         and this should be one of these values.
   */
  virtual LayoutMode GetLayoutMode() = 0;

  /**
   * @brief A callback function to set the page layout of the current document.
   *
   * @details This callback function will be triggered by the javascript properties "Doc.layout".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] layout_mode    The layout mode. Please refer to values starting from @link ActionCallback::e_LayoutModeSinglePage @endlink
   *                           and this should be one of these values.
   * @param[in] is_cover_mode  <b>true</b> means that the cover will always displayed separately, while <b>false</b> means not.
   *
   * @return None.
   */
  virtual void SetLayoutMode(LayoutMode layout_mode, bool is_cover_mode) = 0;

  /**
   * @brief A callback function to get current page zoom value.
   *
   * @details This callback function will be triggered by the javascript properties "Doc.zoom".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return A zoom value. For example, a zoom value of 1.0 specifies 100%. It should be a positive number.
   */
  virtual float GetPageScale() = 0;

  /**
   * @brief A callback function to set current page zoom value.
   *
   * @details This callback function will be triggered by the javascript properties "Doc.zoom" or "Doc.zoomType".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] zoom_mode  The zoom mode. Please refer to values starting from @link pdf::Destination::e_ZoomXYZ @endlink
   *                       and this should be one of these values.
   * @param[in] dest       A @link pdf::Destination @endlink object that represents destination data.
   *
   * @return None.
   */
  virtual void SetPageScale(foxit::pdf::Destination::ZoomMode zoom_mode, const foxit::pdf::Destination& dest) = 0;

  /**
   * @brief A callback function to get the current page zoom mode.
   *
   * @details This callback function will be triggered by the javascript properties "Doc.zoom" or "Doc.zoomType".
   *          This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @return The zoom mode. Please refer to values starting from @link pdf::Destination::e_ZoomXYZ @endlink
   *         and this should be one of these values.
   */
  virtual foxit::pdf::Destination::ZoomMode GetPageZoomMode() = 0;

  /**
   * @brief A callback function to query the text keywords.
   *
   * @details This callback function will be triggered by the javascript method "search.query". This callback function is optional,
   *          so it can be implemented to do nothing.
   *
   * @param[in] keywords       The text content for which to search.
   * @param[in] search_scope   Specifies where the text should be searched. Please refer to values starting from
   *                           @link ActionCallback::e_SearchScopeActiveDoc @endlink and this should be one of these values.
   * @param[in] search_option  A @link SearchOption @endlink object that represents search option.
   * @param[in] di_path        A device-independent path to a folder or search index on the user's computer. This parameter is
   *                           optional. When <i>search_scope</i> is @link ActionCallback::e_SearchScopeFolder @endlink
   *                           or @link ActionCallback::e_SearchScopeIndex @endlink, this parameter is required.
   *
   * @return None.
   */
  virtual void Query(const wchar_t* keywords, SearchScope search_scope, const SearchOption& search_option, const wchar_t* di_path) = 0;

  /**
   * @brief A callback function to add a search index.
   *
   * @details This callback function will be triggered by the javascript method "search.addIndex". This callback function is optional,
   *          so it can be implemented to do nothing.
   *
   * @param[in] di_path      A device-independent path to an index file on the user's hard drive.
   * @param[in] is_selected  Specifies whether the index should be selected for searching. Default value: <b>true</b>.
   *
   * @return A @link SearchIndexConfig @endlink.
   */
  virtual SearchIndexConfig AddSearchIndex(const wchar_t* di_path, bool is_selected) = 0;

  /**
   * @brief (Reserved, unsupported yet) A callback function to remove a search index.
   *
   * @details This callback function will be triggered by the javascript method "search.removeIndex". This callback function is optional,
   *          so it can be implemented to do nothing.
   *
   * @param[in] search_index_config  A @link SearchIndexConfig @endlink that represents the search index config.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  virtual bool RemoveSearchIndex(const SearchIndexConfig& search_index_config) = 0;

  /** 
   * @brief A callback function to get the name list of signature appearance style.
   *
   * @details This callback function will be triggered by the javascript method "SecurityHandler.appearances".
   *          This callback function is optional, so it can be implemented to do nothing.
   *
   * @return An array of signature appearance style name.
   */
  virtual WStringArray GetSignatureAPStyleNameList() = 0;

  /**
   * @brief Initiates a remote procedure call (RPC) or sends an XML message to a SOAP HTTP endpoint.
   *
   * @details The method either waits for the endpoint to reply (synchronous processing) or calls a method
   *          on the notification object (asynchronous processing).<br>
   *          This callback function will be triggered by the javascript method "SOAP.request".
   *          This callback function is optional, so it can be implemented to do nothing.
   * 
   * @param[in] request_params  A @link SOAPRequestProperties @endlink object that contains the property parameters for the SOAP request.
   * 
   * @return A @link SOAPResponseInfo @endlink object. 
   */
  virtual SOAPResponseInfo SoapRequest(const SOAPRequestProperties& request_params) = 0;

  /**
   * @brief A callback function to set the flag specifies whether the document will loop around to the beginning of
   *        the document in response to a page advance (whether generated by mouse click, keyboard, or timer) in full screen mode. 
   * 
   * @details This callback function will be triggered by the javascript property "app.fs.loop".
   *          This callback function is optional, so it can be implemented to do nothing.
   * 
   * @param[in] is_loop  <b>true</b> means to loop around to the beginning of the document, while <b>false</b> means not.
   * 
   * @return None.
   */
  virtual void EnablePageLoop(bool is_loop) = 0;

  /**
   * @brief A callback function to get the flag specifies whether the document will loop around to the beginning of
   *        the document in response to a page advance.
   * 
   * @details This callback function will be triggered by the javascript property "app.fs.loop".
   *          This callback function is optional, so it can be implemented to do nothing.
   * 
   * @return <b>true</b> means to loop around to the beginning of the document, while <b>false</b> means not.
   */
  virtual bool IsPageLoop() = 0;

  /**
   * @brief A callback function to set the default page trastion mode for full screen mode.
   * 
   * @details This callback function will be triggered by the javascript property "app.fs.defaultTransition".
   *          This callback function is optional, so it can be implemented to do nothing.
   * 
   * @param[in] trans_type  A string that specifies the type of the transition effect. Please refer to the follow values:
   *                        "Split", "Box", "Fly", "Blinds", "Push", "Wipe", "Glitter", "Cover", "Uncover", "Dissolve", "Replace", "Fade".
   * @param[in] trans_di    A string that specifies the direction of the transition effect.
   *                        <ul>
   *                        <li> For "Split", this value can be "HorizontalInward", "HorizontalOutward", "VerticalInward" or "VerticalOutward".</li>
   *                        <li> For "Box", this value can be "Outward" or "Inward".</li>
   *                        <li> For "Fly" and "Push", this value can be "Left", "Right", "Up" or "Down".</li>
   *                        <li> For "Blinds", this value can be "Horizontal" or "Vertical".</li>
   *                        <li> For "Wipe", "Glitter", "Uncover" and "Cover", this value can be "Left","LeftUp", "LeftDown", "Right", "RightUp", "RightDown","Up" or "Down".</li>
   *                        <li> For "Dissolve", "Replace" and "Fade", this value will be NULL.</li>
   *                        </ul>
   * @return None.
   */
  virtual void SetDefaultPageTransitionMode(const wchar_t* trans_type, const wchar_t* trans_di) = 0;

  /**
   * @brief A callback function to get the flag specifies whether current document is opened in browser.
   * 
   * @details This callback function will be triggered by the javascript property "doc.hostContainer".
   *          This callback function is optional, so it can be implemented to do nothing.
   * 
   * @return <b>true</b> means current document is opened in browser, while <b>false</b> means not.
   */
  virtual bool IsCurrentDocOpenedInBrowser() = 0;

  /**
   * @brief A callback function to send message asynchronously to the message handler for the host container of the PDF document.
   * 
   * @details For this message to be delivered, the host container (for example, an <OBJECT> element in an HTML page) must have
   *          registered for notification by setting its messageHandler property.<br>
   *          This callback function will be triggered by the javascript method "doc.hostContainer.postMessage".
   *          This callback function is optional, so it can be implemented to do nothing.
   * 
   * @param[in] message  An array of string that specifies the message to be posted.
   * 
   * @return None.
   */
  virtual void PostMessageToHtml(WStringArray message) = 0;

  /**
   * @brief A callback function used to notify javascript execution to begin.
   *
   * @details This callback function is optional, so it can be implemented to do nothing if no action is required.
   *
   * @param[in] document    A PDF document object. It should be valid.
   * @param[in] event_type  The javascript event type. Please refer to values starting from @link JavascriptModifyItemInfo::e_JavascriptEventTypeUnknown @endlink and
   *                       this should be one of these values.
   *
   * @return None.
   */
  virtual void NotifyBeginDoJob(const pdf::PDFDoc& document, JavascriptModifyItemInfo::JavascriptEventType event_type) = 0;

  /**
   * @brief A callback function to notify that data has been modified.
   *
   * @details This callback function is optional, so it can be implemented to do nothing if no action is required.
   *
   * @param[in] document    A PDF document object. It should be valid.
   * @param[in] modify_item_info  A @link JavascriptModifyItemInfo @endlink object containing details about the modification.
   *
   * @return None.
   */
  virtual void NotifyAfterDataChange(const pdf::PDFDoc& document, JavascriptModifyItemInfo modify_item_info) = 0;

  /**
   * @brief A callback function to notify that javascript execution has ended.
   *
   * @details This callback function is optional, so it can be implemented to do nothing if no action is required.
   *
   * @param[in] document    A PDF document object. It should be valid.
   * @param[in] event_type  The javascript event type. Please refer to values starting from @link JavascriptModifyItemInfo::e_JavascriptEventTypeUnknown @endlink and
   *                       this should be one of these values.
   *
   * @return None.
   */
  virtual void NotifyEndDoJob(const pdf::PDFDoc& document, JavascriptModifyItemInfo::JavascriptEventType event_type) = 0;

  /**
   * @brief A callback function to init modify item.
   *
   * @details This callback function is optional, so it can be implemented to do nothing if no action is required.
   *
   * @param[in] document   A PDF document object. It should be valid.
   * @param[in] item_type  The modify item type. Please refer to values starting from @link ActionCallback::e_ModifyItemTypeNone @endlink and
   *                       this should be one of these values.
   * @param[in] page_index  A page index which is used to change current page.
   * @param[in] dict_name   The name of the dictionary.
   *
   * @return <b>true</b> means that the modified item was initialized successfully, and <b>false</b> means that initialization failed.
   */
  virtual bool InitModifyItem(const pdf::PDFDoc& document, ModifyItemType item_type, int page_index, const WString& dict_name) = 0;

  /**
   * @brief A callback function to reset modify item.
   *
   * @details This callback function is optional, so it can be implemented to do nothing if no action is required.
   *
   * @param[in] document  A PDF document object. It should be valid.
   * 
   * @return None.
   */
  virtual void ResetModifyItem(const pdf::PDFDoc& document) = 0;

  /**
   * @brief A callback function to get the visible pages count.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document           A PDF document object. It would be valid.
   *
   * @return The count of visible pages.
   */
  virtual int GetVisiblePageCount(const pdf::PDFDoc& document) = 0;

  /**
   * @brief A callback function to get the visible page index.
   *
   * @details This callback function is optional, so it can be implemented to do nothing and
   *          just return a useless value.
   *
   * @param[in] document           A PDF document object. It would be valid.
   * @param[in] index              The visible page index.  Valid range: from 0 to (<i>count</i>-1).
   *                               <i>count</i> is returned by function @link GetVisiblePagesCount @endlink.
   *
   * @return The page index of visible page.
   */
  virtual int GetVisiblePage(const pdf::PDFDoc& document, int index) = 0;

 protected:
  virtual ~ActionCallback() {}
};
}  // namespace foxit

#endif  // FS_ACTIONCALLBACK_H_

