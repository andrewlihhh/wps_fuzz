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
 * @file fs_portfolio.h
 * @brief Header file for PDF portfolio related definitions and classes.
 */

#ifndef FS_PORTFOLIO_H_
#define FS_PORTFOLIO_H_

#include "common/fs_common.h"
#include "pdf/fs_pdfdoc.h"
#include "pdf/fs_filespec.h"

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
 * @brief PDF portfolio namespace.
 */
namespace portfolio {
class PortfolioNode;
class PortfolioFolderNode;
class PortfolioFileNode;
class SchemaField;
class Portfolio;

/**
 * Class @link PortfolioNode @endlink is the base class for all types of portfolio nodes.
 */
class PortfolioNode : public Base {
 public:
  /**
   * @brief Enumeration for portfolio node type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _Type {
    /** @brief Unknown portfolio node type. */
    e_TypeUnknown  = 0,
    /** @brief Portfolio node type: folder. */
    e_TypeFolder  = 1,
    /** @brief Portfolio node type: file. */
    e_TypeFile    = 2
  } Type;
  
  /**
   * @brief Constructor, with another portfolio node object.
   *
   * @param[in] other  Another PDF portfolio folder object.
   */
  PortfolioNode(const PortfolioNode& other);
  /** @brief Destructor.*/
  ~PortfolioNode();
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another portfolio node object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  PortfolioNode& operator = (const PortfolioNode& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another portfolio node object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const PortfolioNode& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another portfolio node object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const PortfolioNode& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get node type.
   *
   * @return Node type. Please refer to values starting from @link PortfolioNode::e_TypeFolder @endlink
   *         and this would be one of these values.
   */
  Type GetNodeType() const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PortfolioNode(FS_HANDLE handle = NULL);

};

/** This class represents an array of @link PortfolioNode @endlink objects. */
FSDK_DEFINE_ARRAY(PortfolioNodeArray, PortfolioNode)

class PortfolioFileNode;

/**
 * Portfolio folder node is used as a folder, which can contain file and other folder as sub nodes.<br>
 * Class @link PortfolioFolderNode @endlink is derived from class @link PortfolioNode @endlink.
 * It offers function to access a folder node: add file/folder to folder node, remove sub node from folder node,
 * get all the sub nodes in sorted order, and get/set some properties of folder node.
 */
class PortfolioFolderNode FS_FINAL : public PortfolioNode {
 public:
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] other  Parent class object.
   */
  explicit PortfolioFolderNode(const PortfolioNode& other);

  /** @brief Destructor. */
  ~PortfolioFolderNode() {}

  /**
   * @brief Check if current folder node represents root node.
   *
   * @return <b>true</b> means current folder node is the root node,
   *         while <b>false</b> means current folder node is not the root node.
   */
  bool IsRoot() const;

  /**
   * @brief Get name of current folder node.
   *
   * @return Name of current folder node. If current folder node is the root node, 
   *         usually it does not have a name and an empty string will be return for this case.
   */
  WString GetName() const;

