@echo off
setlocal

set PRJ=Shacira

if exist .\zipme.cmd goto ok_zipme
   echo This utility must be called from within the bin directory. You
   echo may also use the Windows explorer and double-click on this file.
   goto end
:ok_zipme

cd ..\..

if exist %PRJ%\readme.txt goto ok_root
   echo This utility assumes that the current project resides in a
   echo directory called '%PRJ%', which cannot be found.
   pause
   goto end
:ok_root

zip -r %PRJ% %PRJ%\* -x *.exe -x *.obj -x *.*~ -x *.vp? -x *.vtg -x *.pch -x *.idb -x *.pdb -x *.sbr -x *.ilk -x *.plg -x *.bsc -x *.ncb -x *.opt -x *.dll -x *.exp -x *.map -x *.aps -x *.res -x *.log -x *.00? -x *.o -x *.bpl -x */CVS/* -x */144MB/* -x *.il* -x */Debug/* -x */Release/* -x */Generated/*

:end
endlocal
