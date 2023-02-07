message("CMake lib")

# add the given directories to those the compiler uses to search for include files (headers file)
include_directories(include)

# file manipulation command: all C++ source files
file(GLOB SOURCES "*.cpp")

# generate a shared library called "checkers_shared" to be built from the source files (specified in the previous command)
add_library(checkers_shared SHARED ${SOURCES})

# sets properties on targets
set_target_properties(checkers_shared PROPERTIES OUTPUT_NAME "checkers_shared")
