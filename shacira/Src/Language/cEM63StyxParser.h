//## begin module%4380553D004C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4380553D004C.cm

//## begin module%4380553D004C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4380553D004C.cp

//## Module: cEM63StyxParser%4380553D004C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Language\cEM63StyxParser.h

#ifndef cEM63StyxParser_h
#define cEM63StyxParser_h 1

//## begin module%4380553D004C.includes preserve=yes

#include "stdosx.h"    // base header STYX library
#include "scn_base.h"  // scanner
#include "scn_pre.h"   // scanner preprocessor
#include "ptm_pp.h"    // Pretty Printer
#include "ptm_gen.h"   // parse & term construction
#include "gls.h"       // general language services
#include "symbols.h"   // symbol table
#include "hmap.h"      // hash maps
#include "EM63_lim.h"  // EM63 scanner table
#include "EM63_pim.h"  // EM63 parser table
#include "EM63_int.h"  // EM63 language interface

//## end module%4380553D004C.includes

// cEM63Parser
#include "Language/cEM63Parser.h"

class __DLL_EXPORT__ cVarRef;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cEM63Session;
class __DLL_EXPORT__ cDownloadCmd;
class __DLL_EXPORT__ cUploadCmd;
class __DLL_EXPORT__ cSetCmd;
class __DLL_EXPORT__ cGetInfoCmd;
class __DLL_EXPORT__ cGetIdCmd;
class __DLL_EXPORT__ cEventlogCmd;
class __DLL_EXPORT__ cReportCmd;
class __DLL_EXPORT__ cAbortCmd;
class __DLL_EXPORT__ cCyclicCondition;
class __DLL_EXPORT__ cInterval;
class __DLL_EXPORT__ cParamCondition;
class __DLL_EXPORT__ cTimeCondition;
class __DLL_EXPORT__ cCondition;
class __DLL_EXPORT__ cEM63Interface;
class __DLL_EXPORT__ cEM63Job;
class __DLL_EXPORT__ cStyxParser;

//## begin module%4380553D004C.additionalDeclarations preserve=yes
//## end module%4380553D004C.additionalDeclarations


//## begin cEM63StyxParser%4380553D004C.preface preserve=yes
//## end cEM63StyxParser%4380553D004C.preface

//## Class: cEM63StyxParser%4380553D004C
//## Category: Language%3E0C4A4402CD
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%438057000381;cContext { -> F}
//## Uses: <unnamed>%43805715031D;cVarRef { -> F}
//## Uses: <unnamed>%4395DF9802AD;cEM63Session { -> F}
//## Uses: <unnamed>%43A2DCDA00EC;cEM63Job { -> F}
//## Uses: <unnamed>%43A417C102BF;cFileSystemUtils { -> F}
//## Uses: <unnamed>%43A6ABFB017D;cTimeCondition { -> F}
//## Uses: <unnamed>%43A6AC0203A0;cParamCondition { -> F}
//## Uses: <unnamed>%43A6AC0B0064;cInterval { -> F}
//## Uses: <unnamed>%43A6B631001F;cCyclicCondition { -> F}
//## Uses: <unnamed>%43AABE3202F5;cEM63Interface { -> F}
//## Uses: <unnamed>%43B25E340269;cReportCmd { -> F}
//## Uses: <unnamed>%43B25E3D00A1;cEventlogCmd { -> F}
//## Uses: <unnamed>%43B25E450179;cGetIdCmd { -> F}
//## Uses: <unnamed>%43B25E4D01E4;cGetInfoCmd { -> F}
//## Uses: <unnamed>%43B25E540388;cUploadCmd { -> F}
//## Uses: <unnamed>%43B25E5C0385;cDownloadCmd { -> F}
//## Uses: <unnamed>%43B25E960066;cCondition { -> F}
//## Uses: <unnamed>%43B29E6D02F5;cStyxParser { -> F}
//## Uses: <unnamed>%43B2C5ED0192;cSetCmd { -> F}
//## Uses: <unnamed>%43BA4FD20019;cAbortCmd { -> F}

class __DLL_EXPORT__ cEM63StyxParser : public cEM63Parser  //## Inherits: <unnamed>%438055EF00BD
{
  //## begin cEM63StyxParser%4380553D004C.initialDeclarations preserve=yes
public:
  //## end cEM63StyxParser%4380553D004C.initialDeclarations

