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
 * @file fs_paragraphedit.h
 * @brief Header file for paragraph edit editing related definitions and classes.
 */

#ifndef FS_PARAGRAPHEDITING_H_
#define FS_PARAGRAPHEDITING_H_

#include "common/fs_common.h"
#include "common/fs_render.h"
#include "pdf/fs_pdfdoc.h"
#include "pdf/fs_pdfpage.h"

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
/**
 * @brief PDF namespace.
 */
namespace addon {
/**
 * @brief Pageeditor namespace.
 */
namespace pageeditor {
// forward declaration
class ParagraphEditing;
class ParagraphEditingUndoItem;

/**
 * This class represents a callback object for paragraph edit provider.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 */
class ParagraphEditingProviderCallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief A callback function to get the render matrix.
   *
   * @param[in] page_index  The page index.
   *
   * @return The matrix.
   */
  virtual Matrix GetRenderMatrix(const pdf::PDFDoc& document, int page_index) = 0;

  /**
   * @brief A callback function to get the page view window handle.
   *
   * @param[in] page_index  The page index.
   *
   * @return The page view window handle.
   */
  virtual void* GetPageViewHandle(const pdf::PDFDoc& document, int page_index) = 0;

  /**
   * @brief A callback function to get the client rectangle in device coordinate system.
   *
   * @return The client rectangle.
   */
  virtual RectF GetClientRect(const pdf::PDFDoc& document) = 0;

  /**
   * @brief A callback function to get the scale of page.
   *
   * @param[in] page_index  The page index.
   *
   * @return The scale value. The returned value should be greater than 0.
   */
  virtual float GetScale(const pdf::PDFDoc& document, int page_index) = 0;

  /**
   * @brief A callback function to go to page view.
   *
   * @param[in] page_index  The page index.
   * @param[in] left        The left point where left mouse button is up in the page, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] top         The top point where left mouse button is up in the page, in [PDF coordinate system] (@ref pdf::PDFPage).
   *
   * @return <b>true</b> means successful, while <b>false</b> means not.
   */
  virtual bool GotoPageView(const pdf::PDFDoc& document, int page_index, float left, float top) = 0;

  /**
   * @brief A callback function used to get visible page indexes.
   *
   * @return The visble page index array.
   */
  virtual Int32Array GetVisiblePageIndexArray(const pdf::PDFDoc& document) = 0;

  /**
   * @brief A callback function used to get visible page rectangle in device coordinate system.
   *
   * @param[in] page_index The page index.
   *
   * @return The page visble rectangle.
   */
  virtual RectF GetPageVisibleRect(const pdf::PDFDoc& document, int page_index) = 0;

  /**
   * @brief A callback function used to get page rectangle in device coordinate system.
   *
   * @param[in] page_index  The page index.
   *
   * @return The page rectangle.
   */
  virtual foxit::RectF GetPageRect(const pdf::PDFDoc& document, int page_index) = 0;

  /**
   * @brief A callback function used to get current page index.
   *
   * @return The page index.
   */
  virtual int GetCurrentPageIndex(const pdf::PDFDoc& document) = 0;

  /**
   * @brief A callback function used to get the page view rotate.
   *
   * @param[in] page_index  The page index.
   *
   * @return The indent value.
   */
  virtual common::Rotation GetRotation(const pdf::PDFDoc& document, int page_index) = 0;

  /**
   * @brief A callback function used to invalidate page rectangle.
   *
   * @param[in] page_index  The page index.
   * @param[in] rects       The invalid areas. The rectangle in <i>invalid_rects</i> is in device coordinate system.
   *
   * @return None.
   */
  virtual void InvalidateRect(const pdf::PDFDoc& document, int page_index, const RectFArray& invalid_rects) = 0;

  /**
   * @brief A callback function used to notify the page to add undo operation.
   *
   * @param[in] undo_item  The undo item object.
   *
   * @return None.
   */
  virtual void AddUndoItem(const ParagraphEditingUndoItem& undo_item) = 0;

