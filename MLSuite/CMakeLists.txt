cmake_minimum_required(VERSION 3.0.0)

set( PROJECT_NAME MLSuite )
set( PROJECT_VERSION 0.1.0 )

# Define the project name (project is a cmake term)
project( ${PROJECT_NAME} VERSION ${PROJECT_VERSION} )

# Add the dependencies
add_subdirectory( depends/yaml-cpp )

# For OpenCV
FIND_PACKAGE( OpenCV REQUIRED )

# This runs whatever is inside files.cmake
# It is different from what add_subdirectory
# generally does. This runs code as if it
# is part of this file. The other one adds 
# a different project.
include( files.cmake )

# Define the library (Executable name + files)
# This generally needs just the sources,
# but if you don't add the headers too then
# they don't show up in Visual Studio
add_library( ${PROJECT_NAME} 
	${CPP_FILES}
	${H_FILES} 
)

# Define the dependencies of the project
# (project name + libraries)
target_link_libraries( ${PROJECT_NAME} 
	YAML_CPP
	${OpenCV_LIBRARIES}
)

# Where this library and projects that depend
# on this library will look for headers
target_include_directories( ${PROJECT_NAME}
	include
)