    //## Constructors (generated)
      cEM63StyxParser();

      cEM63StyxParser(const cEM63StyxParser &right);

    //## Destructor (generated)
      virtual ~cEM63StyxParser();


    //## Other Operations (specified)
      //## Operation: ParseSessionRequest%1134738526
      virtual BOOL_T ParseSessionRequest (cEM63Session *session, CONST_STRING_T file, CONST_STRING_T source_code);

      //## Operation: ParsePresentationRequest%1134738529
      virtual BOOL_T ParsePresentationRequest (cEM63Session *session, cEM63Job *job, CONST_STRING_T file, CONST_STRING_T source_code);

  public:
    // Additional Public Declarations
      //## begin cEM63StyxParser%4380553D004C.public preserve=yes
      //## end cEM63StyxParser%4380553D004C.public

  protected:
    // Additional Protected Declarations
      //## begin cEM63StyxParser%4380553D004C.protected preserve=yes
      //## end cEM63StyxParser%4380553D004C.protected

  private:
    // Additional Private Declarations
      //## begin cEM63StyxParser%4380553D004C.private preserve=yes
      //## end cEM63StyxParser%4380553D004C.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: InitFileParser%1133880597
      void InitFileParser (CONST_STRING_T parse_file);

      //## Operation: InitStringParser%1133880598
      void InitStringParser (CONST_STRING_T parse_string);

      //## Operation: ExitParser%1133880600
      void ExitParser ();

      //## Operation: ParseSessionRequest%1134738533
      BOOL_T ParseSessionRequest (cEM63Session *session);

      //## Operation: ParseSessionCmd%1134738528
      cEM63Job * ParseSessionCmd (cEM63Session *session, EM63SessionCmd e63_session_cmd);

      //## Operation: ParsePresentationRequest%1134738534
      BOOL_T ParsePresentationRequest (cEM63Session *session, cEM63Job *job);

      //## Operation: ParsePresCmd%1134835345
      void ParsePresCmd (cEM63Job *job, EM63PresCmd e63_pres_cmd);

      //## Operation: ParseReportSpec%1134980219
      void ParseReportSpec (cEM63Job *job, EM63ReportSpec e63_report_spec);

      //## Operation: ParseGetInfoSpec%1135093198
      void ParseGetInfoSpec (cEM63Job *job, EM63GetInfoSpec e63_getinfo_spec);

      //## Operation: ParseGetIdSpec%1135761100
      void ParseGetIdSpec (cEM63Job *job, EM63GetIdSpec e63_getid_spec);

      //## Operation: ParseSetSpec%1135788722
      void ParseSetSpec (cEM63Job *job, EM63SetSpec e63_set_spec);

      //## Operation: ParseUploadSpec%1135947266
      void ParseUploadSpec (cEM63Job *job, EM63UploadSpec e63_upload_spec);

      //## Operation: ParseDownloadSpec%1135947267
      void ParseDownloadSpec (cEM63Job *job, EM63DownloadSpec e63_download_spec);

      //## Operation: ParseEventSpec%1136281473
      void ParseEventSpec (cEM63Job *job, EM63EventSpec e63_event_spec);

      //## Operation: ParseAbortSpec%1136281474
      void ParseAbortSpec (cEM63Job *job, EM63AbortSpec e63_abort_spec);

      //## Operation: ParsePresSpec%1134980220
      int ParsePresSpec (EM63PresSpec *e63_pres_spec);

      //## Operation: ParseStartSpec%1134980224
      cCondition * ParseStartSpec (EM63StartSpec *e63_start_spec);

      //## Operation: ParseStopSpec%1134980225
      cCondition * ParseStopSpec (EM63StopSpec *e63_stop_spec);

      //## Operation: ParseReportCondSpec%1134980226
      void ParseReportCondSpec (cReportCmd *report_cmd, EM63ReportCondSpec *e63_report_cond_spec);

      //## Operation: ParseCycleSpec%1134980227
      void ParseCycleSpec (cReportCmd *report_cmd, EM63CycleSpec *e63_cycle_spec);