  /**
   * @brief A callback function used to notify the document have changed.
   *
   * @param[in] document  The valid pdf document.
   *
   * @return None.
   */
  virtual void SetDocChangeMark(const pdf::PDFDoc& document) = 0;

  /**
   * @brief A callback function used to notify text input reach limit.
   *
   * @param[in] page_index  The page index.
   *
   * @return None.
   */
  virtual void NotifyTextInputReachLimit(const pdf::PDFDoc& document, int page_index) = 0;

 protected:
  /** @brief Destructor. */
  virtual ~ParagraphEditingProviderCallback() {}
};

/**
 * This class represents be used to when execute undo/redo operation.
 */
class ParagraphEditingUndoItem FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, with another undo item object.
   *
   * @param[in] other  Another undo item object.
   */
  ParagraphEditingUndoItem(const ParagraphEditingUndoItem& other);

  /** @brief Destructor. */
  ~ParagraphEditingUndoItem();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit ParagraphEditingUndoItem(FS_HANDLE handle);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another undo item object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  ParagraphEditingUndoItem& operator=(const ParagraphEditingUndoItem& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another undo item object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const ParagraphEditingUndoItem& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another undo item object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const ParagraphEditingUndoItem& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Undo this item.
   *
   * @return None.
   */
  void Undo();

  /**
   * @brief Redo this item.
   *
   * @return None.
   */
  void Redo();
};

/**
 * This class represents a paragraph edit operation.
 * Before use any methods of paragraph edit function, please ensure the function @link ParagraphEditing::Activate @endlink has been called.
 * Please call the function @link ParagraphEditing::Deactivate @endlink to deactivate when no need to use any paragraph edit function.
 */

class ParagraphEditing FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for bullet type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _BulletType {
    /** @brief Bullet type: none. */
    e_BulletTypeNone = 0,
    /** @brief Bullet type: solid circle. */
    e_BulletTypeSolidCircle = 1,
    /** @brief Bullet type: solid rectangle. */
    e_BulletTypeSolidRectangle = 2,
    /** @brief Bullet type: solid diamond. */
    e_BulletTypeSolidDiamond = 3,
    /** @brief Bullet type: check. */
    e_BulletTypeCheck = 4,
    /** @brief Bullet type: right arrow (upper white and lower black). */
    e_BulletTypeRightArrow = 5,
    /** @brief Bullet type: inverse tangent circle. */
    e_BulletTypeInverseTangentCircle = 6,
    /** @brief Bullet type: diagonal up right arrow. */
    e_BulletTypeDiagonalUpRightArrow = 7,
    /** @brief Bullet type: black diamond minus white. */
    e_BulletTypeBlackDiamondMinusWhite = 8
  } BulletType;
  
