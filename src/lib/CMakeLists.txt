message("[log] CMake lib")

set(_SHARED_LIBRARY_NAME "checkers_shared")
set(_INCLUDE_DIRECTORIES "board" "game" "move" "piece" "tile")

# add the given directories to those the compiler uses to search for include files (headers file)
include_directories(${_INCLUDE_DIRECTORIES})

# file manipulation command: all C++ source files
#file(GLOB SOURCES "*.cpp")
# (search in every sub-directory)
file(GLOB_RECURSE _SOURCES "*.cpp")

# generate a shared library called "checkers_shared" to be built from the source files (specified in the previous command)
add_library(${_SHARED_LIBRARY_NAME} SHARED ${_SOURCES})

# sets properties on targets
set_target_properties(${_SHARED_LIBRARY_NAME} PROPERTIES OUTPUT_NAME ${_SHARED_LIBRARY_NAME})
