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

echo 📝 Configuring NetServer...
cmake -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B %BUILD_DIR%
if %ERRORLEVEL% NEQ 0 (
    echo ❌ CMake configuration failed!
    exit /b %ERRORLEVEL%
)

echo 🔨 Building NetServer...
cmake --build %BUILD_DIR% --config Release
if %ERRORLEVEL% NEQ 0 (
    echo ❌ Build failed!
    exit /b %ERRORLEVEL%
)

echo ✅ Build complete! NetServerTest is in %BUILD_DIR%\bin 