  /**
   * @brief Enumeration for numbering type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _NumberingType {
    /** @brief Numbering type: none. */
    e_NumberingTypeNone = 0,
    /** @brief Numbering type: 1. 2. 3. */
    e_NumberingTypeDecimalDot = 1,
    /** @brief Numbering type: 1) 2) 3) */
    e_NumberingTypeDecimalRParen = 2,
    /** @brief Numbering type: A. B. C. */
    e_NumberingTypeUpperLatinDot = 3,
    /** @brief Numbering type: a) b) c) */
    e_NumberingTypeLowerLatinRParen = 4,
    /** @brief Numbering type: a. b. c. */
    e_NumberingTypeLowerLatinDot = 5
  } NumberingType;
  

  /** @brief Destructor. */
  ~ParagraphEditing();

  /**
   * @brief Constructor, with another paragraph edit object.
   *
   * @param[in] other  Another paragraph edit object.
   */
  ParagraphEditing(const ParagraphEditing& other);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit ParagraphEditing(FS_HANDLE handle);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another paragraph edit object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  ParagraphEditing& operator=(const ParagraphEditing& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another paragraph edit object. This function will check if current object is equal to this
   * one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const ParagraphEditing& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another paragraph edit object. This function will check if current object is not equal to
   * this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const ParagraphEditing& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Activate paragraph editing.
   * 
   * @return <b>true</b> means succeful, while <b>false</b> means not.
   */
  bool Activate();

  /**
   * @brief Deactivate paragraph editing.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Deactivate();

  /**
   * @brief Start paragraph editing.
   *
   * @param[in] page_index   The page index.
   * @param[in] start_point  A point to start editing on the page, in the device coordinate system.
   * @param[in] end_point    A point to end editing on the page, in the device coordinate system.
   *
   * @return None.
   */
  void StartEditing(int page_index, const PointF& start_point, const PointF& end_point);

  /**
   * @brief Exit paragraph editing.
   *
   * @param[in] is_end_directly  Whether to end editing directly.
   *
   * @return None.
   */
  void ExitEditing(bool is_end_directly = false);

  /**
   * @brief Call this function when insert text into the page.
   *
   * @param[in] text  The text to be inserted.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool InsertText(const WString& text);

  /**
   * @brief Draw the current paragraph editing operation status on the rendering.
   *
   * @details The matrix used in the rendering process is returned by @link ParagraphEditingProviderCallback::GetRenderMatrix @endlink.
   *
   * @param[in] page_index_array  The page index array to render.
   * @param[in] renderer          A valid renderer object for rendering.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Render(const Int32Array page_index_array, const common::Renderer& renderer);

  /**
   * @brief Call this function when a character code is being input.
   *
   * @param[in] char_code  A character code, in UTF16-LE encoding.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnChar(uint32 char_code);

  /**
   * @brief Call this function when key on the keyboard is down.
   *
   * @param[in] key_code  The key code. Please refer to values starting from @link pdf::interform::Filler::e_VkeyUnknown @endlink and
   *                      this should be one of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnKeyDown(uint32 key_code);

  /**
   * @brief Call this function when key on the keyboard is up.
   *
   * @param[in] key_code  The key code. Please refer to values starting from @link pdf::interform::Filler::e_VkeyUnknown @endlink and
   *                      this should be one of these values.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnKeyUp(uint32 key_code);

  /**
   * @brief Call this function when left mouse button is down.
   *
   * @param[in] page_index  The page index.
   * @param[in] point       A point where left mouse button is down in the page, in device coordinate system.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnLButtonDown(int page_index, const PointF& point);

  /**
   * @brief Call this function when left mouse button is up.
   *
   * @param[in] page_index  The page index.
   * @param[in] point       A point where left mouse button is up in the page, in device coordinate system.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnLButtonUp(int page_index, const PointF& point);

  /**
   * @brief Call this function when left mouse button is double clicked.
   *
   * @param[in] page_index  The page index.
   * @param[in] point       A point where left mouse button is double-clicked in the page, in device coordinate system.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnLButtonDoubleClick(int page_index, const PointF& point);

  /**
   * @brief Call this function when mouse moves.
   *
   * @param[in] page_index  The page index.
   * @param[in] point       A point where the mouse in the page, in device coordinate system.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnMouseMove(int page_index, const PointF& point);

  /**
   * @brief Call this function when scrolling the mouse wheel.
   *
   * @param[in] page_index  The page index.
   * @param[in] point       A point where the mouse in the page, in device coordinate system.
   * @param[in] delta       Indicates the amount the mouse wheel has been moved. A positive value means to be moved forward,
   *                        and a negative value means to be moved backward.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnMouseWheel(int page_index, const PointF& point, int32 delta);

  /**
   * @brief Check whether can select all text.
   *
   * @return <b>true</b> means current all text can be selected, while <b>false</b> means not.
   */
  bool CanSelectAll();

  /**
   * @brief Select all text.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool SelectAll();

  /**
   * @brief Check whether can delete text.
   *
   * @return <b>true</b> means current selected text can be deleted, while <b>false</b> means not.
   */
  bool CanDelete();

  /**
   * @brief Delete the selected text.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool DeleteSelected();

  /**
   * @brief Check whether can copy text.
   *
   * @return <b>true</b> means current selected text object can be copied, while <b>false</b> means not.
   */
  bool CanCopy();

  /**
   * @brief Copy the selected text.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool CopySelected();

  /**
   * @brief Check whether can cut text.
   *
   * @return <b>true</b> means current selected text can be cut, while <b>false</b> means not.
   */
  bool CanCut();

  /**
   * @brief Cut the selected text.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool CutSelected();

  /**
   * @brief Check whether can paste text.
   *
   * @return <b>true</b> means current selected text can be pasted, while <b>false</b> means not.
   */
  bool CanPaste();

  /**
   * @brief Paste the copied text.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool PasteSelected();

  /**
   * @brief Check whether can deselect all text.
   *
   * @return <b>true</b> means current selected text can be deselected, while <b>false</b> means not.
   */
  bool CanDeselectAll();

  /**
   * @brief Deselect all text.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool DeselectAll();

  /**
   * @brief Set font name for text.
   *
   * @param[in] font_name The font name.
   *
   * @return None.
   */
  void SetFontName(const WString& font_name);

  /**
   * @brief Set the font size for text.
   *
   * @param[in] font_size  The font size.
   *
   * @return None.
   */
  void SetFontSize(float font_size);

  /**
   * @brief Set text color for text.
   *
   * @param[in] text_color  The text color.
   *
   * @return None.
   */
  void SetTextColor(RGB text_color);

  /**
   * @brief Set bold status for text.
   *
   * @param[in] is_bold  Whether to set selected text as bold. <b>true</b> means current selected text will be set as bold, while <b>false</b> means not.
   *
   * @return None.
   */
  void SetBold(bool is_bold);

  /**
   * @brief Set italic status for text.
   *
   * @param[in] is_italic  Whether to set selected text as italic. <b>true</b> means current selected text will be set as italic, while <b>false</b> means not.
   *
   * @return None.
   */
  void SetItalic(bool is_italic);

  /**
   * @brief Set text alignment for text.
   *
   * @param[in] alignment  Alignment value.Please refer to values starting from @link common::e_AlignmentLeft @endlink and
   *                       this should be one of these values.
   *
   * @return None.
   */
  void SetAlignment(foxit::common::Alignment alignment);

  /**
   * @brief Set char space for text.
   *
   * @param[in] char_space  The char space (unit is 1/72 inch).
   *
   * @return None.
   */
  void SetCharSpace(float char_space);

  /**
   * @brief Set char horizontal scale for text.
   *
   * @param[in] scale  The scale. It should be bigger than 0.
   *
   * @return None.
   */
  void SetCharHorizontalScale(int scale);

  /**
   * @brief Set line space for text.
   *
   * @param[in] line_space  The line space (unit is 1/72 inch).
   *
   * @return None.
   */
  void SetLineSpace(float line_space);

  /**
   * @brief Set underline for text.
   *
   * @param[in] is_underline  <b>true</b> means to underline text, while <b>false</b> means not.
   *
   * @return None.
   */
  void SetUnderline(bool is_underline);

  /**
   * @brief Set strikeout word style for text.
   *
   * @param[in] is_striketrough  <b>true</b> means to set the strikeout word style, while <b>false</b> means not.
   *
   * @return None.
   */
  void SetStrikethrough(bool is_striketrough);

  /**
   * @brief Set the word property of superscript type for text.
   *
   * @param[in] is_super_set  <b>true</b> means to set the word property of superscript type, while <b>false</b> means not.
   *
   * @return None.
   */
  void SetSuperscript(bool is_superscript);

  /**
   * @brief Set the word property of subscript type for text.
   *
   * @param[in] is_sub_script  <b>true</b> means to set the word property of subscript type, while <b>false</b> means not.
   *
   * @return None.
   */
  void SetSubscript(bool is_subscript);

  /**
   * @brief Set paragraph spacing for text.
   *
   * @param[in] paragraph_space  The paragraph spacing.
   *
   * @return None.
   */
  void SetParagraphSpacing(float paragraph_space);

  /**
   * @brief Increase indent for text.
   *
   * @return None.
   */
  void Indent();

  /**
   * @brief Decrease indent for text.
   *
   * @return None.
   */
  void Dedent();

  /**
   * @brief Set bullet list for text.
   *
   * @details Before setting a bullet list, ensure the "wingding.ttf" font has been installed.
   *
   * @param[in] bullet_type  The type of bullet. Please refer to values starting from @link foxit::addon::pageeditor::e_BulletTypeNone @endlink and
   *                         this should be one of these values. 
   *
   * @return None.
   */
  void SetBulletedList(BulletType bullet_type);

  /**
   * @brief Set the look of numbering for text.
   *
   * @param[in] numbering_type  The type of numbering. Please refer to values starting from @link foxit::addon::pageeditor::e_NumberingTypeNone @endlink and
   *                            this should be one of these values. 
   *
   * @return None.
   */
  void SetNumberedList(NumberingType numbering_type);
};

