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
 * @file fs_convert.h
 * @brief Header file for PDF conversion related definitions and classes.
 */

#ifndef FS_CONVERT_H_
#define FS_CONVERT_H_

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
 * @brief Conversion namespace.
 */
namespace conversion {
/** This class represents setting data used for converting HTML to PDF. */
class HTML2PDFSettingData  FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for page mode used for converting HTML to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _HTML2PDFPageMode {
    /** @brief Single page mode.*/
    e_PageModeSinglePage  = 0,
    /** @brief Multiple page mode. */
    e_PageModeMultiplePage = 1
  } HTML2PDFPageMode;
  
  /**
   * @brief Enumeration for scaling mode used for converting HTML to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _HTML2PDFScalingMode {
    /** @brief Scaling mode: Fixed page with no scale. In this mode, the text size of HTML content will not be changed.*/
    e_ScalingModeNone  = 0,
    /** @brief Page scaling: Scale. It means HTML content will be scaled to fit PDF page size. In this mode, the text size may be changed. */
    e_ScalingModeScale = 1,
    /** @brief Page scaling: Enlarge. It means PDF page will be enlarged to HTML content size. In this mode, the text size of HTML content will not be changed.*/
    e_ScalingModeEnlarge = 2
  } HTML2PDFScalingMode;
  
  /**
   * @brief Enumeration for encoding format used for converting HTML to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _HTML2PDFEncodingFormat {
    /** @brief Encoding foramt: Default.The encoding format will be automatically detected in chromium.*/
    e_EncodingFormatDefault  = 0,
    /** @brief Encoding foramt: "ASCII".*/
    e_EncodingFormatASCII = 1,
    /** @brief Encoding foramt: "Latin2".*/
    e_EncodingFormatLatin2 = 2,
    /** @brief Encoding foramt: "Latin3".*/
    e_EncodingFormatLatin3  = 3,
    /** @brief Encoding foramt: "Latin4".*/
    e_EncodingFormatLatin4 = 4,
    /** @brief Encoding foramt: "Latin5".*/
    e_EncodingFormatLatin5  = 5,
    /** @brief Encoding foramt: "Latin6".*/
    e_EncodingFormatLatin6 = 6,
    /** @brief Encoding foramt: "ISO-8859-5".*/
    e_EncodingFormatISO_8859_5 = 7,
    /** @brief Encoding foramt: "Arabic".*/
    e_EncodingFormatArabic = 8,
    /** @brief Encoding foramt: "Greek".*/
    e_EncodingFormatGreek = 9,
    /** @brief Encoding foramt: "Hebrew".*/
    e_EncodingFormatHebrew = 10,
    /** @brief Encoding foramt: "EUC-JP".*/
    e_EncodingFormatEUC_JP = 11,
    /** @brief Encoding foramt: "SJS".*/
    e_EncodingFormatSJS  = 12,
    /** @brief Encoding foramt: "JIS".*/
    e_EncodingFormatJIS = 13,
    /** @brief Encoding foramt: "BIG5".*/
    e_EncodingFormatBIG5 = 14,
    /** @brief Encoding foramt: "GB".*/
    e_EncodingFormatGB  = 15,
    /** @brief Encoding foramt: "EUC-CN".*/
    e_EncodingFormatEUC_CN = 16,
    /** @brief Encoding foramt: "KSC".*/
    e_EncodingFormatKSC = 17,
    /** @brief Encoding foramt: "Unicode".*/
    e_EncodingFormatUnicode  = 18,
    /** @brief Encoding foramt: "EUC".*/
    e_EncodingFormatEUC = 19,
    /** @brief Encoding foramt: "CNS".*/
    e_EncodingFormatCNS = 20,
    /** @brief Encoding foramt: "BIG5-CP950".*/
    e_EncodingFormatBIG5_CP950  = 21,
    /** @brief Encoding foramt: "ASCII-7-bit".*/
    e_EncodingFormatASCII_7_bit = 22,
    /** @brief Encoding foramt: "KOI8R".*/
    e_EncodingFormatKOI8R = 23,
    /** @brief Encoding foramt: "CP852".*/
    e_EncodingFormatCP852 = 24,
    /** @brief Encoding foramt: "CP866".*/
    e_EncodingFormatCP866 = 25,
    /** @brief Encoding foramt: "CP874".*/
    e_EncodingFormatCP874 = 26,
    /** @brief Encoding foramt: "CP932".*/
    e_EncodingFormatCP932 = 27,
    /** @brief Encoding foramt: "CP1250".*/
    e_EncodingFormatCP1250  = 28,
    /** @brief Encoding foramt: "CP1251".*/
    e_EncodingFormatCP1251  = 29,
    /** @brief Encoding foramt: "CP1252".*/
    e_EncodingFormatCP1252 = 30,
    /** @brief Encoding foramt: "CP1253".*/
    e_EncodingFormatCP1253  = 31,
    /** @brief Encoding foramt: "CP1254".*/
    e_EncodingFormatCP1254 = 32,
    /** @brief Encoding foramt: "CP1255".*/
    e_EncodingFormatCP1255 = 33,
    /** @brief Encoding foramt: "CP1256".*/
    e_EncodingFormatCP1256  = 34,
    /** @brief Encoding foramt: "CP1257".*/
    e_EncodingFormatCP1257  = 35,
    /** @brief Encoding foramt: "KOI8U".*/
    e_EncodingFormatKOI8U = 36,
    /** @brief Encoding foramt: "ISO-8859-15".*/
    e_EncodingFormatISO_8859_15 = 37,
    /** @brief Encoding foramt: "ISO-8859-11".*/
    e_EncodingFormatISO_8859_11 = 38,
    /** @brief Encoding foramt: "ISO-8859-8-I".*/
    e_EncodingFormatISO_8859_8_I = 39,
    /** @brief Encoding foramt: "VISUAL".*/
    e_EncodingFormatVISUAL  = 40,
    /** @brief Encoding foramt: "CSN_369103".*/
    e_EncodingFormatCSN_369103 = 41,
    /** @brief Encoding foramt: "ISO-8859-13".*/
    e_EncodingFormatISO_8859_13 = 42,
    /** @brief Encoding foramt: "ISO-2022-KR".*/
    e_EncodingFormatISO_2022_KR  = 43,
    /** @brief Encoding foramt: "GBK".*/
    e_EncodingFormatGBK = 44,
    /** @brief Encoding foramt: "GB18030".*/
    e_EncodingFormatGB18030 = 45,
    /** @brief Encoding foramt: "BIG5_HKSCS".*/
    e_EncodingFormatBIG5_HKSCS  = 46,
    /** @brief Encoding foramt: "ISO_2022_CN".*/
    e_EncodingFormatISO_2022_CN = 47,
    /** @brief Encoding foramt: "TSCII".*/
    e_EncodingFormatTSCII = 48,
    /** @brief Encoding foramt: "TAM".*/
    e_EncodingFormatTAM  = 49,
    /** @brief Encoding foramt: "TAB".*/
    e_EncodingFormatTAB = 50,
    /** @brief Encoding foramt: "JAGRAN".*/
    e_EncodingFormatJAGRAN = 51,
    /** @brief Encoding foramt: "MACINTOSH".*/
    e_EncodingFormatMACINTOSH  = 52,
    /** @brief Encoding foramt: "UTF7".*/
    e_EncodingFormatUTF7 = 53,
    /** @brief Encoding foramt: "BHASKAR".*/
    e_EncodingFormatBHASKAR = 54,
    /** @brief Encoding foramt: "HTCHANAKYA".*/
    e_EncodingFormatHTCHANAKYA  = 55,
    /** @brief Encoding foramt: "UTF-16BE".*/
    e_EncodingFormatUTF_16BE = 56,
    /** @brief Encoding foramt: "UTF-16LE".*/
    e_EncodingFormatUTF_16LE = 57,
    /** @brief Encoding foramt: "UTF-32BE".*/
    e_EncodingFormatUTF_32BE  = 58,
    /** @brief Encoding foramt: "UTF-32LE".*/
    e_EncodingFormatUTF_32LE = 59,
    /** @brief Encoding foramt: "X-BINARYENC".*/
    e_EncodingFormatX_BINARYENC = 60,
    /** @brief Encoding foramt: "HZ-GB-2312".*/
    e_EncodingFormatHZ_GB_2312  = 61,
    /** @brief Encoding foramt: "X-UTF8UTF8".*/
    e_EncodingFormatX_UTF8UTF8 = 62,
    /** @brief Encoding foramt: "X-TAM-ELANGO".*/
    e_EncodingFormatX_TAM_ELANGO = 63,
    /** @brief Encoding foramt: "X-TAM-LTTMBARANI".*/
    e_EncodingFormatX_TAM_LTTMBARANI = 64,
    /** @brief Encoding foramt: "X-TAM-SHREE".*/
    e_EncodingFormatX_TAM_SHREE = 65,
    /** @brief Encoding foramt: "X-TAM-TBOOMIS".*/
    e_EncodingFormatX_TAM_TBOOMIS = 66,
    /** @brief Encoding foramt: "X-TAM-TMNEWS".*/
    e_EncodingFormatX_TAM_TMNEWS = 67,
    /** @brief Encoding foramt: "X-TAM-WEBTAMIL".*/
    e_EncodingFormatX_TAM_WEBTAMIL  = 68,
    /** @brief Encoding foramt: "X-KDDI-Shift_JIS".*/
    e_EncodingFormatX_KDDI_Shift_JIS = 69,
    /** @brief Encoding foramt: "X-DoCoMo-Shift_JIS".*/
    e_EncodingFormatX_DoCoMo_Shift_JIS = 70,
    /** @brief Encoding foramt: "X-SoftBank-Shift_JIS".*/
    e_EncodingFormatX_SoftBank_Shift_JIS  = 71,
    /** @brief Encoding foramt: "X-KDDI-ISO-2022-JP".*/
    e_EncodingFormatX_KDDI_ISO_2022_JP = 72,
    /** @brief Encoding foramt: "X-SoftBank-ISO-2022-JP".*/
    e_EncodingFormatX_SoftBank_ISO_2022_JP = 73
  } HTML2PDFEncodingFormat;
  
  /**
   * @brief Enumeration for media style used for converting HTML to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _HTML2PDFMediaStyle {
    /** @brief Media style: screen. It means PDF page will be displayed in screen media style.*/
    e_MediaStyleScreen  = 0,
    /** @brief Media style: print. It means PDF page will be displayed in print media style.*/
    e_MediaStylePrint  = 1
  } HTML2PDFMediaStyle;
  

  /** @brief Constructor. */
  HTML2PDFSettingData()
    : page_width(0)
    , page_height(0)
    , is_to_page_scale(false)
    , page_margin(0.0f, 0.0f, 0.0f, 0.0f)
    , rotate_degrees(common::e_Rotation0)
    , is_convert_link(false)
    , is_generate_tag(false)
    , page_mode(e_PageModeSinglePage)
    , to_generate_bookmarks(false)
    , scaling_mode(e_ScalingModeScale)
    , encoding_format(e_EncodingFormatDefault)
    , to_render_images(true) 
    , to_remove_underline_for_link(false)
    , to_set_headerfooter(false)
    , headerfooter_title(L"")
    , headerfooter_url(L"")
    , bookmark_root_name(L"")
    , to_resize_objects(false) 
    , to_print_background(true)
    , to_optimize_tag_tree(false)
    , media_style(e_MediaStyleScreen)
    , to_load_active_content(false)
    , to_disable_sandbox(true)
    , to_use_blacklist(false)
    , to_hide_header(false)
    , to_hide_footer(false)
    , to_deny_local_file_access(false) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] page_width                     The page width used for the converted PDF document (unit is 1/72 inch).
   * @param[in] page_height                    The page height used for the converted PDF document (unit is 1/72 inch). This would be ignored if page mode
   *                                           @link HTML2PDFSettingData::e_PageModeSinglePage @endlink is used.
   * @param[in] is_to_page_scale               (Deprecated)Used to decide whether to scale the converted PDF page or not.
   * @param[in] page_margin                    The page margin used for converted PDF document.
   * @param[in] is_convert_link                Used to decide whether the web link should be converted or not.
   * @param[in] rotate_degrees                 The rotation degree used for the converted PDF page.Please refer to values starting from @link common::e_Rotation0 @endlink and
   *                                           this should be one of these values. 
   * @param[in] is_generate_tag                Used to decide whether the tag should be generated or not.
   * @param[in] page_mode                      The page mode used for the converting. Please refer to values starting from
   *                                           @link HTML2PDFSettingData::e_PageModeSinglePage @endlink and this should be one of these values.
   * @param[in] to_generate_bookmarks          Used to decide whether bookmarks should be generated or not.
   * @param[in] scaling_mode                   The scaling mode used for the converted PDF document. Please refer to values starting from @link HTML2PDFSettingData::e_ScalingModeNone @endlink and
   *                                           this should be one of these values. Default value:@link HTML2PDFSettingData::e_ScalingModeScale @endlink.
   * @param[in] encoding_format                The HTML encoding format Please refer to values starting from @link HTML2PDFEncodingFormat::e_EncodingFormatDefault @endlink and
   *                                           this should be one of these values.
   * @param[in] to_render_images               Whether to render images or not.
   * @param[in] to_remove_underline_for_link   Whether to remove underline decoration for link or not.
   * @param[in] to_set_headerfooter            Whether to set header-footer or not.
   * @param[in] headerfooter_title             The header-footer title which is content for center header.
   * @param[in] headerfooter_url               The header-footer url which is content for left footer.
   * @param[in] bookmark_root_name             The bookmark's root name.
   * @param[in] to_resize_objects              Whether to enable the Javascripts related resizing of the objects during rendering process.
   * @param[in] to_print_background            Whether to print background or not.
   * @param[in] to_optimize_tag_tree           Whether to optimize tag tree or not.
   * @param[in] media_style                    The media style used for the converted PDF document. Please refer to values starting from @link HTML2PDFSettingData::e_MediaStyleScreen @endlink and
   *                                           this should be one of these values.
   * @param[in] to_load_active_content         Whether to load active content or not.
   * @param[in] to_disable_sandbox             Whether to disable sandbox or not.
   * @param[in] to_use_blacklist               Whether to use blacklist or not.
   * @param[in] to_hide_header                 Whether to hide header or not.
   * @param[in] to_hide_footer                 Whether to hide footer or not.
   * @param[in] to_deny_local_file_access      Whether to deny local file access or not.
   *
   * @return None.
   */
  HTML2PDFSettingData(float page_width, float page_height, bool is_to_page_scale, RectF page_margin,
      bool is_convert_link, common::Rotation rotate_degrees, bool is_generate_tag, HTML2PDFPageMode page_mode, bool to_generate_bookmarks, HTML2PDFScalingMode scaling_mode,
      HTML2PDFEncodingFormat encoding_format, bool to_render_images, bool to_remove_underline_for_link, bool to_set_headerfooter, const wchar_t* headerfooter_title, 
      const wchar_t* headerfooter_url, const wchar_t* bookmark_root_name, bool to_resize_objects, bool to_print_background, bool to_optimize_tag_tree,
      HTML2PDFMediaStyle media_style, bool to_load_active_content, bool to_disable_sandbox, bool to_use_blacklist,
      bool to_hide_header, bool to_hide_footer, bool to_deny_local_file_access) {
    this->page_width = page_width;
    this->page_height = page_height;
    this->is_to_page_scale = is_to_page_scale;
    this->page_margin = page_margin;
    this->is_convert_link = is_convert_link;
    this->rotate_degrees = rotate_degrees;
    this->is_generate_tag = is_generate_tag;
    this->page_mode = page_mode;
    this->to_generate_bookmarks = to_generate_bookmarks;
    this->scaling_mode = scaling_mode;
    this->encoding_format = encoding_format;
    this->to_render_images = to_render_images;
    this->to_remove_underline_for_link = to_remove_underline_for_link;
    this->to_set_headerfooter = to_set_headerfooter;
    this->headerfooter_title = headerfooter_title;
    this->headerfooter_url = headerfooter_url;
    this->bookmark_root_name = bookmark_root_name;
    this->to_resize_objects = to_resize_objects;
    this->to_print_background = to_print_background;
    this->to_optimize_tag_tree = to_optimize_tag_tree;
    this->media_style = media_style;
    this->to_load_active_content = to_load_active_content;
    this->to_disable_sandbox = to_disable_sandbox;
    this->to_use_blacklist = to_use_blacklist;
    this->to_hide_header = to_hide_header;
    this->to_hide_footer = to_hide_footer;
    this->to_deny_local_file_access = to_deny_local_file_access;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another HTML-to-PDF setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  HTML2PDFSettingData &operator = (const HTML2PDFSettingData& data) {
    page_width = data.page_width;
    page_height = data.page_height;
    is_to_page_scale = data.is_to_page_scale;
    page_margin = data.page_margin;
    is_convert_link = data.is_convert_link;
    rotate_degrees = data.rotate_degrees;
    is_generate_tag = data.is_generate_tag;
    page_mode = data.page_mode;
    to_generate_bookmarks = data.to_generate_bookmarks;
    scaling_mode = data.scaling_mode;
    encoding_format = data.encoding_format;
    to_render_images = data.to_render_images;
    to_remove_underline_for_link = data.to_remove_underline_for_link;
    to_set_headerfooter = data.to_set_headerfooter;
    headerfooter_title = data.headerfooter_title;
    headerfooter_url = data.headerfooter_url;
    bookmark_root_name = data.bookmark_root_name;
    to_resize_objects = data.to_resize_objects;
    to_print_background = data.to_print_background;
    to_optimize_tag_tree = data.to_optimize_tag_tree;
    media_style = data.media_style;
    to_load_active_content = data.to_load_active_content;
    to_disable_sandbox = data.to_disable_sandbox;
    to_use_blacklist = data.to_use_blacklist;
    to_hide_header = data.to_hide_header;
    to_hide_footer = data.to_hide_footer;
    to_deny_local_file_access = data.to_deny_local_file_access;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] page_width                    The page width used for the converted PDF document (unit is 1/72 inch).
   * @param[in] page_height                   The page height used for the converted PDF document (unit is 1/72 inch). This would be ignored if page mode
   *                                          @link HTML2PDFSettingData::e_PageModeSinglePage @endlink is used.
   * @param[in] is_to_page_scale              (Deprecated)Used to decide whether to scale the converted PDF page or not.
   * @param[in] page_margin                   The page margin used for converted PDF document.
   * @param[in] is_convert_link               Used to decide whether the web link should be converted or not.
   * @param[in] rotate_degrees                The rotation degree used for the converted PDF page.Please refer to values starting from @link common::e_Rotation0 @endlink and
   *                                          this should be one of these values.
   * @param[in] is_generate_tag               Used to decide whether the tag should be generated or not.
   * @param[in] page_mode                     The page mode used for the converting. Please refer to values starting from
   *                                          @link HTML2PDFSettingData::e_PageModeSinglePage @endlink and this should be one of these values.
   * @param[in] to_generate_bookmarks         Used to decide whether bookmarks should be generated or not.
   * @param[in] scaling_mode                  The scaling mode used for the converted PDF document. Please refer to values starting from @link HTML2PDFSettingData::e_ScalingModeNone @endlink and
   *                                          this should be one of these values.Default value:@link HTML2PDFSettingData::e_PageScalingScale @endlink.
   * @param[in] encoding_format               The HTML encoding format Please refer to values starting from @link HTML2PDFEncodingFormat::e_EncodingFormatDefault @endlink and
   *                                          this should be one of these values.
   * @param[in] to_render_images              Whether to render images or not.
   * @param[in] to_remove_underline_for_link  Whether to remove underline decoration for link or not.
   * @param[in] to_set_headerfooter           Whether to set header-footer or not.
   * @param[in] headerfooter_title            The header-footer title which is content for center header.
   * @param[in] headerfooter_url              The header-footer url which is content for left footer.
   * @param[in] bookmark_root_name            The bookmark's root name.
   * @param[in] to_resize_objects             Whether to enable the Javascripts related resizing of the objects during rendering process.
   * @param[in] to_print_background           Whether to print background or not.
   * @param[in] to_optimize_tag_tree          Whether to optimize tag tree or not.
   * @param[in] media_style                   The media style used for the converted PDF document. Please refer to values starting from @link HTML2PDFSettingData::e_MediaStyleScreen @endlink and
   *                                          this should be one of these values.
   * @param[in] to_load_active_content        Whether to load active content or not.
   * @param[in] to_disable_sandbox            Whether to disable sandbox or not.
   * @param[in] to_use_blacklist              Whether to use blacklist or not.
   * @param[in] to_hide_header                Whether to hide header or not.
   * @param[in] to_hide_footer                Whether to hide footer or not.
   * @param[in] to_deny_local_file_access     Whether to deny local file access or not.
   *
   * @return None.
   */
  void Set(float page_width, float page_height, bool is_to_page_scale, RectF page_margin,
      bool is_convert_link, common::Rotation rotate_degrees, bool is_generate_tag, HTML2PDFPageMode page_mode, bool to_generate_bookmarks, HTML2PDFScalingMode scaling_mode,
      HTML2PDFEncodingFormat encoding_format, bool to_render_images, bool to_remove_underline_for_link, bool to_set_headerfooter, 
      const wchar_t* headerfooter_title, const wchar_t* headerfooter_url, const wchar_t* bookmark_root_name, bool to_resize_objects, bool to_print_background, bool to_optimize_tag_tree,
      HTML2PDFMediaStyle media_style, bool to_load_active_content, bool to_disable_sandbox, bool to_use_blacklist,
      bool to_hide_header, bool to_hide_footer, bool to_deny_local_file_access) {
    this->page_width = page_width;
    this->page_height = page_height;
    this->is_to_page_scale = is_to_page_scale;
    this->page_margin = page_margin;
    this->is_convert_link = is_convert_link;
    this->rotate_degrees = rotate_degrees;
    this->is_generate_tag = is_generate_tag;
    this->page_mode = page_mode;
    this->to_generate_bookmarks = to_generate_bookmarks;
    this->scaling_mode = scaling_mode;
    this->encoding_format = encoding_format;
    this->to_render_images = to_render_images;
    this->to_remove_underline_for_link = to_remove_underline_for_link;
    this->to_set_headerfooter = to_set_headerfooter;
    this->headerfooter_title = headerfooter_title;
    this->headerfooter_url = headerfooter_url;
    this->bookmark_root_name = bookmark_root_name;
    this->to_resize_objects = to_resize_objects;
    this->to_print_background = to_print_background;
    this->to_optimize_tag_tree = to_optimize_tag_tree;
    this->media_style = media_style;
    this->to_load_active_content = to_load_active_content;
    this->to_disable_sandbox = to_disable_sandbox;
    this->to_use_blacklist = to_use_blacklist;
    this->to_hide_header = to_hide_header;
    this->to_hide_footer = to_hide_footer;
    this->to_deny_local_file_access = to_deny_local_file_access;
  }

  /**
   * @brief The page width used for the converted PDF document (unit is 1/72 inch).
   *
   * @details This value minus the sum of the left and right margins must be bigger than 16.
   */
  float page_width;

  /**
   * @brief The page height used for the converted PDF document (unit is 1/72 inch).
   *
   * @details This value minus the sum of the top and bottom margins must be bigger than 16.
   *
   * @note The page height would be ignored if page mode @link HTML2PDFSettingData::e_PageModeSinglePage @endlink is used.
   */
  float page_height;

  /**
   * @deprecated Current property has been deprecated since Foxit PDF SDK 8.2. This property will not have any effect on converting PDF any more.
   *             For scaling mode, please refer to <i>scaling_mode</i>.
   *
   * @brief Used to decide whether to scale the converted PDF page or not. 
   */
  bool is_to_page_scale;

  /**
   * @brief The page margin used for converted PDF document.
   *
   * @note This value does not represent a rectangle. It just defines the left margin, bottom margin,
   *       right margin and top margin of a PDF page.
   */
  RectF page_margin;

  /** 
   * @brief The rotation degree used for the converted PDF page.Please refer to values starting from @link common::e_Rotation0 @endlink and
   *        this should be one of these values. 
   */
  common::Rotation rotate_degrees;

  /** @brief Used to decide whether the web link should be converted or not. */
  bool is_convert_link;

  /** @brief Used to decide whether the tag should be generated or not. */
  bool is_generate_tag;

  /**
   * @brief The page mode used for the converting. Please refer to values starting from @link HTML2PDFSettingData::e_PageModeSinglePage @endlink and
   *        this should be one of these values.
   */
  HTML2PDFPageMode page_mode;

  /** @brief Used to decide whether bookmarks should be generated or not. */
  bool to_generate_bookmarks;

  /**
   * @brief The scaling mode used for the converted PDF document. Please refer to values starting from @link HTML2PDFSettingData::e_ScalingModeNone @endlink and
   *        this should be one of these values.
   */
  HTML2PDFScalingMode scaling_mode;

  /** @brief The HTML encoding format Please refer to values starting from @link HTML2PDFSettingData::e_EncodingFormatDefault @endlink and
   *        this should be one of these values.
   */
  HTML2PDFEncodingFormat encoding_format;

  /** @brief Used to decide whether to render images or not. */
  bool to_render_images;

  /** @brief Used to decide whether to remove underline decoration for link. */
  bool to_remove_underline_for_link;

  /** @brief Used to decide whether to set header-footer or not. */
  bool to_set_headerfooter;

  /** @brief The header-footer title which is content for center header.*/
  foxit::WString headerfooter_title;

  /** @brief The header-footer url which is content for left footer.*/
  foxit::WString headerfooter_url;

  /** @brief The bookmark's root name.*/
  foxit::WString bookmark_root_name;

  /** @brief Whether to enable the Javascripts related resizing of the objects during rendering process.*/
  bool to_resize_objects;

  /** @brief Used to decide whether to print background or not.*/
  bool to_print_background;

  /** @brief Used to decide whether to optimize tag tree or not.*/
  bool to_optimize_tag_tree;

  /**
   * @brief The media style used for the converted PDF document. Please refer to values starting from @link HTML2PDFSettingData::e_MediaStyleScreen @endlink and
   *        this should be one of these values.
   */
  HTML2PDFMediaStyle media_style;

  /**
   * @brief Used to decide whether to load active content or not.
   *
   * @details This parameter is useful for some optimized web pages. These web page will not load the entire content.
   *          When the user scrolls down the page, the contents of the web page will be loaded when they are displayed on the user screen.
   *          <b>true</b> means to load the active content that has not been loaded by the web page, and <b>false</b> means not. Default:<b>false</b>.
   */
  bool to_load_active_content;

  /**
   * @brief Used to decide whether to disable sandbox or not.
   *
   * @details <b>true</b> means to disable sandbox, and <b>false</b> means not. Default: <b>true</b>.
   */
  bool to_disable_sandbox;

  /**
   * @brief Used to decide whether to use blacklist or not.
   *
   * @details This parameter is useful for checking all accessed URLs during the HTML to the PDF conversion process.<br>
   *          During the conversion of specific URL, there could be many third-party websites that are accessed by the conversion process (images, CSS styles, requests from JavaScripts, and others). <br>
   *          All of these accesses will be checked against the blacklist record. There is a prepared switch that enables the blacklist functionality in the converter. 
   *          <b>true</b> means to use the blacklist, and <b>false</b> means not. Default: <b>false</b>.
   *          Blacklist JSON is located next to the fxhtml2pdf application and its name must be "blacklist.json".It consist from three parts of records:
   *          <ul>
   *          <li>list of domains.</li>
   *          <li>list of IPs.</li>
   *          <li>list of IP ranges.</li>
   *          </ul>
   *          "blacklist.json" Examples:
   *          <pre>
   *          {"Domains":[
   *               "xxx.com",
   *               "xxx.com"
   *               ]
   *           ,
   *          "IPs":["1.2.3.4","5.6.7.8"]
   *          ,
   *          "IPsegments":[{"16":["104.193.88.0","104.193.88.100"]},{"16":["20.0.0.1","20.0.0.10"]}]
   *          }
   *          </pre>
   */
  bool to_use_blacklist;

  /** @brief Used to decide whether to hide header or not. It can not support on Linux x86 platform.*/
  bool to_hide_header;

  /** @brief Used to decide whether to hide footer or not. It can not support on Linux x86 platform.*/
  bool to_hide_footer;

  /** @brief Used to decide whether to deny local file access or not during converting html file. 
   *         It can not support on Linux x86 platform.
   * 
   * @details <b>true</b> means that prevents the HTML file from accessing any local files outside of its own directory.
   *          <b>false</b> means that allows the HTML file to access to any local file paths. 
   *          Default value: <b>false</b>.
   */
  bool to_deny_local_file_access;
};

