// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to convert images to PDF files.

// Include Foxit SDK header files.
#include <time.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

#include "../../../include/common/fs_common.h"
#include "../../../include/common/fs_image.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/pdf/graphics/fs_pdfgraphicsobject.h"
#include "addon/conversion/fs_convert.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace pdf::graphics;
using namespace foxit::addon::conversion;
using namespace common::file;

static const char* sn = "XQSqpYXftiFIcjaUVzEYXWVFvT86aRH+NpxaYmpzjXt+knIjbaBmMQ==";
static const char* key = "8f3g1kNstBkNAgfCSIczuioWaeXe4+c9+glonrwf6b2LMfDWf0CC92cxiF1M4Re6KUqmkA3+M4O1IRQXmfDg2WnFjr6Fy5eBqpmElth3Kch1UnDYqzIPf4PVOEZvUd51NT/a3Rp2dprVjI9p43m4BRUbHi14Ls5WJrbjiVImPsVCUGD4vLwv5KivNUlruYxBJklnVqASv/Ql2eMYs+QjkW2FF561ojrhWBbkZo+foLp7Dks6zaDFn2bjnFO0QQoD20LdUWuJc38kL+k6tcTaieNizW1FzvFVFDY8NWnaPY7k9nth2Ty5DtIdwMs2WuHrWIgd01SI/FkGZnVjdnmHMrGMNaJeiLJi64khor68iqTH+5C+3Eq48zfcsrsA8Qpe3GDEMHA1aDadhOj+wM1jFvjDQNQR4UQrgVEcS8HhoQECjJv3p/n6zpqSUEHwgoWt3MCZaOButo4qsSUf00/oFCrSaKugMwZsIZPzLilaIvyDYEyVUTDeZmnFRCri9Bnylj/uD+N2EPm2YZnsePp/ORv3FIHlNMl6kOQXmZMKsZMGQcCLc8Xxf9nSaiZzYD1jRgcytPBP0ROfN/rG3EI/1lG+ZCnax9oadtpEbEGjUvja70YRE14iVwR8QIRFVpqJVZTCMcmuFpMFfC2CKcYQORBygs+6bnobAli9qIzIoXvbk2gYI5X2WhkZHRwIrOXwk3fW9nFKjCXVpyYSFSdOrkRQdAT5u+6eEIaSD47GmIHoaDDlHH1RF6BusVsCqvfAfG8qIYJNes2q/c5nheCmBThdWjl4MKwxPH7K306MaekAKFPJAwKhBTES9nZrsseQLQ9v8WNGTZyBwJucEHMCol+Vk3lf+PpKEaD6G8TT7n36V43XJ/N09APgDcGxGB4rAAeinCbANyaYOQtZ0jb+5Jb/NKQ2grdA9KoEvafLE09J4VSloQPQOCCbIwhrvwZO0guWaEjXbiN4UPzSOnyQK7lZfFNmAIgjZtAqzIL8yeGes0I/CCI4CiRKz+pFh313WLtbKi3acqO7GrlFH9g652bkeITPg06fhkqSVjf7iHv+ZpZYXWz+K0FiTUaCinPzNKOCWbYrqNcWaM1Y6bR/uoUJkSUMoODHZ3csWhOz7VqUVZc9M4U6Qg0+0wck3w+ZbdEyVSlWnAPXkphg4UYMrMrUFUzHYSjORTdXoLYMveoIbWMhubtugl0DqD8hOEWqaGYYlJo2N2WU54mYEIaoZ8wfpWsMVOfPFyi5j754lngonq5vf36inXn3xRO5CkYFrzXKJ3n2DYiSrVV0ll/5WTkR3F/lEby4CP81UkVubm4GrvH7fBnhQuWgV9GlZbZhaCWl6FC1dnabn+sNwvh3iEP/2oWqi2013gtQQlSSFE5mCg+pCr6zFEAUTNHBqQZrXyMdIJ9tNimbX551HE+bKp5Eog1wHWP1k3orEjQUwm+R";

#if defined(_WIN32) || defined(_WIN64)
static WString output_path = WString::FromLocal("../output_files/");
static WString input_path = WString::FromLocal("../input_files/");
#else
static WString output_path = WString::FromLocal("./output_files/");
static WString input_path = WString::FromLocal("./input_files/");
#endif

class SdkLibMgr {
public:
  SdkLibMgr() : is_initialize_(false){};
  ErrorCode Initialize() {
    ErrorCode error_code = Library::Initialize(sn, key);
    if (error_code != foxit::e_ErrSuccess) {
      printf("Library Initialize Error: %d\n", error_code);
    } else {
      is_initialize_ = true;
    }
    return error_code;

  }
  ~SdkLibMgr(){
    if(is_initialize_)
      Library::Release();
  }
private:
  bool is_initialize_;
};

class FileReader : public ReaderCallback {
public:
  FileReader()
    : m_fileFP(NULL)
    , m_bLargeFile(FALSE) {}

  ~FileReader() {}

  bool LoadFile(const wchar_t* wFilePath, bool bLargeFile = FALSE) {
    std::wstring strTemp(wFilePath);
    CFX_ByteString bytestring = CFX_ByteString::FromUnicode(wFilePath);
    string bstrFilepath = string(bytestring);
#if defined(_WIN32) || defined(_WIN64)
    fopen_s(&m_fileFP, bstrFilepath.c_str(), "rb");
#else
    m_fileFP = fopen(bstrFilepath.c_str(), "rb");
#endif
    if (!m_fileFP)
      return FALSE;
    m_bLargeFile = bLargeFile;
    return TRUE;
  }

  FILESIZE GetSize() {
    if (m_bLargeFile) {
#if defined(_WIN32) || defined(_WIN64)
      _fseeki64(m_fileFP, 0, SEEK_END);
      long long sizeL = _ftelli64(m_fileFP);
#elif defined(__linux__) || defined(__APPLE__)
      fseeko(m_fileFP, 0, SEEK_END);
      long long sizeL = ftello(m_fileFP);
#endif
      return sizeL;
    }
    else {
      fseek(m_fileFP, 0, SEEK_END);
      return (uint32)ftell(m_fileFP);
    }
  }

  FX_BOOL ReadBlock(void* buffer, FILESIZE offset, size_t size) {
    if (m_bLargeFile) {
#if defined(_WIN32) || defined(_WIN64)
      _fseeki64(m_fileFP, offset, SEEK_SET);
#elif defined(__linux__) || defined(__APPLE__)
      fseeko(m_fileFP, offset, SEEK_SET);
#endif
      long long readSize = fread(buffer, 1, size, m_fileFP);
      return (readSize == size);
    }
    else {
      if (!m_fileFP)
        return false;
      if (0 != fseek(m_fileFP, (long)offset, 0))
        return false;
      if (0 == fread(buffer, 1, size, m_fileFP))
        return false;
      return true;
    }
  }

  void Release() {
    if (m_fileFP)
      fclose(m_fileFP);
    m_fileFP = NULL;
    delete this;
  }

private:
  FILE* m_fileFP;
  bool m_bLargeFile;
};

class FileWriter : public WriterCallback {
public:
  FileWriter()
    : m_fileFP(NULL)
    , m_bLargeFile(FALSE) {}

  ~FileWriter() {}

  bool LoadFile(const char* filePath, bool bLargeFile = FALSE) {
#if defined(_WIN32) || defined(_WIN64)
    fopen_s(&m_fileFP, filePath, "wb");
#else
    m_fileFP = fopen(filePath, "wb");
#endif
    if (!m_fileFP)
      return FALSE;
    m_bLargeFile = bLargeFile;
    return TRUE;
  }

