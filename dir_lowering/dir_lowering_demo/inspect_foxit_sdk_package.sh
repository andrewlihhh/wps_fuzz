#!/usr/bin/env bash
set -euo pipefail

WORKDIR="$(cd "$(dirname "$0")" && pwd)"
SDK_DIR="$WORKDIR/foxit_sdk"

cd "$WORKDIR"

zip_path="${1:-}"
if [[ -z "$zip_path" ]]; then
  zip_path="$(find "$WORKDIR" -maxdepth 1 -type f \( -iname '*foxit*.zip' -o -iname '*pdfsdk*.zip' \) | head -n 1 || true)"
fi

if [[ -z "$zip_path" ]]; then
  echo "No Foxit SDK zip found in $WORKDIR"
  echo "Place the official Linux x86_64 SDK zip here and rerun this script."
  exit 1
fi

echo "Using archive: $zip_path"
rm -rf "$SDK_DIR"
mkdir -p "$SDK_DIR"
unzip -q "$zip_path" -d "$SDK_DIR"

echo
echo "Top-level contents under extracted SDK:"
find "$SDK_DIR" -maxdepth 2 -mindepth 1 | sed -n '1,80p'

echo
echo "Looking for common SDK folders:"
find "$SDK_DIR" -type d \( -iname include -o -iname lib -o -iname examples -o -iname doc -o -iname res \) | sed -n '1,40p'

echo
echo "Looking for common license files:"
find "$SDK_DIR" -type f \( -iname 'gsdk_sn.txt' -o -iname 'gsdk_key.txt' -o -iname '*license*' \) | sed -n '1,40p'

echo
echo "Looking for Linux shared libraries:"
find "$SDK_DIR" -type f \( -iname '*.so' -o -iname '*.a' \) | sed -n '1,80p'

first_lib="$(find "$SDK_DIR" -type f -iname '*.so' | head -n 1 || true)"
if [[ -n "$first_lib" ]]; then
  echo
  echo "Architecture check for first shared library: $first_lib"
  file "$first_lib"
fi

echo
echo "Inspection complete."