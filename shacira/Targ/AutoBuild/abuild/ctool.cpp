
#include "abuild.h"
#include "ctool.h"
#include "cbuildconfiguration.h"

bool cTargetSpecification::Parse()
{
   char name_format[0x200] = {0};
   char type_spec[0x100] = {0};
   int params = sscanf(_Specification.c_str(), "%[^:]:%s", name_format, type_spec);
   if (params == 2) {
      _NameFormat = name_format;
      _FileType = cProjectFile::FileTypeSpec(type_spec);
      return true;
   } else if (params == 1) {
      _NameFormat = name_format;
      char white_space[0x200] = {0};
      char base[0x50] = {0};
      char extension[0x20] = {0};
      params = sscanf(name_format, "%[^.].%[^.].%s", base, white_space, extension);
      if (params == 3) {
         _FileType = cProjectFile::FileTypeExtension(extension);
      } else {
         params = sscanf(name_format, "%[^.].%s", base, extension);
         if (params == 2) {
            _FileType = cProjectFile::FileTypeExtension(extension);
         }
      }
      return true;
   }
   return false;
}

cNode * cTool::Node(cGraph * graph)
{
   STRING_T name = _Name;
   cNode * node = graph->Node(name.c_str());
   node->AddProperty("name", name.c_str());
   node->AddProperty("description", _Description.c_str());
   return node;
}
   
bool cTool::Target(int index, const char * base_name,STRING_T & target, int & type)
{
   type = UNKNOWN_FILE;
   cTargetSpecification * target_spec = _TargetSpecs[index];
   if (target_spec != NULL) {
      type = target_spec->FileType();
      target = target_spec->FileName(base_name);
      return true;
   }
   return false;
}

const char * cTool::CommandLine(int type)
{
   return "invalid tool";
}

/*!
 *  Generic Tool
 */

cNode * cGenericTool::Node(cGraph * graph)
{
   return cTool::Node(graph);
}
   
const char * cGenericTool::CommandLine(int type)
{
   _CommandLines = _Command[0];
   int i = 0;
   for (i=1; i<_CommandCount; i++) {
      _CommandLines += "\n\t";
      _CommandLines += _Command[i].c_str();
   }
   return _CommandLines.c_str();
}

bool cGenericTool::ParseDirective(const char * directive, const char * text, const char * file, int line_no)
{
   if (stricmp(directive, "command_line") == 0) {
      _Command[_CommandCount] = text;
      _CommandCount++;
   } else if (stricmp(directive, "target") == 0) {
      cTargetSpecification * target_spec = new cTargetSpecification(text);
      if (target_spec->Parse()) {
         if (target_spec->FileType() == UNKNOWN_FILE) {
//            Printf(M_WARNING, "unknown file type in directive \"%s %s\" no action\n",
//                   directive, text);
         } else {
            _TargetSpecs[_TargetCount] = target_spec;
            _TargetCount++;
         }
      } else {
         Printf(M_WARNING, "failed to parse %s\n",
                text);
      }
   } else if (stricmp(directive, "name") == 0) {
      _Name = text;
   } else if (stricmp(directive, "description") == 0) {
      _Description = text;
   } else {
      Printf(M_WARNING, "unrecognized directive \"%s %s\"\n",
             directive, text);
   }
   return true;
}

/*!
 *  C++ Compiler
 */

const char * cCPPCompiler::CommandLine(int type)
{
   if (type == C_FILE) {
      return "cl /nologo /TC /MD /W3 /GX /O2 /D NDEBUG /D WIN32 /D _MBCS /D _LIB -c $(options) $(definitions) $(include_dirs) $< /Fo$@";
   } else {
      return "cl /nologo /TP /MD /W3 /GX /O2 /D NDEBUG /D WIN32 /D _MBCS /D _LIB -c $(options) $(definitions) $(include_dirs) $< /Fo$@";
   }
}

/*!
 *  Styx Generator
 */

const char * cStyxCompiler::CommandLine(int type)
{
   return "styxw $< -makeC -o$@";
}

/*!
 *  User Interface Compiler
 */

const char * cUserInterfaceCompiler::CommandLine(int type)
{
   return "uic";
}

/*!
 *  Meta Object Compiler
 */

const char * cMetaObjectCompiler::CommandLine(int type)
{
   return "moc";
}

/*!
 *  Model Compiler
 */

const char * cModelCompiler::CommandLine(int type)
{
   return "mdlc";
}

/*!
 *  CORBA Idl Compiler
 */

const char * cCORBAIdlCompiler::CommandLine(int type)
{
   return "omniidl $(include_dirs) -C$(intermediate_dir) -bcxx -WbBOA -Wba $<";
}

/*!
 *  2i Preprocessor
 */

const char * cPreprocessor::CommandLine(int type)
{
   return "pp";
}

/*!
 *  Library Manager
 */

const char * cLibrarian::CommandLine(int type)
{
   return "link -lib /nologo /out:$(intermediate_dir) /out:$@ $(objects)";
}

/*!
 *  Linker
 */

const char * cLinker::CommandLine(int type)
{
   return "link /nologo /subsystem:console /incremental:no /pdb:$(intermediate_dir)/scons.pdb /machine:I386 /nodefaultlib:libcmt.lib /out:$(intermediate_dir) /out:$@ $(objects) $(libraries) $(library_dirs)";
}

