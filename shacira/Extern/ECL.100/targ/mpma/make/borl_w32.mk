#		platform specific tools configuration and defaults
#

EXE_SUFFIX=.exe
LIB_SUFFIX=.lib
OBJ_SUFFIX=.obj

# L I B R A R I E S
#
# system specific library directories
#
SYSTEM_LIBDIRS:=
#
# system specific library names
#
SYSTEM_LIBS:=kernel32 user32 gdi32 winspool comdlg32 advapi32 wsock32 shell32 ole32 uuid oleaut32 odbc32 odbccp32
#

# I N C L U D E S
#
# platform specific include directories
#
SYSTEM_INCLUDES:=
#


# this is an export chapter that offers lists and targets
# system specific representation
#
_LIB_DIRS:=$(LIB_DIRS) $(SYSTEM_LIB_DIRS) $(LIB_DIRS_EXTENSION)
_LIB_PATH:=$(patsubst %,-libpath:%, $(LIB_DIRS))

_LIBS:=$(LIBS) $(SYSTEM_LIBS) $(LIBS_EXTENSION)
_INPUT_LIBS:=$(patsubst %,%$(LIB_SUFFIX), $(_LIBS))

_INCLUDES:=$(INCLUDES) $(SYSTEM_INCLUDES) $(INCLUDES_EXTENSION)
_INCLUDE_PATH:=$(patsubst %,-I%, $(_INCLUDES))


_TARGET_LIBRARY:=$(patsubst %,%$(LIB_SUFFIX), $(TARGET_LIBRARY))
_LIBRARY_SOURCE_LIST:=$(patsubst %,%$(OBJ_SUFFIX), $(LIBRARY_SOURCE_LIST))
_TARGET_BINARY:=$(patsubst %,%$(EXE_SUFFIX), $(TARGET_BINARY))
_BINARY_SOURCE_LIST:=$(patsubst %,%$(OBJ_SUFFIX), $(BINARY_SOURCE_LIST))
_RESOURCE_SOURCE_LIST:=$(patsubst %,%$(OBJ_SUFFIX), $(RESOURCE_SOURCE_LIST))

_TARGET_LIBRARY_1:=$(patsubst %,%$(LIB_SUFFIX), $(TARGET_LIBRARY_1))
_LIBRARY_SOURCE_LIST_1:=$(patsubst %,%$(OBJ_SUFFIX), $(LIBRARY_SOURCE_LIST_1))
_TARGET_BINARY_1:=$(patsubst %,%$(EXE_SUFFIX), $(TARGET_BINARY_1))
_BINARY_SOURCE_LIST_1:=$(patsubst %,%$(OBJ_SUFFIX), $(BINARY_SOURCE_LIST_1))
_RESOURCE_SOURCE_LIST_1:=$(patsubst %,%$(OBJ_SUFFIX), $(RESOURCE_SOURCE_LIST_1))

_TARGET_LIBRARY_2:=$(patsubst %,%$(LIB_SUFFIX), $(TARGET_LIBRARY_2))
_LIBRARY_SOURCE_LIST_2:=$(patsubst %,%$(OBJ_SUFFIX), $(LIBRARY_SOURCE_LIST_2))
_TARGET_BINARY_2:=$(patsubst %,%$(EXE_SUFFIX), $(TARGET_BINARY_2))
_BINARY_SOURCE_LIST_2:=$(patsubst %,%$(OBJ_SUFFIX), $(BINARY_SOURCE_LIST_2))
_RESOURCE_SOURCE_LIST_2:=$(patsubst %,%$(OBJ_SUFFIX), $(RESOURCE_SOURCE_LIST_2))

_TARGET_LIBRARIES:=$(_TARGET_LIBRARY)  $(_TARGET_LIBRARY_1)  $(_TARGET_LIBRARY_2)
_TARGET_BINARIES:=$(_TARGET_BINARY) $(_TARGET_BINARY_1) $(_TARGET_BINARY_2)
_TARGET_RESOURCES:=$(_TRAGET_RESOURCE) $(_TARGET_RESOURCE_1) $(_TARGET_RESOURCE_2)

_LIBRARY_SOURCE_LISTS:=$(_LIBRARY_SOURCE_LIST)  $(_LIBRARY_SOURCE_LIST_1)  $(_LIBRARY_SOURCE_LIST_2)
_BINARY_SOURCE_LISTS:=$(_BINARY_SOURCE_LIST) $(_BINARY_SOURCE_LIST_1) $(_BINARY__SOURCE_LIST_2)
_RESOURCE_SOURCE_LISTS:=$(_RESOURCE_SOURCE_LIST) $(_RESOURCE_SOURCE_LIST_1) $(_RESOURCE_SOURCE_LIST_2)


# library manager
#
ARFLAGS=
AR=lib -nologo
AROUT=/OUT:
define createlib
	$(AR) $(ARFLAGS) $(AROUT)$@ $^
endef
define inslib
	$(AR) $(ARFLAGS) $(AROUT)$@ $@ $^
endef
#

# C - preprocessor
#
CPPFLAGS+=
CPP=cl -E
#

# C - compiler
#
COPTIONS+=-D__MSCPP__ -D__x86__ -D__WIN32__ -D__STL_NO_NEW_IOSTREAMS
CFLAGS+= -Zi -W3
CC=cl -c -nologo -GX -MTd -Zp1
CCOUT=-Fo
define stdcc
	$(CC) $(CPPFLAGS) $(CFLAGS) $(COPTIONS) $(_INCLUDE_PATH) $(CCOUT)$@ $<
endef

# C++ - compiler
#
CXXFLAGS+=
# it is vital to get omniORB applications running to not specify -Zp1 !
CXX=cl -c -nologo -GX -MTd 
define stdcxx
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) $(COPTIONS) $(_INCLUDE_PATH) $(CCOUT)$@ $<
endef
#

# assembler
#
ASOUT=-fo
ASFLAGS=-mf
AS=wasm
define stdas
	$(AS) $(ASFLAGS) $(ASOUT)$@ $<
endef
#

# linker
#
LDFLAGS+= /DEBUG
LD=link -nologo /FORCE:MULTIPLE /MAP
LDOUT=/OUT:
define stdld
	$(LD) $(LDFLAGS) $(_LIB_PATH) $(LDOUT)$@ $^ $(_INPUT_LIBS)
endef

# parser generator
#
YACCFLAGS=--yacc
YACC=bison
define stdyacc
	$(YACC) $(YACCFLAGS) $^
endef
#

#	lexical analysis
#
LEXFLAGS=
LEX=flex
define stdlex
	$(LEX) $(LEXFLAGS) $^
endef

# clean
#
CLEAN=-rm
RM=del
CP=copy
define stdclean
	$(CLEAN) *.pdb *.map $^
endef



