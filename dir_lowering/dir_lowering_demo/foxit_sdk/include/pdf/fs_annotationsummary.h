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
 * @file fs_annotationsummary.h
 * @brief Header file for annotation summary related definitions and classes.
 */

#ifndef FS_ANNOTATIONSUMMARY_H_
#define FS_ANNOTATIONSUMMARY_H_

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
/**
 * This class represents a callback object which is used during summarizing annotation to allow user to decide some format/data.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 * An implemented @link AnnotationSummaryCallback @endlink object can be set to a AnnotationSummary object by function
 * @link AnnotationSummary::SetCallback @endlink.
 */
class AnnotationSummaryCallback {
 public:
  /**
   * @brief Enumeration for string ID used to specify the string or prefix in result document when summarizing annotation.
   *
   * @details Values of this enumeration can be used alone.
   */
  typedef enum _AnnotationSummaryStringID {
    /**
     * @brief Annotations summary string ID: specify the prefix when author information is outputed in result document.
     *        Default prefix is "Author:".
     */
    e_AnnotationSummaryStringIDAuthor = 0,
    /**
     * @brief Annotations summary string ID: specify the prefix when date information is outputed in result document.
     *        Default prefix is "Date:".
     */
    e_AnnotationSummaryStringIDDate = 1,
    /**
     * @brief Annotations summary string ID: specify the prefix when page information is outputed in result document.
     *        Default prefix is "Page:".
     */
    e_AnnotationSummaryStringIDPage = 2,
    /**
     * @brief Annotations summary string ID: specify the prefix when annotation type is outputed in result document.
     *        Default prefix is "Type:".
     */
    e_AnnotationSummaryStringIDType = 3,
    /** @brief Annotations summary string ID: specify the document title in result document. Default title is "Summary of comments:". */
    e_AnnotationSummaryStringIDDocumentTitle = 4,
    /**
     * @brief Annotations summary string ID: specify the prefix when page title is outputed in result document. Default string is "Page:".
     */
    e_AnnotationSummaryStringIDPageTitle = 5,
    /**
     * @brief Annotations summary string ID: specify the string used as content in result document when a page does not have any annotation.
     *        Default content is "No Annotations.".
     */
    e_AnnotationSummaryStringIDNoAnnotations = 6,
    /**
     * @brief Annotations summary string ID: specify the prefix when number information is outputed in result document.
     *        Default prefix is "Number:".
     */
    e_AnnotationSummaryStringIDNumber = 7,
    /**
     * @brief Annotations summary string ID: specify the prefix when subject information is outputed in result document.
     *        Default prefix is "Subject:".
     */
    e_AnnotationSummaryStringIDSubject = 8
  } AnnotationSummaryStringID;
  

  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief A callback function used to specify current locale ID.
   *
   * @details Locale ID is used to decide locale format for some information, such as date format.
   *
   * @return A locale ID. Please refer to values starting from @link common::e_LocaleIDUnspecified @endlink and
   *         this should be one of these values. If returned locale ID is not supported, Foxit PDF SDK will use
   *         value @link common::e_LocaleIDUnspecified @endlink by default.
   */
  virtual common::LocaleID GetCurrentLocaleID() = 0;

  /**
   * @brief A callback function used to specify the font name used locally.
   *
   * @details This function is very useful for user to specify the font used in result document.
   *
   * @return Font name string. If an empty string is returned, Foxit PDF SDK will use "Helvetica" as default font name.
   *         If returned font name is invalid, this name will not take any effect.
   */
  virtual WString GetLocalFontName() = 0;

  /**
   * @brief A callback function used to load a string in local language for a specified case.
   *
   * @details This function is very useful for user to use local language for some string content in result document.
   *          By using this function, user can re-write or translate default output strings to local language for specified case
   *          in result document. Default output strings for these specified cases can be found in comment for values
   *          starting from @link AnnotationSummaryCallback::e_AnnotationSummaryStringIDAuthor @endlink.<br>
   *          Specially, Foxit PDF SDK will add some necessary information/data to the format part in
   *          the result document, in order to make content in the result document more useful.
   *
   * @param[in] id  An annotation summary string ID to specify a summary case. Please refer to values starting
   *                from @link AnnotationSummaryCallback::e_AnnotationSummaryStringIDAuthor @endlink and this would be
   *                one of these values.
   *
   * @return A string used for the specified case.
   */
  virtual WString LoadString(AnnotationSummaryStringID id) = 0;

