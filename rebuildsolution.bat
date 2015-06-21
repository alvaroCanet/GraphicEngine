@echo off
rd /s/q build
premake5.exe --file=premake5.lua vs2012
pause
