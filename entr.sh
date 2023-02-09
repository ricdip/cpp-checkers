#!/bin/sh

# enable dev mode for tests
fd --type f -e cpp -e hpp | entr -crs "make build_debug_test; make run_tests"

# enable dev mode for main
#fd --type f -e cpp -e hpp | entr -crs "make build_debug; make run"
