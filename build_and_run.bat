@echo off
chcp 65001 >nul

call build.bat

echo.
call run.bat

echo FINISHED
