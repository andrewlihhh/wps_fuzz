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
 * @file fs_layoutrecognition.h
 * @brief Header file for layout recognition related definitions and classes.
 */

#ifndef FS_LAYOUTRECOGNITION_H_
#define FS_LAYOUTRECOGNITION_H_

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
 * @brief Layout recognition namespace.
 */
namespace layoutrecognition {
/**
 * This class represents base layout recognition element.
 */
class LRElement : public Base {
 public:
  /**
   * @brief Enumeration for standard structure types.
   *
   * @details Values of this enumeration should be used alone.
   *          Please refer to description of "Standard Structure Types" in Section 10.7.3 of <PDF Reference 1.7> and in description of "Standard structure types" in Section 14.8.4 of <PDF Reference 2.0> for more details.
   */
  typedef enum _ElementType {
    /** @brief Structure element type: Document, which represents a complete document. */
    e_ElementTypeDocument = 0x0000,
    /** @brief Structure element type: DocumentFragment (PDF 2.0), which represents a part of an original complete document.  */
    e_ElementTypeDocumentFragment = 0x0001,
    /** @brief Structure element type: Part, which represents a large-scale division of a document. */
    e_ElementTypePart = 0x0002,
    /**
     * @brief Structure element type: Art, which means "Article" and represents a relatively self-contained body
     *        of text constituting a single narrative or exposition.
     */
    e_ElementTypeArt = 0x0101,
    /**
     * @brief Structure element type: Sect, which means "Section" and represents a container for
     *        grouping related content elements.
     */
    e_ElementTypeSect = 0x0102,
    /**
     * @brief Structure element type: Div, which means "Division" and represents a generic block-level element or
     *        group of elements.
     */
    e_ElementTypeDiv = 0x0100,
    /**
     * @brief Structure element type: BlockQuote, which means "Block quotation" and represents
     *        a portion of text consisting of one or more paragraphs attributed to
     *        someone other than the author of the surrounding text.
     */
    e_ElementTypeBlockQuote = 0x0103,
    /**
     * @brief Structure element type: Caption, which represents a brief portion of text
     *        describing a table or figure.
     */
    e_ElementTypeCaption = 0x0104,
    /**
     * @brief Structure element type: TOC, which means "Table of contents" and represents
     *        a list made up of table of contents item entries and/or other nested table
     *        of contents entries.
     */
    e_ElementTypeTOC = 0x0105,
    /**
     * @brief Structure element type: TOCI, which means "Table of contents item" and represents
     *        an individual member of a table of contents.
     */
    e_ElementTypeTOCI = 0x0106,
    /**
     * @brief Structure element type: Index, which represents a sequence of entries containing 
     *        identifying text accompanied by reference elements that point out occurrences of
     *        the specified text in the main body of a document.
     */
    e_ElementTypeIndex = 0x0107,
    /**
     * @brief Structure element type: Aside (PDF 2.0), which represents content that is
     *        distinct from other content within its parent structure element.
     */
    e_ElementTypeAside = 0x0108,
    /** @brief Structure element type: Title (PDF 2.0), which represents content that is usually referred to as the title of a document or high-level devision of content. */
    e_ElementTypeTitle = 0x0109,
    /** @brief Structure element type: FENote (PDF 2.0), which is used to markup footnotes and endnotes.
     */
    e_ElementTypeFENote = 0x010A,
    /**
     * @brief Structure element type: NonStruct, which means "Nonstructural element" and represents
     *        a grouping element having no inherent structural significance;  it serves solely for
     *        grouping purposes.
     */
    e_ElementTypeNonStruct = 0x010F,
    /**
     * @brief Structure element type: Private, which means "Private element" and represents
     *        a grouping element containing private content belonging to the application producing it.
     */
    e_ElementTypePrivate = 0x0110,
    /** @brief Structure element type: P, which means "Paragraph" and represents a low-level division of text. */
    e_ElementTypeParagraph = 0x0200,
    /**
     * @brief Structure element type: H, which means "Heading" and represents a label for
     *        a subdivision of a document's content. It should be the first child of
     *        the division that it heads.
     */
    e_ElementTypeHeading = 0x0201,
    /** @brief Structure element type: H1, which represents heading with level 1. */
    e_ElementTypeHeading1 = 0x0202,
    /** @brief Structure element type: H2, which represents heading with level 2. */
    e_ElementTypeHeading2 = 0x0203,
    /** @brief Structure element type: H3, which represents heading with level 3. */
    e_ElementTypeHeading3 = 0x0204,
    /** @brief Structure element type: H4, which represents heading with level 4. */
    e_ElementTypeHeading4 = 0x0205,
    /** @brief Structure element type: H5, which represents heading with level 5. */
    e_ElementTypeHeading5 = 0x0206,
    /** @brief Structure element type: H6, which represents heading with level 6. */
    e_ElementTypeHeading6 = 0x0207,
    /** @brief Structure element type: Hn (PDF 2.0), which represents heading with level 7 or more. */
    e_ElementTypeHeadingN = 0x0208,
    /**
     * @brief Structure element type: L, which means "List" and represents a sequence of items of
     *        like meaning and importance.
     */
    e_ElementTypeList = 0x0209,
    /** @brief Structure element type: LI, which means "List item" and represents an individual member of a list. */
    e_ElementTypeListItem = 0x020A,
    /**
     * @brief Structure element type: Lbl, which means "Label" and represents a name or number that
     *        distinguishes a given item from others in the same list or other group of like items.
     */
    e_ElementTypeListLabel = 0x020B,
    /**
     * @brief Structure element type: LBody, which means "List body" and reprsents
     *        the descriptive content of a list item.
     */
    e_ElementTypeListBody = 0x020C,
    /**
     * @brief Structure element type: Table, which represents a two-dimensional layout of
     *        rectangular data cells, possibly having a complex substructure.
     */
    e_ElementTypeTable = 0x020D,
    /**
     * @brief Structure element type: TR, which means "Table row" and represents
     *        a row of headings or data in a table.
     */
    e_ElementTypeTableRow = 0x020E,
    /**
     * @brief Structure element type: TH, which means "Table header cell" and represents
     *        a table cell containing header text describing one or more rows or columns
     *        of the table.
     */
    e_ElementTypeTableHeaderCell = 0x020F,
    /**
     * @brief Structure element type: TD, which means "Table data cell" and represents
     *        a table cell containing data that is part of the table's content.
     */
    e_ElementTypeTableDataCell = 0x0210,
    /**
     * @brief Structure element type: THead, which means "Table header row group" and represents
     *        a group of rows that constitute the header of a table.
     */
    e_ElementTypeTableHeaderGroup = 0x0211,
    /**
     * @brief Structure element type: TBody, which means "Table body row group" and represents
     *        a group of rows that constitute the main body portion of a table.
     */
    e_ElementTypeTableBodyGroup = 0x0212,
    /**
     * @brief Structure element type: TFoot, which means "Table footer row group" and represents
     *        a group of rows that constitute the footer of a table.
     */
    e_ElementTypeTableFootGroup = 0x0213,
    /**
     * @brief Structure element type: Span, which represents a generic inline portion of text
     *        having no particular inherent characteristics.
     */
    e_ElementTypeSpan = 0x0300,
    /**
     * @brief Structure element type: Quote, which means "Quotation" and represents
     *        an inline portion of text attributed to someone other than the author of
     *        the surrounding text.
     */
    e_ElementTypeQuote = 0x0301,
    /**
     * @brief Structure element type: Note, which represents an item of explanatory text,
     *        such as a footnote or an endnote, that is referred to from within the body of
     *        the document.
     */
    e_ElementTypeNote = 0x0302,
    /**
     * @brief Structure element type: Reference, which represents a citation to content
     *        elsewhere in the document.
     */
    e_ElementTypeReference = 0x0303,
    /**
     * @brief Structure element type: BibEntry, which means "Bibliography entry" and represents
     *        a reference identifying the external source of some cited content.
     */
    e_ElementTypeBibEntry = 0x0304,
    /** @brief Structure element type: Code, which represents a fragment of computer program text. */
    e_ElementTypeCode = 0x0305,
    /**
     * @brief Structure element type: Link, which represents an association between a portion of
     *        the ILSE's content and a corresponding link annotation or annotations.
     */
    e_ElementTypeLink = 0x0306,
    /**
     * @brief Structure element type: Annot, which means "Annotation" and represents
     *        an association between a portion of the ILSE's content and
     *        a corresponding PDF annotation.
     */
    e_ElementTypeAnnot = 0x0307,
    /** @brief Structure element type: Ruby, which represents the wrapper around the entire ruby assembly. */
    e_ElementTypeRuby = 0x0308,
    /**
     * @brief Structure element type: RB, which means "Ruby base text" and represents
     *        the full-size text to which the ruby annotation is applied.
     */
    e_ElementTypeRubyBase = 0x0309,
    /**
     * @brief Structure element type: RT, which means "Ruby annotation text" and represents
     *        the smaller-size text that is placed adjacent to the ruby base text.
     */
    e_ElementTypeRubyAnnot = 0x030A,
    /**
     * @brief Structure element type: RP, which means "Ruby punctuation" and represents
     *        punctuation surrounding the ruby annotation text.
     */
    e_ElementTypeRubyPunc = 0x030B,
    /**
     * @brief Structure element type: Warichu, which represents the wrapper around
     *        the entire warichu assembly.
     */
    e_ElementTypeWarichu = 0x030C,
    /**
     * @brief Structure element type: WT, which means "Warichu text" and represents
     *        the smaller-size text of a warichu comment that is formatted into two lines and
     *        placed between surrounding WP elements.
     */
    e_ElementTypeWarichuText = 0x030D,
    /**
     * @brief Structure element type: WP, which means "Warichu punctuation" and represents
     *        the punctuation that surrounds the WT text.
     */
    e_ElementTypeWarichuPunc = 0x030E,
    /**
     * @brief Structure element type: Em (PDF 2.0), which means "Emphasis" and represents content for
     *        the purpose of emphasis.
     */
    e_ElementTypeEm = 0x030F,
    /**
     * @brief Structure element type: Strong (PDF 2.0), which represents content for the purpose of
     *        strong importance, seriousness or urgency for its contents.
     */
    e_ElementTypeStrong = 0x0310,
    /**
     * @brief Structure element type: Sub (PDF 2.0), which means "Sub-division of a block level element" and represents
     *         content typically perceived as a sub-division inside a block level structure element.
     */
    e_ElementTypeSub = 0x0311,
    /** @brief Structure element type: Figure, which represents an item of graphical content. */
    e_ElementTypeFigure = 0x0400,
    /** @brief Structure element type: Formula, which represents a mathematical formula. */
    e_ElementTypeFormula = 0x0401,
    /**
     * @brief Structure element type: Form, which represents a widget annotation
     *        representing an interactive form field.
     */
    e_ElementTypeForm = 0x0402,
    /**
     * @brief Structure element type: Artifact, which includes other Pagination, Layout,
     *        Page and Background artifacts.
     */
    e_ElementTypeArtifact = 0x1000,
    /** @brief Structure element type: TextObject, which means text graphics object element. */
    e_ElementTypeTextObject = 0x80000001,
    /** @brief Structure element type: PathObject, which means path graphics object element. */
    e_ElementTypePathObject = 0x80000002,
    /** @brief Structure element type: ImageObject, which means image graphics object element. */
    e_ElementTypeImageObject = 0x80000003,
    /** @brief Structure element type: ShadingObject, which means shading graphics object element. */
    e_ElementTypeShadingObject = 0x80000004,
    /** @brief Structure element type: FormObject, which means form XObject graphics object element. */
    e_ElementTypeFormObject = 0x80000005,
    /** @brief Structure element type: ContainerObject, which means container object element. */
    e_ElementTypeContainerObject = 0x8000000C,
    /** @brief Structure element type: AnnotObject, which means annotation object element. */
    e_ElementTypeAnnotObject = 0x8000000E,
    /** @brief Structure element type: PageObject, which means page object element. */
    e_ElementTypePageObject = 0x8000000F,
    /** @brief Structure element type: TextContent, which means text content element. */
    e_ElementTypeTextContent = 0xC0000001,
    /** @brief Structure element type: PathContent, which means path content element. */
    e_ElementTypePathContent = 0xC0000002,
    /** @brief Structure element type: ImageContent, which means image content element. */
    e_ElementTypeImageContent = 0xC0000003,
    /** @brief Structure element type: ShadingContent, which means shading content element. */
    e_ElementTypeShadingContent = 0xC0000004,
    /** @brief Structure element type: ComplexContent, which means complex content element. */
    e_ElementTypeComplexContent = 0xC000000D,
    /** @brief Structure element type: AnnotContent, which means annotation content element. */
    e_ElementTypeAnnotContent = 0xC000000E
  } ElementType;
  

