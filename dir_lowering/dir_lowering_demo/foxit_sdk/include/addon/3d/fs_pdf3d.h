#if (defined(_WIN32) || defined(_WIN64)) || defined(__EMSCRIPTEN__)
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
 * @file fs_3dpdf.h
 * @brief Header file for 3D PDF document related classes and methods.
 */

#ifndef FS_3DPDF_H_
#define FS_3DPDF_H_
#include "common/fs_common.h"
#include "pdf/fs_pdfdoc.h"
#include "pdf/annots/fs_annot.h"
/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
/** @brief Add-on namespace. */
namespace addon {
/** @brief 3D PDF namespace. */
namespace pdf3d {
/** @brief This class represents the data of a 3D annotation view. */
class PDF3DAnnotViewData FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  PDF3DAnnotViewData(){}

  /**
  *   @brief Constructor, with another 3D annot view data object.
  * 
  * @param[in] other  Another 3D annot view data object.
  *  */
  PDF3DAnnotViewData(const PDF3DAnnotViewData& other) {
    this->display_name = other.display_name;
    this->name = other.name;
  }

  /** @brief Assign operator.
   * 
   * @param[in] data  Another 3D annot view data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDF3DAnnotViewData& operator = (const PDF3DAnnotViewData& data) {
    this->display_name = data.display_name;
    this->name = data.name;
    return *this;
  }

  /** @brief The display name of the view. This name can be duplicated with other views.*/
  WString display_name;

  /** @brief The name of the view, which is the unique name.*/
  WString name;
};

/** @brief This class represents an array of @link PDF3DAnnotViewData @endlink. */
FSDK_DEFINE_ARRAY(PDF3DAnnotViewDataArray, PDF3DAnnotViewData)

/**
 * This class represents a node in the 3D model tree structure.
 *
 * @see @link PDF3DAnnotInstance @endlink
 */
class ModelNode FS_FINAL : public Base{
 public:
  /**
   * @brief Enumeration for the 3D model node type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PDF3DModelNodeType {
    /** @brief Model root. */
    e_TypeModelRoot = 0,
    /** @brief Group. */
    e_TypeGroup = 1,
    /** @brief Mesh. */
    e_TypeMesh = 2,
    /** @brief Sprite. */
    e_TypeSprite = 3,
    /** @brief Markup. */
    e_TypeMarkup = 4,
    /** @brief Punctual light. */
    e_TypePunctualLight = 5,
    /** @brief Ambient light. */
    e_TypeAmbientLight = 6,
    /** @brief View camera. */
    e_TypeViewCamera = 7,
    /** @brief Clipping plane. */
    e_TypeClippingPlane = 8,
    /** @brief Procedural. */
    e_TypeProcedural = 9,
    /** @brief Bone. */
    e_TypeBone = 10,
    /** @brief Dummy. */
    e_TypeDummy = 11
  } PDF3DModelNodeType;
  
    /** @brief Constructor. */
  ModelNode() {}

  /**
   * @brief Constructor, with another model node object.
   * 
   * @param[in] other  Another model node object.
   */
  ModelNode(const ModelNode& other);

  /** @brief Destructor. */
  ~ModelNode();

  /**
   * @brief Check whether current object is empty or not.
   * 
   * @details When the current object is empty, that means current object is useless.
   * 
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Assign operator.
   * 
   * @param[in] other  Another model node object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  ModelNode& operator=(const ModelNode& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another model node object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const ModelNode& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another model node object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const ModelNode& other) const;
  
  /**
   * @brief Get the type of the node.
   * 
   * @return The type of the node. Please refer to values starting from
   *         @link ModelNode::e_TypeModelRoot @endlink and this will be one of these values.
   */
  PDF3DModelNodeType GetNodeType();

  /**
   * @brief Get the first child node of current node.
   * 
   * @return The first child node of current node. If there is no child node, an empty object will be returned.
   */
  ModelNode GetFirstChildNode();

  /**
   * @brief Get the next sibling node of current node.
   *
   * @return The next sibling node of current node. If there is no next sibling node, an empty object will be returned.
   */
  ModelNode GetNextSiblingNode();

  /**
   * @brief Get the parent node of current node.
   *
   * @return The parent node of current node. If there is no parent node, an empty object will be returned.
   */
  ModelNode GetParentNode();

  /**
   * @brief Get the name of current node.
   *
   * @return The name of current node.
   */
  WString GetName();

  /**
   * @brief Set the visibility of current node.
   *
   * @param[in] is_visible  A boolean value used to set the visibility of current node. <br>
   *                        <b>true</b> means visible, while <b>false</b> means invisible.
   *
   * @return None.
   */
  void SetVisible(bool is_visible);

  /**
   * @brief Check whether current node is visible or not.
   *
   * @return <b>true</b> means current node is visible, while <b>false</b> means invisible.
   */
  bool IsVisible();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit ModelNode(FS_HANDLE handle);
};

/**
 * This class represents a 3D annotation instance.
 *
 * @see @link PDF3DContext @endlink
 */
