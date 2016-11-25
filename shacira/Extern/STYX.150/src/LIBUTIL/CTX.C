/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [ctx.c]                     Program Context                              */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

#include "ctx_app.h"

#include "sink.h"
#include "literal.h"
#include "pathes.h"
#include "binimg.h"
#include "ctx_imp.h"

/*!
   <p>This module [ctx] provides functions for the definition of a program context and 
   the verification of the current commandline against the current program context.

   <p>The definition interface will be used by the <a href="cmdlib.htm">CMD Compiler</a> 
   which parses and evaluates a command decription file [.cmd], constructs a program context 
   out of it and finally makes it persistent.

   <p>The application interface will be used by the applications and the generated
   program specific context modules.
   <br>
*/

/* ------------------------- Globals & Constants -------------------------- */

#define CONTEXT        CTX_T_IMP(CTX_ctx_val())

#define EXTENSION      ".cim"

#define Num_MIN        "-2147483648" /* min value of a "long int" */
#define Num_MAX        "2147483647"  /* max value of a "long int" */

static int errcnt = 0;

/*I------------------------ Definition interface -------------------------- */

CTX_T CTX_new(short cnt, string name)
/* make new context for program 'name' and 'cnt' arguments */
{ CTX_T_Imp ctx; int i;

  BUG_NULL(name);
  ctx = New(CTX_T_Imp);
  ctx->cnt = cnt;
  ctx->prg = StrCopy(name);
  ctx->tbl = (CTX_L_Imp)NewMem(cnt * SizeOf(CTX_L_Imp));
  for( i=0; i < cnt; ++i )
    ctx->tbl[i].asg = False;
  return( ctx );
}

void  CTX_free(CTX_T ctx)
/* drop context 'ctx' */
{ int cnt, i;

  BUG_NULL(ctx);
  cnt = CTX_T_IMP(ctx)->cnt;
  FreeMem(CTX_T_IMP(ctx)->prg);
  if( cnt                                               && 
      CTX_T_IMP(ctx)->tbl[cnt-1].asg                    &&
      ! strcmp(CTX_T_IMP(ctx)->tbl[cnt-1].ide,CTX_VARG)  )
  { StdCPtr* vargs = (StdCPtr*)CTX_T_IMP(ctx)->tbl[cnt-1].val;

    if( CTX_T_IMP(ctx)->tbl[cnt-1].typ == CTX_PATH   ||
        CTX_T_IMP(ctx)->tbl[cnt-1].typ == CTX_NAME   ||
        CTX_T_IMP(ctx)->tbl[cnt-1].typ == CTX_STRING  )
      for( i=1; i <= (int)vargs[0]; ++i ) FreeMem(vargs[i]);
    FreeMem(CTX_T_IMP(ctx)->tbl[cnt-1].ide);
    FreeMem(vargs);
    --cnt;
  }
  for( i=0; i < cnt; ++i )
  {
    if( CTX_T_IMP(ctx)->tbl[i].asg &&
        ( CTX_T_IMP(ctx)->tbl[i].typ == CTX_PATH ||
          CTX_T_IMP(ctx)->tbl[i].typ == CTX_NAME ||
          CTX_T_IMP(ctx)->tbl[i].typ == CTX_STRING ) )
      FreeMem(CTX_T_IMP(ctx)->tbl[i].val);
    FreeMem(CTX_T_IMP(ctx)->tbl[i].ide);
    if( CTX_T_IMP(ctx)->tbl[i].cat == CTX_OPT || 
        CTX_T_IMP(ctx)->tbl[i].cat == CTX_ENV  )
      FreeMem(CTX_T_IMP(ctx)->tbl[i].dft);
  }
  FreeMem(CTX_T_IMP(ctx)->tbl);
  FreeMem(ctx);
}

void  CTX_set
      (
        CTX_T ctx, short idx, string ide, 
        byte cat, byte typ, string dft
      )
/* assign argument 'ide' of category 'cat', with type 'typ' and 
   default value 'dft' to context entry ctx[idx] 
*/
{
  BUG_NULL(ctx); BUG_NULL(ide);
  BUG_RNG0(idx,CTX_T_IMP(ctx)->cnt);
  CTX_T_IMP(ctx)->tbl[idx].ide = StrCopy(ide);
  CTX_T_IMP(ctx)->tbl[idx].cat = cat;
  CTX_T_IMP(ctx)->tbl[idx].typ = typ;
  if( CTX_T_IMP(ctx)->tbl[idx].cat == CTX_OPT || 
      CTX_T_IMP(ctx)->tbl[idx].cat == CTX_ENV  )
    CTX_T_IMP(ctx)->tbl[idx].dft = dft;
}

