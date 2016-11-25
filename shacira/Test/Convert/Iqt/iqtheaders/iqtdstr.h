/*********************************************************************
*
*  MODUL: IQTDSTR.H
*
**********************************************************************
*
*  --- HISTORY ---
*  09.01.90   -TSchw-      Implementiert
*  09.07.90   -TSchw-      IMPORT_SL_TAB eingefuehrt
*  09.08.90   -TSchw-      USE_ISCOSBIT_KERN und USE_ISCOSREG_KERN eingefuehrt
*                          sowie "#include <ktabs.h>"
*  10.08.90   -SF-         IMPORT_DSDISK eingefuehrt
*  17.08.90   -JS-         WkzIStuf eingebaut
*  17.08.90   -SF-         Umrechnungs-Parameter fuer Datentraeger definiert
*  29.08.90   -JSCh-       BolzSoft eingefuehrt (Druckbolzenabgleich)
*  10.09.90   -SF-         iqttsk.h vor iqtdev.h einbinden
*  11.09.90   -SF-         Umrechnungs-Parameter fuer Datentraeger geaendert
*   4.10.90   -SF-         <dsfunct.h> einbinden und die davon betroffenen
*                          H-Files geloescht
*   5.10.90   -SF-         <dsfuncf.h> und <dsconvf.h> einbinden
*   8.10.90   -SF-         <dsfunc.h> und <dsconv.h> einbinden
*   8.10.90   -SF-         <fltfunc.h> und <fltfuncf.h> einbinden
*  15.10.90   -SF-         <dsfunc.h> wurde 2x eingebunden
*  23.10.90   -TSchw-      <g_text.h> mit 2 #ifdef eingeklammert, wegen der
*                          Uebersetzung von errtab.c in Versionen
*  23.11.90   -SF-         <std_el.h> bei den Seiten einbinden
*  05.09.91   -SF-         IMPORT_EXPCONF eingebaut
*
*********************************************************************/

#ifndef _iqtdstr
#define _iqtdstr

/*********************************************************************
*  ZUSAMMENFASSUNGEN VON DEFINE'S
**********************************************************************/

/* USE_ONLY_PAGES:  Dies kann in Seitenbeschreibungen definiert werden.
                    Damit werden alle noetigen Include-Files automatisch
                    eingebunden. */
#ifdef USE_ONLY_PAGES
#define _USECRT
#define USE_ALL_REGISTER
#define IMPORT_NOT_IQTTSK
#define IMPORT_NOT_GLOBAL
#define IMPORT_TEXTVAR
#define IMPORT_DSFUNC
#define IMPORT_PFUNC
#define IMPORT_KP_OPT
#define IMPORT_STD_EL
#endif

/* Alle Register-Definitionen einbinden */
#ifdef USE_ALL_REGISTER
#define   USE_ALL_IQTREG
#define   USE_ALL_IQTBIT
#define   USE_ALL_ISCOSREG
#define   USE_ALL_ISCOSBIT
#endif

/* Alle IQT-Register-Definitionen einbinden */
#ifdef USE_ALL_IQTREG
#define   USE_IQTREG_KLOECK
#define   USE_IQTREG_SPC
#define   USE_IQTREG_BDE
#define   USE_IQTREG_AXIS
#define   USE_IQTREG_DATE
#define   USE_IQTREG_PG
#define   USE_IQTREG_OTHERS
#define   USE_IQTREG_WCLOCK
#define   USE_IQTREG_PRINT
#define   USE_IQTREG_IFK
#define   USE_IQTREG_SCHICHT
#endif

/* Alle IQT-Bit-Definitionen einbinden */
#ifdef USE_ALL_IQTBIT
#define   USE_IQTBIT_KLOECK
#define   USE_IQTBIT_OTHERS
#endif

/* Alle ISCOS-Register-Definitionen einbinden */
#ifdef USE_ALL_ISCOSREG
#define   USE_ISCOSREG_KLOECK
#define   USE_ISCOSREG_HEAT
#define   USE_ISCOSREG_OTHERS
#endif

/* Alle ISCOS-Bit-Definitionen einbinden */
#ifdef USE_ALL_ISCOSBIT
#define   USE_ISCOSBIT_KLOECK
#define   USE_ISCOSBIT_KERN
#endif

/*********************************************************************
*  ABHAENGIGKEITEN abfangen
**********************************************************************/

