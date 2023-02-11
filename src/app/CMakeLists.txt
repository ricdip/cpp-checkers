message("[log] CMake app")

set(_EXECUTABLE_NAME "cpp_checkers")
set(_SHARED_LIBRARY_NAME "checkers_shared")

# file manipulation command: all C++ source files
file(GLOB _SOURCES "*.cpp")

# generate an executable target called "cpp_checkers" to be built from the source files (specified in the previous command)
add_executable(${_EXECUTABLE_NAME} ${_SOURCES})

# specify libraries or flags to use when linking a given target and/or its dependents
target_link_libraries(${_EXECUTABLE_NAME} ${_SHARED_LIBRARY_NAME})