/** This class represents setting data used for converting TXT to PDF. */
class TXT2PDFSettingData FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  TXT2PDFSettingData()
    : page_width(0)
    , page_height(0)
    , text_size(0)
    , text_color(0xFF000000)
    , linespace(0)
    , is_break_page(false) {
  }

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] page_width     Page width used for the converted PDF document.
   * @param[in] page_height    Page height used for the converted PDF document.
   * @param[in] page_margin    Page margin used for converted PDF document.
   * @param[in] font           Font object used for converted PDF document.
   * @param[in] text_size      Font size used for converted PDF document.
   * @param[in] text_color     Font color used for converted PDF document.
   * @param[in] linespace      Line space used for converted PDF document.
   * @param[in] is_break_page  Used to decide whether to insert a page break in converted PDF document when meeting character 0x0c.
   *
   * @return None.
   */
  TXT2PDFSettingData(float page_width, float page_height, RectF page_margin, const common::Font& font, float text_size,
                     ARGB text_color, float linespace, bool is_break_page) {
    this->page_width = page_width;
    this->page_height = page_height;
    this->page_margin = page_margin;
    this->font = font;
    this->text_size = text_size;
    this->text_color = text_color;
    this->linespace = linespace;
    this->is_break_page = is_break_page;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another TXT-to-PDF setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TXT2PDFSettingData& operator=(const TXT2PDFSettingData& data) {
    page_width = data.page_width;
    page_height = data.page_height;
    page_margin = data.page_margin;
    font = data.font;
    text_size = data.text_size;
    text_color = data.text_color;
    linespace = data.linespace;
    is_break_page = data.is_break_page;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] page_width     Page width used for the converted PDF document.
   * @param[in] page_height    Page height used for the converted PDF document.
   * @param[in] page_margin    Page margin used for converted PDF document.
   * @param[in] font           Font object used for converted PDF document.
   * @param[in] text_size      Font size used for converted PDF document.
   * @param[in] text_color     Font color used for converted PDF document.
   * @param[in] linespace      Line space used for converted PDF document.
   * @param[in] is_break_page  Used to decide whether to insert a page break in converted PDF document when meeting character 0x0c.
   *
   * @return None.
   */
  void Set(float page_width, float page_height, RectF page_margin, const common::Font& font, float text_size,
           ARGB text_color, float linespace, bool is_break_page) {
    this->page_width = page_width;
    this->page_height = page_height;
    this->page_margin = page_margin;
    this->font = font;
    this->text_size = text_size;
    this->text_color = text_color;
    this->linespace = linespace;
    this->is_break_page = is_break_page;
  }

  /** @brief Page width used for the converted PDF document. */
  float page_width;

  /** @brief Page height used for the converted PDF document. */
  float page_height;

  /**
   * @brief Page margin used for converted PDF document.
   *
   * @note This value does not represent a rectangle. It just defines the left margin, bottom margin,
   *       right margin and top margin of a PDF page.
   */
  RectF page_margin;

  /** @brief A font object. */
  common::Font font;

  /** @brief Font size. If valid, it should be above 0. */
  float text_size;

  /** @brief Font color. */
  ARGB text_color;

  /** @brief Line spacing. If valid, it should be above 0. */
  float linespace;

  /** @brief Used to decide whether to insert a page break in converted PDF document when meeting character 0x0c. */
  bool is_break_page;
};

