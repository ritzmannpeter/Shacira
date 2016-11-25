
#ifndef __core__
#define __core__

/*.SI.***********************************************************************/
#ifndef _syntax
#include <syntax.h>
#define _syntax
#endif
#ifndef _program
#include <program.h>
#define _program
#endif
/*.EI.***********************************************************************/

#define START_CONDITION                 1               /* Startbedingung                                                               */
#define CORE_OUT_MOVEMENT               2               /* Ausfahrbewegung Kern                                         */
#define CORE_IN_MOVEMENT                3               /* Einfahrbewegung Kern                                         */
#define AIR_VALVE_OFF                   4               /* Luftventil Blasen ein                                        */
#define AIR_VALVE_ON                            5               /* Luftventil Blasen aus                                        */
#define TURNAROUND                              6               /* Wendebewegung                                                                */
                                           
#define IS_START_CONDITION(ident)       (ident == START_CONDITION)
#define IS_CORE_MOVEMENT(ident)         (ident == CORE_IN_MOVEMENT || ident == CORE_OUT_MOVEMENT)
#define IS_AIR_VALVE(ident)                     (ident == AIR_VALVE_ON || ident == AIR_VALVE_OFF)
#define IS_TURNAROUND(ident)                    (ident == TURNAROUND)

/* Kodierung des Infoworts
 */
#define PARALLEL                                        0x0001  /* parallele Bewegung                                   */
#define ENDPOSITION                             0x0002  /* Bewegung bis Endposition                     */
#define MULTIPLE_HUB                            0x0004  /* Mehrfachbewegung                                             */
#define START_DELAY                             0x0008  /* Bewegung verz”gert                                   */
#define TIMED_CTRL                              0x0010  /* Bewegung zeitlich ueberwacht         */
#define CTRL_POINT_MACHINE      0x0020  /* Bewegung mit Wegueberwachung         */ 
#define ENDPOS_UNDER_PRESSURE   0x0040  /* Endposition unter Druck                              */
/* 0x0080 Signaltyp siehe unten */
/* 0x0100 Signaltyp siehe unten */
#define ELECTRIC_CORE                   0x0200  /* Elektrisch - pneumatischer Kern      */
#define WINDING_CORE                            0x0400  /* Schraubkern                                                          */
#define TURNAROUND_LOCKED               0x0800  /* Wenden verriegelt                                            */

/* Signaltyp                                            0x0080
                                                                                0x0100  
        wird durch zwei Bits kodiert                    */
#define END_SWITCH                              0x0000  
#define TIMER                                           0x0001
#define WAY_FACILITY                            0x0002

#define GET_SIGNAL_TYPE(info)                   ((info&0x0180)>>7)
#define SET_SIGNAL_TYPE(info, type)     (info = (info&(~0x0180)) | (type<<7)&0x0180)

/* Startpunkt - Semantik:
 * ordnet den Startpunkten eine feste Identifikation zu, da sowohl
 * im IQT (Plausibilit„tsueberpruefung, Parameter usw.) als auch
 * in der SPS mit fast jedem Startpunkt eine spezielle Semantik verbunden
 * ist.
 */
#define PRE_MOULD_CLOSE         1       /* Vor Werkzeug schlie~en                                                               */
#define PAR_MOULD_CLOSE         2       /* Parallel Werkzeug schlie~en mit Wegtpunkt            */
#define IMD_MOULD_CLOSE         3       /* Bei Werkzeug schlie~en mit Zwischenstop              */
#define PRE_CLPOWER_RAISE       4       /* Vor Schlie~kraftaufbau                                                               */
#define PAR_CLPOWER_RAISE       5       /* Parallel Schlie~kraftaufbau                                          */
#define POST_CLPOWER_RAISE      6       /* Nach Schlie~kraftaufbau                                                              */
#define PRE_INJECTION           7       /* Vor Einspritzen                                                                              */
#define IMD_INJ_PHASE           8       /* Mit Start Einspritzstufe                                                     */
#define END_INJECTION	         9       /* Ende Einspritzen                                                                             */
#define IMD_COOLING                     10      /* Mit K}hlzeit                                                                                 */
#define PRE_CLPOWER_FALL        11      /* Vor Schlie~kraftabbau                                                                */
#define PAR_CLPOWER_FALL        12      /* Parallel Schlie~kraftabbau                                              */
#define POST_CLPOWER_FALL       13      /* Nach Schlie~kraftabbau                                                               */
#define PAR_MOULD_OPEN          14      /* Parallel Werkzeug |ffnen mit Wegpunkt                        */
#define IMD_MOULD_OPEN          15      /* Bei Werkzeug |ffnen mit Zwischenstop                 */
#define IMD_OPEN_MOULD          16      /* Bei ge|ffnetem Werkzeug                                                              */
#define IMD_START_EJECTOR       17      /* Mit Start Auswerfer                                                                  */
#define FROM_HANDLING           18      /* Von Entnahmegeraet                                                                   */

