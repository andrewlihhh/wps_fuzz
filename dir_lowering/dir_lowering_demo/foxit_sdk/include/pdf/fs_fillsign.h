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
 * @file fs_fillsign.h
 * @brief Header file for PDF fill-sign related definitions and classes.
 */

#ifndef FS_FILLSIGN_H_
#define FS_FILLSIGN_H_

#include "common/fs_common.h"
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
namespace pdf {
class FillSignObject;

/**
 * This class represents text fill-sign object data.
 */
class TextFillSignObjectData FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] text_state  Text state information.
   * @param[in] text        Text content string.
   *
   * @return None.
   */
  TextFillSignObjectData(const graphics::TextState& text_state, WString text) {
    this->text_state = text_state;
    this->text = text;
  }

  /** @brief Constructor. */
  TextFillSignObjectData() {}

  /**
   * @brief Constructor, with another text fill-sign object data.
   *
   * @param[in] text_data  Another text fill-sign object data.
   */
  TextFillSignObjectData(const TextFillSignObjectData& text_data) {
    text_state = text_data.text_state;
    text = text_data.text;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] text_data  Another text fill-sign object data, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TextFillSignObjectData& operator=(const TextFillSignObjectData& text_data) {
    text_state = text_data.text_state;
    text = text_data.text;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] text_state  Text state information.
   * @param[in] text        Text content string.
   *
   * @return None.
   */
  void Set(const graphics::TextState& text_state, WString text) {
    this->text_state = text_state;
    this->text = text;
  }

  /** @brief Text state information. */
  graphics::TextState text_state;
  /** @brief Text content string. */
  WString text;
};

/** This class represents an array of @link TextFillSignObjectData @endlink objects. */
FSDK_DEFINE_ARRAY(TextFillSignObjectDataArray, TextFillSignObjectData)

/**
 * Fill-sign means to fill some graphics objects to PDF page and sign them. This class is used as a manager for fill-sign objects.
 * User can use this class to add/get/remove fill-sign objects (including cross mark, check mark, dot, line, round rectangle,
 * signature and initials signature) to PDF page.
 */
