/****************************************************************************
*
*
*   DATEI:        STD_EL.H
*
*  BESCHREIBUNG:
*     In dieser Datei werden alle Standard-Objekte, Seiten und Elemente
*     definiert, die in den Seiten-Beschreibungen verwendet werden koennen.
*
*  HISTORY:
*     23.11.90    -SF-     Implementierung
*     12.09.91    -UP-     NULL durch NULL_ELEMENT ersetzt
*     19.12.91    -TSchw-  In STD_HEATTEXT Schluesselschalter von 1 auf 3
*                          erhoeht, Forderung Gehring, Kalis
*     11.04.01 -HAns-      OPT_OBJ eingefuegt.
*
****************************************************************************/

#define OPT_OBJ(Line,El,Opt)\
   { Line, (ELEMENT *) &(El), CYCL_REFRESH_NONE|EVENT_REFRESH_OFF,\
     {PDarkOption, Opt} }

#define STD_OBJ(Line,El)\
   { (Line), (ELEMENT *)&(El), CYCL_REFRESH_NONE|EVENT_REFRESH_OFF,NOFUNC }

#define STD_HEADTEXT(name,t1,t2)\
static const FIXTEXT name = {\
  ELID_FIXTEXT, NULL_ELEMENT,\
  CYCL_REFRESH_NONE|EVENT_REFRESH_OFF,\
  {0,0}, HEADLINE_COLOR, NOFUNC,\
  t1,t2 }

#define STD_FIXTEXT(name,next,xpos,t1,t2)\
static const FIXTEXT name = {\
  ELID_FIXTEXT, (ELEMENT_PTR) (next),\
  CYCL_REFRESH_NONE|EVENT_REFRESH_OFF,\
  {xpos,0}, TEXT_COLOR, NOFUNC,\
  t1,t2 }

#define STD_INDTEXT(name,next,ref,xpos,reg,t1,t2)\
static const INDTEXT name = {\
  ELID_INDTEXT, (ELEMENT_PTR) (next),\
  ref,\
  {xpos,0}, TEXT_COLOR,\
  NOFUNC,\
  {reg,NO_REGIND}, t1,t2 }

#define STD_TEXT(name,next,xpos,varnr,rsz,csz,text)\
static const TEXT name = {\
  ELID_TEXT, (ELEMENT_PTR) (next),\
  CYCL_REFRESH_NONE|EVENT_REFRESH_OFF,\
  {xpos,0}, TEXT_COLOR, 1, varnr,\
  NOFUNC, NOFUNC, NOFUNC,\
  0, 0, rsz, csz, FALSE, text,\
  {0, 0, 0, 0, 0 } }

#define STD_FREETEXT(name,text)\
static const TEXT name = {\
  ELID_TEXT, NULL_ELEMENT,\
  CYCL_REFRESH_NONE|EVENT_REFRESH_OFF,\
  {0,0}, TEXT_COLOR, 3, 21,\
  NOFUNC, NOFUNC, NOFUNC,\
  0, 0, 19, 53, TRUE, text,\
  {0, 0, 0, 0, 0 } }

#define STD_HEATTEXT(name,next,xpos,varnr,type,ind1)\
static const TEXT name = {\
  ELID_HEATTEXT, (ELEMENT_PTR) (next),\
  CYCL_REFRESH_NONE|EVENT_REFRESH_OFF,\
  {xpos,0}, TEXT_COLOR, 3, varnr,\
  NOFUNC, NOFUNC, NOFUNC,\
  0, 0, 1, 11, FALSE, type,\
  {0, ind1, 1, 0, REGIND_CCU } }

#define STD_REGSOLL(name,next,dim,text,xpos,varnr,reg,form,t1,t2)\
static const REGSOLL name = {\
  ELID_REGSOLL, (ELEMENT_PTR) (next),\
  CYCL_REFRESH_NONE|EVENT_REFRESH_OFF,\
  {xpos,0}, SOLL_COLOR, 1, varnr,\
  {reg,NO_REGIND},\
  form,\
  (ELEMENT_PTR) dim, (ELEMENT_PTR) text,\
  NOFUNC,\
  t1,t2,\
  NOFUNC }

#define STD_REGIST(name,next,dim,text,xpos,varnr,reg,form,ref)\
static const REGIST name = {\
  ELID_REGIST, (ELEMENT_PTR) (next),\
  ref,\
  {xpos,0}, IST_COLOR,\
  {reg,NO_REGIND},\
  form,\
  (ELEMENT_PTR) dim, (ELEMENT_PTR) text,\
  varnr, NOFUNC }
