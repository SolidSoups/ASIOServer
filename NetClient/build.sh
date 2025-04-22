#!/bin/bash

BUILD_DIR="build"

echo "🧹 Clearing caches..."
rm -rf "$BUILD_DIR"

echo "📂 Making build folder..."
mkdir -p "$BUILD_DIR"

echo "📝 Configuring NetClient..."
cmake -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B "$BUILD_DIR"
if [ $? -ne 0 ]; then
    echo "❌ CMake configuration failed!"
    exit 1
fi

echo "🔨 Building NetClient..."
cmake --build "$BUILD_DIR" --config Release
if [ $? -ne 0 ]; then
    echo "❌ Build failed!"
    exit 1
fi

echo "✅ Build complete! NetClientTest is in $BUILD_DIR/bin" 