  /** @brief Constructor. */
  LRElement() {}

  /**
   * @brief Constructor, with another base element object.
   *
   * @param[in] other  Another base element object.
   */
  LRElement(const LRElement& other);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit LRElement(FS_HANDLE handle);

  /** @brief Destructor. */
  ~LRElement();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another base element object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  LRElement& operator = (const LRElement& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another base element object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const LRElement& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another base element object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const LRElement& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get element type.
   *
   * @return Element type. Please refer to values starting from @link LRElement::e_ElementTypeDocument @endlink
   *         and this would be one of these values.
   */
  ElementType GetElementType();

  /**
   * @brief Check whether current object is content element or not.
   *
   * @return <b>true</b> means current object is content element,
   *         while <b>false</b> means current object is not content element.
   */
  bool IsContentElement() const;

  /**
   * @brief Check whether current object is graphics object element or not.
   *
   * @return <b>true</b> means current object is graphics object element,
   *         while <b>false</b> means current object is not graphics object element.
   */
  bool IsGraphicsObjectElement() const;

  /**
   * @brief Check whether current object is structure element or not.
   *
   * @return <b>true</b> means current object is structure element,
   *         while <b>false</b> means current object is not structure element,
   */
  bool IsStructureElement() const;

  /**
   * @brief Convert type (enum value) of current element to a short and memorable string (text) representation.
   *
   * @return A short and memorable string that represents type of current element.
   *         If there is no short and memorable string, this function would return an empty string.
   */
  String StringifyType() const;

  /**
   * @brief Convert enum value of a specified element type to a short and memorable string (text) representation.
   *
   * @param[in] type  A specified element type. Please refer to values starting from @link LRElement::e_ElementTypeDocument @endlink
   *                  and this should be one of these values.
   *
   * @return A string that represents the short and memorable string representation for specified type.
   *         If there is no short and memorable string representation or input type is an invalid enum value,
   *         this function would return an empty string.
   */
  static String StringifyElementType(ElementType type);
};

/**
 * This class represents a structure element. A structure element can be used to construct a tree, like graphics structure element, paragraph
 * structure element, span structure element and so on.
 */
class LRStructureElement FS_FINAL : public LRElement {
 public:
  /**
   * @brief Enumeration for element general layout attribute types.
   *
   * @details Values of this enumeration should be used alone.
   *          For more details, please refer to "Layout Attributes" in <PDF reference 1.7> P916.
   */
  typedef enum _AttributeType {
    /** @brief Attribute type: invalid. */
    e_AttributeTypeInvalid = 0x0,
    /**
     *  @brief Attribute type: role, which means strings of structure element meaning and 
     *         standard type it maps to.
     *
     * @note Value type for this attribute type is string.
     */
    e_AttributeTypeRole = 0x524f4c45,
    /**
     * @brief Attribute type: Placement, which means the positioning of the element with
     *        respect to the enclosing reference area and other content.
     * 
     * @note Value type for this attribute type is enum. Valid enum values are:<br>
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumBlock @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumInline @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumBefore @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumStart @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumEnd @endlink</li>
     *       </ul>
     */
    e_AttributeTypePlacement = 0x504c4143,
    /**
     * @brief Attribute type: Rotation
     *
     * @note Value type for this attribute type is number.
     */
    e_AttributeTypeRotation = 0x524f5441,
    /**
     * @brief Attribute type: WritingMode, which means the directions of layout progression for 
     *        packing of ILSEs (inline progression) and stacking of BLSEs (block progression).
     *
     * @note Value type for this attribute type is enum. Valid enum values are:<br>
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumLrTb @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumRlTb @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumTbRl @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumTbLr @endlink (PDF 2.0)</li>
     *       </ul>
     */
    e_AttributeTypeWritingMode = 0x574d4f44,
    /**
     * @brief Attribute type: Destination (PDF 2.0), which provides a means to access content.
     *
     * @note Value type for this attribute type is an array of zero or stirngs with ID.
     */
    e_AttributeTypeDestination = 0x44455354,
    /**
     * @brief Attribute type: BBox, which represents the element's bounding box (the rectangle
     *        that completely encloses its visible content).
     *
     * @note Value type for this attribute type is an array of four numbers in [PDF coordinate system] (@ref pdf::PDFPage)
     *       giving the coordinates of the left, bottom, right, and top edges of the elements's bounding box.
     */
    e_AttributeTypeBBox = 0x42424f58,
    /**
     * @brief Attribute type: Width, which represents the width of the element's content rectangle.
     *
     * @note Value type for this attribute type is number or enum value @link LRStructureElement::e_AttributeValueEnumAuto @endlink.
     */
    e_AttributeTypeWidth = 0x57445448,
    /**
     * @brief Attribute type: Height, which represents the height of the element's content rectangle.
     *
     * @note Value type for this attribute type is number or enum value @link LRStructureElement::e_AttributeValueEnumAuto @endlink.
     */
    e_AttributeTypeHeight = 0x48474854,
    /**
     * @brief Attribute type: BackgroundColor, which represents the color to be used to
     *        fill the background of a table cell or any element's content rectangle.
     *
     * @note Value type for this attribute type is RGB color.
     */
    e_AttributeTypeBackgroundColor = 0x424b4743,
    /**
     * @brief Attribute type: BorderColor, which represents the color of the border
     *       drawn on the edges of a table cell or any element's content rectangle.
     *
     * @note Value type for this attribute type is RGB color or an array of RGB color values.
     */
    e_AttributeTypeBorderColor = 0x42445243,
    /**
     * @brief Attribute type: BorderStyle, which represents the style of an element's border.
     *
     * @note Value type for this attribute type is enum or an array of enum values.
     *       Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumNone @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumHidden @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumDotted @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumDashed @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumSolid @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumDouble @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumGroove @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumRidge @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumInset @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumOutset @endlink</li>
     *       </ul>
     */
    e_AttributeTypeBorderStyle = 0x42445253,
    /**
     * @brief Attribute type: BorderThickness, which represents the thickness of the border
     *        drawn on the edges of a table cell or any element's content rectangle.
     *
     * @note Value type for this attribute type is number (for all four edges) or
     *       an array of four numbers (for one edge of the border, in the order of
     *       the before, after, start, and end edge).
     */
    e_AttributeTypeBorderThickness = 0x42445254,
    /**
     * @brief Attribute type: Attached, which specifies the edges of the page, if any,
     *        to which the artifact is logically attached.
     *
     * @note Value type for this attribute type is an array of specified enum values.
     *       Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumTop @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumLeft @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumBottom @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumRight @endlink</li>
     *       </ul>
     */
    e_AttributeTypeAttached = 0x41545448,
    /**
     * @brief Attribute type: Subtype, which means the subtype of annotation or artifact.
     *
     * @note Value type for this attribute type:
     *       <ul>
     *       <li>For annotation, value type is string.</li>
     *       <li>For artifact, value type is enum. Valid enum values are:
     *           <ul>
     *           <li>@link LRStructureElement::e_AttributeValueEnumPagination @endlink</li>
     *           <li>@link LRStructureElement::e_AttributeValueEnumLayout @endlink</li>
     *           <li>@link LRStructureElement::e_AttributeValueEnumPage @endlink</li>
     *           <li>@link LRStructureElement::e_AttributeValueEnumBackground @endlink</li>
     *           </ul>
     *       </li>
     *       </ul>
     */
    e_AttributeTypeSubType = 0x53554254,
    /**
     * @brief Attribute type: Padding, which specifies an offset to account for the separation between the element's content rectangle and the surrounding border.
     *
     * @note Value type for this attribute type is number (for all four sides) or
     *       an array of four numbers (for the before, after, start, and end edge).
     */
    e_AttributeTypePadding = 0x50414447,
    /**
     * @brief Attribute type: Color, which represents the color to be used for drawing text and
     *        the default value for the color of table borders and text decorations. 
     *
     * @note Value type for this attribute type is RGB color.
     */
    e_AttributeTypeColor = 0x434f4c52,
    /**
     * @brief Attribute type: SpaceBefore, which represents the amount of extra space preceding
     *        the before edge of the BLSE.
     *
     * @note Value type for this attribute type is number.
     */
    e_AttributeTypeSpaceBefore = 0x53504246,
    /**
     * @brief Attribute type: SpaceAfter, which represents the amount of extra space following
     *        the after edge of the BLSE.
     *
     * @note Value type for this attribute type is number.
     */
    e_AttributeTypeSpaceAfter = 0x53504146,
    /**
     * @brief Attribute type: StartIndent, which represents the distance from the start edge of
     *        the reference area to that of the BLSE.
     *
     * @note Value type for this attribute type is number.
     */
    e_AttributeTypeStartIndent = 0x53494e44,
    /**
     * @brief Attribute type: EndIndent, which represents the distance from the end edge of
     *        the BLSE to that of the reference area.
     *
     * @note Value type for this attribute type is number.
     */
    e_AttributeTypeEndIndent = 0x45494e44,
    /**
     * @brief Attribute type: TextIndent, which represents the additional distance
     *        from the start edge of the BLSE, as specified by
    *         @link LRStructureElement::e_AttributeTypeStartIndent @endlink,
     *        to that of the first line of text. 
     *
     * @note Value type for this attribute type is number.
     */
    e_AttributeTypeTextIndent = 0x54494e44,
    /**
     * @brief Attribute type: TextAlign, which represents the alignment of text and
     *        other content within lines of the BLSE.
     *
     * @note Value type for this attribute type is enum. Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumStart @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumCenter @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumEnd @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumJustify @endlink</li>
     *       </ul>
     */
    e_AttributeTypeTextAlign = 0x54414c4e,
    /**
     * @brief Attribute type: BlockAlign, which represents the alignment, in the block-progression direction,
     *        of content within the table cell.
     *
     * @note Value type for this attribute type is enum. Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumBefore @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumCenter @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumAfter @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumJustify @endlink</li>
     *       </ul>
     */
    e_AttributeTypeBlockAlign = 0x42414c4e,
    /**
     * @brief Attribute type: InlineAlign, which represents the alignment, in the inline-progression direction,
     *        of content within the table cell.
     *
     * @note Value type for this attribute type is enum. Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumStart @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumCenter @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumEnd @endlink</li>
     *       </ul>
     */
    e_AttributeTypeInlineAlign = 0x49414c4e,
    /**
     * @brief Attribute type: TBorderStyle, which represents the style of the border drawn on
     *        each edge of a table cell.
     *
     * @note Value type for this attribute type is enum or an array of specified enum values.
     *       Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumNone @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumHidden @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumDotted @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumDashed @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumSolid @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumDouble @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumGroove @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumRidge @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumInset @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumOutset @endlink</li>
     *       </ul>
     */
    e_AttributeTypeTBorderStyle = 0x54424453,
    /**
     * @brief Attribute type: TPadding, which specifies an offset to account for the separation
     *        between the table cell's content rectangle and the surrounding border.
     *
     * @note Value type for this attribute type is number (for all four edges of the table cell) or
     *       an array of four numbers (for the before edge, after edge, start edge,
     *       and end edge of the content rectangle).
     */
    e_AttributeTypeTPadding = 0x54504144,
    /**
     * @brief Attribute type: BaselineShift, which means the distance by which the element's baseline
     *        is shifted relative to that of its parent element.
     *
     * @note Value type for this attribute type is number.
     */
    e_AttributeTypeBaselineShift = 0x42534846,
    /**
     * @brief Attribute type: LineHeight, which means the element's preferred height, in the block-progression direction.
     *
     * @note Value type for this attribute type can be number or enum. Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumNormal @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumAuto @endlink</li>
     *       </ul>
     */
    e_AttributeTypeLineHeight = 0x4c484754,
    /**
     * @brief Attribute type: TextDecorationColor, which represents the color to be used for
     *        drawing text decorations.
     *
     * @note Value type for this attribute type is RGB color.
     */
    e_AttributeTypeTextDecorationColor = 0x5444434c,
    /**
     * @brief Attribute type: TextDecorationThickness, which represents the thickness of each line drawn
     *        as part of the text decoration.
     *
     * @note Value type for this attribute type is number.
     */
    e_AttributeTypeTextDecorationThickness = 0x54445448,
    /**
     * @brief Attribute type: TextDecorationType, which represents the text decoration, if any,
     *        to be applied to the element's text.
     *
     * @note Value type for this attribute type is enum or an array of specified enum values.
     *       Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumNone @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumUnderline @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumOverline @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumLineThrough @endlink</li>
     *       </ul>
     */
    e_AttributeTypeTextDecorationType = 0x54445459,
    /**
     * @brief Attribute type: RubyAlign, which represents the justification of the lines within a ruby assembly.
     *
     * @note Value type for this attribute type is enum or an array of specified enum values.
     *       Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumStart @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumCenter @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumEnd @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumJustify @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumDistribute @endlink</li>
     *       </ul>
     */
    e_AttributeTypeRubyAlign = 0x5242414c,
    /**
     * @brief Attribute type: RubyPosition, which represents the placement of the RT structure element
     *        relative to the RB element in a ruby assembly.
     *
     * @note Value type for this attribute type is enum. Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumBefore @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumAfter @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumWarichu @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumInline @endlink</li>
     *       </ul>
     */
    e_AttributeTypeRubyPosition = 0x52425053,
    /**
     * @brief Attribute type: GlyphOrientationVertical, which specifies the orientation of glyphs
     *        when the inline-progression direction is top to bottom or bottom to top.
     *
     * @note Value type for this attribute type is number (which should be one of specified numbers -90, 0, 90, 180, and 270) or
     *       enum (which should be value @link LRStructureElement::e_AttributeValueEnumAuto @endlink).
     */
    e_AttributeTypeGlyphOrientationVertical = 0x474f5654,
    /**
     * @brief Attribute type: ColumnCount, which represents the number of columns
     *        in the content of the grouping element.
     *
     * @note Value type for this attribute type is number.
     */
    e_AttributeTypeColumnCount = 0x434c434e,
    /**
     * @brief Attribute type: ColumnGap, which represents the desired space between adjacent columns,
     *        measured in the inline-progression direction.
     *
     * @note Value type for this attribute type can be number (for all columns) or an array of numbers.
     *       When the value type is array:
     *       <ul>
     *       <li>if the array contains (ColumnCount-1) numbers, these numbers represent the space
     *           between the first and second columns, the second and third columns, and so on,
     *           respectively.</li>
     *       <li>if there are fewer than (ColumnCount-1) numbers, the last element specifies
     *           all remaining spaces; excess array elements are ignored.</li>
     *       </ul>
     */
    e_AttributeTypeColumnGap = 0x434c4750,
    /**
     * @brief Attribute type: ColumnWidths, which represents the desired width of the columns, 
     *        measured in the inline-progression direction.
     *
     * @note Value type for this attribute type can be number (for all columns) or an array of numbers.
     *       When the value type is array:
     *       <ul>
     *       <li>if the array contains ColumnCount numbers, these numbers represent the width of each column, in order.</li>
     *       <li>if there are fewer than ColumnCount numbers, the last element specifies
     *           all remaining widths; excess array elements are ignored.</li>
     *       </ul>
     */
    e_AttributeTypeColumnWidths = 0x434c5744,
    /**
     * @brief Attribute type only for List: ListNumbering, which represents the numbering system to be used to
     *        generate the content of the Lbl (Label) elements in an autonumbered list,
     *        or the symbol used to identify each item in an unnumbered list.
     *
     * @note Value type for this attribute type is enum. Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumNone @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumDisc @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumCircle @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumSquare @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumDecimal @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumUpperRoman @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumLowerRoman @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumUpperAlpha @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumLowerAlpha @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumUnordered @endlink (PDF 2.0)</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumOrdered @endlink (PDF 2.0)</li>
     *       </ul>
     */
    e_AttributeTypeListNumbering = 0x4c4e554d,
    /**
     * @brief Attribute type only for PrintField: Role, which represents the type of form field
     *        represented by this graphic. 
     *
     * @note Value type for this attribute type is enum. Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumRB @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumCB @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumPB @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumTV @endlink</li>
     *       </ul>
     */
    e_AttributeTypeFieldRole = 0x46524f4c,
    /**
     * @brief Attribute type only for PrintField: checked, which represents the state of
     *        a radio button or check box field. 
     *
     * @note Value type for this attribute type is enum. Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumOn @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumOff @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumNeutral @endlink</li>
     *       </ul>
     */
    e_AttributeTypeFieldChecked = 0x43484b44,
    /**
     * @brief Attribute type only for PrintField: Desc, which represents the alternate name of the field,
     *        similar to the value supplied in the TU entry of the field dictionary
     *        for interactive fields.
     *
     * @note Value type for this attribute type is string.
     */
    e_AttributeTypeFieldDesc = 0x46445343,
    /**
     * @brief Attribute type only for Table: RowSpan, which represents the number of rows
     *        in the enclosing table that are spanned by the cell.
     *
     * @note Value type for this attribute type is number.
     */
    e_AttributeTypeRowSpan = 0x5253504e,
    /**
     * @brief Attribute type only for Table: ColSpan, which represents the number of columns
     *        in the enclosing table that are spanned by the cell.
     *
     * @note Value type for this attribute type is number.
     */
    e_AttributeTypeColSpan = 0x4353504e,
    /**
     * @brief (Currently, unsupported) Attribute type only for Table: Headers, which represents an array of element identifiers.
     *
     * @note Value type for this attribute type is an array of strings.
     */
    e_AttributeTypeTableHeaders = 0x54484453,
    /**
     * @brief Attribute type only for Table: Scope, which indicates whether the header cell applies to
     *        the rest of the cells in the row that contains it, the column that contains it,
     *        or both the row and the column that contain it.
     *
     * @note Value type for this attribute type is enum. Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumRow @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumColumn @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumBoth @endlink</li>
     *       </ul>
     */
    e_AttributeTypeTableHeaderScope = 0x54485343,
    /**
     * @brief Attribute type only for Table: Summary, which represents a summary of the table's purpose and structure,
     *        for use in non-visual rendering such as speech or braille.
     *
     * @note Value type for this attribute type is string.
     */
    e_AttributeTypeTableSummary = 0x5442534d,
    /**
     * @brief Attribute type: Short (PDF 2.0), which contains a short form of the content of
     *        a TH structure element's content.
     *
     * @note Value type for this attribute type is string.
     */
    e_AttributeTypeShort	= 0x53484f52,
    /**
     * @brief (Reserved) Attribute type: Direction.
     *
     * @note Value type for this attribute type is enum. Valid enum values are:
     *       <ul>
     *       <li>@link LRStructureElement::e_AttributeValueEnumStart @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumEnd @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumBefore @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumAfter @endlink</li>
     *       <li>@link LRStructureElement::e_AttributeValueEnumOther @endlink (PDF 2.0)</li>
     *       </ul>
     */
    e_AttributeTypeDirection = 0x44495245,
    /**
     * @brief (Reserved) Attribute type: ABox.
     *
     * @note Value type for this attribute type is an array of four numbers.
     */
    e_AttributeTypeABox = 0x414c4258,
    /**
     * @brief (Reserved) Attribute type: Version, which represents schema version of layout recognition engine.
     *
     * @note Value type for this attribute type is number.
     */
    e_AttributeTypeVersion = 0x5645534e
  } AttributeType;
  
