/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [meta_exp.c]           Meta-Expression Constructors/Destructors          */
/*                                                                          */
/* Copyright (c) 1999 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"
#include "otab.h"


/*I------------------------ Types & Macros ------------------------------ */


#define MVAL_TYP_ROW   0  /* vector with child elements                   */
#define MVAL_TYP_INT   1  /* number, up to 4 bytes                        */
#define MVAL_TYP_ABS   2  /* external value : abstract type               */
#define MVAL_TYP_STR   3  /* null-terminated string                       */
#define MVAL_TYP_RAW   4  /* byte array: len ( 4 byte ) byte ...          */
#define MVAL_TYP_NSTR  5  /* null-terminated string ( copy )              */
#define MVAL_TYP_BIN   6  /* byte array: len ( 4 byte ) byte ... ( copy ) */


/*DOC_INTERFACE*/
typedef Abs_T (*MF_Cpy_T)(Abs_T val); // type of copy function for external value
typedef void  (*MF_Del_T)(Abs_T val); // type of free function for external value


ConcreteType(MValPtr_T) // type of meta element pointer value 
{
  Abs_T val;    /* value           */
  MF_Cpy_T cpy; /* copy function   */
  MF_Del_T del; /* delete function */
};

ConcreteType(MVal_T) // type of meta element value 
{
  int typ; /* see above */
  union _val 
  {
    ROW(_/*Meta_T*/)       rval;
    long                   nval;
    ConcreteImp(MValPtr_T) pval;
    c_string               sval;
    c_byte*                bval;
  } val;
};

ExternalType(Meta_T) // type of meta element
{
   c_string            id;  // element name
   c_string            typ; // element type ( name of evaluation handler, e.g. styx ) 
   c_string            loc; // element location
   long                row; // ... line
   long                col; // ... column 
   ConcreteImp(MVal_T) val; // element value 
};


/*I ------------------------- Create & Dispose -------------------------- */

Meta_T Meta_new(c_string id, c_string typ)
/* creates a new meta element with 
   identifier 'id' and meta type 'typ'
*/
{ Meta_T elm = New(Meta_T);
  elm->id      = id==NULL?id:StrCopy(id);
  elm->typ     = typ==NULL?typ:StrCopy(typ);
  elm->loc     = (c_string)NULL;
  elm->row     = -1;
  elm->col     = -1;
  elm->val.typ = -1;
  return elm;
}

static void Meta_delete_aux(Meta_T elm, c_bool delroot)
/* delete meta element */
{ 
  BUG_NULL(elm);
  switch( elm->val.typ )
  {
    case MVAL_TYP_NSTR: 
      if( elm->val.val.sval != NULL ) FreeMem(elm->val.val.sval);
      break;
    case MVAL_TYP_BIN: 
      if( elm->val.val.bval != NULL ) FreeMem(elm->val.val.bval);
      break;
    case MVAL_TYP_ABS: 
      if( elm->val.val.pval.val != NULL ) (*elm->val.val.pval.del)(elm->val.val.pval.val);
      break;
    case MVAL_TYP_ROW: 
      if( elm->val.val.rval != NULL ) 
      { long cnt = OT_CNT(elm->val.val.rval), i;
        for( i=0; i < cnt; ++i )
        {
          Meta_delete_aux(OT_GET(Meta_T,elm->val.val.rval,i),C_True);
        }
        OT_DEL_T(elm->val.val.rval);
      }
      break;
  }
  if( delroot )
  {
    if( elm->id != NULL )  FreeMem(elm->id);
    if( elm->typ != NULL ) FreeMem(elm->typ);
    FreeMem(elm);
  }
  else
  {
    elm->val.typ = -1;
  }
}

void Meta_delete(Meta_T elm)
/* frees meta element 'elm' */
{ 
  Meta_delete_aux(elm,C_True);
}

/*I------------------------ Constructors ------------------------------- */

/*!! 
   In the constructor and set functions 'id' and 'typ' will be copied. 
   Most of the values won't. Otherwise it's documented explicit.
   For string and abstract values it can be specified by the user.
*/

Meta_T Meta_grp_mk(c_string id, c_string typ, ROW(Meta_T) parts)
/* constructs a meta element of type 'group' and
   child elements in 'parts' as value
*/
{ Meta_T elm = Meta_new(id,typ);
  elm->val.typ      = MVAL_TYP_ROW;
  elm->val.val.rval = parts;
  return elm;
}

Meta_T Meta_int_mk(c_string id, c_string typ, long val)
/* constructs a meta element of type 'int' and 'val' as value */
{ Meta_T elm = Meta_new(id,typ);
  elm->val.typ      = MVAL_TYP_INT;
  elm->val.val.nval = val;
  return elm;
}

