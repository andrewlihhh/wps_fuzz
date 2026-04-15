#ifndef FS_TABLEGENERATOR_H_
#define FS_TABLEGENERATOR_H_

#include "common/fs_common.h"
#include "pdf/fs_pdfdoc.h"
#include "pdf/fs_pdfpage.h"
#ifndef __EMSCRIPTEN_RENDER__
#include "pdf/annots/fs_annot.h"
#endif

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
 * @brief Table generator namespace.
 */
namespace tablegenerator {
/** This class represents table border information. */
class TableBorderInfo FS_FINAL : public Object{
 public:
  /**
   * @brief Enumeration for PDF annotation type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _TableBorderStyle {
    /** @brief Table border style: Solid.*/
    e_TableBorderStyleSolid      = 0,
    /** @brief Table border style: Dashed.*/
    e_TableBorderStyleDashed = 1
  } TableBorderStyle;
  

  /** @brief Constructor. */
  TableBorderInfo()
      : table_border_style(e_TableBorderStyleSolid)
      , line_width(0.0f)
      , color(0xff000000)
      , dash_phase(0.0f)
      , dashes(FloatArray()) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] table_border_style    Table border style. Please refer to values starting from @link TableBorderInfo::e_TableBorderStyleSolid @endlink and
   *                                  this should be one of these values.
   * @param[in] line_width            Table border line width, in points. This should be a non-negative value.
   *                                  If this value is 0, no border is drawn.
   * @param[in] color                 The table border color. Format: 0xAARRGGBB.
   * @param[in] dash_phase            Dash phase. Only useful when parameter <i>style</i> is
   *                                  @link TableBorderInfo::e_TableBorderStyleDashed @endlink.
   * @param[in] dashes                A dash array that represents the dash patterns. The value of each element in this array
   *                                  should not be negative. Only useful when <i>style</i> is @link TableBorderInfo::e_TableBorderStyleDashed @endlink.
   */
  TableBorderInfo(const TableBorderStyle& table_border_style, float line_width, ARGB color, float dash_phase, FloatArray dashes)
    :table_border_style(table_border_style)
    ,line_width(line_width) 
    ,color(color)
    ,dash_phase(dash_phase)
    ,dashes(dashes) {}

  /**
   * @brief Constructor, with another table border information object.
   *
   * @param[in] table_border_info  Another table border information object.
   */
  TableBorderInfo(const TableBorderInfo& table_border_info)
    : table_border_style(table_border_info.table_border_style)
    , line_width(table_border_info.line_width)
    , color(table_border_info.color)
    , dash_phase(table_border_info.dash_phase)
    , dashes(table_border_info.dashes) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another table border information object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TableBorderInfo &operator = (const TableBorderInfo& data) {
    table_border_style = data.table_border_style;
    line_width = data.line_width;
    color = data.color;
    dash_phase = data.dash_phase;
    dashes = data.dashes;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] table_border_info  Another table border information object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const TableBorderInfo& table_border_info) const {
    if (dashes.GetSize() != table_border_info.dashes.GetSize()) return false;
    for (int i = 0; i < dashes.GetSize(); i++)
      if (dashes.GetAt(i) != table_border_info.dashes.GetAt(i)) return false;

    return (table_border_style == table_border_info.table_border_style &&
            fabs(line_width- table_border_info.line_width) <= FLT_EPSILON &&
            color == table_border_info.color &&
            dash_phase == table_border_info.dash_phase);
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] data  Another table border information object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const TableBorderInfo& data) const  {
    return !((*this) == data);
  }

  /**
   * @brief Set value.
   *
   * @param[in] table_border_style    Table border style. Please refer to values starting from @link TableBorderInfo::e_TableBorderStyleSolid @endlink and
   *                                  this should be one of these values.
   * @param[in] line_width            Table border line width, in points. This should be a non-negative value.
   *                                  If this value is 0, no border is drawn.
   * @param[in] color                 The table border color. Format: 0xAARRGGBB.
   * @param[in] dash_phase            Dash phase. Only useful when parameter <i>style</i> is
   *                                  @link TableBorderInfo::e_TableBorderStyleDashed @endlink.
   * @param[in] dashes                A dash array that represents the dash patterns. The value of each element in this array
   *                                  should not be negative. Only useful when <i>style</i> is @link TableBorderInfo::e_TableBorderStyleDashed @endlink.
   *
   * @return None.
   */
  void Set(const TableBorderStyle& table_border_style, float line_width, ARGB color, float dash_phase, FloatArray dashes) {
    this->table_border_style = table_border_style;
    this->line_width = line_width;
    this->color = color;
    this->dash_phase = dash_phase;
    this->dashes = dashes;
  }

  /**
   * @brief Table border style. Please refer to values starting from @link TableBorderInfo::e_TableBorderStyleSolid @endlink and
   *        this should be one of these values.
   */
  TableBorderStyle table_border_style;

  /**
   * @brief Table border line width, in points. This should be a non-negative value.
   *        If this value is 0, no border is drawn.
   */
  float line_width;

  /** @brief The table border color. Format: 0xAARRGGBB. */
  ARGB color;

  /**
   * @brief Dash phase.It should not be negative. Only useful when parameter <i>style</ i> is @link TableBorderInfo::e_TableBorderStyleDashed @endlink.
   *        Please refer to <PDF Reference 1.7> P211 "dash pattern" for more details. 
   */
  float dash_phase;

  /**
   * @brief A dash array that represents the dash patterns. The value of each element in this array
   *        should not be negative. Only useful when <i>style</i> is @link TableBorderInfo::e_TableBorderStyleDashed @endlink.
   *        Please refer to <PDF Reference 1.7> P211 "dash pattern" for more details. 
   */
  FloatArray dashes;
};