void  CTX_put(string env, CTX_T ctx)
/* put binary image of context 'ctx' */
{ string hd; int i;

  BUG_NULL(env); BUG_NULL(ctx);
  putBgn(env,CTX_T_IMP(ctx)->prg,EXTENSION);
  hd = Str_printf
       (
         "[%s%s] Binary Context Image for %s\n",
         CTX_T_IMP(ctx)->prg,EXTENSION,CTX_T_IMP(ctx)->prg
       );
  putHeader(hd,"cim",1,0);
  putWord(CTX_T_IMP(ctx)->cnt);
  putString(CTX_T_IMP(ctx)->prg);
  for( i=0; i < CTX_T_IMP(ctx)->cnt; ++i )
  {
    putString(CTX_T_IMP(ctx)->tbl[i].ide);
    putByte(CTX_T_IMP(ctx)->tbl[i].cat);
    putByte(CTX_T_IMP(ctx)->tbl[i].typ);
    if( CTX_T_IMP(ctx)->tbl[i].cat == CTX_OPT || 
        CTX_T_IMP(ctx)->tbl[i].cat == CTX_ENV  )
      putString(CTX_T_IMP(ctx)->tbl[i].dft);
  }
  FreeMem(hd);
  putEnd();
}

CTX_T CTX_get(string env, string name)
/* get context from binary image [$'env'/'name'.cim] */
{ CTX_T_Imp ctx; short cnt; int i;

  BUG_NULL(env); BUG_NULL(name);
  getBgn(env,name,EXTENSION);
  getHeader("cim",1,0);
  getWord(&cnt);
  ctx = New(CTX_T_Imp);
  ctx->cnt = cnt;
  getString(&ctx->prg);
  ctx->tbl = (CTX_L_Imp)NewMem(cnt * SizeOf(CTX_L_Imp));
  for( i=0; i < ctx->cnt; ++i )
  {
    getString(&ctx->tbl[i].ide);
    getByte(&ctx->tbl[i].cat);
    getByte(&ctx->tbl[i].typ);
    if( ctx->tbl[i].cat == CTX_OPT || 
        ctx->tbl[i].cat == CTX_ENV  )
      getString(&ctx->tbl[i].dft);
    ctx->tbl[i].asg = False;
  }
  getEnd();
  return ctx;
}

void CTX_usage(CTX_T ctx)
/* print usage for context 'ctx' */
{ CTX_T_Imp ctx_imp = CTX_T_IMP(ctx); int i;

  fprintf(STDERR,"Usage: %s", ctx_imp->prg);
  for (i = 0; i < ctx_imp->cnt; i++)
    if (ctx_imp->tbl[i].cat == CTX_OPT)
    {
      fprintf(STDERR," [-%s",ctx_imp->tbl[i].ide);
      switch( ctx_imp->tbl[i].typ )
      {
        case CTX_FLAG   : break;
        case CTX_PATH   : fprintf(STDERR,"=path"); break;
        case CTX_STRING : fprintf(STDERR,"=string"); break;
        case CTX_NAME   : fprintf(STDERR,"=name"); break;
        case CTX_INT    : fprintf(STDERR,"=int"); break;
        default         : fprintf(STDERR,"???(%d)",ctx_imp->tbl[i].cat); break;
      }
      fprintf(STDERR,"]");
    }
  for (i = 0; i < ctx_imp->cnt; i++)
    if(ctx_imp->tbl[i].cat == CTX_ARG)
      fprintf(STDERR," %s",ctx_imp->tbl[i].ide);
  FNL(STDERR);
  STD_ERREXIT;
}