 protected:
  ~AnnotationSummaryCallback() {}
};

/**
 * This class represents settings for summarizing annotation. This would be used in class @link AnnotationSummary @endlink.
 *
 * @see @link AnnotationSummary @endlink
 */
class AnnotationSummarySettings FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for options used for annotation summary layout.
   *
   * @details Values of this enumeration can be used alone.
   */
  typedef enum _SummaryLayout {
    /** @brief If set, that means to layout document and annotations with connector lines on separate pages. */
    e_SummaryLayoutSeparatePagesWithLine = 0,
    /** @brief If set, that means to layout document and annotations with connector lines on single pages. */
    e_SummaryLayoutSinglePageWithLine = 1,
    /** @brief If set, that means to layout annotations only. */
    e_SummaryLayoutAnnotationOnly = 2,
    /** @brief If set, that means to layout document and annotations with sequence numbers on separate pages. */
    e_SummaryLayoutSeparatePagesWithSequenceNumber = 3,
    /** @brief If set, that means to layout document and annotations with sequence numbers on separate pages. */
    e_SummaryLayoutSinglePageWithSequenceNumber = 4
  } SummaryLayout;
  
  /**
   * @brief Enumeration for options used for sorting annotation in result document.
   *
   * @details Values of this enumeration can be used alone.
   */
  typedef enum _SortType {
    /** @brief If set, that means to sort annotation by author in result document. */
    e_TypeSortByAuthor = 0,
    /** @brief If set, that means to sort annotation by date in result document. */
    e_TypeSortByDate = 1,
    /** @brief If set, that means to sort annotation by page in result document. */
    e_TypeSortByPage = 2,
    /** @brief If set, that means to sort annotation by annotation type in result document. */
    e_TypeSortByAnnotationType = 3
  } SortType;
  
  /**
   * @brief Enumeration for options used for font size type in result document.
   *
   * @details Values of this enumeration can be used alone.
   */
  typedef enum _FontSizeType {
    /** @brief If set, that means to use small font size in result document. */
    e_FontSizeSmall = 0,
    /** @brief If set, that means to use medium font size in result document. */
    e_FontSizeMedium = 1,
    /** @brief If set, that means to use large font size in result document. */
    e_FontSizeLarge = 2
  } FontSizeType;
  

  /**
   * @brief Constructor, with parameters.
   */
  AnnotationSummarySettings();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit AnnotationSummarySettings(FS_HANDLE handle);

  /** @brief Destructor. */
  ~AnnotationSummarySettings();

  /**
   * @brief Constructor, with another annotation summary setting object.
   *
   * @param[in] other  Another annotation summary setting object.
   */
  AnnotationSummarySettings(const AnnotationSummarySettings& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another annotation summary setting object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  AnnotationSummarySettings& operator=(const AnnotationSummarySettings& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another annotation summary setting object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const AnnotationSummarySettings& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another annotation summary setting object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const AnnotationSummarySettings& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set summary layout type.
   *
   * @details For a newly constructed object, if this function is not called to set this option,
   *          that means to use @link AnnotationSummarySettings::e_SummaryLayoutSeparatePagesWithLine @endlink
   *          as the default value of this option.
   *
   * @param[in] type  Summary layout type. Please refer to values starting
   *                  from @link AnnotationSummarySettings::e_SummaryLayoutSeparatePagesWithLine @endlink
   *                  and this should be one of these values.
   *
   * @return None.
   */
  void SetSummaryLayout(SummaryLayout type);

  /**
   * @brief Set the option to decide to sort annotation by what.
   *
   * @details For a newly constructed object, if this function is not called to set this option,
   *          that means to use @link AnnotationSummarySettings::e_TypeSortByAnnotationType @endlink
   *          as the default value of this option.
   *
   * @param[in] type  Sorting type for summarizing annotations. Please refer to values starting
   *                  from @link AnnotationSummarySettings::e_TypeSortByAuthor @endlink
   *                  and this should be one of these values.
   *
   * @return None.
   */
  void SetSortType(SortType type);

  /**
   * @brief Set the font size type used in result document of annotation summary.
   *
   * @details For a newly constructed object, if this function is not called to set this option,
   *          that means to use @link AnnotationSummarySettings::e_FontSizeMedium @endlink
   *          as the default value of this option.
   *
   * @param[in] type  Font size type used in result document of annotation summary. Please refer to values starting
   *                  from @link AnnotationSummarySettings::e_FontSizeSmall @endlink
   *                  and this should be one of these values.
   *
   * @return None.
   */
  void SetFontSize(FontSizeType type);

  /**
   * @brief Set the option to decide which type of annotations will be summarized.
   *
   * @details For a newly constructed object, if this function is not called to set this option,
   *          that means to summarize annotation in all supported types.
   *
   * @param[in] type     Annotation type to decide which annotations is to be summarized.
   *                     Please refer to values starting from
   *                     @link annots::Annot::e_Note @endlink and this should be one of these values
   *                     except @link annots::Annot::e_Link @endlink, @link annots::Annot::e_PSInk @endlink,
   *                     @link annots::Annot::e_Sound @endlink, @link annots::Annot::e_Movie @endlink,
   *                     @link annots::Annot::e_Widget @endlink, @link annots::Annot::e_Screen @endlink,
   *                     @link annots::Annot::e_PrinterMark @endlink, @link annots::Annot::e_TrapNet @endlink,
   *                     @link annots::Annot::e_Watermark @endlink, @link annots::Annot::e_3D @endlink,
   *                     @link annots::Annot::e_Popup @endlink, @link annots::Annot::e_Redact @endlink.
   * @param[in] use_all  A boolean value to decide whether to summarize all the supported annotations in result document:
   *                     <ul>
   *                     <li><b>true</b> means to summarize annotations in all the supported types.
   *                         In this case, parameter <i>type</i> would be ignored.</li>
   *                     <li><b>false</b> means to only summarize annotations specified by parameter <i>type</i>.</li>
   *                     </ul>
   *
   * @return None.
   */
  void SetAnnotType(annots::Annot::Type type, bool use_all);

  /**
   * @brief Set the file title string when location of the document needs to be outputed in result document.
   *
   * @details If not set, an empty string will be used as default.
   *
   * @param[in] title  Summary title used in result document.
   *
   * @return None.
   */
  void SetFileTitle(const wchar_t* title);

  /**
   * @brief Set the page rectangle in result document.
   *
   * @details If not set, default rectangle (0.0, 0.0, 612.0, 792.0) will be used.
   *
   * @param[in] rect  Page rectangle used in result document.
   *
   * @return None.
   */
  void SetPageRect(const RectF& rect);

  /**
   * @brief Set the page margin used in result document.
   *
   * @details This value does not represent a rectangle. It just defines the left margin, bottom margin,
   *          right margin and top margin of a PDF page.
   *          If no margin value is set, Foxit PDF SDK will use a maring defined as (50.0, 50.0, 50.0, 50.0) as default.
   *
   * @param[in] margin  Page margin used in result document.
   *
   * @return None.
   */
  void SetPageMargin(const RectF& margin);

  /**
   * @brief Set starting page index.
   *
   * @details For a newly constructed object, if this function is not called, default value 0 will be used as the starting page index.
   *
   * @param[in] page_index  Page index to specify the starting page where summarizing operation starts.
   *                        Valid range: from 0 to (<i>count</i>-1). <i>count</i> is returned by function
   *                        @link PDFDoc::GetPageCount @endlink for the PDF document whose annotations are to be summarized.
   *                        This index will be checked when function @link AnnotationSummary::StartSummarize @endlink is called.
   *
   * @return None.
   */
  void SetStartPage(int page_index);

  /**
   * @brief Set ending page index.
   *
   * @details For a newly constructed object, if this function is not called, default value (<i>count</i>-1) will be used as the ending page index.
   *          <i>count</i> is returned by function @link PDFDoc::GetPageCount @endlink for the PDF document whose annotations are to be summarized.
   *
   * @param[in] page_index  Page index to specify the ending page where summarizing operation ends.
   *                        Valid range: from 0 to (<i>count</i>-1). <i>count</i> is returned by function
   *                        @link PDFDoc::GetPageCount @endlink for the PDF document whose annotations are to be summarized.
   *                        This index will be checked when function @link AnnotationSummary::StartSummarize @endlink is called.
   *
   * @return None.
   */
  void SetEndPage(int page_index);

  /**
   * @brief Set the flag to decide whether to output information of pages which have no annotation.
   *
   * @details or a newly constructed object, if this function is not called, default value <b>true</b> will be used.
   *
   * @param[in] enable  A boolean value to decide whether to output information of pages which have no annotation:
   *                    <b>true</b> means to output information of pages which have no annotation,
   *                    while <b>false</b> means not to output information of pages which have no annotation,
   *
   * @return None.
   */
  void EnableOutputNoAnnotationPage(bool enable);

  /**
   * @brief Set connector line color.
   *
   * @details This option will take effect when summary layout type is set @link AnnotationSummarySettings::e_SummaryLayoutSeparatePagesWithLine @endlink
   *          or @link AnnotationSummarySettings::e_SummaryLayoutSinglePageWithLine @endlink
   *          by function by @link AnnotationSummarySettings::SetSummaryLayout @endlink.
   *          If not set, default value 0x000000 will be used.
   *
   * @param[in] color  Connector line color. Format: 0xRRGGBB.
   *
   * @return None.
   */
  void SetConnectorLineColor(RGB color);

  /**
   * @brief Set connector line opacity.
   *
   * @details This option will take effect when summary layout type is set @link AnnotationSummarySettings::e_SummaryLayoutSeparatePagesWithLine @endlink
   *          or @link AnnotationSummarySettings::e_SummaryLayoutSinglePageWithLine @endlink
   *          by function by @link AnnotationSummarySettings::SetSummaryLayout @endlink.
   *          If not set, default value 1.0 will be used.
   *
   * @param[in] opacity  Connector line opacity. Valid range: from 0.0 to 1.0.
   *                     0.0 means full transparency and 1.0 means full opaque.
   *
   * @return None.
   */
  void SetConnectorLineOpacity(float opacity);

  /**
   * @brief Set the markup annotation thumbnail used in result document to indicates the type of annotation.
   *
   * @details Thumbnail bitmap does not use alpha channel. So user is recommended to set a bitmap
   *          without alpha channel to be the new thumbnail. If a bitmap with alpha channel is set,
   *          the new thumbnail will use white background by default. <br>
   *          If not set, no thumbnail will be used for corresponding annotation type.
   *
   * @param[in] type       Annotation type to decide whose thumbnail is to be set. Please refer to values starting from
   *                       @link annots::Annot::e_Note @endlink and this should be one of these values
   *                       except @link annots::Annot::e_Link @endlink, @link annots::Annot::e_PSInk @endlink,
   *                       @link annots::Annot::e_Sound @endlink, @link annots::Annot::e_Movie @endlink,
   *                       @link annots::Annot::e_Widget @endlink, @link annots::Annot::e_Screen @endlink,
   *                       @link annots::Annot::e_PrinterMark @endlink, @link annots::Annot::e_TrapNet @endlink,
   *                       @link annots::Annot::e_Watermark @endlink, @link annots::Annot::e_3D @endlink,
   *                       @link annots::Annot::e_Popup @endlink, @link annots::Annot::e_Redact @endlink.
   * @param[in] thumbnail  A bitmap used as thumbnail for an annotation type in result document.
   *                       This should be a valid bitmap. If the bitmap size is not 12*12,
   *                       the bitmap will be scaled to 12*12 when being used.
   *
   * @return None.
   */
  void SetAnnotThumbnail(annots::Annot::Type type, const common::Bitmap& thumbnail);
};

/**
 * This class can be used to summarize annotation and genearte a PDF file as the result document.
 */
class AnnotationSummary FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor.
   *
   * @param[in] document  A valid PDF document. It should has been loaded successfully.
   */
  AnnotationSummary(const pdf::PDFDoc& document);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit AnnotationSummary(FS_HANDLE handle);

  /** @brief Destructor. */
  ~AnnotationSummary();

  /**
   * @brief Constructor, with another annotation summary object.
   *
   * @param[in] other  Another annotation summary object.
   */
  AnnotationSummary(const AnnotationSummary& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another annotation summary object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  AnnotationSummary& operator=(const AnnotationSummary& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another annotation summary object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const AnnotationSummary& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another annotation summary object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const AnnotationSummary& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set a callback object for annotation summary.
   *
   * @details If this function is not called, that means no callback will be used.
   *
   * @param[in] callback  A @link AnnotationSummaryCallback @endlink object which is implemented by user.
   *                      User can change some information/data during summarizing annotations by this callback.
   *                      Please ensure that the callback object keeps valid until the life-cycle of current AnnotationSummary object ends.<br>
   *                      If this is <b>NULL</b>, that means to use default information/data.
   *
   * @return None.
   */
  void SetCallback(AnnotationSummaryCallback* callback);

  /**
   * @brief Start to summarize annotation.
   *
   * @details It may take a long time to summarize annotation, so Foxit PDF SDK uses a progressive process to do this.
   *          If related source PDF document does not have any annotation whose type is supported (please refer to comment of
   *          function @link AnnotationSummarySettings::SetAnnotType @endlink), or related source PDF document does not have any annotation,
   *          this function will throw exception @link foxit::e_ErrUnknown @endlink.
   *
   * @param[in] dest_file_path  A full path to save a PDF file as the result of annotation summary. This should not be an empty string.
   * @param[in] settings        Setting data used to summarize annotation.
   * @param[in] pause           Pause object which decides if the summarizing process needs to be paused.
   *                            This can be <b>NULL</b> which means not to pause during the parsing process.
   *                            If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                            Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  common::Progressive StartSummarize(const char* dest_file_path, const AnnotationSummarySettings& settings, common::PauseCallback* pause = NULL);

  /**
   * @brief Start to summarize annotation.
   *
   * @details It may take a long time to summarize annotation, so Foxit PDF SDK uses a progressive process to do this.
   *          If related source PDF document does not have any annotation whose type is supported (please refer to comment of
   *          function @link AnnotationSummarySettings::SetAnnotType @endlink), or related source PDF document does not have any annotation,
   *          this function will throw exception @link foxit::e_ErrUnknown @endlink.
   *
   * @param[in] dest_file_path  A full path to save a PDF file as the result of annotation summary. This should not be an empty string.
   * @param[in] settings        Setting data used to summarize annotation.
   * @param[in] pause           Pause object which decides if the summarizing process needs to be paused.
   *                            This can be <b>NULL</b> which means not to pause during the parsing process.
   *                            If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                            Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  common::Progressive StartSummarize(const wchar_t* dest_file_path, const AnnotationSummarySettings& settings, common::PauseCallback* pause = NULL);

  /**
   * @brief Start to summarize annotation.
   *
   * @details It may take a long time to summarize annotation, so Foxit PDF SDK uses a progressive process to do this.
   *          If related source PDF document does not have any annotation whose type is supported (please refer to comment of
   *          function @link AnnotationSummarySettings::SetAnnotType @endlink), or related source PDF document does not have any annotation,
   *          this function will throw exception @link foxit::e_ErrUnknown @endlink.
   *
   * @param[in] dest_file  A @link common::file::WriterCallback @endlink object which is implemented by user to
   *                       store the data of annotation summary to a PDF file as result in custom method.
   * @param[in] settings   Setting data used to summarize annotation.
   * @param[in] pause      Pause object which decides if the summarizing process needs to be paused.
   *                       This can be <b>NULL</b> which means not to pause during the parsing process.
   *                       If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                       Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  common::Progressive StartSummarize(foxit::common::file::WriterCallback* dest_file, const AnnotationSummarySettings& settings, foxit::common::PauseCallback* pause = NULL);
};

}  // namespace pdf
}  // namespace foxit
#endif  // FS_ANNOTATIONSUMMARY_H_
