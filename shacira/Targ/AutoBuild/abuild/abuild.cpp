
#include <stdarg.h>
#include "abuild.h"
#include "cproject.h"
#include "cdirectoryutils.h"
#include "cpath.h"
#include "cbuildconfiguration.h"
#include "cvirtualfilesystem.h"
#include "portingsupport.h"

STRING_T _File;
int _Line = 0;
int _Column = 0;
static const char * _LogFile = "e:\\usr\\prj\\shacira\\targ\\autoconfig\\abuild.log";
//static unsigned long _MsgClass = M_INFO|M_WARNING|M_ERROR;
static unsigned long _MsgClass = M_ERROR|M_WARNING;
unsigned long _BuildFlags = 0;

static char _Text[0x20000] = {0};
void Printf(unsigned long msg_class, const char * fmt_str, ...)
{
   if (!(_MsgClass & msg_class)) {
      return;
   }
   va_list args;
   va_start(args, fmt_str);
   try {
      vsprintf(_Text, fmt_str, args);
      if (msg_class & M_INFO) {
         printf("%s", _Text);
      } else if (msg_class & M_WARNING) {
         printf("%s(%d) : warning: %s", _File.c_str(), _Line, _Text);
      } else if (msg_class & M_ERROR) {
         printf("%s(%d) : error: %s", _File.c_str(), _Line, _Text);
      }
      if (_LogFile != NULL) {
         FILE * stream = fopen(_LogFile, "a");
         if (stream != NULL) {
            if (msg_class & M_INFO) {
               fprintf(stream, "%s", _Text);
            } else if (msg_class & M_WARNING) {
               fprintf(stream, "%s(%d) : warning: %s", _File.c_str(), _Line, _Text);
            } else if (msg_class & M_ERROR) {
               fprintf(stream, "%s(%d) : error: %s", _File.c_str(), _Line, _Text);
            }
            fclose(stream);
         }
      }
   } catch (...) {
   }
}

static cVirtualFileSystem _Vfs;

void AddVFS(const char * path)
{
   _Vfs.AddPath(path);
}

bool FindVFS(const char * path)
{
   bool success = _Vfs.FindPath(path);
   if (success) {
      return true;
   } else {
      return false;
   }
}

static bool GenerateXMLBackend(cBuildConfiguration * config, const char * project_name)
{
   char xml_file[0x100] = {0};
   sprintf(xml_file, "%s.xml", project_name);
   Printf(M_INFO, "generating XML backend file %s ...\n", xml_file);
   cGraph * graph = new cGraph;
   config->Node(graph);
   cNode * node = graph->Node("root");
   graph->SetRootNode(node);
   remove(xml_file);
   STRING_T xml_data;
   graph->XML(xml_data);
   FILE * stream = fopen(xml_file, "a");
   if (stream != NULL) {
      fprintf(stream, "%s", xml_data.c_str());
      fclose(stream);
      Printf(M_INFO, "XML backend file %s successfully generated\n", xml_file);
      return true;
   } else {
      Printf(M_ERROR, "failed to generate XML backend file %s\n", xml_file);
      return false;
   }
}

static bool GenerateEnvironment()
{
   return true;
}

static void Usage()
{
   printf("\n");
   printf("usage:\n");
   printf("   abuild options\n");
   printf("       options:\n");
   printf("         -cf <configuration file>\n");
   printf("         -bf <build file>\n");
   printf("         -df generate dependency files\n");
   printf("         -v be verbose\n");
   printf("         -V be very verbose\n");
   printf("         -xml generate XML backend file\n");
   printf("         -config <environment file>t\n");
   printf("         -lf <log file>\n");
   printf("\n");
   printf("\n");
}

static const char * GetParam(int & i, const char * option, const char * next_param)
{
   if (strlen(option) > 0) {
      i++;
      return option;
   } else {
      if (next_param == NULL || *next_param == '-') {
         i++;
         return NULL;
      } else {
         i += 2;
         return next_param;
      }
   }
}