  /**
   * @brief Add a file (specified by file path) to be a sub node.
   *
   * @details Foxit PDF SDK will retrieve some properties (such as file name, modified date and etc.)
   *          from input file path and set them to the file specification object of returned file node.
   *          User can also update properties by functions in class @link FileSpec @endlink for the returned file node.
   *
   * @param[in] file_path  A full path of an existing local file.
   *
   * @return Newly added file node object.
   */
  PortfolioFileNode AddFile(const wchar_t* file_path);
  /**
   * @brief Add a file (specified with @link foxit::common::file::StreamCallback @endlink) to be a sub node.
   *
   * @details Foxit PDF SDK CANNOT retrieve any property from input stream callback.
   *          So user should update properties by functions in class @link FileSpec @endlink for returned file node.
   *
   * @param[in] file_stream  A @link foxit::common::file::StreamCallback @endlink object
   *                         which is implemented by user to read the file content.
   * @param[in] file_name    File name for the file specified by stream callback. This name will
   *                         be used in file specification which is related with the returned file node object.
   *
   * @return Newly added file node object.
   */
  PortfolioFileNode AddFile(foxit::common::file::StreamCallback* file_stream, const wchar_t* file_name);
  /**
   * @brief Add an loaded PDF document to be a sub node.
   *
   * @details Foxit PDF SDK will try to retrieve properties (such as creation date and modified date)
   *          from input PDF document's metadata and set them to the file specification object of returned file node.
   *          User can also update properties by functions in class @link FileSpec @endlink for the returned file node.
   *
   * @param[in] pdf_doc    A valid PDF document object which has been loaded successsfully.
   * @param[in] file_name  File name for the file specified by stream callback. This name will
   *                       be used in file specification which is related with the returned file node object.
   *
   * @return Newly added file node object.
   */
  PortfolioFileNode AddPDFDoc(const PDFDoc& pdf_doc, const wchar_t* file_name);

  /**
   * @brief Add a new sub folder.
   *
   * @param[in] folder_name  Folder name for the new sub folder.
   *
   * @return Newly added folder node object.
   */
  PortfolioFolderNode AddSubFolder(const wchar_t* folder_name);

  /**
   * @brief Remove a sub node.
   *
   * @param[in] sub_node  A node object which represents a sub node of current node to be removed.
   *
   * @return None.
   */
  void RemoveSubNode(const PortfolioNode& sub_node);

  /**
   * @brief Get sub nodes array, which has been sorted according to sorting order and specified field name defined in class @link Portfolio @endlink.
   *
   * @details If the type of values (which are to be compared) is string, Foxit PDF SDK will compare these string values
   *          without taking care of whether a character is a capital or a small letter.
   *
   * @return An array of sorted sub nodes.
   */
  PortfolioNodeArray GetSortedSubNodes() const;

  /**
   * @brief Get the last modified date time.
   *
   * @details If structure of sub nodes is changed (such as add file/folder, remove sub node),
   *          Foxit PDF SDK will update last modified date time of current folder node automatically.
   *
   * @return Last modified date time.
   */
  DateTime GetModifiedDateTime() const;
  /**
   * @brief Get the creation date time.
   *
   * @return Creation date time.
   */
  DateTime GetCreationDateTime() const;

  /**
   * @brief Get description.
   *
   * @return Description string.
   */
  WString GetDescription() const;
  /**
   * @brief Set description.
   *
   * @param[in] description  Description string to be set. This can be an empty string.
   *
   * @return None.
   */
  void SetDescription(const wchar_t* description);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PortfolioFolderNode(FS_HANDLE handle = NULL);

};

/**
 * Portfolio file node is always associated with a file specification which represents an embedded file in portfolio PDF document.<br>
 * Class @link PortfolioFileNode @endlink is derived from class @link PortfolioNode @endlink.
 * It offers function to access related file specification object and the key name for this file specification object.
 */
class PortfolioFileNode FS_FINAL : public PortfolioNode {
 public:
  /**
   * @brief Constructor, with parent class object.
   *
   * @param[in] other  Parent class object.
   */
  explicit PortfolioFileNode(const PortfolioNode& other);

  /** @brief Destructor. */
  ~PortfolioFileNode() {}

  /**
   * @brief Get the related file specification object which is used to access an embedded file information and data.
   *
   * @return A file specification object.
   */
  FileSpec GetFileSpec() const;

  /**
   * @brief Get the key name of the related file specification object.
   *
   * @details Key name is used for storing a file specification. Key name can be used in class @link Attachments @endlink.
   *          Also, key name can be used to specify the initial document in class @link Portfolio @endlink.
   *
   * @return A file specification object.
   */
  WString GetKeyName() const;

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit PortfolioFileNode(FS_HANDLE handle = NULL);

};

/**
 * Schema field can be used to decide which information of a node is to be shown or hide in application.
 */