#ifdef USE_ISCOSREG_KLOECK
#define  USE_ISCOSREG_KERN       /* Spritzwerttabellen mit einbinden */
#endif

/*********************************************************************
*  INCLUDE-FILES
**********************************************************************/

#ifndef _stddef
#include <stddef.h>
#define _stddef
#endif
#ifndef _stdio
#include <stdio.h>
#define _stdio
#endif
#ifndef _string
#include <string.h>
#define _string
#endif
#ifndef _stdlib
#include <stdlib.h>
#define _stdlib
#endif
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif



#ifndef _register       /* wegen SET_ALL_ ... */
#include <register.h>
#define _register
#endif
#ifndef _dsglobal
#include <dsglobal.h>
#define _dsglobal
#endif
#ifndef _devcrt
#include <devcrt.h>
#define _devcrt
#endif
#ifndef _devkbd
#include <devkbd.h>
#define _devkbd
#endif
#ifndef _dstruct
#include <dstruct.h>
#define _dstruct
#endif
#ifndef _g_const
#include <g_const.h>
#define _g_const
#endif

#ifndef _iqtreg
#include <iqtreg.h>
#define _iqtreg
#endif
#ifndef _iqtbit
#include <iqtbit.h>
#define _iqtbit
#endif
#ifndef _iscosreg
#include <iscosreg.h>
#define _iscosreg
#endif
#ifndef _iscosbit
#include <iscosbit.h>
#define _iscosbit
#endif
#ifndef _ktabs
#include <ktabs.h>
#define _ktabs
#endif
#ifndef _std_el
#include <std_el.h>
#define _std_el
#endif
#ifndef _userdef
#include <userdef.h>
#define _userdef
#endif
#ifndef _kp_opt
#include <kp_opt.h>
#define _kp_opt
#endif
#ifndef _dsfunc
#include <dsfunc.h>
#define _dsfunc
#endif
#ifndef _dsfuncf
#include <dsfuncf.h>
#define _dsfuncf
#endif
#ifndef _iqtdev
#include <iqtdev.h>
#define _iqtdev
#endif



#ifdef IMPORT_IQTTSK
#ifndef _iqttsk
#include <iqttsk.h>
#define _iqttsk
#endif
#endif

#ifndef IMPORT_NOT_GLOBAL
#ifndef _global
#include <global.h>
#define _global
#endif
#endif


#ifdef IMPORT_PTEXT
#ifndef _g_text
#include <g_text.h>
#define _g_text
#endif
#endif

#ifdef IMPORT_ERRSTR_FUNCTIONS
#ifndef _g_text
#include <g_text.h>
#define _g_text
#endif
#ifndef _error
#include <error.h>
#define _error
#endif
#endif

#ifdef IMPORT_TEXTVAR
#ifndef _textvar
#include <textvar.h>
#define _textvar
#endif
#endif

#ifdef IMPORT_PFUNC
#ifndef _dsfunc
#include <dsfunc.h>
#define _dsfunc
#endif
#endif

#ifdef IMPORT_DSFUNCF
#ifndef _dsfuncf
#include <dsfuncf.h>
#define _dsfuncf
#endif
#endif

#ifdef IMPORT_DSFUNC
#ifndef _dsfunc
#include <dsfunc.h>
#define _dsfunc
#endif
#endif

#ifdef IMPORT_DSCONVF
#ifndef _dsconvf
#include <dsconvf.h>
#define _dsconvf
#endif
#endif

#ifdef IMPORT_DSCONV
#ifndef _dsconv
#include <dsconv.h>
#define _dsconv
#endif
#endif

#ifdef IMPORT_FUNCPAR
#ifndef _funcpar
#include <funcpar.h>
#define _funcpar
#endif
#endif

#ifdef IMPORT_DEVISCOS
#ifndef _deviscos
#include <deviscos.h>
#define _deviscos
#endif
#endif

#ifdef IMPORT_KIF
#ifndef _kp_opt
#include <kp_opt.h>
#define _kp_opt
#endif
#ifndef _util
#include <util.h>
#define _util
#endif
#ifndef _kif
#include <kif.h>
#define _kif
#endif
#endif

#ifdef IMPORT_HOST_TYPES
#ifndef _host
#include <host.h>
#define _host
#endif
#endif

#ifdef IMPORT_FLTFUNC
#ifndef _fltfunc
#include <fltfunc.h>
#define _fltfunc
#endif
#ifndef _fltfuncf
#include <fltfunc.h>
#define _fltfuncf
#endif
#endif