class PDF3DAnnotInstance FS_FINAL : public Base{
 public:
  /**
   * @brief Enumeration for the 3D controller tool.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PDF3DController {
    /** @brief rotate. */
    e_ControllerRotate = 0,
    /** @brief spin. */
    e_ControllerSpin = 1,
    /** @brief pan. */
    e_ControllerPan = 2,
    /** @brief zoom. */
    e_ControllerZoom = 3,
    /** @brief walk. */
    e_ControllerWalk = 4,
    /** @brief fly. */
    e_ControllerFly	= 5
  } PDF3DController;
  
  /**
  * @brief Enumeration for the 3D render mode.
  *
  * @details Values of this enumeration should be used alone.
  */
  typedef enum _PDF3DRenderMode {
    /** @brief Solid. */
    e_RenderModeSolid = 1,
    /** @brief Solid wireframe. */
    e_RenderModeSolidWireframe = 2,
    /** @brief Solid outline. */
    e_RenderModeSolidOutline = 3,
    /** @brief Transparent. */
    e_RenderModeTransparent = 4,
    /** @brief Transparent wireframe. */
    e_RenderModeTransparentWireframe = 5,
    /** @brief Bounding box. */
    e_RenderModeBoundingBox = 6,
    /** @brief Transparent bounding box. */
    e_RenderModeTransparentBoundingBox = 7,
    /** @brief Transparent bounding box outline. */
    e_RenderModeTransparentBoundingBoxOutline = 8,
    /** @brief Wireframe. */
    e_RenderModeWireframe = 9,
    /** @brief Shaded wireframe. */
    e_RenderModeShadedWireframe = 10,
    /** @brief Hidden wireframe. */
    e_RenderModeHiddenWireframe = 11,
    /** @brief Illustration. */
    e_RenderModeIllustration = 12,
    /** @brief Shaded illustration. */
    e_RenderModeShadedIllustration = 13,
    /** @brief Vertices. */
    e_RenderModeVertices = 14,
    /** @brief Shaded vertices. */
    e_RenderModeShadedVertices = 15
  } PDF3DRenderMode;
  

  /** @brief Constructor. */
  PDF3DAnnotInstance(){}

  /**
   * @brief Constructor, with another 3d annot instance object.
   *
   * @param[in] other  Another 3d annot instance object.
   */
  PDF3DAnnotInstance(const PDF3DAnnotInstance& other);

  /** @brief Destructor. */
  ~PDF3DAnnotInstance();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another 3d annot instance object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDF3DAnnotInstance& operator=(const PDF3DAnnotInstance& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another 3d annot instance object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const PDF3DAnnotInstance& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another 3d annot instance object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const PDF3DAnnotInstance& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Set controller.
   *
   * @details Ensure the function @link PDF3DAnnotInstance::ActivateCanvas @endlink has been called.
   *
   * @param[in] tool_tag  The controller tool to be set. Please refer to values starting from
   *                      @link PDF3DAnnotInstance::e_ControllerRotate @endlink and this should be one of these values.<br>
   *                      Default value: @link PDF3DAnnotInstance::e_ControllerRotate @endlink.
   *
   * @return None.
   */
  void SetController(PDF3DController tool_tag);

  /**
   * @brief Set model render mode.
   *
   * @details Ensure the function @link PDF3DAnnotInstance::ActivateCanvas @endlink has been called.
   * 
   * @param[in] render_mode  The render mode to be set. Please refer to values starting from
   *                         @link PDF3DAnnotInstance::e_RenderModeSolid @endlink and this should be one of these values.<br>
   *                         Default value: @link PDF3DAnnotInstance::e_RenderModeSolidOutline @endlink.
   * 
   * @return None.
   */
  void SetRenderMode(PDF3DRenderMode render_mode);

  /**
   * @brief Activate canvas.
   * 
   * @param[in] screen_canvas_parent  The parent window handle used to activate the canvas.
   * 
   * @return The canvas handle.
   */
  FX_HWND ActivateCanvas(FX_HWND screen_canvas_parent);

  /**
   * @brief Update the canvas. 
   * 
   * @details Ensure the function @link PDF3DAnnotInstance::ActivateCanvas @endlink has been called.
   *          Call this function when the canvas size and position need to be updated.
   * 
   * @param[in] rect  The new area of canvas in device coordinate system.
   * 
   * @return None.
   */
  void UpdateCanvas(RectI rect);

  /**
   * @brief Call this function when pressing the left button.
   * 
   * @details Ensure the function @link PDF3DAnnotInstance::ActivateCanvas @endlink has been called.
   * 
   * @param[in] flag   The flag of the mouse event.
   * @param[in] point  The point of the mouse.
   * 
   * @return None.
   */
  void OnLButtonDown(int flag, PointF point);

  /**
   * @brief Call this function when releasing the left button.
   * 
   * @details Ensure the function @link PDF3DAnnotInstance::ActivateCanvas @endlink has been called.
   * 
   * @param[in] flag   The flag of the mouse event.
   * @param[in] point  The point of the mouse.
   * 
   * @return None.
   */
  void OnLButtonUp(int flag, PointF point);

  /**
   * @brief Call this function when moving the mouse.
   *
   * @details Ensure the function @link PDF3DAnnotInstance::ActivateCanvas @endlink has been called.
   * 
   * @param[in] flag   The flag of the mouse event.
   * @param[in] point  The point of the mouse.
   * 
   * @return None.
   */
  void OnMouseMove(int flag, PointF point);

  /**
   * @brief Call this function when scrolling the mouse wheel.
   * 
   * @details Ensure the function @link PDF3DAnnotInstance::ActivateCanvas @endlink has been called.
   * 
   * @param[in] flag   The flag of the mouse event.
   * @param[in] delta  The delta of the mouse wheel.
   * @param[in] point  The point of the mouse.
   * 
   * @return None.
   */
  void OnMouseWheel(int flag, int delta, PointF point);

  /**
   * @brief Call this function when pressing the right button.
   * 
   * @details Ensure the function @link PDF3DAnnotInstance::ActivateCanvas @endlink has been called.
   * 
   * @param[in] flag   The flag of the mouse event.
   * @param[in] point  The point of the mouse.
   * 
   * @return None.
   */
  void OnRButtonDown(int flag, PointF point);

  /**
   * @brief Call this function when releasing the right button.
   * 
   * @details Ensure the function @link PDF3DAnnotInstance::ActivateCanvas @endlink has been called.
   * 
   * @param[in] flag   The flag of the mouse event.
   * @param[in] point  The point of the mouse.
   * 
   * @return None.
   */
  void OnRButtonUp(int flag, PointF point);

  /**
   * @brief Reset the view back to the default view, the 3D model will be reset to its default state.
   * 
   * @details Ensure the function @link PDF3DAnnotInstance::ActivateCanvas @endlink has been called.
   * 
   * @return None.
   */
  void ResetDefaultView();

  /**
   * @brief Get the list of all preset views in the 3D model.
   * 
   * @details Ensure the function @link PDF3DAnnotInstance::ActivateCanvas @endlink has been called.
   * 
   * @return An array of view data.
   */
  PDF3DAnnotViewDataArray GetPresetViewList();

  /**
   * @brief Apply the preset view .
   * 
   * @details Ensure the function @link PDF3DAnnotInstance::ActivateCanvas @endlink has been called.
   * 
   * @param[in] view_data  The data of the view to be set. It should be one of the data array returned by function @link GetPresetViewList @endlink.
   * 
   * @return None.
   */
  void ApplyPresetView(const PDF3DAnnotViewData& view_data);

  /**
   * @brief Get the root node of the 3D model tree structure.
   * 
   * @details Ensure the function @link PDF3DAnnotInstance::ActivateCanvas @endlink has been called.
   *
   * @return The root node of the 3D model tree structure.
   */
  ModelNode GetRootNode();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PDF3DAnnotInstance(FS_HANDLE handle);
};
/** @brief This class represents an array of @link PDF3DAnnotInstance @endlink. */
FSDK_DEFINE_ARRAY(PDF3DAnnotInstanceArray, PDF3DAnnotInstance)