class FillSign FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for fill-sign object type.
   *
   * @details Values of this enumeration can be used alone.
   */
  typedef enum _FillSignObjectType {
    /** @brief Text fill-sign object.*/
    e_FillSignObjectTypeText = 0,
    /** @brief Cross mark fill-sign object.*/
    e_FillSignObjectTypeCrossMark = 1,
    /** @brief Check mark fill-sign object.*/
    e_FillSignObjectTypeCheckMark = 2,
    /** @brief Round rectangle fill-sign object.*/
    e_FillSignObjectTypeRoundRectangle = 3,
    /** @brief Line fill-sign object.*/
    e_FillSignObjectTypeLine = 4,
    /** @brief Dot fill-sign object.*/
    e_FillSignObjectTypeDot = 5,
    /** @brief Signature fill-sign object.*/
    e_FillSignObjectTypeSignature = 6,
    /** @brief Initials signature fill-sign object.*/
    e_FillSignObjectTypeInitialsSignature = 7
  } FillSignObjectType;
  

  /**
   * @brief Constructor, from a PDF page object.
   *
   * @details Please ensure input PDF page has been parsed successfully.
   *
   * @param[in] page  A valid PDF page object.
   */
  explicit FillSign(const PDFPage& page);

  /**
   * @brief Constructor, with another @link FillSign @endlink object.
   *
   * @param[in] other  Another object.
   */
  FillSign(const FillSign& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another @link FillSign @endlink object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  FillSign& operator = (const FillSign& other);

  /** @brief Destructor. */
  ~FillSign();

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another @link FillSign @endlink object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const FillSign& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another @link FillSign @endlink object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const FillSign& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Add a new fill-sign object (except text fill-sign object) to related PDF page (which is used in constructor).
   *
   * @details This function can be used to add fill-sign object except type @link FillSign::e_FillSignObjectTypeText @endlink.
   *          If you want to add a fill-sign object with type @link FillSign::e_FillSignObjectTypeText @endlink,
   *          please call function @link FillSign::AddTextObject @endlink instead.
   *          <ul>
   *          <li>If to add a fill-sign object with type @link FillSign::e_FillSignObjectTypeCrossMark @endlink,
   *              @link FillSign::e_FillSignObjectTypeCheckMark @endlink, @link FillSign::e_FillSignObjectTypeLine @endlink
   *              or @link FillSign::e_FillSignObjectTypeDot @endlink, the bigger value of input width and height will be
   *              used as both width and height for the new fill-sign object.
   *          </li>
   *          <li>If to add a fill-sign object with type @link FillSign::e_FillSignObjectTypeLine @endlink, input <i>height</i> is useless
   *              and will be ignored.
   *          </li>
   *          </ul>
   *
   * @param[in] type      Fill-sign type which is used to specify what kind of fill-sign object is to be added.
   *                      Please refer to values starting from @link FillSign::e_FillSignObjectTypeCrossMark @endlink
   *                      and this should be one of these values.
   * @param[in] point     Left-bottom point for new fill-sign object, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] width     Width for new fill-sign object.
   * @param[in] height    Height for new fill-sign object.
   * @param[in] rotation  Rotation status information. This rotation value includes the view rotation and page rotation property information.
   *                      Please refer to values starting from @link common::e_Rotation0 @endlink
   *                      and this should be one of these values except @link common::e_RotationUnknown @endlink.
   *
   * @return A new fill-sign object.
   */
  FillSignObject AddObject(FillSignObjectType type, const PointF& point, float width, float height,
                           common::Rotation rotation = common::e_Rotation0);

  /**
   * @brief Add a new text fill-sign object to related PDF page (which is used in constructor).
   *
   * @param[in] text_data           A text data array to be set to new text fill-sign object. For each text fill-sign object data,
   *                                <b>origin_position</b> of member <b>text_state</b> will not be used.
   * @param[in] point               Left-bottom point for new fill-sign object, in [PDF coordinate system] (@ref pdf::PDFPage).
   * @param[in] width               Width for new fill-sign object.
   * @param[in] height              Height for new fill-sign object.
   * @param[in] rotation            Rotation status information. This rotation value includes the view rotation and page rotation property information.
   *                                Please refer to values starting from @link common::e_Rotation0 @endlink
   *                                and this should be one of these values except @link common::e_RotationUnknown @endlink.
   * @param[in] is_comb_field_mode  A boolean value to decide whether for comb field mode or normal mode:
   *                                <ul>
   *                                <li><b>true</b> means to set input text data in comb field mode. For each text fill-sign object data,
   *                                    if <b>charspace</b> of member <b>text_state</b> is 0, default value 6.0f will be used instead.</li>
   *                                <li><b>false</b> means to set input text data in normal mode. For each text fill-sign object data,
   *                                    <b>charspace</b> of member <b>text_state</b> will not be used. </li>
   *                                </ul>
   *
   * @return A new fill-sign object.
   */
  FillSignObject AddTextObject(const TextFillSignObjectDataArray& text_data, const PointF& point, float width,
                               float height, common::Rotation rotation = common::e_Rotation0, bool is_comb_field_mode = false);

  /**
   * @brief Remove a specified fill-sign object.
   *
   * @details After adding a fill-sign object with type @link FillSign::e_FillSignObjectTypeSignature @endlink or
   *          @link FillSign::e_FillSignObjectTypeInitialsSignature @endlink, all the existed fill-sign objects
   *          which belong to the same PDF document cannot be removed. For this case, this function will
   *          return <b>false</b> if any existed fill-sign object is to be removed.
   *
   * @param[in] fillsign_object  A fill-sign object to be removed.
   *
   * @return <b>true</b> means success, while <b>false</b> means failed.
   */
  bool RemoveObject(const FillSignObject& fillsign_object);

  /**
   * @brief Get a fill-sign object by specified point in [PDF coordinate system] (@ref pdf::PDFPage). 
   *
   * @details After adding a fill-sign object with type @link FillSign::e_FillSignObjectTypeSignature @endlink or
   *          @link FillSign::e_FillSignObjectTypeInitialsSignature @endlink, all the existed fill-sign objects
   *          which belong to the same PDF document cannot be retrieved.
   *
   * @param[in] point  A specified point in [PDF coordinate system] (@ref pdf::PDFPage). 
   *
   * @return A fill-sign object.
   */
  FillSignObject GetObjectAtPoint(const PointF& point);

  /**
   * @brief Get a fill-sign object by specified point in device coordinate system.
   *
   * @details After adding the fill-sign object with type @link FillSign::e_FillSignObjectTypeSignature @endlink or
   *          @link FillSign::e_FillSignObjectTypeInitialsSignature @endlink,all the existed fill-sign objects
   *          which belong to the same PDF document cannot be retrieved.
   *
   * @param[in] point   A specified point in device coordinate system.
   * @param[in] matrix  A transform matrix from device coordinate system to [PDF coordinate system] (@ref pdf::PDFPage).
   *
   * @return A fill-sign object.
   */
  FillSignObject GetObjectAtDevicePoint(const PointF& point, const Matrix& matrix);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit FillSign(FS_HANDLE handle =  NULL);
};

/**
 * Class @link FillSignObject @endlink is the base class for all kinds of fill-sign object.
 * This class offers base functions to get type, to move a fill-sign object or to generate content
 * for a fill-sign object.
 */
class FillSignObject : public Base {
 public:
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit FillSignObject(FS_HANDLE handle);

#ifndef __EMSCRIPTEN_RENDER__
  /**
   * @brief Constructor, with another fill-sign object.
   *
   * @param[in] other  Another fill-sign object.
   */
  FillSignObject(const FillSignObject& other);
#endif