/**
 * @brief A callback class used for converting DWG to PDF.
 *
 * @details This class is used to receive the progress of converting DWG to PDF.
 */
class DWG2PDFProgressCallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;
  /**
   * @brief A callback function to be called when converting DWG to PDF.
   *
   * @param[in] message   The message of the current converting process.
   * @param[in] progress  The progress of the current converting process. It ranges from 0 to 100.
   *
   * @return None.
   */
  virtual void OnProgress(const wchar_t* message, float progress) = 0;
 };

/**
 * This class represents settings used for converting DWG to PDF. This would be used in class @link Convert
 * @endlink.
 *
 * @see @link Convert @endlink
 */
class DWG2PDFSettingData FS_FINAL : public Object {
 public:
  /**
   * @brief Enumeration for flags of DWG to PDF export.
   *
   * @details Values of this enumeration could be used alone or in a combination.
   */
  typedef enum _DWG2PDFExportFlags {
    /**
     * @brief Bit 1. Enable embedding of TTF(True Type Font) program to PDF file. The whole TTF font file will be embedded (huge PDF size).
     */
    e_FlagEmbededTTF = 0x0001,
    /**
     * @brief Bit 2. Enable TTF font text to geometry conversion.
     */
    e_FlagTTFTextAsGeometry = 0x0002,
    /**
     * @brief Bit 3. Enable SHX font text to geometry conversion.
     */
    e_FlagSHXTextAsGeometry = 0x0004,
    /**
     * @brief Bit 4. Enable simple geometry optimization (separated segments to one polyline, Bezier curve control points).
     */
    e_FlagSimpleGeomOptimization = 0x0008,
    /** @brief Bit 5. If enabled, layer support will be added to PDF file (1.5 version required). */
    e_FlagEnableLayers = 0x0010,
    /** @brief Bit 6. If enabled, invisible layers will be added to PDF file (1.5 version required). */
    e_FlagIncludeOffLayers = 0x0020,
    /**
     * @brief Bit 7. Enable embedding of TTF font program to PDF file. The TTF font will be reduced by removing unused parts (smaller PDF file size, but limited editing).
     */
    e_FlagEmbededOptimizedTTF = 0x0040,
    /**
     * @brief Bit 8. Determines whether software uses vector hidden-line removal for corresponding viewports.
     */
    e_FlagUseHLR = 0x0080,
    /** @brief Bit 9. Enable compression of internal PDF streams. */
    e_FlagFlateCompression = 0x0100,
    /** @brief Bit 10. Enable ASCIIHex encoding of internal PDF streams. */
    e_FlagASCIIHexEncoding = 0x0200,
    /** @brief Bit 11. Enable hyperlinks export. */
    e_FlagExportHyperlinks = 0x0400,
    /** 
     * @brief Bit 12. If enabled, layout geometry will be zoomed to paper size, else layout settings will be applied.
     * @note This mode works like some Layout settings: "Plot Area" - "Extents", "Fit to Paper", "Center the plot", these settings applied to specified paper size and orientation,
     *       but some settings like "Plot lineweight", "Plot style" are still applying from Layout settings.
     */
    e_FlagZoomToExtentsMode = 0x0800,
    /** @brief Bit 13. Create linearized PDF file. */
    e_FlagLinearized = 0x1000,
    /** @brief Bit 15. Enable measuring scale in pdf. */
    e_FlagMeasuring = 0x4000
  } DWG2PDFExportFlags;
  
