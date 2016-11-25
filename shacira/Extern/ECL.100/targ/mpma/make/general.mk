#
# this makefile contains general constant definitions
#

empty :=
colon := ;
space := $(empty) $(empty)

#.SUFFIXES: .asm

# standard dependencies and commands for library generation
#
%.o: %.c
	$(stdcc)
%.o: %.cpp
	$(stdcxx)
%.o: %.cc
	$(stdcxx)
%.o: %.asm
	$(stdas)
%.o: %.s
	$(stdas)
%.exe: %.o
	$(stdld)

# dependencies and commands for library generation,
# source and target files in different directories
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(stdcc)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(stdcxx)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(stdcxx)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	$(stdas)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	$(stdas)
$(OBJ_DIR)/%.exe: $(SRC_DIR)/%.o
	$(stdld)

# Project related definitions
#
# PROJECT library source directories
#
PROJECT_LIB_DIRS:=$(PROJECT_ROOT)/lib/$(PLATFORM)
#
# PROJECT Library target directory
#
PROJECT_LIB_DIR:=$(PROJECT_ROOT)/lib/$(PLATFORM)
#
# PROJECT library names
#
PROJECT_LIBS:=ls2i PA150 ADDIDATA OPC WTOPCSvr
#
# PROJECT include directories
#
PROJECT_INCLUDES:=../../../../src
#
# PROJECT Binary directory
#
PROJECT_BIN_DIR:=$(PROJECT_ROOT)$/bin/$(PLATFORM)
#


# ORB related definitions
#
# ORB library source directories
#
ifndef ORB_BASE
ORB_BASE:=e:/usr/bin/omniorb.304
endif
#
ORB_LIB_DIRS:=$(ORB_BASE)/lib/$(PLATFORM)
#
# ORB library names
#
ORB_LIBS:=omnithread2_rt omniORB304_rt omniDynamic304_rt
#
# ORB include directories
#
ORB_INCLUDES:=$(ORB_BASE)/include $(ORB_BASE)/include/omniORB3
#

# STL related definitions
#
# STL library source directories
#
STL_BASE:=$(PROJECT_ROOT)/STL/stlport
#
STL_LIB_DIRS:=
#
# STL library names
#
STL_LIBS:=stlport_vc5_debug_static
#
# STL include directories
#
STL_INCLUDES:= $(STL_BASE) $(STL_BASE)/old_hp
#

# ECL related definitions
#
# ECL library source directories
#
ECL_BASE:=$(PROJECT_ROOT)/ECL
#
#ECL_LIB_DIRS:=$(ECL_BASE)/lib/$(PLATFORM)
#
# ECL library names
#
ECL_LIBS:=ecl
#
# ECL include directories
#
ECL_INCLUDES:= $(ECL_BASE)/src
#

# list of all used library directories
#
LIB_DIRS:=. $(PROJECT_LIB_DIRS) $(ORB_LIB_DIRS) $(ECL_LIB_DIRS)
#
# list of all used libraries
#
LIBS:=$(PROJECT_LIBS) $(ORB_LIBS) $(ECL_LIBS)
#
# list of all include directories
#
INCLUDES:=. $(PROJECT_INCLUDES) $(ORB_INCLUDES) $(STL_INCLUDES) $(ECL_INCLUDES)
#

# hook for users
#
.PHONY: all
#.PHONY: libraries
#.PHONY: binaries
#.PHONY: resources
.PHONY: clean

all: libraries binaries resources

#all: $(_TARGET_LIBRARY)

#$(_TARGET_LIBRARY): $(_LIBRARY_SOURCE_LIST)
#	$(createlib)

#clean: $(_TARGET_LIBRARY) $(_LIBRARY_SOURCE_LIST)
#	$(stdclean)
	
test:
	echo  $(libraries) $(binaries) $(resources)
#	echo $(_TARGET_LIBRARY)
#	echo $(_LIB_PATH)
#	echo $(_INPUT_LIBS)
#	echo $(_INCLUDE_PATH)
#	echo $(inslib)
#	echo $(createlib)
#	echo $(stdcpp)
#	$(stdcc)
#	echo $(stdcxx)
#	echo $(stdas)
#	echo $(stdld)

