@echo off
chcp 65001 >nul
setlocal

call build.bat
if %ERRORLEVEL% NEQ 0 (
    echo ❌ Build failed!
    exit /b %ERRORLEVEL%
)

echo ✅ Build successful, starting NetServerTest...
call run.bat 