/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [lim2dot.c]      Scanner table visualisation ( lim -> dot )              */
/*                                                                          */
/* Copyright (c) 2004 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "stdosx.h"

#include "hmap.h"
#include "pgm_base.h"
#include "scn_imp.h"
#include "gstream.h"
#include "line_scn.h"
#include "pathes.h"
#include "sink.h"

#include "lim2dot_cim.h"

#define imgfile  CTX_EVAL(string,"Img")
#define tmplfile CTX_EVAL(string,"Template")
#define outfile  CTX_EVAL(string,"OutFile")

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

static void edgeCharacter(Sink snk, wc_char wc)
{ byte b = (byte)wc;
  if( ((wc_char)b) == wc )
  {
    switch(b)
    {
      case '\r': Sink_printf(snk,"\\r");  break;
      case '\n': Sink_printf(snk,"\\n");  break;
      case '\t': Sink_printf(snk,"\\t");  break;
      case '\\': Sink_printf(snk,"\\\\"); break;
      case '"' : Sink_printf(snk,"\\\""); break;
      default  :
        if( isprint(b) && b != ' ' ) 
          Sink_printf(snk,"%c",b);
        else Sink_printf(snk,"0x%02x",b);
    }
  }
  else Sink_printf(snk,"0x%08lx",wc);
}

static c_string edgeLabel(MAP(wc_char,wc_char) edge)
{ Sink snk = Sink_open();
  MAPIT itr; wc_char lwr, upr;
  MAP_forItrAsg(lwr,upr,itr,edge)
  {
    if( lwr == upr )
    {
      Sink_printf(snk," "); 
      edgeCharacter(snk,lwr);
    }
    else
    {
      Sink_printf(snk," "); 
      edgeCharacter(snk,lwr);
      Sink_printf(snk,"-"); 
      edgeCharacter(snk,upr);
    }
  }
  return Sink_close(snk);
}

static void scn2dot(scn_t scn)
{ long i, j, k, t; 
  for( i=0; i < scn->States; ++i )
  { 
    for( k=0; k < scn->States; ++k )
    { MAP(wc_char,wc_char) edge = MAP_newPrimMap();
      c_string lbl = NULL;
      for( j=scn->StaEdg[i]; j < scn->StaEdg[i+1]; ++j )
      { 
        if( k+1 == scn->EdgeS[j] ) // follow state = 0 ==> error
        { wc_char lwr = scn->EdgeC[j], 
                  upr = j > scn->StaEdg[i] ? scn->EdgeC[j-1]-1 : lwr;
          MAP_dfndom(edge,lwr,upr);
        }
      }
      if( MAP_count(edge) > 0 )
      {
        lbl = edgeLabel(edge);
        fprintf
        (
          SysOut,"\n    node%ld -> node%ld [label=\"%s\"]", i,k,lbl 
        );
        FreeMem(lbl);
      }
      MAP_freeMap(edge);
    }
    t = scn->StaFin[i];
    if( t > 0 )
    {
      fprintf(SysOut,"\n    node%ld [label=\"%s\",shape=box]",i,scn->TokId[t]);
    }
    else
    if( i==0 )
    {
      fprintf(SysOut,"\n    node0 [shape=box]");
    }
  }
}

static void lim2dot(scn_t scn)
{
  fprintf(SysOut,"\ndigraph %s",scn->Name);
  fprintf(SysOut,"\n{");
  evalTemplate();
  if( scn->Groups == 0 ) 
  {
    scn2dot(scn);
  }
  else
  { int i, j, g;
    for( i=0; i < scn->Groups; ++i )
    {
      fprintf(SysOut,"\n  subgraph %s",scn->GrpScn[i]->Name);
      fprintf(SysOut,"\n  {");
      scn2dot(scn->GrpScn[i]);
      fprintf(SysOut,"\n  }\n");
    }
    for( i=0; i < scn->Groups; ++i )
    {
      for( j=0; i < scn->GrpScn[i]->Tokens; ++j )
      {
        g = scn->GrpScn[i]->Switch[j];
        if( g >= 0 )
        {
          fprintf
          (
            SysOut,"\n  %s -> %s [label=\"%s\"]",
            scn->GrpScn[i]->Name,
            scn->GrpScn[g]->Name,
            scn->GrpScn[i]->TokId[j]
          );
        }
      }
    }
    fprintf(SysOut,"\n  %s [shape=box]",scn->Name);
  }
  fprintf(SysOut,"\n}\n");
}

int main(int argc, string argv[])
{ Scn_T scn; 
  /* init module */
  PGM_init(argc,argv,CTX_init_lim2dot);
  /* get the scanner */
  Scn_get_file(imgfile,&scn);
  /* produce the dot file */
  if( strlen(outfile) > 0 )
    SysOut = OpnFile(outfile,"wt");
  else SysOut = stdout;
  lim2dot(Scn_IMP(scn));
  /* free the scanner */
  Scn_free(scn);
  /* quit module */
  PGM_quit();
  BUG_CORE;
  return(0);
}