  /**
   * @brief Enumeration for hatches export type used for converting DWG to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _DWG2PDFExportHatchesType {
    /** @brief Hatches export type: Exports hatch as a bitmap. */
    e_DWG2PDFExportHatchesTypeBitmap  = 0,
    /** @brief Hatches export type: Exports hatch as a set of triangles (vectorizer). */
    e_DWG2PDFExportHatchesTypeDrawing  = 1,
    /** @brief Hatches export type: Exports hatch as a PDF path (solid hatches only). */
    e_DWG2PDFExportHatchesTypePdfPaths  = 2,
    /** @brief Hatches export type: Exports hatch as a polygon (solid hatches only). */
    e_DWG2PDFExportHatchesTypePolygons  = 3
  } DWG2PDFExportHatchesType;
  
  /**
   * @brief Enumeration for searchable text type used for converting DWG to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _DWG2PDFSearchableTextType {
    /** @brief Searchable text type: No searchable text. */
    e_DWG2PDFSearchableTextTypeNoSearch  = 0,
    /** @brief Searchable text type: Only text displayed with SHX font is searchable. */
    e_DWG2PDFSearchableTextTypeSHX  = 1,
    /** @brief Searchable text type: Only text displayed with TTF font is searchable. */
    e_DWG2PDFSearchableTextTypeTTF  = 2
  } DWG2PDFSearchableTextType;
  
  /**
   * @brief Enumeration for color policy used for converting DWG to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _DWG2PDFColorPolicy {
    /** @brief Color policy: No color policy. A drawing is exported with its native color palette (as is). */
    e_DWG2PDFColorPolicyNoPolicy = 0,
    /** @brief Color policy: Drawing is exported to a monochrome PDF file. */
    e_DWG2PDFColorPolicyMono = 1,
    /** @brief Color policy: Drawing is exported to a grayscale PDF file. Native colors are converted into grayscale. */
    e_DWG2PDFColorPolicyGrayscale = 2
  } DWG2PDFColorPolicy;
  

  /**
   * @brief Constructor, with parameters.
   */
  DWG2PDFSettingData()
      : export_flags(1)
      , export_hatches_type(e_DWG2PDFExportHatchesTypeBitmap)
      , other_export_hatches_type(e_DWG2PDFExportHatchesTypeBitmap)
      , gradient_export_hatches_type(e_DWG2PDFExportHatchesTypeBitmap)
      , searchable_text_type(e_DWG2PDFSearchableTextTypeNoSearch)
      , is_active_layout(false)
      , paper_width(0.0f)
      , paper_height(0.0f)
      , color_policy(e_DWG2PDFColorPolicyNoPolicy)
      , is_output_progress(true)
      , progress_callback(NULL){}

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another DWG-to-PDF setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  DWG2PDFSettingData& operator=(const DWG2PDFSettingData& data) {
    export_flags = data.export_flags;
    export_hatches_type = data.export_hatches_type;
    other_export_hatches_type = data.other_export_hatches_type;
    gradient_export_hatches_type = data.gradient_export_hatches_type;
    searchable_text_type = data.searchable_text_type;
    is_active_layout = data.is_active_layout;
    output_title = data.output_title;
    output_author = data.output_author;
    output_subject = data.output_subject;
    output_keywords = data.output_keywords;
    output_creator = data.output_creator;
    output_producer = data.output_producer;
    paper_width = data.paper_width;
    paper_height = data.paper_height;
    color_policy = data.color_policy;
    is_output_progress = data.is_output_progress;
    progress_callback = data.progress_callback;
    return (*this);
  }

  /**
   * @brief The export flags used for the converted PDF document. Please refer to values starting from @link DWG2PDFSettingData::e_FlagEmbededTTF @endlink and
   *        this can be one or a combination of these values
   *        It could also be 0, which means all bits in the flag are 0.
   */
  uint32 export_flags;

  /**
   * @brief The type of solid hatches export.
   *
   * @details It use @link DWG2PDFSettingData::e_DWG2PDFExportHatchesTypeBitmap @endlink as the default value of this option.
   *          Please refer to values starting from @link DWG2PDFSettingData::e_DWG2PDFExportHatchesTypeBitmap @endlink
   *          and this should be one of these values.
   */
  DWG2PDFExportHatchesType export_hatches_type;

  /**
   * @brief The type of other (non-solid) hatches export.
   *
   * @details For this option, only @link DWG2PDFSettingData::e_DWG2PDFExportHatchesTypeBitmap @endlink
   *          and @link DWG2PDFSettingData::e_DWG2PDFExportHatchesTypeDrawing @endlink are supported.
   *          It use @link DWG2PDFSettingData::e_DWG2PDFExportHatchesTypeBitmap @endlink as the default value of this option.
   *          Please refer to values starting from @link DWG2PDFSettingData::e_DWG2PDFExportHatchesTypeBitmap @endlink
   *          and this should be one of these values
   */
  DWG2PDFExportHatchesType other_export_hatches_type;

  /**
   * @brief The type of gradient hatches export.
   *
   * @details For this option, only @link DWG2PDFSettingData::e_DWG2PDFExportHatchesTypeBitmap @endlink
   *          and @link DWG2PDFSettingData::e_DWG2PDFExportHatchesTypeDrawing @endlink are supported.
   *          It use @link DWG2PDFSettingData::e_DWG2PDFExportHatchesTypeBitmap @endlink as the default value of this option.
   *          Please refer to values starting from @link DWG2PDFSettingData::e_DWG2PDFExportHatchesTypeBitmap @endlink
   *          and this should be one of these values
   */
  DWG2PDFExportHatchesType gradient_export_hatches_type;

  /**
   * @brief The type of search text type.
   *
   * @details This option can be used if SHX or TTF text exported as geometry(@link DWG2PDFSettingData::e_FlagTTFTextAsGeometry @endlink
   *          and @link DWG2PDFSettingData::e_FlagSHXTextAsGeometry @endlink are enabled by <i>export_flags</i>).
   *          It use @link DWG2PDFSettingData::e_DWG2PDFSearchableTextTypeNoSearch @endlink as the default value of this option.
   *          Please refer to values starting from @link DWG2PDFSettingData::e_DWG2PDFSearchableTextTypeNoSearch @endlink
   *          and this should be one of these values.
   */
  DWG2PDFSearchableTextType searchable_text_type;

  /**
   * @brief <b>true</b> means to export the active layout only, while <b>false</b> means not. Default value: <b>false</b>.
   */
  bool is_active_layout;

  /**
   * @brief The title for the output PDF document, an empty string will be used as default.
   */
  foxit::WString output_title;

  /**
   * @brief The author for the output PDF document, an empty string will be used as default.
   */
  foxit::WString output_author;

  /**
   * @brief The subject for the output PDF document, an empty string will be used as default.
   */
  foxit::WString output_subject;

  /**
   * @brief The keywords for the output PDF document, an empty string will be used as default.
   */
  foxit::WString output_keywords;

  /**
   * @brief The creator for the output PDF document, an empty string will be used as default.
   */
  foxit::WString output_creator;

  /**
   * @brief The producer for the output PDF document, an empty string will be used as default.
   */
  foxit::WString output_producer;

  /**
   * @brief The paper width used for the converted PDF document.
   *
   * @details This option can be used if layout geometry will be zoomed to paper size(@link DWG2PDFSettingData::e_FlagZoomToExtentsMode @endlink
   *          are enabled by <i>export_flags</i>).
   *          It use the default value 210.0f. this values are in millimeters.
   */
  float paper_width;

  /**
   * @brief The paper height used for the converted PDF document.
   *
   * @details This option can be used if layout geometry will be zoomed to paper size(@link DWG2PDFSettingData::e_FlagZoomToExtentsMode @endlink
   *          are enabled by <i>export_flags</i>).
   *          It use the default value 297.0f. this values are in millimeters.
   */
  float paper_height;

  /**
   * @brief The color policy used for the converted PDF document.
   *
   * @details It use @link DWG2PDFSettingData::e_DWG2PDFColorPolicyNoPolicy @endlink as the default value of this option.
   *          Please refer to values starting from @link DWG2PDFSettingData::e_DWG2PDFColorPolicyNoPolicy @endlink
   *          and this should be one of these values.
   */
  DWG2PDFColorPolicy color_policy;

  /**
   * @brief A boolean value which indicates whether to output progress logs.
   *        <b>true</b> means to output progress logs, and <b>false</b> means not.
   *        Default value: <b>true</b>.
   */
  bool is_output_progress;

  /**
   * @brief A pointer to a @link DWG2PDFProgressCallback @endlink object which is used to receive the progress of converting DWG to PDF.
   *        This parameter can be <b>NULL</b>.
   */
  void* progress_callback;
};

#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)