  FILESIZE GetSize() {
    if (!m_fileFP)
      return 0;
    if (m_bLargeFile) {
#if defined(_WIN32) || defined(_WIN64)
      _fseeki64(m_fileFP, 0, SEEK_END);
      long long sizeL = _ftelli64(m_fileFP);
#elif defined(__linux__) || defined(__APPLE__)
      fseeko(m_fileFP, 0, SEEK_END);
      long long sizeL = ftello(m_fileFP);
#endif
      return sizeL;
    }
    else {
      fseek(m_fileFP, 0, SEEK_END);
      return (uint32)ftell(m_fileFP);
    }
  }

  FX_BOOL Flush() {
    return fflush(m_fileFP) == 0;
  }

  FX_BOOL WriteBlock(const void* buffer, FILESIZE offset, size_t size) {
    if (!m_fileFP)
      return FALSE;
    if (m_bLargeFile) {
#if defined(_WIN32) || defined(_WIN64)
      _fseeki64(m_fileFP, offset, SEEK_SET);
#elif defined(__linux__) || defined(__APPLE__)
      fseeko(m_fileFP, offset, SEEK_SET);
#endif
      size_t readSize = fwrite(buffer, sizeof(char), size, m_fileFP);
      return (readSize == size);
    }
    else {
      if (!m_fileFP)
        return false;
      int ret1 = fseek(m_fileFP, (long)offset, SEEK_SET);
      uint64 write_size = fwrite(buffer, sizeof(char), size, m_fileFP);
      if (write_size == size) {
        return TRUE;
      }
    }
    return FALSE;
  }

  void Release() {
    if (m_fileFP)
      fclose(m_fileFP);
    m_fileFP = NULL;
    delete this;
  }

private:
  FILE* m_fileFP;
  bool m_bLargeFile;
};

void Image2PDF(WString input_file,WString output_file)
{
  Image image(input_file);
  int count = 1;
  if (image.GetType() != Image::e_JBIG2) {
    count = image.GetFrameCount();
  }  
  PDFDoc doc;
  for (int i = 0; i < count; i++) {
    PDFPage page = doc.InsertPage(i, image.GetWidth(), image.GetHeight());
    page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);
    // Add image to page
    page.AddImage(image, i, PointF(0, 0), image.GetWidth(), image.GetHeight(), true);
  }
  doc.SaveAs(output_file, PDFDoc::e_SaveFlagNoOriginal);

}

void FromImage(WString input_file, WString output_file)
{
  try {
    Convert::FromImage(input_file, output_file);
  }
  catch (foxit::Exception& e) {
    cout << e.GetMessage() << endl;
  }
}

void FromImage(FileReader *reader, FileWriter *writer)
{
  try {
    Convert::FromImage(reader, writer);
  }
  catch (foxit::Exception& e) {
    cout << e.GetMessage() << endl;
  }
}

