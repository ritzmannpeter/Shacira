
#ifndef _cbuildconfiguration_h
#define _cbuildconfiguration_h 	1

#include "global_defs.h"
#include "cconfigbase.h"
#include "ctool.h"
#include "cprojectfile.h"

typedef std::map<STRING_T,cTool*> TOOL_MAP_T;

class cBuildConfiguration : public cConfigBase
{
public:
   cBuildConfiguration(const char * config_file);
   virtual ~cBuildConfiguration();
   virtual cNode * Node(cGraph * graph);
   cTool * Tool(int type);
   cTool * Tool(const char * file,
                const char * absolute_path,
                const char * base_name,
                const char * file_name,
                const char * extension);
   inline const char * ConfigName()
   {
      return _ConfigName.c_str();
   };
   inline const char * System()
   {
      return _System.c_str();
   };
   inline const char * Compiler()
   {
      return _Compiler.c_str();
   };
   inline const char * ToolChain()
   {
      return _ToolChain.c_str();
   };
   inline const char * COptions()
   {
      return _COptions.c_str();
   };
   inline const char * LinkOptions()
   {
      return _LinkOptions.c_str();
   };
   inline const char * LibOptions()
   {
      return _LibOptions.c_str();
   };
   inline const char * MakeCode()
   {
      return _MakeCode.c_str();
   };
   inline const char * CDefSymbol()
   {
      return "-D ";
   };
   inline const char * LibAddSymbol()
   {
      if (strcmp(_ToolChain.c_str(), "gnu") == 0 ||
          strcmp(_ToolChain.c_str(), "mingw") == 0 ||
          strcmp(_ToolChain.c_str(), "cygwin") == 0) {
         return "-l ";
      }
      return "";
   };
   inline const char * LibPathAddSymbol()
   {
      if (strcmp(_ToolChain.c_str(), "gnu") == 0 ||
          strcmp(_ToolChain.c_str(), "mingw") == 0 ||
          strcmp(_ToolChain.c_str(), "cygwin") == 0) {
         return "-L ";
      }
      return "-libpath:";
   };
   const char * IncludePathAddSymbol()
   {
      return "-I ";
   };
   inline const char * StaticLibPrefix()
   {
      if (strcmp(_ToolChain.c_str(), "gnu") == 0 ||
          strcmp(_ToolChain.c_str(), "mingw") == 0 ||
          strcmp(_ToolChain.c_str(), "cygwin") == 0) {
         return "lib";
      }
      return "";
   };
   inline const char * StaticLibLinkExtension()
   {
      if (strcmp(_ToolChain.c_str(), "gnu") == 0 ||
          strcmp(_ToolChain.c_str(), "mingw") == 0 ||
          strcmp(_ToolChain.c_str(), "cygwin") == 0) {
         return "";
      } 
      return ".lib";
   };
   inline const char * StaticLibTargetExtension()
   {
      if (strcmp(_ToolChain.c_str(), "gnu") == 0 ||
          strcmp(_ToolChain.c_str(), "mingw") == 0 ||
          strcmp(_ToolChain.c_str(), "cygwin") == 0) {
         return ".a";
      }
      return ".lib";
   };
   inline const char * SharedLibPrefix()
   {
      if (strcmp(_System.c_str(), "linux") == 0) {
         return "lib";
      }
      return "";
   };
   inline const char * SharedLibExtension()
   {
      if (strcmp(_System.c_str(), "linux") == 0) {
         return ".so";
      }
      return ".dll";
   };
   inline const char * ExecutablePrefix()
   {
      return "";
   };
   inline const char * ExecutableExtension()
   {
      if (strcmp(_System.c_str(), "linux") == 0) {
         return "";
      }
      return ".exe";
   };
   inline const char * PathDelimiter()
   {
      if (*_PathDelimiter != '\0') {
         return _PathDelimiter;
      }
      if (strcmp(_ToolChain.c_str(), "vs6") == 0) {
         return "\\";
      }
      return "/";
   };
   inline void SetDefinitions(cSymbolTable * symbol_table)
   {
      symbol_table->Define("_WIN32");
      symbol_table->Define("_MSC_VER", 1200);
   };
   inline const char * IntermediateDirectory()
   {
      return _ConfigName.c_str();
   };
   inline const char * ToolSpecs()
   {
      return "make = make\nrm = erase\nmkdir = mkdir";
   };
   inline cProject * Root()
   {
      return _Root;
   };
   inline void SetRoot(cProject * project)
   {
      _Root = project;
   };
   inline void AddCOption(const char * text)
   {
      if (_COptions.size() > 0) {
         _COptions += " ";
      }
      _COptions += text;
   };
   inline void AddCPPOption(const char * text)
   {
      if (_CPPOptions.size() > 0) {
         _CPPOptions += " ";
      }
      _CPPOptions += text;
   };
   inline void AddLibOption(const char * text)
   {
      if (_LibOptions.size() > 0) {
         _LibOptions += " ";
      }
      _LibOptions += text;
   };
   inline void AddLinkOption(const char * text)
   {
      if (_LinkOptions.size() > 0) {
         _LinkOptions += " ";
      }
      _LinkOptions += text;
   };
   inline void AddASMOption(const char * text)
   {
      if (_ASMOptions.size() > 0) {
         _ASMOptions += " ";
      }
      _ASMOptions += text;
   };
   void Clone(cProject * project);
protected:
   virtual bool ParseDirective(const char * directive, const char * text, const char * file, int line_no);
private:
   STRING_T _Compiler;
   STRING_T _System;
   STRING_T _ToolChain;
   STRING_T _MakeCode;
   cProject * _Root;
   cTool * _Tools[0x100];
   char _PathDelimiter[2];
   STRING_T _COptions;
   STRING_T _CPPOptions;
   STRING_T _LibOptions;
   STRING_T _LinkOptions;
   STRING_T _ASMOptions;
};

#endif

