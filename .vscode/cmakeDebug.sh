#!/bin/bash

# The full directory name of the script no matter where it is being called from
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

BUILD_DEBUG_DIR=${DIR}/../../MachineLearningSuite-build/Debug
mkdir -p ${BUILD_DEBUG_DIR}
cd ${BUILD_DEBUG_DIR}
cmake ../../MachineLearningSuite-src -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=${DIR}/../../OpenCV-build/Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON