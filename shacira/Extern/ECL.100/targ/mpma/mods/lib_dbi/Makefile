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
SRC_DIR:=../../../../src/dbi
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
TARGET_LIBRARY:=$(PROJECT_ROOT)/Lib/$(PLATFORM)\ecl_dbi
LIBRARY_SOURCE_LIST:=edb_cursor edb_cursor_ex edb_database edb_dictionary \
                     edb_dml edb_field edb_function edb_query edb_record \
                     edb_row edb_sql edb_transaction edb_var

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
$(OBJ_DIR)/edb_cursor.o:      $(SRC_DIR)/edb_cursor.cpp
$(OBJ_DIR)/edb_cursor_ex.o:   $(SRC_DIR)/edb_cursor_ex.cpp
$(OBJ_DIR)/edb_database.o:    $(SRC_DIR)/edb_database.cpp
$(OBJ_DIR)/edb_dictionary.o:  $(SRC_DIR)/edb_dictionary.cpp
$(OBJ_DIR)/edb_dml.o:         $(SRC_DIR)/edb_dml.cpp
$(OBJ_DIR)/edb_field.o:       $(SRC_DIR)/edb_field.cpp
$(OBJ_DIR)/edb_function.o:    $(SRC_DIR)/edb_function.cpp
$(OBJ_DIR)/edb_query.o:       $(SRC_DIR)/edb_query.cpp
$(OBJ_DIR)/edb_record.o:      $(SRC_DIR)/edb_record.cpp
$(OBJ_DIR)/edb_row.o:         $(SRC_DIR)/edb_row.cpp
$(OBJ_DIR)/edb_sql.o:         $(SRC_DIR)/edb_sql.cpp
$(OBJ_DIR)/edb_transaction.o: $(SRC_DIR)/edb_transaction.cpp
$(OBJ_DIR)/edb_var.o:         $(SRC_DIR)/edb_var.cpp
	$(stdcxx)

