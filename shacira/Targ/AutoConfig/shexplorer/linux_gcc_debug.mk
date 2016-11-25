
make file generated by Autoconfig: dont edit

# build definitions
config = debug
compiler = gcc
system = linux
target_type = executable

# include general build instructions
include $(SHACIRADIR)/Targ/platforms/linux_gcc.defs

# include dependencies
-include linux_gcc_debug.dep

A_I_PATHS = \
	-I../../../Src/Apps/SHExplorer \
	-I. \
	-Ilinux_gcc_debug \
	-I../../../Src/GUIFramework \
	-I../../../Src/GUIFramework/QTFramework \
	-I../../../Src/GUIFramework/QTFramework/CWidgets \
	-I../../../Src/GUIFramework/QTFramework/Dialogs \
	-I../../../Src/GUIFramework/QTFramework/HTML \
	-I../../../Src/GUIFramework/QTFramework/Keypads \
	-I../guiframework/linux_gcc_debug \
	-I../../../Src \
	-I../../../Src/Include \
	-I../../../Src/Orb \
	-I../ccs/linux_gcc_debug \
	-I../../../Extern/ECL/src \
	-I/prj/omniORB-4.0.7/include \
	-I/prj/omniORB-4.0.7/include/COS \
	-I/prj/omniORB-4.0.7/include/omniORB4 \
	-I../../../Extern/STYX/src \
	-I../../../Extern/STYX/src/inc \
	-I../../../Extern/STYX/src/libbase \
	-I../../../Extern/STYX/src/modstd \
	-I/prj/qt3/include \
	-I/prj/qt3/makespecs/default
A_GEN_HEADERS = \
	linux_gcc_debug/ExplorerForm.h

A_L_PATHS = \
	-L"/prj/qt3/lib" \
	-L"../styx/linux_gcc_debug" \
	-L"/prj/omniORB-4.0.7/lib" \
	-L"../ecl/linux_gcc_debug" \
	-L"../ccs/linux_gcc_debug" \
	-L"../guiframework/linux_gcc_debug"
A_LIBS = \
	-lguiframework \
	-lccs \
	-lecl \
	-lomniDynamic4 \
	-lomniORB4 \
	-lomnithread \
	-lstyx \
	-lqt-mt
A_OBJECTS = \
	linux_gcc_debug/CServerList.o \
	linux_gcc_debug/ExplorerForm.o \
	linux_gcc_debug/SHExplorer.o \
	linux_gcc_debug/moc_CServerList.o \
	linux_gcc_debug/moc_ExplorerForm.o
A_TARGETS = \
	linux_gcc_debug/ExplorerForm.h \
	linux_gcc_debug/ExplorerForm.cpp \
	linux_gcc_debug/moc_CServerList.cpp \
	linux_gcc_debug/moc_ExplorerForm.cpp \
	linux_gcc_debug/CServerList.o \
	linux_gcc_debug/ExplorerForm.o \
	linux_gcc_debug/SHExplorer.o \
	linux_gcc_debug/moc_CServerList.o \
	linux_gcc_debug/moc_ExplorerForm.o

.PHONY: linux_gcc_debug all clean


dependencies:
	$(make) -C ../guiframework -flinux_gcc_debug.mk all

clean:
	-rm $(A_TARGETS)

linux_gcc_debug/shexplorer: $(A_TARGETS)
	$(link)

all: dependencies linux_gcc_debug $(A_TARGETS) linux_gcc_debug/shexplorer

linux_gcc_debug: linux_gcc_debug.mk
	$(mkdir) $@

linux_gcc_debug/moc_ExplorerForm.o: linux_gcc_debug/moc_ExplorerForm.cpp
	$(cpp)

linux_gcc_debug/ExplorerForm.o: linux_gcc_debug/ExplorerForm.cpp
	$(cpp)

linux_gcc_debug/moc_ExplorerForm.cpp: linux_gcc_debug/ExplorerForm.h
	$(QTDIR)/bin/moc linux_gcc_debug/ExplorerForm.h -olinux_gcc_debug/moc_ExplorerForm.cpp

linux_gcc_debug/moc_CServerList.o: linux_gcc_debug/moc_CServerList.cpp
	$(cpp)

linux_gcc_debug/CServerList.o: ../../../Src/Apps/SHExplorer/CServerList.cpp
	$(cpp)

linux_gcc_debug/moc_CServerList.cpp: ../../../Src/Apps/SHExplorer/CServerList.h
	$(QTDIR)/bin/moc ../../../Src/Apps/SHExplorer/CServerList.h -olinux_gcc_debug/moc_CServerList.cpp

linux_gcc_debug/ExplorerForm.cpp: ../../../Src/Apps/SHExplorer/ExplorerForm.ui
	$(QTDIR)/bin/uic ../../../Src/Apps/SHExplorer/ExplorerForm.ui -o linux_gcc_debug/ExplorerForm.h
	$(QTDIR)/bin/uic ../../../Src/Apps/SHExplorer/ExplorerForm.ui -i linux_gcc_debug/ExplorerForm.h -o linux_gcc_debug/ExplorerForm.cpp
linux_gcc_debug/ExplorerForm.h: ../../../Src/Apps/SHExplorer/ExplorerForm.ui
	$(QTDIR)/bin/uic ../../../Src/Apps/SHExplorer/ExplorerForm.ui -o linux_gcc_debug/ExplorerForm.h
	$(QTDIR)/bin/uic ../../../Src/Apps/SHExplorer/ExplorerForm.ui -i linux_gcc_debug/ExplorerForm.h -o linux_gcc_debug/ExplorerForm.cpp

linux_gcc_debug/SHExplorer.o: ../../../Src/Apps/SHExplorer/SHExplorer.cpp
	$(cpp)