/** @brief This class represents PDF 3D annotation */
class PDF3DAnnot FS_FINAL : public Base{
 public:
  /**
   * @brief Enumeration for the 3D annot type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PDF3DType {
    /** @brief 3D Artwork. */
    e_3DTypeArtwork = 0,
    /** @brief Rich Media . */
    e_3DTypeRichMedia = 1
  } PDF3DType;
  

  /** @brief Destructor. */
  ~PDF3DAnnot();

  /**
   * @brief Constructor, with another 3d annot object.
   *
   * @param[in] other  Another 3d annot object.
   */
  PDF3DAnnot(const PDF3DAnnot& other);

  /**
  * @brief Assign operator.
  *
  * @param[in] other  Another 3d annot object, whose value would be assigned to current object.
  *
  * @return Reference to current object itself.
  */
  PDF3DAnnot& operator=(const PDF3DAnnot& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another 3d annot object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const PDF3DAnnot& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another 3d annot object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const PDF3DAnnot& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the annotation index corresponding to 3d annot.
   *
   * @return The index of annotation.
   */
  int GetAnnotIndex();

  /**
   * @brief Get associated annotation.
   *
   * @return An annotation object.
   */
  pdf::annots::Annot GetAnnot();

  /**
   * @brief Get the type of 3D annot.
   * 
   * @return The type of 3D annot. Please refer to values starting from
   *         @link PDF3DAnnot::e_3DTypeArtwork @endlink and this will be one of these values.
   */
  PDF3DType Get3DAnnotType();
  
  /**
   * @brief Get the instance of 3D Artwork.
   *
   * @details If the 3D annot type is not @link PDF3DAnnot::e_3DTypeArtwork @endlink, an empty object will be returned.
   * 
   * @return An 3d instance object.
   */
  PDF3DAnnotInstance Get3DArtworkInstance();

  /**
   * @brief Get the instance array of rich media.
   * 
   * @details If the 3D annot type is not @link PDF3DAnnot::e_3DTypeRichMedia @endlink, an empty array will be returned.
   *
   * @return An 3d instance objects array.
   */
  PDF3DAnnotInstanceArray GetRichMediaInstances();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PDF3DAnnot(FS_HANDLE handle);
};
FSDK_DEFINE_ARRAY(PDF3DAnnotArray, PDF3DAnnot)