  /**
   * @brief Enumeration for element general layout attribute enum values.
   *
   * @details Values of this enumeration should be used alone.
   *          This is the set of enum values for all attribute types whose value types are enum or an array of enum values.
   */
  typedef enum _AttributeValueEnum {
    /** @brief Invalid enum value. */
    e_AttributeValueEnumInvalid = 0x0,
    /**
     * @brief Enum value: Block, which means to be stacked in the block-progression direction
     *        within an enclosing reference area or parent BLSE.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypePlacement @endlink.
     */
    e_AttributeValueEnumBlock = 0x424c434b,
    /**
     * @brief Enum value: Inline, which means the placement for attributes Placement/RubyPosition.
     *
     * @details <ul>
     *          <li>For attribute Placement, this means to be packed in the inline-progression direction
     *              within an enclosing BLSE. </li>
     *          <li>For attribute RubyPosition, this means that the RT and associated RP elements are
     *              to be formatted as a parenthesis comment, following the RB element</li>
     *          </ul>
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypePlacement @endlink,
    *        and @link LRStructureElement::e_AttributeTypeRubyPosition @endlink.
     */
    e_AttributeValueEnumInline = 0x494e4c4e,
    /**
     * @brief Enum value: Warichu, which means the RT and associated RP elements are to
     *        be formatted as a warichu, following the RB element.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeRubyPosition @endlink.
     */
    e_AttributeValueEnumWarichu = 0x57415249,
    /**
     * @brief Enum value: Before, which means the placement for attributes Placement/RubyPosition or alignment for attribute BlockAlign.
     *
     * @details <ul>
     *          <li>For attribute Placement, this means to be placed so that the before edge of
     *              the element's allocation rectangle coincides with that of the nearest
     *              enclosing reference area.</li>
     *          <li>For attribute BlockAlign, this means before edge of the first child's allocation rectangle
     *              aligned with that of the table cell's content rectangle.</li>
     *          <li>For attribute RubyPosition, this means the placement of the RT structure element
     *              relative to the RB element in a ruby assembly.</li>
     *          </ul>
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypePlacement @endlink,
     *       @link LRStructureElement::e_AttributeTypeBlockAlign @endlink,
     *       and @link LRStructureElement::e_AttributeTypeRubyPosition @endlink.
     */
    e_AttributeValueEnumBefore = 0x42454652,
    /**
     * @brief Enum value: After, which means the alignment for attribute BlockAlign or the placement for attribute RubyPosition.
     *
     * @details <ul>
     *          <li>For attribute BlockAlign, this means after edge of the last child's allocation rectangle 
     *              aligned with that of the table cell's content rectangle.</li>
     *          <li>For attribute RubyPosition, this means the RT content is to be aligned along the
     *              after edge of the element.</li>
     *          </ul>
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypeBlockAlign @endlink,
     *       and @link LRStructureElement::e_AttributeTypeRubyPosition @endlink.
     */
    e_AttributeValueEnumAfter = 0x41465445,
    /**
     * @brief Enum value: Start, which means the place for attribute Placement,
     *        or the alignment for attributes TextAlign/InlineAlign/RubyAlign.
     *
     * @details <ul>
     *          <li>For attribute Placement, this means to be placed so that the start edge of
     *              the element's allocation rectangle coincides with that of the nearest
     *              enclosing reference area.</li>
     *          <li>For attribute TextAlign, this means to be aligned with the start edge.</li>
     *          <li>For attribute InlineAlign, this means start edge of each child's allocation rectangle 
     *              aligned with that of the table cell's content rectangle.</li>
     *          <li>For attribute RubyAlign, this means that the content is to be aligned on the start edge
     *              in the inlineprogression direction.</li>
     *          </ul>
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypePlacement @endlink,
     *       @link LRStructureElement::e_AttributeTypeTextAlign @endlink,
     *       @link LRStructureElement::e_AttributeTypeInlineAlign @endlink,
     *       and @link LRStructureElement::e_AttributeTypeRubyAlign @endlink.
     */
    e_AttributeValueEnumStart = 0x53545254,
    /**
     * @brief Enum value: End, which means the place for attribute Placement,
     *        or the alignment for attributes TextAlign/InlineAlign/RubyAlign.
     *
     * @details <ul>
     *          <li>For attribute Placement, this means to be placed so that the end edge of
     *              the element's allocation rectangle coincides with that of the nearest
     *              enclosing reference area. </li>
     *          <li>For attribute TextAlign, this means to be aligned with the end edge.</li>
     *          <li>For attribute InlineAlign, this means end edge of each child's allocation rectangle
     *              aligned with that of the table cell's content rectangle.</li>
     *          <li>For attribute RubyAlign, this means that the content is to be aligned on the end edge
     *              in the inlineprogression direction.</li>
     *          </ul>
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypePlacement @endlink,
     *       @link LRStructureElement::e_AttributeTypeTextAlign @endlink,
     *       @link LRStructureElement::e_AttributeTypeInlineAlign @endlink,
     *       and @link LRStructureElement::e_AttributeTypeRubyAlign @endlink.
     */
    e_AttributeValueEnumEnd = 0x454e4400,
    /**
     * @brief Enum value: LtTb, which means inline progression from left to right;
     *        block progression from top to bottom. 
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeWritingMode @endlink.
     */
    e_AttributeValueEnumLrTb = 0x4c525442,
    /**
     * @brief Enum value: RlTb, which means inline progression from right to left;
     *        block progression from top to bottom. 
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeWritingMode @endlink.
     */
    e_AttributeValueEnumRlTb = 0x524c5442,
    /**
     * @brief Enum value: TbRl, which means inline progression from top to bottom;
     *        block progression from right to left.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeWritingMode @endlink.
     */
    e_AttributeValueEnumTbRl = 0x5442524c,
    /**
     * @brief Enum value: TbLr (PDF 2.0), which means inline progression from top to bottom;
     *        block progression from left to right.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeWritingMode @endlink.
     */
    e_AttributeValueEnumTbLr = 0x54424c52,
    /**
     * @brief Enum value: None, which means no such attribute.
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypeBorderStyle @endlink,
     *       @link LRStructureElement::e_AttributeTypeTBorderStyle @endlink,
    .*       @link LRStructureElement::e_AttributeTypeTextDecorationType @endlink,
     *       and @link LRStructureElement::e_AttributeTypeListNumbering @endlink.
     */
    e_AttributeValueEnumNone = 0x4e4f4e45,
    /**
     * @brief Enum value: Hidden, which is same as None except in terms of
     *        border conflict resolution for table elements.
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypeBorderStyle @endlink,
     *       and @link LRStructureElement::e_AttributeTypeTBorderStyle @endlink.
     */
    e_AttributeValueEnumHidden = 0x4849444e,
    /**
     * @brief Enum value: Dotten, which means the border is a series of dots.
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypeBorderStyle @endlink,
     *       and @link LRStructureElement::e_AttributeTypeTBorderStyle @endlink.
     */
    e_AttributeValueEnumDotted = 0x444f5444,
    /**
     * @brief Enum value: Dashed, which means the border is a series of short line segments.
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypeBorderStyle @endlink,
     *       and @link LRStructureElement::e_AttributeTypeTBorderStyle @endlink.
     */
    e_AttributeValueEnumDashed = 0x44534844,
    /**
     * @brief Enum value: Solid, which means the border is a single line segment.
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypeBorderStyle @endlink,
     *       and @link LRStructureElement::e_AttributeTypeTBorderStyle @endlink.
     */
    e_AttributeValueEnumSolid = 0x534f4c44,
    /**
     * @brief Enum value: Double, which means the border is two solid lines.
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypeBorderStyle @endlink,
     *       and @link LRStructureElement::e_AttributeTypeTBorderStyle @endlink.
     */
    e_AttributeValueEnumDouble = 0x44424c45,
    /**
     * @brief Enum value: Groove, which means the border looks as though it were carved into the canvas.
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypeBorderStyle @endlink,
     *       and @link LRStructureElement::e_AttributeTypeTBorderStyle @endlink.
     */
    e_AttributeValueEnumGroove = 0x41525459,
    /**
     * @brief Enum value: Ridge, which means the border looks as though it were coming out of the canvas (the opposite of Groove).
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypeBorderStyle @endlink,
     *       and @link LRStructureElement::e_AttributeTypeTBorderStyle @endlink.
     */
    e_AttributeValueEnumRidge = 0x52444745,
    /**
     * @brief Enum value: Inset, which means the border makes the entire box
     *        look as though it were embedded in the canvas.
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypeBorderStyle @endlink,
     *       and @link LRStructureElement::e_AttributeTypeTBorderStyle @endlink.
     */
    e_AttributeValueEnumInset = 0x494e5354,
    /**
     * @brief Enum value: Outset, which means the border makes the entire box
     *        look as though it were coming out of the canvas (the opposite of Inset).
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypeBorderStyle @endlink,
     *       and @link LRStructureElement::e_AttributeTypeTBorderStyle @endlink.
     */
    e_AttributeValueEnumOutset = 0x4f545354,
    /**
     * @brief Enum value: Normal, which means to adjust the line height to include any nonzero value
  specified for attribute BaselineShift .
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeLineHeight @endlink.
     */
    e_AttributeValueEnumNormal = 0x4e524d4c,
    /**
     * @brief Enum value: Auto.
     *
     * @details <ul>
     *          <li>For attribute Width and Height, this indicates that no specific value and
     *              the value will be determined automatically.</li>
     *          <li>For attribute LineHeight, this means not to adjust for the value of BaselineShift.</li>
     *          <li>For attribute GlyphOrientationVertical, this specifies a default orientation for
     *              text depending on whether it is fullwidth(as wide as it is high).</li>
     *          </ul>
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypeWidth @endlink,
     *       @link LRStructureElement::e_AttributeTypeHeight @endlink, 
     *       @link LRStructureElement::e_AttributeTypeLineHeight @endlink, 
     *       and @link LRStructureElement::e_AttributeTypeGlyphOrientationVertical @endlink.
     */
    e_AttributeValueEnumAuto = 0x4155544f,
    /**
     * @brief Enum value: Center, which means the alignment for attributes TextAlign/InlineAlign/RubyAlign.
     *
     * @details <ul>
     *          <li>For attribute TextAlign, this means to be centered between the start and end edges.</li>
     *          <li>For attribute InlineAlign, this means that each child centered within the table cell.</li>
     *          <li>For attribute RubyAlign, this means that the content is to be centered
     *              in the inline-progression direction</li>
     *          </ul>
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypeTextAlign @endlink,
     *       @link LRStructureElement::e_AttributeTypeInlineAlign @endlink, 
     *       and @link LRStructureElement::e_AttributeTypeRubyAlign @endlink.
     */
    e_AttributeValueEnumCenter = 0x434e5452,
    /**
     * @brief Enum value: Justify, which means the alignment for attributes TextAlign/BlockAlign/RubyAlign.
     *
     * @details <ul>
     *          <li>For attribute TextAlign, this means to be aligned with both the start and end edges,
     *              with internal spacing within each line expanded, if necessary,
     *              to achieve such alignment.</li>
     *          <li>For attribute BlockAlign, this means that children are aligned with both the before
     *              and after edges of the table cell's content rectangle. </li>
     *          <li>For attribute RubyAlign, this means that the content is to be centered
     *              in the inline-progression direction</li>
     *          </ul>
     *
     * @note This can be used with attribute types @link LRStructureElement::e_AttributeTypeTextAlign @endlink,
     *       @link LRStructureElement::e_AttributeTypeBlockAlign @endlink, 
     *       and @link LRStructureElement::e_AttributeTypeRubyAlign @endlink.
     */
    e_AttributeValueEnumJustify = 0x4a535459,
    /**
     * @brief Enum value: Middle, which means children are centered within the table cell.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeBlockAlign @endlink.
     */
    e_AttributeValueEnumMiddle = 0x4d49444c,
    /**
     * @brief Enum value: Underline, which means a line below the text.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeTextDecorationType @endlink.
     */
    e_AttributeValueEnumUnderline = 0x55444c4e,
    /**
     * @brief Enum value: Overline, which means a line above the text.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeTextDecorationType @endlink.
     */
    e_AttributeValueEnumOverline = 0x4f564c4e,
    /**
     * @brief Enum value: LineThrough, which means a line through the middle of the text.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeTextDecorationType @endlink.
     */
    e_AttributeValueEnumLineThrough = 0x4c4e5448,
    /**
     * @brief Enum value: Distribute, which means the content is to be expanded to fill the available width
     *        in the inline-progression direction.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeRubyAlign @endlink.
     */
    e_AttributeValueEnumDistribute = 0x44535442,
    /**
     * @brief Enum value: Disc, which means solid circular bullet.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeListNumbering @endlink.
     */
    e_AttributeValueEnumDisc = 0x44495343,
    /**
     * @brief Enum value: Circle, which means open circular bullet.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeListNumbering @endlink.
     */
    e_AttributeValueEnumCircle = 0x4352434c,
    /**
     * @brief Enum value: Square, which means solid square bullet.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeListNumbering @endlink.
     */
    e_AttributeValueEnumSquare = 0x53515552,
    /**
     * @brief Enum value: Decimal, which means decimal arabic numerals (1-9, 10-99, ...).
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeListNumbering @endlink.
     */
    e_AttributeValueEnumDecimal = 0x44434d4c,
    /**
     * @brief Enum value: UpperRoman, which means uppercase roman numerals (I, II, III, IV, ...).
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeListNumbering @endlink.
     */
    e_AttributeValueEnumUpperRoman = 0x5550524d,
    /**
     * @brief Enum value: LowerRoman, which means lowercase roman numerals (i, ii, iii, iv, ...).
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeListNumbering @endlink.
     */
    e_AttributeValueEnumLowerRoman = 0x4c57524d,
    /**
     * @brief Enum value: UpperAlpha, which means uppercase letters (A, B, C, ...).
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeListNumbering @endlink.
     */
    e_AttributeValueEnumUpperAlpha = 0x5550414c,
    /**
     * @brief Enum value: LowerAlpha, which means lowercase letters (a, b, c, ...).
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeListNumbering @endlink.
     */
    e_AttributeValueEnumLowerAlpha = 0x4c57414c,
    /**
     * @brief Enum value: Unordered (PDF 2.0), which means unordered list with unspecified bullets.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeListNumbering @endlink.
     */
    e_AttributeValueEnumUnordered = 0x554e4f52,
    /**
     * @brief Enum value: Ordered (PDF 2.0), which means ordered lists with unspecified numbering.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeListNumbering @endlink.
     */
    e_AttributeValueEnumOrdered = 0x4f524445,
    /** @brief Enum value: float. */
    e_AttributeValueEnumFloat = 0x464c4f54,
    /**
     * @brief Enum value: rb, which means radio button.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeFieldRole @endlink.
     */
    e_AttributeValueEnumRB = 0x52420000,
    /**
     * @brief Enum value: cb, which means check box.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeFieldRole @endlink.
     */
    e_AttributeValueEnumCB = 0x43420000,
    /**
     * @brief Enum value: pb, which means push button.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeFieldRole @endlink.
     */
    e_AttributeValueEnumPB = 0x50440000,
    /**
     * @brief Enum value: tv, which means text-value field.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeFieldRole @endlink.
     */
    e_AttributeValueEnumTV = 0x54560000,
    /**
     * @brief Enum value: on, which means the state is on.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeFieldChecked @endlink.
     */
    e_AttributeValueEnumOn = 0x4f4e0000,
    /**
     * @brief Enum value: off, which means the state is off.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeFieldChecked @endlink.
     */
    e_AttributeValueEnumOff = 0x4f464600,
    /**
     * @brief Enum value: neutral, which means the state is neutral.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeFieldChecked @endlink.
     */
    e_AttributeValueEnumNeutral = 0x4e555452,
    /**
     * @brief Enum value: Row, which means row of a table.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeTableHeaderScope @endlink.
     */
    e_AttributeValueEnumRow = 0x524f5700,
    /**
     * @brief Enum value: Row, which means column of a table.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeTableHeaderScope @endlink.
     */
    e_AttributeValueEnumColumn = 0x434c4d4e,
    /**
     * @brief Enum value: Row, which means both row and column of a table.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeTableHeaderScope @endlink.
     */
    e_AttributeValueEnumBoth = 0x424f5448,
    /**
     * @brief Enum value: Left, which means left edge of the page.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeAttached @endlink.
     */
    e_AttributeValueEnumLeft = 0x4c454654,
    /**
     * @brief Enum value: Top, which means top edge of the page.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeAttached @endlink.
     */
    e_AttributeValueEnumTop = 0x544f5000,
    /**
     * @brief Enum value: Bottom, which means bottom edge of the page.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeAttached @endlink.
     */
    e_AttributeValueEnumBottom = 0x42544f4d,
    /**
     * @brief Enum value: Right, which means right edge of the page.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeAttached @endlink.
     */
    e_AttributeValueEnumRight = 0x52474854,
    /**
     * @brief Enum value: Pagination, which means pagination artifacts. Ancillary page features
     *        such as running heads and folios (page numbers).
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeSubType @endlink.
     */
    e_AttributeValueEnumPagination = 0x5041474e,
    /**
     * @brief Enum value: Layout, which means layout artifacts. Purely cosmetic typographical or
     *        design elements such as footnote rules or background screens.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeSubType @endlink.
     */
    e_AttributeValueEnumLayout = 0x4c41594f,
    /**
     * @brief Enum value: Page, which means page artifacts. Production aids extraneous to
     *        the document itself, such as cut marks and color bars.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeSubType @endlink.
     */
    e_AttributeValueEnumPage = 0x50414745,
    /**
     * @brief Enum value: Background, which means background artifacts. Background artifacts 
     *        typically serve as a background for content shown either on top of or
     *        placed adjacent to that background.
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeSubType @endlink.
     */
    e_AttributeValueEnumBackground = 0x424b474e,
    /** @brief Enum value: Header. */
    e_AttributeValueEnumHeader = 0x48454144,
    /** @brief Enum value: Footer. */
    e_AttributeValueEnumFooter = 0x464f4f54,
    /** @brief Enum value: Watermark. */
    e_AttributeValueEnumWatermark = 0x57544d4b,
    /** @brief Enum value: PageNum (PDF2.0). */
    e_AttributeValueEnumPageNum = 0x504e554d,
    /** @brief Enum value: Bates (PDF2.0). */
    e_AttributeValueEnumBates = 0x42415445,
    /**
     * @brief Enum value: Other (PDF 2.0).
     *
     * @note This can be used with attribute type @link LRStructureElement::e_AttributeTypeDirection @endlink.
     */
    e_AttributeValueEnumOther = 0x4f544845
  } AttributeValueEnum;
  
