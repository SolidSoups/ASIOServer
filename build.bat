@echo off
chcp 65001 >nul
setlocal
set "BUILD_DIR=build"

echo 🧹 Clearing caches...
if exist %BUILD_DIR% (
  rmdir /s /q %BUILD_DIR%
)

echo 📂 Making build folder...
mkdir %BUILD_DIR%

echo 📝 Configuring project and generating compile_commands.json...
cmake -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B %BUILD_DIR%

echo 🔨 Building the project...
cmake --build %BUILD_DIR% 
