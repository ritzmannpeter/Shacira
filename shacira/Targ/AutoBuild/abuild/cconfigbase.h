
#ifndef _cconfigbase_h
#define _cconfigbase_h 	1

#include "global_defs.h"
#include "cpath.h"
#include "csymboltable.h"
#include "cstatestack.h"
#include "cgraphnode.h"
#include "cgraph.h"

class cConfigBase : public cGraphNode
{
public:
   cConfigBase(const char * config_file, const char * name);
   virtual ~cConfigBase();
   virtual bool Parse();
   inline cSymbolTable * CSymbols()
   {
      return _CSymbols;
   };
   inline cSymbolTable * BuildSymbols()
   {
      return _BuildSymbols;
   };
protected:
   cPath * _ConfigFile;
   STRING_T _ConfigName;
private:
   cSymbolTable * _CSymbols;
   static cSymbolTable * _BuildSymbols;
protected:
   virtual bool ParseSpecs(const char * spec_file);
   virtual bool ParseDirective(const char * directive, const char * text, const char * file, int line_no);
   bool CheckForMOCFile(const char * file);
private:
   char _ParseBuffer[0x2000];
   char _CheckBuffer[0x2000];
};

#endif