#undef TESTS
#ifdef TESTS
#include "cvalue.h"
#include "cvaluet.h"
#endif
int abuild(int argc, char* argv[])
{
#ifdef TESTS
//TestValues();
//printf("allocated %d\n", cValue::Allocations());
TestValueT();
return 0;
#endif

   if (_LogFile != NULL) {
      remove(_LogFile);
   }
   const char * build_file = "build.cfg";
   const char * config_file = NULL;
   const char * shacira_dir = getenv("shacira");
   if (shacira_dir == NULL) {
      shacira_dir = getenv("SHACIRADIR");
   }
   if (shacira_dir == NULL) {
      fprintf(stderr, "no shacira directory\nplease set environment variable shacira to the root directory of the SHACIRA project\n");
      return -1;
   }
   const char * ctools = getenv("ctools");
   if (ctools == NULL) {
      ctools = "mingw";
//      ctools = "vc6";
   }
   const char * configuration = getenv("configuration");
   if (configuration == NULL) {
      configuration = "debug";
   }
   const char * env_file = "environment.inc";
   const char * param = NULL;
   int i = 1;
   for (i=0; i<argc; i++) {
      if (i != 0) {
         fprintf(stderr, " ");
      }
      fprintf(stderr, "%s", argv[i]);
   }
   fprintf(stderr, "\n");
   i = 1;
   while (i < argc) {
      if (strncmp(argv[i], "-config", 7) == 0) {
         param = GetParam(i, &(argv[i])[7], argv[i+1]);
         if (param == NULL) {
            fprintf(stderr, "no environment file specified using %s\n", env_file);
         } else {
            env_file = param;
            fprintf(stderr, "environment file %s\n", env_file);
         }
         _BuildFlags |= GENERATE_ENVIRONMENT;
      } else if (strncmp(argv[i], "-cf", 3) == 0) {
         param = GetParam(i, &(argv[i])[3], argv[i+1]);
         if (param == NULL) {
            fprintf(stderr, "no configuration file specified using %s\n", config_file);
         } else {
            config_file = param;
            fprintf(stderr, "configuration file %s\n", config_file);
         }
      } else if (strncmp(argv[i], "-bf", 2) == 0) {
         param = GetParam(i, &(argv[i])[3], argv[i+1]);
         if (param == NULL) {
            fprintf(stderr, "no build file specified using %s\n", build_file);
         } else {
            build_file = param;
            fprintf(stderr, "build file %s\n", build_file);
         }
      } else if (strncmp(argv[i], "-lf", 2) == 0) {
         param = GetParam(i, &(argv[i])[3], argv[i+1]);
         if (param == NULL) {
            fprintf(stderr, "no log file specified using %s\n", _LogFile);
         } else {
            _LogFile = param;
            fprintf(stderr, "log file %s\n", _LogFile);
         }
      } else if (strcmp(argv[i], "-v") == 0) {
         _MsgClass |= M_INFO;
         i++;
         fprintf(stderr, "verbose\n");
      } else if (strcmp(argv[i], "-V") == 0) {
         _MsgClass |= M_INFO;
         i++;
         fprintf(stderr, "very verbose\n");
      } else if (strcmp(argv[i], "-df") == 0) {
         _BuildFlags |= GENERATE_DEP_FILES;
         i++;
         fprintf(stderr, "generate dependency files\n");
      } else if (strcmp(argv[i], "-xml") == 0) {
         _BuildFlags |= GENERATE_XML_BACKEND;
         i++;
         fprintf(stderr, "generate xml backend file\n");
      } else if (strcmp(argv[i], "-port_v14") == 0) {
         return PortToShacira14();
      } else if (strcmp(argv[i], "-port_linux") == 0) {
         return PortToLinux();
      } else if (strcmp(argv[i], "-port_qt4") == 0) {
         return PortToQT4();
      } else {
         fprintf(stderr, "invalid option %s\n", argv[i]);
         Usage();
         return -1;
      }
   }
   char auto_config_file[0x200] = {0};
   if (config_file == NULL) {
      sprintf(auto_config_file, "%s/Targ/AutoConfig/configurations/win32_%s_%s.cfg",
              shacira_dir, ctools, configuration);
      fprintf(stderr, "using configuration\n", auto_config_file);
      config_file = auto_config_file;
   }
//   if (_BuildFlags & GENERATE_ENVIRONMENT) {
//      return GenerateEnvironment();
//   }
//   return 0;
   if (config_file == NULL) {
      printf("no configuration file\n");
      Usage();
   } else {
   	  STRING_T x = cDirectoryUtils::FullPath(build_file).c_str();
      printf("build:\n%s\n", cDirectoryUtils::FullPath(build_file).c_str());
      printf("configuration:\n%s\n", cDirectoryUtils::FullPath(config_file).c_str());
      printf("...\n");
   }

   cBuildConfiguration * config = new cBuildConfiguration(config_file);
   if (config->Parse()) {
      cDirectoryUtils::_PathDelimiter = config->PathDelimiter();
      cProject project(config, build_file);
      if (project.Parse()) {
         config->SetRoot(&project);
         if (_BuildFlags & GENERATE_XML_BACKEND) {
            GenerateXMLBackend(config, project.ProjectName().c_str());
         }
         if (project.Build()) {
            printf("done\n");
            return 0;
         } else {
            printf("failed\n");
            return -1;
         }
      } else {
         printf("failed\n");
         return -1;
      }
   } else {
      printf("failed\n");
      return -1;
   }
   return -1;
}

int main(int argc, char* argv[])
{
   int rc = abuild(argc, argv);
   return rc;
}
