

patches for uic3

converter.patch:

>cd %QTDIR%\src\tools\uic3
>patch converter.cpp converter.patch
rebuild qt uic3:
>qmake
>nmake release

gnu utilitiy patch.exe can be found in patchutils
create patch files with diff.exe