/** This class represents setting data used for converting Word to PDF. */
class Word2PDFSettingData FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for optimize option (which specifies resolution and quality)
   *        for converting Word to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ConvertOptimizeOption {
    /** @brief Optimize option: convert for print, which is higher quality and results in a larger file size. */
    e_ConvertOptimizeOptionForPrint  = 0,
    /** @brief Optimize option: convert for screen, which is a lower quality and results in a smaller file size. */
    e_ConvertOptimizeOptionForOnScreen = 1
  } ConvertOptimizeOption;
  
  /**
   * @brief Enumeration for content option which specifies
   *        how much content of Word document is to be converted to PDF document.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ConvertContentOption {
    /** @brief Convert Word document without markup. */
    e_ConvertContentOptionOnlyContent  = 0,
    /** @brief Convert Word document with markup. */
    e_ConvertContentOptionWithMarkup = 1
  } ConvertContentOption;
  
  /**
   * @brief Enumeration for bookmark option for for converting Word to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ConvertBookmarkOption {
    /** @brief Do not create bookmark in converted PDF file. */
    e_ConvertBookmarkOptionNone  = 0,
    /**
     * @brief Create bookmarks in converted PDF file by using each heading of Word document.
     * @details Here, "Word heading" includes only headings within the main document and text boxes
     *          not within headers, footers, endnotes, footnotes, or comments.
     */
    e_ConvertBookmarkOptionUseHeadings = 1,
    /**
     * @brief Create bookmarks in converted PDF file by using each bookmarks of Word document.
     * @details Here, "Word bookmark" includes all bookmarks except those contained within headers and footers.
     */
    e_ConvertBookmarkOptionUseWordBookmark = 2
  } ConvertBookmarkOption;
  

  /** @brief Constructor. */
  Word2PDFSettingData()
      : include_doc_props(false)
      , optimize_option(Word2PDFSettingData::e_ConvertOptimizeOptionForPrint)
      , content_option(Word2PDFSettingData::e_ConvertContentOptionOnlyContent)
      , bookmark_option(Word2PDFSettingData::e_ConvertBookmarkOptionNone)
      , convert_to_pdfa(false)
      , disable_vba_code(false)
  {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] include_doc_props  A boolean value which indicates whether to include
   *                               Word document properties in the converted PDF document.
   * @param[in] optimize_option    Optimize option for covnerting Word to PDF, which specifies
   *                               the resolution and quality of the converted PDF document.
   *                               Please refer to values starting
   *                               from @link Word2PDFSettingData::e_ConvertOptimizeOptionForPrint @endlink
   *                               and this should be one of these values.
   * @param[in] content_option     Content option for covnerting Word to PDF, which specifies
   *                               how much content of Word document is to be converted to PDF file.
   *                               Please refer to values starting
   *                               from @link Word2PDFSettingData::e_ConvertContentOptionOnlyContent @endlink
   *                               and this should be one of these values.
   * @param[in] bookmark_option    Bookmark option for covnerting Word to PDF, which specifies
   *                               whether to export bookmarks to converted PDF file,
   *                               and the type of bookmarks. Please refer to values starting
   *                               from @link Word2PDFSettingData::e_ConvertBookmarkOptionNone @endlink
   *                               and this should be one of these values.
   * @param[in] convert_to_pdfa    (Reserved) A boolean value which indicates whether to convert to a PDF/A file
   *                               or a common PDF file. Currently, this is useless and Foxit PDF SDK will treated as <b>false</b>.
   * @param[in] disable_vba_code   A boolean value decide whether to disable the execution of vba code in the Word document.
   */
  Word2PDFSettingData(bool include_doc_props, ConvertOptimizeOption optimize_option,
                      ConvertContentOption content_option, ConvertBookmarkOption bookmark_option,
                      bool convert_to_pdfa, bool disable_vba_code) {
    this->include_doc_props = include_doc_props;
    this->optimize_option = optimize_option;
    this->content_option = content_option;
    this->bookmark_option = bookmark_option;
    this->convert_to_pdfa = convert_to_pdfa;
    this->disable_vba_code = disable_vba_code;
  }

  /**
  * @brief Assign operator.
  *
  * @param[in] data  Another Word-to-PDF setting data object, whose value would be assigned to current object.
  *
  * @return Reference to current object itself.
  */
  Word2PDFSettingData &operator = (const Word2PDFSettingData& data) {
    include_doc_props = data.include_doc_props;
    optimize_option = data.optimize_option;
    content_option = data.content_option;
    bookmark_option = data.bookmark_option;
    convert_to_pdfa = data.convert_to_pdfa;
    disable_vba_code = data.disable_vba_code;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] include_doc_props  A boolean value which indicates whether to include
   *                               Word document properties in the converted PDF document.
   * @param[in] optimize_option    Optimize option for covnerting Word to PDF, which specifies
   *                               the resolution and quality of the converted PDF document.
   *                               Please refer to values starting
   *                               from @link Word2PDFSettingData::e_ConvertOptimizeOptionForPrint @endlink
   *                               and this should be one of these values.
   * @param[in] content_option     Content option for covnerting Word to PDF, which specifies
   *                               how much content of Word document is to be converted to PDF file.
   *                               Please refer to values starting
   *                               from @link Word2PDFSettingData::e_ConvertContentOptionOnlyContent @endlink
   *                               and this should be one of these values.
   * @param[in] bookmark_option    Bookmark option for covnerting Word to PDF, which specifies
   *                               whether to export bookmarks to converted PDF file,
   *                               and the type of bookmarks. Please refer to values starting
   *                               from @link Word2PDFSettingData::e_ConvertBookmarkOptionNone @endlink
   *                               and this should be one of these values.
   * @param[in] convert_to_pdfa    (Reserved) A boolean value which indicates whether to convert to a PDF/A file
   *                               or a common PDF file. Currently, this is useless and Foxit PDF SDK will treated as <b>false</b>.
   * @param[in] disable_vba_code   A boolean value decide whether to disable the execution of vba code in the Word document.
   *
   * @return None.
   */
  void Set(bool include_doc_props, ConvertOptimizeOption optimize_option,
           ConvertContentOption content_option, ConvertBookmarkOption bookmark_option,
           bool convert_to_pdfa, bool disable_vba_code) {
    this->include_doc_props = include_doc_props;
    this->optimize_option = optimize_option;
    this->content_option = content_option;
    this->bookmark_option = bookmark_option;
    this->convert_to_pdfa = convert_to_pdfa;
    this->disable_vba_code = disable_vba_code;
  }

  /**
   * @brief A boolean value which indicates whether to include Word document properties
   *        in the converted PDF document.
   *
   * @details <b>true</b> means to include Word document properties in the converted PDF document.<br>
   *          <b>false</b> means not to include Word document properties in the converted PDF document.
   */
  bool include_doc_props;

  /**
   * @brief Optimize option for covnerting Word to PDF, which specifies the resolution and quality of
   *        the converted PDF document. Please refer to values starting
   *        from @link Word2PDFSettingData::e_ConvertOptimizeOptionForPrint @endlink and
   *        this should be one of these values.
   */
  ConvertOptimizeOption optimize_option;

  /**
   * @brief Content option for covnerting Word to PDF, which specifies how much content of Word document
   *        is to be converted to PDF file. Please refer to values starting
   *        from @link Word2PDFSettingData::e_ConvertContentOptionOnlyContent @endlink and
   *        this should be one of these values.
   */
  ConvertContentOption content_option;

  /**
   * @brief Bookmark option for covnerting Word to PDF, which specifies whether to export bookmarks to converted PDF file,
   *        and the type of bookmarks. Please refer to values starting
   *        from @link Word2PDFSettingData::e_ConvertBookmarkOptionNone @endlink and
   *        this should be one of these values.
   */
  ConvertBookmarkOption bookmark_option;

  /**
   * @brief (Reserved) A boolean value which indicates whether to convert to a PDF/A file
   *        or a common PDF file. Currently, this is useless and Foxit PDF SDK will treated as <b>false</b>.
   *
   * @details <b>true</b> means to convert Word document to a PDF/A file.<br>
   *          <b>false</b> means to convert Word document to a common file.
   */
  bool convert_to_pdfa;

  /**
   * @brief A boolean value decide whether to disable the execution of vba code in the Word document.
   *
   * @details <b>true</b> means to disable the vba code, while <b>false</b> means not.
   *          Default value:<b>false</b>.<br>
   *          This flag is only supported on Windows platforms.
   */
  bool disable_vba_code;
};

/** This class represents setting data used for converting Excel to PDF. */
class Excel2PDFSettingData FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for quality for converting Excel to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ConvertQuality {
    /** @brief Standard quality. */
    e_ConvertQualityStandard  = 0,
    /** @brief Minimum quality. */
    e_ConvertQualityMinimum = 1
  } ConvertQuality;
  
  /**
   * @brief Enumeration for scaling type for each sheet in the Excel document for converting Excel to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ScaleType {
    /** @brief No scaling. */
    e_ScaleTypeNone  = 0,
    /** @brief Fit all columns of one sheet on one page. */
    e_ScaleTypeFitAllColumns = 1,
    /** @brief Fit all rows of one sheet on one page. */
    e_ScaleTypeFitAllRows = 2,
    /** @brief Fit a sheet on one page. */
    e_ScaleTypeFitSheet = 3
  } ScaleType;
  

  /** @brief Constructor. */
  Excel2PDFSettingData()
      : include_doc_props(false)
      , quality(Excel2PDFSettingData::e_ConvertQualityStandard)
      , ignore_print_area(true)
      , scale_type(Excel2PDFSettingData::e_ScaleTypeNone)
      , convert_to_pdfa(false)
      , disable_vba_code(false)
  {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] include_doc_props  A boolean value which indicates whether to include
   *                               Excel document properties in the converted PDF document.
   * @param[in] quality            Quality for covnerting Excel to PDF. Please refer to values starting
   *                               from @link Excel2PDFSettingData::e_ConvertQualityStandard @endlink and
   *                               this should be one of these values.
   * @param[in] ignore_print_area  A boolean value which indicates whether to ignore any print area set
   *                               when converting Excel document to PDF file.
   * @param[in] scale_type         Scale type for the Excel sheet when converting Excel document to
   *                               PDF file. Please refer to values starting from
   *                               @link Excel2PDFSettingData::e_ScaleTypeNone @endlink
   *                               and this should be one of these values.
   * @param[in] convert_to_pdfa    (Reserved) A boolean value which indicates whether to convert to a PDF/A file
   *                               or a common PDF file. Currently, this is useless and Foxit PDF SDK will treated as <b>false</b>.
   * @param[in] disable_vba_code   A boolean value decide whether to disable the execution of vba code in the Excel document.
   */
  Excel2PDFSettingData(bool include_doc_props, ConvertQuality quality, bool ignore_print_area,
                       ScaleType scale_type, bool convert_to_pdfa, bool disable_vba_code) {
    this->include_doc_props = include_doc_props;
    this->quality = quality;
    this->ignore_print_area = ignore_print_area;
    this->scale_type = scale_type;
    this->convert_to_pdfa = convert_to_pdfa;
    this->disable_vba_code = disable_vba_code;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another Excel-to-PDF setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Excel2PDFSettingData &operator = (const Excel2PDFSettingData& data) {
    include_doc_props = data.include_doc_props;
    quality = data.quality;
    ignore_print_area = data.ignore_print_area;
    scale_type = data.scale_type;
    convert_to_pdfa = data.convert_to_pdfa;
    disable_vba_code = data.disable_vba_code;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] include_doc_props  A boolean value which indicates whether to include
   *                               Excel document properties in the converted PDF document.
   * @param[in] quality            Quality for covnerting Excel to PDF. Please refer to values starting
   *                               from @link Excel2PDFSettingData::e_ConvertQualityStandard @endlink and
   *                               this should be one of these values.
   * @param[in] ignore_print_area  A boolean value which indicates whether to ignore any print area set
   *                               when converting Excel document to PDF file.
   * @param[in] scale_type         Scale type for the Excel sheet when converting Excel document to
   *                               PDF file. Please refer to values starting from
   *                               @link Excel2PDFSettingData::e_ScaleTypeNone @endlink
   *                               and this should be one of these values.
   * @param[in] convert_to_pdfa    (Reserved) A boolean value which indicates whether to convert to a PDF/A file
   *                               or a common PDF file. Currently, this is useless and Foxit PDF SDK will treated as <b>false</b>.
   * @param[in] disable_vba_code   A boolean value decide whether to disable the execution of vba code in the Excel document.
   *
   * @return None.
   */
  void Set(bool include_doc_props, ConvertQuality quality, bool ignore_print_area,
           ScaleType scale_type, bool convert_to_pdfa) {
    this->include_doc_props = include_doc_props;
    this->quality = quality;
    this->ignore_print_area = ignore_print_area;
    this->scale_type = scale_type;
    this->convert_to_pdfa = convert_to_pdfa;
    this->disable_vba_code = disable_vba_code;
  }

  /**
   * @brief A boolean value which indicates whether to include Excel document properties
   *        in the converted PDF document.
   *
   * @details <b>true</b> means to include Excel document properties in the converted PDF document.<br>
   *          <b>false</b> means not to include Excel document properties in the converted PDF document.
   */
  bool include_doc_props;

  /**
   * @brief Quality for covnerting Excel to PDF. Please refer to values starting
   *        from @link Excel2PDFSettingData::e_ConvertQualityStandard @endlink and
   *        this should be one of these values.
   */
  ConvertQuality quality;

  /**
   * @brief A boolean value which indicates whether to ignore any print area set
   *        when converting Excel document to PDF file.
   *
   * @details <b>true</b> means to ignore any setting of print area in Excel document.<br>
   *          <b>false</b> means to use the setting of print areas in Excel document.
   */
  bool ignore_print_area;

  /**
   * @brief Scale type for the Excel sheet when converting Excel document to PDF file.
   *        Please refer to values starting from @link Excel2PDFSettingData::e_ScaleTypeNone @endlink
   *        and this should be one of these values.
   */
  ScaleType scale_type;

  /**
   * @brief (Reserved) A boolean value which indicates whether to convert to a PDF/A file
   *        or a common PDF file. Currently, this is useless and Foxit PDF SDK will treated as <b>false</b>.
   *
   * @details <b>true</b> means to convert Excel document to a PDF/A file.<br>
   *          <b>false</b> means to convert Excel document to a common file.
   */
  bool convert_to_pdfa;

  /**
   * @brief A boolean value decide whether to disable the execution of vba code in the Excel document.
   *
   * @details <b>true</b> means to disable the vba code, while <b>false</b> means not.
   *          Default value:<b>false</b>.<br>
   *          This flag is only supported on Windows platforms.
   */
  bool disable_vba_code;
};

