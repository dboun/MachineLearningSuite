cmake_minimum_required(VERSION 3.1)

set( PROJECT_NAME MLSuite )
set( PROJECT_VERSION 0.1.0 )

# Define the project name (project is a cmake term)
project( ${PROJECT_NAME} VERSION ${PROJECT_VERSION} )

# Add the dependencies
add_subdirectory( depends/yaml-cpp )

# For OpenCV (it is an external dependency)
FIND_PACKAGE( OpenCV REQUIRED )

# This runs whatever is inside files.cmake
# It is different from what add_subdirectory
# generally does. This runs code as if it
# is part of this file. The other one adds 
# a different project (looks for CMakeLists.txt
# in the corresponding directory).
include( files.cmake )

# Define the library (Executable name + files)
# This generally needs just the sources,
# but if you don't add the headers too then
# they don't show up in Visual Studio.
# SHARED means create shared objects (.dll or .so)
# and not static libraries (.a etc)
add_library( ${PROJECT_NAME} SHARED
	${CPP_FILES}
	${H_FILES} 
)

# Define the dependencies of the project
# (project name + libraries)
target_link_libraries( ${PROJECT_NAME} 
	yaml-cpp
	${OpenCV_LIBRARIES}
)

# Where this library and projects that depend
# on this library will look for headers
target_include_directories( ${PROJECT_NAME} PUBLIC
	${PROJECT_SOURCE_DIR}/include
)