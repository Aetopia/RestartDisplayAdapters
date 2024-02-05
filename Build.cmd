@echo off
cd "%~dp0"
windres -i .rc -o .o
gcc -Os -s -nostdlib -mwindows WinMain.c .o -lSetupapi -lKernel32 -o RestartDisplayAdapters.exe
del .o
upx --best --ultra-brute RestartDisplayAdapters.exe