      //## Operation: ParseSamplesSpec%1134980221
      int ParseSamplesSpec (EM63SamplesSpec *e63_samples_spec);

      //## Operation: ParseSessionsSpec%1134980222
      int ParseSessionsSpec (EM63SessionsSpec *e63_sessions_spec);

      //## Operation: ParseParameter%1134980223
      STRING_T ParseParameter (EM63Parameter *e63_parameter);

      //## Operation: ParseFileSpec%1133963358
      STRING_T ParseFileSpec (EM63FileSpec *e63_file_spec);

      //## Operation: ParseParamId%1134980233
      STRING_T ParseParamId (EM63ParamId *e63_param_id);

      //## Operation: ParseTimeConst%1134992996
      int ParseTimeConst (EM63TimeConst *e63_time_const);

      //## Operation: ParseDateConst%1134992993
      int ParseDateConst (EM63DateConst *e63_date_const);

      //## Operation: ParseIntegerConst%1134980228
      int ParseIntegerConst (EM63IntegerConst *e63_integer_const);

      //## Operation: ParseInteger%1134980228
      STRING_T ParseInteger (EM63Integer *e63_integer);

      //## Operation: ParseCondSpec%1134992990
      cCondition * ParseCondSpec (EM63CondSpec *e63_cond_spec);

      //## Operation: ParseTimeCondSpec%1134992991
      cCondition * ParseTimeCondSpec (EM63TimeCondSpec *e63_time_cond_spec);

      //## Operation: ParseRelOp%1134992982
      int ParseRelOp (EM63RelOp *e63_relop);

      //## Operation: ParseConstantSpec%1134992994
      STRING_T ParseConstantSpec (EM63ConstantSpec *e63_constant_spec);

      //## Operation: NatValue%1134980229
      int NatValue (GLS_Tok *token);

      //## Operation: HexValue%1134980230
      int HexValue (GLS_Tok *token);

      //## Operation: RealValue%1134980231
      double RealValue (GLS_Tok *token);

      //## Operation: StringValue%1134980232
      STRING_T StringValue (GLS_Tok *token);
      STRING_T CommandIdentifier(EM63CmdIde * e63_cmd_identifier);
      STRING_T Name(EM63Name * e63_name);

    // Data Members for Class Attributes

      //## Attribute: ScanTable%4395A5A501B7
      //## begin cEM63StyxParser::ScanTable%4395A5A501B7.attr preserve=no  implementation: Scn_T {U} NULL
      Scn_T _ScanTable;
      //## end cEM63StyxParser::ScanTable%4395A5A501B7.attr

      //## Attribute: ScanStream%4395A5A501B8
      //## begin cEM63StyxParser::ScanStream%4395A5A501B8.attr preserve=no  implementation: Scn_Stream {U} NULL
      Scn_Stream _ScanStream;
      //## end cEM63StyxParser::ScanStream%4395A5A501B8.attr

      //## Attribute: ParseTable%4395A5A501C6
      //## begin cEM63StyxParser::ParseTable%4395A5A501C6.attr preserve=no  implementation: PLR_Tab {U} NULL
      PLR_Tab _ParseTable;
      //## end cEM63StyxParser::ParseTable%4395A5A501C6.attr

      //## Attribute: ParseConfig%4395A5A501D6
      //## begin cEM63StyxParser::ParseConfig%4395A5A501D6.attr preserve=no  implementation: PT_Cfg {U} NULL
      PT_Cfg _ParseConfig;
      //## end cEM63StyxParser::ParseConfig%4395A5A501D6.attr

      //## Attribute: Root%4395A5A501D7
      //## begin cEM63StyxParser::Root%4395A5A501D7.attr preserve=no  implementation: PT_Term {U} NULL
      PT_Term _Root;
      //## end cEM63StyxParser::Root%4395A5A501D7.attr

    // Additional Implementation Declarations
      //## begin cEM63StyxParser%4380553D004C.implementation preserve=yes
      //## end cEM63StyxParser%4380553D004C.implementation

};

//## begin cEM63StyxParser%4380553D004C.postscript preserve=yes
//## end cEM63StyxParser%4380553D004C.postscript

// Class cEM63StyxParser 

//## begin module%4380553D004C.epilog preserve=yes
//## end module%4380553D004C.epilog


#endif
