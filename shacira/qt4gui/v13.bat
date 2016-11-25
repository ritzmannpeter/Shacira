junction -d omniORB
junction omniORB omniORB-3.0.4
junction -d Shacira
junction Shacira Shacira.V_1_3_0

xcopy %QTDIR%\plugins\designer\apcwidgets.* %QTDIR%\plugins\designer\v14 /d /Y
xcopy %QTDIR%\plugins\designer\q3_cwidget_plugin.* %QTDIR%\plugins\designer\v14 /d /Y
xcopy %QTDIR%\plugins\designer\q3_kbdlayout_plugin.* %QTDIR%\plugins\designer\v14 /d /Y
xcopy %QTDIR%\plugins\designer\q3_keypad_plugin.* %QTDIR%\plugins\designer\v14 /d /Y
xcopy %QTDIR%\plugins\designer\mosaicwidgets.* %QTDIR%\plugins\designer\v13 /d /Y
xcopy %QTDIR%\plugins\designer\nwidgets.* %QTDIR%\plugins\designer\v13 /d /Y
xcopy %QTDIR%\plugins\designer\pvwidgets.* %QTDIR%\plugins\designer\v13 /d /Y
xcopy %QTDIR%\plugins\designer\pmwidgets.* %QTDIR%\plugins\designer\v13 /d /Y
xcopy %QTDIR%\plugins\designer\cwidgets.* %QTDIR%\plugins\designer\v13 /d /Y
xcopy %QTDIR%\plugins\designer\qt_plugin_kbdlayouts.* %QTDIR%\plugins\designer\v13 /d /Y
xcopy %QTDIR%\plugins\designer\qt_plugin_keypads.* %QTDIR%\plugins\designer\v13 /d /Y

del %QTDIR%\plugins\designer\apcwidgets.*
del %QTDIR%\plugins\designer\q3_cwidget_plugin.*
del %QTDIR%\plugins\designer\q3_kbdlayout_plugin.*
del %QTDIR%\plugins\designer\q3_keypad_plugin.*

xcopy %QTDIR%\plugins\designer\v13 %QTDIR%\plugins\designer /d /Y

