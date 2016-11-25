/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [pim2dot.c]        Parse table visualisation ( pim -> dot )              */
/*                                                                          */
/* Copyright (c) 2004 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"

#include "prs.h"
#include "hset.h"
#include "literal.h"
#include "pgm_base.h"
#include "gstream.h"
#include "line_scn.h"
#include "pathes.h"
#include "sink.h"

#include "pim2dot_cim.h"

#define imgfile  CTX_EVAL(string,"Img")
#define tmplfile CTX_EVAL(string,"Template")
#define outfile  CTX_EVAL(string,"OutFile")
#define diatype  CTX_EVAL(string,"DiaType")

static FILE* SysOut = NULL;


static void evalTemplate()
{ 
  if( strlen(tmplfile) > 0 )
  { FILE* fp = OpnFile(tmplfile,"rb");
    string line = Line_get(fp);
    fprintf(SysOut,"\n");
    while( line != NULL )
    {
      fprintf(SysOut,"%s\n",line);
      FreeMem(line);
      line = Line_get(fp);
    }
    fprintf(SysOut,"\n");
  }
}

static MAP(long,long) collectTNodes(PLR_Tab ptab)
{ MAP(long,long) states = MAP_newPrimMap();
  long i; 
  for( i=0; i < PLR_stateCnt(ptab); ++i )
  { 
    MAP_dfndom(states,i,-1);
  }
  return states;
}


static string dotLiteral(string s, string q)
{ Sink res = Sink_open();
  for (; *s != 0; s += 1)
    switch(*s)
    {
      case '\"' :
      case '\\' : Sink_putc(res,'\\'); Sink_putc(res, *s); break;
      case '\r' : Sink_putc(res,'\\'); Sink_putc(res,'r'); break;
      case '\n' : Sink_putc(res,'\\'); Sink_putc(res,'n'); break;
      case '\f' : Sink_putc(res,'\\'); Sink_putc(res,'f'); break;
      case '\t' : Sink_putc(res,'\\'); Sink_putc(res,'t'); break;
      default   : if( strchr(q,(*s)) != NULL )
                  {
                    Sink_putc(res,'\\'); Sink_putc(res,(*s));
                  }
                  else
                  if (!isspace(*s) && isprint(*s))
                    Sink_putc(res,*s);
                  else Sink_printf(res,"0x%02x",(*s)&0xff);
    };
  return Sink_close(res);
}

static void printRNode(PLR_Tab ptab, long nt)
{ c_bool start = C_False;
  long i;
  for( i=0; i < PLR_startCnt(ptab); ++i )
  {
    if( PLR_startSymbol(ptab,i) == nt )
    {
      start = C_True; break;
    }
  }
  fprintf(SysOut,"\n  node%ld [",nt);
  fprintf(SysOut," label=\"%s\"",PLR_symName(ptab,nt));
  if( start )
    fprintf(SysOut," shape=box");
  fprintf(SysOut,"]");
}

static void printTNode(PLR_Tab ptab, MAP(long,long) states, long state)
{ ROW(long) vaction = PLR_actionValues(ptab,state);
  long l, p, s, t, i; c_string sym; c_bool reduce = C_False;
  s = MAP_apply(long,states,state);
  fprintf(SysOut,"\n  node%ld [",state);
  fprintf(SysOut," label=\"{%ld",state);
  if( s >= 0 )
  {
    if( CFG_WCKEY(PLR_symType(ptab,s)) || CFG_KEY(PLR_symType(ptab,s)) )
    { string lbl = dotLiteral(PLR_symName(ptab,s),"<>{}|");
      fprintf(SysOut,"|%s",lbl);
      FreeMem(lbl);
    }
    else
    { 
      fprintf(SysOut,"|%s",PLR_symName(ptab,s));
    }
  }
  else
  {
    fprintf(SysOut,"|");
  }
  for( i=0; i < OT_CNT(vaction); i+=2 )
  {
    p = OT_GET(long,vaction,i);
    t = OT_GET(long,vaction,i+1);
    if( p >= -1 ) 
    {
      reduce = C_True;
      if( p >= 0 ) 
      {
        l   = PLR_prodSymCnt(ptab,p);
        sym = PLR_symName(ptab,PLR_prodNonTerm(ptab,p));
        fprintf(SysOut,"|%ld-%s.%s",l,sym,PLR_prodName(ptab,p));
      }
      else
      if( t >= PLR_tokenCnt(ptab) )
      {
        s   = t - PLR_tokenCnt(ptab);
        sym = PLR_symName(ptab,PLR_startSymbol(ptab,s));
        fprintf(SysOut,"|%s",sym);
      }
    }
  }
  fprintf(SysOut,"}\"");
  fprintf(SysOut," shape=record");
  if( reduce )
    fprintf(SysOut," style=filled");
  fprintf(SysOut,"]");
  OT_DEL_T(vaction);
}

static void pim2tdot(PLR_Tab ptab)
{ MAP(long,long) edges = MAP_newPrimMap(),
                 states = collectTNodes(ptab);
  MAPIT itr; long i, j, k, s1, s2, t, s;
  fprintf(SysOut,"\ndigraph t_%s",PLR_language(ptab));
  fprintf(SysOut,"\n{");
  evalTemplate();
  for( i=0; i < PLR_stateCnt(ptab); ++i )
  { ROW(int) vshift = PLR_shiftValues(ptab,i);
    MAP_rmvall(edges);
    for( k=0; k < OT_CNT(vshift); k+=2 )
    {
      s1 = OT_GET(long,vshift,k+1);
      t  = OT_GET(long,vshift,k);
      MAP_ovrdom(edges,s1,i);
      s = MAP_apply(long,states,s1);
      assert0( s < 0 || s == t, "shift symbol mismatch");
      MAP_ovrdom(states,s1,t); // t = 0..tokenCnt-1
    }
    MAP_forItrAsg(j,k,itr,edges) 
    {
      fprintf(SysOut,"\n  node%ld -> node%ld ",i,j);
    }
    OT_DEL_T(vshift);
  }
  for( i=0; i < PLR_nontermCnt(ptab); ++i )
  { ROW(int) vgoto = PLR_gotoValues(ptab,i);
    MAP_rmvall(edges);
    for( j=0; j < OT_CNT(vgoto); j+=2 )
    {
      s1 = OT_GET(long,vgoto,j+1);
      s2 = OT_GET(long,vgoto,j);
      s = MAP_apply(long,states,s2);
      assert0( s < 0 || s == PLR_NTI_TO_NTS(ptab,i), "goto symbol mismatch");
      MAP_ovrdom(states,s2,PLR_NTI_TO_NTS(ptab,i));
      fprintf(SysOut,"\n  node%ld -> node%ld ",s1,s2);
    }
    OT_DEL_T(vgoto);
  }
  for( i=0; i < PLR_stateCnt(ptab); ++i )
  { 
    printTNode(ptab,states,i);
  }
  fprintf(SysOut,"\n}\n");
  MAP_freeMap(edges);
  MAP_freeMap(states);
}

static void pim2rdot(PLR_Tab ptab)
{ MAP(long,SET(long)) products = MAP_newPrimMap();
  MAP(long,long) edges = MAP_newPrimMap();
  SET(long) ntset, pset; long nt, p, s, i, j;
  if( !strcmp(diatype,"R") ) 
    fprintf(SysOut,"\ndigraph r_%s",PLR_language(ptab));
  else
    fprintf(SysOut,"\ndigraph a_%s",PLR_language(ptab));
  fprintf(SysOut,"\n{");
  evalTemplate();
  for( i=0; i < PLR_nontermCnt(ptab); ++i )
  {
    s = PLR_NTI_TO_NTS(ptab,i);
    if( !strcmp(diatype,"A") ) 
      s = PLR_NTS_TO_NTC(ptab,s);
    if( !MAP_defined(products,s) )
    {
      pset = HS_CREATE_ADTSET(long);
      MAP_dfndom(products,s,pset);
      printRNode(ptab,s);
    }
  }
  for( i=0; i < PLR_prodCnt(ptab); ++i )
  {
    nt = PLR_prodNonTerm(ptab,i);
    if( nt < PLR_tokenCnt(ptab) + PLR_nontermCnt(ptab) )
    {
      if( !strcmp(diatype,"A") ) 
        nt = PLR_NTS_TO_NTC(ptab,nt);
      pset = MAP_apply(SET(long),products,nt);
      HS_SET_ELM(i,pset);
    }
  }
  for( i=0; i < PLR_nontermCnt(ptab); ++i )
  { HS_Itr itr;
    nt = PLR_NTI_TO_NTS(ptab,i);
    if( !strcmp(diatype,"A") ) 
      nt = PLR_NTS_TO_NTC(ptab,nt);
    pset = MAP_apply(SET(long),products,nt);
    if( pset != NULL )
    {
      ntset = HS_CREATE_ADTSET(long);
      HS_FORALL(p,itr,pset)
      {
        for( j=0; j < PLR_prodSymCnt(ptab,p); ++j )
        {
          s = PLR_prodSymbol(ptab,p,j);
          if( CFG_NTM(PLR_symType(ptab,s)) )
          {
            if( !strcmp(diatype,"A") ) 
              s = PLR_NTS_TO_NTC(ptab,s);
            HS_SET_ELM(s,ntset);
          }
        }
      }
      HS_FORALL(s,itr,ntset)
      {
        fprintf(SysOut,"\n  node%ld -> node%ld ",nt,s);
      }
      HS_DROP_SET(ntset);
      HS_DROP_SET(pset);
      if( !strcmp(diatype,"A") ) 
        MAP_ovrdom(products,nt,NULL);
    }
  }
  fprintf(SysOut,"\n}\n");
  MAP_freeMap(edges);
  MAP_freeMap(products);
}

int main(int argc, string argv[])
{ PLR_Tab ptab; 
  /* init module */
  PGM_init(argc,argv,CTX_init_pim2dot);
  /* get the parse table */
  ptab = PLR_getTab_file(imgfile);
  /* produce the dot file */
  if( strlen(outfile) > 0 )
    SysOut = OpnFile(outfile,"wt");
  else SysOut = stdout;
  if( !strcmp(diatype,"T") ) pim2tdot(ptab);
  else                       pim2rdot(ptab);
  /* free the parse table */
  PLR_delTab(ptab);
  /* quit module */
  PGM_quit();
  BUG_CORE;
  return(0);
}