  /** @brief Constructor. */
  FillSignObject() {}

#ifndef __EMSCRIPTEN_RENDER__

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another fill-sign object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  FillSignObject& operator = (const FillSignObject& other);
#endif

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another fill-sign object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator ==(const FillSignObject& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another fill-sign object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
   bool operator != (const FillSignObject& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
   bool IsEmpty() const;

#ifndef __EMSCRIPTEN_RENDER__
  /** @brief Destructor. */
  virtual ~FillSignObject();
#endif

  /**
   * @brief Get fill-sign type
   *
   * @return Fill-sign type. Please refer to values starting from
   *         @link FillSign::e_FillSignObjectTypeText @endlink
   *         and this would be one of these values.
   */
  FillSign::FillSignObjectType GetType();

  /**
   * @brief Move current fill-sign object.
   *
   * @details <ul>
   *          <li>If to add a fill-sign object with type @link FillSign::e_FillSignObjectTypeCrossMark @endlink,
   *              @link FillSign::e_FillSignObjectTypeCheckMark @endlink, @link FillSign::e_FillSignObjectTypeLine @endlink
   *              or @link FillSign::e_FillSignObjectTypeDot @endlink, the bigger value of input width and height will be
   *              used as both width and height as the moving result.
   *          </li>
   *          <li>If to move a fill-sign object with type @link FillSign::e_FillSignObjectTypeLine @endlink, input <i>height</i> is useless
   *              and will be ignored.
   *          </li>
   *          <li>This function does not support to move a fill-sign object with @link FillSign::e_FillSignObjectTypeSignature @endlink 
   *              or @link FillSign::e_FillSignObjectTypeInitialsSignature @endlink. 
   *              For this case, exception @link e_ErrUnsupported @endlink will be thrown.
   *          </li>
   *          </ul>
   *
   * @param[in] point     New left-bottom point for current fill-sign object, in [PDF coordinate system] (@ref pdf::PDFPage). 
   * @param[in] width     New width for current fill-sign object.
   * @param[in] height    New height for current fill-sign object.
   * @param[in] rotation  Rotation status information. This rotation value includes the view rotation and page rotation property information.
   *                      Please refer to values starting from @link common::e_Rotation0 @endlink
   *                      and this should be one of these values except @link common::e_RotationUnknown @endlink.
   *
   * @return None.
   */
  void Move(const PointF& point, float width, float height, common::Rotation rotation = common::e_Rotation0);

  /**
   * @brief Get rectangle, in [PDF coordinate system] (@ref pdf::PDFPage).
   *
   * @return Fill-sign object rectangle.
   *         If there is no rectangle information, a RectF object with all 0 values would be returned.
   */
  RectF GetRect() const;

  /**
   * @brief Generate content for current fill-sign object.
   *
   * @details For fill-sign object with type @link FillSign::e_FillSignObjectTypeSignature @endlink or
   *          @link FillSign::e_FillSignObjectTypeInitialsSignature @endlink,
   *          function @link SignatureFillSignObject::SetBitmap @endlink should be called first.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool GenerateContent();

};

/**
 * Class @link TextFillSignObject @endlink is derived from class @link FillSignObject @endlink, and is used to represent a text fill-sign object.
 *
 * @see @link FillSignObject @endlink
 */
class TextFillSignObject FS_FINAL : public FillSignObject {
 public:
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] fillsign_object  Parent class object.
   */
  explicit TextFillSignObject(const FillSignObject& fillsign_object);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit TextFillSignObject(FS_HANDLE handle);

  /** @brief Constructor. */
  TextFillSignObject() {}

  /** @brief Destructor. */
  ~TextFillSignObject() {}

  /**
   * @brief Get text data array.
   *
   * @return A text data array.
   */
  TextFillSignObjectDataArray GetTextDataArray();

  /**
   * @brief Check whether current mode is comb field mode or not.
   *
   * @return <b>true</b> means current mode is comb field mode, while <b>false</b> means current mode is normal mode.
   */
  bool IsCombFieldMode();
};

 /**
 * Class @link SignatureFillSignObject @endlink is derived from class @link FillSignObject @endlink,
 * and is used to represent a signature or initiials signature fill-sign object.
 *
 * @see @link FillSignObject @endlink
 */
class SignatureFillSignObject FS_FINAL: public FillSignObject {
 public:
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] fillsign_object  Parent class object.
   */
  explicit SignatureFillSignObject(const FillSignObject& fillsign_object);

    // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit SignatureFillSignObject(FS_HANDLE handle);

   /** @brief Constructor. */
   SignatureFillSignObject() {}

  /** @brief Destructor. */
  ~SignatureFillSignObject() {}

  /**
   * @brief Check if current annotation is an initials signature fill-sign object.
   *
   * @return <b>true</b> means current object is an initials signature fill-sign object,
   *         while <b>false</b> means current object is a signature fill-sign object.
   */
  bool IsInitialsType();

  /**
   * @brief Set a bitmap.
   *
   * @param[in] bitmap  A bitmap to be set to current fill-sign object. This should be a valid bitmap object.
   *
   * @return None.
   */
  void SetBitmap(const common::Bitmap& bitmap);
};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_FILLSIGN_H_

