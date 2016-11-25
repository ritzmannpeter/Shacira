@echo off
setlocal

if "%PROJECT_TOP%"=="" set PROJECT_TOP=f:\proj\host\ls2i\src\ecl\targ\mpma

if exist %PROJECT_TOP%\bin\setenv.bat goto ok
   echo PROJECT_TOP variable not set correctly!
   echo Terminating without having anything done...
   goto end
:ok

echo.
echo Setting environment for compiling the ECL class library...

cd /d %PROJECT_TOP%
set PATH=%PATH%;%PROJECT_TOP%;bin\win32
call vcvars32.bat

echo.

cmd

:end
endlocal
