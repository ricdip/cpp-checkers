message("[log] CMake tests")

set(_GTEST_LIBRARY_NAME "GTest::gtest_main")
set(_SHARED_LIBRARY_NAME "checkers_shared")

set(_TESTS "ai_test" "board_test" "game_test" "move_generator_test" "move_test" "piece_test" "player_test" "tile_test")

# find a package (usually provided by something external to the project), and load its package-specific details
find_package(GTest REQUIRED)

# adds an executable target to be built from the source files listed in the command invocation
# list of test files (for each declared test)
foreach(_TEST ${_TESTS})
    add_executable(${_TEST} ${_TEST}.cpp)
endforeach()

# specify libraries or flags to use when linking a given target and/or its dependents (for each declared test)
foreach(_TEST ${_TESTS})
    target_link_libraries(${_TEST} ${_GTEST_LIBRARY_NAME})
    target_link_libraries(${_TEST} ${_SHARED_LIBRARY_NAME})
endforeach()

# loads and runs CMake code from the file given: gtest_discover_tests is here
include(GoogleTest)

# Automatically add tests with CTest by scanning source code for Google Test macros (for each declared test)
foreach(_TEST ${_TESTS})
    gtest_add_tests(TARGET ${_TEST})
endforeach()