#define IS_AGGREGAT_RELATED(id)	((id == PRE_INJECTION) || \
	                               (id == IMD_INJ_PHASE) || \
											 (id == END_INJECTION))


/* Programmzeile
 */
typedef struct core_line
{       int ident;
        int number;
        UWORD info;
        int p;
        int v;
        int s1;
        int s2;
        int tA;
        int tV;
        int s3;
        int M;
        int tR;
	    int index;
}       CORE_LINE;

#define ACT_LINE                        -1

/* Exportierte Funktionen
 */

#ifdef DLL_CORE

extern int  (far *vCORE_ProgCreate)(int  lines);
#define CORE_ProgCreate(lines) ((*vCORE_ProgCreate)(lines))

extern int  (far *vCORE_ProgRemove)();
#define CORE_ProgRemove() ((*vCORE_ProgRemove)())

extern int  (far *vCORE_ProgAppend)(void *  line);
#define CORE_ProgAppend(line) ((*vCORE_ProgAppend)(line))

extern int  (far *vCORE_ProgLines)();
#define CORE_ProgLines() ((*vCORE_ProgLines)())

extern int  (far *vCORE_ProgLineLen)();
#define CORE_ProgLineLen() ((*vCORE_ProgLineLen)())

extern int  (far *vCORE_ProgFill)();
#define CORE_ProgFill() ((*vCORE_ProgFill)())

extern int  (far *vCORE_ProgCursor)();
#define CORE_ProgCursor() ((*vCORE_ProgCursor)())

extern int  (far *vCORE_ident)(int  line);
#define CORE_ident(line) ((*vCORE_ident)(line))

extern int  (far *vCORE_number)(int  line);
#define CORE_number(line) ((*vCORE_number)(line))

extern UWORD (far *vCORE_info)(int  line);
#define CORE_info(line) ((*vCORE_info)(line))

extern int  (far *vCORE_p)(int  line);
#define CORE_p(line) ((*vCORE_p)(line))

extern int  (far *vCORE_v)(int  line);
#define CORE_v(line) ((*vCORE_v)(line))

extern int  (far *vCORE_s1)(int  line);
#define CORE_s1(line) ((*vCORE_s1)(line))

extern int  (far *vCORE_s2)(int  line);
#define CORE_s2(line) ((*vCORE_s2)(line))

extern int  (far *vCORE_tA)(int  line);
#define CORE_tA(line) ((*vCORE_tA)(line))

extern int  (far *vCORE_tV)(int  line);
#define CORE_tV(line) ((*vCORE_tV)(line))

extern int  (far *vCORE_s3)(int  line);
#define CORE_s3(line) ((*vCORE_s3)(line))

extern int  (far *vCORE_M)(int  line);
#define CORE_M(line) ((*vCORE_M)(line))

extern int  (far *vCORE_tR)(int  line);
#define CORE_tR(line) ((*vCORE_tR)(line))

extern int  (far *vCORE_index)(int  line);
#define CORE_index(line) ((*vCORE_index)(line))

extern int  (far *vCORE_set_ident)(int  line, int  val);
#define CORE_set_ident(line, val) ((*vCORE_set_ident)(line, val))

extern int  (far *vCORE_set_number)(int  line, int  val);
#define CORE_set_number(line, val) ((*vCORE_set_number)(line, val))

extern int  (far *vCORE_set_info)(int  line, UWORD val);
#define CORE_set_info(line, val) ((*vCORE_set_info)(line, val))

extern int  (far *vCORE_set_p)(int  line, int  val);
#define CORE_set_p(line, val) ((*vCORE_set_p)(line, val))

extern int  (far *vCORE_set_v)(int  line, int  val);
#define CORE_set_v(line, val) ((*vCORE_set_v)(line, val))

