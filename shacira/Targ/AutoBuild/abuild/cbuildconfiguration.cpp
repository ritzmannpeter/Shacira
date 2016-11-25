
#include "cbuildconfiguration.h"
#include "cproject.h"
#include "abuild.h"

#define VALID_TYPE(type) \
   (type != OBJECT_FILE && \
    type != H_FILE && \
    type != UNKNOWN_FILE && \
    type != DETECT)

cBuildConfiguration::cBuildConfiguration(const char * config_file)
   : cConfigBase(config_file, "build_config")
{
   _Root = NULL;
   _System = "win32";
   _Compiler = "vc6";
   _ToolChain = "vs6";
   memset(_Tools, 0, sizeof(_Tools));
   memset(_PathDelimiter, 0, sizeof(_PathDelimiter));
}

cBuildConfiguration::~cBuildConfiguration()
{
}

void cBuildConfiguration::Clone(cProject * project)
{
   project->_COptions = _COptions;
   project->_CPPOptions = _CPPOptions;
   project->_LibOptions = _LibOptions;
   project->_LinkOptions = _LinkOptions;
   project->_ASMOptions = _ASMOptions;
}

cNode * cBuildConfiguration::Node(cGraph * graph)
{
   cNode * root_node = graph->Node("root");
   graph->SetRootNode(root_node);
   cNode * config_node = graph->Node("build_configuration");
   config_node->AddProperty("compiler",  _Compiler.c_str());
   config_node->AddProperty("system",  _System.c_str());
   config_node->AddProperty("toolchain",  _ToolChain.c_str());
   ///...
   cAngle * angle = new cAngle(graph, "build_configuration", root_node, config_node);
   root_node->AddAngle(angle);
   if (_Root != NULL) {
      cNode * root_project_node = _Root->Node(graph);
      cAngle * angle = new cAngle(graph, "root_project", root_node, root_project_node);
      root_node->AddAngle(angle);
   }
   int i = 0;
   int len = sizeof(_Tools) / sizeof(cTool*);
   for (i=0; i<len; i++) {
      cTool * tool = _Tools[i];
      if (tool != NULL) {
         STRING_T name = tool->Name();
         cNode * tool_node = tool->Node(graph);
         cAngle * angle = new cAngle(graph, "tool", root_node, tool_node);
         root_node->AddAngle(angle);
      }
   }
   return root_node;
}
   
cTool * cBuildConfiguration::Tool(int type)
{
   cTool * tool = _Tools[type];
   if (tool == NULL) {
      if (VALID_TYPE(type)) {
         Printf(M_WARNING, "no tool for type %d using null tool\n",
                type);
      }
      tool = new cTool(type);
      _Tools[type] = tool;
   }
   return tool;
}

cTool * cBuildConfiguration::Tool(const char * file,
                                  const char * absolute_path,
                                  const char * base_name,
                                  const char * file_name,
                                  const char * extension)
{
   int type = cProjectFile::FileTypeExtension(extension);
   if (type == H_FILE) {
      if (CheckForMOCFile(file)) {
         type = MOC_FILE;
      }
   }
   cTool * tool = _Tools[type];
   if (tool == NULL) {
      if (VALID_TYPE(type)) {
         Printf(M_WARNING, "no generic tool for type %d\n",
                type);
      }
      switch (type) {
      case DETECT:
         break;
      case CORBA_IDL_FILE:
         Printf(M_WARNING, "using builtin tool cCORBAIdlCompiler\n");
         tool = new cCORBAIdlCompiler(type);
         break;
      case COM_IDL_FILE:
         break;
      case C_FILE:
      case CPP_FILE:
         Printf(M_WARNING, "using builtin tool cCPPCompiler\n");
         tool = new cCPPCompiler(type);
         break;
      case H_FILE:
         break;
      case STYX_FILE:
         Printf(M_WARNING, "using builtin tool cStyxCompiler\n");
         tool = new cStyxCompiler(type);
         break;
      case UI_FILE:
         tool = new cUserInterfaceCompiler(type);
         break;
      case MOC_FILE:
         Printf(M_WARNING, "using builtin tool cMetaObjectCompiler\n");
         tool = new cMetaObjectCompiler(type);
         break;
      case PP_FILE:
         Printf(M_WARNING, "using builtin tool cPreprocessor\n");
         tool = new cPreprocessor(type);
         break;
      case MDLC_FILE:
         Printf(M_WARNING, "using builtin tool cModelCompiler\n");
         tool = new cModelCompiler(type);
         break;
      case STATIC_LIBRARY_FILE:
         Printf(M_WARNING, "using builtin tool cLibrarian\n");
         tool = new cLibrarian(type);
         break;
      case EXECUTABLE_FILE:
         Printf(M_WARNING, "using builtin tool cLinker\n");
         tool = new cLinker(type);
         break;
      case SHARED_LIBRARY_FILE:
         Printf(M_WARNING, "using builtin tool cSharedLinker\n");
         tool = new cSharedLinker(type);
         break;
      }
      if (tool == NULL) {
         if (VALID_TYPE(type)) {
            Printf(M_WARNING, "no tool for type %d using null tool\n",
                   type);
         }
         tool = new cTool(type);
      }
      _Tools[type] = tool;
   }
   return tool;
}

