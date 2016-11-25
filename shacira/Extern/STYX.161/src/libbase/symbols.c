/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [symbols.c]                    Type: Symbol                              */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "standard.h"

#include "literal.h"
#include "hmap.h"


/*!! 
    This module implements the symbol type for a unique representation of strings 
    and the symbol table in which they are stored. One intention is the reduction 
    of place- and time-complexity when dealing with many identical strings.
    
    Specification
    1) forall String s : strcmp(s,symbolToString(stringToSymbol(s))) == 0.
    2) forall Symbol s : equalSymbols(s,stringToSymbol(symbolToString(s)).
    3) equalSymbols is an equality.
*/

/*I------------------------------ The Type -------------------------------- */

#define SYMTYP_LENGTH   1
#define SYMTYP_STRING   "s"
#define SYMTYP_BSTRING  "b"

ExternalType( symbol ) /* Abstract symbol type */
{
  long key;
  char str[1];
};

static MAP(string,symbol) symtab = (MAP(string,symbol)) NULL;
static int initcount_symbols     = 0;

/*I----------------------------- Init & Quit ------------------------------ */

static long symstrHash(string s)
/* hash function for symbol strings */
{
  if( s != (string)NULL )
  {
    if( !strncmp(s,SYMTYP_STRING,SYMTYP_LENGTH) )
      return strHash(s);
    else
    { long len;
      memcpy(&len,s+SYMTYP_LENGTH,sizeof(long));
      len += sizeof(long) + SYMTYP_LENGTH;
      return bytesHash((byte*)s,len);
    }
  }
  else return 0;
}

static bool symstrEqual(string s1, string s2)
/* equal function for symbol strings */
{
  if( s1 != (string)NULL && s2 != (string)NULL )
  {
    if( !strncmp(s1,s2,SYMTYP_LENGTH) )
    {
      if( !strncmp(s1,SYMTYP_STRING,SYMTYP_LENGTH) )
        return strEqual(s1,s2);
      else
      { long offset = sizeof(long) + SYMTYP_LENGTH, len1, len2;
        memcpy(&len1,s1+SYMTYP_LENGTH,sizeof(long));
        memcpy(&len2,s2+SYMTYP_LENGTH,sizeof(long));
        if( len1 == len2 )
          return !memcmp(s1+offset,s2+offset,len1);
      }
    }
    return False;
  }
  else return s1 == s2;
}

void initSymbols(void)
/* initializes the symbol table */
{ MAPTY symtyp;
  if( initcount_symbols == 0 )
  {
    assert0
    (
      symtab == (MAP(string,symbol))NULL, "symbol table already initalized"
    );
    symtyp = MAP_newTyp
             (
               primCopy, FreeMem, symstrEqual, symstrHash, primCopy, FreeMem
             );
    symtab = MAP_newMap(symtyp);
  }
  ++initcount_symbols;
}

void freeSymbols(void)
/* releases the symbol table */
{ MAPTY symtyp;
  --initcount_symbols;
  if( initcount_symbols == 0 )
  {
    assert0
    (
      symtab != (MAP(string,symbol))NULL, "symbol table not initalized"
    );
    symtyp = MAP_MapTyp(symtab);
    MAP_freeMap(symtab); MAP_freeTyp(symtyp);
    symtab = (MAP(string,symbol)) NULL;
  }
}

/*I----------------------------- Conversion ------------------------------- */

#define MAGIC        0x7654321L
#define MAGIC_BINARY 0x7654329L


static StdCPtr StrBytConcat(string Str, StdCPtr bytes, long len)
/* copies and concatenates string 'Str' ( without '\0' ) 
   and 'len' bytes of byte array 'bytes'; allocs memory 
*/
{ long   lens = strlen(Str);
  byte*  res  = (byte*)NewMem(len+lens);
  memcpy(res,Str,lens);
  memcpy(res+lens,bytes,len);
  return res;
}

static string StrConcat(string Str1, string Str2)
/* copies and concatenates strings 'Str1' and 'Str2'; 
   allocs memory 
*/
{ long   len1 = strlen(Str1), len2 = strlen(Str2);
  string res  = (string)NewMem(len1+len2+1);
  strcpy(res,Str1); strcat(res,Str2);
  return res;
}

symbol stringToSymbol(string str)
/* converts string 'str' into a symbol */
{ StdCPtr sem = sysbase_sem();
  symbol  sym = (symbol)NULL;
  assert0(symtab != (MAP(string,symbol)) NULL, "symbol table not initalized");
  if( sem == (StdCPtr)NULL || waitSem(sem) == 1 )
  { string dom = StrConcat(SYMTYP_STRING,str);
    if (!MAP_defined(symtab, dom))
    { symbol s = (symbol)NewMem(SizeOf(symbol)+strlen(str)+1);
      s->key = /*strHash(str)*/ MAGIC;
      strcpy(s->str,str);
      MAP_dfndom(symtab, dom, s);
      sym = s;
    }
    else 
    {
      sym = MAP_apply(symbol,symtab,dom);
      FreeMem(dom);
    }
    if( sem != (StdCPtr)NULL ) postSem(sem,1);
  }
  return sym;
}

