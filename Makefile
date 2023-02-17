.DEFAULT_GOAL := all

# main
# build release version of checkers
.PHONY: build_release_test
build_release_test: clean build_cmake_release_test build_make

# build debug version of checkers
.PHONY: build_debug_test
build_debug_test: clean build_cmake_debug_test build_make

# build release version of checkers
.PHONY: build_release
build_release: clean build_cmake_release build_make

# build debug version of checkers
.PHONY: build_debug
build_debug: clean build_cmake_debug build_make

# cmake build rules
# launch CMake with build type Release and tests
.ONESHELL:
.PHONY: build_cmake_release_test
build_cmake_release_test:
	if [ ! -d "build" ]; then mkdir "build"; fi
	cd build
	cmake -DCMAKE_BUILD_TYPE=Release -D_TESTS=ON ..

# launch CMake with build type Debug and tests
.ONESHELL:
.PHONY: build_cmake_debug_test
build_cmake_debug_test:
	if [ ! -d "build" ]; then mkdir "build"; fi
	cd build
	cmake -DCMAKE_BUILD_TYPE=Debug -D_TESTS=ON ..

# launch CMake with build type Release
.ONESHELL:
.PHONY: build_cmake_release
build_cmake_release:
	if [ ! -d "build" ]; then mkdir "build"; fi
	cd build
	cmake -DCMAKE_BUILD_TYPE=Release ..

# launch CMake with build type Debug
.ONESHELL:
.PHONY: build_cmake_debug
build_cmake_debug:
	if [ ! -d "build" ]; then mkdir "build"; fi
	cd build
	cmake -DCMAKE_BUILD_TYPE=Debug ..

# make build rules
# launch make in CMake build directory
.ONESHELL:
.PHONY: build_make
build_make:
	cd build
	make VERBOSE=1

# clean and run rules
# clean build directory
.PHONY: clean
clean:
	rm -rf build/*

# run the app program
.PHONY: run
run: ./build/src/app/cpp_checkers
	./build/src/app/cpp_checkers

# run the tests
.PHONY: run_tests
run_tests: ./build/src/tests/piece_test ./build/src/tests/tile_test ./build/src/tests/board_test ./build/src/tests/move_test ./build/src/tests/move_generator_test ./build/src/tests/game_test ./build/src/tests/ai_test ./build/src/tests/player_test
	./build/src/tests/piece_test
	./build/src/tests/tile_test
	./build/src/tests/board_test
	./build/src/tests/move_test
	./build/src/tests/move_generator_test
	./build/src/tests/game_test
	./build/src/tests/ai_test
	./build/src/tests/player_test

# dev rules
# run dev mode (with entr)
.PHONY: dev
dev: ./entr.sh
	./entr.sh

# generate .clang-format file
.PHONY: clang-format-generate
clang-format-generate:
	clang-format -style=llvm -dump-config > .clang-format

# format code with clang-format
.PHONY: format
format:
	fd --type f -e cpp -e hpp | xargs clang-format -i

# clean, build release version and run program
.PHONY: all
all: clean build_release run
