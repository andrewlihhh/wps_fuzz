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
 * @file fs_combination.h
 * @brief Header file for PDF file combination related definitions and classes.
 */

#ifndef FS_COMBINATION_H_
#define FS_COMBINATION_H_

#include "common/fs_common.h"
#include "pdf/fs_pdfdoc.h"

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
/** This class represents information of source PDF file which is to be combined with other PDF files. */
class CombineDocumentInfo FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @details This constructor does not check the validity of input PDF file and
   *          the check will be done in function @link Combination::StartCombineDocuments @endlink.
   *
   * @param[in] file_path  File path of a PDF file, which is to be combined with other PDF files.
   * @param[in] password   Owner password of PDF file which is specified by parameter <i>file_path</i>.
   */
  CombineDocumentInfo(const WString& file_path, const WString& password);

  /**
   * @brief Constructor, with parameters.
   *
   * @details This constructor does not check the validity of input PDF file and
   *          the check will be done in function @link Combination::StartCombineDocuments @endlink.
   *
   * @param[in] doc  A valid PDF document object which represents a PDF file to be combined with other PDF files.
   *                 Please ensure input PDF document object have been loaded; otherwise unknown error may occur later
   *                 when current information object is used.
   */
  CombineDocumentInfo(const PDFDoc& doc);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit CombineDocumentInfo(FS_HANDLE handle);

  /** @brief Destructor. */
  ~CombineDocumentInfo();

  /**
   * @brief Constructor, with another information object.
   *
   * @param[in] other  Another information object.
   */
  CombineDocumentInfo(const CombineDocumentInfo& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another information object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  CombineDocumentInfo& operator=(const CombineDocumentInfo& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another information object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const CombineDocumentInfo& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another information object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const CombineDocumentInfo& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set the title of a new parent bookmark for the root bookmark of related source PDF document in combined result file.
   *
   * @details This function is to set the bookmark title for a new bookmark in combined result file,
   *          if option value @link Combination::e_CombineDocsOptionBookmark @endlink is used for combination
   *          and related source PDF file has any bookmark. The new bookmark will be used as a parent bookmark and
   *          root bookmark of related source PDF doucment will be inserted to be the child node of the new parent bookmark
   *          in combined result PDF file.<br>
   *          If no bookmark title is set or an empty title is set, GSDK will generate a bookmark title automatically
   *          during combination process which is started by function @link Combination::StartCombineDocuments @endlink.
   *
   * @param[in] bookmark_title  Title of a new parent bookmark which is used in combined result PDF file.
   *
   * @return None.
   */
  void SetBookmarkTitle(const WString& bookmark_title);

  /**
   * @brief Set the name of the PDF file, which will be combined with other PDF files.
   *
   * @details This function is invalid if the constructor @link CombineDocumentInfo::CombineDocumentInfo @endlink with a file path parameter is called.
   *          If option value @link Combination::e_CombineDocsOptionOCProperties @endlink is used for combination
   *          and the PDF file to be combined has multiple layers, then the PDF file name to be set 
   *          will be shown on the root node of the combined PDF file's layers.
   *
   * @param[in] pdf_file_name  The name of the PDF file, which will be combined with other PDF files.
   *
   * @return None.
   */
  void SetPDFFileName(const WString& pdf_file_name);
};

/** This class represents an array of @link CombineDocumentInfo @endlink objects. */
FSDK_DEFINE_ARRAY(CombineDocumentInfoArray, CombineDocumentInfo)

/**
 * This class can be used to combine several PDF files into one PDF file.
 */
class Combination FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for options used for combining PDF files.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _CombineDocsOptions {
    /** @brief If set, that means bookmarks of source PDF files will be outputted to combined result PDF file. */
    e_CombineDocsOptionBookmark = 0x0001,
    /** @brief If set, that means fields with same name will be renamed in combined result PDF file. */
    e_CombineDocsOptionAcroformRename = 0x0002,
    /** @brief If set, that means structure trees of source PDF files will be outputted to combined result PDF file. */
    e_CombineDocsOptionStructrueTree = 0x0004,
    /** @brief If set, that means output intents of source PDF files will be outputted to combined result PDF file. */
    e_CombineDocsOptionOutputIntents = 0x0008,
    /** @brief If set, that means "OCProperties" of source PDF files will be outputted to combined result PDF file. */
    e_CombineDocsOptionOCProperties = 0x0010,
    /** @brief If set, that means "MarkInfo" of source PDF files will be outputted to combined result PDF file. */
    e_CombineDocsOptionMarkInfos = 0x0020,
    /** @brief If set, that means page labels of source PDF files will be outputted to combined result PDF file. */
    e_CombineDocsOptionPageLabels = 0x0040,
    /**
     * @brief If set, that means "Dests" name trees and "EmbeddedFiles" name trees of source PDF files will
     *        be outputted to combined result PDF file.
     */
    e_CombineDocsOptionNames = 0x0080,
    /**
     * @brief If set, that means object streams will be used to generate combined result PDF file in order to
     *        reduce result file size.
     */
    e_CombineDocsOptionObjectStream = 0x0100,
    /** @brief If set, that means duplicate stream objects from source PDF files will be outputted to combined result PDF file. */
    e_CombineDocsOptionDuplicateStream = 0x0200
  } CombineDocsOptions;
  

  /**
   * @brief Start to combine PDF files.
   *
   * @details It may take a long time to combining documents, so Foxit PDF SDK uses a progressive process to do this.
   *          This function does not support to combine XFA document.
   *
   * @param[in] dest_file_path  A full path to save the combined result PDF file. This should not be an empty string.
   * @param[in] document_array  An information array which represents information of source PDF files which are to be combined.
   * @param[in] options         Options for combining PDF documents. Please refer to values starting from
   *                            @link Combination::e_CombineDocsOptionBookmark @endlink and this can be one or a combination of these values.
   *                            0 means no option is used.
   * @param[in] pause           Pause object which decides if the combining process needs to be paused.
   *                            This can be <b>NULL</b> which means not to pause during the parsing process.
   *                            If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                            Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  static common::Progressive StartCombineDocuments(const char* dest_file_path, const CombineDocumentInfoArray& document_array, uint32 options, common::PauseCallback* pause = NULL);

  /**
   * @brief Start to combine PDF files.
   *
   * @details It may take a long time to combining documents, so Foxit PDF SDK uses a progressive process to do this.
   *          This function does not support to combine XFA document.
   *
   * @param[in] dest_file_path  A full path to save the combined result PDF file. This should not be an empty string.
   * @param[in] document_array  An information array which represents information of source PDF files which are to be combined.
   * @param[in] options         Options for combining PDF documents. Please refer to values starting from
   *                            @link Combination::e_CombineDocsOptionBookmark @endlink and this can be one or a combination of these values.
   *                            0 means no option is used.
   * @param[in] pause           Pause object which decides if the combining process needs to be paused.
   *                            This can be <b>NULL</b> which means not to pause during the parsing process.
   *                            If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                            Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  static common::Progressive StartCombineDocuments(const wchar_t* dest_file_path, const CombineDocumentInfoArray& document_array, uint32 options, common::PauseCallback* pause = NULL);

  /**
   * @brief Start to combine PDF files.
   *
   * @details It may take a long time to combining documents, so Foxit PDF SDK uses a progressive process to do this.
   *          This function does not support to combine XFA document.
   *
   * @param[in] dest_file       A @link common::file::WriterCallback @endlink object which is implemented by user to
   *                            store the data of combined result PDF file in custom method.
   * @param[in] document_array  An information array which represents information of source PDF files which are to be combined.
   * @param[in] options         Options for combining PDF documents. Please refer to values starting from
   *                            @link Combination::e_CombineDocsOptionBookmark @endlink and this can be one or a combination of these values.
   *                            0 means no option is used.
   * @param[in] pause           Pause object which decides if the combining process needs to be paused.
   *                            This can be <b>NULL</b> which means not to pause during the parsing process.
   *                            If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                            Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  static common::Progressive StartCombineDocuments(foxit::common::file::WriterCallback* dest_file, const CombineDocumentInfoArray& document_array, uint32 options, foxit::common::PauseCallback* pause = NULL);
};

}  // namespace pdf
}  // namespace foxit
#endif  // FS_COMBINATION_H_