void CTX_C_Modul(string Environ, CTX_T Ctx)
/* compiles context 'ctx' to [$'Environ'/'Name'_cim.c] */
{ FILE *tf; CTX_T_Imp ctx = CTX_T_IMP(Ctx); char fid[9]; int maxlen=0,i; 

  sprintf(fid,"%.4s_cim",ctx->prg);
  tf = OpenPath(Environ,fid,".c","wt");
  fprintf(tf,"/* [%s.c] Context table for '%s'  */\n\n", fid, ctx->prg);
  fprintf(tf,"#include \"ctx.h\"\n\n");
  fprintf(tf,"void CTX_init_%s(int argc, c_string argv[])\n",ctx->prg);
  fprintf(tf,"{ CTX_T ctx;\n");
  fprintf(tf,"  ctx = CTX_new(%d,\"%s\");\n",ctx->cnt,ctx->prg);
  for (i = 0; i < ctx->cnt; i++)
    maxlen = MAX(strlen(ctx->tbl[i].ide),maxlen);
  for (i = 0; i < ctx->cnt; i++)
  {
    fprintf(tf,"  CTX_set(ctx,%2d,",i);
    fprintf(tf,"\"%s\",%*s",ctx->tbl[i].ide,maxlen-strlen(ctx->tbl[i].ide),"");
    switch( ctx->tbl[i].cat )
    {
      case CTX_ARG : fprintf(tf,"CTX_ARG,"); break;
      case CTX_OPT : fprintf(tf,"CTX_OPT,"); break;
      case CTX_ENV : fprintf(tf,"CTX_ENV,"); break;
      default      : fprintf(tf,"%7d,",ctx->tbl[i].cat); break;
    }
    switch( ctx->tbl[i].typ )
    {
      case CTX_FLAG   : fprintf(tf,"CTX_FLAG,  "); break;
      case CTX_PATH   : fprintf(tf,"CTX_PATH,  "); break;
      case CTX_STRING : fprintf(tf,"CTX_STRING,"); break;
      case CTX_NAME   : fprintf(tf,"CTX_STRING,"); break;
      case CTX_INT    : fprintf(tf,"CTX_INT,   "); break;
      default         : fprintf(tf,"%10d,",ctx->tbl[i].cat); break;
    }
    if( ctx->tbl[i].cat == CTX_OPT || 
        ctx->tbl[i].cat == CTX_ENV  )
    { string s = LIT_c_str_lit(ctx->tbl[i].dft);

      fprintf(tf,"StrCopy(%s)",s); FreeMem(s);
    }
    else
      fprintf(tf,"\"\"");
    fprintf(tf,");\n");
  }
  fprintf(tf,"  CTX_ctx_set(ctx);\n");
  fprintf(tf,"  CTX_interprete(argc, argv);\n");
  fprintf(tf,"}\n");
  fclose(tf);
}

static void CTX_prVal(int typ, Abs_T val, bool shell)
{
  switch( typ )
  {
    case CTX_FLAG   :
      fprintf(STDOUT,"%s",((bool)val)?"true":"false"); 
      break;
    case CTX_PATH   :
      if( shell ) fprintf(STDOUT,"%s",(string)val);
      else        fprintf(STDOUT,"<%s>",(string)val);
      break;
    case CTX_STRING :
      if( shell ) fprintf(STDOUT,"'%s'",(string)val);
      else        fprintf(STDOUT,"\"%s\"",(string)val);
      break;
    case CTX_NAME   :
      fprintf(STDOUT,"%s",(string)val);
      break;
    case CTX_INT    :
      fprintf(STDOUT,"%ld",(long)val);
      break;
    default         : BUG;
  }
}

void CTX_sh_list(void)
/* print shell context */
{ int i;

  for (i = 0; i < CONTEXT->cnt; i++)
  {
    fprintf(STDOUT,"%s=",CONTEXT->tbl[i].ide);
    if (CONTEXT->tbl[i].asg)
    {
      if( i == CONTEXT->cnt - 1 && ! strcmp(CONTEXT->tbl[i].ide,CTX_VARG) )
        fprintf(STDOUT,"%d",(int)((Abs_T*)CONTEXT->tbl[i].val)[0]);
      else CTX_prVal(CONTEXT->tbl[i].typ,CONTEXT->tbl[i].val,True);
    }
    NL;
  }
}

