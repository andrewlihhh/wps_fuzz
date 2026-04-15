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
 * @file fs_formcombination.h
 * @brief Header file for form combination related definitions and classes.
 */

#ifndef FS_FORMCOMBINATION_H_
#define FS_FORMCOMBINATION_H_

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
 * This class represents form file information. Form file can be PDF, FDF, XML or XFDF format.
 */
class FormFileInfo FS_FINAL : public Base{
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @details This constructor will check the validition of input file.
   *
   * @param[in] file_path  File path of a form file. This should be a PDF, FDF, XML or XFDF file.
   * @param[in] password   The password of input file specified by parameter <i>file_path</i>.
   *                       This is only useful when input file is a PDF file. If input file is not a PDF file or
   *                       input PDF file does not have any password, please pass an empty string.
   */
  FormFileInfo(const wchar_t* file_path, const WString& password);

  /**
   * @brief Constructor, with parameters.
   *
   * @details This constructor will check the validition of input file.
   *
   * @param[in] reader_callback  The reader file callback of a file, which is to be combined with other files.
   *                             And it only supports PDF, FDF, XML and XFDF files.
   * @param[in] password         The password of input file specified by parameter <i>reader_callback</i>.
   *                             This is only useful when input file is a PDF file. If input file is not a PDF file or
   *                             input PDF file does not have any password, please pass an empty string.
   * @param[in] file_name        File name of input file which is specified by parameter <i>reader_callback</i>.
   *                             This name will be written into target file when current information object is used in combination.
   *                             This can be an empty string.
   */
  FormFileInfo(foxit::common::file::ReaderCallback* reader_callback, const WString& password, const wchar_t* file_name);

  /** @brief Destructor. */
  ~FormFileInfo();

  /**
   * @brief Constructor, with another information object.
   *
   * @param[in] other  Another information object.
   */
  FormFileInfo(const FormFileInfo& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another information object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  FormFileInfo& operator=(const FormFileInfo& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another information object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const FormFileInfo& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another information object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const FormFileInfo& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit FormFileInfo(FS_HANDLE handle);
};

/** This class represents an array of @link FormFileInfo @endlink objects. */
FSDK_DEFINE_ARRAY(FormFileInfoArray, FormFileInfo)

/**
 * This class is used to combine form data from several files and export combined form data to spreadsheet.
 */
class FormCombination FS_FINAL : public Base{
 public:
  /**
   * @brief Combine form data and export these data to a CSV file.
   *
   * @param[in] form_file_array  A form file information array. This array contains information of source form files whose form data are to be combined.
   * @param[in] dest_csv_file    A full path of a CSV file, to which combined result will be saved to. This should not be an empty string.
   * @param[in] append           A boolean value used to decide whether combined form data is appended to the CSV file if the CSV file exists:
   *                             <b>true</b> means to append combined form data to an existed CSV file, while <b>false</b> means not.
   *
   * @return None.
   */
  static void CombineFormsToCSV(const FormFileInfoArray& form_file_array, const wchar_t* dest_csv_file, bool append);

  /**
   * @brief Combine form data and export these data to a CSV file.
   *
   * @param[in] form_file_array  A form file information array. This array contains information of source form files whose form data are to be combined.
   * @param[in] dest_csv_file    A @link common::file::StreamCallback @endlink object which is implemented by user to save combined form data to a CSV file.
   *                             This should not be <b>NULL</b>. Please do not use append mode in writing callback functions.
   * @param[in] append           A boolean value used to decide whether combined form data is appended to the CSV file if the CSV file exists:
   *                             <b>true</b> means to append combined form data to an existed CSV file, while <b>false</b> means not.
   *
   * @return None.
   */
  static void CombineFormsToCSV(const FormFileInfoArray& form_file_array, foxit::common::file::StreamCallback* dest_csv_file, bool append);
};
}
}
#endif