/** This class represents setting data used for converting PowerPoint to PDF. */
class PowerPoint2PDFSettingData FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for intent for converting PowerPoint to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ConvertIntent {
    /** @brief Intent: converted result file will be used for printing. */
    e_ConvertIntentPrint  = 0,
    /** @brief Intent: converted result file will be used for showing on screen. */
    e_ConvertIntentScreen = 1
  } ConvertIntent;
  
  /**
   * @brief Enumeration for specifying the page layout order in which slides appear on converted handouts.
   *        Handouts can be used to show multiple slides on one page when converting PowerPoint to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _HandoutOrder {
    /**
     * @brief When converting PowerPoint in handouts type, convert handouts with consecutive slides 
     *        displayed horizontally first (in horizontal rows).
     */
    e_HandoutOrderHorizontalFirst  = 0,
    /**
     * @brief When converting PowerPoint in handouts type, convert handouts with consecutive slides
     * displayed vertically first (in vertical columns).
     */
    e_HandoutOrderVerticalFirst = 1
  } HandoutOrder;
  
  /**
   * @brief Enumeration for output type for converting PowerPoint to PDF.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _OutputType {
    /** @brief Output type: slides. */
    e_OutputSlides = 1,
    /** @brief Output type: notes pages. */
    e_OutputNotesPages = 2,
    /** @brief Output type: outline view. */
    e_OutputOutline = 3,
    /** @brief Output type: handouts with one slide per handout page. */
    e_OutputOneSlideHandouts = 4,
    /** @brief Output type: handouts with two slide per handout page. */
    e_OutputTwoSlideHandouts = 5,
    /** @brief Output type: handouts with three slide per handout page. */
    e_OutputThreeSlideHandouts = 6,
    /** @brief Output type: handouts with four slide per handout page. */
    e_OutputFourSlideHandouts = 7,
    /** @brief Output type: handouts with six slide per handout page. */
    e_OutputSixSlideHandouts = 8,
    /** @brief Output type: handouts with nine slide per handout page. */
    e_OutputNineSlideHandouts = 9
  } OutputType;
  

  /** @brief Constructor. */
  PowerPoint2PDFSettingData()
    : intent(PowerPoint2PDFSettingData::e_ConvertIntentPrint)
    , frame_output_slides(false)
    , output_type(PowerPoint2PDFSettingData::e_OutputSlides)
    , handout_order(PowerPoint2PDFSettingData::e_HandoutOrderVerticalFirst)
    , output_hidden_slides(false)
    , include_doc_props(false)
    , disable_vba_code(false)
  {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] intent                Converting intent. Please refer to values starting from
   *                                  @link PowerPoint2PDFSettingData::e_ConvertIntentPrint @endlink and
   *                                  this should be one of these values.
   * @param[in] frame_output_slides   A boolean value which indicates whether to frame output slides
   *                                  in the converted PDF document or not.
   * @param[in] output_type           Output type used to specify which component of PowerPoint document is to be converted. 
   *                                  Please refer to values starting from @link PowerPoint2PDFSettingData::e_OutputSlides @endlink
   *                                  and this should be one of these values.
   * @param[in] handout_order         Handout order used to specify the page layout order in which slides appear on converted handouts
   *                                  that show multiple slides on one page. Please refer to values starting from
   *                                  @link PowerPoint2PDFSettingData::e_HandoutOrderHorizontalFirst @endlink and 
   *                                  this should be one of these values.
   * @param[in] output_hidden_slides  A boolean value which indicates whether to convert hidden slides to the converted PDF document.
   * @param[in] include_doc_props     A boolean value which indicates whether to include PowerPoint document properties
   *                                  in the converted PDF document.
   * @param[in] disable_vba_code      A boolean value decide whether to disable the execution of vba code in the PowerPoint document.
   */
  PowerPoint2PDFSettingData(ConvertIntent intent, bool frame_output_slides, OutputType output_type, HandoutOrder handout_order,
                            bool output_hidden_slides, bool include_doc_props, bool disable_vba_code) {
    this->intent = intent;
    this->frame_output_slides = frame_output_slides;
    this->handout_order = handout_order;
    this->output_hidden_slides = output_hidden_slides;
    this->output_type = output_type;
    this->include_doc_props = include_doc_props;
    this->disable_vba_code = disable_vba_code;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another PowerPoint-to-PDF setting data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PowerPoint2PDFSettingData &operator = (const PowerPoint2PDFSettingData& data) {
    intent = data.intent;
    frame_output_slides = data.frame_output_slides;
    output_type = data.output_type;
    handout_order = data.handout_order;
    output_hidden_slides = data.output_hidden_slides;
    include_doc_props = data.include_doc_props;
    disable_vba_code = data.disable_vba_code;
    return (*this);
  }

  /**
   * @brief Set value.
   *
   * @param[in] intent                Converting intent. Please refer to values starting from
   *                                  @link PowerPoint2PDFSettingData::e_ConvertIntentPrint @endlink and
   *                                  this should be one of these values.
   * @param[in] frame_output_slides   A boolean value which indicates whether to frame output slides
   *                                  in the converted PDF document or not.
   * @param[in] output_type           Output type used to specify which component of PowerPoint document is to be converted.
   *                                  Please refer to values starting from @link PowerPoint2PDFSettingData::e_OutputSlides @endlink
   *                                  and this should be one of these values.
   * @param[in] handout_order         Handout order used to specify the page layout order in which slides appear on converted handouts
   *                                  that show multiple slides on one page. Please refer to values starting from
   *                                  @link PowerPoint2PDFSettingData::e_HandoutOrderHorizontalFirst @endlink and
   *                                  this should be one of these values.
   * @param[in] output_hidden_slides  A boolean value which indicates whether to convert hidden slides to the converted PDF document.
   * @param[in] include_doc_props     A boolean value which indicates whether to include PowerPoint document properties
   *                                  in the converted PDF document.
   * @param[in] disable_vba_code      A boolean value decide whether to disable the execution of vba code in the PowerPoint document.
   *
   * @return None.
   */
  void Set(ConvertIntent intent, bool frame_output_slides, OutputType output_type, HandoutOrder handout_order,
           bool output_hidden_slides, bool include_doc_props, bool disable_vba_code) {
    this->intent = intent;
    this->frame_output_slides = frame_output_slides;
    this->output_type = output_type;
    this->handout_order = handout_order;
    this->output_hidden_slides = output_hidden_slides;
    this->include_doc_props = include_doc_props;
    this->disable_vba_code = disable_vba_code;
  }

  /**
   * @brief Converting intent. Please refer to values starting from @link PowerPoint2PDFSettingData::e_ConvertIntentPrint @endlink
   *        and this should be one of these values.
   */
  ConvertIntent intent;

  /**
   * @brief A boolean value which indicates whether to frame output slides in the converted PDF document.
   *
   * @details <b>true</b> means to frame output slides in the converted PDF document.<br>
   *          <b>false</b> means not to frame output slides in the converted PDF document.
   */
  bool frame_output_slides;

  /**
   * @brief Output type used to specify which component (slides, handouts, notes pages, or an outline) of PowerPoint document is to
   *        be converted to PDF document. Please refer to values starting from @link PowerPoint2PDFSettingData::e_OutputSlides @endlink
   *        and this should be one of these values.
   */
  OutputType output_type;

  /**
   * @brief Handout order used to specify the page layout order in which slides appear on converted handouts.
   *        Handouts can be used to show multiple slides on one page when converting PowerPoint to PDF.
   *        Please refer to values starting from @link PowerPoint2PDFSettingData::e_HandoutOrderHorizontalFirst @endlink
   *        and this should be one of these values.
   *
   * @note This would be available only when <i>output_type</i> is one of following value:
   *       <ul>
   *       <li>@link PowerPoint2PDFSettingData::e_OutputOneSlideHandouts @endlink</li>
   *       <li>@link PowerPoint2PDFSettingData::e_OutputTwoSlideHandouts @endlink</li>
   *       <li>@link PowerPoint2PDFSettingData::e_OutputThreeSlideHandouts @endlink</li>
   *       <li>@link PowerPoint2PDFSettingData::e_OutputFourSlideHandouts @endlink</li>
   *       <li>@link PowerPoint2PDFSettingData::e_OutputSixSlideHandouts @endlink</li>
   *       <li>@link PowerPoint2PDFSettingData::e_OutputNineSlideHandouts @endlink</li>
   *       </ul>
   */
  HandoutOrder handout_order;

  /**
   * @brief A boolean value which indicates whether to convert hidden slides to the converted PDF document.
   *
   * @details <b>true</b> means to convert hidden slides to the converted PDF document.<br>
   *          <b>false</b> means not to convert hidden slides to the converted PDF document.
   */
  bool output_hidden_slides;

  /**
   * @brief A boolean value which indicates whether to include PowerPoint document properties
   *        in the converted PDF document.
   *
   * @details <b>true</b> means to include PowerPoint document properties in the converted PDF document.<br>
   *          <b>false</b> means not to include PowerPoint document properties in the converted PDF document.
   */
  bool include_doc_props;

  /**
   * @brief A boolean value decide whether to disable the execution of vba code in the PowerPoint document.
   *
   * @details <b>true</b> means to disable the vba code, while <b>false</b> means not.
   *          Default value:<b>false</b>.<br>
   *          This flag is only supported on Windows platforms.
   */
  bool disable_vba_code;
};
#endif  // #if (defined(_WIN32) || defined(_WIN64))

/** This class represents related resource file data used for converting HTML to PDF. */
class HTML2PDFRelatedResource FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  HTML2PDFRelatedResource() 
    : related_resource_file(NULL)
    , resource_file_relative_path(L"") {
  }

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] related_resource_file        The related resouce file.
   * @param[in] resource_file_relative_path  The path of <i> related_resource_file </i> in the HTML content.
   *
   * @return None.
   */
  HTML2PDFRelatedResource(foxit::common::file::ReaderCallback* related_resource_file, foxit::WString resource_file_relative_path) {
    this->related_resource_file = related_resource_file;
    this->resource_file_relative_path = resource_file_relative_path;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another HTML-to-PDF related resource object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  HTML2PDFRelatedResource &operator = (const HTML2PDFRelatedResource& data) {
    related_resource_file = data.related_resource_file;
    resource_file_relative_path = data.resource_file_relative_path;
    return (*this);
  }

  /** @brief The related resouce file. */
  foxit::common::file::ReaderCallback* related_resource_file;

  /** 
   * @brief The path of <i> related_resource_file </i> in the HTML content.
   *
   * @details This value should be consistent with the path in the HTML content. For example: The path of <i> related_resource_file </i> in
   *          HTML content is <img src="../one.png">, this value should be set to "../one.png".
   */
  foxit::WString resource_file_relative_path;
};

/** This class represents an array of related resource data objects. */
FSDK_DEFINE_ARRAY(HTML2PDFRelatedResourceArray, HTML2PDFRelatedResource)