/** This class represents 3D launch setting. */
class PDF3DLaunchSetting FS_FINAL : public Object {
 public:
  /**
   * @brief Enumeration for activation enable setting for the 3D launch setting type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PDF3DActivationEnableSetting {
    /** @brief Enable when the content is clicked. */
    e_3DActivationEnableSettingContentClicked = 0,
    /** @brief Enable when the page containing the content is opened. */
    e_3DActivationEnableSettingPageOpened = 1,
    /** @brief Enable when the page containing the content is visible. */
    e_3DActivationEnableSettingPageVisible = 2
  } PDF3DActivationEnableSetting;
  
  /**
   * @brief Enumeration for activation disable setting for the 3D launch setting type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PDF3DActivationDisableSetting {
    /** @brief Disable when "Disable Content" is selected from the context menu. */
    e_3DActivationDisableSettingContextMenuSelected = 0,
    /** @brief Disable when the page containing the content is closed. */
    e_3DActivationDisableSettingPageClosed = 1,
    /** @brief Disable when the page containing the content is not visible. */
    e_3DActivationDisableSettingPageInvisible = 2
  } PDF3DActivationDisableSetting;
  
  /**
   * @brief Enumeration for activation playback style for the 3D launch setting type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PDF3DActivationPlaybackStyleSetting {
    /** @brief Play content on page. */
    e_3DActivationPlaybackStyleOnPage = 0,
    /** @brief Play content in floating window. */
    e_3DActivationPlaybackStyleInFloatingWindow = 1
  } PDF3DActivationPlaybackStyleSetting;
  
  /**
   * @brief Enumeration for appearance setting for border width for the 3D launch setting type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PDF3DAppearanceSettingBorderWidth {
    /** @brief No border. */
    e_3DAppearanceSettingBorderWidthNone = 0,
    /** @brief Thin. */
    e_3DAppearanceSettingBorderWidthThin = 1,
    /** @brief Medium. */
    e_3DAppearanceSettingBorderWidthMedium = 2,
    /** @brief Thick. */
    e_3DAppearanceSettingBorderWidthThick = 3
  } PDF3DAppearanceSettingBorderWidth;
  
  /**
   * @brief Enumeration for poster image for the 3D launch setting type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PDF3DPosterImageSetting {
    /** @brief Keep current poster. */
    e_3DPosterImageKeepCurrent = 0,
    /** @brief Retrieve poster from default view. */
    e_3DPosterImageRetrieveFromDefaultView = 1,
    /** @brief Create poster from file. */
    e_3DPosterImageCreateFromFile = 2
  } PDF3DPosterImageSetting;
  

  /** @brief Constructor. */
  PDF3DLaunchSetting()
   : activation_enable(e_3DActivationEnableSettingContentClicked)
   , activation_disable(e_3DActivationDisableSettingContextMenuSelected)
   , activation_playback(e_3DActivationPlaybackStyleOnPage)
   , window_width(320)
   , window_height(240)
   , border_width(e_3DAppearanceSettingBorderWidthNone)
   , is_transparent_background(false)
   , poster_image(e_3DPosterImageKeepCurrent)
   , poster_file_path(L"") {
  }

  /**
   * @brief Constructor, with another 3D launch setting object.
   *
   * @param[in] launch_setting  Another 3D launch setting object.
   */
  PDF3DLaunchSetting(const PDF3DLaunchSetting& launch_setting)
    : activation_enable(launch_setting.activation_enable)
    , activation_disable(launch_setting.activation_disable)
    , activation_playback(launch_setting.activation_playback)
    , window_width(launch_setting.window_width)
    , window_height(launch_setting.window_height)
    , border_width(launch_setting.border_width)
    , is_transparent_background(launch_setting.is_transparent_background)
    , poster_image(launch_setting.poster_image) 
    , poster_file_path(launch_setting.poster_file_path) {
  }

  /**
   * @brief Constructor with parameter.
   *
   * @param[in] activation_enable         The activation enable setting for 3D.
   *                                      Please refer to values starting from @link PDF3DLaunchSetting::e_3DActivationEnableSettingContentClicked @endlink
   *                                      and this should be one of these values.
   * @param[in] activation_disable        The activation disable setting for 3D.
   *                                      Please refer to values starting from @link PDF3DLaunchSetting::e_3DActivationDisableSettingContextMenuSelected @endlink
   *                                      and this should be one of these values.
   * @param[in] activation_playback       The activation playback setting for 3D.
   *                                      Please refer to values starting from @link PDF3DLaunchSetting::e_3DActivationPlaybackStyleOnPage @endlink
   *                                      and this should be one of these values.
   * @param[in] window_width              The window width setting for 3D. Default value is 320.
   * @param[in] window_height             The window height setting for 3D. Default value is 240.
   * @param[in] border_width              The border width setting for 3D.
   *                                      Please refer to values starting from @link PDF3DLaunchSetting::e_3DAppearanceSettingBorderWidthNone @endlink
   *                                      and this should be one of these values.
   * @param[in] is_transparent_background This flag indicates whether the 3D content background is transparent.
   * @param[in] poster_image              The poster image.
   *                                      Please refer to values starting from @link PDF3DLaunchSetting::e_3DPosterImageKeepCurrent @endlink
   *                                      and this should be one of these values.
   * @param[in] poster_file_path          The file path of poster image.
   */
  PDF3DLaunchSetting(PDF3DActivationEnableSetting activation_enable, PDF3DActivationDisableSetting activation_disable ,
           PDF3DActivationPlaybackStyleSetting activation_playback, int window_width, int window_height,
           PDF3DAppearanceSettingBorderWidth border_width, bool is_transparent_background,
           PDF3DPosterImageSetting poster_image, WString poster_file_path) {
    this->activation_enable = activation_enable;
    this->activation_disable = activation_disable;
    this->activation_playback = activation_playback;
    this->window_width = window_width;
    this->window_height = window_height;
    this->border_width = border_width;
    this->is_transparent_background = is_transparent_background;
    this->poster_image = poster_image;
    this->poster_file_path = poster_file_path;
  }

  /**
   * @brief Set the values.
   *
   * @param[in] activation_enable         The activation enable setting for 3D.
   *                                      Please refer to values starting from @link PDF3DLaunchSetting::e_3DActivationEnableSettingContentClicked @endlink 
   *                                      and this should be one of these values.
   * @param[in] activation_disable        The activation disable setting for 3D.
   *                                      Please refer to values starting from @link PDF3DLaunchSetting::e_3DActivationDisableSettingContextMenuSelected @endlink 
   *                                      and this should be one of these values.
   * @param[in] activation_playback       The activation playback setting for 3D.
   *                                      Please refer to values starting from @link PDF3DLaunchSetting::e_3DActivationPlaybackStyleOnPage @endlink
   *                                      and this should be one of these values.
   * @param[in] window_width              The window width setting for 3D. Default value is 320.
   * @param[in] window_height             The window height setting for 3D. Default value is 240.
   * @param[in] border_width              The border width setting for 3D.
   *                                      Please refer to values starting from @link PDF3DLaunchSetting::e_3DAppearanceSettingBorderWidthNone @endlink
   *                                      and this should be one of these values.
   * @param[in] is_transparent_background This flag indicates whether the 3D content background is transparent.
   * @param[in] poster_image              The poster image.
   *                                      Please refer to values starting from @link PDF3DLaunchSetting::e_3DPosterImageKeepCurrent @endlink
   *                                      and this should be one of these values.
   * @param[in] poster_file_path          The file path of poster image.
   *
   * @return None.
   */
  void Set(PDF3DActivationEnableSetting activation_enable, PDF3DActivationDisableSetting activation_disable ,
           PDF3DActivationPlaybackStyleSetting activation_playback, int window_width, int window_height,
           PDF3DAppearanceSettingBorderWidth border_width, bool is_transparent_background, 
           PDF3DPosterImageSetting poster_image, WString poster_file_path) {
    this->activation_enable = activation_enable;
    this->activation_disable = activation_disable;
    this->activation_playback = activation_playback;
    this->window_width = window_width;
    this->window_height = window_height;
    this->border_width = border_width;
    this->is_transparent_background = is_transparent_background;
    this->poster_image = poster_image;
    this->poster_file_path = poster_file_path;
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] launch_setting Another 3D launch setting object.
   *
   * @return Reference to current object itself.
   */
  PDF3DLaunchSetting& operator=(const PDF3DLaunchSetting& launch_setting) {
    this->activation_enable = launch_setting.activation_enable;
    this->activation_disable = launch_setting.activation_disable;
    this->activation_playback = launch_setting.activation_playback;
    this->window_width = launch_setting.window_width;
    this->window_height = launch_setting.window_height;
    this->border_width = launch_setting.border_width;
    this->is_transparent_background = launch_setting.is_transparent_background;
    this->poster_image = launch_setting.poster_image;
    this->poster_file_path = launch_setting.poster_file_path;
    return *this;
  }

  /**
   * @brief The activation enable setting for 3D. Please refer to values starting from
   *        @link PDF3DLaunchSetting::e_3DActivationEnableSettingContentClicked @endlink and this should
   *        be one of these values.
   */
  PDF3DActivationEnableSetting activation_enable;

  /**
   * @brief The activation disable setting for 3D. Please refer to values starting from
   *        @link PDF3DLaunchSetting::e_3DActivationDisableSettingContextMenuSelected @endlink and this should
   *        be one of these values.
   */
  PDF3DActivationDisableSetting activation_disable;

  /**
   * @brief The activation playback setting for 3D. Please refer to values starting from
   *        @link PDF3DLaunchSetting::e_3DActivationPlaybackStyleOnPage @endlink and this should
   *        be one of these values.
   */
  PDF3DActivationPlaybackStyleSetting activation_playback;

  /**
   * @brief The window width setting for 3D. Default value is 320.
   */
  int window_width;

  /**
   * @brief The window height setting for 3D. Default value is 240.
   */
  int window_height;

  /**
   * @brief The border width setting for 3D. Please refer to values starting from
   *        @link PDF3DLaunchSetting::e_3DAppearanceSettingBorderWidthNone @endlink and this should
   *        be one of these values.
   */
  PDF3DAppearanceSettingBorderWidth border_width;

  /**
   * @brief This flag indicates whether the 3D content background is transparent. 
   *        <b>true</b> means transparent, while <b>false</b> means not. Default value is <b>false</b>.
   */
  bool is_transparent_background;

  /**
   * @brief The poster image. Please refer to values starting from
   *        @link PDF3DLaunchSetting::e_3DPosterImageKeepCurrent @endlink and this should
   *        be one of these values.
   */
  PDF3DPosterImageSetting poster_image;

  /**
   * @brief The file path of poster image. 
   *        This field is valid only when <i>poster_image</i> is set to @link PDF3DLaunchSetting::e_3DPosterImageCreateFromFile @endlink.
   */
  WString poster_file_path;
};