void CTX_list(CTX_T ctx)
/* DEBUG; print context 'ctx' */
{ CTX_T_Imp ctx_imp  = CTX_T_IMP(ctx); int maxlen=0,i;

  fprintf(STDOUT,"Command %s\n", ctx_imp->prg);
  for (i = 0; i < ctx_imp->cnt; i++)
    maxlen = MAX(strlen(ctx_imp->tbl[i].ide),maxlen);
  for (i = 0; i < ctx_imp->cnt; i++)
  {
    fprintf(STDOUT,"--  ");
    switch( ctx_imp->tbl[i].cat )
    {
      case CTX_ARG : fprintf(STDOUT,"Arg"); break;
      case CTX_OPT : fprintf(STDOUT,"Opt"); break;
      case CTX_ENV : fprintf(STDOUT,"Env"); break;
      default      : fprintf(STDOUT,"???(%d)",ctx_imp->tbl[i].cat); break;
    }
    fprintf(STDOUT," %-*s : ",maxlen,ctx_imp->tbl[i].ide);
    switch( ctx_imp->tbl[i].typ )
    {
      case CTX_FLAG   : fprintf(STDOUT,"flag  "); break;
      case CTX_PATH   : fprintf(STDOUT,"path  "); break;
      case CTX_STRING : fprintf(STDOUT,"string"); break;
      case CTX_NAME   : fprintf(STDOUT,"name  "); break;
      case CTX_INT    : fprintf(STDOUT,"int   "); break;
      default         : fprintf(STDOUT,"???(%d)",ctx_imp->tbl[i].cat); break;
    }
    fprintf(STDOUT," = ");
    if (ctx_imp->tbl[i].asg)
    {
      if( i == ctx_imp->cnt - 1 && ! strcmp(ctx_imp->tbl[i].ide,CTX_VARG) )
      { int cnt = (int)((Abs_T*)ctx_imp->tbl[i].val)[0], j;
        fprintf(STDOUT,"%d",cnt);
        for( j=1; j <= cnt; ++j )
        {
          fprintf(STDOUT,"\n  %s(%3d) = ",CTX_VARG,j);
          CTX_prVal(ctx_imp->tbl[i].typ,((Abs_T*)ctx_imp->tbl[i].val)[j],False);
        }
      }
      else CTX_prVal(ctx_imp->tbl[i].typ,ctx_imp->tbl[i].val,False);
    }
    else
      fprintf(STDOUT,"[UNDEFINED]");
    NL;
  }
}

static long Num_error(string val, string msg)
{
  fprintf(STDOUT,"[Usage] : %s : %s\n",msg,val);
  errcnt += 1; return 0;
}

static bool Num_less(bool sa, string va, bool sb, string vb)
/* whether to strings containing numbers are less w.r.t. numeric order */
/* sa, sb are the signs, true means negative */
/* va, vb are the digits without leading 0s  */
{
  if (sa != sb) return sa && !sb;
  if (sa) return Num_less(0,vb,0,va);
  if (strlen(va) != strlen(vb)) return strlen(va) < strlen(vb);
  return strcmp(va,vb) < 0;
}

static long Num_conv(string val)
/* converts a string to an integer                                       */
/* this routine is very general and not restricted to short, int or long */
{ bool sign = (val[0] == '-'); int slen = strlen(val), i, j; long res;

  /* skip leading 0s */
  if (val[sign] == 0)
    return Num_error(val,"Zahl erwarted");
  for (i = sign; i < slen-1; i++) if (val[i] != '0') break;
  /* check digits */
  for (j = i; j < slen; j++)
    if ('0' > val[j] || val[j] > '9')
      return Num_error(val,"Zahl erwarted");
  /* check value range */
  if (Num_less(sign,val+i,Num_MIN[0]=='-',Num_MIN+(Num_MIN[0]=='-')))
    return Num_error(val,"zu kleine Zahl");
  if (Num_less(Num_MAX[0]=='-',Num_MAX+(Num_MAX[0]=='-'),sign,val+i))
    return Num_error(val,"zu grosse Zahl");
  /* actual conversion */
  res = 0;
  for (j = i; j < slen; j++)
    res = 10 * res + (val[j]-'0');
  return sign ? -res : res;
}

static Abs_T CTX_convert(int typ, string val)
/* converts ctx-typed value val */
{
  switch( typ )
  {
    case CTX_FLAG :
      if (strcmp(val,"true" ) == 0) return (Abs_T) 1;
      if (strcmp(val,"false") == 0) return (Abs_T) 0;
      fprintf(STDERR,"[Usage]: '%s' is not a boolean value",val);
      errcnt += 1; return (Abs_T) 0;
    case CTX_PATH :
      return (Abs_T) StrCopy(val);
    case CTX_NAME :
      return (Abs_T) StrCopy(val);
    case CTX_STRING :
      return (Abs_T) StrCopy(val);
    case CTX_INT :
      return (Abs_T) Num_conv(val);
    default:
      BUG; return (Abs_T) 0;
  }
}