/**
 * This class represents a join split operation.
 * Before use join split feature, ensure the function @link JoinSplit::Activate @endlink has been called successfully.
 * Please call the function @link JoinSplit::Deactivate @endlink to deactivate when no need to use any join split function.
 */
class JoinSplit FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for join spilt operation type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _JoinSplitOperationType {
    /** @brief Join spilt operation type: Join. */
    e_JoinSplitOperationTypeJoin = 0,
    /** @brief Join spilt operation type: Spilt. */
    e_JoinSplitOperationTypeSpilt = 1,
    /** @brief Join spilt operation type: Link. */
    e_JoinSplitOperationTypeLink = 2,
    /** @brief Join spilt operation type: Unlink. */
    e_JoinSplitOperationTypeUnlink = 3,
    /** @brief Join spilt operation type: SelectNone. */
    e_JoinSplitOperationTypeSelectNone = 4,
    /** @brief Join spilt operation type: Close. */
    e_JoinSplitOperationTypeClose = 5
  } JoinSplitOperationType;
  

  /** @brief Destructor. */
  ~JoinSplit();

  /**
   * @brief Constructor, with another join split object.
   *
   * @param[in] other  Another join split object.
   */
  JoinSplit(const JoinSplit& other);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit JoinSplit(FS_HANDLE handle);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another join split object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  JoinSplit& operator=(const JoinSplit& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another join split object. This function will check if current object is equal to this
   * one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const JoinSplit& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another join split object. This function will check if current object is not equal to
   * this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const JoinSplit& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Activate join split editing.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Activate();

  /**
   * @brief Deactivate join split editing.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Deactivate();

  /**
   * @brief Exit join split editing.
   *
   * @return None.
   */
  void ExitJoinEditing();

  /**
   * @brief Draw the currently join split operation state on the rendering.
   *
   * @details The matrix used in the rendering process is returned by @link ParagraphEditingProviderCallback::GetRenderMatrix @endlink.
   *
   * @param[in] page_index_array  The page index array to render.
   * @param[in] renderer          A valid renderer object for rendering.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Render(Int32Array page_index_array, const common::Renderer& renderer);

  /**
   * @brief Call this function when left mouse button is down.
   *
   * @param[in] page_index  The page index.
   * @param[in] point       A point where left mouse button is down in the page, in device coordinate system.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnLButtonDown(int page_index, const PointF& point);

  /**
   * @brief Call this function when left mouse button is up.
   *
   * @param[in] page_index  The page index.
   * @param[in] point       A point where left mouse button is up in the page, in device coordinate system.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnLButtonUp(int page_index, const PointF& point);

  /**
   * @brief Call this function when mouse moves.
   *
   * @param[in] page_index  The page index.
   * @param[in] point       A point where mouse moves in the page, in device coordinate system.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool OnMouseMove(int page_index, const PointF& point);

  /**
   * @brief Get join split editing operation state.
   *
   * @return <b>true</b> means enabled, while <b>false</b> means not.
   */
  bool GetEnableStatus(JoinSplit::JoinSplitOperationType type);

  /**
   * @brief Call this function to join text.
   *
   * @return None.
   */
  void JoinBoxes();

  /**
   * @brief Call this function to split text.
   *
   * @return None.
   */
  void SplitBoxes();

  /**
   * @brief Call this function to link text.
   *
   * @return None.
   */
  void LinkBoxes();

  /**
   * @brief Call this function to unlink text.
   *
   * @return None.
   */
  void UnlinkBoxes();

  /**
   * @brief Call this function to clear all selected text.
   *
   * @return None.
   */
  void SelectNone();
};

