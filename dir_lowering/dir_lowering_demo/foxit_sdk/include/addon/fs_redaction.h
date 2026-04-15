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
 * @file fs_redaction.h
 * @brief Header file for redaction related definitions and classes.
 */

#ifndef FS_REDACTION_H_
#define FS_REDACTION_H_

#include "common/fs_common.h"
#include "pdf/fs_pdfdoc.h"
#include "pdf/fs_pdfpage.h"
#include "pdf/annots/fs_annot.h"

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
 * This class represents a callback object for applying redaction callback.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 */
class ApplyRedactionCallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;
  
  /**
   * @brief A callback function used to check whether to generate stream file or not.
   *
   * @return <b>true</b> means needs to generate stream file, while <b>false</b> not.
   */
  virtual bool NeedToGenerateStreamFile() = 0;
};

/**
 * Redacting a PDF file allows user to hide sensitive information while keeping the document's formatting.
 * This class can be used to mark page contents with redact annotations and apply redaction to
 * permanently remove (redact) visible text and images from PDF documents to protect confidential information
 * such as social security numbers.
 *
 * @see @link pdf::annots::Redact @endlink
 */
class Redaction FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, from a PDF document object.
   *
   * @param[in] document  A valid PDF document object.
   *
   * @note If module "Redaction" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using redaction related functions and
   *       this constructor will throw exception @link foxit::e_ErrNoRedactionModuleRight @endlink.
   */
  explicit Redaction(const pdf::PDFDoc& document);

  /**
   * @brief Constructor, with another redaction object.
   *
   * @param[in] other  Another redaction object.
   */
  Redaction(const Redaction& other);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Redaction(FS_HANDLE handle);
  /** @brief Destructor. */
  ~Redaction();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another redaction object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Redaction& operator = (const Redaction& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another redaction object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Redaction& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another redaction object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Redaction& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Mark page contents (text object, image object, and path object) which are to be redacted.
   *
   * @details This function is to add special marks (called redact annotation) to the specified rectangles areas,
   *          in order to redact page contents in these areas. Usually, the marked area has two appearance:
   *          <ul>
   *          <li>Normal appearance, which is used when the marked area is not interacting with the user.
   *              The border color (also known as stroke color) can be set by
   *              @link pdf::annots::Annot::SetBorderColor @endlink.
   *              The fill color can be set by @link pdf::annots::Redact::SetFillColor @endlink.
   *              The opcacity can be set by @link pdf::annots::Markup::SetOpacity @endlink.
   *          </li>
   *          <li>Rollover appearance, which is used when the user moves the cursor into the marked area without
   *              pressing the mouse button. The border color and fill color are the same and can be set by
   *              @link pdf::annots::Redact::SetApplyFillColor @endlink.
   *          </li>
   *          </ul>
   *          Once function @link Redaction::Apply @endlink is called, all the page contents under these marked area will be
   *          removed permanently and these marked areas will keep their rollover appearance all the time.<br>
   *
   * @param[in] page   A PDF page whose content will be marked.
   * @param[in] rects  Specify areas in the page to be marked. It should not be an empty array.
   *                   All the input rectangles will be treated as one redact annotation.
   *
   * @return A redact annotation object (along with a pop-up annotation by default), with default appearance:<br>
   *         apply fill color = black, border color = red, opacity = 1.0.
   */
  pdf::annots::Redact MarkRedactAnnot(const pdf::PDFPage& page, const RectFArray& rects);

  /**
   * @brief Enable file stream for image object during applying.
   *
   * @details Once this functions is called, the image object stream will be written into the temporary file 
   *          in the directory which is specified in <i>temp_directory_path</i>. 
   *          The temporary file must be kept before destroying document and will be automatically deleted during destroying document.
   *
   * @param temp_directory_path The temporary directory path. If it is empty, the temporary directory will be current path default.
   * @param apply_redaction_callback The callback for applying redaction
   *                                 which is implemented based on callback class @link addon::ApplyRedactionCallback @endlink.
   * 
   * @return None.
   */
  void EnableFileStream(const WString& temp_directory_path, ApplyRedactionCallback* apply_redaction_callback);

  /**
   * @brief Apply redaction in marked areas: remove the text or graphics under marked areas permanently.
   *
   * @details Once this functions is called, all the marked page content(text object, image object, and path object)
   *          in the document will be removed permanently. All the redact annotations which specify marked areas will
   *          be removed (with their pop-up annotations) and these marked areas will be filled by the color
   *          specified by @link pdf::annots::Redact::SetApplyFillColor @endlink.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  bool Apply();

  /**
   * @brief Start to apply redaction in marked areas: remove the text or graphics under marked areas permanently.
   * 
   * @details This function is similar to function @link Redaction::Apply @endlink, but this function will
   *          return a progressive object which can be used to do the redaction progressively.
   * 
   * @param[in] pause  A callback object which decides if the applying process should be paused.
   *                   This can be <b>NULL</b> which means not to pause during the applying process.
   *                   If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                   Default value: <b>NULL</b>.
   * 
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  common::Progressive StartApply(common::PauseCallback* pause = NULL);
};
}  // namespace addon
}  // namespace foxit

#endif  // FS_REDACTION_H_

