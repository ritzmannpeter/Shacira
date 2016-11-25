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
SRC_DIR:=../../../../src/base
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
TARGET_LIBRARY:=$(PROJECT_ROOT)/Lib/$(PLATFORM)\ecl_base
LIBRARY_SOURCE_LIST:=eb_array \
                     eb_base \
                     eb_bprintf \
                     eb_clip \
                     eb_cmdarg \
                     eb_collect \
                     eb_dde \
                     eb_docview \
                     eb_elo \
                     eb_eloex \
                     eb_err \
                     eb_event \
                     eb_except \
                     eb_file \
                     eb_geo2d \
                     eb_list \
                     eb_map \
                     eb_math \
                     eb_msg \
                     eb_npipe \
                     eb_object \
                     eb_osver \
                     eb_process \
                     eb_prof \
                     eb_queue \
                     eb_res \
                     eb_ring \
                     eb_sema \
                     eb_shmem \
                     eb_str \
                     eb_thread \
                     eb_time

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
$(OBJ_DIR)/eb_array.o:   $(SRC_DIR)/eb_array.cpp
$(OBJ_DIR)/eb_base.o:    $(SRC_DIR)/eb_base.cpp
$(OBJ_DIR)/eb_bprintf.o: $(SRC_DIR)/eb_bprintf.cpp
$(OBJ_DIR)/eb_clip.o:    $(SRC_DIR)/eb_clip.cpp
$(OBJ_DIR)/eb_cmdarg.o:  $(SRC_DIR)/eb_cmdarg.cpp
$(OBJ_DIR)/eb_collect.o: $(SRC_DIR)/eb_collect.cpp
$(OBJ_DIR)/eb_dde.o:     $(SRC_DIR)/eb_dde.cpp
$(OBJ_DIR)/eb_docview.o: $(SRC_DIR)/eb_docview.cpp
$(OBJ_DIR)/eb_elo.o:     $(SRC_DIR)/eb_elo.cpp
$(OBJ_DIR)/eb_eloex.o:   $(SRC_DIR)/eb_eloex.cpp
$(OBJ_DIR)/eb_err.o:     $(SRC_DIR)/eb_err.cpp
$(OBJ_DIR)/eb_event.o:   $(SRC_DIR)/eb_event.cpp
$(OBJ_DIR)/eb_except.o:  $(SRC_DIR)/eb_except.cpp
$(OBJ_DIR)/eb_file.o:    $(SRC_DIR)/eb_file.cpp
$(OBJ_DIR)/eb_geo2d.o:   $(SRC_DIR)/eb_geo2d.cpp
$(OBJ_DIR)/eb_list.o:    $(SRC_DIR)/eb_list.cpp
$(OBJ_DIR)/eb_map.o:     $(SRC_DIR)/eb_map.cpp
$(OBJ_DIR)/eb_math.o:    $(SRC_DIR)/eb_math.cpp
$(OBJ_DIR)/eb_msg.o:     $(SRC_DIR)/eb_msg.cpp
$(OBJ_DIR)/eb_npipe.o:   $(SRC_DIR)/eb_npipe.cpp
$(OBJ_DIR)/eb_object.o:  $(SRC_DIR)/eb_object.cpp
$(OBJ_DIR)/eb_osver.o:   $(SRC_DIR)/eb_osver.cpp
$(OBJ_DIR)/eb_process.o: $(SRC_DIR)/eb_process.cpp
$(OBJ_DIR)/eb_prof.o:    $(SRC_DIR)/eb_prof.cpp
$(OBJ_DIR)/eb_queue.o:   $(SRC_DIR)/eb_queue.cpp
$(OBJ_DIR)/eb_res.o:     $(SRC_DIR)/eb_res.cpp
$(OBJ_DIR)/eb_ring.o:    $(SRC_DIR)/eb_ring.cpp
$(OBJ_DIR)/eb_sema.o:    $(SRC_DIR)/eb_sema.cpp
$(OBJ_DIR)/eb_shmem.o:   $(SRC_DIR)/eb_shmem.cpp
$(OBJ_DIR)/eb_str.o:     $(SRC_DIR)/eb_str.cpp
$(OBJ_DIR)/eb_thread.o:  $(SRC_DIR)/eb_thread.cpp
$(OBJ_DIR)/eb_time.o:    $(SRC_DIR)/eb_time.cpp
	$(stdcxx)

