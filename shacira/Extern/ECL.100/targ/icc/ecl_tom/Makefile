#
# MAKEFILE
# ========
# Make ECL_TOM
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

MYOBJ           = et_tomate.obj \
                  et_tools.obj \
                  et_concli.obj \
                  et_conser.obj

MYLIB           = $(LIBDIR)\ecl_base.lib

!INCLUDE ..\..\MAKEHEAD.ICC

#
# DEFAULT RULE
#

default:        release

release:        $(DLLDIR)\ecl_tom.dll \
                $(LIBDIR)\ecl_tom.lib \
                $(BINDIR)\remcon.exe

clean:
        @if exist *.obj del *.obj
        @if exist *.dll del *.dll
        @if exist *.lib del *.lib
        @if exist *.exe del *.exe


#
# COMPILE RULES
#

et_tomate.obj:  et_tomate.cpp   et_tomate.hpp                   \
                                $(ECLDIR)\base\eb_thread.hpp    \
                                $(ECLDIR)\base\eb_except.hpp    \
                                $(ECLDIR)\base\eb_base.hpp

et_tools.obj:   et_tools.cpp    et_tools.hpp                    \
                                et_tomate.hpp                   \
                                $(ECLDIR)\base\eb_thread.hpp    \
                                $(ECLDIR)\base\eb_except.hpp    \
                                $(ECLDIR)\base\eb_base.hpp

et_concli.obj:  et_concli.cpp   et_concli.hpp                   \
                                et_conser.hpp                   \
                                et_tomate.hpp                   \
                                $(ECLDIR)\base\eb_msg.hpp       \
                                $(ECLDIR)\base\eb_str.hpp       \
                                $(ECLDIR)\base\eb_sema.hpp      \
                                $(ECLDIR)\base\eb_ring.hpp      \
                                $(ECLDIR)\base\eb_queue.hpp     \
                                $(ECLDIR)\base\eb_npipe.hpp     \
                                $(ECLDIR)\base\eb_err.hpp       \
                                $(ECLDIR)\base\eb_thread.hpp    \
                                $(ECLDIR)\base\eb_except.hpp    \
                                $(ECLDIR)\base\eb_base.hpp

et_conser.obj:  et_conser.cpp   et_conser.hpp                   \
                                et_concli.hpp                   \
                                et_tomate.hpp                   \
                                $(ECLDIR)\base\eb_msg.hpp       \
                                $(ECLDIR)\base\eb_str.hpp       \
                                $(ECLDIR)\base\eb_sema.hpp      \
                                $(ECLDIR)\base\eb_ring.hpp      \
                                $(ECLDIR)\base\eb_queue.hpp     \
                                $(ECLDIR)\base\eb_npipe.hpp     \
                                $(ECLDIR)\base\eb_err.hpp       \
                                $(ECLDIR)\base\eb_thread.hpp    \
                                $(ECLDIR)\base\eb_except.hpp    \
                                $(ECLDIR)\base\eb_base.hpp

remcon.obj:     remcon.cpp      et_concli.hpp                   \
                                $(ECLDIR)\base\eb_msg.hpp       \
                                $(ECLDIR)\base\eb_str.hpp       \
                                $(ECLDIR)\base\eb_sema.hpp      \
                                $(ECLDIR)\base\eb_ring.hpp      \
                                $(ECLDIR)\base\eb_queue.hpp     \
                                $(ECLDIR)\base\eb_npipe.hpp     \
                                $(ECLDIR)\base\eb_err.hpp       \
                                $(ECLDIR)\base\eb_thread.hpp    \
                                $(ECLDIR)\base\eb_except.hpp    \
                                $(ECLDIR)\base\eb_base.hpp


#
# BIND RULES
#

remcon.exe:     $(LIBDIR)\ecl_base.lib  \
                ecl_tom.lib             \
                remcon.obj
	$(LN) -Gm+ -Ti+ -Tl+ -Q -Tdp -Ft- -Gd+ remcon.obj $(LINKLIB) ecl_tom.lib remcon.def


!IF $(MK_MAKEDLL) > 0

ecl_tom.dll : $(MYOBJ) ecl_tom.def
        $(LN) $(CL_OPT) -Ge- $(LINKOBJ) -Fe $*.dll $(LINKLIB) ecl_tom.def

ecl_tom.lib : ecl_tom.dll
        $(IMPLIB) $*.lib $*.dll

!ELSE

ecl_tom.lib : $(MYOBJ)
        $(LB) $* -+$(?: = -+);

!ENDIF


#
# COPY RULES
#

$(DLLDIR)\ecl_tom.dll : ecl_tom.dll
        ! copy $? $(DLLDIR)

$(LIBDIR)\ecl_tom.lib : ecl_tom.lib
        ! copy $? $(LIBDIR)

$(BINDIR)\remcon.exe : remcon.exe
        ! copy $? $(BINDIR)

