#!/bin/bash

# The full directory name of the script no matter where it is being called from
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Source directory
OpenCV_SRC_DIR=${DIR}/../../OpenCV-src

# Build directories
OpenCV_BUILD_DEBUG_DIR=${DIR}/../../OpenCV-build/Debug
OpenCV_BUILD_RELEASE_DIR=${DIR}/../../OpenCV-build/Release

git clone https://github.com/opencv/opencv ${OpenCV_SRC_DIR}

# Checkout specified version (it is a git tag)
cd ${OpenCV_SRC_DIR}
git fetch --all --tags
git checkout tags/3.4.8

# Build Debug
mkdir -p ${OpenCV_BUILD_DEBUG_DIR}
cd ${OpenCV_BUILD_DEBUG_DIR}
cmake ${OpenCV_SRC_DIR} -DCMAKE_BUILD_TYPE=Debug
make -j8

# Build Release
mkdir -p ${OpenCV_BUILD_RELEASE_DIR}
cd ${OpenCV_BUILD_RELEASE_DIR}
cmake ${OpenCV_SRC_DIR} -DCMAKE_BUILD_TYPE=Release
make -j8