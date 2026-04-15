// Copyright (C) 2003-2026, Foxit Software Inc..
// All Rights Reserved.
//
// http://www.foxitsoftware.com
//
// The following code is copyrighted and contains proprietary information and trade secrets of Foxit Software Inc..
// You cannot distribute any part of Foxit PDF SDK to any third party or general public,
// unless there is a separate license agreement with Foxit Software Inc. which explicitly grants you such rights.
//
// This file contains an example to demonstrate how to use Foxit PDF SDK to do LTV verification (using default callback) in PDF document.

// Include header files.
#include <iostream>
#include <time.h>
#include <ctime>
#if defined(_WIN32) || defined(_WIN64)
#include<direct.h>
#else
#include <sys/stat.h>
#endif

// Include Foxit SDK header files.
#include "../../../include/pdf/annots/fs_annot.h"
#include "../../../include/common/fs_image.h"
#include "../../../include/pdf/fs_pdfdoc.h"
#include "../../../include/pdf/fs_pdfpage.h"
#include "../../../include/pdf/fs_signature.h"
#include "../../../include/pdf/fs_ltvverifier.h"

using namespace std;
using namespace foxit;
using namespace foxit::common;
using foxit::common::Library;
using namespace pdf;
using namespace objects;
using namespace file;

// sn and key information from Foxit PDF SDK's key files are used to initialize Foxit PDF SDK library. 
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

WString output_directory = output_path + L"ltv/";

#define FREE_ETSIRFC316TSA_SERVER_NAME L"FreeTSAServer"
#define FREE_ETSIRFC316TSA_SERVER_URL L"http://ca.signfiles.com/TSAServer.aspx"

#define PKCS7_SIGNATURE_FILTER "Adobe.PPKLite"
#define PKCS7_SIGNATURE_SUBFILTER "adbe.pkcs7.detached"


FILE* OpenFileWrapper(const char* file_name, const char* file_mode) {
  FILE* ret_file = NULL;
#if defined(_WIN32) || defined(_WIN64)
  fopen_s(&ret_file, (const char*)file_name, (const char*)file_mode);
#else
  ret_file = fopen((const char*)file_name, (const char*)file_mode);
#endif
  return ret_file;
}

string TransformSignatureStateToString(uint32 sig_state) {
  string state_str;
  if (sig_state & Signature::e_StateUnknown)
    state_str += "Unknown";
  if (sig_state & Signature::e_StateNoSignData) {
    if (state_str.length()>0) state_str += "|";
    state_str += "NoSignData";
  }
  if (sig_state & Signature::e_StateUnsigned) {
    if (state_str.length()>0) state_str += "|";
    state_str += "Unsigned";
  }
  if (sig_state & Signature::e_StateSigned) {
    if (state_str.length()>0) state_str += "|";
    state_str += "Signed";
  }
  if (sig_state & Signature::e_StateVerifyValid) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerfiyValid";
  }
  if (sig_state & Signature::e_StateVerifyInvalid) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyInvalid";
  }
  if (sig_state & Signature::e_StateVerifyErrorData) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyErrorData";
  }
  if (sig_state & Signature::e_StateVerifyNoSupportWay) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyNoSupportWay";
  }
  if (sig_state & Signature::e_StateVerifyErrorByteRange) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyErrorByteRange";
  }
  if (sig_state & Signature::e_StateVerifyChange) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyChange";
  }
  if (sig_state & Signature::e_StateVerifyIncredible) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyIncredible";
  }
  if (sig_state & Signature::e_StateVerifyNoChange) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyNoChange";
  }
  if (sig_state & Signature::e_StateVerifyIssueValid) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyIssueValid";
  }
  if (sig_state & Signature::e_StateVerifyIssueUnknown) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyIssueUnknown";
  }
  if (sig_state & Signature::e_StateVerifyIssueRevoke) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyIssueRevoke";
  }
  if (sig_state & Signature::e_StateVerifyIssueExpire) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyIssueExpire";
  }
  if (sig_state & Signature::e_StateVerifyIssueUncheck) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyIssueUncheck";
  }
  if (sig_state & Signature::e_StateVerifyIssueCurrent) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyIssueCurrent";
  }
  if (sig_state & Signature::e_StateVerifyTimestampNone) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampNone";
  }
  if (sig_state & Signature::e_StateVerifyTimestampDoc) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampDoc";
  }
  if (sig_state & Signature::e_StateVerifyTimestampValid) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampValid";
  }
  if (sig_state & Signature::e_StateVerifyTimestampInvalid) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampInvalid";
  }
  if (sig_state & Signature::e_StateVerifyTimestampExpire) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampExpire";
  }
  if (sig_state & Signature::e_StateVerifyTimestampIssueUnknown) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampIssueUnknown";
  }
  if (sig_state & Signature::e_StateVerifyTimestampIssueValid) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampIssueValid";
  }
  if (sig_state & Signature::e_StateVerifyTimestampTimeBefore) {
    if (state_str.length()>0) state_str += "|";
    state_str += "VerifyTimestampTimeBefore";
  }
  if (sig_state & Signature::e_StateCertCannotGetVRI) {
    if (state_str.length()>0) state_str += "|";
    state_str += "CertCannotGetVRI";
  }
  return state_str;
}