class TableCellData;
/** @brief This class represents an array of @link TableCellData @endlink objects,inserted in the order of the displayed table from left to right.*/
FSDK_DEFINE_ARRAY(TableCellDataColArray, TableCellData)
/** This class represents an array of @link TableCellDataColArray @endlink objects,inserted in the order of the displayed table from top to bottom. */
FSDK_DEFINE_ARRAY(TableCellDataArray, TableCellDataColArray)

/** This class represents table cell data. */
class TableCellData  FS_FINAL : public Object{
 public:
  /** @brief Constructor. */
  TableCellData()
    : cell_text_style(foxit::pdf::RichTextStyle())
    , cell_fill_color(0xFFFFFFFF)
    , cell_text(L"")
    , cell_margin(RectF()) {}

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] cell_text_style  The style of cell text.
   * @param[in] cell_fill_color  The fill color of cell. Format: 0xAARRGGBB.
   * @param[in] cell_text        The text content of cell.
   * @param[in] cell_image       The image content of cell.
   * @param[in] cell_margin      The cell margin.
   */
  TableCellData(const foxit::pdf::RichTextStyle& cell_text_style, const ARGB cell_fill_color, const WString& cell_text, const foxit::common::Image& cell_image, const RectF& cell_margin)
    :cell_text_style(cell_text_style)
    ,cell_fill_color(cell_fill_color)
    ,cell_text(cell_text)
    ,cell_image(cell_image)
    ,cell_margin(cell_margin) {}

  /**
   * @brief Constructor, with another table cell data object.
   *
   * @param[in] data  Another table cell data object, whose value would be assigned to current object.
   */
  TableCellData(const TableCellData& data)
    : cell_text_style(data.cell_text_style)
    , cell_fill_color(data.cell_fill_color)
    , cell_text(data.cell_text)
    , cell_image(data.cell_image)
    , cell_margin(data.cell_margin) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another table cell data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TableCellData &operator = (const TableCellData& data) {
    cell_text_style = data.cell_text_style;
    cell_fill_color = data.cell_fill_color;
    cell_text = data.cell_text;
    cell_image = data.cell_image;
    cell_margin = data.cell_margin;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] data  Another table cell data object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const TableCellData& data) const {
    return (cell_text_style == data.cell_text_style &&
            cell_fill_color == data.cell_fill_color &&
            cell_text == data.cell_text &&
            cell_image == data.cell_image &&
            cell_margin == data.cell_margin);
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] data  Another table cell data object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const TableCellData& data) const  {
    return !((*this) == data);
  }

  /**
   * @brief Set value.
   *
   * @param[in] cell_text_style  The style of cell text.
   * @param[in] cell_fill_color  The fill color of cell. Format: 0xAARRGGBB.
   * @param[in] cell_text        The text content of cell.
   * @param[in] cell_image       The image content of cell.
   * @param[in] cell_margin      The cell margin.
   *
   * @return None.
   */
  void Set(const foxit::pdf::RichTextStyle& cell_text_style, const ARGB cell_fill_color, const WString& cell_text, const foxit::common::Image& cell_image, const RectF& cell_margin) {
    this->cell_text_style = cell_text_style;
    this->cell_fill_color = cell_fill_color;
    this->cell_text = cell_text;
    this->cell_image = cell_image;
    this->cell_margin = cell_margin;
  }

  /** @brief The style of cell text.*/
  foxit::pdf::RichTextStyle cell_text_style;

  /** @brief The fill color of cell. Format: 0xAARRGGBB. */
  ARGB cell_fill_color;

  /**
   * @brief The text content of cell. 
   *
   * @note Currently, it is not supported for text and image to exist in the same cell.
   *                  For merged cells, their contents is text or image which is set in the first merged cell.
   */
  WString cell_text;

  /**
   * @brief The image content of cell.  
   *
   * @note Currently, it is not supported for text and image to exist in the same cell.
   *                  For merged cells, their contents is text or image which is set in the first merged cell.
   */
  foxit::common::Image cell_image;

  /**
   * @brief The cell margin between the content and cell border.
   *
   * @note This value does not represent a rectangle. It just defines the left margin, bottom margin,
   *       right margin and top margin of a table cell. The value should not be negative and should not be bigger than the cell's height or width.
   */
  RectF cell_margin;
};