#ifdef IMPORT_FLTFUNCF
#ifndef _fltfuncf
#include <fltfuncf.h>
#define _fltfuncf
#endif
#ifndef _fltfunc
#include <fltfunc.h>
#define _fltfunc
#endif
#endif

#ifdef IMPORT_KP_OPT
#ifndef _kp_opt
#include <kp_opt.h>
#define _kp_opt
#endif
#endif

#ifdef IMPORT_SL_TAB
#ifndef _dstruct
#include <dstruct.h>
#define _dstruct
#endif
#endif

#ifdef IMPORT_DSDISK
#ifndef _dsdisk
#include <dsdisk.h>
#define _dsdisk
#endif
#endif

#ifdef IMPORT_KPROM
#ifndef _kprom
#include <kprom.id>
#define _kprom
#endif
#ifndef _kp_id
#include <kpid.h>
#define _kp_id
#endif
#endif


#ifdef IMPORT_IREGINIT
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_IREGINIT*/

#ifdef IMPORT_INITHOOK
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_INITHOOK*/

#ifdef IMPORT_FASTHOOK
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_FASTHOOK*/

#ifdef IMPORT_INJHOOK
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_INJHOOK*/

#ifdef IMPORT_SLOWHOOK
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_SLOWHOOK*/

#ifdef IMPORT_MINHOOK
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_MINHOOK*/

#ifdef IMPORT_HEATWORK
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_HEATWORK*/

#ifdef IMPORT_DSUTIL
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_DSUTIL*/

#ifdef IMPORT_CARRIER
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_CARRIER*/

#ifdef IMPORT_TCONTROL
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_TCONTROL*/

#ifdef IMPORT_TABLES
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_TABLES*/

#ifdef IMPORT_TEST
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_TEST*/

#ifdef IMPORT_CLUNIT
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_CLUNIT*/

#ifdef IMPORT_INJFUNC
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_INJFUNC*/

#ifdef IMPORT_TRANSFER
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_TRANSFER*/

#ifdef IMPORT_KERNZUGF
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_KERNZUGF*/

#ifdef IMPORT_KPFUNC
#ifndef _dsfunct
#include <dsfunct.h>
#define _dsfunct
#endif
#endif /*IMPORT_KPFUNC*/

#ifdef IMPORT_BBRAM
#ifndef _bbram
#include <bbram.h>
#define _bbram
#endif
#endif

#ifdef _USEPRN
#ifndef _devprn
#include <devprn.h>
#define _devprn
#endif
#endif

#ifdef IMPORT_REGISTER_FUNCTIONS
#ifndef _register
#include <register.h>
#define _register
#endif
#endif

#ifdef IMPORT_ERROR_FUNCTIONS
#ifndef _error
#include <error.h>
#define _error
#endif
#endif


#ifdef IMPORT_STRING
#endif

#ifdef IMPORT_SHOW_FUNCTIONS
#ifndef _util
#include <util.h>
#define _util
#endif
#ifndef _show
#include <show.h>
#define _show
#endif
#ifndef _dswork
#include <dswork.h>
#define _dswork
#endif
#endif

#ifdef IMPORT_MESSAGE_FUNCTIONS
#ifndef _util
#include <util.h>
#define _util
#endif
#endif

#ifdef IMPORT_PRINT_FUNCTIONS
#ifndef _print
#include <print.h>
#define _print
#endif
#endif

#ifdef IMPORT_MEMORY_FUNCTIONS
#ifndef _iqtmem
#include <iqtmem.h>
#define _iqtmem
#endif
#endif

#ifdef IMPORT_DSP_FUNCTIONS
#ifndef _dispatch
#include <dispatch.h>
#define _dispatch
#endif
#endif

#ifdef _USEROB
#ifndef _devrob
#include <devrob.h>
#define _devrob
#endif
#endif

#ifdef _USEISCOS
#ifndef _deviscos
#include <deviscos.h>
#define _deviscos
#endif
#endif

#ifdef IMPORT_GETTEXT_FUNCTIONS
#ifndef _dswork
#include <dswork.h>
#define _dswork
#endif
#endif

#ifdef IMPORT_BG_FUNCTIONS
#ifndef _bg
#include <bg.h>
#define _bg
#endif
#endif

#ifdef _USEDISK
#ifndef _devdisk
#include <devdisk.h>
#define _devdisk
#endif
#endif


#endif   /* ifndef _iqtdstr */

