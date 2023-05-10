@echo off

@set "Png2Dmp=%~dp0/../../EventAssembler/Tools/Png2Dmp.exe"

@cd %~dp0/PNG

@dir *.png /b > png.txt

@for /f "tokens=*" %%m in (png.txt) do ("%Png2Dmp%" "%%m" --lz77)

@del png.txt

@cd %~dp0

@copy "%~dp0PNG\*.dmp" "%~dp0DMP" > nul

@del "%~dp0PNG\*.dmp"

echo Done!

pause