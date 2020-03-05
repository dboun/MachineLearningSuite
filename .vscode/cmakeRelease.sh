#!/bin/bash

# The full directory name of the script no matter where it is being called from
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

BUILD_RELEASE_DIR=${DIR}/../../MachineLearningSuite-build/Release
mkdir -p ${BUILD_RELEASE_DIR}
cd ${BUILD_RELEASE_DIR}
cmake ../../MachineLearningSuite-src -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=${DIR}/../../OpenCV-build/Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON