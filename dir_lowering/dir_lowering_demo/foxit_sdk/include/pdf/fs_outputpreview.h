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
 * @file fs_outputpreview.h
 * @brief Header file for output preview related definitions and classes.
 */

#ifndef FS_OUTPUTPREVIEW_H_
#define FS_OUTPUTPREVIEW_H_

#include "common/fs_common.h"
#include "pdf/fs_pdfdoc.h"
#include "common/fs_render.h"

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
 * This class can be used to do output preview. Output preview is to preview color separations and test different color profiles.
 * Before use this class, please ensure function @link common::Library::SetDefaultICCProfilesPath @endlink has been called successfully;
 * otherwise unexpcted error or result may occur when this class is being used to do output preview.
 * Currently, this feature is not supported on the Linux ARM and Mac ARM platform.
 */
class OutputPreview FS_FINAL : public Base{
 public:
  /**
   * @brief Enumeration for show type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ShowType {
    /** @brief If set, show all. */
    e_ShowAll  = 0,
    /** @brief If set, only show with DeviceCMYK. */
    e_ShowDeviceCMYK  = 1,
    /** @brief If set, only show without DeviceCMYK. */
    e_ShowNotDeviceCMYK    = 2,
    /** @brief If set, only show with ICCBased CMYK. */
    e_ShowICCBasedCMYK    = 3,
    /** @brief If set, only show with spot color. */
    e_ShowSpotColor    = 4,
    /** @brief If set, only show with DeviceCMYK and spot. */
    e_ShowDeviceCMYKAndSpot    = 5,
    /** @brief If set, only show with DeviceCMYK or spot. */
    e_ShowNotDeviceCMYKOrSpot    = 6,
    /** @brief If set, only show with DeviceN. */
    e_ShowDeviceN    = 7,
    /** @brief If set, only show with CMYK. */
    e_ShowCMYK    = 8,
    /** @brief If set, only show with RGB. */
    e_ShowRGB    = 9,
    /** @brief If set, only show with DeviceRGB. */
    e_ShowDeviceRGB    = 10,
    /** @brief If set, only show with ICCBased RGB. */
    e_ShowICCBasedRGB    = 11,
    /** @brief If set, only show with Gray. */
    e_ShowGray    = 12,
    /** @brief If set, only show with DeviceGray */
    e_ShowDeviceGray    = 13,
    /** @brief If set, only show with CalGray. */
    e_ShowCalGray    = 14,
    /** @brief If set, only show with Calibrated. */
    e_ShowCalibrated    = 15,
    /** @brief If set, only show with Lab. */
    e_ShowLab    = 16,
    /** @brief If set, only show with Device. */
    e_ShowDevice    = 17,
    /** @brief If set, only show images. */
    e_ShowImages    = 18,
    /** @brief If set, only show solid color. */
    e_ShowSolidColor    = 19,
    /** @brief If set, only show smooth shades. */
    e_ShowSmoothShades    = 20,
    /** @brief If set, only show registration color. */
    e_ShowRegistrationColor    = 21,
    /** @brief If set, only show text. */
    e_ShowText    = 22,
    /** @brief If set, only show line art. */
    e_ShowLineArt    = 23
  } ShowType;
  
  /**
  * @brief Enumeration for colorant type.
  *
  * @details Values of this enumeration should be used alone.
  */
  typedef enum _ColorantType {
    /** @brief Colorant type: process. */
    e_ColorantTypeProcess  = 0,
    /** @brief Colorant type: spot. */
    e_ColorantTypeSpot    = 1
  } ColorantType;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] pdf_doc  A valid PDF document object.
   */
  OutputPreview(const PDFDoc& pdf_doc);
  /**
   * @brief Constructor, with another output preview object.
   *
   * @param[in] other  Another output preview object.
   */
  OutputPreview(const OutputPreview& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another output preview object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  OutputPreview& operator = (const OutputPreview& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another output preview object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const OutputPreview& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another output preview object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const OutputPreview& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /** @brief Destructor. */
  ~OutputPreview();

  /**
   * @brief Set simulation ICC profile file path.
   *
   * @details If the color space of input ICC profile file is not one of RGB/Gray/CMYK, this function will throw @link foxit::e_ErrUnsupported @endlink.<br>
   *          This function should be called successfully before calling function @link OutputPreview::GeneratePreviewBitmap @endlink.
   *
   * @param[in] icc_profile_path  File path for an ICC profile which is to be used as simulation profile for output preview.
   *
   * @return None.
   */
  void SetSimulationProfile(const WString& icc_profile_path);

  /**
   * @brief Set show type.
   *
   * @details If no show type is set to current object, value @link OutputPreview::e_ShowAll @endlink will be used by default
   *          when function @link OutputPreview::GeneratePreviewBitmap @endlink is called.
   *
   * @param[in] show_type  Show type. Please refer to values starting from @link OutputPreview::e_ShowAll @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetShowType(ShowType show_type);

  /**
   * @brief Get Separations plates.
   *
   * @details If to get plates of process colorant type, please ensure function @link OutputPreview::SetSimulationProfile @endlink has been called successfully;
   *          otherwise no plate of process colorant type will be retrieved.
   *
   * @param[in] colorant_type  Colorant type. Please refer to values starting from @link OutputPreview::e_ColorantTypeProcess @endlink and this should be one of these values.
   *
   * @return A string array which represents plate names.
   */
  StringArray GetPlates(ColorantType colorant_type);

  /**
   * @brief Get the color value of a plate.
   * 
   * @details This function is only useful for a plate in spot colorant type.
   *
   * @param[in] plate_name  Plate name. This can be retrieved form the returned string array of function @link OutputPreview::GetPlates @endlink.
   *
   * @return RGB color of the specified plate.
   */
  RGB GetSpotPlateColor(const char* plate_name);

  /**
   * @brief Set the check status for a plate.
   *
   * @param[in] plate_name  Plate name. This can be retrieved from the returned string array of function @link OutputPreview::GetPlates @endlink.
   * @param[in] to_check    Check status: <b>true</b> means to check the plate, while <b>false</b> means not to check the plate.
   *
   * @return None.
   */
  void SetCheckStatus(const String& plate_name, bool to_check);

  /**
   * @brief Check whether a plate is checked or not.
   *
   * @details For a newly constructed output preview object, all the plates are not checked.
   *
   * @param[in] plate_name  Plate name. This can be retrieved from the returned string array of function @link OutputPreview::GetPlates @endlink.
   *
   * @return <b>true</b> means the plate is checked, while <b>false</b> means the plate is not checked.
   */
  bool IsChecked(const String& plate_name) const;

  /**
   * @brief Set the flag to decide whether to enable simulate overprint.
   *
   * @details If this function is not called, default value <b>true</b> will be used.
   *
   * @param[in] is_to_simulate_overprint  <b>true</b> means to simulate overprinting.
   *                                      <b>false</b> means not to simulate overprinting.
   *
   * @return None.
   */
  void EnableSimulateOverprint(bool is_to_simulate_overprint);

  /**
   * @brief Generate the output preview bitmap for a PDF page.
   *
   * @details This function will render target PDF page with flags and options specified in input <i>renderer</i> and settings of current output preview object,
   *          and then return the final output preview bitmap. Rendering process in this function will not affect input <i>renderer</i>.<br>
   *          Please ensure function @link OutputPreview::SetSimulationProfile @endlink has been called successfully; otherwise this function will throw @link foxit::e_ErrUnsupported @endlink.
   *
   * @param[in] page      A valid PDF page object. This PDF page should have been parsed.
   * @param[in] matrix    The transformation matrix used for rendering, which is usually returned by function @link PDFPage::GetDisplayMatrix @endlink. 
   * @param[in] renderer  A valid renderer object.
   *
   * @return A bitmap which represents the output preview result.
   */
  common::Bitmap GeneratePreviewBitmap(const PDFPage& page, const Matrix& matrix, const common::Renderer& renderer);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit OutputPreview(FS_HANDLE handle =  NULL);

};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_OUTPUTPREVIEW_H_