bool cBuildConfiguration::ParseDirective(const char * directive, const char * text, const char * file, int line_no)
{
   cGenericTool * generic_tool = NULL;
   STRING_T base_dir = _ConfigFile->AbsoluteDirectory();
   if (stricmp(directive, "compiler") == 0) {
      _Compiler = text;
      BuildSymbols()->Define("compiler", text);
   } else if (stricmp(directive, "system") == 0) {
      _System = text;
      BuildSymbols()->Define("system", text);
   } else if (stricmp(directive, "toolchain") == 0) {
      _ToolChain = text;
      BuildSymbols()->Define("toolchain", text);
   } else if (stricmp(directive, "path_delimiter") == 0) {
      int len = strlen(text);
      int i = 0;
      for (i=0; i<len; i++) {
         if (text[i] != ' ') {
            _PathDelimiter[0] = text[i];
            cDirectoryUtils::_PathDelimiter = _PathDelimiter;
            break;
         }
      }
   } else if (stricmp(directive, "c_option") == 0) {
      AddCOption(text);
   } else if (stricmp(directive, "cpp_option") == 0) {
      AddCPPOption(text);
   } else if (stricmp(directive, "lib_option") == 0) {
      AddLibOption(text);
   } else if (stricmp(directive, "link_option") == 0) {
      AddLinkOption(text);
   } else if (stricmp(directive, "asm_option") == 0) {
      AddASMOption(text);
   } else if (stricmp(directive, "make") == 0) {
      _MakeCode += text;
      _MakeCode += "\n";
   } else if (stricmp(directive, "cpp") == 0) {
      STRING_T tool_file = cDirectoryUtils::AppendPath(base_dir.c_str(), text);
      _Tools[CPP_FILE] = generic_tool = new cGenericTool(tool_file.c_str(), CPP_FILE);
   } else if (stricmp(directive, "c") == 0) {
      STRING_T tool_file = cDirectoryUtils::AppendPath(base_dir.c_str(), text);
      _Tools[C_FILE] = generic_tool = new cGenericTool(tool_file.c_str(), C_FILE);
   } else if (stricmp(directive, "cidl") == 0) {
      STRING_T tool_file = cDirectoryUtils::AppendPath(base_dir.c_str(), text);
      _Tools[CORBA_IDL_FILE] = generic_tool = new cGenericTool(tool_file.c_str(), CORBA_IDL_FILE);
   } else if (stricmp(directive, "parsgen") == 0) {
      STRING_T tool_file = cDirectoryUtils::AppendPath(base_dir.c_str(), text);
      _Tools[STYX_FILE] = generic_tool = new cGenericTool(tool_file.c_str(), STYX_FILE);
   } else if (stricmp(directive, "moc") == 0) {
      STRING_T tool_file = cDirectoryUtils::AppendPath(base_dir.c_str(), text);
      _Tools[MOC_FILE] = generic_tool = new cGenericTool(tool_file.c_str(), MOC_FILE);
   } else if (stricmp(directive, "uic") == 0) {
      STRING_T tool_file = cDirectoryUtils::AppendPath(base_dir.c_str(), text);
      _Tools[UI_FILE] = generic_tool = new cGenericTool(tool_file.c_str(), UI_FILE);
   } else if (stricmp(directive, "pp") == 0) {
      STRING_T tool_file = cDirectoryUtils::AppendPath(base_dir.c_str(), text);
      _Tools[PP_FILE] = generic_tool = new cGenericTool(tool_file.c_str(), PP_FILE);
   } else if (stricmp(directive, "mdlc") == 0) {
      STRING_T tool_file = cDirectoryUtils::AppendPath(base_dir.c_str(), text);
      _Tools[MDLC_FILE] = generic_tool = new cGenericTool(tool_file.c_str(), MDLC_FILE);
   } else if (stricmp(directive, "asm") == 0) {
      STRING_T tool_file = cDirectoryUtils::AppendPath(base_dir.c_str(), text);
      _Tools[ASM_FILE] = generic_tool = new cGenericTool(tool_file.c_str(), ASM_FILE);
   } else if (stricmp(directive, "slink") == 0) {
      STRING_T tool_file = cDirectoryUtils::AppendPath(base_dir.c_str(), text);
      _Tools[SHARED_LIBRARY_FILE] = generic_tool = new cGenericTool(tool_file.c_str(), SHARED_LIBRARY_FILE);
   } else if (stricmp(directive, "link") == 0) {
      STRING_T tool_file = cDirectoryUtils::AppendPath(base_dir.c_str(), text);
      _Tools[EXECUTABLE_FILE] = generic_tool = new cGenericTool(tool_file.c_str(), EXECUTABLE_FILE);
   } else if (stricmp(directive, "lib") == 0) {
      STRING_T tool_file = cDirectoryUtils::AppendPath(base_dir.c_str(), text);
      _Tools[STATIC_LIBRARY_FILE] = generic_tool = new cGenericTool(tool_file.c_str(), STATIC_LIBRARY_FILE);
   } else {
      Printf(M_WARNING, "unrecognized directive \"%s %s\"\n",
             directive, text);
   }
   if (generic_tool != NULL) { 
      if (generic_tool->Parse()) {
         return true;
      } else {
         return false;
      }
   }
   return true;
}

