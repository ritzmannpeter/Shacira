/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [glo_tab.c]                   Global Table                               */
/*                                                                          */
/* Copyright (c) 1993 by Lars D\olle, Heike Manns                           */
/* ------------------------------------------------------------------------ */
    
#include "standard.h"
#include "symbols.h"

#include "hmap.h"
#include "sink.h"

static MAP(symbol,DL_Hdl) dlltab;
static MAP(symbol,Abs_T)  glotab_0;
static MAP(Abs_T,symbol)  glotab_1;

/*! 
   <p>Through the means of the module [glo_tab] it is possible to store and retrieve
   arbitrary pairs ( key, value ) with a bijective mapping between them. 
   <p>This defines a special global process memory.
   <p>Originally this functionality was needed in order to make statically bind C-functions 
   persistent. ( see also <a href="binimg.htm">[binimg]</a> )
   <p>In addition this module handles i.e. keeps track of dynamical loaded objects.<br><br>
*/

/*I----------------------------- Init & Quit -------------------------------- */

void Glo_init(void)
/* inits [glo_tab] */
{ MAPTY glotyp;
  glotyp   = MAP_newTyp(primCopy,primFree,primEqual,primHash,primCopy,primFree);
  dlltab   = MAP_newMap(glotyp);
  glotab_0 = MAP_newMap(glotyp);
  glotab_1 = MAP_newMap(glotyp);
}

void Glo_quit(void)
/* quits [glo_tab] */
{ MAPTY glotyp; MAPIT itr; symbol dom; DL_Hdl rng;
  glotyp = MAP_MapTyp(glotab_0);
  MAP_forItrAsg(dom,rng,itr,dlltab) DL_close(rng);
  MAP_freeMap(dlltab);
  MAP_freeMap(glotab_0);
  MAP_freeMap(glotab_1);
  MAP_freeTyp(glotyp);
}

/*I----------------------------- Table access ------------------------------- */

void Glo_def(symbol Name, Abs_T Value)
/* adds global ( 'Name' <--> 'Value' ) */
{ string s = symbolToString(Name);
  assert1( !MAP_defined(glotab_0,Name ), "'%s' already defined", s);
  assert1( !MAP_defined(glotab_1,Value),
           "value to define for '%s' is already defined", s);
  MAP_dfndom(glotab_0,Name,Value);
  MAP_dfndom(glotab_1,Value,Name);
}

void Glo_rmv(symbol Name)
/* deletes global 'Name' */
{ Abs_T Value = MAP_apply(Abs_T,glotab_0,Name);
  MAP_rmvdom(glotab_0,Name );
  MAP_rmvdom(glotab_1,Value);
}

bool Glo_key_known(symbol Name)
/* whether 'Name' is defined */
{
  return( MAP_defined(glotab_0,Name) );
}

bool Glo_val_known(Abs_T Value)
/* whether 'Value' is defined */
{
  return( MAP_defined(glotab_1,Value) );
}

Abs_T Glo__val(symbol Name)
#define Glo_val(T,N) ((T)Glo__val(N))
/* value defined for 'Name' */
{
  return( MAP_apply(Abs_T,glotab_0,Name) );
}

symbol Glo_key(Abs_T Value)
/* name defined for 'Value' */
{
  return( MAP_apply(symbol,glotab_1,Value) );
}

symbol Glo_objkey_mk(symbol Lib, symbol Obj)
/* constructs key for loadable object */
{ symbol keysym;
  string keynam;
  keynam = Str_printf("%s.%s",symbolToString(Lib),symbolToString(Obj));
  keysym = stringToSymbol(keynam);
  FreeMem(keynam);
  return keysym;
}

bool Glo_objkey_de(symbol glokey, symbol* Lib, symbol* Obj)
/* destructs key of loadable object */
{ string keynam, libnam, objnam;
  long   len, i;
  keynam = symbolToString(glokey);
  len    = strlen(keynam);
  for( i=len-1; i >= 0; --i )
  {
    if( keynam[i] == '.' )
    {
      libnam = SubStrCopy(keynam,i);
      objnam = StrCopy(keynam+i+1);
      *Lib   = stringToSymbol(libnam);
      *Obj   = stringToSymbol(objnam);
      FreeMem(libnam);
      FreeMem(objnam);
      return True;
    }
  }
  return False;
}

StdCPtr Glo_load(symbol Lib, symbol Obj, bool saveObj)
/* loads the object if not already defined 
   'saveObj' --> saves it in the global table 
*/
{ DL_Hdl  hdl; 
  symbol  objkey = Glo_objkey_mk(Lib,Obj);
  StdCPtr objval = (StdCPtr)NULL;
  if( MAP_defined(glotab_0,objkey) )
    return MAP_apply(StdCPtr,glotab_0,objkey);
  else
  {
    if( MAP_defined(dlltab,Lib) )
      hdl = MAP_apply(DL_Hdl,dlltab,Lib);
    else
    {
      hdl = DL_open(symbolToString(Lib),-1);
      if( hdl != (DL_Hdl)NULL )
        MAP_dfndom(dlltab,Lib,hdl);
    }
    if( hdl != (DL_Hdl)NULL )
    {
      objval = DL_symbol(hdl,symbolToString(Obj));
      if( objval != (StdCPtr)NULL && saveObj ) Glo_def(objkey,objval);
    }
    return objval;
  }
}