Meta_T Meta_abs_mk
       (
         c_string id, c_string typ, Abs_T val, MF_Cpy_T cpy, MF_Del_T del
       )
/* constructs a meta element of type 'abstract', 'val' as value, 
   'cpy' as copy function and 'del' as free function
*/
{ Meta_T elm = (Meta_T)NULL;
  BUG_NULL(cpy); BUG_NULL(del);
  { 
    elm = Meta_new(id,typ);
    elm->val.typ          = MVAL_TYP_ABS;
    elm->val.val.pval.cpy = cpy;
    elm->val.val.pval.del = del;
    elm->val.val.pval.val = val==NULL?val:(*cpy)(val);
  }
  return elm;
}

Meta_T Meta_str_mk(c_string id, c_string typ, c_string val, c_bool valcopy)
/* constructs a meta element of type 'string' and 'val' as value
   'valcopy' --> copies value
*/
{ Meta_T elm = Meta_new(id,typ);
  if( valcopy )
  {
    elm->val.typ      = MVAL_TYP_NSTR;
    elm->val.val.sval = val==NULL?val:StrCopy(val);
  }
  else
  {
    elm->val.typ      = MVAL_TYP_STR;
    elm->val.val.sval = val;
  }
  return elm;
}

Meta_T Meta_raw_mk(c_string id, c_string typ, c_byte* val)
/* constructs a meta element of type 'raw' and 'val' as value
   ( val = (4 byte) len byte ... ) 
*/
{ Meta_T elm = Meta_new(id,typ);
  elm->val.typ      = MVAL_TYP_RAW;
  elm->val.val.bval = val;
  return elm;
}

Meta_T Meta_bin_mk(c_string id, c_string typ, long len, c_byte* val)
/* constructs a meta element of type 'binary' and 'val' as value
   of length 'len' ( copies value )
*/
{ Meta_T elm = NULL;
  if( len > 0 ) BUG_NULL(val); 
  else
  { c_byte* bin = (c_byte*)NewMem(len+4);
    memcpy(bin,&len,4);
    if( len > 0 ) memcpy(bin+4,val,len);
    elm = Meta_new(id,typ);
    elm->val.typ      = MVAL_TYP_BIN;
    elm->val.val.bval = bin;
  }
  return elm;
}

Meta_T Meta_set_loc(Meta_T elm, c_string loc, long row, long col)
/* adds / updates location information 'loc', 'row' and 'col'
   in meta element 'elm' ( no copy of 'loc' ) 
*/
{ 
  BUG_NULL(elm);
  elm->loc = loc;
  elm->row = row;
  elm->col = col;
  return elm;
}

Meta_T Meta_set_key(Meta_T elm, c_string id, c_string typ)
/* adds / updates key information 'id', 'typ' in meta element 'elm' */
{ 
  BUG_NULL(elm);
  if( elm->id  != NULL ) FreeMem(elm->id);
  if( elm->typ != NULL ) FreeMem(elm->typ);
  elm->id  = id==NULL?id:StrCopy(id);
  elm->typ = typ==NULL?typ:StrCopy(typ);
  return elm;
}

Meta_T Meta_set_grp(Meta_T elm, ROW(Meta_T) parts)
/* adds / updates group value 'parts' in meta element 'elm' */
{ 
  BUG_NULL(elm);
  Meta_delete_aux(elm,C_False);
  elm->val.typ      = MVAL_TYP_ROW;
  elm->val.val.rval = parts;
  return elm;
}

Meta_T Meta_set_int(Meta_T elm, long val)
/* adds / updates int value 'val' in meta element 'elm' */
{ 
  BUG_NULL(elm);
  Meta_delete_aux(elm,C_False);
  elm->val.typ      = MVAL_TYP_INT;
  elm->val.val.nval = val;
  return elm;
}

Meta_T Meta_set_abs(Meta_T elm, Abs_T val, MF_Cpy_T cpy, MF_Del_T del)
/* adds / updates abstract value 'val', 'cpy', 'del' 
   in meta element 'elm' 
*/
{ 
  BUG_NULL(elm);
  Meta_delete_aux(elm,C_False);
  elm->val.typ          = MVAL_TYP_ABS;
  elm->val.val.pval.cpy = cpy;
  elm->val.val.pval.del = del;
  elm->val.val.pval.val = val==NULL?val:(*cpy)(val);
  return elm;
}

Meta_T Meta_set_str(Meta_T elm, c_string val, c_bool valcopy)
/* adds / updates string value 'val' in meta element 'elm' 
   'valcopy' --> copies value
*/
{ 
  BUG_NULL(elm);
  Meta_delete_aux(elm,C_False);
  if( valcopy )
  {
    elm->val.typ      = MVAL_TYP_NSTR;
    elm->val.val.sval = val==NULL?val:StrCopy(val);
  }
  else
  {
    elm->val.typ      = MVAL_TYP_STR;
    elm->val.val.sval = val;
  }
  return elm;
}

