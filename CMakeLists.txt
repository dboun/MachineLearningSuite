cmake_minimum_required(VERSION 3.1)

# Use C++11
set ( CMAKE_CXX_STANDARD 11 )

# Enable exporting of compile commands (useful for intellisense in vscode etc)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL 
	"Enable/Disable output of compile commands during generation." FORCE
)

set( PROJECT_NAME MachineLearningSuite )

# Create the project
project( ${PROJECT_NAME} )

# Add the library that we want to link.
# All the computation happens inside this library.
# The current project is just the CLI program that calls this library.
add_subdirectory( MLSuite )

# Add the CmdParser dependency
add_subdirectory( depends/CmdParser )

# Define the executable (Executable name + files)
add_executable( ${PROJECT_NAME} main.cxx )

# Define the dependencies of the executable
# (Executable name + libraries)
target_link_libraries( ${PROJECT_NAME} 
	MLSuite
	CmdParser
)