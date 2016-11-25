/* ------------------------------------------------------------------------- */
/*                                                                           */
/* [xml_dfn.h]              XML Base Library                                 */
/*                        - global definitions -                             */
/*                                                                           */
/* Copyright (c) 2003 by D\olle, Manns.                                      */
/* ------------------------------------------------------------------------- */

#ifndef XML_DFN_INCL
#define XML_DFN_INCL


#include "standard.h"
#include "gstream.h"


/*I-------------------------- Types and macros ------------------------------ */


AbstractType(UrlHdl_T); /* Abstract URL handle type */


/*! <p><b>External XML I/O handler</b><br>
*/
typedef void     (*XMLHDL_io_init)();
typedef void     (*XMLHDL_io_cleanup)();
typedef UrlHdl_T (*XMLHDL_io_create_handle)();
typedef void     (*XMLHDL_io_drop_handle)(UrlHdl_T hdl);
typedef c_bool   (*XMLHDL_io_download)
                 (
                   UrlHdl_T hdl, c_string url, c_string auth, 
                   GStream_T stream, void (*prMsg)(c_string msg)
                 );


#endif
