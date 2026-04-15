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
 * @file fs_ofdpage.h
 * @brief Header file for OFD page related classes and methods.
 */

#ifndef FS_OFDPAGE_H_
#define FS_OFDPAGE_H_

#include "common/fs_common.h"

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
 * This class is used to get information of an OFD page.
 * Please ensure @link common::Library::InitializeOFDEngine @endlink has been called successfully before using this class.
 * 
 * @see @link common::Library @endlink
 */
class OFDPage FS_FINAL : public Base{
 public:
  /** @brief Constructor. */
  OFDPage();

  /**
   * @brief Constructor, with another OFD page object.
   */
  OFDPage(const OFDPage& other);

  /**
   * @brief Release current OFD page object.
   * 
   * @details Please call this function before @link  common::Library::ReleaseOFDEngine @endlink to release
   *          current OFD page object.
   * 
   * @return None.
   */
  void Release();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another OFD page object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  OFDPage& operator=(const OFDPage& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another OFD page object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const OFDPage& other) const;

  /**
   * @brief Not equal operator.
   * 
   * @param[in] other  Another OFD page object. This function will check if current object is not equal to this one.
   * 
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const OFDPage& other) const;

  /**
   * @brief Check whether current object is empty or not.
   * 
   * @details When the current object is empty, that means current object is useless.
   * 
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get page width (unit is 1/72 inch).
   * 
   * @return Page width.
   */
  float GetWidth() const;

  /**
   * @brief Get page height (unit is 1/72 inch).
   * 
   * @return Page height.
   */
  float GetHeight() const;

  /**
   * @brief Get display matrix.
   * 
   * @details This function is used to get a matrix for displaying the page.
   * 
   * @param[in] left    Left position of the display area.
   * @param[in] top     Top position of the display area.
   * @param[in] width   Width of the display area.
   * @param[in] height  Height of the display area.
   * @param[in] rotate  Rotation of the display area. Please refer to values starting from @link common::e_Rotation0 @endlink and
   *                    this should be one of these values.
   * 
   * @return A matrix for displaying the page.
   */
  Matrix GetDisplayMatrix(int left, int top, int width, int height, common::Rotation rotate);
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit OFDPage(FS_HANDLE handle);
};

}  // namespace ofd
}  // namespace addon
}  // namespace foxit

#endif  // FS_OFDPAGE_H_

#endif  // #if (defined(_WIN32) || defined(_WIN64)) || (defined(__linux__) && defined(__x86_64__) && !defined(__ANDROID__))