void PKCS7Signature(const WString& input_pdf_path, const WString& signed_pdf_path) {
  PDFDoc pdf_doc(input_pdf_path);
  pdf_doc.StartLoad();
  PDFPage pdf_page = pdf_doc.GetPage(0);
  float page_width = pdf_page.GetWidth();
  float page_height = pdf_page.GetHeight();
  RectF new_sig_rect((page_width / 2 - 50.0f), (page_height / 2 - 50.0f), (page_width / 2 + 50.0f), (page_height / 2 + 50.0f));
  Signature new_signature = pdf_page.AddSignature(new_sig_rect);
  new_signature.SetFilter(PKCS7_SIGNATURE_FILTER);
  new_signature.SetSubFilter(PKCS7_SIGNATURE_SUBFILTER);

  //String new_value;
  new_signature.SetKeyValue(Signature::e_KeyNameSigner, L"Foxit PDF SDK");
  new_signature.SetKeyValue(Signature::e_KeyNameContactInfo, L"support@foxitsoftware.com");
  new_signature.SetKeyValue(Signature::e_KeyNameDN, L"CN=CN,MAIL=MAIL@MAIL.COM");
  new_signature.SetKeyValue(Signature::e_KeyNameLocation, L"Fuzhou, China");
  String new_value;
  new_value.Format("As a sample for subfilter \"%s\" ", PKCS7_SIGNATURE_SUBFILTER);
  new_signature.SetKeyValue(Signature::e_KeyNameReason, (const wchar_t*)WString::FromLocal(new_value));
  new_signature.SetKeyValue(Signature::e_KeyNameText, (const wchar_t*)WString::FromLocal(new_value));
  DateTime sign_time = DateTime::GetLocalTime();
  new_signature.SetSignTime(sign_time);
  // Set appearance flags to decide which content would be used in appearance.
  uint32 ap_flags = Signature::e_APFlagLabel | Signature::e_APFlagSigner |
    Signature::e_APFlagReason | Signature::e_APFlagDN |
    Signature::e_APFlagLocation | Signature::e_APFlagText |
    Signature::e_APFlagSigningTime;
  new_signature.SetAppearanceFlags(ap_flags);

  WString cert_path = input_path + L"foxit_all.pfx";
  WString cert_password = L"123456";
  Progressive sign_progressive = new_signature.StartSign(cert_path, cert_password, Signature::e_DigestSHA256, signed_pdf_path);
  if (sign_progressive.GetRateOfProgress() != 100) {
    if (Progressive::e_Finished != sign_progressive.Continue()) {
      printf("[Failed] Fail to sign the new CAdES signature.\r\n");
      return;
    }
  }
}

// Here, the implementation of TrustedCertStoreCallback is very simple : 
// trust all input certificate(s) when this callback function is triggered during LTV verification.
// User can improve the implementation of the callback class TrustedCertStoreCallback or choose not to use TrustedCertStoreCallback.
class MyTrustedCertStoreCallback : public TrustedCertStoreCallback {
public:
  MyTrustedCertStoreCallback() {}
  ~MyTrustedCertStoreCallback() {}

  virtual bool IsCertTrusted(const String& cert) {
    return true;
  }
  
  virtual bool IsCertTrustedRoot(const String& cert) {
    return true;
  }
};

