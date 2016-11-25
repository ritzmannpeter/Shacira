#
# MAKEFILE
# ========
# Make ECL_DRAW
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

MYOBJ           = ed_base.obj \
                  ed_device.obj \
                  ed_space.obj \
                  ed_bitmap.obj

MYLIB           = $(LIBDIR)\ecl_base.lib

!INCLUDE ..\..\MAKEHEAD.ICC


#
# DEFAULT RULE
#

default:        release

release:        $(DLLDIR)\ecl_draw.dll \
                $(LIBDIR)\ecl_draw.lib

clean:
        @if exist *.obj del *.obj
        @if exist *.dll del *.dll
        @if exist *.lib del *.lib


#
# COMPILE RULES
#

#*chead on*

ed_base.obj:    ed_base.cpp     ed_base.hpp \
                                $(ECLDIR)\base\eb_geo2d.hpp

ed_device.obj:  ed_device.cpp   ed_device.hpp \
                                ed_base.hpp \
                                $(ECLDIR)\base\eb_geo2d.hpp \
                                $(ECLDIR)\base\eb_base.hpp

ed_space.obj:   ed_space.cpp    ed_space.hpp \
                                ed_device.hpp \
                                ed_base.hpp \
                                $(ECLDIR)\base\eb_geo2d.hpp \
                                $(ECLDIR)\base\eb_base.hpp

ed_bitmap.obj:  ed_bitmap.cpp   ed_bitmap.hpp \
                                ed_space.hpp \
                                ed_device.hpp \
                                ed_base.hpp \
                                $(ECLDIR)\base\eb_geo2d.hpp \
                                $(ECLDIR)\base\eb_base.hpp

#*chead off*


#
# BIND RULES
#

!IF $(MK_MAKEDLL) > 0

ecl_draw.dll : $(MYOBJ) ecl_draw.def
        $(LN) $(CL_OPT) -Ge- $(LINKOBJ) -Fe $*.dll $(LINKLIB) ecl_draw.def

ecl_draw.lib : ecl_draw.dll
        $(IMPLIB) $*.lib $*.dll

!ELSE

ecl_draw.lib : $(MYOBJ)
        $(LB) $* -+$(?: = -+);

!ENDIF


#
# COPY RULES
#

$(DLLDIR)\ecl_draw.dll : ecl_draw.dll
        ! copy $? $(DLLDIR)

$(LIBDIR)\ecl_draw.lib : ecl_draw.lib
        ! copy $? $(LIBDIR)

