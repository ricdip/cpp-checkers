.DEFAULT_GOAL := help

# help
.SILENT: help
.PHONY: help # [MAIN] Display this help message
help:
	@grep -E '^.PHONY:.+#.+' Makefile | sed 's/.PHONY: //' | awk -F ' # ' '{printf "%-30s %s\n", $$1, $$2}'

# main
.PHONY: build_release_test # [MAIN] Build release version (checkers library and tests)
build_release_test: clean build_cmake_release_test build_make

.PHONY: build_debug_test # [MAIN] Build debug version (checkers library and tests)
build_debug_test: clean build_cmake_debug_test build_make

.PHONY: build_release # [MAIN] Build release version (checkers library and app)
build_release: clean build_cmake_release build_make

.PHONY: build_debug # [MAIN] Build debug version (checkers library and app)
build_debug: clean build_cmake_debug build_make

# cmake build rules
.ONESHELL:
.PHONY: build_cmake_release_test # [SUB]  Launch CMake with build type Release and tests
build_cmake_release_test:
	if [ ! -d "build" ]; then mkdir "build"; fi
	cd build
	cmake -DCMAKE_BUILD_TYPE=Release -D_TESTS=ON ..

.ONESHELL:
.PHONY: build_cmake_debug_test # [SUB]  Launch CMake with build type Debug and tests
build_cmake_debug_test:
	if [ ! -d "build" ]; then mkdir "build"; fi
	cd build
	cmake -DCMAKE_BUILD_TYPE=Debug -D_TESTS=ON ..

.ONESHELL:
.PHONY: build_cmake_release # [SUB]  Launch CMake with build type Release
build_cmake_release:
	if [ ! -d "build" ]; then mkdir "build"; fi
	cd build
	cmake -DCMAKE_BUILD_TYPE=Release ..

.ONESHELL:
.PHONY: build_cmake_debug # [SUB]  Launch CMake with build type Debug
build_cmake_debug:
	if [ ! -d "build" ]; then mkdir "build"; fi
	cd build
	cmake -DCMAKE_BUILD_TYPE=Debug ..

# make build rules
.ONESHELL:
.PHONY: build_make # [SUB]  Launch make in CMake build directory
build_make:
	cd build
	make VERBOSE=1

# clean and run rules
.PHONY: clean # [MAIN] Clean build directory
clean:
	rm -rf build/*

.PHONY: run # [MAIN] Run app
run: ./build/src/app/cpp_checkers
	./build/src/app/cpp_checkers

.PHONY: run_tests # [MAIN] Run tests
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
.PHONY: dev # [DEV]  Run dev mode (with entr)
dev: ./entr.sh
	./entr.sh

.PHONY: clang-format-generate # [DEV]  Generate .clang-format file
clang-format-generate:
	clang-format -style=llvm -dump-config > .clang-format

.PHONY: format # [DEV]  Format code with clang-format
format:
	fd --type f -e cpp -e hpp | xargs clang-format -i

.PHONY: all # [MAIN] Clean, build release version and run program
all: clean build_release run
