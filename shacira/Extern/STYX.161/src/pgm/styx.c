/* ------------------------------------------------------------------------- */
/*                                                                           */
/* [styx.c]                     STYX Compiler                                */
/*                   - realizes an abstract syntax tree -                    */
/*                                                                           */
/* Copyright (c) 1993 by D\olle, Manns.                                      */
/* ------------------------------------------------------------------------- */

#include "stdosx.h"

#include "pathes.h"
#include "styx_gen.h"

#include "styx_cim.h"

#define language   CTX_EVAL(string,"Language")
#define verbose    CTX_EVAL(bool,"verbose")
#define diagnose   CTX_EVAL(bool,"diagnose")
#define makeIMG    CTX_EVAL(bool,"makeIMG")
#define makeINT    CTX_EVAL(bool,"makeINT")
#define makeANT    CTX_EVAL(bool,"makeANT")
#define makeC      CTX_EVAL(bool,"makeC")
#define export     CTX_EVAL(bool,"export")
#define shortform  CTX_EVAL(bool,"shortform")

static void generate(Styx_T styctx)
{ PLR_Tab PTab = (PLR_Tab)NULL;
  if( shortform ) STYX_set_shortform(styctx,shortform);
  if( makeIMG ) STYX_createTabIMG(styctx,"BINSTYX");
  if( makeC   ) STYX_createTabC(styctx,"GENSTYX");
  if( export  ) STYX_exportTab(styctx,"BINSTYX");
  STYX_get_tables(styctx,&PTab,_);
  if( PTab != (PLR_Tab)NULL )
  {
    STYX_createABS(styctx,"GENSTYX");
    if( makeC || makeINT )
    {
      STYX_createIntC(styctx,"GENSTYX");
    }
    if( makeANT )
    {
      STYX_createAntC(styctx,"GENSTYX");
    }
  }
  if( !makeIMG && !makeINT && !makeC && !export )
    fprintf(STDERR,"Note: No file created.\n");
}

int main(int argc, string argv[])
{ StyxApp_T styapp; Styx_T styctx, rng; 
  MAP(symbol,Styx_T) embed = (MAP(_,_))NULL;
  MAPIT itr; symbol dom; int rc;

  CTX_init_styx(argc,argv);
  if (verbose) 
  {
    fprintf(STDERR,"Welcome to Styx %s as of '%s'\n",VERSION,__DATE__);
  }
  styapp = STYX_app_init();
  if( styapp != (StyxApp_T)NULL )
  {
    styctx = STYX_init(styapp,language,NULL,verbose,diagnose);
    if( styctx != (Styx_T)NULL )
    { c_string filename = MkPath("SPESTYX",language,".sty",'p');
      rc = STYX_compile_file(styctx,filename,"SPESTYX");
      FreeMem(filename);
      if( rc == 0 )
      {
        generate(styctx);
        embed = STYX_get_embed(styctx);
        if( embed != (MAP(_,_))NULL )
        {
          MAP_forItrAsg(dom,rng,itr,embed)
          {
            generate(rng);
          }
          MAP_freeMap(embed);
        }
      }
      STYX_quit(styctx);
    }
    else fprintf(STDERR,"'%s' compilation init failed.\n",language);
  }
  else fprintf(STDERR,"Styx application init failed.\n");
  STYX_app_quit(styapp);
  CTX_quit();
  BUG_CORE;
  return 0;
}