  /**
   * @brief Enumeration for value type of element general layout attribute.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _AttributeValueType {
    /** @brief Empty value type. */
    e_AttributeValueTypeEmpty = 0x0,
    /** @brief Value type: enum. */
    e_AttributeValueTypeEnum = 0x1,
    /** @brief Value type: 32-bit signed integer. */
    e_AttributeValueTypeInt32 = 0x2,
    /** @brief Value type: float. */
    e_AttributeValueTypeFloat = 0x3,
    /** @brief Value type: ARGB color type, 32 bits, ((b) | ((g) << 8) | ((r) << 16)) | ((a) << 24). */
    e_AttributeValueTypeARGB = 0x4,
    /** @brief Value type: wide string. */
    e_AttributeValueTypeWStr = 0x5,
    /** @brief Value type: element. */
    e_AttributeValueTypeElement = 0x6,
    /** @brief Value type: an array of enum values. */
    e_AttributeValueTypeEnumArray = 0x101,
    /** @brief Value type: an array of integer values. */
    e_AttributeValueTypeInt32Array = 0x102,
    /** @brief Value type: an array of float values. */
    e_AttributeValueTypeFloatArray = 0x103,
    /** @brief Value type: an array of ARGB values. */
    e_AttributeValueTypeARGBArray = 0x104,
    /** @brief Value type: an array of wide strings. */
    e_AttributeValueTypeWStrArray = 0x105,
    /** @brief Value type: an array of elements. */
    e_AttributeValueTypeElementArray = 0x106
  } AttributeValueType;
  