/** @brief The table cell index.The x means the row index of cell and the y means the column index of cell.*/
typedef CFX_Point TableCellIndex;

/** @brief An array of table cell index.*/
FSDK_DEFINE_ARRAY(TableCellIndexArray, TableCellIndex)

/** This class represents table data. */
class TableData  FS_FINAL : public Object {
 public:
  /** @brief Constructor. */
  TableData() : rect(RectF())
    ,row_count(0)
    ,col_count(0)
    ,outside_border_left(TableBorderInfo())
    ,outside_border_right(TableBorderInfo())
    ,outside_border_top(TableBorderInfo())
    ,outside_border_bottom(TableBorderInfo())
    ,inside_border_row(TableBorderInfo())
    ,inside_border_col(TableBorderInfo()) {
  }

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] rect                   The rectangle of the table which specifies the position in PDF page.
   * @param[in] row_count              The count of rows in the table.
   * @param[in] col_count              The count of columns in the table.
   * @param[in] outside_border_left    The left outside border info.
   * @param[in] outside_border_right   The right outside border info.
   * @param[in] outside_border_top     The top outside border info.
   * @param[in] outside_border_bottom  The bottom outside border info.
   * @param[in] inside_border_row      The row inside border info.
   * @param[in] inside_border_col      The column inside border info.
   * @param[in] merge_cells            The merge cells.
   * @param[in] row_height_array       The row height array. The row height will be set as default value automatically if the member of array is zero. Default: (height of <i>rect</i>)/<i>row_count</i>.
   * @param[in] col_width_array        The column width array. The column width will be set as default value automatically if the member of array is zero. Default: (width of <i>rect</i>)/<i>col_count</i>.
   */
  TableData(RectF rect, int row_count, int col_count, TableBorderInfo outside_border_left,
    TableBorderInfo outside_border_right, TableBorderInfo outside_border_top, TableBorderInfo outside_border_bottom,
    TableBorderInfo inside_border_row, TableBorderInfo inside_border_col, TableCellIndexArray merge_cells, FloatArray row_height_array, FloatArray col_width_array)
    :rect(rect)
    ,row_count(row_count)
    ,col_count(col_count)
    ,outside_border_left(outside_border_left)
    ,outside_border_right(outside_border_right)
    ,outside_border_top(outside_border_top)
    ,outside_border_bottom(outside_border_bottom)
    ,inside_border_row(inside_border_row)
    ,inside_border_col(inside_border_col)
    ,merge_cells(merge_cells)
    ,row_height_array(row_height_array)
    ,col_width_array(col_width_array) {
  }

  /**
   * @brief Constructor, with another table cell data object.
   *
   * @param[in] data  Another table data object, whose value would be assigned to current object.
   */
  TableData(const TableData& data)
    :rect(data.rect)
    ,row_count(data.row_count)
    ,col_count(data.col_count)
    ,outside_border_left(data.outside_border_left)
    ,outside_border_right(data.outside_border_right)
    ,outside_border_top(data.outside_border_top)
    ,outside_border_bottom(data.outside_border_bottom)
    ,inside_border_row(data.inside_border_row)
    ,inside_border_col(data.inside_border_col)
    ,merge_cells(data.merge_cells)
    ,row_height_array(data.row_height_array)
    ,col_width_array(data.col_width_array) {
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] data  Another table data object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const TableData& data) const {
    if (merge_cells.GetSize() != data.merge_cells.GetSize()) return false;
    for (size_t i = 0; i < merge_cells.GetSize(); i++)
      if (merge_cells.GetAt(i) != data.merge_cells.GetAt(i)) return false;
    if (row_height_array.GetSize() != data.row_height_array.GetSize()) return false;
    for (int i = 0; i < row_height_array.GetSize(); i++)
      if (fabs(row_height_array.GetAt(i) - data.row_height_array.GetAt(i)) > FLT_EPSILON)  return false;
    if (col_width_array.GetSize() != data.col_width_array.GetSize()) return false;
    for (int i = 0; i < col_width_array.GetSize(); i++)
      if (fabs(col_width_array.GetAt(i) - data.col_width_array.GetAt(i)) > FLT_EPSILON)  return false;
    return (rect == data.rect &&
            row_count == data.row_count &&
            col_count == data.col_count &&
            outside_border_left == data.outside_border_left && 
            outside_border_right == data.outside_border_right &&
            outside_border_top == data.outside_border_top &&
            outside_border_bottom == data.outside_border_bottom &&
            inside_border_row == data.inside_border_row &&
            inside_border_col == data.inside_border_col);
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] data  Another table data object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const TableData& data) const  {
    return !((*this) == data);
  }

  /**
   * @brief Assign operator.
   *
   * @param[in] data  Another table cell data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  TableData &operator = (const TableData& data) {
    rect = data.rect;
    row_count = data.row_count;
    col_count = data.col_count;
    outside_border_left = data.outside_border_left;
    outside_border_right = data.outside_border_right;
    outside_border_top = data.outside_border_top;
    outside_border_bottom = data.outside_border_bottom;
    inside_border_row = data.inside_border_row;
    inside_border_col = data.inside_border_col;
    merge_cells = data.merge_cells;
    row_height_array = data.row_height_array;
    col_width_array = data.col_width_array;
    return *this;
  }

  /**
   * @brief Set value.
   *
   * @param[in] rect                   The rectangle of the table which specifies the position in PDF page.
   * @param[in] row_count              The count of rows in the table.
   * @param[in] col_count              The count of columns in the table.
   * @param[in] outside_border_left    The left outside border info.
   * @param[in] outside_border_right   The right outside border info.
   * @param[in] outside_border_top     The top outside border info.
   * @param[in] outside_border_bottom  The bottom outside border info.
   * @param[in] inside_border_row      The row inside border info.
   * @param[in] inside_border_col      The column inside border info.
   * @param[in] merge_cells            The merge cells.
   * @param[in] row_height_array       The row height array. The row height will be set as default value automatically if the member of array is zero. Default: (height of <i>rect</i>)/<i>row_count</i>.
   * @param[in] col_width_array        The column width array. The column width will be set as default value automatically if the member of array is zero. Default: (width of <i>rect</i>)/<i>col_count</i>.
   *
   * @return None.
   */
  void Set(RectF rect, int row_count, int col_count, TableBorderInfo outside_border_left,
    TableBorderInfo outside_border_right, TableBorderInfo outside_border_top, TableBorderInfo outside_border_bottom,
    TableBorderInfo inside_border_row, TableBorderInfo inside_border_col, TableCellIndexArray merge_cells, FloatArray row_height_array, FloatArray col_width_array) {
    this->rect = rect;
    this->row_count = row_count;
    this->col_count = col_count;
    this->outside_border_left = outside_border_left;
    this->outside_border_right = outside_border_right;
    this->outside_border_top = outside_border_top;
    this->outside_border_bottom = outside_border_bottom;
    this->inside_border_row = inside_border_row;
    this->inside_border_col = inside_border_col;
    this->merge_cells = merge_cells;
    this->row_height_array = row_height_array;
    this->col_width_array = col_width_array;
  }

  /** 
   * @brief Rectangle of the table which specifies the position in PDF page.
   *        It should be in [PDF coordinate system] (@ref pdf::PDFPage).
   */
  RectF rect;

  /** @brief The count of rows in the table.*/
  int row_count;

  /** @brief The count of columns in the table.*/
  int col_count;

  /** @brief The left outside border info.*/
  TableBorderInfo outside_border_left;

  /** @brief The right outside border info.*/
  TableBorderInfo outside_border_right;

  /** @brief The top outside border info.*/
  TableBorderInfo outside_border_top;

  /** @brief The bottom outside border info.*/
  TableBorderInfo outside_border_bottom;

  /** @brief The row inside border info. */
  TableBorderInfo inside_border_row;

  /** @brief The column inside border info. */
  TableBorderInfo inside_border_col;

  /**
   * @brief The merge cells. The length of this array must be even and the zero length means no merge cell.
   *
   * @note In a merged cell index array, every two consecutive members are grouped into cells. 
   *       The first member represents the starting cell of the merged cell, and the second member represents the ending cell of the merged cell.
   *       For the table cell index, the valid range: from 0 to (<i>row_count</i> - 1) or (<i>col_count</i> - 1).
   */
  TableCellIndexArray merge_cells;

  /** @brief The row height array. The row height will be set as default value automatically if the member of array is zero. Default: (height of <i>rect</i>)/<i>row_count</i>.*/
  FloatArray row_height_array;

  /** @brief The column width array. The column width will be set as default value automatically if the member of array is zero. Default: (width of <i>rect</i>)/<i>col_count</i>.*/
  FloatArray col_width_array;
};

/**
 * This class represents a callback object for generating table.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 */
class TableGeneratorCallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief A callback function to get the top margin of the table to be generated to a new page.
   *
   * @param[in] page_index  The page index. It would start from 0.
   *
   * @return The table top margin to page.
   */
  virtual float GetTableTopMarginToPage(int page_index) = 0;

  /**
   * @brief A callback function to get new page basic information to be generated to a new page.
   *
   * @details This callback function is only used for @link TableGenerator::InsertTablePagesToDocument @endlink.
   *          It will be triggered if the page width or page height is less than or equal to zero.
   *          Users must ensure that the text size is greater than zero in @link pdf::RichTextStyle @endlink if the content of cell is text.
   *
   * @param[in] page_index        The page index. It would start from 0.
   * @param[in] rest_table_height The rest table height(unit is 1/72 inch).
   * @param[in] table_width       The table width(unit is 1/72 inch).
   *
   * @return The basic page information.(The <i>rotation</i> is not supported currently).
   */
  virtual foxit::pdf::PageBasicInfo GetNewPageBasicInfo(int page_index, float rest_table_height, float table_width) = 0;
};

/**
 * This class is used to insert tables to PDF document.
 * Before using any class or methods in this module, please ensure Foxit PDF SDK has been initialized successfully
 * by function @link common::Library::Initialize @endlink with a key including "TableMaker" module.
 *
 * @see @link common::Library @endlink
 */
class TableGenerator FS_FINAL : public Base{
 public:
  /**
   * @brief Add a new table to the PDF page.
   *
   * @param[in] page        A valid PDF page object.
   * @param[in] data        The object of @link TableData @endlink.
   *                        Please make sure that the product of @link TableData::row_count @endlink and @link TableData::col_count @endlink in <i>data</i>
   *                        is the same as the number of <i>cell_array</i>, otherwise an exception will be thrown.
   *                        Please make sure that the @link TableData::rect @endlink in <i>data</i> is not empty and is in the page box of the current page,
   *                        otherwise an exception will be thrown.
   * @param[in] cell_array  This is a two-dimensional array, an array of @link TableCellDataColArray @endlink objects. 
   *                        Exception @link foxit::e_ErrUnsupported @endlink will be thrown if the text and image are in the same cell. 
   * 
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool AddTableToPage(const foxit::pdf::PDFPage& page, const TableData& data, const TableCellDataArray& cell_array);

  /**
   * @brief Insert a new table which is contained in one or multi pages into the document.
   *
   * @param[in] doc                      A valid PDF document object.
   * @param[in] dest_page_index          A dest page index in current PDF document. This is used to specify where
   *                                     the new pages will be inserted. If parameter <i>dest_page_index</i> is less than 0,
   *                                     the new pages will be inserted to the first. <br>
   *                                     If parameter <i>dest_page_index</i> is equal to or larger than current page count,
   *                                     the new pages will be inserted to the end.
   * @param[in] page_width               The new pages width (unit is 1/72 inch).
   * @param[in] page_height              The new pages height (unit is 1/72 inch).
   * @param[in] data                     The object of @link TableData @endlink.
   *                                     Please make sure that the product of @link TableData::row_count @endlink and @link TableData::col_count @endlink in <i>data</i>
   *                                     is the same as the number of <i>cell_array</i>, otherwise an exception will be thrown.
   *                                     Please make sure that the @link TableData::rect @endlink in <i>data</i> is not empty and is in the page box of the current page,
   *                                     otherwise an exception will be thrown.
   * @param[in] cell_array               This is a two-dimensional array, an array of @link TableCellDataColArray @endlink objects. 
   *                                     Exception @link foxit::e_ErrUnsupported @endlink will be thrown if the text and image are in the same cell. 
   * @param[in] allow_to_cross_page      A boolean value spacifies that whether to allow the table to cross page.<b>true</b> means allow, <b>false</b> means not.
   *                                     Currently, cell merging is not supported if parameter <i>allow_to_cross_page</i> is <b>true</b>.
   * @param[in] tablegenerator_callback  The callback for table generator,
   *                                     which is implemented based on callback class @link addon::tablegenerator::TableGeneratorCallback @endlink.
   * 
   * @return <b>true</b> means success, while <b>false</b> means failure.
   */
  static bool InsertTablePagesToDocument(const foxit::pdf::PDFDoc& doc, int dest_page_index, float page_width, float page_height, const TableData& data, const TableCellDataArray& cell_array, bool allow_to_cross_page, TableGeneratorCallback* tablegenerator_callback = NULL);
};
}
}
}
#endif
