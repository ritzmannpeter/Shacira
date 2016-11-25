
#include "cDependentConfig.h"
#include "cAutoConfig.h"

cDependentConfig::cDependentConfig(const char * config_path, cAutoConfig * parent)
{
   _Path = new cPath(config_path);
   _Parent = parent;
   char current_directory[1024] = {0};
   DWORD len = GetCurrentDirectory(sizeof(current_directory), current_directory);
   STRING_T new_path = _Path->Path();
   if (SetCurrentDirectory(new_path.c_str())) {
      _Config = new cAutoConfig(parent->_ConfigName.c_str(), _Path->FileName().c_str());
      cPath::SetBaseDirectory(cFileSystemUtils::CurrentDir().c_str());
      cPath::_RelativePaths = true;
//      cPath::Print();
      _Config->BuildMakeFile();
      SetCurrentDirectory(current_directory);
   } else {
      fprintf(stderr, "failed to change to directory %s\n", new_path.c_str());
      exit(-1);
   }
}

cDependentConfig::~cDependentConfig()
{
}

cAutoConfig * cDependentConfig::Config()
{
   return _Config;
}

STRING_T cDependentConfig::Path()
{
   return _Path->Path();
}