  /** @brief Constructor. */
  LRStructureElement() {}

  /**
   * @brief Constructor, with another structure element object.
   *
   * @param[in] other  Another structure element object.
   */
  LRStructureElement(const LRStructureElement& other);

  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] element  Parent class object.
   */
  LRStructureElement(const LRElement& element);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit LRStructureElement(FS_HANDLE handle);

  /** @brief Destructor. */
  ~LRStructureElement() {}

  /**
   * @brief Convert the enum value of a specified attribute type to a short and memorable string (text) representation.
   *
   * @param[in] type  Enum value of a specified attribute type. Please refer to values starting from @link LRStructureElement::e_AttributeTypeInvalid @endlink
   *                  and this should be one of these values.
   *
   * @return A string that represents the short and memorable string representation for specified type.
   *         If there is no short and memorable string representation, or input type is @link LRStructureElement::e_AttributeTypeInvalid @endlink
   *         or an invalid enum value, this function would return an empty string.
   */
  static String StringifyAttributeType(AttributeType type);

  /**
   * @brief Parse a string representation for attribute type and retrieve the enum value for this attribute type.
   *
   * @param[in] type_string  A string representation for a structure element attribute type.
   *
   * @return Enum value for attribute type. Please refer to values starting from @link LRStructureElement::e_AttributeTypeInvalid @endlink
   *         and this would be one of these values.
   */
  static AttributeType ParseAttributeType(String type_string);

