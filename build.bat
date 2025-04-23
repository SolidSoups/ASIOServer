@echo off
chcp 65001 >nul
setlocal
set "BUILD_DIR=build"

echo 🧹 Clearing caches and stopping running processes...
taskkill /F /IM ASIOServer.exe /IM NetServerTest.exe /IM NetClientTest.exe >nul 2>&1
if exist %BUILD_DIR% (
  rmdir /s /q %BUILD_DIR%
)

echo 📂 Making build folder...
mkdir %BUILD_DIR%

echo 📝 Configuring project and generating compile_commands.json...
cmake -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B %BUILD_DIR%
if %ERRORLEVEL% NEQ 0 (
    echo ❌ CMake configuration failed!
    exit /b %ERRORLEVEL%
)

echo 🔨 Building the project...
cmake --build %BUILD_DIR% --config Release
if %ERRORLEVEL% NEQ 0 (
    echo ❌ Build failed!
    exit /b %ERRORLEVEL%
)

echo ✅ Build complete! Executables are in %BUILD_DIR%\bin
explorer.exe .\build\bin
