message("CMake app")

# file manipulation command: all C++ source files
file(GLOB SOURCES "*.cpp")

# generate an executable target called "cpp_checkers" to be built from the source files (specified in the previous command)
add_executable(cpp_checkers ${SOURCES})

# specify libraries or flags to use when linking a given target and/or its dependents
target_link_libraries(cpp_checkers checkers_shared)
