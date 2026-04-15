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
* @file fs_taggedpdf.h
* @brief Header file for PDF tag related definitions and classes.
*/

#ifndef FS_TAGGEDPDF_H_
#define FS_TAGGEDPDF_H_

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
 * @brief Accessibility namespace.
 */
namespace accessibility {
/**
 * This class represents a callback object used to tag PDF document.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user
 * in derived class. User can also re-write the virtual functions in this class in custom way.
 */
class TaggedPDFCallback {
 public:
  /**
   * @brief Enumeration for report category type used for tagged PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ReportCategory {
    /** @brief Report category type: region. */
    e_ReportCategoryRegion = 0,
    /** @brief Report category type: artifact. */
    e_ReportCategoryArtifact = 1,
    /** @brief Report category type: paragraph. */
    e_ReportCategoryParagraph = 2,
    /** @brief Report category type: list item. */
    e_ReportCategoryListItem = 3,
    /** @brief Report category type: figure. */
    e_ReportCategoryFigure = 4,
    /** @brief Report category type: table. */
    e_ReportCategoryTable = 5,
    /** @brief Report category type: table row. */
    e_ReportCategoryTableRow = 6,
    /** @brief Report category type: table header. */
    e_ReportCategoryTableHeader = 7,
    /** @brief Report category type: toc item. */
    e_ReportCategoryTocItem = 8
  } ReportCategory;
  
  /**
   * @brief Enumeration for report confidence used for tag PDF document.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ReportConfidence {
    /** @brief Report confidence: high. */
    e_ReportConfidenceHigh = 0,
    /** @brief Report confidence: medium high. */
    e_ReportConfidenceMediumHigh = 1,
    /** @brief Report confidence: medium. */
    e_ReportConfidenceMedium = 2,
    /** @brief Report confidence: medium low. */
    e_ReportConfidenceMediumLow = 3,
    /** @brief Report confidence: low. */
    e_ReportConfidenceLow = 4
  } ReportConfidence;
  

  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief A callback function used to get the tagged PDF document result information, triggered when the document will be tagged.
   *
   * @details This function is very useful for user to get the tagged PDF document result information.
   *
   * @param[in] category    The report category for tagged PDF. Please refer to values starting
   *                        from @link TaggedPDFCallback::e_ReportCategoryRegion @endlink and this would be
   *                        one of these values.
   * @param[in] confidence  The report confidence for tagged PDF. Please refer to values starting
   *                        from @link TaggedPDFCallback::e_ReportConfidenceHigh @endlink and this would be
   *                        one of these values.
   * @param[in] page_index  The page index of current report item belongs to.
   * @param[in] rect        The rectangle of current report item.
   *
   * @return None.
   */
  virtual void Report(ReportCategory category, ReportConfidence confidence, int page_index, const RectF& rect) = 0;

 protected:
  ~TaggedPDFCallback() {}
};

/**
 * This class represents settings for a tagged PDF document.The tagged PDF means that only tagging information for PDF structure here.
 * Before using any class or methods in this module, please ensure Foxit PDF SDK has been initialized successfully
 * by function @link common::Library::Initialize @endlink with a key including "Accessibility" module.
 *
 * @see @link common::Library @endlink
 */
