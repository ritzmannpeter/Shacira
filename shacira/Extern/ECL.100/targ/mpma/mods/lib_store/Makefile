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
SRC_DIR:=../../../../src/store
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
TARGET_LIBRARY:=$(PROJECT_ROOT)/Lib/$(PLATFORM)\ecl_store
LIBRARY_SOURCE_LIST:=es_base es_field es_filter es_query es_row es_store es_var

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
$(OBJ_DIR)/es_base.o:   $(SRC_DIR)/es_base.cpp
$(OBJ_DIR)/es_field.o:  $(SRC_DIR)/es_field.cpp
$(OBJ_DIR)/es_filter.o: $(SRC_DIR)/es_filter.cpp
$(OBJ_DIR)/es_query.o:  $(SRC_DIR)/es_query.cpp
$(OBJ_DIR)/es_record.o: $(SRC_DIR)/es_record.cpp
$(OBJ_DIR)/es_row.o:    $(SRC_DIR)/es_row.cpp
$(OBJ_DIR)/es_store.o:  $(SRC_DIR)/es_store.cpp
$(OBJ_DIR)/es_var.o:    $(SRC_DIR)/es_var.cpp
	$(stdcxx)

