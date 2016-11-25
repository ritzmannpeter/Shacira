@echo off
setlocal

set DEF_DIR=c:\usr\bin\tools
set PP_DIR=%~dp0%
set PP_EXE=%PP_DIR%\pp.exe

if not exist %PP_DIR%\ppChead.pre set PP_DIR=%DEF_DIR%
if not exist %PP_DIR%\pp.exe set PP_EXE=pp

set APP_MSG_FILE=%PP_DIR%\ppError.msg
set PRE_FILE=%PP_DIR%\ppChead.pre

IF not exist %1.c GOTO NOC
  %PP_EXE% -o%1.h  %PRE_FILE% %1.c
  goto END
:NOC
IF not exist %1.cpp goto NOCPP
  %PP_EXE% -o%1.hpp %PRE_FILE% %1.cpp
  goto END
:NOCPP
  echo [BAT] Aufruf: MAKEHEAD filename
:END