  /**
   * @brief Convert the enum value of a specified attribute value enum to a short and memorable string (text) representation.
   *
   * @param[in] type  Enum value of a specified attribute value enum. Please refer to values starting from
   *                  @link LRStructureElement::e_AttributeValueEnumInvalid @endlink and this should be one of these values.
   *
   * @return A string that represents the short and memorable string representation for specified enum.
   *         If there is no short and memorable string representation, or input enum value is @link LRStructureElement::e_AttributeValueEnumInvalid @endlink
   *         or an invalid enum value, this function would return an empty string.
   */
  static String StringifyEnumVariant(AttributeValueEnum type);

  /**
   * @brief Check whether input attribute value type represents an array.
   *
   * @param[in] type  Attribute value type. Please refer to values starting from @link LRStructureElement::e_AttributeValueTypeEmpty @endlink
   *                  and this should be one of these values.
   *
   * @return <b>true</b> means input type represents an array, while <b>false</b> means input type does not represent an array.
   */
  static bool IsArrayAttributeValueType(AttributeValueType type);

  /**
   * @brief Get supported attribute count.
   *
   * @return Count of supported attribute.
   */
  int GetSupportedAttributeCount();

  /**
   * @brief Get a supported attribute type by index.
   *
   * @param[in] index  Index for a supported attribute whose type is to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link LRStructureElement::GetSupportedAttributeCount @endlink.
   *
   * @return Attribute type of the attribute specified by index.
   */
  AttributeType GetSupportedAttribute(int index);

