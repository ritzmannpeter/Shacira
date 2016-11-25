
STYX_INCLUDES = -Ie:/usr/prj/Shacira/Extern/STYX/src/INC -Ie:/usr/prj/Shacira/Extern/STYX/src/LIBBASE -Ie:/usr/prj/Shacira/Extern/STYX/src/MODSTD 
SHACIRA_INCLUDES = -Ie:/usr/prj/Shacira/Src -Ie:/usr/prj/Shacira/Src/Include -Ie:/usr/prj/Shacira/Src/Orb -Ie:/usr/prj/Shacira/Extern/ADDIDATA/include -Ie:/usr/prj/Shacira/Extern/FALCON/include -Ie:/usr/prj/Shacira/Extern/SIEMENS/C
GUI_INCLUDES = -Ie:/usr/prj/Shacira/Src/GUIFramework -Ie:/usr/prj/Shacira/Src/GUIFramework/QtFramework -Ie:/usr/prj/Shacira/Src/GUIFramework/QtFramework/CWidgets -Ie:/usr/prj/Shacira/Src/GUIFramework/QtFramework/Keypads -Ie:/usr/prj/Shacira/Src/GUIFramework/QtFramework/Dialogs -Ie:/usr/prj/Shacira/Src/GUIFramework/QtFramework/HTML
ECL_INCLUDES = -Ie:/usr/prj/Shacira/Extern/ECL/src
STL_INCLUDES = -Ie:/usr/prj/Shacira/Extern/STL/stlport
ORB_INCLUDES = -Ie:/usr/bin/OmniORB.304/include -Ie:/usr/bin/OmniORB.304/include/omniORB3
QT_INCLUDES = -Ie:/usr/bin/Qt.334/include

type=
type=-mno-cygwin

INCLUDES = $(SHACIRA_INCLUDES) \
            $(STYX_INCLUDES) \
            $(ORB_INCLUDES) \
            -Ie:/temp/GnuECL/shared/ecl/src \
            -Ie:/usr/bin/Qt.334/include

liba.o: liba.cpp
	g++ $(type) -c -Wno-deprecated $(INCLUDES) -o$@ $<

libb.o: libb.cpp
	g++ $(type) -c -Wno-deprecated $(INCLUDES) -o$@ $<

libc.o: libc.cpp
	g++ $(type) -c -Wno-deprecated $(INCLUDES) -o$@ $<

debug/test.o: test.cpp

#	g++ $(type) -c -Wno-deprecated $(INCLUDES) -o$@ $<

libliba.a: liba.o
	ar r $@ $<

liblibb.a: libb.o
	ar r $@ $<

liblibc.a: libc.o
	ar r $@ $<

test: debug/test.o libliba.a liblibb.a liblibc.a
	g++ $(type) $< -o$@ -L./ -lliba -llibb -llibc -lwsock32 -lqt-mt334 2>linkerrors

all: test



