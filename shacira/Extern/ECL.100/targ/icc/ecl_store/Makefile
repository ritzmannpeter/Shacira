#
# MAKEFILE
# ========
# Make ECL_STOR
#

#
# Configuration section
#

MK_CPP          = 1             # Compile C++?
MK_USEDLL       = 1             # Use dynamic libraries
MK_MAKEDLL      = 1             # Build dynamic libraries
MK_DEBUG        = 1             # Want debug infos?
MK_PROFILE      = 1             # Want profile hooks?
MK_OPTIMIZE     = 0             # Optimize code?
MK_PEDANTIC     = 0             # Want pedantic compiler?
MK_REVISION     = 1.0           # Revision number for RCS
MK_TRY          = 0             # Test makefile?
MK_DBGMEM       = 0             # Trace dynamic memory handling

MYOBJ           = es_base.obj \
                  es_store.obj \
                  es_var.obj

MYLIB           = $(LIBDIR)\ecl_base.lib

!INCLUDE ..\..\MAKEHEAD.ICC


#
# DEFAULT RULE
#

default:        release

release:        $(DLLDIR)\ecl_stor.dll \
                $(LIBDIR)\ecl_stor.lib

clean:
        @if exist *.obj del *.obj
        @if exist *.dll del *.dll
        @if exist *.lib del *.lib


#
# COMPILE RULES
#

#*chead on*

es_base.obj:    es_base.cpp     es_base.hpp \
                                $(ECLDIR)\base\eb_base.hpp

es_store.obj:   es_store.cpp    es_store.hpp \
                                es_base.hpp \
                                $(ECLDIR)\base\eb_base.hpp \
                                $(ECLDIR)\base\eb_time.hpp

es_var.obj:     es_var.cpp      es_var.hpp \
                                es_store.hpp \
                                es_base.hpp \
                                $(ECLDIR)\base\eb_base.hpp \
                                $(ECLDIR)\base\eb_time.hpp \
                                $(ECLDIR)\base\eb_str.hpp \
                                $(ECLDIR)\base\eb_err.hpp


#*chead off*


#
# BIND RULES
#

!IF $(MK_MAKEDLL) > 0

ecl_stor.dll : $(MYOBJ) $(MYLIB) ecl_stor.def
        $(LN) $(CL_OPT) -Ge- $(LINKOBJ) -Fe $*.dll $(LINKLIB) ecl_stor.def

ecl_stor.lib : ecl_stor.dll
        $(IMPLIB) $*.lib $*.dll

!ELSE

ecl_stor.lib : $(MYOBJ)
        $(LB) $* -+$(?: = -+);

!ENDIF


#
# COPY RULES
#

$(DLLDIR)\ecl_stor.dll : ecl_stor.dll
        ! copy $? $(DLLDIR)

$(LIBDIR)\ecl_stor.lib : ecl_stor.lib
        ! copy $? $(LIBDIR)

