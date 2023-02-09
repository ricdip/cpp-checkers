message("CMake tests")

# find a package (usually provided by something external to the project), and load its package-specific details
find_package(GTest REQUIRED)
# adds an executable target to be built from the source files listed in the command invocation
# list of test files
add_executable(piece_test piece_test.cpp)
add_executable(tile_test tile_test.cpp)
add_executable(board_test board_test.cpp)
add_executable(move_test move_test.cpp)
add_executable(game_test game_test.cpp)

# specify libraries or flags to use when linking a given target and/or its dependents
target_link_libraries(piece_test GTest::gtest_main)
target_link_libraries(piece_test checkers_shared)
target_link_libraries(tile_test GTest::gtest_main)
target_link_libraries(tile_test checkers_shared)
target_link_libraries(board_test GTest::gtest_main)
target_link_libraries(board_test checkers_shared)
target_link_libraries(move_test GTest::gtest_main)
target_link_libraries(move_test checkers_shared)
target_link_libraries(game_test GTest::gtest_main)
target_link_libraries(game_test checkers_shared)

# loads and runs CMake code from the file given: gtest_discover_tests is here
include(GoogleTest)

# automatically add tests with CTest by querying the compiled test executable for available tests
# gtest_discover_tests
gtest_add_tests(TARGET piece_test)
gtest_add_tests(TARGET tile_test)
gtest_add_tests(TARGET board_test)
gtest_add_tests(TARGET move_test)
gtest_add_tests(TARGET game_test)