/** This class represents 3D advanced setting. */
class PDF3DAdvancedSetting FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for lighting scheme for the 3D advanced setting type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PDF3DLightingScheme {
    /** @brief None. */
    e_3DLightingSchemeNone = 0,
    /** @brief From file. */
    e_3DLightingSchemeFromFile = 1,
    /** @brief No lights. */
    e_3DLightingSchemeNoLights = 2,
    /** @brief White lights. */
    e_3DLightingSchemeWhiteLights = 3,
    /** @brief Day lights. */
    e_3DLightingSchemeDayLights = 4,
    /** @brief Hard lights. */
    e_3DLightingSchemeHardLights = 5,
    /** @brief Primary lights. */
    e_3DLightingSchemePrimaryLights = 6,
    /** @brief Night lights. */
    e_3DLightingSchemeNightLights = 7,
    /** @brief Blue lights. */
    e_3DLightingSchemeBlueLights = 8,
    /** @brief Red lights. */
    e_3DLightingSchemeRedLights = 9,
    /** @brief Cube lights. */
    e_3DLightingSchemeCubeLights = 10,
    /** @brief CAD lights. */
    e_3DLightingSchemeCADLights= 11,
    /** @brief Headlamp. */
    e_3DLightingSchemeHeadlamp= 12
  } PDF3DLightingScheme;
  
  /**
   * @brief Enumeration for rendering style for the 3D advanced setting type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PDF3DRenderingStyle {
    /** @brief None. */
    e_3DRenderingStyleNone = 0,
    /** @brief Bounding box. */
    e_3DRenderingStyleBoundingBox = 1,
    /** @brief Transparent bounding box. */
    e_3DRenderingStyleTransparentBoundingBox = 2,
    /** @brief Transparent bounding box outline. */
    e_3DRenderingStyleTransparentBoundingBoxOutline = 3,
    /** @brief Vertices. */
    e_3DRenderingStyleVertices = 4,
    /** @brief Shaded vertices. */
    e_3DRenderingStyleShadedVertices = 5,
    /** @brief Wireframe. */
    e_3DRenderingStyleWireframe = 6,
    /** @brief Shaded wireframe. */
    e_3DRenderingStyleShadedWireframe = 7,
    /** @brief Solid. */
    e_3DRenderingStyleSolid = 8,
    /** @brief Transparent. */
    e_3DRenderingStyleTransparent = 9,
    /** @brief Solid wireframe. */
    e_3DRenderingStyleSolidWireframe = 10,
    /** @brief Transparent wireframe. */
    e_3DRenderingStyleTransparentWireframe = 11,
    /** @brief Illustration. */
    e_3DRenderingStyleIllustration = 12,
    /** @brief Solid outline. */
    e_3DRenderingStyleSolidOutline = 13,
    /** @brief Shaded illustration. */
    e_3DRenderingStyleShadedIllustration = 14,
    /** @brief Hidden wireframe. */
    e_3DRenderingStyleHiddenWireframe = 15
  } PDF3DRenderingStyle;
  
  /**
   * @brief Enumeration for animation style for the 3D advanced setting type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PDF3DAnimationStyle {
    /** @brief None. */
    e_3DAnimationStyleNone = 0,
    /** @brief Loop. */
    e_3DAnimationStyleLoop = 1,
    /** @brief Bounce. */
    e_3DAnimationStyleBounce = 2
  } PDF3DAnimationStyle;
  
  /**
   * @brief Enumeration for default views for the 3D advanced setting type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _PDF3DDefaultViews {
    /** @brief No views. */
    e_3DDefaultViewsNoViews = 0,
    /** @brief Left,top,front,Iso(all ortho). */
    e_3DDefaultViewsLeftTopFrontIsoAllOrtho = 1,
    /** @brief Left,top,front,Iso(all perspective). */
    e_3DDefaultViewsLeftTopFrontIsoAllPerspective = 2,
    /** @brief Left,top,front,(ortho)Iso(perspective).  */
    e_3DDefaultViewsLeftTopFrontOrthoIsoPerspective = 3,
    /** @brief Left,top,front,(perspective)Iso(ortho). */
    e_3DDefaultViewsLeftTopFrontPerspectiveIsoOrtho = 4,
    /** @brief Left,top,right,front,bottom,back(all ortho). */
    e_3DDefaultViewsLeftTopFrontRightBottomBackAllOrtho = 5,
    /** @brief Views from file. */
    e_3DDefaultViewsFromFile = 6
  } PDF3DDefaultViews;
  

  /** @brief Constructor. */
  PDF3DAdvancedSetting()
   : background_color(0x5E5E5E)
   , lighting_scheme(e_3DLightingSchemeNone)
   , rendering_style(e_3DRenderingStyleBoundingBox)
   , animation_style(e_3DAnimationStyleNone) 
   , default_views(e_3DDefaultViewsNoViews) 
   , is_add_default_views(false)
   , is_retain_views_and_comments(false)
   , is_show_tool_bar(true)
   , is_open_model_tree(false) 
   , script_file_path(L"") {
  }

  /**
   * @brief Constructor, with another 3D advanced setting object.
   *
   * @param[in] advanced_setting  Another 3D advanced setting object.
   */
  PDF3DAdvancedSetting(const PDF3DAdvancedSetting& advanced_setting)
    : background_color(advanced_setting.background_color)
    , lighting_scheme(advanced_setting.lighting_scheme)
    , rendering_style(advanced_setting.rendering_style)
    , animation_style(advanced_setting.animation_style)
    , default_views(advanced_setting.default_views) 
    , is_add_default_views(advanced_setting.is_add_default_views)
    , is_retain_views_and_comments(advanced_setting.is_retain_views_and_comments)
    , is_show_tool_bar(advanced_setting.is_show_tool_bar)
    , is_open_model_tree(advanced_setting.is_open_model_tree)
    , script_file_path(advanced_setting.script_file_path) {
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] advanced_setting Another 3D advanced setting object.
   *
   * @return Reference to current object itself.
   */
  PDF3DAdvancedSetting& operator=(const PDF3DAdvancedSetting& advanced_setting) {
    this->background_color = advanced_setting.background_color;
    this->lighting_scheme = advanced_setting.lighting_scheme;
    this->rendering_style = advanced_setting.rendering_style;
    this->animation_style = advanced_setting.animation_style;
    this->default_views = advanced_setting.default_views;
    this->is_add_default_views = advanced_setting.is_add_default_views;
    this->is_retain_views_and_comments = advanced_setting.is_retain_views_and_comments;
    this->is_show_tool_bar = advanced_setting.is_show_tool_bar;
    this->is_open_model_tree = advanced_setting.is_open_model_tree;
    this->script_file_path = advanced_setting.script_file_path;
    return *this;
  }

  /**
   * @brief Constructor with parameter.
   *
   * @param[in] background_color             The background color. Default value: 0x5e5e5e.
   * @param[in] lighting_scheme              The lighting scheme setting for 3D.
   *                                         Please refer to values starting from @link PDF3DAdvancedSetting::e_3DLightingSchemeNone @endlink
   *                                         and this should be one of these values.
   * @param[in] rendering_style              The activation rendering style setting for 3D. 
   *                                         Please refer to values starting from @link PDF3DAdvancedSetting::e_3DRenderingStyleBoundingBox @endlink
   *                                         and this should be one of these values.
   * @param[in] animation_style              The activation animation setting for 3D.
   *                                         Please refer to values starting from @link PDF3DAdvancedSetting::e_3DAnimationStyleNone @endlink
   *                                         and this should be one of these values.
   * @param[in] default_views                The default views setting for 3D. 
   *                                         Please refer to values starting from @link PDF3DAdvancedSetting::e_3DDefaultViewsNoViews @endlink
   *                                         and this should be one of these values.
   * @param[in] is_add_default_views         This flag indicates whether to add default views.
   * @param[in] is_retain_views_and_comments This flag indicates whether to retain views and comments.
   * @param[in] is_show_tool_bar             This flag indicates whether to show tool bar.
   * @param[in] is_open_model_tree           This flag indicates whether to open model tree.
   * @param[in] script_file_path             The script file path.
   */
  PDF3DAdvancedSetting(foxit::RGB background_color, PDF3DLightingScheme lighting_scheme ,
          PDF3DRenderingStyle rendering_style, PDF3DAnimationStyle animation_style, 
          PDF3DDefaultViews default_views, bool is_add_default_views, bool is_retain_views_and_comments,
          bool is_show_tool_bar, bool is_open_model_tree, WString script_file_path) {
   this->background_color = background_color;
   this->lighting_scheme = lighting_scheme;
   this->rendering_style = rendering_style;
   this->animation_style = animation_style;
   this->default_views = default_views;
   this->is_add_default_views = is_add_default_views;
   this->is_retain_views_and_comments = is_retain_views_and_comments;
   this->is_show_tool_bar = is_show_tool_bar;
   this->is_open_model_tree = is_open_model_tree;  
   this->script_file_path = script_file_path;
 }
  /**
   * @brief Set the values.
   *
   * @param[in] background_color             The background color.Default value: 0x5e5e5e.
   * @param[in] lighting_scheme              The lighting scheme setting for 3D.
   *                                         Please refer to values starting from @link PDF3DAdvancedSetting::e_3DLightingSchemeNone @endlink
   *                                         and this should be one of these values.
   * @param[in] rendering_style              The activation rendering style setting for 3D. 
   *                                         Please refer to values starting from @link PDF3DAdvancedSetting::e_3DRenderingStyleBoundingBox @endlink
   *                                         and this should be one of these values.
   * @param[in] animation_style              The activation animation style setting for 3D.
   *                                         Please refer to values starting from @link PDF3DAdvancedSetting::e_3DAnimationStyleNone @endlink
   *                                         and this should be one of these values.
   * @param[in] default_views                The default views setting for 3D. 
   *                                         Please refer to values starting from @link PDF3DAdvancedSetting::e_3DDefaultViewsNoViews @endlink
   *                                         and this should be one of these values.
   * @param[in] is_add_default_views         This flag indicates whether to add default views.
   * @param[in] is_retain_views_and_comments This flag indicates whether to retain views and comments.
   * @param[in] is_show_tool_bar             This flag indicates whether to show tool bar.
   * @param[in] is_open_model_tree           This flag indicates whether to open model tree.
   * @param[in] script_file_path             The script file path.
   *
   * @return None.
   */
  void Set(foxit::RGB background_color, PDF3DLightingScheme lighting_scheme , 
          PDF3DRenderingStyle rendering_style, PDF3DAnimationStyle animation_style, 
          PDF3DDefaultViews default_views, bool is_add_default_views, bool is_retain_views_and_comments,
          bool is_show_tool_bar, bool is_open_model_tree, WString script_file_path) {
   this->background_color = background_color;
   this->lighting_scheme = lighting_scheme;
   this->rendering_style = rendering_style;
   this->animation_style = animation_style;
   this->default_views = default_views;
   this->is_add_default_views = is_add_default_views;
   this->is_retain_views_and_comments = is_retain_views_and_comments;
   this->is_show_tool_bar = is_show_tool_bar;
   this->is_open_model_tree = is_open_model_tree;  
   this->script_file_path = script_file_path;
 }
  /**
   * @brief The background color.Default value: 0x5e5e5e.
   */
  foxit::RGB background_color;

  /**
   * @brief The lighting scheme setting for 3D. Please refer to values starting from
   *        @link PDF3DAdvancedSetting::e_3DLightingSchemeNone @endlink and this should
   *        be one of these values.
   */
  PDF3DLightingScheme lighting_scheme;

  /**
   * @brief The activation rendering style setting for 3D. Please refer to values starting from
   *        @link PDF3DAdvancedSetting::e_3DRenderingStyleBoundingBox @endlink and this should
   *        be one of these values.
   */
  PDF3DRenderingStyle rendering_style;

  /**
   * @brief The activation animation style setting for 3D. Please refer to values starting from
   *        @link PDF3DAdvancedSetting::e_3DAnimationStyleNone @endlink and this should
   *        be one of these values.
   */
  PDF3DAnimationStyle animation_style;

  /**
   * @brief The default views setting for 3D. Please refer to values starting from
   *        @link PDF3DAdvancedSetting::e_3DDefaultViewsNoViews @endlink and this should
   *        be one of these values.
   */
  PDF3DDefaultViews default_views;

  /** 
   * @brief This flag indicates whether to add default views. 
   *        <b>true</b> means to add, while <b>false</b> means not. Default value is <b>false</b>. 
   */
  bool is_add_default_views;

  /**
   * @brief This flag indicates whether to retain views and comments.
   *        <b>true</b> means to retain, while <b>false</b> means not. Default value is <b>false</b>.
   */
  bool is_retain_views_and_comments;

  /**
   * @brief This flag indicates whether to show tool bar.
   *        <b>true</b> means to show, while <b>false</b> means not. Default value is <b>false</b>.
   */
  bool is_show_tool_bar;

  /**
   * @brief This flag indicates whether to open model tree.
   *        <b>true</b> means to open, while <b>false</b> means not. Default value is <b>false</b>.
   */
  bool is_open_model_tree;

  /** @brief This flag indicates the script file path.*/
  WString script_file_path;
};

