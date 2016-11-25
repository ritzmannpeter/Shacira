
#ifndef _ctool_h
#define _ctool_h 	1

#include "global_defs.h"
#include "cconfigbase.h"
#include "cprojectfile.h"

class cTargetSpecification
{
public:
   cTargetSpecification(const char * specification)
   {
      _FileType = UNKNOWN_FILE;
      _Specification = specification;
   };
   cTargetSpecification(const char * name_format, int file_type)
   {
      _FileType = file_type;
      _NameFormat = name_format;
   };
   virtual bool Parse();
   inline const char * Specification()
   {
      return _Specification.c_str();
   };
   inline int FileType()
   {
      return _FileType;
   };
   inline STRING_T FileName(const char * base_name)
   {
      char file_name[0x200] = {0};
      sprintf(file_name, _NameFormat.c_str(), base_name);
      return file_name;
   };
private:
   STRING_T _Specification;
   STRING_T _NameFormat;
   int _FileType;
};

class cTool : public cGraphNode
{
public:
   cTool(int type)
   {
      _TargetCount = 0;
      memset(_TargetSpecs, 0, sizeof(_TargetSpecs));
      _Type = type;
      char name[0x40] = {0};
      sprintf(name, "tool_%d", _Type);
      _Name = name;
      _Description = "unknown";
   };
   virtual ~cTool()
   {
   };
   virtual cNode * Node(cGraph * graph);
   inline int FileType()
   {
      return _Type;
   };
   inline const char * Name()
   {
      return _Name.c_str();
   }
   inline const char * Description()
   {
      return _Description.c_str();
   }
   virtual bool Target(int index, const char * base_name,STRING_T & target, int & type);
   virtual const char * CommandLine(int type);
protected:
   int _Type;
   STRING_T _Name;
   STRING_T _Description;
   cTargetSpecification * _TargetSpecs[0x20];
   unsigned long _TargetCount;
};

class cGenericTool : public cTool, public cConfigBase
{
public:
   cGenericTool(const char * config_file, int type) :
      cTool(type), cConfigBase(config_file, "tool")
   {
      _CommandCount = 0;
      _ConfigFile = new cPath(config_file);
   };
   virtual cNode * Node(cGraph * graph);
   virtual const char * CommandLine(int type);
protected:
   virtual bool ParseDirective(const char * directive, const char * text, const char * file, int line_no);
private:
   cPath * _ConfigFile;
   STRING_T _CommandLines;
   STRING_T _Command[0x10];
   int _CommandCount;
};

class cCPPCompiler : public cTool
{
public:
   cCPPCompiler(int type) :
      cTool(type)
   {
      _TargetSpecs[0] = new cTargetSpecification("%s.o", OBJECT_FILE);
   };
   virtual const char * CommandLine(int type);
};

class cStyxCompiler : public cTool
{
public:
   cStyxCompiler(int type) :
      cTool(type)
   {
      _TargetSpecs[0] = new cTargetSpecification("%s_lim.h", H_FILE);
      _TargetSpecs[1] = new cTargetSpecification("%s_pim.h", H_FILE);
      _TargetSpecs[2] = new cTargetSpecification("%s_int.h", H_FILE);
      _TargetSpecs[3] = new cTargetSpecification("%s_lim.c", C_FILE);
      _TargetSpecs[4] = new cTargetSpecification("%s_pim.c", C_FILE);
      _TargetSpecs[5] = new cTargetSpecification("%s_int.c", C_FILE);
   };
   virtual const char * CommandLine(int type);
};

class cUserInterfaceCompiler : public cTool
{
public:
   cUserInterfaceCompiler(int type) :
      cTool(type)
   {
      _TargetSpecs[0] = new cTargetSpecification("%s.h", H_FILE);
      _TargetSpecs[1] = new cTargetSpecification("%s.cpp", CPP_FILE);
      _TargetSpecs[2] = new cTargetSpecification("moc_%s.h", H_FILE);
      _TargetSpecs[2] = new cTargetSpecification("moc_%s.cpp", CPP_FILE);
   };

   virtual const char * CommandLine(int type);
};

class cMetaObjectCompiler : public cTool
{
public:
   cMetaObjectCompiler(int type) :
      cTool(type)
   {
      _TargetSpecs[0] = new cTargetSpecification("moc_%s.cpp", CPP_FILE);
   };
   virtual const char * CommandLine(int type);
};

class cModelCompiler : public cTool
{
public:
   cModelCompiler(int type) :
      cTool(type)
   {
   };
   virtual const char * CommandLine(int type);
};

class cCORBAIdlCompiler : public cTool
{
public:
   cCORBAIdlCompiler(int type) :
      cTool(type)
   {
      _TargetSpecs[0] = new cTargetSpecification("%s.hh", H_FILE);
      _TargetSpecs[1] = new cTargetSpecification("%sSK.cc", CPP_FILE);
      _TargetSpecs[2] = new cTargetSpecification("%sDynSK.cc", CPP_FILE);
   };
   virtual const char * CommandLine(int type);
};

class cPreprocessor : public cTool
{
public:
   cPreprocessor(int type) :
      cTool(type)
   {
   };
   virtual const char * CommandLine(int type);
};

class cLibrarian : public cTool
{
public:
   cLibrarian(int type) :
      cTool(type)
   {

   };
   virtual const char * CommandLine(int type);
};

class cLinker : public cTool
{
public:
   cLinker(int type) :
      cTool(type)
   {
   };
   virtual const char * CommandLine(int type = UNKNOWN_FILE);
};

class cSharedLinker : public cLinker
{
public:
   cSharedLinker(int type) :
      cLinker(type)
   {
   };
};

#endif

