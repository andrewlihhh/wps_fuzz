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
 * @file fs_pdfstructtree.h
 * @brief Header file for PDF structure tree related definitions and classes.
 */

#ifndef FS_PDFSSTRUCTTREE_H_
#define FS_PDFSSTRUCTTREE_H_

#include "common/fs_common.h"
#include "pdf/objects/fs_pdfobject.h"

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
  // forward declaration
  class PDFPage;

/**
 * @brief PDF objects namespace.
 */
namespace objects { 
/**
 * This class represents structure tree entity.
 */
class StructTreeEntity : public Base {
 public:
  /**
   * @brief Enumeration for structure tree entity type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _StructTreeEntityType {
    /**
     * @brief Structure tree entity type: unknown.
     */
    e_UnknownType = -1,
    /**
     * @brief Structure tree entity type: Element, which represents a structure element.
     */
    e_StructTreeEntityTypeElement = 0,
    /**
     * @brief Structure tree entity type: MarkedContent, which represents a marked-content item.
     */
    e_StructTreeEntityTypeMarkedContent = 1,
    /**
     * @brief Structure tree entity type: ObjectContent, which represents a PDF object content item, 
     *        such as annotation and XObject.
     */
    e_StructTreeEntityTypeObjectContent = 2
  } StructTreeEntityType;
  
  
  /** @brief Constructor.*/
  StructTreeEntity() {}

  /** @brief Destructor. */
  ~StructTreeEntity();

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit StructTreeEntity(FS_HANDLE handle);

  /**
   * @brief Constructor, with another structure element entity object.
   *
   * @param[in] other  Another structure element entity object.
   */
  StructTreeEntity(const StructTreeEntity& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another structure element entity object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  StructTreeEntity& operator = (const StructTreeEntity& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other Another structure element entity object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const StructTreeEntity& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another structure element entity object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const StructTreeEntity& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get structure tree entity type.
   *
   * @return Structure tree entity type. Please refer to values starting from @link StructTreeEntity::e_StructTreeEntityTypeElement @endlink
   *         and this would be one of these values.
   */
  StructTreeEntityType GetType() const;

  /**
   * @brief Get the related PDF page.
   *
   * @return A PDF page object which is the related PDF page.
   */
  PDFPage GetPage() const;
};

/**
 * This class represents structure element.
 */
class StructElement FS_FINAL : public StructTreeEntity {
 public:
  /**
   * @brief Enumeration for structure element info type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _ElementInfoType {
    /**
     * @brief Structure element info type: Title, which means the title of the structure element. A text string representing it in human-readable form.
     */
    e_ElementInfoTypeTitle = 0,
    /**
     * @brief Structure element info type: Language, which means the natural language for all text in the
     *        structure element except where overridden by language specifications for nested structure elements or marked content. 
     */
    e_ElementInfoTypeLanguage = 1,
    /**
     * @brief Structure element info type: Alternative Description, which means the alternative description of structure element.
     */
    e_ElementInfoTypeAltDescription = 2,
    /**
     * @brief Structure element info type: Expanded Form, which means the expanded form of structure element.
     */
    e_ElementInfoTypeExpandedForm = 3,
    /**
     * @brief Structure element info type: Actual Text, which means the actual text of structure element.
     */
    e_ElementInfoTypeActualText = 4
  } ElementInfoType;
  
   
  /** @brief Constructor.*/
  StructElement() {}

  /**
   * @brief Constructor, with another structure element object.
   *
   * @param[in] other  Another structure element object.
   */
  StructElement(const StructElement& other);

  /**
   * @brief Constructor, with another structure element object.
   *
   * @param[in] other  Another structure element object.
   */
  StructElement(const StructTreeEntity& other);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit StructElement(FS_HANDLE handle);

  /** @brief Destructor. */
  ~StructElement() {}

  /**
   * @brief Get structure type name.
   *
   * @details Every structure element shall have a structure type, a name object that identifies the nature of the   *          structure element and its role within the document (such as a chapter, paragraph, or footnote).
   *          Please refer to the description of "Standard Structure Types" in Section 10.7.3 of <PDF Reference 1.7> or
   *          the description of "Standard structure types" in Section 14.8.4 of <PDF Reference 2.0> for more details.
   *
   * @return A string that represents structure type name of current structure element.
   */
  String GetStructureTypeName() const;

  /**
   * @brief Get the count of child structure tree entities in the current structure element.
   *
   * @return The count of child structure tree entities.
   */
  int GetChildCount() const;

  /**
   * @brief Get a child structure tree entity by index.
   *
   * @param[in] index  Index of a child structure tree entity to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link StructElement::GetChildCount @endlink.
   *
   * @return A child structure tree entity object.
   */
  StructTreeEntity GetChild(int index);

  /**
   * @brief Remove a child structure tree entity by index.
   *
   * @param[in] index  Index of a child structure tree entity to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link StructElement::GetChildCount @endlink.
   *
   * @return None.
   */
  void RemoveChild(int index);

  /**
   * @brief Check whether the structure element information of a specific type exist.
   *
   * @param[in] type  Structure element information type. Please refer to values starting from @link StructElement::e_ElementInfoTypeTitle @endlink
   *                  and this would be one of these values.
   *
   * @return <b>true</b> means the element information type has element information, 
   *         while <b>false</b> means the element information type does not have element information.
   */
  bool HasElementInfo(ElementInfoType type) const;

  /**
   * @brief Get the structure element information.
   *
   * @details Before get structure element information, ensure that the function @link StructElement::HasElementInfo @endlink has been called
   *          and returned true (using the corresponding type).
   *
   * @param[in] type  Structure element information type. Please refer to values starting from @link StructElement::e_ElementInfoTypeTitle @endlink
   *                  and this would be one of these values.
   *
   * @return Structure element information string.
   */
  WString GetElementInfo(ElementInfoType type) const;

  /**
   * @brief Get the parent structure element.
   *
   * @return Parent structure element. If function @link StructElement::IsEmpty @endlink for the returned object returns <b>true</b>,
   *         that means current element does not have a parent element.
   */
  StructElement GetParentElement();
 };

/**
 * This class represents a marked-content item.
 */
class StructMarkedContent FS_FINAL : public StructTreeEntity {
 public:
  /** @brief Constructor.*/
  StructMarkedContent() {}

