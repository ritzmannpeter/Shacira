

#include "cBuildEntry.h"
#include "cAutoConfig.h"

//static STRING_T _System = "win32";
//static STRING_T _Compiler = "vcpp";
static STRING_T _System = "linux";
static STRING_T _Compiler = "gcc";
static STRING_T _Configuration = "debug";
static STRING_T _ConfigFile = "build.cfg";

STRING_T System()
{
   return _System;
}

STRING_T Compiler()
{
   return _Compiler;
}

STRING_T Configuration()
{
   return _Configuration;
}

STRING_T ConfigFile()
{
   return _ConfigFile;
}

static STRING_MAP_T _Symbols;

void SetSymbol(CONST_STRING_T sym_name, CONST_STRING_T sym_value)
{
   _Symbols[sym_name] = sym_value;
}

STRING_T GetSymbol(CONST_STRING_T sym_name)
{
   STRING_MAP_T::const_iterator i = _Symbols.find(sym_name);
   if (i == _Symbols.end()) {
      return "";
   } else {
      return (*i).second;
   }
}

static STRING_T Arg(const char * a0, const char * a1)
{
   if (*a0 != '\0') {
      return a0;
   } else if (*a1 != '-') {
      return a1;
   }
   return "";
}

int mmake(int argc, char* argv[])
{
   cAutoConfig * config = NULL;
   const char * config_file = "build.cfg";
   int arg = 0;
   for (arg=1; arg<argc; arg++) {
      if (strncmp(argv[arg], "-system", 7) == 0) {
         STRING_T system = Arg(&(argv[arg][7]), argv[arg+1]);
         if (strcmp(system.c_str(), "win32") == 0) {
         } else if (strcmp(system.c_str(), "linux") == 0) {
         } else {
            fprintf(stderr, "invalid system %s (win32,linux)\n", system.c_str());
            return -1;
         }
         _System = system;
      }
      if (strncmp(argv[arg], "-compiler", 9) == 0) {
         STRING_T compiler = Arg(&(argv[arg][9]), argv[arg+1]);
         if (strcmp(compiler.c_str(), "vcpp") == 0) {
         } else if (strcmp(compiler.c_str(), "gcc") == 0) {
         } else {
            fprintf(stderr, "invalid compiler %s (vcpp,gcc)\n", compiler.c_str());
            return -1;
         }
         _Compiler = compiler;
      }
      if (strncmp(argv[arg], "-config", 7) == 0) {
         STRING_T config = Arg(&(argv[arg][7]), argv[arg+1]);
         if (strcmp(config.c_str(), "debug") == 0) {
         } else if (strcmp(config.c_str(), "release") == 0) {
         } else {
            fprintf(stderr, "invalid configuration %s (debug,release)\n", config.c_str());
            return -1;
         }
         _Configuration = config;
      }
      if (strncmp(argv[arg], "-buildfile", 10) == 0) {
         STRING_T config_file = Arg(&(argv[arg][10]), argv[arg+1]);
         if (config_file.size() == 0) {
            fprintf(stderr, "no build file specified\n");
            return -1;
         }
         _ConfigFile = config_file;
      }
      if (argv[arg][0] == '-') {
//         fprintf(stderr, "invalid option %s\n", argv[arg]);
//         return -1;
      }
   }
   if (Configuration() == "debug") {
      SetSymbol("CONFIGID", "d");
   }
   if (System() == "linux") {
      cFileSystemUtils::set_Type(FSYS_UNIX);
   }
   printf("2i AutoConfig\n");
   printf("building configuration %s for\n", Configuration().c_str());
   printf("system %s\n", System().c_str());
   printf("compiler %s\n", Compiler().c_str());
   printf("build definitions %s\n", cFileSystemUtils::FullPath(ConfigFile().c_str()).c_str());
   printf("...\n");
   config = new cAutoConfig(Configuration().c_str(), ConfigFile().c_str());
   cPath::SetBaseDirectory(cFileSystemUtils::CurrentDir().c_str());
   cPath::_RelativePaths = true;
   config->BuildMakeFile();
   delete config;
   return 0;
}

int main(int argc, char* argv[])
{
   return mmake(argc, argv);
}