static void CTX_assing(int idx, string val)
{
  if (idx < 0) return;
  if (CONTEXT->tbl[idx].cat != CTX_OPT
   && CONTEXT->tbl[idx].cat != CTX_ARG
   && CONTEXT->tbl[idx].cat != CTX_ENV )
  {
    fprintf(STDERR,"[Usage]: cannot assign to option '%s'\n",
            CONTEXT->tbl[idx].ide);
    errcnt += 1; return;
  }
  if (CONTEXT->tbl[idx].asg)
  {
    fprintf(STDERR,"[Usage]: option '%s' assigned more than once\n",
            CONTEXT->tbl[idx].ide);
    errcnt += 1; return;
  }
  CONTEXT->tbl[idx].asg = True;
  CONTEXT->tbl[idx].val = CTX_convert(CONTEXT->tbl[idx].typ,val);
}

static void CTX_varg_asgn(int vargc, string vargv[])
{ Abs_T* vargs = (Abs_T*)NewMem((vargc + 1) * sizeof(Abs_T)); int i;

  vargs[0] = (Abs_T)vargc;
  for( i=0; i < vargc; ++i )
    vargs[i+1] = CTX_convert(CONTEXT->tbl[CONTEXT->cnt-1].typ,vargv[i]);
  CONTEXT->tbl[CONTEXT->cnt-1].asg = True;
  CONTEXT->tbl[CONTEXT->cnt-1].val = (StdCPtr)vargs;
}

static void CTX_option_flag(string flg)
{ int idx = (int)CTX_eval(flg,True);

  if (idx < 0)
  {
    fprintf(STDERR,"[Usage]: invalid option '%s'\n",flg);
    errcnt += 1;
    return;
  }
  if ((CONTEXT->tbl[idx].cat != CTX_OPT &&
       CONTEXT->tbl[idx].cat != CTX_ENV  ) ||
      CONTEXT->tbl[idx].typ != CTX_FLAG     )
  {
    fprintf(STDERR,"[Usage]: Option '%s' is not a flag\n",flg);
    errcnt += 1;
  }
  CTX_assing(idx,strcmp(CONTEXT->tbl[idx].dft,"true")?"true":"false");
}

static void CTX_option_asgn(string var, string val)
/* NOTE: var must be freed */
{ int idx = (int)CTX_eval(var,True);

  if (idx < 0)
  {
    fprintf(STDERR,"[Usage]: invalid option '%s'\n",var);
    errcnt += 1;
  }
  else
    CTX_assing(idx,val);
  FreeMem(var);
}

static int CTX_args(void)
/* number of static arguments in current context */
{ int cnt = 0, i;

  for (i = 0; i < CONTEXT->cnt; i++)
    cnt += ( CONTEXT->tbl[i].cat == CTX_ARG       && 
             ! CONTEXT->tbl[i].asg                &&
             strcmp(CONTEXT->tbl[i].ide,CTX_VARG) );
  return cnt;
}

static void CTX_argument(string arg)
{ int i;

  for (i = 0; i < CONTEXT->cnt; i++)
    if (CONTEXT->tbl[i].cat == CTX_ARG && !CONTEXT->tbl[i].asg)
      break;
  if (i >= CONTEXT->cnt || ! strcmp(CONTEXT->tbl[i].ide,CTX_VARG))
  {
    fprintf(STDERR,"[Usage]: unexpected argument '%s'\n",arg);
    errcnt += 1; return;
  }
  CTX_assing(i,arg);
}

static string loc_dirname; /* the path of the actual program executable */

string CTX_dirname(void)
/* path of the current program */
{
  return loc_dirname;
}

static void prep_loc_dirname(string argv0)
/* prepares 'loc_dirname' */
{ int i,len = strlen(argv0);
  loc_dirname = StrCopy(argv0);
  for 
  (
    i = len; 
    i>0 && loc_dirname[i-1] != '\\' && loc_dirname[i-1] != '/';
    i--
  ); /* noop */
  if (i>0) loc_dirname[i-1] = 0;
  for (; i>=0; i--)
   if (loc_dirname[i] == '\\')
     loc_dirname[i] = '/';
}