#if (defined(_WIN32) || defined(_WIN64)) || defined(__linux__) 
/** This class represents the parameters for the conversion between OFD and PDF. */
class OFDConvertParam FS_FINAL : public Object{
 public:
   /** @brief Constructor. */
   OFDConvertParam()
   :is_embed_font(false) {}

   /**
    * @brief Constructor, with parameters.
    *
    * @param[in] is_embed_font  <b>true</b> means to embed font in the converted file, while <b>false</b> means not.
    */
   OFDConvertParam(bool is_embed_font) {
     this->is_embed_font = is_embed_font;
   }

   /**
    * @brief Set value.
    *
    * @param[in] is_embed_font  <b>true</b> means to embed font in the converted file, while <b>false</b> means not.
    *
    * @return None.
    */
   void Set(bool is_embed_font) {
     this->is_embed_font = is_embed_font;
   }

   /** @brief Whether to embed font in the converted file. <b>true</b> means to embed font in the converted file, while <b>false</b> means not. */
   bool is_embed_font;
};
#endif

/**
 * Conversion add-on module can be used to do some conversion between PDF file and other file formats.
 * Before using any class or methods in this module, please ensure Foxit PDF SDK has been initialized successfully
 * by function @link common::Library::Initialize @endlink with a key including "Conversion" module.
 * Before using function @link Convert::FromDWG @endlink, please ensure Foxit PDF SDK has been initialized successfully
 * by function @link common::Library::Initialize @endlink with a key including "DWG2PDF" module.
 * From version 11.0, we do not update and maintance HTML2PDF engine package on linux x86 platform
 * and maybe it will be deprecated in the future version on linux x86 platform.
 *
 * @see @link common::Library @endlink
 */
class Convert FS_FINAL : public Base {
 public:
   /**
    * @brief Enumeration for engine type used for office to PDF conversion on Windows platforms.
    *
    * @details Values of this enumeration should be used alone.
    */
   typedef enum _Office2PdfEngine {
     /** @brief Microsoft Office automation engine. */
     e_Office2PdfEngineMicrosoft = 0,
     /** @brief WPS Office automation engine. */
     e_Office2PdfEngineWps = 1
   } Office2PdfEngine;
   

   /**
    * @brief Convert a HTML format file or a URL of a Web page to a PDF file.
    *
    * @details Currently, this function can only be used for desktop platforms; for other platform, this function will
    *          return directly without doing anything.
    *
    * @param[in] src_html        A URL of Web page or a HTML format file path. This should not be an empty string.
    * @param[in] engine_path     The directory path of "HTML to PDF" engine. This should not be an empty string.
    * @param[in] cookies_path    Path of cookies file. If this is an empty string, that means no cookie file is used.
    *                            Data format is strongly recommended to use JSON format.
    * @param[in] setting_data    Setting data used for converting.
    * @param[in] saved_pdf_path  A path for saving the converted PDF file. This should not be an empty string.
    * @param[in] timeout         Seconds for timeout used for loading web pages. It should be set to a value greater than 15.
    *                            If this is less than 15, 15 will be used by default.
    *
    * @return None.
    */
   static void FromHTML(const wchar_t* src_html, const wchar_t* engine_path, const wchar_t* cookies_path, const HTML2PDFSettingData& setting_data, const wchar_t* saved_pdf_path, int32 timeout);

   /**
    * @brief Convert a HTML format file or a URL of a Web page to a PDF file.
    *
    * @details Currently, this function can only be used for desktop platforms; for other platform, this function will
    *          return directly without doing anything.
    *
    * @param[in] src_html        A URL of Web page or a HTML format file path. This should not be an empty string.
    * @param[in] engine_path     The directory path of "HTML to PDF" engine. This should not be an empty string.
    * @param[in] cookies_reader  A @link common::file::ReaderCallback @endlink object which is implemented by user to
    *                            pass cookies data to Foxit PDF SDK. If this is <b>NULL</b>, that means no cookie data
    *                            is used. Data format is strongly recommended to use JSON format.
    * @param[in] setting_data    Setting data used for converting.
    * @param[in] saved_pdf_path  A path for saving the converted PDF file. This should not be an empty string.
    * @param[in] timeout         Seconds for timeout used for loading web pages. It should be set to a value greater than 15.
    *                            If this is less than 15, 15 will be used by default.
    *
    * @return None.
    */
   static void FromHTML(const wchar_t* src_html, const wchar_t* engine_path, foxit::common::file::ReaderCallback* cookies_reader, const HTML2PDFSettingData& setting_data, const wchar_t* saved_pdf_path, int32 timeout);

   /**
    * @brief Convert a HTML format file or a URL of a Web page to a PDF file.
    *
    * @details Currently, this function can only be used for desktop platforms; for other platform, this function will
    *          return directly without doing anything.
    * 
    * @param[in] src_html              A URL of Web page or a HTML format file path. This should not be an empty string.
    * @param[in] engine_path           The directory path of "HTML to PDF" engine. This should not be an empty string.
    * @param[in] cookies_reader        A @link common::file::ReaderCallback @endlink object which is implemented by user to
    *                                  pass cookies data to Foxit PDF SDK. If this is <b>NULL</b>, that means no cookie data
    *                                  is used. Data format is strongly recommended to use JSON format.
    * @param[in] setting_data          Setting data used for converting.
    * @param[in] saved_pdf_filestream  A @link common::file::WriterCallback @endlink object for saving the converted PDF file. This should not be <b>NULL</b>.
    * @param[in] timeout               Seconds for timeout used for loading web pages. It should be set to a value greater than 15.
    *                                  If this is less than 15, 15 will be used by default.
    *
    * @return None.
    */
   static void FromHTML(const wchar_t* src_html, const wchar_t* engine_path, foxit::common::file::ReaderCallback* cookies_reader, const HTML2PDFSettingData& setting_data, foxit::common::file::WriterCallback* saved_pdf_filestream, int32 timeout);

   /**
    * @brief Convert a HTML format file or a URL of a Web page to a PDF file.
    *
    * @details Currently, this function can only be used for desktop platforms and mac arm platforms; for other platform, this function will
    *          return directly without doing anything.
    * 
    * @param[in] src_html                         A @link common::file::ReaderCallback @endlink object which is implemented by user to
    *                                             pass html data to Foxit PDF SDK. It must be vaild.
    * @param[in] html2pdf_related_resource_array  The @link HTML2PDFRelatedResourceArray @endlink which is related to source HTML. 
    * @param[in] engine_path                      The directory path of "HTML to PDF" engine. This should not be an empty string.
    * @param[in] cookies_reader                   (Reserved;Not supported yet)A @link common::file::ReaderCallback @endlink object 
    *                                             which is implemented by user to pass cookies data to Foxit PDF SDK. If this is <b>NULL</b>, that means no cookie 
    *                                             data is used. Data format is strongly recommended to use JSON format.
    * @param[in] setting_data                     Setting data used for converting.
    * @param[in] saved_pdf_filestream             A @link common::file::WriterCallback @endlink object for saving the converted PDF file. This should not be <b>NULL</b>.
    * @param[in] timeout                          Seconds for timeout used for loading web pages. It should be set to a value greater than 15.
    *                                             If this is less than 15, 15 will be used by default.
    *
    * @return None.
    */
   static void FromHTML(foxit::common::file::ReaderCallback* src_html, const HTML2PDFRelatedResourceArray& html2pdf_related_resource_array, const wchar_t* engine_path, foxit::common::file::ReaderCallback* cookies_reader, const HTML2PDFSettingData& setting_data, foxit::common::file::WriterCallback* saved_pdf_filestream, int32 timeout);

   /**
    * @brief Convert a TXT format file to a PDF file.
    *
    * @param[in] src_txt         A TXT format file path. This should not be an empty string.
    * @param[in] saved_pdf_path  A path for saving the converted PDF file. This should not be an empty string.
    * @param[in] setting_data    Setting data used for converting.
    *
    * @return None.
    */
   static void FromTXT(const wchar_t* src_txt, const wchar_t* saved_pdf_path, const TXT2PDFSettingData& setting_data);

   /**
    * @brief Convert a Image format file to a PDF file.
    *
    * @param[in] src_img  A image format file path. This should not be an empty string.
    * @param[in] saved_pdf_path  A path for saving the converted PDF file. This should not be an empty string.
    *
    * @return None.
    */
   static void FromImage(const wchar_t* src_img, const wchar_t* saved_pdf_path);

   /**
    * @brief Convert a Image format file to a PDF file.
    *
    * @param[in] file_reader  A @link common::file::ReaderCallback @endlink object which is
    *           implemented by user to pass image data to Foxit PDF SDK. It must be valid.
    * @param[in] saved_pdf_filestream  A @link common::file::WriterCallback @endlink object for saving the
    *           converted PDF file. This should not be <b>NULL</b>.
    *
    * @return None.
    */
   static void FromImage(foxit::common::file::ReaderCallback* file_reader, foxit::common::file::WriterCallback* saved_pdf_filestream);

   /**
    * @brief Convert a DWG format file to a PDF file.
    *
    * @details Currently, this function can only be used for desktop platforms; for other platform, this function will
    *          return <b>false</b> directly without doing anything.
    *
    * @param[in] engine_path     The directory path of "DWG to PDF" engine. This should not be an empty string.
    * @param[in] src_dwg_path    A DWG or DXF format file path. This should not be an empty string.
    * @param[in] saved_pdf_path  A path for saving the converted PDF file. This should not be an empty string.
    * @param[in] settings        The @link DWG2PDFSettingData @endlink object used for converting.
    *
    * @return None.
    */

   static bool FromDWG(const wchar_t* engine_path, const wchar_t* src_dwg_path, const wchar_t* saved_pdf_path,
                       const DWG2PDFSettingData& settings);

#if (defined(_WIN32) || defined(_WIN64))
   /**
    * @brief Convert a Word format file to a PDF file.
    *
    * @details Currently, this function can only be used for Windows.
    *
    * @param[in] src_word_file_path  Path of a Word format file. This should not be an empty string.
    * @param[in] src_file_password   Password for the input Word format file. If no password is needed for the file,
    *                                please pass an empty string.
    * @param[in] saved_pdf_path      Path of the saved PDF file as conversion result. This should not be an empty string.
    * @param[in] setting_data        Setting data used for converting.
    * @param[in] engine              Conversion engine to use. Please refer to values starting from 
    *                                @link Convert::e_Office2PdfEngineMicrosoft @endlink and this should be one of these values.
    *                                Default value:@link Convert::e_Office2PdfEngineMicrosoft @endlink.
    *
    * @return None.
    */
   static void FromWord(const wchar_t* src_word_file_path, const wchar_t* src_file_password, const wchar_t* saved_pdf_path, const Word2PDFSettingData& setting_data, Office2PdfEngine engine = e_Office2PdfEngineMicrosoft);

   /**
    * @brief Convert an Excel format file to a PDF file.
    *
    * @details Currently, this function can only be used for Windows.
    *
    * @param[in] src_excel_file_path  Path of a Excel format file. This should not be an empty string.
    * @param[in] src_file_password    Password for the input Excel format file. If no password is needed for the file,
    *                                 please pass an empty string.
    * @param[in] saved_pdf_path       Path of the saved PDF file as conversion result. This should not be an empty string.
    * @param[in] setting_data         Setting data used for converting.
    * @param[in] engine               Conversion engine to use. Please refer to values starting from 
    *                                 @link Convert::e_Office2PdfEngineMicrosoft @endlink and this should be one of these values.
    *                                 Default value:@link Convert::e_Office2PdfEngineMicrosoft @endlink.
    *
    * @return None.
    */
   static void FromExcel(const wchar_t* src_excel_file_path, const wchar_t* src_file_password, const wchar_t* saved_pdf_path, const Excel2PDFSettingData& setting_data, Office2PdfEngine engine = e_Office2PdfEngineMicrosoft);