class SchemaField FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor.
   */
  SchemaField();

  /**
   * @brief Constructor, with another schema field object.
   *
   * @param[in] other  Another PDF portfolio folder object.
   */
  SchemaField(const SchemaField& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another schema field object, whose value would be assigned to current object
   *
   * @return Reference to current object itself.
   */
  SchemaField& operator = (const SchemaField& other); 

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another schema field object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const SchemaField& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another schema field object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const SchemaField& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /** @brief Destructor. */
  ~SchemaField();

  /**
   * @brief Get the key name string.
   *
   * @details Each schema field is stored by a unique key name.
   *          Schema field's key name can be used:
   *          <ul>
   *          <li>as the field name for sorting in class @link Portfolio @endlink.</li>
   *          <li>as the entry's key name in file or folder node's dictionary when schema field's subtype means data type.</li>
   *          </ul>
   *
   * @return Key name string.
   */
  String GetKeyName() const;

  /**
   * @brief Set the key name string.
   *
   * @details Each schema field is stored by a unique key name.
   *          Schema field's key name can be used:
   *          <ul>
   *          <li>as the field name for sorting in class @link Portfolio @endlink.</li>
   *          <li>as the entry's key name in file or folder node's dictionary when schema field's subtype means data type.</li>
   *          </ul>
   *
   * @param[in] key_name  New key name string. This should not be an empty string.
   * 
   * @return None.
   */
  void SetKeyName(const char* key_name);

  /**
   * @brief Get the subtype name string.
   * 
   * @details Subtype name can be used to specify some properties of file node and folder node directly:
   *          <ul>
   *          <li>"F", means the file name of an embedded file or name of a folder node.</li>
   *          <li>"Desc", means the description of an embedded file or descrpition of a folder node.</li>
   *          <li>"ModDate", means the modification date of the embedded file or descrpition of a folder node.</li>
   *          <li>"CreationDate", means the creation date of the embedded file or descrpition of a folder node.</li>
   *          <li>"Size", means the uncompressed size of the embedded file; a folder node does not have size.</li>
   *          <li>"CompressedSize", means the compressed size of the embedded file; a folder node does not have compressed size.</li>
   *          </ul>
   *          For other case, subtype name is used to specified the data type of an specified entry in file or folder node dictionary.
   *          The key for the entry is specified by current schema field's key name. and the data type is specified by:
   *          <ul>
   *          <li>"S", means the field data shall be stored as a PDF text string.</li>
   *          <li>"D", means the field data shall be stored as a PDF date string.</li>
   *          <li>"N", means the field data shall be stored as a PDF number.</li>
   *          </ul>
   *
   * @return Subtype name string.
   */
  String GetSubtypeName() const;
  /**
   * @brief Set the subtype name string.
   * 
   * @details Subtype name can be used to specify some properties of file node and folder node directly:
   *          <ul>
   *          <li>"F", means the file name of an embedded file or name of a folder node.</li>
   *          <li>"Desc", means the description of an embedded file or descrpition of a folder node.</li>
   *          <li>"ModDate", means the modification date of the embedded file or descrpition of a folder node.</li>
   *          <li>"CreationDate", means the creation date of the embedded file or descrpition of a folder node.</li>
   *          <li>"Size", means the uncompressed size of the embedded file; a folder node does not have size.</li>
   *          <li>"CompressedSize", means the compressed size of the embedded file; a folder node does not have compressed size.</li>
   *          </ul>
   *          For other case, subtype name is used to specified the data type of an specified entry in file or folder node dictionary.
   *          The key for the entry is specified by current schema field's key name. and the data type is specified by:
   *          <ul>
   *          <li>"S", means the field data shall be stored as a PDF text string.</li>
   *          <li>"D", means the field data shall be stored as a PDF date string.</li>
   *          <li>"N", means the field data shall be stored as a PDF number.</li>
   *          </ul>
   *
   * @param[in] subtype_name  Subtype name string. This should not be an empty string.
   *                          Please refer to "Details" part for more information.
   *
   * @return None.
   */
  void SetSubtypeName(const char* subtype_name);

  /**
   * @brief Get the display name.
   *
   * @details Display name is used for displaying. This can be different from schema field's key name.
   *
   * @return Display name string.
   */
  WString GetDisplayName() const;
  /**
   * @brief Set the display name.
   *
   * @details Display name is used for displaying. This can be different from schema field's key name.
   *
   * @param[in] display_name  Display name string. This should not be an empty string.
   *
   * @return None.
   */
  void SetDisplayName(const wchar_t* display_name);

  /**
   * @brief Check if current field is initially visible in application or not.
   *
   * @return <b>true</b> means current field is initially visible in application,
   *         while <b>false</b> means current field is initially invisible in application.
   */
  bool IsVisible() const;
  /**
   * @brief Set the initial visibility of current field in application.
   *
   * @param[in] is_visible  <b>true</b> means current field is initially visible in application,
   *                        while <b>false</b> means current field is initially invisible in application.
   *
   * @return None.
   */
  void SetVisibility(bool is_visible);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit SchemaField(FS_HANDLE handle);

};

