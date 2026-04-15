# Foxit SDK experiment status

## What is blocked

The official Foxit PDF SDK Linux trial is not exposed as a public anonymous download.
Foxit routes the Linux SDK trial through a required form that asks for:

- Business Email
- First Name
- Last Name
- Company
- Phone Number
- Country/Region

Because of that, the SDK archive cannot be downloaded autonomously without real user-provided form data.

## What is already prepared

This folder now contains two experiment assets that become useful as soon as the official Linux x86_64 SDK zip is available here.

### 1. Package inspection script

Run:

```bash
cd /home/kzl/dir_lowering_demo
bash inspect_foxit_sdk_package.sh
```

What it does:

- finds a likely Foxit SDK zip in the current folder
- extracts it to `foxit_sdk/`
- checks for `include`, `lib`, `examples`, `doc`, `res`
- looks for license files like `gsdk_sn.txt` and `gsdk_key.txt`
- prints shared libraries and their architecture

### 2. Real Foxit C API lowering skeleton

File:

- [dir_to_foxit_pdf_c_api.c](/home/kzl/dir_lowering_demo/dir_to_foxit_pdf_c_api.c)

This is closer to Foxit's documented C API than the earlier placeholder example. It models:

- DIR document
- DIR pages
- DIR text objects

And lowers them through these Foxit-style steps:

1. `FSDK_Library_Initialize`
2. `FSDK_PDFDoc_Create`
3. `FSDK_PDFDoc_InsertPage`
4. `FSDK_TextObject_Create`
5. `FSDK_Font_Create`
6. `FSDK_TextObject_SetTextState`
7. `FSDK_TextObject_SetText`
8. `FSDK_GraphicsObjects_InsertGraphicsObject`
9. `FSDK_GraphicsObjects_GenerateContent`
10. `FSDK_PDFDoc_SaveAs`

In other words, this file shows a more realistic `DIR -> Foxit PDF SDK -> PDF` path once the actual Linux SDK headers and libraries are present.

## What to do next when the SDK zip is available

1. Put the official Foxit Linux x86_64 SDK zip into this directory.
2. Run `bash inspect_foxit_sdk_package.sh`.
3. Adapt include paths and linker paths from the extracted package layout.
4. Fill in the real license values from `gsdk_sn.txt` and `gsdk_key.txt`.
5. Compile the C example against the real Foxit headers and libraries.

## Important note

Foxit publicly documents Linux support, but it does not provide a public anonymous Linux trial link. So the remaining blocker is not technical; it is vendor-controlled package access.