/**
 * This class represents a 3D PDF context. Before using any class or methods in this module, please ensure
 * Foxit PDF SDK has been initialized successfully by function @link common::Library::Initialize @endlink
 * with a key including "3D" module.<br>
 * Currently, 3D module only supports Windows.
 * 
 * @see @link common::Library @endlink
 */
class PDF3DContext FS_FINAL : public Base{
 public:
  /** @brief Constructor, with a PDF document object.*/
  explicit PDF3DContext(const pdf::PDFDoc& doc);

  /**
   * @brief Constructor, with another 3d context object.
   *
   * @param[in] other  Another 3d context object.
   */
  PDF3DContext(const PDF3DContext& other);

  /** @brief Destructor. */
  ~PDF3DContext();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another 3d context object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDF3DContext& operator=(const PDF3DContext& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another 3d context object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const PDF3DContext& other) const;

  /**
  * @brief Not equal operator.
  *
  * @param[in] other  Another 3d context object. This function will check if current object is not equal to this one.
  *
  * @return <b>true</b> means not equal, while <b>false</b> means equal.
  */
  bool operator!=(const PDF3DContext& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get 3d annot objects array by page index.
   *
   * @param[in] page_index  Page index. Valid range: from 0 to (<i>page_count</i>-1).
   *                        <i>page_count</i> is returned by function @link pdf::PDFDoc::GetPageCount @endlink.
   *
   * @return 3d annot objects array.
   */
  PDF3DAnnotArray GetPage3DAnnotArray(int page_index);

  /**
   * @brief Refresh 3D Objects.
   *
   * @details To dynamically display 3D effects, it is necessary to modify the interface based on loop calls.
   *
   * @return None.
   */
  void Invalidate();

  /**
   * @brief Add a 3D annotation to the PDF page.
   * 
   * @param[in] threeD_file_path         The file path of 3D file. Currently, it supports u3d and prc.
   * @param[in] page_index               The index of the page to which the 3D annotation is added. Valid range: from 0 to (<i>page_count</i>-1).
   * @param[in] rectf                    The rectangle of new 3d annotation in [PDF coordinate system].
   * @param[in] screen_canvas_parent     The screen canvas parent handle.
   * @param[in] launch_setting           The 3D launch setting.
   * @param[in] advanced_setting         The 3D advanced setting.
   * 
   * @return The added 3D annotation object.
   */
  PDF3DAnnot Add3DAnnot(const wchar_t* threeD_file_path, int page_index, foxit::RectF rectf, void* screen_canvas_parent,
      PDF3DLaunchSetting launch_setting, PDF3DAdvancedSetting advanced_setting);

  /**
   * @brief Add a 3D annotation to the PDF page.
   *
   * @param[in] threeD_file_read     The file reader callback of 3D file. Currently, it supports u3d and prc.
   *                                 Please refer to @link common::file::ReaderCallback @endlink for details.
   * @param[in] page_index           The index of the page to which the 3D annotation is added. Valid range: from 0 to (<i>page_count</i>-1).
   * @param[in] rectf                The rectangle of new 3d annotation in [PDF coordinate system].
   * @param[in] screen_canvas_parent The screen canvas parent handle.
   * @param[in] launch_setting       The 3D launch setting.
   * @param[in] advanced_setting     The 3D advanced setting.
   *
   * @return The added 3D annotation object.
   */
  PDF3DAnnot Add3DAnnot(foxit::common::file::ReaderCallback* threeD_file_read, int page_index, foxit::RectF rectf, void* screen_canvas_parent, PDF3DLaunchSetting launch_setting, PDF3DAdvancedSetting advanced_setting);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PDF3DContext(FS_HANDLE handle = NULL);
};
} //pdf3d
} //addon
} //foxit
#endif //FS_3DPDF_H_
#endif //defined(_WIN32) || defined(_WIN64)
