/*----------------------------------------------------------------------------*/
/*                                                                            */
/* [syscbhdl.h]            Types of system handlers ( abort ... )             */
/*                                                                            */
/* Copyright (c) 1999 by Doelle, Manns                                        */
/*----------------------------------------------------------------------------*/

#ifndef SYSCBHDL_INCL
#define SYSCBHDL_INCL

/*! <p><b>External abort handler</b><br>
    called if an exception was raised<br>
    Note, that normal program execution isn't possible at this time.
*/
typedef void (*PHDL_ABORT)(char* abortmsg);

/*! <p><b>External trap handler</b><br>
    called if an exception was raised and no abort handler was defined<br>
    After that the program aborts. ( used by the xaron project )
*/
typedef void (*PHDL_TRAP)();

/*! <p><b>External memory handler</b><br>
    called once if memory allocation failed in order to release memory
*/
typedef void (*PHDL_FREEMEM)(size_t cnt);

#endif //_INCL