/**
 * This class represents a paragraph editing manager used for editing PDF page.
 *
 * User can call the function @link ParagraphEditingMgr::GetParagraphEditing @endlink to get current @link ParagraphEditing @endlink object in the process of using edit page.
 * User can call the function @link ParagraphEditingMgr::GetJoinSplit @endlink to get current @link JoinSplit @endlink object in the process of using edit page.
 *
 * @see @link ParagraphEditing @endlink
 * @see @link JoinSplit @endlink
 */
class ParagraphEditingMgr FS_FINAL : public Base{
 public:
   /**
    * @brief Constructor.
    *
    * @param[in] callback  A valid paragraph editing provider callback object.
    * @param[in] document  A valid PDF document object.
    */
   explicit ParagraphEditingMgr(ParagraphEditingProviderCallback* callback, const pdf::PDFDoc& document);

   /** @brief Destructor. */
   ~ParagraphEditingMgr();

   /**
    * @brief Constructor, with another paragraph edit manager object.
    *
    * @param[in] other  Another paragraph edit manager object.
    */
   ParagraphEditingMgr(const ParagraphEditingMgr& other);

   // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
   explicit ParagraphEditingMgr(FS_HANDLE handle = NULL);

   /**
    * @brief Assign operator.
    *
    * @param[in] other  Another paragraph edit manager object, whose value would be assigned to current object.
    *
    * @return Reference to current object itself.
    */
   ParagraphEditingMgr& operator=(const ParagraphEditingMgr& other);

