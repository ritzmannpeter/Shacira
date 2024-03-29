
make file generated by Autoconfig: dont edit

# build definitions
config = debug
compiler = gcc
system = linux
target_type = executable
project_defs = -D_NO_QT_

# include general build instructions
include $(SHACIRADIR)/Targ/platforms/linux_gcc.defs

# include dependencies
-include linux_gcc_debug.dep

A_I_PATHS = \
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
	-I../../../Extern/STYX/src/modstd
A_GEN_HEADERS =

A_L_PATHS = \
	-L"../styx/linux_gcc_debug" \
	-L"/prj/omniORB-4.0.7/lib" \
	-L"../ecl/linux_gcc_debug" \
	-L"../ccs/linux_gcc_debug"
A_LIBS = \
	-lccs \
	-lecl \
	-lomniDynamic4 \
	-lomniORB4 \
	-lomnithread \
	-lstyx
A_OBJECTS = \
	linux_gcc_debug/InfCons.o
A_TARGETS = \
	linux_gcc_debug/InfCons.o

.PHONY: linux_gcc_debug all clean


dependencies:
	$(make) -C ../ccs -flinux_gcc_debug.mk all

clean:
	-rm $(A_TARGETS)

linux_gcc_debug/icons: $(A_TARGETS)
	$(link)

all: dependencies linux_gcc_debug $(A_TARGETS) linux_gcc_debug/icons

linux_gcc_debug: linux_gcc_debug.mk
	$(mkdir) $@

linux_gcc_debug/InfCons.o: ../../../Src/Apps/InfCons/InfCons.cpp
	$(cpp)