symbol lstringToSymbol(string str)
/* converts ( lower case ) string 'str' into a symbol */
{ string lstr;
  symbol lsym;
  assert0(symtab != (MAP(string,symbol)) NULL, "symbol table not initalized");
  lstr = StrCopy(str); StrToLower(lstr);
  lsym = stringToSymbol(lstr);
  FreeMem(lstr);
  return lsym;
}

symbol ustringToSymbol(string str)
/* converts ( upper case ) string 'str' into a symbol */
{ string ustr;
  symbol usym;
  assert0(symtab != (MAP(string,symbol)) NULL, "symbol table not initalized");
  ustr = StrCopy(str); StrToLower(ustr);
  usym = stringToSymbol(ustr);
  FreeMem(ustr);
  return usym;
}

string symbolToString(symbol sym)
/* string corresponding to symbol 'sym' */
{
  assert0
  (
    sym != (symbol)NULL && (sym->key==MAGIC || sym->key==MAGIC_BINARY),
    "symbolToString : non-symbol"
  );
  if( sym->key == MAGIC ) return sym->str;
  else
  { long len;
    memcpy(&len,sym->str,sizeof(long));
    return sym->str+sizeof(long)+len;
  }
}

symbol bstringToSymbol(c_bstring bstr)
/* converts binary string 'bstr' into a symbol */
{ StdCPtr sem = sysbase_sem();
  symbol  sym = (symbol)NULL;
  assert0(symtab != (MAP(string,symbol)) NULL, "symbol table not initalized");
  if( sem == (StdCPtr)NULL || waitSem(sem) == 1 )
  { long len, i, j; byte* dom;
    memcpy(&len,bstr,sizeof(long)); len += sizeof(long);
    dom = StrBytConcat(SYMTYP_BSTRING,bstr,len);
    if (!MAP_defined(symtab, dom))
    { symbol s = (symbol)NewMem(SizeOf(symbol)+len+2*(len-sizeof(long))+1);
      s->key = MAGIC_BINARY;
      memcpy(s->str,bstr,len);
      MAP_dfndom(symtab, dom, s);
      for( i=sizeof(long), j=len; i < len; ++i, j+=2 )
        sprintf(s->str+j,"%02x",bstr[i]);
      sym = s;
    }
    else 
    {
      sym = MAP_apply(symbol,symtab,dom);
      FreeMem(dom);
    }
    if( sem != (StdCPtr)NULL ) postSem(sem,1);
  }
  return sym;
}

c_bstring symbolToBString(symbol sym)
/* binary string corresponding to symbol 'sym' */
{
  assert0
  (
    sym != (symbol)NULL && sym->key==MAGIC_BINARY,
    "symbolToBString : non-symbol"
  );
  return (c_bstring)sym->str;
}

/*I------------------------------ Predicates ------------------------------ */

bool equalSymbols(symbol a, symbol b)
/* whether two symbols 'a' and 'b' are equal */
{
  return a == b;
}


bool binarySymbol(symbol s)
/* whether symbol 's' represents a binary string */
{
  return s && s->key == MAGIC_BINARY;
}

/*I----------------------------- Debugging -------------------------------- */

void printSymbols(int indent)
/* prints the symbol table to stdout */
{ MAPIT itr; string dom; symbol e;
  assert0(symtab != (MAP(string,symbol)) NULL, "symbol table not initalized");
  fprintf(STDOUT,"Symbols /* count = %ld */",MAP_count(symtab));
  NL; fprintf(STDOUT,"{"); NL;
  MAP_forItrAsg(dom, e, itr, symtab)
  { 
    fprintf(STDOUT,"  Symbol (%08lx) ",e->key);
    if( e->key == MAGIC )
    { string s;
      s = LIT_c_str_lit(e->str);
      //fprintf(STDOUT,"%s",e->str);
      fprintf(STDOUT,"%s",s);
      FreeMem(s);
    }
    else
    if( e->key == MAGIC_BINARY )
    { long len, i; 
      byte* b = e->str + sizeof(long);
      memcpy(&len,e->str,sizeof(long));
      fprintf(STDOUT,"%ld:",len);
      for( i=0; i < len; ++i )
        fprintf(STDOUT," %02x",*b);
    }
    else C_BUG;
    if (!MAP_emptyItr(itr))
      fprintf(STDOUT,",");
    NL;
  }
  fprintf(STDOUT,"}");
  NL; NL;
}

long countSymbols(void)
/* number of symbols in the symbol table */
{
  return MAP_count(symtab);
}
