
echo off

set system=%1
set ctools=%2
set configuration=%3
if "%configuration%" == "" set configuration=debug

rem echo ctools: %ctools%

set BUILDCFG=%system%_%ctools%_%configuration%
set BUILDCFG=%system%_%ctools%_%configuration%

set shacira=e:/usr/prj/Shacira
set qt=%shacira%/Targ/Tools/%ctools%/qt3
set QTDIR=%qt%
set QTVERSION=337
set QMAKESPEC=local
set omniorb=%shacira%/Targ/Tools/%ctools%/omniORB4
set ORBDIR=%omniorb%
set PYTHONPATH=%omniorb%/lib/python
set msys=%shacira%/Targ/Tools/gnu/msys
set mingw=%shacira%/Targ/Tools/gnu/mingw

set vstudio=c:/Programme/Microsoft Visual Studio
set msdev=%vstudio%/Common/MSDev98/Bin
set vcpp=%vstudio%/VC98/Bin
set mstools=%vstudio%/Common/Tools/WinNT

set PATH=c:/windows/system32;%mingw%/bin;%msys%/bin;%shacira%/Targ;%shacira%/Targ/Tools/%ctools%;%qt%/bin;%qt%/bin/designer;%omniorb%/bin;%msdev%;%vcpp%;%mstools%

PROMPT $P: %ctools%$G


