#!/bin/bash

set -e  # Exit immediately on error

# clear the caches
rm -rf build

# Create build directory if it doesn't exist
mkdir -p build

# Configure project and generate compile_commands.json
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build

# Optionally symlink compile_commands.json to root (for clangd)
ln -sf build/compile_commands.json compile_commands.json

# Build the project
cmake --build build