/** This class represents an array of @link SchemaField @endlink objects. */
FSDK_DEFINE_ARRAY(SchemaFieldArray, SchemaField)

/**
 * PDF portfolio is a combination of files with different formats. PDF portfolio itself is a PDF document,
 * and then files with different formats can be embedded into this kind of PDF document.<br>
 * Class @link Portfolio @endlink can be used to create a new blank PDF portfolio or access an existed portfolio PDF document,
 * and then to get/set portfolio properties and to access root node in order to enumerate all nodes or add/remove node.
 */
class Portfolio FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for initial view mode for a portfolio PDF document.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _InitialViewMode {
    /** @brief Unknown initial view mode. */
    e_InitialViewUnknownMode  = 0,
    /**
     * @brief Initial view mode: details mode, with all information (specified by schema fields)
     *        presented in a multicolumn format.
     * @note This mode provides the most information to the user. */
    e_InitialViewDetailMode  = 1,
    /**
     * @brief Initial view mode: tile mode, with each file and folder node denoted by a small icon and
     *        a subset of information (specified by schema fields).
     * @note This mode provides top-level information about embedded files to the user. */
    e_InitialViewTileMode    = 2,
    /**
     * @brief Initial view mode: hidden mode.
     */
    e_InitialViewHidden    = 3
  } InitialViewMode;
  

  /**
   * @brief Create a PDF portfolio with a new and blank PDF document created automatically.
   *
   * @details This function will create a new and blank PDF document as a portfolio PDF document automatically. 
   *          Function @link Portfolio::GetPortfolioPDFDoc @endlink can be used to retrieve the related PDF document object.
   *          Function @link Portfolio::GetSchemaFields @endlink can be used to retrieve default schema fields.
   *
   * @return A PDF portfolio object.
   */
  static Portfolio CreatePortfolio();

  /**
   * @brief Create a PDF portfolio with an existed portfolio PDF document.
   *
   * @details This function is just to create a PDF portfolio object to be associated with
   *          an existed portfolio PDF document in order to access portfolio information.
   *
   * @param[in] portfolio_pdf_doc  A portfolio PDF document.
   * 
   * @return A PDF portfolio object.
   */
  static Portfolio CreatePortfolio(const foxit::pdf::PDFDoc& portfolio_pdf_doc);

  /**
   * @brief Constructor, with another PDF portfolio object.
   *
   * @param[in] other  Another bookmark object.
   */
  Portfolio(const Portfolio& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another PDF portfolio object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Portfolio& operator = (const Portfolio& other);

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another PDF portfolio object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Portfolio& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another PDF portfolio object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Portfolio& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const; 

  /** @brief Destructor. */
  ~Portfolio();

  /**
   * @brief Get related portfolio PDF document object.
   *
   * @return Related portfolio PDF document object.
   */
  PDFDoc GetPortfolioPDFDoc() const;

  /**
   * @brief Get root node which is always a folder node.
   *
   * @details PDF portfolio organizes files into a hierarchical structure -- a tree with a single root folder (also known as root node)
   *          as the common ancestor for all other folders and files.
   *
   * @return A portfolio node object that represents the root node.
   */
  PortfolioNode GetRootNode() const;

  /**
   * @brief Get initial view mode.
   *
   * @return Initial view mode. Please refer to values starting from @link Portfolio::e_InitialViewUnknownMode @endlink and it would be one of these values.
   */
  InitialViewMode GetInitialViewMode() const;
  /**
   * @brief Set initial view mode.
   *
   * @param[in] mode  Initial view mode. Please refer to values starting from @link Portfolio::e_InitialViewDetailMode @endlink and
   *                  it should be one of these values except @link Portfolio::e_InitialViewUnknownMode @endlink.
   *
   * @return None.
   */
  void SetInitialViewMode(InitialViewMode mode);

  /**
   * @brief Check whether nodes should be sorted in ascending order or not.
   *
   * @return <b>true</b> means nodes should be sorted in ascending order with specified field,
   *         while <b>false</b> means nodes should sorted in descending order with specified field.
   */
  bool IsSortedInAscending() const;
  /**
   * @brief Set the boolean to decide whether nodes should be sorted in ascending order or not.
   *
   * @param[in] use_ascending_order  A boolean to decide the sorted order: 
   *                                 <b>true</b> means nodes should be sorted in ascending order with specified field,
   *                                 while <b>false</b> means nodes should sorted in descending order with specified field.
   *
   * @return None.
   */
  void SetSortingOrder(bool use_ascending_order);
  /**
   * @brief Get the key name of a schema field which is used for sorting.
   *
   * @return Key name of a schema field which is used for sorting.
   */
  String GetSortingFieldKeyName() const;
  /**
   * @brief Set the key name of a schema field for sorting.
   *
   * @param[in] name  Key name of a schema field for sorting.
   *
   * @return None.
   */
  void SetSortingFieldKeyName(const char* name);

  /**
   * @brief Get the key name of an attachment (as file specification) which should be the initial document.
   *
   * @details Class @link Attachments @endlink can be used to retrieve the file specification object by key name.
   * 
   * @return Key name of an attachment(as file specification). If an empty string is returned,
   *         that means the related portfolio PDF document should be the initial document.
   */
  WString GetInitialFileSpecKeyName() const;
  /**
   * @brief Set the key name of an attachment (as file specification) which should be the initial document.
   *
   * @details Function @link PortfolioFileNode::GetKeyName @endlink can be used to get the key name of a file specification associated with a file node.
   *          Or use class @link Attachments @endlink to retrieve a key name of a file specification.
   * 
   * @param[in] name  Key name of an attachment(as file specification). If an empty string is returned,
   *                  that means the related portfolio PDF document should be the initial document.
   *
   * @return None.
   */
  void SetInitialFileSpecKeyName(const wchar_t* name);

  /**
   * @brief Get schema fields.
   *
   * @details Schema fields are used to decide which properties of file node or folder node are to be shown in application.
   *
   * @return Schema fields. Order of these fields are decided by their index order in returned array.
   */
  SchemaFieldArray GetSchemaFields() const;
  /**
   * @brief Set schema fields.
   *
   * @details Schema fields are used to decide which properties of file node or folder node are to be shown in application.<br>
   *          When this function succeeds, all the old schema fields will be removed and input ones will be used instead.
   *
   * @param[in] field_array  New schema fields array. Order of these fields are decided by their index order in this array.
   * 
   * @return None.
   */
  void SetSchemaFields(const SchemaFieldArray& field_array);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Portfolio(FS_HANDLE handle =  NULL);

};

}  // namespace portfolio
}  // namespace pdf
}  // namespace foxit

#endif  // FS_PORTFOLIO_H_

