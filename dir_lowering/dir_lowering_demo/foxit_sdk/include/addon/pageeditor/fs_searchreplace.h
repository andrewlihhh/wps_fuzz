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
 * @file fs_searchreplace.h
 * @brief Header file for text searching and replacing related definitions and classes.
 */

#ifndef FS_SEARCHREPLACE_H_
#define FS_SEARCHREPLACE_H_

#include "common/fs_common.h"
#include "pdf/fs_pdfdoc.h"
#include "pdf/fs_pdfpage.h"

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
 * @brief Page Editor namespace.
 */
namespace pageeditor {
/**
 * This class represents the find option which is used by @link TextSearchReplace @endlink objects.
 */
class FindOption FS_FINAL : public Object{
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] is_whole_word      A boolean value specifies that whether to match whole words only.<b>true</b> means to match whole words only, otherwise no.
   * @param[in] is_case_sensitive  A boolean value specifies that whether to match case.<b>true</b> means to match case, otherwise no.
   */
  FindOption(bool is_whole_word, bool is_case_sensitive) 
    : is_whole_word(is_whole_word)
    , is_case_sensitive(is_case_sensitive) {
  }

  /** @brief Constructor. */
  FindOption()
    : is_whole_word(false)
    , is_case_sensitive(false) {}

  /**
   * @brief Constructor, with another find option object.
   *
   * @param[in] find_option  Another find option object.
   */
  FindOption(const FindOption& find_option) {
    this->is_whole_word = find_option.is_whole_word;
    this->is_case_sensitive = find_option.is_case_sensitive;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another find option object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  FindOption& operator=(const FindOption& find_option) {
    this->is_whole_word = find_option.is_whole_word;
    this->is_case_sensitive = find_option.is_case_sensitive;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another find-option object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const FindOption& other) const {
    return (is_whole_word == other.is_whole_word && is_case_sensitive == other.is_case_sensitive);
  }
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another find-option object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const FindOption& other) const {
    return (is_whole_word != other.is_whole_word || is_case_sensitive != other.is_case_sensitive);
  }

  /**
  * @brief Set value.
  *
  * @param[in] is_whole_word      A boolean value specifies that whether to match whole words only. <b>true</b> means to match whole words only, otherwise no.
  * @param[in] is_case_sensitive  A boolean value specifies that whether to match case.<b>true</b> means to match case, otherwise no.
  *
  * @return None.
  */
  void Set(bool is_whole_word, bool is_case_sensitive) {
    this->is_whole_word = is_whole_word;
    this->is_case_sensitive = is_case_sensitive;
  }

  /** @brief A boolean value specifies that whether to match whole words only. <b>true</b> means to match whole words only, otherwise no. */
  bool is_whole_word;

  /** @brief A boolean value specifies that whether to match case.<b>true</b> means to match case, otherwise no.*/
  bool is_case_sensitive;
};
/**
 * This class represents a callback object for replacing.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 */
class ReplaceCallback {
 public:
  /**
   * @brief A callback function to verify whether need to replace text.
   *
   * @param[in] search_text             The search text. It will not be empty.
   * @param[in] replace_text            The text will be replaced with. It will not be empty.
   * @param[in] current_page_index      The current page index.Valid range: from 0 to (<i>count</i>-1). <i>count</i> is returned by function
   *                                    @link PDFDoc::GetPageCount @endlink for PDF document.
   * @param[in] text_rect_array         The found text rect array.
   *
   * @return <b>true</b> means to replace, while <b>false</b> means not.
   */
  virtual bool NeedToReplace(const WString& search_text, const WString& replace_text, int current_page_index, const RectFArray& text_rect_array) = 0;

  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

 protected:
  virtual ~ReplaceCallback() {}
};
/**
 * This class can be used for searching and replacing text.
 * Before using any class or methods in this module, please ensure Foxit PDF SDK has been initialized successfully
 * by function @link common::Library::Initialize @endlink with a key including "AdvEdit" module.
 *
 * @see @link common::Library @endlink
 */
class TextSearchReplace FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor.
   *
   * @param[in] doc         A valid PDF document object to be searched or replaced.
   *                        Currently, Foxit PDF SDK does not support to do the replacing for dynamic XFA document.
   *
   * @details This constructor is to construct a text search replace object.
   */
   TextSearchReplace(const foxit::pdf::PDFDoc& doc);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit TextSearchReplace(FS_HANDLE handle);

  /** @brief Destructor. */
  ~TextSearchReplace();

  /**
   * @brief Constructor, with another text search replace object.
   *
   * @param[in] other  Another text search replace object.
   */
  TextSearchReplace(const TextSearchReplace& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another text search replace object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TextSearchReplace& operator=(const TextSearchReplace& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another text search replace object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const TextSearchReplace& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another text search replace object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const TextSearchReplace& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means that current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set keywords and page index to do searching and replacing.
   *
   * @param[in] keywords    The text content to be replaced. It should not be an empty string.
   * @param[in] page_index  Index of the page that will be searched and replaced.Valid range: from 0 to (<i>count</i>-1). <i>count</i> is returned by function
   *                        @link PDFDoc::GetPageCount @endlink for PDF document.
   *                        This is only used for @link TextSearchReplace::ReplacePrev @endlink and @link TextSearchReplace::ReplaceNext @endlink.
   * @param[in] find_option The find option. It should be a valid find option object.
   *
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  void SetPattern(const WString& keywords, int page_index, const FindOption& find_option);

  /**
   * @brief Set replacing callback function.
   *
   * @param[in] replace_callback  The callback object for replacing.This should be implemented by user and
   *                              can be <b>NULL</b>. It means that the found text always needs to be replaced if it is <b>NULL</b>
   *
   * @return None.
   */
  void SetReplaceCallback(ReplaceCallback* replace_callback);

  /**
   * @brief Replace previous text with replacing text. 
   * 
   * @param[in] replace_text The text to be replaced with. This should not be an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means that <i>keywords</i> is not found. 
   *         It will still return <b>true</b> if users do not want to replace.
   */
  bool ReplacePrev(const WString& replace_text);

  /**
   * @brief Replace next text with replacing text. 
   * 
   * @param[in] replace_text The text to be replaced with. This should not be an empty string.
   *
   * @return <b>true</b> means success, while <b>false</b> means that <i>keywords</i> is not found.
   *         It will still return <b>true</b> if users do not want to replace.
   */
  bool ReplaceNext(const WString& replace_text);
};
}
}
}
#endif
