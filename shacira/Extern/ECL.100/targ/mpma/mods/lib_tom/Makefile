# directory specific makefile
#

# include environment specific definitions
#
include $(PROJECT_TOP)/Make/env.mk
#

# directories
#
CURRENT=$PWD
OBJ_DIR:=.
SRC_DIR:=../../../../src/tom
#

# here is the place to add definitions that are subsequently interpreted within
# general.mk and $(PLATFORM).mk
#
INCLUDES_EXTENSION:=../
#
LIB_DIRS:=$(LIB_DIRS)
LIBS:=$(LIBS)
INCLUDES:=$(INCLUDES)
#
ARFLAGS+=
CPPFLAGS+=
CFLAGS+=
COPTIONS+=
CXXFLAGS+=
ASFLAGS+=
LDFLAGS+=
#

# include general definitions
#
include $(PROJECT_ROOT)/Make/general.mk
#

# here is the place to list library file dependencies
#
# list of objects that should be placed in the library with name $(TARGET_LIBRARY)
#
TARGET_LIBRARY:=$(PROJECT_ROOT)/Lib/$(PLATFORM)\ecl_tom
LIBRARY_SOURCE_LIST:=et_con et_concli et_conser et_tomate et_tools

#
#
BINARY_SOURCE_LIST:=
TARGET_BINARY:=
#
BINARY_SOURCE_LIST_1:=
TARGET_BINARY_1:=
#

# include platform specific definitions
#
include $(PROJECT_ROOT)/Make/platform.mk
#

libraries: $(_TARGET_LIBRARIES)
binaries: $(_TARGET_BINARIES)
resources: $(_TARGET_RESOURCES)

$(_TARGET_LIBRARY): $(_LIBRARY_SOURCE_LIST)
	$(createlib)
$(_TARGET_LIBRARY_1): $(_LIBRARY_SOURCE_LIST_1)
	$(inslib)
$(_TARGET_LIBRARY_2): $(_LIBRARY_SOURCE_LIST_2)
	$(inslib)
	
$(_TARGET_BINARY): $(_BINARY_SOURCE_LIST)
$(_TARGET_BINARY_1): $(_BINARY_SOURCE_LIST_1)
$(_TARGET_BINARY_2): $(_BINARY_SOURCE_LIST_2)
	
clean: $(_LIBRARY_SOURCE_LISTS) $(_TARGET_BINARIES) $(_BINARY_SOURCE_LISTS) $(_TARGET_RESOURCES) $(_RESOURCE_SOURCE_LISTS)
	echo $^
#       $(stdclean)

# dependencies for this module
#
$(OBJ_DIR)/eb_con.o:     $(SRC_DIR)/et_con.cpp
$(OBJ_DIR)/eb_concli.o:  $(SRC_DIR)/et_concli.cpp
$(OBJ_DIR)/eb_conser.o:  $(SRC_DIR)/et_conser.cpp
$(OBJ_DIR)/eb_tomate.o:  $(SRC_DIR)/et_tomate.cpp
$(OBJ_DIR)/eb_tools.o:   $(SRC_DIR)/et_tools.cpp
	$(stdcxx)

