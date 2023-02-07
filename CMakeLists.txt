message("CMake main")

# minimum required version of cmake for a project
cmake_minimum_required(VERSION 3.25.2)

# project name, version, languages and description specification
project(cpp-checkers
    VERSION 0.1.0
    LANGUAGES CXX
    DESCRIPTION "A C++ implementation of checkers")

# print compiler id
message("using compiler: '${CMAKE_CXX_COMPILER_ID}'")

# set compiler flags based on used compiler
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Clang compiler
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC compiler
    # debug flags
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -pedantic -Werror -g -fsanitize=address")
    # release flags
    set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -pedantic -Werror -O2")
endif()

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

# add subdirectory lib to the build
add_subdirectory(src/lib)

# provide a boolean option that the user can optionally select
option(_TESTS "Build tests instead of app" OFF)
if(_TESTS)
    # enable testing for current directory and below
    enable_testing()
    # add subdirectory tests to the build
    add_subdirectory(src/tests)
else()
    # add subdirectory app to the build
    add_subdirectory(src/app)
endif(_TESTS)
# unset a variable, cache variable, or environment variable
unset(_TESTS CACHE)