class TaggedPDF FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor.
   *
   * @param[in] doc  A valid PDF document object to be tagged.
   *
   * @details This constructor is to construct a tagged PDF object with default settings.
   */
  TaggedPDF(const foxit::pdf::PDFDoc& doc);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit TaggedPDF(FS_HANDLE handle);

  /** @brief Destructor. */
  ~TaggedPDF();

  /**
   * @brief Constructor, with another tagged PDF object.
   *
   * @param[in] other  Another tagged PDF object.
   */
  TaggedPDF(const TaggedPDF& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another tagged PDF object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TaggedPDF& operator=(const TaggedPDF& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another tagged PDF object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const TaggedPDF& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another tagged PDF object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const TaggedPDF& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set a callback object for tagged PDF.
   *
   * @details If this function is not called, that means no callback will be used.
   *
   * @param[in] callback  A @link TaggedPDFCallback @endlink object which is implemented by user.
   *                      User can change some information/data during tagged PDF document by this callback.
   *                      Please ensure that the callback object keeps valid until the life-cycle of current
   *                      tagged PDF object ends.<br>
   *                      If this is <b>NULL</b>, that means to use default information/data.
   *
   * @return None.
   */
  void SetCallback(TaggedPDFCallback* callback);

  /**
   * @brief Start to auto tag the given PDF document with specified tagged settings.
   *
   * @details If user wants to get specific tag results when tagging document process, please refer to function
   *          @link TaggedPDF::SetCallback @endlink about callback function
   *          @link TaggedPDFCallback::Report @endlink.
   *
   * @param[in] pause  Pause object which decides if the auto tagging process needs to be paused.
   *                   This can be <b>NULL</b> which means not to pause during the tagging process.
   *                   If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                   Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  common::Progressive StartTagDocument(common::PauseCallback* pause = NULL);

  /**
   * @brief Get the count of figures in tagged document, excluding the decorative figures.
   *
   * @details The function is only used for a tagged PDF document. Please call function
   *          @link pdf::PDFDoc::IsTaggedPDF @endlink to check current PDF document whether
   *          is a tagged PDF document.
   *
   * @return The count of figures.
   */
  int GetFigureCount();

  /**
   * @brief Decorate the figure.The decorative figure can not set alternate text.
   *
   * @details The function is only used for a tagged PDF document. Please call function
   *          @link pdf::PDFDoc::IsTaggedPDF @endlink to check current PDF document whether
   *          is a tagged PDF document.
   *
   * @param[in] figure_index  The index of figure. Valid range: from 0 to (<i>count</i>-1).
   *                          <i>count</i> is returned by function @link TaggedPDF::GetFigureCount @endlink.
   *
   * @return <b>true</b> means decorate figure successed, while <b>false</b> means not.
   */
  bool SetAsDecorativeFigure(int figure_index);

  /**
   * @brief Set figure alternate text.
   *
   * @details The alternate text is the human-readable text, the PDF documents can be enhanced by providing alternate text for images,
   *          formulas, or other items that do not translate naturally into text.
   *          The function is only used for a tagged PDF document. Please call function
   *          @link pdf::PDFDoc::IsTaggedPDF @endlink to check current PDF document whether
   *          is a tagged PDF document.
   *
   * @param[in] figure_index  The index of figure. Valid range: from 0 to (<i>count</i>-1).
   *                          <i>count</i> is returned by function @link TaggedPDF::GetFigureCount @endlink.
   *
   * @param[in] alternate_text  The alternative descriptions text.
   *
   * @return None.
   */
  void SetFigureAlternateText(int figure_index, const wchar_t*  alternate_text);

  /**
   * @brief Get the alternate text of the figure.
   *
   * @details The alternate text is the human-readable text, the PDF documents can be enhanced by providing alternate text for images,
   *          formulas, or other items that do not translate naturally into text.
   *          The function is only used for a tagged PDF document. Please call function
   *          @link pdf::PDFDoc::IsTaggedPDF @endlink to check current PDF document whether
   *          is a tagged PDF document.
   *
   * @param[in] figure_index  The index of figure. Valid range: from 0 to (<i>count</i>-1).
   *                          <i>count</i> is returned by function @link TaggedPDF::GetFigureCount @endlink.
   *
   * @return The alternative descriptions text.
   */
  WString GetFigureAlternateText(int figure_index);

  /**
   * @brief Get the rectangle of figure.
   *
   * @details The function is only used for a tagged PDF document. Please call function
   *          @link pdf::PDFDoc::IsTaggedPDF @endlink to check current PDF document whether
   *          is a tagged PDF document.
   *
   * @param[in] figure_index  The index of figure. Valid range: from 0 to (<i>count</i>-1).
   *                          <i>count</i> is returned by function @link TaggedPDF::GetFigureCount @endlink.
   *
   * @return The figure rectangle.If there is any error, this function will return an empty rectangle.
   */
  RectF GetFigureRect(int figure_index);

  /**
   * @brief Get the figure page index by the figure index.
   *
   * @details The function is only used for a tagged PDF document. Please call function
   *          @link pdf::PDFDoc::IsTaggedPDF @endlink to check current PDF document whether 
   *          is a tagged PDF document.
   *
   * @param[in] figure_index  The index of figure. Valid range: from 0 to (<i>count</i>-1).
   *                          <i>count</i> is returned by function @link TaggedPDF::GetFigureCount @endlink.
   *
   * @return The page index. Valid value would starts from 0. If there is any error, this function will return -1.
   */
  int GetFigurePageIndex(int figure_index);

};

}
}
}
#endif