Meta_T Meta_set_raw(Meta_T elm, c_byte* val)
/* adds / updates raw value 'val' in meta element 'elm' */
{ 
  BUG_NULL(elm);
  Meta_delete_aux(elm,C_False);
  elm->val.typ      = MVAL_TYP_RAW;
  elm->val.val.bval = val;
  return elm;
}

Meta_T Meta_set_bin(Meta_T elm, long len, c_byte* val)
/* adds / updates binary value 'val' of length 'len' 
   in meta element 'elm' 
*/
{ 
  BUG_NULL(elm);
  Meta_delete_aux(elm,C_False);
  if( len > 0 ) BUG_NULL(val); 
  else
  { c_byte* bin = (c_byte*)NewMem(len+4);
    memcpy(bin,&len,4);
    if( len > 0 ) memcpy(bin+4,val,len);
    elm->val.typ      = MVAL_TYP_BIN;
    elm->val.val.bval = bin;
  }
  return elm;
}

/*I------------------------ Destructors -------------------------------- */

void Meat_get_loc(Meta_T elm, c_string* loc, long* row, long* col)
/* get location information of meta element 'elm' */
{ 
  BUG_NULL(elm);
  if( loc != NULL ) *loc = elm->loc;
  if( row != NULL ) *row = elm->row;
  if( row != NULL ) *row = elm->col;
}

bool Meta_grp_de(Meta_T elm, c_string* id, c_string* typ, ROW(Meta_T)* parts)
/* destructs group meta element 'elm' */
{
  BUG_NULL(elm);
  if( elm->val.typ == MVAL_TYP_ROW )
  {
    if( id    != NULL ) *id    = elm->id;
    if( typ   != NULL ) *typ   = elm->typ;
    if( parts != NULL ) *parts = elm->val.val.rval;
    return C_True;
  }
  else return C_False;
}

bool Meta_int_de(Meta_T elm, c_string* id, c_string* typ, long* val)
/* destructs int meta element 'elm' */
{
  BUG_NULL(elm);
  if( elm->val.typ == MVAL_TYP_INT )
  {
    if( id  != NULL ) *id  = elm->id;
    if( typ != NULL ) *typ = elm->typ;
    if( val != NULL ) *val = elm->val.val.nval;
    return C_True;
  }
  else return C_False;
}

bool Meta_abs_de
     (
       Meta_T elm, c_string* id, c_string* typ, 
       Abs_T* val, MF_Cpy_T* cpy, MF_Del_T* del
     )
/* destructs abstract meta element 'elm' */
{ 
  BUG_NULL(elm);
  if( elm->val.typ == MVAL_TYP_ABS )
  {
    if( id  != NULL ) *id  = elm->id;
    if( typ != NULL ) *typ = elm->typ;
    if( val != NULL ) *val = elm->val.val.pval.val;
    if( cpy != NULL ) *cpy = elm->val.val.pval.cpy;
    if( del != NULL ) *del = elm->val.val.pval.del;
    return C_True;
  }
  else return C_False;
}

bool Meta_str_de(Meta_T elm, c_string* id, c_string* typ, c_string* val)
/* destructs string meta element 'elm' */
{
  BUG_NULL(elm);
  if( elm->val.typ == MVAL_TYP_STR || elm->val.typ == MVAL_TYP_NSTR )  
  {
    if( id  != NULL ) *id  = elm->id;
    if( typ != NULL ) *typ = elm->typ;
    if( val != NULL ) *val = elm->val.val.sval;
    return C_True;
  }
  else return C_False;
}

bool Meta_raw_de(Meta_T elm, c_string* id, c_string* typ, c_byte** val)
/* destructs raw meta element 'elm' */
{
  BUG_NULL(elm);
  if( elm->val.typ == MVAL_TYP_RAW )
  {
    if( id  != NULL ) *id  = elm->id;
    if( typ != NULL ) *typ = elm->typ;
    if( val != NULL ) *val = elm->val.val.bval;
    return C_True;
  }
  else return C_False;
}

bool Meta_bin_de(Meta_T elm, c_string* id, c_string* typ, long* len, c_byte** val)
/* destructs binary meta element 'elm' */
{
  BUG_NULL(elm);
  if( elm->val.typ == MVAL_TYP_BIN )
  {
    if( id  != NULL ) *id  = elm->id;
    if( typ != NULL ) *typ = elm->typ;
    if( len != NULL ) memcpy(len,elm->val.val.bval,4);
    if( val != NULL ) *val = elm->val.val.bval+4;
    return C_True;
  }
  else return C_False;
}

