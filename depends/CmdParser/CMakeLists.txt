cmake_minimum_required(VERSION 3.0.0)

set( PROJECT_NAME CmdParser )

# Define the project name (project is a cmake term)
project( ${PROJECT_NAME} )

# Define the library (library name + files)
add_library( ${PROJECT_NAME} 
	cbicaCmdParser.cpp
	cbicaCmdParser.h
)

# Where to look for headers
# In this case it is set at the root of
# the project, because that's where the header is
target_include_directories( ${PROJECT_NAME}
	${PROJECT_SOURCE_DIR}
)

# Define the dependencies of the library.
# Generally CmdParser depends on yaml-cpp
# https://github.com/CBICA/CmdParser
# But since MLSuite depends on yaml-cpp too,
# we can just expect it to be found.
# This is generally weird, I just didn't
# want it to build yaml twice, and I wanted
# yaml-cpp to be a dependency inside the MLSuite library.
target_link_libraries( ${PROJECT_NAME} YAML-CPP )