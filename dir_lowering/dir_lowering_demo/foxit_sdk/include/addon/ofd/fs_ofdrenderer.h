#if (defined(_WIN32) || defined(_WIN64))|| defined(__linux__)
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
 * @file fs_ofddoc.h
 * @brief Header file for OFD renderer related classes and methods.
 */

#ifndef FS_OFDRENDERER_H_
#define FS_OFDRENDERER_H_

#include "common/fs_common.h"
#include "common/fs_image.h"
#include "fs_ofdpage.h"

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
  * @brief OFD namespace.
  */
namespace ofd {
/**
 * This class is used to render an OFD page to a bitmap.
 * Please ensure @link common::Library::InitializeOFDEngine @endlink has been called successfully before using this class.
 *
 * @see @link common::Library @endlink
 */
class OFDRenderer FS_FINAL : public Base{
 public:
  /**
   * @brief Enumeration for rendering color mode.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ColorMode {
    /** @brief Normal color mode. */
    e_ColorModeNormal = 0,
    /** @brief Map gray/white/black color value to background/foreground; for other colors, no change. */
    e_ColorModeMappingGray = 1,
    /** @brief Map a color value to the color range defined by a background color and a foreground color. */
    e_ColorModeMapping = 2
  } ColorMode;
  
  /**
   * @brief Enumeration for OFD rendering content flags.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _ContentFlag {
    /** @brief If set, all content will be rendered. This value should be used alone. */
    e_ContentFlagAllContent = 0x00,
    /** @brief If set, page content will be rendered. */
    e_ContentFlagPage = 0x01,
    /** @brief If set, annotations will be rendered.(Excluding highlight annotation and stamp) */
    e_ContentFlagAnnot = 0x02,
    /** @brief If set, highlight annotations will be rendered. */
    e_ContentFlagHighLightAnnots = 0x04,
    /** @brief If set, stamp annotations will be rendered. */
    e_ContentFlagStampAnnots = 0x08
  } ContentFlag;
  

  /**
   * @brief Constructor.
   */
  OFDRenderer() {}

  /**
   * @brief Constructor, with a bitmap object.
   *
   * @param[in] bitmap  A bitmap object. It should not be an empty bitmap.
   */
  OFDRenderer(const common::Bitmap & bitmap);
  /**
   * @brief Constructor, with another renderer object.
   *
   * @param[in] other  Another renderer object.
   */
  OFDRenderer(const OFDRenderer& other);

  /** @brief Destructor. */
  ~OFDRenderer();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another OFD renderer object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  OFDRenderer& operator = (const OFDRenderer& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another OFD renderer object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const OFDRenderer& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another OFD renderer object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const OFDRenderer& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set the color mode.
   *
   * @param[in] color_mode  Color mode. Please refer to values starting from @link OFDRenderer::e_ColorModeNormal @endlink and
   *                        this should be one of these values.
   *                        The default value is @link OFDRenderer::e_ColorModeNormal @endlink.
   *
   * @return None.
   */
  void SetColorMode(ColorMode color_mode);

  /**
   * @brief Set the content flag.
   *
   * @param[in] content_flag  Content flag. Please refer to values starting from @link OFDRenderer::e_ContentFlagAllContent @endlink and
   *                          this can be one or a combination of these values.
   *                          The default value is @link OFDRenderer::e_ContentFlagAllContent @endlink.
   * 
   * @return None.
   */
  void SetContentFlag(uint32 content_flag);

  /**
   * @brief Start to render an OFD page.
   *
   * @details This function is used to start to render an OFD page.
   *
   * @param[in] page    An OFD page object. It should not be an empty object.
   * @param[in] matrix  A matrix for rendering the page, which is usually returned by function
   *                    @link OFDPage::GetDisplayMatrix @endlink.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  common::Progressive StartRender(const OFDPage& page, const Matrix& matrix);
};

}//namespace ofd
}//namespace addon
}//namespace foxit
#endif  // FS_OFDRENDERER_H_
#endif  // (defined(_WIN32) || defined(_WIN64)) || (defined(__linux__) && defined(__x86_64__) && !defined(__ANDROID__))
