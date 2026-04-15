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
 * @file fs_optimization.h
 * @brief Header file for PDF optimization related definitions and classes.
 */

#ifndef FS_PDFOPTIMIZATION_H_
#define FS_PDFOPTIMIZATION_H_

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
 * @brief Optimization namespace.
 */
namespace optimization {
class ImageSettings;
class MonoImageSettings;
class OptimizerSettings;
class OptimizeScannedPDFSettings;

/** @brief Structure of audit space, the unit is byte type. */
class AuditSpaceSize FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  AuditSpaceSize()
    : content_streams(0)
    , images(0)
    , fonts(0)
    , bookmarks(0)
    , x_object_forms(0)
    , structure_infos(0)
    , acroforms(0)
    , link_annots(0)
    , named_destnations(0)
    , color_space(0)
    , pattern_infos(0)
    , piece_infos(0)
    , comments_and_3d_contents(0)
    , shading_pattern_infos(0)
    , extend_graphics_states(0)
    , cross_ref_tables(0)
    , thumbs(0)
    , embed_files(0)
    , web_infos(0) { }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another Audit Space Size data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  AuditSpaceSize & operator = (const AuditSpaceSize & data) {
    content_streams = data.content_streams;
    images = data.images;
    fonts = data.fonts;
    bookmarks = data.bookmarks;
    x_object_forms = data.x_object_forms;
    named_destnations = data.named_destnations;
    structure_infos = data.structure_infos;
    acroforms = data.acroforms;
    link_annots = data.link_annots;
    color_space = data.color_space;
    pattern_infos = data.pattern_infos;
    piece_infos = data.piece_infos;
    comments_and_3d_contents = data.comments_and_3d_contents;
    shading_pattern_infos = data.shading_pattern_infos;
    extend_graphics_states = data.extend_graphics_states;
    cross_ref_tables = data.cross_ref_tables;
    thumbs = data.thumbs;
    embed_files = data.embed_files;
    web_infos = data.web_infos;
    return (*this);
  }

  /**
   * @brief Total size of all page content streams in bytes.
   *
   * @details Content streams include the actual PDF instructions for rendering page content.
   */
  uint32 content_streams;

  /**
   * @brief Total size of embedded images in bytes.
   *
   * @details Includes all raster images used across the document.
   */
  uint32 images;

  /**
   * @brief Total size of embedded fonts in bytes.
   *
   * @details Includes both fully and partially embedded font programs.
   */
  uint32 fonts;

  /**
   * @brief Total size of bookmarks data in bytes.
   *
   * @details Bookmarks (or outlines) help navigate a PDF document's content hierarchy.
   */
  uint32 bookmarks;

  /**
   * @brief Total size of XObject Forms in bytes.
   *
   * @details XObject Forms are reusable content streams that can be drawn multiple times.
   */
  uint32 x_object_forms;

  /**
   * @brief Total size of structural information in bytes.
   *
   * @details Structural information includes tagged PDF structures used for accessibility and reflow.
   */
  uint32 structure_infos;

  /**
   * @brief Total size of AcroForm data in bytes.
   *
   * @details AcroForms define interactive form fields in PDF documents.
   */
  uint32 acroforms;

  /**
   * @brief Total size of link annotations in bytes.
   *
   * @details Includes all hyperlink and navigation annotations within the document.
   */
  uint32 link_annots;

  /**
   * @brief Total size of named destinations in bytes.
   *
   * @details Named destinations are predefined navigation targets used by links and outlines.
   */
  uint32 named_destnations;

  /**
   * @brief Total size of color space definitions in bytes.
   *
   * @details Includes all color space objects like ICC profiles, CalRGB, DeviceN, etc.
   */
  uint32 color_space;

  /**
   * @brief Total size of pattern objects in bytes.
   *
   * @details Includes tiling and shading patterns used for fills and strokes.
   */
  uint32 pattern_infos;

  /**
   * @brief Total size of piece information in bytes.
   *
   * @details PieceInfo is used by some workflows to store private application data.
   */
  uint32 piece_infos;

  /**
   * @brief Total size of comments and 3D contents in bytes.
   *
   * @details Includes PDF comments and embedded 3D object data, such as U3D or PRC models.
   */
  uint32 comments_and_3d_contents;

  /**
   * @brief Total size of shading pattern information in bytes.
   *
   * @details Covers all shading patterns used for gradient fills.
   */
  uint32 shading_pattern_infos;

  /**
   * @brief Total size of extended graphics states in bytes.
   *
   * @details Extended graphics states control rendering properties like transparency, blend modes, and line styles.
   */
  uint32 extend_graphics_states;

  /**
   * @brief Total size of the cross-reference table in bytes.
   *
   * @details The cross-reference table maps object numbers to byte offsets in the PDF file.
   */
  uint32 cross_ref_tables;

  /**
   * @brief Total size of page thumbnails in bytes.
   *
   * @details Thumbnails are small preview images associated with pages.
   */
  uint32 thumbs;

  /**
   * @brief Total size of embedded file streams in bytes.
   *
   * @details Embedded files include attachments such as spreadsheets, text files, or other documents.
   */
  uint32 embed_files;

  /**
   * @brief Total size of web-related metadata in bytes.
   *
   * @details Web info may include additional metadata used for web viewing or cataloging.
   */
  uint32 web_infos;
};

/**
 * This class represent a callback object used during the process to optimizie PDF document.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 */
class ImageCompressionCallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief Get temporary file stream. The file stream is used for saving the encoding result of JPEG2000 and JBIG2 temporarily.
   *
   * @param[in] bitmap  A bitmap object need to be encoded.
   * 
   * @return A @link common::file::StreamCallback @endlink object which is implemented by user. This callback would be used to save image data.
   *         Foxit PDF SDK will call the callback function @link common::file::StreamCallback::Release @endlink of the returned stream object 
   *         when it is no longer needed.
   */
  virtual common::file::StreamCallback* GetTemporaryFileStream(const common::Bitmap& bitmap) = 0;

 protected:
  ~ImageCompressionCallback() {}
};

/** 
 * This class can be used to optimize PDF file to reduce file size.
 * Before using this class to do optimization, please ensure Foxit PDF SDK has been initialized successfully
 * by function @link common::Library::Initialize @endlink with a key including "Optimizer" module.
 *
 * @see @link common::Library @endlink
 */ 
class Optimizer FS_FINAL : public Base {
 public:
  typedef foxit::addon::optimization::OptimizerSettings OptimizerSettings;
  typedef foxit::addon::optimization::OptimizeScannedPDFSettings OptimizeScannedPDFSettings;
  /**
   * @brief Optimize the given PDF document with specified optimizer settings.
   *
   * @param[in] doc       A valid PDF document object to be optimized.
   * @param[in] settings  Setting data used for optimization processing settings.
   * @param[in] pause     Pause object which decides if the process needs to be paused.
   *                      This can be <b>NULL</b> which means not to pause during the optimization process.
   *                      If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *
   * @note If module "Optimizer" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using Optimization related functions and
   *       this function will throw exception @link foxit::e_ErrNoOptimizerModuleRight @endlink.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  static common::Progressive Optimize(const pdf::PDFDoc& doc,const OptimizerSettings& settings,common::PauseCallback* pause);
    
  /**
   * @brief Start to make subsets for embedded fonts in the given PDF document.
   *
   * @details This function can be used to remove useless embedded characters from the data of embedded fonts (if there's any in a PDF document)
   *          in order to reduce the size of a PDF document.
   *
   * @param[in] doc       A valid PDF document object to be processed a subset of embedded fonts.
   * @param[in] pause     Pause object which decides if the process needs to be paused.
   *                      This can be <b>NULL</b> which means not to pause during the embeded font subset process.
   *                      If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *
   * @note If module "Optimizer" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using Optimization related
   *       functions and this function will throw exception @link foxit::e_ErrNoOptimizerModuleRight @endlink.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  static common::Progressive StartSubsetEmbedFont(const pdf::PDFDoc& doc, common::PauseCallback* pause);
  
  /**
   * @brief Optimize the scanned PDF document with specified optimizers settings.
   *
   * @param[in] doc                      A valid PDF document object to be optimized.
   * @param[in] settings                 Setting data used for optimization processing settings.
   * @param[in] image_compress_callback  A @link foxit::addon::optimization::ImageCompressionCallback @endlink object which is implemented by user
   *                                     for temp file data during replacing page process. When replacing pages process is finished (no matter successfully or not),
   *                                     callback function @link foxit::addon::optimization::ImageCompressionCallback::Release @endlink will be called by Foxit PDF SDK.
   * @param[in] pause                    Pause object which decides if the process needs to be paused.
   *                                     This can be <b>NULL</b> which means not to pause during the optimization process.
   *                                     If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *
   * @note If module "Optimizer" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using Optimization related functions and
   *       this function will throw exception @link foxit::e_ErrNoOptimizerModuleRight @endlink.
   *       If optimize the scanned pdf finished, the specify pages to be optimized needs to be reloaded.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to coninue the progress until the progress is finished.
   */
  static common::Progressive OptimizeScannedPDF(const pdf::PDFDoc& doc, const OptimizeScannedPDFSettings& settings, ImageCompressionCallback* image_compress_callback, common::PauseCallback* pause);

  /**
   * @brief Compute audit space.
   *
   * @param[in] doc  A valid PDF document object to audit space.
   *
   * @return A struct that contain all audit space contents.
   */
  static AuditSpaceSize ComputeAuditSpace(const pdf::PDFDoc& doc);
};

/**
 * This class represents downsampling/recompression settings for color and grayscale images. 
 * This class object can be set to class @link OptimizerSettings @endlink and then be used to optimize a PDF document.
 *
 * @see @link OptimizerSettings @endlink
 */