  /**
   * @brief Get value count of a specified attribute type.
   *
   * @details <ul>
   *          <li>When the value type of an attribute type represents an array, this function returns the size of the array.</li>
   *          <li>When the value type of an attribute type does not represent an array, this function will alway return 1.</li>
   *          </ul>
   *
   * @param[in] type  Attribute type. Please refer to values starting from @link LRStructureElement::e_AttributeTypeRole @endlink
   *                  and this should be one of these values.
   *
   * @return Value count of a specified attribute type.
   */
  int GetAttributeValueCount(AttributeType type);

  /**
   * @brief Get attribute value type for a specified attribute type.
   *
   * @param[in] type  Attribute type. Please refer to values starting from @link LRStructureElement::e_AttributeTypeRole @endlink
   *                  and this should be one of these values.
   *
   * @return Value type for the specified attribute type. Please refer to values starting from @link LRStructureElement::e_AttributeValueTypeEmpty @endlink
   *         and this would be one of these values.
   */
  AttributeValueType GetAttributeValueType(AttributeType type);

  /**
   * @brief Get an enum value (specified by index) for specified attribute type.
   *
   * @details This function is available for attributes whose value type is @link LRStructureElement::e_AttributeValueTypeEnum @endlink or
   *          @link LRStructureElement::e_AttributeValueTypeEnumArray @endlink. For other value type, this function will return
   *          @link LRStructureElement::e_AttributeValueEnumInvalid @endlink.
   *
   * @param[in] type   Attribute type. Please refer to values starting from @link LRStructureElement::e_AttributeTypeRole @endlink
   *                   and this should be one of these values.
   * @param[in] index  Index to specify which value will be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link LRStructureElement::GetAttributeValueCount @endlink.
   *
   * @return An enum value. Please refer to values starting from @link LRStructureElement::e_AttributeValueEnumInvalid @endlink
   *         and this would be one of these values.
   */
  AttributeValueEnum GetAttributeValueEnum(AttributeType type, int index);

  /**
   * @brief Get an integer value (specified by index) for specified attribute type.
   *
   * @details This function is available for attributes whose value type is @link LRStructureElement::e_AttributeValueTypeInt32 @endlink or
   *          @link LRStructureElement::e_AttributeValueTypeInt32Array @endlink. For other value type, this function will return 0.
   *
   * @param[in] type   Attribute type. Please refer to values starting from @link LRStructureElement::e_AttributeTypeRole @endlink
   *                   and this should be one of these values.
   * @param[in] index  Index to specify which value will be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link LRStructureElement::GetAttributeValueCount @endlink.
   *
   * @return Integer value.
   */
  int32 GetAttributeValueInt32(AttributeType type, int index);

  /**
   * @brief Get a float value (specified by index) for specified attribute type.
   *
   * @details This function is available for attributes whose value type is @link LRStructureElement::e_AttributeValueTypeFloat @endlink or
   *          @link LRStructureElement::e_AttributeValueTypeFloatArray @endlink. For other value type, this function will return 0.0.
   *
   * @param[in] type   Attribute type. Please refer to values starting from @link LRStructureElement::e_AttributeTypeRole @endlink
   *                   and this should be one of these values.
   * @param[in] index  Index to specify which value will be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link LRStructureElement::GetAttributeValueCount @endlink.
   *
   * @return Float value.
   */
  float GetAttributeValueFloat(AttributeType type, int index);