   /**
    * @brief Convert a PowerPoint format file to a PDF file.
    *
    * @details Currently, this function can only be used for Windows.
    *
    * @param[in] src_ppt_file_path  Path of a PowerPoint format file. This should not be an empty string.
    * @param[in] src_file_password  Password for the input Excel format file. If no password is needed for the file,
    *                               please pass an empty string.
    * @param[in] saved_pdf_path     Path of the saved PDF file as conversion result. This should not be an empty string.
    * @param[in] setting_data       Setting data used for converting.
    * @param[in] engine             Conversion engine to use. Please refer to values starting from 
    *                               @link Convert::e_Office2PdfEngineMicrosoft @endlink and this should be one of these values.
    *                               Default value:@link Convert::e_Office2PdfEngineMicrosoft @endlink.
    *
    * @return None.
    */
   static void FromPowerPoint(const wchar_t* src_ppt_file_path, const wchar_t* src_file_password, const wchar_t* saved_pdf_path, const PowerPoint2PDFSettingData& setting_data, Office2PdfEngine engine = e_Office2PdfEngineMicrosoft);

#elif defined(__linux__) && !(defined(__ANDROID__) || defined(_FS_IOS_) || defined(_SWIG_ANDROID_) || defined(_SWIG_IOS_))
   /**
    * @brief Convert a Word format file to a PDF file.
    *
    * @details Currently, this function can be used for Linux armv8 or Linux x86/x86_64 system. 
    *          If you are on a Linux armv8 system, then please ensure that WPS professional is installed on the machine.
    *          If you are on a Linux x86/x86_64 system, then please ensure that LibreOffice is installed on the machine.
    *
    * @param[in] src_word_file_path           Path of a Word format file. This should not be an empty string.
    * @param[in] src_file_password            Password for the input Word format file. If no password is needed for the file,
    *                                         please pass an empty string.
    * @param[in] saved_pdf_path               Path of the saved PDF file as conversion result. This should not be an empty string.
    * @param[in] engine_path                  In linux armv8 system, it is used to represent the path of WPS engine(librpcwpsapi.so). For examples, "/opt/kingsoft/wps-office/office6".
    *                                         It can be empty. Default path: "/opt/kingsoft/wps-office/office6".
    *                                         In linux x86/x86_64 system, it is used to represent the path of LibreOffice engine(soffice.bin), and it can not be empty.
    *                                         For examples, "/usr/lib/libreoffice/program".
    * @param[in] setting_data                 (Reserved, unsupported yet)Setting data used for converting.
    * @param[in] fx_engine_path               The path of "Office to PDF" engine. This parameter is applicable only to Linux x86/x86_64 systems. 
    *                                         It can be empty. If the parameter is empty, LibreOffice engine will be called directly for Word to PDF conversion,
    *                                         otherwise LibreOffice engine will be called through the "Office to PDF" engine for Word to PDF conversion.
    * @param[in] specified_user_profile_path  The User-defined directory path to store the user profile of the LibreOffice engine. It needs to be used with "Office to PDF" engine.
    *                                         It can be empty. If the parameter is empty, the LibreOffice engine will use the default user profile and does not suppot multi-threading,
    *                                         otherwise LibreOffice engine will create a new user profile in the User-defined directory to support multi-threading.
    *
    * @return None.
    */
   static void FromWord(const wchar_t* src_word_file_path, const wchar_t* src_file_password, const wchar_t* saved_pdf_path, const wchar_t* engine_path, const Word2PDFSettingData& setting_data, const wchar_t* fx_engine_path = L"", const wchar_t* specified_user_profile_path = L"");

   /**
    * @brief Convert an Excel format file to a PDF file.
    *
    * @details Currently, this function can be used for Linux armv8 or Linux x86/x86_64 system. 
    *          If you are on a Linux armv8 system, then please ensure that WPS professional is installed on the machine.
    *          If you are on a Linux x86/x86_64 system, then please ensure that LibreOffice is installed on the machine.
    *
    * @param[in] src_excel_file_path          Path of a Excel format file. This should not be an empty string.
    * @param[in] src_file_password            Password for the input Excel format file. If no password is needed for the file,
    *                                         please pass an empty string.
    * @param[in] saved_pdf_path               Path of the saved PDF file as conversion result. This should not be an empty string.
    * @param[in] engine_path                  In linux armv8 system, it is used to represent the path of WPS engine(librpcetapi.so). For examples, "/opt/kingsoft/wps-office/office6".
    *                                         It can be empty. Default path: "/opt/kingsoft/wps-office/office6".
    *                                         In linux x86/x86_64 system, it is used to represent the path of LibreOffice engine(soffice.bin), and it can not be empty.
    *                                         For examples, "/usr/lib/libreoffice/program".        
    * @param[in] setting_data                 (Reserved, unsupported yet)Setting data used for converting.
    * @param[in] fx_engine_path               The path of "Office to PDF" engine. This parameter is applicable only to Linux x86/x86_64 systems.
    *                                         It can be empty. If the parameter is empty, LibreOffice engine will be called directly for Excel to PDF conversion,
    *                                         otherwise LibreOffice engine will be called through the "Office to PDF" engine for Excel to PDF conversion.
    * @param[in] specified_user_profile_path  The User-defined directory path to store the user profile of the LibreOffice engine. It needs to be used with "Office to PDF" engine.
    *                                         It can be empty. If the parameter is empty, the LibreOffice engine will use the default user profile and does not suppot multi-threading,
    *                                         otherwise LibreOffice engine will create a new user profile in the User-defined directory to support multi-threading.
    *
    * @return None.
    */
   static void FromExcel(const wchar_t* src_excel_file_path, const wchar_t* src_file_password, const wchar_t* saved_pdf_path, const wchar_t* engine_path, const Excel2PDFSettingData& setting_data, const wchar_t* fx_engine_path = L"", const wchar_t* specified_user_profile_path = L"");

   /**
    * @brief Convert a PowerPoint format file to a PDF file.
    *
    * @details Currently, this function can be used for Linux armv8 or Linux x86/x86_64 system. 
    *          If you are on a Linux armv8 system, then please ensure that WPS professional is installed on the machine.
    *          If you are on a Linux x86/x86_64 system, then please ensure that LibreOffice is installed on the machine.
    *
    * @param[in] src_ppt_file_path            Path of a PowerPoint format file. This should not be an empty string.
    * @param[in] src_file_password            Password for the input Excel format file. If no password is needed for the file,
    *                                         please pass an empty string.
    * @param[in] saved_pdf_path               Path of the saved PDF file as conversion result. This should not be an empty string.
    * @param[in] engine_path                  In linux armv8 system, it is used to represent the path of WPS engine(librpcwppapi.so). For examples, "/opt/kingsoft/wps-office/office6".
    *                                         It can be empty. Default path: "/opt/kingsoft/wps-office/office6".
    *                                         In linux x86/x86_64 system, it is used to represent the path of LibreOffice engine(soffice.bin), and it can not be empty.
    *                                         For examples, "/usr/lib/libreoffice/program".  
    * @param[in] setting_data                 (Reserved, unsupported yet)Setting data used for converting.
    * @param[in] fx_engine_path               The path of "Office to PDF" engine. This parameter is applicable only to Linux x86/x86_64 systems.
    *                                         It can be empty. If the parameter is empty, LibreOffice engine will be called directly for PowerPoint to PDF conversion,
    *                                         otherwise LibreOffice engine will be called through the "Office to PDF" engine for PowerPoint to PDF conversion.
    * @param[in] specified_user_profile_path  The User-defined directory path to store the user profile of the LibreOffice engine. It needs to be used with "Office to PDF" engine.
    *                                         It can be empty. If the parameter is empty, the LibreOffice engine will use the default user profile and does not suppot multi-threading,
    *                                         otherwise LibreOffice engine will create a new user profile in the User-defined directory to support multi-threading.
    *
    * @return None.
    */
   static void FromPowerPoint(const wchar_t* src_ppt_file_path, const wchar_t* src_file_password, const wchar_t* saved_pdf_path, const wchar_t* engine_path, const PowerPoint2PDFSettingData& setting_data, const wchar_t* fx_engine_path = L"", const wchar_t* specified_user_profile_path = L"");
#endif

   /**
    * @brief Convert a PDF file to a XML format file.
    *
    * @param[in] src_pdf_path             Path of a PDF file. This should not be an empty string.
    * @param[in] src_file_password        Password for the input PDF file. If no password is needed for the file, please pass an empty string.
    * @param[in] saved_xml_path           Path of the saved XML format file as conversion result. This should not be an empty string.
    * @param[in] saved_image_folder_path  A path to specify a folder where image files will be generated during the converting.
    *                                     If this is an empty string, image files will be generated to a folder named "images" (if not exist,
    *                                     Foxit PDF SDK will generate such folder by default). Folder "images" would be in the same directory 
    *                                     with saved XML format file (as parameter <i>saved_xml_path</i>).
    * @param[in] is_force_to_tagged_pdf   (Only useful when input PDF file is not a tagged PDF file) 
    *                                     A boolean value to decide whether input PDF file is allowed to be converted to a tagged PDF 
    *                                     when input PDF file is not a tagged PDF:
    *                                     <ul>
    *                                     <li><b>true</b> means input PDF file (which is not tagged PDF yet) will first be converted to a tagged PDF.
    *                                         Then the tagged PDF will be converted to a XML format file.</li>
    *                                     <li><b>false</b> means not allow to convert input PDF file (which is not tagged PDF yet) to a tagged PDF.
    *                                          In this case, input PDF file will not be converted to XML format file and this function will return <b>false</b>.</li>
    *                                     </ul>
    *
    * @return <b>true</b> means success, while <b>false</b> means failure.
    */
   static bool ToXML(const wchar_t* src_pdf_path, const wchar_t* src_file_password, const wchar_t* saved_xml_path, const wchar_t* saved_image_folder_path, bool is_force_to_tagged_pdf);

#if (defined(_WIN32) || defined(_WIN64)) || defined(__linux__) 
   /**
    * @brief Convert OFD file to PDF file.
    * 
    * @details Please ensure @link common::Library::InitializeOFDEngine @endlink has been called successfully before using this function.
    *
    * @param[in] src_ofd_path         A full path of an existing OFD file. It should not be an empty string.
    * @param[in] password             Password for the OFD file. It should be an empty string if the OFD file is not encrypted.
    * @param[in] saved_pdf_file_path  A full path for the converted PDF file. It should not be an empty string.
    * @param[in] convert_param        A convert parameter object.
    *
    * @return <b>true</b> means success, while <b>false</b> means failure.
    */
   static bool FromOFD(const wchar_t* src_ofd_path, const wchar_t* password, const wchar_t* saved_pdf_file_path, OFDConvertParam convert_param);

   /**
    * @brief Convert PDF file to OFD file.
    *
    * @details Please ensure @link common::Library::InitializeOFDEngine @endlink has been called successfully before using this function.
    *
    * @param[in] src_pdf_path         A full path of an existing PDF file. It should not be an empty string.
    * @param[in] password             Password for the PDF file. It should be an empty string if the PDF file is not encrypted.
    * @param[in] saved_ofd_file_path  A full path for the converted OFD file. It should not be an empty string.
    * @param[in] convert_param        A convert parameter object.
    *
    * @return <b>true</b> means success, while <b>false</b> means failure.
    */
   static bool ToOFD(const wchar_t* src_pdf_path, const wchar_t* password, const wchar_t* saved_ofd_file_path, OFDConvertParam convert_param);
#endif // #if (defined(_WIN32) || defined(_WIN64)) || defined(__linux__)

};
}
}
}
#endif
