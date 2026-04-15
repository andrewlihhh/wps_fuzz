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
 * @brief Header file for OFD document related classes and methods.
 */

#ifndef FS_OFDDOC_H_
#define FS_OFDDOC_H_

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
 * This class is used to get information of an OFD document.
 * Please ensure @link common::Library::InitializeOFDEngine @endlink has been called successfully before using this class.
 *
 * @see @link common::Library @endlink
 */
class OFDDoc FS_FINAL : public Base{
 public:
  /**
   * @brief Constructor.
   */
  OFDDoc();

  /**
   * @brief Constructor, from an existing OFD file path.
   *
   * @param[in] path      A full path of an existing PDF file. It should not be an empty string.
   * @param[in] password  Password for the OFD file. It should be an empty string if the OFD file is not encrypted.
   *
   */
  OFDDoc(const wchar_t* path, const wchar_t* password);

  /**
   * @brief Constructor, with another OFD document object.
   *
   * @param[in] other  Another OFD document object.
   */
  OFDDoc(const OFDDoc& other);

  /**
   * @brief Release current OFD document object.
   *
   * @details Please call this function before @link common::Library::ReleaseOFDEngine @endlink to release
   *          current OFD document object.
   *
   * @return None.
   */
  void Release();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another OFD document object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  OFDDoc& operator=(const OFDDoc& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another OFD document object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const OFDDoc& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another OFD document object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const OFDDoc& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get page count of current OFD document.
   *
   * @return Page count of current OFD document.
   */
  int GetPageCount() const;

  /**
   * @brief Get OFD page object by index.
   *
   * @param[in] index  Index of the page. Valid range: from 0 to (<i>page_count</i>-1).
   *                   <i>page_count</i> returned by function @link OFDDoc::GetPageCount @endlink.
   *
   * @return OFD page object.
   */
  OFDPage GetPage(int index) const;
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit OFDDoc(FS_HANDLE handle);
};

}//namespace ofd
}//namespace addon
}//namespace foxit
#endif  // FS_OFDDOC_H_
#endif  // (defined(_WIN32) || defined(_WIN64)) || (defined(__linux__) && defined(__x86_64__) && !defined(__ANDROID__))