  /**
   * @brief Get an ARGB value (specified by index) for specified attribute type.
   *
   * @details This function is available for attributes whose value type is @link LRStructureElement::e_AttributeValueTypeARGB @endlink or
   *          @link LRStructureElement::e_AttributeValueTypeARGBArray @endlink. For other value type, this function will return 0.
   *
   * @param[in] type   Attribute type. Please refer to values starting from @link LRStructureElement::e_AttributeTypeRole @endlink
   *                   and this should be one of these values.
   * @param[in] index  Index to specify which value will be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link LRStructureElement::GetAttributeValueCount @endlink.
   *
   * @return ARGB value.
   */
  ARGB GetAttributeValueARGB(AttributeType type, int index);

  /**
   * @brief Get a string value (specified by index) for specified attribute type.
   *
   * @details This function is available for attributes whose value type is @link LRStructureElement::e_AttributeValueTypeWStr @endlink or
   *          @link LRStructureElement::e_AttributeValueTypeWStrArray @endlink. For other value type, this function will return an empty string.
   *
   * @param[in] type   Attribute type. Please refer to values starting from @link LRStructureElement::e_AttributeTypeRole @endlink
   *                   and this should be one of these values.
   * @param[in] index  Index to specify which value will be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link LRStructureElement::GetAttributeValueCount @endlink.
   *
   * @return Wide string value.
   */
  WString GetAttributeValueString(AttributeType type, int index);

  /**
   * @brief Get an structure element object (specified by index) for specified attribute type.
   *
   * @details This function is available for attributes whose value type is @link LRStructureElement::e_AttributeValueTypeElement @endlink or
   *          @link LRStructureElement::e_AttributeValueTypeElementArray @endlink. For other value type, this function will return a structure element
   *          whose function @link LRStructureElement::IsEmpty @endlink returns <b>true</b>.
   *
   * @param[in] type   Attribute type. Please refer to values starting from @link LRStructureElement::e_AttributeTypeRole @endlink
   *                   and this should be one of these values.
   * @param[in] index  Index to specify which value will be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link LRStructureElement::GetAttributeValueCount @endlink.
   *
   * @return A structure element.
   */
  LRStructureElement GetAttributeValueElement(AttributeType type, int index);

  /**
   * @brief Get the parent element.
   *
   * @return Parent element. If function @link LRStructureElement::IsEmpty @endlink for the returned object returns <b>true</b>,
   *         that means current element does not have a parent element.
   */
  LRStructureElement GetParentElement() const;

  /**
   * @brief Get the count of children elements.
   *
   * @return Count of children elements.
   */
  int GetChildCount();

  /**
   * @brief Get a child element by index.
   *
   * @param[in] index  Index of a child element to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link LRStructureElement::GetChildCount @endlink.
   *
   * @return A child element.
   */
  LRElement GetChild(int index);

  /**
   * @brief Get bounding box.
   *
   * @return Bounding box.
   */
  RectF GetBBox() const;
};

/**
 * This class represents a graphics object element. Graphics object element can be used to get related the graphics object.
 */
class LRGraphicsObjectElement FS_FINAL : public LRElement {
 public:
  /** @brief Constructor. */
  LRGraphicsObjectElement() {}

  /**
   * @brief Constructor, with another graphics object element object.
   *
   * @param[in] other  Another graphics object element object.
   */
  LRGraphicsObjectElement(const LRGraphicsObjectElement& other);

  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] element  Parent class object.
   */
  LRGraphicsObjectElement(const LRElement& element);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit LRGraphicsObjectElement(FS_HANDLE handle);

  /** @brief Destructor. */
  ~LRGraphicsObjectElement() {}

  /**
   * @brief Get the parent graphics object element.
   *
   * @return Parent graphics object element. If function @link LRGraphicsObjectElement::IsEmpty @endlink for the returned object returns <b>true</b>,
   *         that means current element does not have a parent graphics object element.
   */
  LRGraphicsObjectElement GetParentGraphicsObjectElement() const;

  /**
   * @brief Get related graphics object.
   *
   * @return Related graphics object. If no graphics object can be retrieved, this function will return <b>NULL</b>.
   */
  pdf::graphics::GraphicsObject* GetGraphicsObject() const;

  /**
   * @brief Get PDF dictionary of related graphics object.
   *
   * @details This function is available when related graphics object is a form XObject type.
   *          For other graphics object type, this function will return <b>NULL</b>.
   *
   * @return PDF dictionary of related graphics object.
   */
  pdf::objects::PDFDictionary* GetDict() const;
  
  /**
   * @brief Get index of related graphics object.
   *
   * @return Index of graphics object.
   */
  int GetGraphicsObjectIndex() const;
  
  /**
   * @brief Get bounding box.
   *
   * @return Bounding box.
   */
  RectF GetBBox() const;

  /**
   * @brief Get matrix.
   *
   * @return The matrix.
   */
  Matrix GetMatrix() const;
};

/**
 * This class represents a content element. A content element contains the content from the graphics object.
 */
class LRContentElement FS_FINAL : public LRElement {
 public:
  /** @brief Constructor. */
  LRContentElement() {}

  /**
   * @brief Constructor, with another content element object.
   *
   * @param[in] other  Another content element object.
   */
  LRContentElement(const LRContentElement& other);

  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] element  Parent class object.
   */
  LRContentElement(const LRElement& element);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit LRContentElement(FS_HANDLE handle);

  /** @brief Destructor. */
  ~LRContentElement() {}

  /**
   * @brief Get the parent element.
   *
   * @return Parent element. If function @link LRStructureElement::IsEmpty @endlink for the returned object returns <b>true</b>,
   *         that means current element does not have a parent element.
   */
  LRStructureElement GetParentElement() const;

  /**
   * @brief Get the related graphics object element.
   *
   * @return Related graphics object element. If function @link LRGraphicsObjectElement::IsEmpty @endlink
   *         for the returned object returns <b>true</b>, that means current element does not have a parent element.
   */
  LRGraphicsObjectElement GetGraphicsObjectElement() const;

  /**
   * @brief Get the range of current content element in current graphics object.
   *
   * @details All the indexes specified in the range represents current content element in the graphics object position.
   *
   * @return A range object.
   */
  common::Range GetGraphicsObjectRange();

  /**
   * @brief Get bounding box.
   *
   * @return Bounding box.
   */
  RectF GetBBox() const;

  /**
   * @brief Get matrix.
   *
   * @return Matrix.
   */
  Matrix GetMatrix() const;
};

/**
 *  This class can be used to parse layout recognition to get the root element.
 */
class LRContext FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, from a PDF Page object.
   *
   * @param[in] page  A valid PDF page object.
   * @note If module "LayoutRecognition" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using layoutrecognition related functions and
   *       this constructor will throw exception @link foxit::e_ErrNoLayoutRecognitionModuleRight @endlink.
   */
  LRContext(const pdf::PDFPage& page);

  /**
   * @brief Constructor, with another context object.
   *
   * @param[in] other  Another context object.
   */
  LRContext(const LRContext& other);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit LRContext(FS_HANDLE handle);

  /** @brief Destructor. */
  ~LRContext();

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another context object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  LRContext& operator=(const LRContext& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another context object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator==(const LRContext& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another context object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator!=(const LRContext& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;
  
  /**
   * @brief Start to parse layout recognition for related PDF page.
   *
   * @details It may take a long time to do parsing, so Foxit PDF SDK uses a progressive process to do this.
   *          If there is any error occurs in parsing progress, this function will throw exception.
   *          Please refer to class @link foxit::Exception @endlink and values starting from @link foxit::e_ErrFile @endlink.
   * 
   * @param[in] pause  Pause callback object which decides if the parsing process needs to be paused.
   *                   This can be <b>NULL</b> which means not to pause during the parsing process.
   *                   If this is not <b>NULL</b>, it should be a valid pause object implemented by user.
   *                   Default value: <b>NULL</b>.
   *
   * @return A progressive object. Please check the rate of current progress by function
   *         @link common::Progressive::GetRateOfProgress @endlink. If the rate is not 100 yet, call function
   *         @link common::Progressive::Continue @endlink to continue the progress until the progress is finished.
   */
  common::Progressive StartParse(common::PauseCallback* pause = NULL);

  /**
   * @brief Get the root element of structure tree.
   *
   * @details Please ensure current context object has been parsed successfully before calling this function;
   *          otherwise, no valid root structure element can be retrieved.
   *
   * @return Root element.
   */
  LRStructureElement GetRootElement();
};
}  // namespace layoutrecognition
}  // namespace addon
}  // namespace foxit
#endif  // FS_LAYOUTRECOGNITION_H_