class ImageSettings FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for compression mode used for color or gray image.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ImageCompressMode {
    /** @brief Compression mode: high. This flag will be invalid if the image dpi is less than 200.*/
    e_ImageCompressHigh = 10003,
    /** @brief Compression mode: jpeg. */
    e_ImageCompressjpeg = 10005,
    /** @brief Compression mode: jpeg2000. */
    e_ImageCompressjpeg2000 = 10006,
    /** @brief Compression mode: retain, which means no compression. */
    e_ImageCompressRetain  = 10007,
    /** @brief Compression mode: zip. */
    e_ImageCompressZip = 10009
  } ImageCompressMode;
  
  /**
   * @brief Enumeration for loss compression quality used for color or gray image.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ImageCompressQuality {
    /** @brief Compression quality: Minimum. */
    e_ImageCompressQualityMinimum = 1,
    /** @brief Compression quality: Low. */
    e_ImageCompressQualityLow = 2,
    /** @brief Compression quality: Medium. */
    e_ImageCompressQualityMedium = 3,
    /** @brief Compression quality: High. */
    e_ImageCompressQualityHigh  = 4,
    /** @brief Compression quality: Maximum. */
    e_ImageCompressQualityMaximum  = 5,
    /** @brief Compression quality: Lossless, only for jpeg2000 compress mode. */
    e_ImageCompressQualityLossless = 6
  } ImageCompressQuality;
  
  /**
   * @brief Enumeration for stretch mode.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _StretchMode {
    /** @brief When this is set, that means to do default stretching. */
    e_StretchDefault = -1,
    /** @brief When this is set, that means to do without stretching */
    e_StretchOff = 0x00,
    /** @brief When this is set, that means to do interpolation for zooming. */
    e_StretchInterpol = 0x20,
    /** @brief When this is set, that means not to do halftone for shrinking or rotating*/
    e_StretchDownsample = 0x04,
    /** @brief When this is set, that means to do bicubic interpolation for zooming. */
    e_StretchBicubic = 0x80,
    /** @brief When this is set, that means not to do any interpolation for stretching. */
    e_StretchNoSmooth = 0x100
  } StretchMode;
  
  /**
   * @brief Constructor.
   *
   * @details This constructor is to construct a color/gray image settings object with default setting options.
   *          User can also call "set" methods in this class to change these setting options.
   *          Please refer to comment of these "set" methods for more details about default values.
   */
  ImageSettings();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit ImageSettings(FS_HANDLE handle);

  /** @brief Destructor. */
  ~ImageSettings();

  /**
   * @brief Constructor, with another image settings object.
   *
   * @param[in] other  Another image settings object.
   */
  ImageSettings(const ImageSettings& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another image settings object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  ImageSettings& operator = (const ImageSettings& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another image settings object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const ImageSettings& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another image settings object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const ImageSettings& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set stretch mode used for optimizing color/gray images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set this option,
   *          that means to use @link ImageSettings::e_StretchBicubic @endlink as the default value of this option.
   *
   * @param[in] mode  Stretch mode. Please refer to values starting from @link ImageSettings::e_StretchOff @endlink
   *                  and this should be one of these values.
   *
   * @return None.
   */
   void SetStretchMode(StretchMode mode);

  /**
   * @brief Set the DPI value as the target compressed value for compressing color/gray images in a PDF document.
   *
   * @details When an image can be compressed, the resolution of this image will be compressed to the DPI value set by current function.<br>
   *          For a newly constructed object, if this function is not called to set option,
   *          that means to use 150 as the default value of this option.
   *
   * @param[in] dpi  DPI value which is set to be the target compressed DPI value.
   *
   * @return None.
   */
  void SetImageDPI(int32 dpi);

  /**
   * @brief Set the lower limit DPI value for the color/gray image to decide if the image is to be compressed in a PDF document.
   *
   * @details If the resolution of an image in the PDF document is above the lower limit DPI value, this image will be compressed to
   *          the target compressed DPI value which is set by function @link ImageSettings::SetImageDPI @endlink.<br>
   *          For a newly constructed object, if this function is not called to set option,
   *          that means a DPI value (which is 1.5 times of target compressed DPI value) will
   *          be used as the default value of this option.
   *
   * @param[in] dpi_limit  DPI value as the lower limit. This value should be a positive number. Suggested range:
   *                       bigger than target compressed DPI value (set by function @link ImageSettings::SetImageDPI @endlink) and
   *                       the maximum value is 10 times of target compressed DPI value. <br>
   *                       If input value is not bigger than the target compressed DPI value, a DPI value which is one more than
   *                       the target compressed DPI value will be used instead.<br>
   *                       If input value is bigger than the maximum value, the maximum value value will be used instead.
   *
   * @return None.
   */
  void SetImageDPILimit(int dpi_limit);

  /**
   * @brief Set compression mode used for optimizing color/gray images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set option,
   *          that means to use @link ImageSettings::e_ImageCompressjpeg @endlink as the default value of this option.
   *
   * @param[in] mode  Image compression mode. Please refer to values starting from @link ImageSettings::e_ImageCompressHigh @endlink
   *                  and this should be one of these values.
   *
   * @return None.
   */
  void SetCompressionMode(ImageCompressMode mode);

  /**
   * @brief Set the quality for lossy compression modes, used for optimizing color/gray images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set this option,
   *          that means to use @link ImageSettings::e_ImageCompressQualityMinimum @endlink as
   *          the default value of this option.
   *
   * @param[in] quality  Quality value for lossy compression modes. Please refer to values starting from
   *                     @link ImageSettings::e_ImageCompressQualityMinimum @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetQuality(ImageCompressQuality quality);
  
  /**
   * @brief Set the background downscale value for lossy compression modes, used for optimizing color images in a PDF document.
   *
   * @details This function is used to reduce the resolution of the background image. 
   *
   * @param[in] down_scale  Background downscale value for lossy compression modes. It should be above 0.
   *                        If the value is 1, the background resolution is not reduced. 
   *                        If the value is larger than 1, the higher the value, the lower the background resolution.
   *                        If this function is not called to set this option, that means to use 3 as the default value of this option.
   *
   * @return None.
   */
  void SetBackgroundDownScale(int32 down_scale);
  
  /**
   * @brief Set the foreground downscale value for lossy compression modes, used for optimizing color images in a PDF document.
   *
   * @details This function is used to reduce the resolution of the foreground image. 
   *
   * @param[in] down_scale  Foreground downscale value for lossy compression modes. It should be above 0.
   *                        If the value is 1, the foreground resolution is not reduced. 
   *                        If the value is larger than 1, the higher the value, the lower the foreground resolution.
   *                        If this function is not called to set this option, that means to use 3 as the default value of this option.
   *
   * @return None.
   */
  void SetForegroundDownScale(int32 down_scale);

  /**
   * @brief Set the text sensitivity for lossy compression modes, used for optimizing color images in a PDF document.
   *
   * @details This function affects the segmentation into foreground (usually text) and background. 
   *          if this function is not called to set this option, that means to use 60 as the default value of this option.
   *
   * @param[in] text_sensitivity  The value of text sensitivity. A higher sensitivity value
   *                              results in more content represented in the foreground. The value is especially important in
   *                              case of documents with low contrast and documents with patterns, images or color in
   *                              background. Instead, the effect on simple text documents with high contrast, clear bright
   *                              background and sharp dark symbols is low.
   *                              Valid values: from 0 to 100.
   *
   * @return None. 
   */
  void SetTextSensitivity(int32 text_sensitivity);
  
  /**
   * @brief Set the tile size for JPEG2000 compression modes, used for optimizing color/gray images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set this option,
   *          that means to use 256 as the default value of this option.
   *
   * @param[in] size  The size of tile, and this value can only be between 128 and 2048.
   *
   * @note This method only valid in @link ImageSettings::e_ImageCompressjpeg2000 @endlink compression mode.
   *
   * @return None.
   */
  void SetTileSize(int size);
};

/**
 * This class represents downsampling/recompression settings for monochrome images.
 * This class object can be set to class @link OptimizerSettings @endlink and then be used to optimize a PDF document.
 *
 * @see @link OptimizerSettings @endlink
 */
class MonoImageSettings FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for compression mode used for monochrome image.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _MonoImageCompressMode {
    /** @brief Compression mode: CCITT Group 3. */
    e_ImageCompressCCITT3 = 10001,
    /** @brief Compression mode: CCITT Group 4. */
    e_ImageCompressCCITT4 = 10002,
    /** @brief Compression mode: high.*/
    e_ImageCompressHigh = 10003,
    /** @brief Compression mode: jbig2. */
    e_ImageCompressjbig2 = 10004,
    /** @brief Compression mode: retain, which means no compression. */
    e_ImageCompressRetain  = 10007,
    /** @brief Compression mode: run-length. */
    e_ImageCompressRunLength = 10008,
    /** @brief Compression mode: zip. */
    e_ImageCompressZip = 10009
  } MonoImageCompressMode;
  
  /**
   * @brief Enumeration for compression quality used for monochrome image.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _MonoImageCompressQuality {
    /** @brief Compression quality: Lossless. */
    e_ImageCompressQualityLossless = 1,
    /** @brief Compression quality: Lossy. */
    e_ImageCompressQualityLossy = 2,
    /** @brief Compression quality: Minimum, only for e_ImageCompressHigh compress mode. */
    e_ImageCompressQualityMinimum = 3,
    /** @brief Compression quality: Low, only for e_ImageCompressHigh compress mode. */
    e_ImageCompressQualityLow = 4,
    /** @brief Compression quality: Medium, only for e_ImageCompressHigh compress mode. */
    e_ImageCompressQualityMedium = 5,
    /** @brief Compression quality: High, only for e_ImageCompressHigh compress mode. */
    e_ImageCompressQualityHigh = 6,
    /** @brief Compression quality: Maximum, only for e_ImageCompressHigh compress mode. */
    e_ImageCompressQualityMaximum = 7
  } MonoImageCompressQuality;
  
  /**
   * @brief Enumeration for stretch mode.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _StretchMode {
    /** @brief When this is set, that means to do default stretching. */
    e_StretchDefault = -1,
    /** @brief When this is set, that means to do without stretching */
    e_StretchOff = 0x00,
    /** @brief When this is set, that means to do interpolation for zooming. */
    e_StretchInterpol = 0x20,
    /** @brief When this is set, that means not to do halftone for shrinking or rotating*/
    e_StretchDownsample = 0x04,
    /** @brief When this is set, that means to do bicubic interpolation for zooming. */
    e_StretchBicubic = 0x80,
    /** @brief When this is set, that means not to do any interpolation for stretching. */
    e_StretchNoSmooth = 0x100
  } StretchMode;
  
  /**
   * @brief Constructor.
   *
   * @details This constructor is to construct a monochrome image settings object with default setting options.
   *          User can also call "set" methods in this class to change these setting options.
   *          Please refer to comment of these "set" methods for more details about default values.
   */
  MonoImageSettings();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit MonoImageSettings(FS_HANDLE handle);

  /** @brief Destructor. */
  ~MonoImageSettings();

  /**
   * @brief Constructor, with another result information object.
   *
   * @param[in] other  Another monochrome image settings object.
   */
  MonoImageSettings(const MonoImageSettings& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another monochrome image settings object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  MonoImageSettings& operator = (const MonoImageSettings& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another monochrome image settings object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const MonoImageSettings& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another monochrome image settings object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const MonoImageSettings& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set the DPI value as the target compressed value for compressing monochrome images in a PDF document.
   *
   * @details When an image can be compressed, the resolution of this image will be compressed to the DPI value set by current function.<br>
   *          For a newly constructed object, if this function is not called to set option,
   *          that means to use 250 as the default value of this option.
   *
   * @param[in] dpi  DPI value. If the images can be compressed, the resolution of these images will be compressed to this value.
   *
   * @return None.
   */
  void SetImageDPI(int32 dpi);

  /**
   * @brief Set the lower limit DPI value for the monochrome image to decide if the image is to be compressed in a PDF document.
   *
   * @details If the resolution of an image in the PDF document is above the lower limit DPI value, this image will be compressed to
   *          the target compressed DPI value which is set by function @link MonoImageSettings::SetImageDPI @endlink.<br>
   *          For a newly constructed object, if this function is not called to set option,
   *          that means a DPI value (which is 1.5 times of target compressed DPI value) will
   *          be used as the default value of this option.
   *
   * @param[in] dpi_limit  DPI value as the lower limit. This value should be a positive number. Suggested range:
   *                       bigger than target compressed DPI value (set by function @link MonoImageSettings::SetImageDPI @endlink) and
   *                       the maximum value is 10 times of target compressed DPI value. <br>
   *                       If input value is not bigger than the target compressed DPI value, a DPI value which is one more than
   *                       the target compressed DPI value will be used instead.<br>
   *                       If input value is bigger than the maximum value, the maximum value value will be used instead.
   *
   * @return None.
   */
  void SetImageDPILimit(int dpi_limit);

  /**
   * @brief Set compression mode used for optimizing monochrome images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set option,
   *          that means to use @link MonoImageSettings::e_ImageCompressCCITT4 @endlink as the default value of this option.
   *
   * @param[in] mode  Image compression mode. Please refer to values starting from @link MonoImageSettings::e_ImageCompressHigh @endlink
   *                  and this should be one of these values.
   *
   * @return None.
   */
  void SetCompressionMode(MonoImageCompressMode mode);

  /**
   * @brief Set stretch mode used for optimizing monochrome images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set this option,
   *          that means to use @link MonoImageSettings::e_StretchBicubic @endlink as the default value of this option.
   *
   * @param[in] mode  Stretch mode. Please refer to values starting from @link ImageSettings::e_StretchOff @endlink
   *                  and this should be one of these values.
   *
   * @return None.
   */
  void SetStretchMode(StretchMode mode) ;

  /**
   * @brief Set compression quality, used for optimizing monochrome images in a PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set this option,
   *          that means to use @link MonoImageSettings::e_ImageCompressQualityLossless @endlink
   *          as the default value of this option.
   *
   * @param[in] quality  Compression quality. Please refer to values starting from
   *                     @link MonoImageSettings::e_ImageCompressQualityLossless @endlink
   *                     and this should be one of these values.
   *
   * @return None.
   */
   void SetQuality(MonoImageCompressQuality quality);
};

/**
 * This class represents the settings for unembedded fonts.
 * This class object can be set to class @link OptimizerSettings @endlink and then be used to optimize a PDF document.
 *
 * @see @link OptimizerSettings @endlink
 */
class UnembeddedFontSettings FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor.
   */
  UnembeddedFontSettings();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit UnembeddedFontSettings(FS_HANDLE handle);

  /** @brief Destructor. */
  ~UnembeddedFontSettings();

  /**
   * @brief Constructor, with another unembedded font settings object.
   *
   * @param[in] other  Another ImageSettings object.
   */
  UnembeddedFontSettings(const UnembeddedFontSettings& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another unembedded font settings object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  UnembeddedFontSettings& operator=(const UnembeddedFontSettings& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another unembedded font settings object. This function will check if current object is equal to this
   *                   one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const UnembeddedFontSettings& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another unembedded font settings object. This function will check if current object is not equal to
   *                   this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const UnembeddedFontSettings& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Sets whether to include subsets of all unembedded fonts.
   *
   * @param[in] is_subset_all_emb_fonts  <b>true</b> means to include subsets of all unembedded fonts.
   *                                     <b>false</b> means not to include subsets of all unembedded fonts.
   *
   * @return void.
   */
  void SetSubsetAllEmFonts(bool is_subset_all_emb_fonts);

  /**
   * @brief Set a font name array to specify which fonts are to be unembeded.
   *
   * @details This function can be used to specify which fonts are to be unembedded.
   *          User can use function @link pdf::PDFDoc::GetEmbeddedFontData @endlink to
   *          get the embedded font name arrays of a PDF document, then decide which embeded fonts are to be unembeded,
   *          and pass the unembeded font name array to current function.
   *
   * @param[in] font_name_array  A font name array to specify which fonts are to be unembeded.
   *
   * @return None.
   */
  void SetUnembeddedFontNameArray(const WStringArray& font_name_array);
};

/**
 * This class represents settings for optimizing a PDF document. It would be used in class @link Optimizer @endlink.
 *
 * @see @link Optimizer @endlink
 */
class OptimizerSettings FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for optimizer options.
   *
   * @details Values of this enumeration can be used alone or in a combination.
   */
  typedef enum _OptimizerOptions {
    /** @brief Optimize PDF document by compressing images. */
    e_OptimizerCompressImages  = 0x01,
    /** @brief Optimize PDF document by cleaning up. */
    e_OptimizerCleanUp = 0x02,
    /** @brief Optimize PDF document by discarding objects. */
    e_OptimizerDiscardObjects = 0x04,
    /** @brief Optimize PDF document by unembedding some embedded fonts. */
    e_OptimizerUnembeddedFonts = 0x08,
    /** @brief Optimize PDF document by discarding user data. */
    e_OptimizerDiscardUserData = 0x10,
    /** @brief Optimize PDF document by doing transparency. */
    e_OptimizerTransparency = 0x20
  } OptimizerOptions;
  
  /**
   * @brief Enumeration for cleaning up options.
   *
   * @details Values of this enumeration can be used alone or in a combination.
   */
  typedef enum _CleanUpOptions {
    /** @brief Use Flate to encode streams that are not encoded. */
    e_CleanUpUseFlateForNonEncodedStream  = 0x01,
    /** @brief In streams that use LZW encoding, use Flate instead. */
    e_CleanUpUseFlateInsteadOfLZW = 0x02,
    /** @brief Remove invalid bookmarks.*/
    e_CleanUpRemoveInvalidBookmarks = 0x04,
    /** @brief Remove invalid links. */
    e_CleanUpRemoveInvalidLinks = 0x08,
    /** @brief Discard unreferenced named destination. */
    e_CleanUpDiscardUnreferencedNamedDes = 0x10,
    /** @brief Cleanup page content Change 0A,0D in the content stream to Spaces*/
    e_CleanUpOptPageContent = 0x20
  } CleanUpOptions;
  
  /**
   * @brief Enumeration for discarding objects options.
   *
   * @details Values of this enumeration can be used alone or in a combination.
   */
  typedef enum _DiscardObjectsOptions {
    /** @brief Discard all form submission, import and reset actions. */
    e_DiscardObjectsFormActions  = 0x01,
    /** @brief Flatten form fields. */
    e_DiscardObjectsFlattenFormFields = 0x02,
    /**
     * @brief Discard all JavaScript actions.
     * 
     * @details Currently, it can not remove the javascript action in "OpenAction" of catalog. 
     */
    e_DiscardObjectsJavaScriptActions = 0x04,
    /** @brief Discard embedded page thumbnails. */
    e_DiscardObjectsEmbeddedPageThumbnails = 0x08,
    /** @brief Discard embedded print settings. */
    e_DiscardObjectsEmbeddedPrintSettings = 0x10,
    /** @brief Discard bookmarks. */
    e_DiscardObjectsBookmarks = 0x20,
    /**
     * @brief Discard all alternate images.
     *
     * @details Some PDF documents include multiple versions of the same image for different purposes,
     *          such as low-resolution on-screen viewing and high-resolution printing.
     *          If this option value is set to be used, that means to remove all versions of
     *          an image except the one destined for on-screen viewing.
     */
    e_DiscardObjectsAlternateImages = 0x40,
    /** @brief Discard document tags. */
    e_DiscardObjectsDocumentTags = 0x80,
    /** @brief Discard embedded search index. */
    e_DiscardObjectsEmbeddedSearchIndex = 0x100,
    /** @brief Detect and merge image fragments. */
    e_DiscardObjectsDetectAndMergeImageFragment = 0x200,
    /** @brief smooth lines to curves*/
    e_DiscardObjectsSmoothlinestocurves = 0x400
  } DiscardObjectsOptions;
  
  /**
   * @brief Enumeration for discarding user data options.
   *
   * @details Values of this enumeration can be used alone or in a combination.
   */
  typedef enum _DiscardUserDataOptions {
    /** @brief Discard all annotations, forms and multimedia. */
    e_DiscardUserDataAllAnnotsFormsAndMultimedia  = 0x01,
    /** @brief Discard external cross references. */
    e_DiscardUserDataExternalCrossReferences = 0x02,
    /** @brief Discard document information and metadata. */
    e_DiscardUserDataDocumentInfoAndMetaData = 0x04,
    /** @brief Discard file attachments. */
    e_DiscardUserDataFileAttchments = 0x08,
    /** @brief Discard private data of other applications. */
    e_DiscardUserDataPrivateDataOfOtherApp = 0x10,
    /** @brief Discard hidden layer content and flatten visible layers. */
    e_DiscardUserDataLayer = 0x20,
    /** @brief discard tag user data */
    e_DiscardUserAllData = 0x40
  } DiscardUserDataOptions;
  
  /**
   * @brief Enumeration for transparency mode.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _TransparencyMode {
    /** 
     * @brief Transparency mode: low resolution.
     * 
     * @details Low resolution includes: Transparency level: 75; Line Art and Text: 288;
     *                                   Gradient and Meshes: 144; Convert All Text to Outlines: False;
     *                                   Convert All Strokes to Outlines: True;
     *                                   Clip Complex Regions: False;
     *                                   Preserve Overprint Settings: True.
     */
    e_TransparencyModeLowResolution = 0,
    /**
     * @brief Transparency mode: medium resolution.
     *
     * @details Medium resolution includes: Transparency level: 75; Line Art and Text: 300;
     *                                      Gradient and Meshes: 150; Convert All Text to Outlines: False;
     *                                      Convert All Strokes to Outlines: True;
     *                                      Clip Complex Regions: True;
     *                                      Preserve Overprint Settings: True.
     */
    e_TransparencyModeMediumResolution = 1,
    /**
     * @brief Transparency mode: high resolution.
     *
     * @details High resolution includes: Transparency level: 100; Line Art and Text: 1200;
     *                                    Gradient and Meshes: 300; Convert All Text to Outlines: False;
     *                                    Convert All Strokes to Outlines: False;
     *                                    Clip Complex Regions: True;
     *                                    Preserve Overprint Settings: True.
     */
    e_TransparencyModeHighResolution = 2
  } TransparencyMode;
  

  /**
   * @brief Constructor.
   *
   * @details This constructor is to construct a optimizer settings object with default setting options.
   *          User can also call "set" methods in this class to change setting options.
   *          Please refer to comment in other settings class (which can be set to current object)
   *          for more details about what default setting options are.
   */
  OptimizerSettings(); 

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit OptimizerSettings(FS_HANDLE handle);

  /** @brief Destructor. */
  ~OptimizerSettings();

  /**
   * @brief Constructor, with another optimizer settings object.
   *
   * @param[in] other  Another optimizer settings object.
   */
  OptimizerSettings(const OptimizerSettings& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another optimizer settings object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  OptimizerSettings& operator = (const OptimizerSettings& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another optimizer settings object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const OptimizerSettings& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another optimizer settings object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const OptimizerSettings& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set options to decide which kind of optimizer setting will be used for optimizing PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set any optimizer options,
   *          that means no optimizer setting is useful.
   *
   * @param[in] optimize_options  The options to decide which kind of optimizer setting will be used for optimizing PDF document.
   *                              0 means no optimizer setting of any kind is useful. Please refer to values starting from
   *                              @link OptimizerSettings::e_OptimizerCompressImages @endlink and this can be one or
   *                              a combination of these values.
   *
   * @return None.
   */
  void SetOptimizerOptions(uint32 optimize_options);

 /**
  * @deprecated Current function has been deprecated since Foxit PDF SDK 10.0. 
  *             This function will not have any effect on @link OptimizerSettings @endlink any more.
  *             For setting color image, please call function @link OptimizerSettings::SetColorImageSettings @endlink. 
  *             Please refer to <b>SetColorImageSettings</b> related function in @link OptimizerSettings @endlink for more details.
  *             For setting grayscale image, please call function @link OptimizerSettings::SetGrayscaleImageSettings @endlink.
  *             Please refer to <b>SetGrayscaleImageSettings</b> related function in @link OptimizerSettings @endlink for more details.
  *
  * @brief Set optimization related settings for color/gray image.
  *
  * @details For a newly constructed object, if this function is not called to set any color/gray image settings,
  *          that means to use default color/gray image settings. Please refer to comment in
  *          class @link ImageSettings @endlink for default values.<br>
  *          ImageSettings set by this function is useful only when option value
  *          @link OptimizerSettings::e_OptimizerCompressImages @endlink is set by
  *          function @link OptimizerSettings::SetOptimizerOptions @endlink.
  *
  * @param[in] settings  Optimization related settings for color and grayscale images.
  *
  * @return None.
  */
  void SetColorGrayImageSettings(const ImageSettings& settings);

  /**
   * @brief Set optimization related settings for color image.
   *
   * @details For a newly constructed object, if this function is not called to set any color image settings,
   *          that means to use default color image settings. Please refer to comment in
   *          class @link ImageSettings @endlink for default values.<br>
   *          ImageSettings set by this function is useful only when option value
   *          @link OptimizerSettings::e_OptimizerCompressImages @endlink is set by
   *          function @link OptimizerSettings::SetOptimizerOptions @endlink.
   *
   * @param[in] settings  Optimization related settings for color images.
   *
   * @return None.
   */
  void SetColorImageSettings(const ImageSettings& settings);

  /**
   * @brief Set optimization related settings for grayscale image.
   *
   * @details For a newly constructed object, if this function is not called to set any grayscale image settings,
   *          that means to use default grayscale image settings. Please refer to comment in
   *          class @link ImageSettings @endlink for default values.<br>
   *          @link ImageSettings @endlink set by this function is useful only when option value
   *          @link OptimizerSettings::e_OptimizerCompressImages @endlink is set by
   *          function @link OptimizerSettings::SetOptimizerOptions @endlink.
   *
   * @param[in] settings  Optimization related settings for grayscale images.
   *
   * @return None.
   */
  void SetGrayscaleImageSettings(const ImageSettings& settings);
    
  /**
   * @brief Set optimization related settings for monochrome image.
   *
   * @details For a newly constructed object, if this function is not called to set any monochrome image settings,
   *          that means to use default monochrome image settings.
   *          Please refer to comment in class @link MonoImageSettings @endlink for detail values.<br>
   *          MonoImageSettings set by this function is useful only when option value
   *          @link OptimizerSettings::e_OptimizerCompressImages @endlink is set by
   *          function @link OptimizerSettings::SetOptimizerOptions @endlink.
   *
   * @param[in] settings  Optimization related settings for monochrome images.
   *
   * @return None.
   */
  void SetMonoImageSettings(const MonoImageSettings& settings);

  /**
   * @brief Set optimization related settings for unembedding fonts.
   *
   * @details For a newly constructed object, if this function is not called to set any unembedded fonts settings,
   *          that means to no font is to be unembedded.
   *          UnembeddedFontSettings set by this function is useful only when option value
   *          @link OptimizerSettings::e_OptimizerUnembeddedFonts @endlink is set by
   *          function @link OptimizerSettings::SetOptimizerOptions @endlink.
   *
   * @param[in] settings  Optimization related settings for unembedding fonts.
   *
   * @return None.
   */
  void SetUnembeddedFontSettings(const UnembeddedFontSettings& settings);

  /**
   * @brief Set optimization related options for cleaning up.
   *
   * @details For a newly constructed object, if this function is not called to set any clean-up options,
   *          that means not to do clean-up optimization.
   *          Clean-up options set by this function are useful only when option value
   *          @link OptimizerSettings::e_OptimizerCleanUp @endlink is set by
   *          function @link OptimizerSettings::SetOptimizerOptions @endlink.
   *
   * @param[in] clean_up_options  Optimization related options for cleaning up. 0 means not to do clean-up optimization.
   *                              Please refer to values starting from
   *                              @link OptimizerSettings::e_CleanUpUseFlateForNonEncodedStream @endlink and
   *                              this can be one or a combination of these values.
   *
   * @return None.
   */
  void SetCleanUpOptions(foxit::uint32 clean_up_options);

  /**
   * @brief Set optimization related options for discarding objects.
   *
   * @details For a newly constructed object, if this function is not called to set any discard-objects options,
   *          that means not to do discard-objects optimization.
   *          Discard-objects options set by this function are useful only when option value
   *          @link OptimizerSettings::e_OptimizerDiscardObjects @endlink is set by
   *          function @link OptimizerSettings::SetOptimizerOptions @endlink.
   *
   * @param[in] discard_objects_options  Optimization related options for discarding objects.
   *                                     0 means not to do discarding-objects optimization. Please refer to
   *                                     values starting from @link OptimizerSettings::e_DiscardObjectsFormActions @endlink
   *                                     and this can be one or a combination of these values.
   *
   * @return None.
   */
  void SetDiscardObjectsOptions(foxit::uint32 discard_objects_options);

  /**
   * @brief Set optimization related options for discarding user data.
   *
   * @details For a newly constructed object, if this function is not called to set any discard-userdata options,
   *          that means not to do discard-userdata optimization.
   *          Discard-userdata options set by this function are useful only when option value
   *          @link OptimizerSettings::e_OptimizerDiscardUserData @endlink is set by
   *          function @link OptimizerSettings::SetOptimizerOptions @endlink.
   *
   * @param[in] discard_userdata_options  Optimization related options for discarding user data.
   *                                      0 means not to do discarding-userdata optimization. Please refer to
   *                                      values starting from @link OptimizerSettings::e_DiscardUserDataAllAnnotsFormsAndMultimedia @endlink
   *                                      and this can be one or a combination of these values.
   *
   * @return None.
   */
  void SetDiscardUserDataOptions(foxit::uint32 discard_userdata_options);

  /**
   * @brief Set optimization related options for doing transparency.
   *
   * @details For a newly constructed object, if this function is not called to set any transparency mode,
   *          that means the transparency mode is @link OptimizerSettings::e_TransparencyModeLowResolution @endlink default.
   *
   * @param[in] transparency_mode  Optimization related options for transparency mode.
   *                               Please refer to values starting from @link OptimizerSettings::e_TransparencyModeLowResolution @endlink
   *                               and this must be one of these values. Default value is @link OptimizerSettings::e_TransparencyModeLowResolution @endlink.
   *
   * @return None.
   */
  void SetTransparencyMode(TransparencyMode transparency_mode);
};

/**
 * This class represents settings for optimizing a scanned PDF document. It would be used in class @link Optimizer @endlink.
 *
 * @see @link Optimizer @endlink
 */
class OptimizeScannedPDFSettings FS_FINAL : public Base{
 public:
  /**
   * @brief Enumeration for compression mode used for color or gray image.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ScannedImageCompressMode {
    /** @brief Compression mode: high. */
    e_ScannedImageCompressHigh = 1,
    /** @brief Compression mode: jpeg. */
    e_ScannedImageCompressjpeg = 2,
    /** @brief Compression mode: jpeg2000 lossless. */
    e_ScannedImageCompressjpeg2000LossLess = 3,
    /** @brief Compression mode: jpeg2000 lossy. */
    e_ScannedImageCompressjpeg2000Lossy = 4
  } ScannedImageCompressMode;
  
  /**
   * @brief Enumeration for compression mode used for monochrome image.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ScannedMonoImageCompressMode {
    /** @brief Compression mode: jbig2 lossy. */
    e_ScannedMonoImageCompressjbig2Lossy = 1,
    /** @brief Compression mode: jbig2 lossless. */
    e_ScannedMonoImageCompressjbig2LossLess = 2,
    /** @brief Compression mode: CCITT Group 4. */
    e_ScannedMonoImageCompressCCITT4 = 3,
    /** @brief Compression mode: high. */
    e_ScannedMonoImageCompressHigh = 4
  } ScannedMonoImageCompressMode;
  

  OptimizeScannedPDFSettings();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit OptimizeScannedPDFSettings(FS_HANDLE handle);

  /** @brief Destructor. */
  ~OptimizeScannedPDFSettings();

  /**
   * @brief Constructor, with another result information object.
   *
   * @param[in] other  Another optimizer settings object.
   */
  OptimizeScannedPDFSettings(const OptimizeScannedPDFSettings& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another result optimizer settings object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  OptimizeScannedPDFSettings& operator = (const OptimizeScannedPDFSettings& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another result optimizer settings object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const OptimizeScannedPDFSettings& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another result optimizer settings object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const OptimizeScannedPDFSettings& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set the pages which will be optimized.
   *
   * @details For a newly constructed object,if this function is not called. all pages will be optimized.
   *
   * @param[in] pages  The Specify pages, If <b>pages</b> doesn't not add pages index means all pages will be optimized.
   *
   * @return None.
   */
  void SetOptimizedPages(const common::Range& pages);

  /**
   * @brief Set compression mode used for optimizing color/gray images in the scanned PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set option,
   *          that means to use OptimizeScannedPDFSettings::e_ImageCompressjpeg as the default value of this option.
   *
   * @param[in] mode  Image compression mode. Please refer to values starting from @link OptimizeScannedPDFSettings::e_ScannedImageCompressHigh @endlink
   *                  and this should be one of these values.
   *
   * @return None.
   */
  void SetColorGrayImageCompressionMode(ScannedImageCompressMode mode);

  /**
   * @brief Set the quality for lossy compression modes, used for optimizing color/gray images in a scanned PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set this option,
   *          that means to use 33 as the default value of this option.
   *
   * @param[in] quality  Quality value for lossy compression modes, the value must between 0 and 100.
   *
   * @note This method only valid in @link OptimizeScannedPDFSettings::e_ScannedImageCompressHigh @endlink and @link OptimizeScannedPDFSettings::e_ScannedImageCompressjpeg @endlink compress mode.
   *
   * @return None.
   */
  void SetColorGrayImageCompressionQuality(foxit::uint32 quality);

  /**
   * @brief Set compression mode used for optimizing monochrome images in a scanned PDF document.
   *
   * @details For a newly constructed object, if this function is not called to set option,
   *          that means to use @link OptimizeScannedPDFSettings::e_ScannedMonoImageCompressjbig2Lossy @endlink as the default value of this option.
   *
   * @param[in] mode  Image compression mode. Please refer to values starting from @link OptimizeScannedPDFSettings::e_ScannedMonoImageCompressjbig2Lossy @endlink
   *                  and this should be one of these values.
   *
   * @return None.
   */
  void SetMonoImageCompressionMode(ScannedMonoImageCompressMode mode);
};

}  // namespace optimization 
}  // namespace addon
}  // namespace foxit

#endif
