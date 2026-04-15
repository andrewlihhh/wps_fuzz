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
 * @file fs_snappointmgr.h
 * @brief Header file for PDF snap point manager related definitions and classes.
 */

#ifndef FS_SNAPPOINTMGR_H_
#define FS_SNAPPOINTMGR_H_

#include "common/fs_common.h"
#include "pdf/fs_pdfpage.h"

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
 * This class represents information of a snapped point, which is snapped with specified snapping flags by class @link SnapPointMgr @endlink.
 *
 * @see @link SnapPointMgr @endlink.
 */
class SnappedPoint FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for snapped point type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _SnappedPointType {
    /** @brief This means the snapped point is invalid. */
    e_TypeNone = 0,
    /** @brief Snapped point type: endpoint, which means the snapped point is an endpoint of a path. */
    e_TypeEndpoint = 1,
    /** @brief Snapped point type: midpoint, which means the snapped point is the midpoint for two endpoints of a path. */
    e_TypeMidpoint = 2,
    /** @brief Snapped point type: intersection point, which means the snapped point is the intersection of two intersecting paths. */
    e_TypeIntersectionPoint = 3,
    /** @brief Snapped point type: nearest point, which means the snapped point is the nearest point (which is in a path) to the specified point. */
    e_TypeNearestPoint = 4
  } SnappedPointType;
  

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit SnappedPoint(FS_HANDLE handle = NULL);

  /** @brief Destructor. */
  ~SnappedPoint();

  /**
   * @brief Constructor, with another snapped point object.
   *
   * @param[in] other  Another snapped point object.
   */
  SnappedPoint(const SnappedPoint& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another snapped point object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  SnappedPoint& operator=(const SnappedPoint& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another snapped point object. This function will check if current object is equal to this
   * one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const SnappedPoint& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another snapped point object. This function will check if current object is not equal to this
   * one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const SnappedPoint& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the snapped point type.
   *
   * @return Snapped point type. Please refer to values starting from @link SnappedPoint::e_TypeNone @endlink and
   *         this would be one of these values.
   */
  SnappedPointType GetType();

  /**
   * @brief Get the point value.
   *
   * @details Point value represents a point in a path.
   *
   * @return Snapped point value.
   */
  PointF GetPoint();
};

/**
 * This class represents a manager for snapping point. This class can be used to snap point in a path with specified snapping flags.
 */
class SnapPointMgr FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for snapping point flags which are used to specify what kind of point in a path is to be snapped.
   *
   * @details Values of this enumeration can be used alone or in combination.
   */
  typedef enum _SnapPointFlags {
    /** @brief If set, that means to get the endpoint of a path. */
    e_FlagEndpoint = 0x0001,
    /** @brief If set, that means to get the midpoint for two endpoints of a path. */
    e_FlagMidpoint = 0x0002,
    /** @brief If set, that means to get the intersection of two intersecting paths. */
    e_FlagIntersectionPoint = 0x0004,
    /** @brief If set, that means to get the nearest point (which is in a path) to the specified point. */
    e_FlagNearestPoint = 0x0008
  } SnapPointFlags;
  

  /**
   * @brief Constructor, from a parsed PDF page object.
   *
   * @param[in] page  A valid PDF page object. This page should has been parsed.
   */
  explicit SnapPointMgr(const PDFPage& page);

  /**
   * @brief Constructor, with another snap point manager object.
   *
   * @param[in] other  Another snap point manager object.
   */
  SnapPointMgr(const SnapPointMgr& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another snap point manager object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  SnapPointMgr& operator = (const SnapPointMgr& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another snap point manager object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const SnapPointMgr& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another snap point manager object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const SnapPointMgr& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /** @brief Destructor. */
  ~SnapPointMgr();

  /**
   * @brief Reload current manager.
   *
   * @details This function should be called after any path in related PDF page has been modified.
   *
   * @return None.
   */
  void Reload();
  
  /**
   * @brief Get the snapped point information at/around a specified position in [PDF coordinate system] (@ref PDFPage).
   *
   * @param[in] position  A specified position, in [PDF coordinate system] (@ref PDFPage).
   * @param[in] flags     Flags for snapping point. Please refer to values starting from @link SnapPointMgr::e_FlagEndpoint @endlink
   *                      and this should be one or a combination of these values.
   *
   * @return Information for a snapped point. If the return value of function @link SnappedPoint::IsEmpty @endlink for
   *         the returned snapped point object is <b>true</b>, that means no suitable point can be snapped.
   */
  SnappedPoint GetSnappedPointAtPos(const PointF& position, foxit::uint32 flags);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit SnapPointMgr(FS_HANDLE handle =  NULL);
};
}  // namespace pdf
}  // namespace foxit
#endif  // FS_SNAPPOINTMGR_H_