  /**
   * @brief Constructor, with another structure marked-content object.
   *
   * @param[in] other  Another structure marked-content object.
   */
  StructMarkedContent(const StructMarkedContent& other);

  /**
   * @brief Constructor, with another structure tree entity object.
   *
   * @param[in] other  Another structure tree entity object.
   */
  StructMarkedContent(const StructTreeEntity& other);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit StructMarkedContent(FS_HANDLE handle);

  /** @brief Destructor. */
  ~StructMarkedContent() {}

  /**
   * @brief Get the parent structure element.
   *
   * @return Parent structure element. If function @link StructElement::IsEmpty @endlink for the returned object returns <b>true</b>,
   *         that means current element does not have a parent element.
   */
  StructElement GetParentElement();

  /**
   * @brief Get marked-content identifier(MCID).
   *
   * @return Marked-content identifier.
   */
  uint32 GetMCID() const;

  /**
   * @brief Get PDF dictionary of the content stream that contains the marked-content sequence.
   *
   * @details The content stream containing the marked-content sequence. This entry should be present only if the   *          marked-content sequence resides in a content stream other than the content stream for the page.
   *
   * @return PDF dictionary of content stream that contains
   *         the marked-content sequence.
   */
  pdf::objects::PDFDictionary* GetStmDict() const;

  /**
   * @brief Get PDF dictionary of content stream owner.
   *
   * @return PDF dictionary of content stream owner.
   */
  pdf::objects::PDFDictionary* GetStmOwnerDict() const;
};

/**
 * This class represents a PDF object content item. 
 */
class StructObjectContent FS_FINAL : public StructTreeEntity {
 public:
  /**
   * @brief Enumeration for object type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _StructObjectType {
    /** @brief Unknown Type.*/
    e_UnknownType = -1,
    /** @brief Invaild object.*/
    e_StructObjectTypeInvalid = 0,
    /** @brief Image object.*/
    e_StructObjectTypeImage = 1,
    /** @brief Form object.*/
    e_StructObjectTypeForm = 2,
    /** @brief Annot object.*/
    e_StructObjectTypeAnnot = 3
  } StructObjectType;
  