void UseLTVVerifier(const PDFDoc& pdf_doc, bool is_to_add_dss) {
  // Here use default RevocationCallback, so no need to call LTVVerifier::SetRevocationCallback
  LTVVerifier ltv_verifier(pdf_doc, true, true, false, LTVVerifier::e_SignatureCreationTime);

  // Use implemented TrustedCertStoreCallback to trust some cerificates during LTV verification.
  // Here, the implementation of TrustedCertStoreCallback is very simple : 
  // trust all input certificate(s) when this callback function is triggered during LTV verification.
  // User can improve the implementation of the callback class TrustedCertStoreCallback or choose not to use TrustedCertStoreCallback.
  MyTrustedCertStoreCallback my_callback;
  ltv_verifier.SetTrustedCertStoreCallback(&my_callback);

  ltv_verifier.SetVerifyMode(LTVVerifier::e_VerifyModeAcrobat);

  SignatureVerifyResultArray sig_verify_result_array = ltv_verifier.Verify();
  for (size_t i = 0; i < sig_verify_result_array.GetSize(); i++) {
    SignatureVerifyResult sig_verify_result = sig_verify_result_array.GetAt(i);
    String signature_name = sig_verify_result.GetSignatureName();
    uint32 sig_state = sig_verify_result.GetSignatureState();
    SignatureVerifyResult::LTVState ltv_state = sig_verify_result.GetLTVState();
    string ltv_state_str;
    switch (ltv_state) {
      case SignatureVerifyResult::e_LTVStateInactive:
        ltv_state_str = "inactive";
        break;
      case SignatureVerifyResult::e_LTVStateEnable:
        ltv_state_str = "enabled";
        break;
      case SignatureVerifyResult::e_LTVStateNotEnable:
        ltv_state_str = "not enabled";
        break;
    }
    printf("Signature name:%s, signature state: %s, LTV state: %s\r\n",
           signature_name.GetBuffer(signature_name.GetLength()),
           TransformSignatureStateToString(sig_state).c_str(),
           ltv_state_str.c_str());
    signature_name.ReleaseBuffer();
  }

  if (is_to_add_dss) {
    for (size_t i = 0; i < sig_verify_result_array.GetSize(); i++) {
      if (sig_verify_result_array.GetAt(i).GetSignatureState() & Signature::e_StateVerifyValid)
        ltv_verifier.AddDSS(sig_verify_result_array.GetAt(i));
    }
  }
}

void DoLTV(const WString& signed_pdf_path, const WString& saved_ltv_pdf_path) {
  // Use default SignatureCallback for signing a time stamp signature with filter "Adobe.PPKLite" and subfilter "ETSI.RFC3161",
  // so no need to register a custom signature callback.

  TimeStampServerMgr::Initialize();
  TimeStampServer timestamp_server = TimeStampServerMgr::AddServer(FREE_ETSIRFC316TSA_SERVER_NAME, FREE_ETSIRFC316TSA_SERVER_URL, L"", L"");
  TimeStampServerMgr::SetDefaultServer(timestamp_server);

  PDFDoc pdf_doc(signed_pdf_path);
  pdf_doc.StartLoad();
  // Add DSS
  printf("== Before Add DSS ==\r\n");
  UseLTVVerifier(pdf_doc, true);

  // Add DTS
  PDFPage pdf_page = pdf_doc.GetPage(0);
  // The new time stamp signature will have default filter name "Adobe.PPKLite" and default subfilter name "ETSI.RFC3161".
  Signature timestamp_signature = pdf_page.AddSignature(RectF(), L"", Signature::e_SignatureTypeTimeStamp);
  Progressive sign_progressive = timestamp_signature.StartSign(L"", L"", Signature::e_DigestSHA256, saved_ltv_pdf_path);
  if (sign_progressive.GetRateOfProgress() != 100)
    sign_progressive.Continue();

  // Check saved file.
  PDFDoc check_pdf_doc(saved_ltv_pdf_path);
  check_pdf_doc.StartLoad();
  // Just LTV veify.
  printf("== After Add DSS ==\r\n");
  UseLTVVerifier(check_pdf_doc, false);

  TimeStampServerMgr::Release();
}

int main(int argc, char *argv[]) {
#if defined(_WIN32) || defined(_WIN64)
  _mkdir(String::FromUnicode(output_directory));
#else
  mkdir(String::FromUnicode(output_directory), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif

  int err_ret = 0;
  WString input_file_name = L"AboutFoxit.pdf";
  WString input_file_path = input_path + input_file_name;
  SdkLibMgr sdk_lib_mgr;
  // Initialize library.
  ErrorCode error_code = sdk_lib_mgr.Initialize();
  if (error_code != foxit::e_ErrSuccess) {
    return 1;
  }

  printf("Input file path: %s\r\n", (const char*)String::FromUnicode(input_file_path));
  try {
    // Add a PKCS7 signature and sign it.
    WString signed_pdf_path = output_directory + input_file_name.Left(input_file_name.GetLength()-4) + L"_signed.pdf";
    PKCS7Signature(input_file_path, signed_pdf_path);

    // Do LTV
    WString saved_ltv_pdf_path = signed_pdf_path.Left(signed_pdf_path.GetLength() - 4) + L"_ltv.pdf";
    DoLTV(signed_pdf_path, saved_ltv_pdf_path);

  } catch (const Exception& e) {
    cout << e.GetMessage() << endl;
    err_ret = 1;
  } catch(...) {
    cout << "Unknown Exception" << endl;
    err_ret = 1;
  }

  return err_ret;
}