int main(int argc, char *argv[])
{
  WString output_directory = output_path + L"image2pdf/";
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  try {
    {
      // Convert .bmp file to PDF document.
      WString input_file = input_path + L"watermark.bmp";
      WString output_file = output_directory + L"watermark_bmp.pdf";
      Image2PDF(input_file,output_file);
      cout << "Convert BMP file to PDF file." << endl;
    }
    {
      // Convert .jpg file to PDF document.
      WString input_file = input_path + L"image_samples.jpg";
      WString output_file = output_directory + L"image_samples_jpg.pdf";
      Image2PDF(input_file,output_file);
      cout << "Convert JPG file to PDF file." << endl;
    }
    {
      // Convert .tif file to PDF document.
      WString input_file = input_path + L"TIF2Pages.tif";
      WString output_file = output_directory + L"TIF2Pages_tif.pdf";
      Image2PDF(input_file,output_file);
      cout << "Convert TIF file to PDF file." << endl;
    }
    {
      // Convert .gif file to PDF document.
      WString input_file = input_path + L"image005.gif";
      WString output_file = output_directory + L"image005_gif.pdf";
      Image2PDF(input_file,output_file);
      cout << "Convert GIF file to PDF file." << endl;
    }
    {
      // Convert .png file to PDF document.
      WString input_file = input_path + L"1.png";
      WString output_file = output_directory + L"1_png.pdf";
      Image2PDF(input_file, output_file);
      cout << "Convert PNG file to PDF file." << endl;
    }
    {
      // Convert .jb2 file to PDF document.
      WString input_file = input_path + L"STR_039.jb2";
      WString output_file = output_directory + L"STR_039_jb2.pdf";
      Image2PDF(input_file, output_file);
      cout << "Convert JB2 file to PDF file." << endl;
    }
    {
      // Convert .jp2 file to PDF document.
      WString input_file = input_path + L"1.jp2";
      WString output_file = output_directory + L"1_jp2.pdf";
      Image2PDF(input_file, output_file);
      cout << "Convert JP2 file to PDF file." << endl;
    }
    {
      // Convert .jpx file to PDF document.
      WString input_file = input_path + L"1.jpx";
      WString output_file = output_directory + L"1_jpx.pdf";
      Image2PDF(input_file, output_file);
      cout << "Convert JPX file to PDF file." << endl;
    }

  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }
  // Convert from filepath
  try {
    cout << "Start: convert file from file path." << endl;
    {
      // Convert .bmp file to PDF document.
      WString input_file = input_path + L"watermark.bmp";
      WString output_file = output_directory + L"watermark_bmp_frompath.pdf";
      FromImage(input_file, output_file);
      cout << "Convert BMP file to PDF file." << endl;
    }
    {
      // Convert .jpg file to PDF document.
      WString input_file = input_path + L"image_samples.jpg";
      WString output_file = output_directory + L"image_samples_jpg_frompath.pdf";
      FromImage(input_file, output_file);
      cout << "Convert JPG file to PDF file." << endl;
    }
    {
      // Convert .tif file to PDF document.
      WString input_file = input_path + L"TIF2Pages.tif";
      WString output_file = output_directory + L"TIF2Pages_tif_frompath.pdf";
      FromImage(input_file, output_file);
      cout << "Convert TIF file to PDF file." << endl;
    }
    {
      // Convert .gif file to PDF document.
      WString input_file = input_path + L"image005.gif";
      WString output_file = output_directory + L"image005_gif_frompath.pdf";
      FromImage(input_file, output_file);
      cout << "Convert GIF file to PDF file." << endl;
    }
    {
      // Convert .png file to PDF document.
      WString input_file = input_path + L"1.png";
      WString output_file = output_directory + L"1_png_frompath.pdf";
      FromImage(input_file, output_file);
      cout << "Convert PNG file to PDF file." << endl;
    }
    {
      // Convert .jb2 file to PDF document.
      WString input_file = input_path + L"STR_039.jb2";
      WString output_file = output_directory + L"STR_039_jb2_frompath.pdf";
      FromImage(input_file, output_file);
      cout << "Convert JB2 file to PDF file." << endl;
    }
    {
      // Convert .jp2 file to PDF document.
      WString input_file = input_path + L"1.jp2";
      WString output_file = output_directory + L"1_jp2_frompath.pdf";
      FromImage(input_file, output_file);
      cout << "Convert JP2 file to PDF file." << endl;
    }
    {
      // Convert .jpx file to PDF document.
      WString input_file = input_path + L"1.jpx";
      WString output_file = output_directory + L"1_jpx_frompath.pdf";
      FromImage(input_file, output_file);
      cout << "Convert JPX file to PDF file." << endl;
    }
    cout << "End: convert file from file path." << endl;
  }
  catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }

  // Convert from stream
  try {
    cout << "Start: convert file from stream." << endl;
    {
      // Convert .bmp file to PDF document.
      WString input_file = input_path + L"watermark.bmp";
      FileReader *filereader = new FileReader();
      filereader->LoadFile(input_file);
      WString output_file = output_directory + L"watermark_bmp_stream.pdf";
      FileWriter *filewriter = new FileWriter();
      filewriter->LoadFile(String::FromUnicode(output_file));
      FromImage(filereader, filewriter);
      cout << "Convert BMP file to PDF file." << endl;
    }
    {
      // Convert .jpg file to PDF document.
      WString input_file = input_path + L"image_samples.jpg";
      FileReader *filereader = new FileReader();
      filereader->LoadFile(input_file);
      WString output_file = output_directory + L"image_samples_jpg_stream.pdf";
      FileWriter *filewriter = new FileWriter();
      filewriter->LoadFile(String::FromUnicode(output_file));
      FromImage(filereader, filewriter);
      cout << "Convert JPG file to PDF file." << endl;
    }
    {
      // Convert .tif file to PDF document.
      WString input_file = input_path + L"TIF2Pages.tif";
      FileReader *filereader = new FileReader();
      filereader->LoadFile(input_file);
      WString output_file = output_directory + L"TIF2Pages_tif_stream.pdf";
      FileWriter *filewriter = new FileWriter();
      filewriter->LoadFile(String::FromUnicode(output_file));
      FromImage(filereader, filewriter);
      cout << "Convert TIF file to PDF file." << endl;
    }
    {
      // Convert .gif file to PDF document.
      WString input_file = input_path + L"image005.gif";
      FileReader *filereader = new FileReader();
      filereader->LoadFile(input_file);
      WString output_file = output_directory + L"image005_gif_stream.pdf";
      FileWriter *filewriter = new FileWriter();
      filewriter->LoadFile(String::FromUnicode(output_file));
      FromImage(filereader, filewriter);
      cout << "Convert GIF file to PDF file." << endl;
    }
    {
      // Convert .png file to PDF document.
      WString input_file = input_path + L"1.png";
      FileReader *filereader = new FileReader();
      filereader->LoadFile(input_file);
      WString output_file = output_directory + L"1_png_stream.pdf";
      FileWriter *filewriter = new FileWriter();
      filewriter->LoadFile(String::FromUnicode(output_file));
      FromImage(filereader, filewriter);
      cout << "Convert PNG file to PDF file." << endl;
    }

    {
      // Convert .jb2 file to PDF document.
      WString input_file = input_path + L"STR_039.jb2";
      FileReader *filereader = new FileReader();
      filereader->LoadFile(input_file);
      WString output_file = output_directory + L"STR_039_jb2_stream.pdf";
      FileWriter *filewriter = new FileWriter();
      filewriter->LoadFile(String::FromUnicode(output_file));
      FromImage(filereader, filewriter);
      cout << "Convert JB2 file to PDF file." << endl;
    }

    {
      // Convert .jp2 file to PDF document.
      WString input_file = input_path + L"1.jp2";
      FileReader *filereader = new FileReader();
      filereader->LoadFile(input_file);
      WString output_file = output_directory + L"1_jp2_stream.pdf";
      FileWriter *filewriter = new FileWriter();
      filewriter->LoadFile(String::FromUnicode(output_file));
      FromImage(filereader, filewriter);
      cout << "Convert JP2 file to PDF file." << endl;
    }
    {
      // Convert .jpx file to PDF document.
      WString input_file = input_path + L"1.jpx";
      FileReader *filereader = new FileReader();
      filereader->LoadFile(input_file);
      WString output_file = output_directory + L"1_jpx_stream.pdf";
      FileWriter *filewriter = new FileWriter();
      filewriter->LoadFile(String::FromUnicode(output_file));
      FromImage(filereader, filewriter);
      cout << "Convert JPX file to PDF file." << endl;
    }
    cout << "End: convert file from  stream." << endl;
  }
  catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  }
  catch(...)
  {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}

