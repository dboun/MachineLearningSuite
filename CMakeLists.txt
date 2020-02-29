cmake_minimum_required(VERSION 3.0.0)

set( PROJECT_NAME MachineLearningSuite )
set( PROJECT_VERSION 0.1.0 )

# Define the project name (project is a cmake term)
project( ${PROJECT_NAME} VERSION ${PROJECT_VERSION} )

# Add the library that we build
add_subdirectory( MLSuite )

# Define the executable (Executable name + files)
add_executable ( ${PROJECT_NAME} main.cxx )

# Define the dependencies of the executable
# (Executable name + libraries)
target_link_libraries( ${PROJECT_NAME} MLSuite )