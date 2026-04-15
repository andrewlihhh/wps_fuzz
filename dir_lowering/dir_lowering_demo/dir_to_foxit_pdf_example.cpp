#include <cerrno>
#include <cmath>
#include <codecvt>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>

#include <nlohmann/json.hpp>

#include "foxit_sdk/include/common/fs_common.h"
#include "foxit_sdk/include/common/fs_image.h"
#include "foxit_sdk/include/pdf/fs_pdfdoc.h"
#include "foxit_sdk/include/pdf/fs_pdfpage.h"
#include "foxit_sdk/include/pdf/graphics/fs_pdfgraphicsobject.h"

using nlohmann::json;

using foxit::ARGB;
using foxit::ErrorCode;
using foxit::Exception;
using foxit::Matrix;
using foxit::POSITION;
using foxit::PointF;
using foxit::RectF;
using foxit::common::Font;
using foxit::common::Image;
using foxit::common::Library;
using foxit::common::Path;
using foxit::pdf::PDFDoc;
using foxit::pdf::PDFPage;
using foxit::pdf::graphics::GraphicsObject;
using foxit::pdf::graphics::ImageObject;
using foxit::pdf::graphics::PathObject;
using foxit::pdf::graphics::TextObject;
using foxit::pdf::graphics::TextState;

namespace {

enum class DirObjectType {
  Text,
  Image,
  Path,
  Table,
};

struct DirColor {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

struct DirPoint {
  float x;
  float y;
};

struct DirTextObject {
  float x;
  float y;
  std::string font_name;
  float font_size;
  DirColor color;
  std::string text;
};

struct DirImageObject {
  float x;
  float y;
  float width;
  float height;
  std::string image_path;
};

struct DirPathObject {
  std::vector<DirPoint> points;
  DirColor stroke_color;
  DirColor fill_color;
  bool stroke;
  bool fill;
  bool closed;
};

struct DirTableObject {
  float x;
  float y;
  float width;
  float height;
  std::string font_name;
  float font_size;
  DirColor text_color;
  DirColor border_color;
  std::vector<std::vector<std::string> > cells;
};

struct DirObject {
  DirObjectType type;
  DirTextObject text;
  DirImageObject image;
  DirPathObject path;
  DirTableObject table;
};

struct DirPage {
  float width;
  float height;
  std::vector<DirObject> objects;
};

struct DirDocument {
  std::string title;
  std::vector<DirPage> pages;
};

class FoxitLibraryGuard {
 public:
  FoxitLibraryGuard() : initialized_(false) {}

  void Initialize(const std::string& sn, const std::string& key) {
    const ErrorCode code = Library::Initialize(sn.c_str(), key.c_str());
    if (code != foxit::e_ErrSuccess) {
      std::ostringstream stream;
      stream << "Foxit Library::Initialize failed with error code " << code;
      throw std::runtime_error(stream.str());
    }
    initialized_ = true;
  }

  ~FoxitLibraryGuard() {
    if (initialized_) {
      Library::Release();
    }
  }

 private:
  bool initialized_;
};

std::string Trim(const std::string& input) {
  const std::string whitespace = " \t\r\n";
  const size_t start = input.find_first_not_of(whitespace);
  if (start == std::string::npos) {
    return "";
  }
  const size_t end = input.find_last_not_of(whitespace);
  return input.substr(start, end - start + 1);
}

std::string ReadKeyValue(const std::string& path, const std::string& prefix) {
  std::ifstream input(path.c_str());
  if (!input) {
    throw std::runtime_error("Failed to open license file: " + path);
  }

  std::string line;
  while (std::getline(input, line)) {
    if (line.rfind(prefix, 0) == 0) {
      return Trim(line.substr(prefix.size()));
    }
  }

  throw std::runtime_error("Missing key '" + prefix + "' in " + path);
}

std::wstring Utf8ToWide(const std::string& input) {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > converter;
  return converter.from_bytes(input);
}

void EnsureDirectory(const std::string& path) {
  if (mkdir(path.c_str(), 0755) == 0 || errno == EEXIST) {
    return;
  }

  throw std::runtime_error("Failed to create directory: " + path + ", errno=" + std::to_string(errno));
}

float ParseColorComponent(const json& value) {
  const double component = value.get<double>();
  if (component <= 1.0) {
    return static_cast<float>(component * 255.0);
  }
  return static_cast<float>(component);
}

DirColor ParseColor(const json& color_json) {
  if (!color_json.is_array() || color_json.size() != 3) {
    throw std::runtime_error("Color must be a 3-element array");
  }

  DirColor color;
  color.red = static_cast<uint8_t>(std::round(ParseColorComponent(color_json[0])));
  color.green = static_cast<uint8_t>(std::round(ParseColorComponent(color_json[1])));
  color.blue = static_cast<uint8_t>(std::round(ParseColorComponent(color_json[2])));
  return color;
}

DirPoint ParsePoint(const json& point_json) {
  if (!point_json.is_array() || point_json.size() != 2) {
    throw std::runtime_error("Point must be a 2-element array");
  }

  DirPoint point;
  point.x = point_json[0].get<float>();
  point.y = point_json[1].get<float>();
  return point;
}

DirTextObject ParseTextObject(const json& object_json) {
  const DirPoint position = ParsePoint(object_json.at("position"));

  DirTextObject text;
  text.x = position.x;
  text.y = position.y;
  text.font_name = object_json.value("font", "Helvetica");
  text.font_size = object_json.value("font_size", 12.0f);
  text.color = ParseColor(object_json.at("color"));
  text.text = object_json.at("data").get<std::string>();
  return text;
}

DirImageObject ParseImageObject(const json& object_json) {
  const DirPoint position = ParsePoint(object_json.at("position"));
  const DirPoint size = ParsePoint(object_json.at("size"));

  DirImageObject image;
  image.x = position.x;
  image.y = position.y;
  image.width = size.x;
  image.height = size.y;
  image.image_path = object_json.at("path").get<std::string>();
  return image;
}

DirPathObject ParsePathObject(const json& object_json) {
  DirPathObject path;
  path.stroke_color = ParseColor(object_json.at("stroke_color"));
  path.fill_color = ParseColor(object_json.at("fill_color"));
  path.stroke = object_json.value("stroke", true);
  path.fill = object_json.value("fill", false);
  path.closed = object_json.value("closed", false);

  const json& points_json = object_json.at("points");
  if (!points_json.is_array() || points_json.empty()) {
    throw std::runtime_error("Path object points must be a non-empty array");
  }

  for (json::const_iterator it = points_json.begin(); it != points_json.end(); ++it) {
    path.points.push_back(ParsePoint(*it));
  }
  return path;
}

DirTableObject ParseTableObject(const json& object_json) {
  const DirPoint position = ParsePoint(object_json.at("position"));
  const DirPoint size = ParsePoint(object_json.at("size"));

  DirTableObject table;
  table.x = position.x;
  table.y = position.y;
  table.width = size.x;
  table.height = size.y;
  table.font_name = object_json.value("font", "Helvetica");
  table.font_size = object_json.value("font_size", 11.0f);
  table.text_color = ParseColor(object_json.at("text_color"));
  table.border_color = ParseColor(object_json.at("border_color"));

  const json& cells_json = object_json.at("cells");
  if (!cells_json.is_array() || cells_json.empty()) {
    throw std::runtime_error("Table cells must be a non-empty 2D array");
  }

  for (json::const_iterator row_it = cells_json.begin(); row_it != cells_json.end(); ++row_it) {
    if (!row_it->is_array() || row_it->empty()) {
      throw std::runtime_error("Each table row must be a non-empty array");
    }

    std::vector<std::string> row;
    for (json::const_iterator cell_it = row_it->begin(); cell_it != row_it->end(); ++cell_it) {
      row.push_back(cell_it->get<std::string>());
    }
    table.cells.push_back(row);
  }

  return table;
}

DirObject ParseObject(const json& object_json) {
  DirObject object;
  const std::string type = object_json.at("type").get<std::string>();

  if (type == "text") {
    object.type = DirObjectType::Text;
    object.text = ParseTextObject(object_json);
    return object;
  }
  if (type == "image") {
    object.type = DirObjectType::Image;
    object.image = ParseImageObject(object_json);
    return object;
  }
  if (type == "path") {
    object.type = DirObjectType::Path;
    object.path = ParsePathObject(object_json);
    return object;
  }
  if (type == "table") {
    object.type = DirObjectType::Table;
    object.table = ParseTableObject(object_json);
    return object;
  }

  throw std::runtime_error("Unsupported DIR object type: " + type);
}

DirDocument ParseDirDocument(const std::string& json_path) {
  std::ifstream input(json_path.c_str());
  if (!input) {
    throw std::runtime_error("Failed to open DIR JSON: " + json_path);
  }

  json document_json;
  input >> document_json;

  DirDocument document;
  document.title = document_json.value("title", "Foxit DIR Lowering Demo");

  const json& pages_json = document_json.at("pages");
  if (!pages_json.is_array() || pages_json.empty()) {
    throw std::runtime_error("DIR document must contain a non-empty pages array");
  }

  for (json::const_iterator page_it = pages_json.begin(); page_it != pages_json.end(); ++page_it) {
    DirPage page;
    page.width = page_it->value("width", 595.0f);
    page.height = page_it->value("height", 842.0f);

    const json& objects_json = page_it->at("objects");
    for (json::const_iterator object_it = objects_json.begin(); object_it != objects_json.end(); ++object_it) {
      page.objects.push_back(ParseObject(*object_it));
    }
    document.pages.push_back(page);
  }

  return document;
}

ARGB ToArgb(const DirColor& color) {
  return 0xFF000000u | (static_cast<ARGB>(color.red) << 16) |
         (static_cast<ARGB>(color.green) << 8) | static_cast<ARGB>(color.blue);
}

Font ResolveFont(const std::string& font_name) {
  if (font_name == "Helvetica") {
    return Font(Font::e_StdIDHelvetica);
  }
  if (font_name == "Helvetica-Bold") {
    return Font(Font::e_StdIDHelveticaB);
  }
  if (font_name == "Times-Roman") {
    return Font(Font::e_StdIDTimes);
  }
  if (font_name == "Times-Bold") {
    return Font(Font::e_StdIDTimesB);
  }
  return Font(Font::e_StdIDHelvetica);
}

float TopLeftYToPdfY(const PDFPage& page, float y, float object_height) {
  return page.GetHeight() - y - object_height;
}

PointF TopLeftPointToPdfPoint(const PDFPage& page, const DirPoint& point) {
  return PointF(point.x, page.GetHeight() - point.y);
}

void AddTextObject(PDFPage& page, const DirTextObject& text) {
  POSITION position = page.GetLastGraphicsObjectPosition(GraphicsObject::e_TypeText);
  TextObject* text_object = TextObject::Create();

  TextState state;
  state.font_size = text.font_size;
  state.font = ResolveFont(text.font_name);
  state.textmode = TextState::e_ModeFill;

  text_object->SetFillColor(ToArgb(text.color));
  text_object->SetTextState(page, state, false, 400);
  text_object->SetText(Utf8ToWide(text.text).c_str());
  page.InsertGraphicsObject(position, text_object);

  const RectF rect = text_object->GetRect();
  const float pdf_x = text.x;
  const float pdf_y = TopLeftYToPdfY(page, text.y, text.font_size);
  text_object->Transform(Matrix(1, 0, 0, 1, pdf_x - rect.left, pdf_y - rect.bottom), false);
}

void AddImageObject(PDFPage& page, const DirImageObject& image) {
  POSITION position = page.GetLastGraphicsObjectPosition(GraphicsObject::e_TypeImage);
  Image source_image(image.image_path.c_str());
  if (source_image.GetWidth() <= 0 || source_image.GetHeight() <= 0) {
    throw std::runtime_error("Failed to load image for DIR object: " + image.image_path);
  }

  ImageObject* image_object = ImageObject::Create(page.GetDocument());
  image_object->SetImage(source_image, 0);
  image_object->SetMatrix(Matrix(image.width, 0, 0, image.height, image.x, TopLeftYToPdfY(page, image.y, image.height)));
  page.InsertGraphicsObject(position, image_object);
}

void AddPathObject(PDFPage& page, const DirPathObject& dir_path) {
  POSITION position = page.GetLastGraphicsObjectPosition(GraphicsObject::e_TypePath);
  Path path_data;

  const PointF first = TopLeftPointToPdfPoint(page, dir_path.points.front());
  path_data.MoveTo(first);
  for (size_t i = 1; i < dir_path.points.size(); ++i) {
    path_data.LineTo(TopLeftPointToPdfPoint(page, dir_path.points[i]));
  }
  if (dir_path.closed) {
    path_data.CloseFigure();
  }

  PathObject* path_object = PathObject::Create();
  path_object->SetPathData(path_data);
  path_object->SetStrokeState(dir_path.stroke);
  path_object->SetStrokeColor(ToArgb(dir_path.stroke_color));
  path_object->SetFillColor(ToArgb(dir_path.fill_color));
  path_object->SetFillMode(dir_path.fill ? foxit::common::e_FillModeWinding : foxit::common::e_FillModeNone);
  page.InsertGraphicsObject(position, path_object);
}

void AddTableObject(PDFPage& page, const DirTableObject& table) {
  const size_t row_count = table.cells.size();
  size_t column_count = 0;
  for (size_t i = 0; i < row_count; ++i) {
    if (table.cells[i].size() > column_count) {
      column_count = table.cells[i].size();
    }
  }
  if (column_count == 0) {
    throw std::runtime_error("Table object must contain at least one column");
  }

  const float column_width = table.width / static_cast<float>(column_count);
  const float row_height = table.height / static_cast<float>(row_count);

  Path grid_path;
  for (size_t row = 0; row < row_count; ++row) {
    for (size_t column = 0; column < column_count; ++column) {
      const float cell_x = table.x + column_width * static_cast<float>(column);
      const float cell_y = table.y + row_height * static_cast<float>(row);
      const float pdf_bottom = TopLeftYToPdfY(page, cell_y, row_height);
      grid_path.AppendRect(RectF(cell_x, pdf_bottom, cell_x + column_width, pdf_bottom + row_height));

      if (column < table.cells[row].size()) {
        DirTextObject cell_text;
        cell_text.x = cell_x + 6.0f;
        cell_text.y = cell_y + 8.0f;
        cell_text.font_name = table.font_name;
        cell_text.font_size = table.font_size;
        cell_text.color = table.text_color;
        cell_text.text = table.cells[row][column];
        AddTextObject(page, cell_text);
      }
    }
  }

  POSITION position = page.GetLastGraphicsObjectPosition(GraphicsObject::e_TypePath);
  PathObject* path_object = PathObject::Create();
  path_object->SetPathData(grid_path);
  path_object->SetStrokeState(true);
  path_object->SetStrokeColor(ToArgb(table.border_color));
  path_object->SetFillMode(foxit::common::e_FillModeNone);
  page.InsertGraphicsObject(position, path_object);
}

void LowerObject(PDFPage& page, const DirObject& object, size_t page_index, size_t object_index) {
  switch (object.type) {
    case DirObjectType::Text:
      std::cout << "[lower] page=" << page_index << " object=" << object_index << " type=text -> TextObject" << std::endl;
      AddTextObject(page, object.text);
      return;
    case DirObjectType::Image:
      std::cout << "[lower] page=" << page_index << " object=" << object_index << " type=image -> ImageObject" << std::endl;
      AddImageObject(page, object.image);
      return;
    case DirObjectType::Path:
      std::cout << "[lower] page=" << page_index << " object=" << object_index << " type=path -> PathObject" << std::endl;
      AddPathObject(page, object.path);
      return;
    case DirObjectType::Table:
      std::cout << "[lower] page=" << page_index << " object=" << object_index << " type=table -> PathObject + TextObject" << std::endl;
      AddTableObject(page, object.table);
      return;
  }

  throw std::runtime_error("Unexpected DIR object type during lowering");
}

void LowerPage(PDFDoc& doc, const DirPage& dir_page, size_t page_index) {
  PDFPage page = doc.InsertPage(doc.GetPageCount(), dir_page.width, dir_page.height);
  for (size_t i = 0; i < dir_page.objects.size(); ++i) {
    LowerObject(page, dir_page.objects[i], page_index, i);
  }
  page.GenerateContent();
}

void LowerDirToPdfWithFoxit(const DirDocument& document, const std::string& output_path) {
  if (document.pages.empty()) {
    throw std::runtime_error("DIR document must contain at least one page");
  }

  PDFDoc doc;
  for (size_t i = 0; i < document.pages.size(); ++i) {
    LowerPage(doc, document.pages[i], i);
  }

  if (!doc.SaveAs(output_path.c_str(), PDFDoc::e_SaveFlagNoOriginal)) {
    throw std::runtime_error("Foxit PDFDoc::SaveAs failed for " + output_path);
  }
}

}  // namespace

int main() {
  try {
    const std::string sn = ReadKeyValue("foxit_sdk/lib/gsdk_sn.txt", "SN=");
    const std::string key = ReadKeyValue("foxit_sdk/lib/gsdk_key.txt", "Sign=");

    FoxitLibraryGuard sdk;
    sdk.Initialize(sn, key);

    EnsureDirectory("output");

    const DirDocument document = ParseDirDocument("foxit_dir_sample.json");
    const std::string output_path = "output/foxit_dir_output.pdf";
    LowerDirToPdfWithFoxit(document, output_path);
    std::cout << "Saved PDF to " << output_path << std::endl;
    return 0;
  } catch (const Exception& exception) {
    std::cerr << "Foxit SDK exception: " << exception.GetMessage() << std::endl;
  } catch (const std::exception& exception) {
    std::cerr << "Error: " << exception.what() << std::endl;
  }

  return 1;
}