  /** @brief Constructor.*/
  StructObjectContent() {}

  /**
   * @brief Constructor, with another structure object content object.
   *
   * @param[in] other  Another structure object content object.
   */
  StructObjectContent(const StructObjectContent& other);

  /**
   * @brief Constructor, with another structure tree entity object.
   *
   * @param[in] other  Another structure tree entity object.
   */
  StructObjectContent(const StructTreeEntity& other);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit StructObjectContent(FS_HANDLE handle);

  /** @brief Destructor. */
  ~StructObjectContent() {}

  /**
   * @brief Get the parent structure element.
   *
   * @return Parent structure element. If function @link StructElement::IsEmpty @endlink for the returned object returns <b>true</b>,
   *         that means current element does not have a parent element.
   */
  StructElement GetParentElement();

  /**
   * @brief Get related object type.
   *
   * @return Related object type. Please refer to values starting from @link StructObjectContent::e_Invalid @endlink
   *         and this would be one of these values.
   */
  StructObjectType GetObjectType() const;

  /**
   * @brief Get PDF dictionary of related object.
   *
   * @details This function is available to the following types of objects: @link StructObjectContent::e_Image @endlink, 
   *          @link StructObjectContent::e_Form @endlink and @link StructObjectContent::e_Annot @endlink.
   *          For @link StructObjectContent::e_Invalid type, this function will return <b>NULL</b>.
   *
   * @return PDF dictionary of related object.
   */
  pdf::objects::PDFDictionary* GetDict() const;
};

/**
 * PDF structure tree is a kind of common data structure in tagged PDF documents. A structure tree is used
 * in PDF files to represent the organization and hierarchy of the document's content.
 * PDF structure tree has following characteristics:<br>
 * <ul>
 * <li>A PDF structure tree is also a hierarchical structure, with the top node representing
 *     the entire document and the lower nodes representing pages, paragraphs, headings, and other elements.</li>
 * <li>A PDF structure tree contains semantic information about the content of the document, 
 *     such as headings, paragraphs, tables, and lists. This information is used to enhance the accessibility
 *     and usability of the document, as well as to optimize its display and printing;</li>
 * </ul>
 * Class @link PDFStructTree @endlink is used to be associated with an existing PDF structure tree.
 * It offers functions to get structure elements in the PDF structure tree.
 */
class PDFStructTree FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @details If there exists PDF structure tree in the PDF document,
   *          this function is just to construct a PDF structure tree object to be associated with the structure tree.
   *
   * @param[in] document  A valid PDF document object.
   */
  PDFStructTree(const PDFDoc& document);
  
  /** @brief Destructor. */
  ~PDFStructTree();

  /**
   * @brief Constructor, with another PDF structure tree object.
   *
   * @param[in] other  Another PDF structure tree object.
   */
  PDFStructTree(const PDFStructTree& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another PDF structure tree object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PDFStructTree& operator = (const PDFStructTree& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another PDF structure tree object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const PDFStructTree& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another PDF structure tree object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const PDFStructTree& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get count of structure elements in current PDF structure tree.
   *
   * @return The structure elements count.
   */
  int GetChildCount() const;

  /**
   * @brief Get the structure element by index.
   *
   * @param[in] index  Index of the structure element to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link PDFStructTree::GetChildCount @endlink.
   *
   * @return A @link StructElement @endlink object.
   */
  StructElement GetChild(int index) const;

  /**
   * @brief Remove the structure element by index.
   *
   * @param[in] index  Index of the structure element to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link PDFStructTree::GetChildCount @endlink.
   *
   * @return None.
   */
  void RemoveChild(int index);

   // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
   explicit PDFStructTree(FS_HANDLE handle);
};
}  // namespace objects
}  // namespace pdf
}  // namespace foxit
#endif  // FS_PDFSTRUCTTREE_H_

