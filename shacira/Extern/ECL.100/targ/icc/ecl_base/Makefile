#
# MAKEFILE
# ========
# Make ECL_BASE
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

MYOBJ           = eb_base.obj \
                  eb_bprintf.obj \
                  eb_err.obj \
                  eb_str.obj \
                  eb_time.obj \
                  eb_file.obj \
                  eb_cmdarg.obj \
                  eb_shmem.obj \
                  eb_sema.obj \
                  eb_ring.obj \
                  eb_queue.obj \
                  eb_except.obj \
                  eb_thread.obj \
                  eb_npipe.obj \
                  eb_msg.obj \
                  eb_collect.obj \
                  eb_array.obj \
                  eb_list.obj \
                  eb_map.obj \
                  eb_math.obj \
                  eb_geo2d.obj

MYLIB           =

!INCLUDE ..\..\MAKEHEAD.ICC


#
# DEFAULT RULE
#

default:        release

release:        $(DLLDIR)\ecl_base.dll \
                $(LIBDIR)\ecl_base.lib

clean:
        @if exist *.obj del *.obj
        @if exist *.dll del *.dll
        @if exist *.lib del *.lib


#
# COMPILE RULES
#

#*chead on*

eb_base.obj:    eb_base.cpp     eb_base.hpp

eb_bprintf.obj: eb_bprintf.cpp  eb_base.hpp     \
                                eb_bprintf.hpp

eb_err.obj:     eb_err.cpp      eb_base.hpp     \
                                eb_err.hpp

eb_str.obj:     eb_str.cpp      eb_base.hpp     \
                                eb_err.hpp      \
                                eb_str.hpp

eb_time.obj:    eb_time.cpp     eb_base.hpp     \
                                eb_err.hpp      \
                                eb_str.hpp      \
                                eb_time.hpp

eb_file.obj:    eb_file.cpp     eb_base.hpp     \
                                eb_err.hpp      \
                                eb_str.hpp      \
                                eb_file.hpp

eb_cmdarg.obj:  eb_cmdarg.cpp   eb_base.hpp     \
                                eb_err.hpp      \
                                eb_str.hpp      \
                                eb_file.hpp     \
                                eb_cmdarg.hpp

eb_shmem.obj:   eb_shmem.cpp    eb_base.hpp     \
                                eb_err.hpp      \
                                eb_str.hpp      \
                                eb_shmem.hpp

eb_sema.obj:    eb_sema.cpp     eb_base.hpp     \
                                eb_str.hpp      \
                                eb_sema.hpp

eb_ring.obj:    eb_ring.cpp     eb_base.hpp     \
                                eb_sema.hpp     \
                                eb_err.hpp      \
                                eb_ring.hpp

eb_queue.obj:   eb_queue.cpp    eb_base.hpp     \
                                eb_sema.hpp     \
                                eb_ring.hpp     \
                                eb_queue.hpp

eb_except.obj:  eb_except.cpp   eb_base.hpp     \
                                eb_thread.hpp   \
                                eb_except.hpp

eb_thread.obj:  eb_thread.cpp   eb_base.hpp     \
                                eb_except.hpp   \
                                eb_thread.hpp

eb_npipe.obj:   eb_npipe.cpp    eb_base.hpp     \
                                eb_sema.hpp     \
                                eb_err.hpp      \
                                eb_ring.hpp     \
                                eb_queue.hpp    \
                                eb_thread.hpp   \
                                eb_npipe.hpp

eb_msg.obj:     eb_msg.cpp      eb_base.hpp     \
                                eb_sema.hpp     \
                                eb_err.hpp      \
                                eb_ring.hpp     \
                                eb_queue.hpp    \
                                eb_thread.hpp   \
                                eb_npipe.hpp    \
                                eb_msg.hpp

eb_collect.obj: eb_collect.cpp  eb_base.hpp     \
                                eb_collect.hpp

eb_array.obj:   eb_array.cpp    eb_base.hpp     \
                                eb_collect.hpp  \
                                eb_array.hpp

eb_list.obj:    eb_list.cpp     eb_base.hpp     \
                                eb_collect.hpp  \
                                eb_list.hpp

eb_map.obj:     eb_map.cpp      eb_base.hpp     \
                                eb_collect.hpp  \
                                eb_map.hpp

eb_math.obj:    eb_math.cpp     eb_base.hpp     \
                                eb_math.hpp

eb_geo2d.obj:   eb_geo2d.cpp    eb_base.hpp     \
                                eb_array.hpp    \
                                eb_math.hpp     \
                                eb_geo2d.hpp

#*chead off*


#
# BIND RULES
#

!IF $(MK_MAKEDLL) > 0

ecl_base.dll : $(MYOBJ) ecl_base.def
        $(LN) $(CL_OPT) -Ge- $(LINKOBJ) -Fe $*.dll $(LINKLIB) ecl_base.def

ecl_base.lib : ecl_base.dll
        $(IMPLIB) $*.lib $*.dll

!ELSE

ecl_base.lib : $(MYOBJ)
        $(LB) $* -+$(?: = -+);

!ENDIF


#
# COPY RULES
#

$(DLLDIR)\ecl_base.dll : ecl_base.dll
        ! copy $? $(DLLDIR)

$(LIBDIR)\ecl_base.lib : ecl_base.lib
        ! copy $? $(LIBDIR)