   /**
    * @brief Equal operator.
    *
    * @param[in] other  Another paragraph edit manager object. This function will check if current object is equal to this one.
    *
    * @return <b>true</b> means equal, while <b>false</b> means not equal.
    */
   bool operator==(const ParagraphEditingMgr& other) const;

   /**
    * @brief Not equal operator.
    *
    * @param[in] other  Another paragraph edit manager object. This function will check if current object is not equal to this one.
    *
    * @return <b>true</b> means not equal, while <b>false</b> means equal.
    */
   bool operator!=(const ParagraphEditingMgr& other) const;

   /**
    * @brief Check whether current object is empty or not.
    *
    * @details When the current object is empty, that means current object is useless.
    *
    * @return <b>true</b> means current object is empty, while <b>false</b> means not.
    */
   bool IsEmpty() const;

   /**
    * @brief Get the paragraph edit object.
    *
    * @return The @link ParagraphEditing @endlink object.
    */
   ParagraphEditing GetParagraphEditing();

   /**
    * @brief Get the join split object.
    *
    * @return The @link JoinSplit @endlink object.
    */
   JoinSplit GetJoinSplit();

   /**
    * @brief Set the dpi for the paragraph editing provider used.
    *
    * @param[in] horizontal_dpi  A horizontal dpi for paragraph editing provider. It should be greater than 0.Default Value:96.
    * @param[in] vertical_dpi    A vertical dpi for paragraph editing provider. It should be greater than 0. Default Value:96.
    *
    * @return None.
    */
   void SetSystemDPI(float horizontal_dpi, float vertical_dpi);
};
}  // namespace pageeditor
}  // namespace addon
}  // namespace foxit
#endif  // FS_PARAGRAPHEDIT_H_