void CTX_interprete(int argc, string argv[])
/* process current program context */
{ int first_varg = argc, i;
  prep_loc_dirname(argv[0]);
  if (argc == 2 && !strcmp(argv[1],"-?" )) { CTX_usage(CONTEXT); STD_ERREXIT; }
  if (argc == 2 && !strcmp(argv[1],"-??")) { CTX_list (CONTEXT); STD_ERREXIT; }
  if( CONTEXT->cnt && ! strcmp(CONTEXT->tbl[CONTEXT->cnt-1].ide,CTX_VARG) )
  { int cnt = CTX_args(), idx = 1;

    for (i = 1; i < argc; i++) 
      if (argv[i][0] == '-') idx = i + 1;
      else
      {
        if( cnt > 0 ) 
        {
          idx = i + 1; --cnt;
        }
      }
    first_varg = idx;
  }
  /* process options */
  for (i = 1; i < MIN(argc,first_varg); i++) 
  {
    if (argv[i][0] == '-')
    { string opt = argv[i]; int sl = strlen(opt), j;

      for( j = 0; j < sl; j++) if (opt[j] == '=') break;
      if (j >= sl)
        CTX_option_flag(argv[i]+1);
      else
        CTX_option_asgn(SubStrCopy(argv[i]+1,j-1),argv[i]+j+1);
    }
  }
  /* process arguments */
  for (i = 1; i < MIN(argc,first_varg); i++) 
  {
    if (argv[i][0] != '-') CTX_argument(argv[i]);
  }
  /* process variable arguments */
  if( CONTEXT->cnt && ! strcmp(CONTEXT->tbl[CONTEXT->cnt-1].ide,CTX_VARG) )
  {
    if( first_varg < argc ) 
      CTX_varg_asgn(argc-first_varg,&argv[first_varg]);
    else
      CTX_varg_asgn(0,(string*)NULL);
  }
  /* process defaults */
  for (i = 0; i < CONTEXT->cnt; i++)
  if (!CONTEXT->tbl[i].asg)
  {
    switch( CONTEXT->tbl[i].cat )
    {
      case CTX_ARG :
        fprintf(STDERR,"[Usage]: paramenter '%s' expected\n",
                CONTEXT->tbl[i].ide);
        errcnt += 1; break;
      case CTX_OPT :
        CTX_assing(i,CONTEXT->tbl[i].dft);
        break;
      case CTX_ENV :
        if (getenv(CONTEXT->tbl[i].ide))
          CTX_assing(i,getenv(CONTEXT->tbl[i].ide));
        else
        if( *(CONTEXT->tbl[i].dft) != '\0' )
          CTX_assing(i,CONTEXT->tbl[i].dft);
        else
        {
          fprintf(STDERR,"[Usage]: shell variable '%s' expected\n",
                  CONTEXT->tbl[i].ide);
          errcnt += 1;
        }
        break;
      default      : BUG;
    }
  }
  if (errcnt > 0)
    CTX_usage(CONTEXT);
}

/*I------------------------ Application interface ------------------------- */

void CTX_init(int argc, string argv[])
/* initialize and process current program context */
{ CTX_T ctx; string stdnam;

  assert0(argc>0,"interner Fehler bei der Uebergabe der Kommandozeile");
  /* MSDOS produces d:\Path...\ProgId.EXE, the full pathname in argv[0] */
  /* UNIX produces ProgId or Path/ProgId, in dependance of the call     */
  /* thus we remove prefixes and suffixes to get the program name       */
  stdnam = BaseFile(argv[0]);
  CTX_ctx_set(CTX_new(1,"[CTX_init]"));
  CTX_set(CONTEXT,0,"PATH",CTX_ENV,CTX_PATH,"");
  CTX_interprete(1, argv);
  ctx = CTX_get("PATH",stdnam);
  CTX_free(CONTEXT);
  CTX_ctx_set(ctx);
  FreeMem(loc_dirname);
  CTX_interprete(argc,argv);
  FreeMem(stdnam);
}

void CTX_quit(void)
/* drop current program context */
{
  CTX_free(CONTEXT);
  FreeMem(loc_dirname);
}
