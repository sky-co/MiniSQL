#!/usr/bin/env bash

set -eu

echo "Build source files with CMake..."
Build_File_Path="build"


rm -rf ${Build_File_Path}
mkdir ${Build_File_Path}
cd ${Build_File_Path}
cmake ..
make