extern int  (far *vCORE_set_s1)(int  line, int  val);
#define CORE_set_s1(line, val) ((*vCORE_set_s1)(line, val))

extern int  (far *vCORE_set_s2)(int  line, int  val);
#define CORE_set_s2(line, val) ((*vCORE_set_s2)(line, val))

extern int  (far *vCORE_set_tA)(int  line, int  val);
#define CORE_set_tA(line, val) ((*vCORE_set_tA)(line, val))

extern int  (far *vCORE_set_tV)(int  line, int  val);
#define CORE_set_tV(line, val) ((*vCORE_set_tV)(line, val))

extern int  (far *vCORE_set_s3)(int  line, int  val);
#define CORE_set_s3(line, val) ((*vCORE_set_s3)(line, val))

extern int  (far *vCORE_set_M)(int  line, int  val);
#define CORE_set_M(line, val) ((*vCORE_set_M)(line, val))

extern int  (far *vCORE_set_tR)(int  line, int  val);
#define CORE_set_tR(line, val) ((*vCORE_set_tR)(line, val))

extern int  (far *vCORE_set_index)(int  line, int  val);
#define CORE_set_index(line, val) ((*vCORE_set_index)(line, val))

extern int  (far *vCORE_CursorMove)(int  direction, int  distance);
#define CORE_CursorMove(direction, distance) ((*vCORE_CursorMove)(direction, distance))

extern int  (far *vCORE_SetMark)(int  mark, int  value, long  context);
#define CORE_SetMark(mark, value, context) ((*vCORE_SetMark)(mark, value, context))

extern int  (far *vCORE_RegisterMarkEvent)(int  mark, MARKFUNC event_func);
#define CORE_RegisterMarkEvent(mark, event_func) ((*vCORE_RegisterMarkEvent)(mark, event_func))

extern int  (far *vCORE_InsertLine)();
#define CORE_InsertLine() ((*vCORE_InsertLine)())

extern int  (far *vCORE_DeleteLine)();
#define CORE_DeleteLine() ((*vCORE_DeleteLine)())

#else

GLOBAL int far CORE_ProgCreate(int lines);
GLOBAL int far CORE_ProgRemove();
GLOBAL int far CORE_ProgAppend(void * line);
GLOBAL int far CORE_ProgLines(void);
GLOBAL int far CORE_ProgLineLen(void);
GLOBAL int far CORE_ProgFill(void);
GLOBAL int far CORE_ProgCursor(void);
GLOBAL int far CORE_ident(int line);
GLOBAL int far CORE_number(int line);
GLOBAL UWORD far CORE_info(int line);
GLOBAL int far CORE_p(int line);
GLOBAL int far CORE_v(int line);
GLOBAL int far CORE_s1(int line);
GLOBAL int far CORE_s2(int line);
GLOBAL int far CORE_tA(int line);
GLOBAL int far CORE_tV(int line);
GLOBAL int far CORE_s3(int line);
GLOBAL int far CORE_M(int line);
GLOBAL int far CORE_tR(int line);
GLOBAL int far CORE_index(int line);
GLOBAL int far CORE_set_ident(int line, int val);
GLOBAL int far CORE_set_number(int line, int val);
GLOBAL int far CORE_set_info(int line, UWORD val);
GLOBAL int far CORE_set_p(int line, int val);
GLOBAL int far CORE_set_v(int line, int val);
GLOBAL int far CORE_set_s1(int line, int val);
GLOBAL int far CORE_set_s2(int line, int val);
GLOBAL int far CORE_set_tA(int line, int val);
GLOBAL int far CORE_set_tV(int line, int val);
GLOBAL int far CORE_set_s3(int line, int val);
GLOBAL int far CORE_set_M(int line, int val);
GLOBAL int far CORE_set_tR(int line, int val);
GLOBAL int far CORE_set_index(int line, int val);
GLOBAL int far CORE_CursorMove(int direction, int distance);
GLOBAL int far CORE_SetMark(int mark, int value, long context);
GLOBAL int far CORE_RegisterMarkEvent(int mark, MARKFUNC event_func);
GLOBAL int far CORE_InsertLine(void);
GLOBAL int far CORE_DeleteLine(void);

#endif

#define UNABLE_TO_CREATE_COREPROG               -10

#endif /* __core__ */




