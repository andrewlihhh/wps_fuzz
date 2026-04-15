#!/usr/bin/env python3
import argparse
import os
import subprocess
import sys
import tempfile
from pathlib import Path


DEFAULT_SDK_DLL = Path("/home/kzl/wps_fuzz/openxml_sdk_demo/bin/Release/net8.0/openxml_sdk_demo.dll")
DEFAULT_OUTPUT_DIR = Path("/tmp/nautilus-openxml-wrapper")


def parse_args():
    argv = sys.argv[1:]
    if "--" in argv:
        split_index = argv.index("--")
        wrapper_argv = argv[:split_index]
        target_argv = argv[split_index + 1 :]
    else:
        wrapper_argv = argv
        target_argv = []

    parser = argparse.ArgumentParser(
        description="Lower Nautilus-generated JSON IR into DOCX, then hand the DOCX to a target program."
    )
    parser.add_argument("input_ir", help="Path to the Nautilus-generated IR file")
    parser.add_argument(
        "--sdk-dll",
        default=str(DEFAULT_SDK_DLL),
        help="Path to the built Open XML SDK demo DLL",
    )
    parser.add_argument(
        "--output-dir",
        default=str(DEFAULT_OUTPUT_DIR),
        help="Directory for temporary generated DOCX files",
    )
    parser.add_argument(
        "--keep-docx",
        action="store_true",
        help="Keep the generated DOCX on disk after the target exits",
    )
    args = parser.parse_args(wrapper_argv)
    args.target = target_argv
    return args


def build_docx(input_ir: Path, sdk_dll: Path, output_dir: Path) -> Path:
    if not input_ir.is_file():
        raise FileNotFoundError(f"IR file not found: {input_ir}")
    if not sdk_dll.is_file():
        raise FileNotFoundError(
            "Open XML SDK demo DLL not found. Build it first with: "
            "dotnet build -c Release /home/kzl/wps_fuzz/openxml_sdk_demo/openxml_sdk_demo.csproj"
        )

    output_dir.mkdir(parents=True, exist_ok=True)
    with tempfile.NamedTemporaryFile(prefix="nautilus-", suffix=".docx", dir=output_dir, delete=False) as handle:
        docx_path = Path(handle.name)

    lower_cmd = ["dotnet", str(sdk_dll), str(input_ir), str(docx_path)]
    subprocess.run(lower_cmd, check=True)
    return docx_path


def materialize_target_command(target_args, docx_path: Path):
    if not target_args:
        return []
    replaced = [str(docx_path) if arg == "@@" else arg for arg in target_args]
    if "@@" not in target_args:
        replaced.append(str(docx_path))
    return replaced


def main() -> int:
    args = parse_args()
    input_ir = Path(args.input_ir).resolve()
    sdk_dll = Path(args.sdk_dll).resolve()
    output_dir = Path(args.output_dir).resolve()

    docx_path = build_docx(input_ir, sdk_dll, output_dir)
    print(f"Generated DOCX: {docx_path}")

    if not args.target:
        return 0

    target_cmd = materialize_target_command(args.target, docx_path)
    try:
        completed = subprocess.run(target_cmd)
        return completed.returncode
    finally:
        if not args.keep_docx:
            try:
                os.unlink(docx_path)
            except FileNotFoundError:
                pass


if __name__ == "__main__":
    sys.exit(main())
