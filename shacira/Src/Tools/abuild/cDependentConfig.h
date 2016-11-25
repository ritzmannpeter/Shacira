
#ifndef cDependentConfig_h
#define cDependentConfig_h

#include "cConfigUtils.h"
#include "cPath.h"
class cAutoConfig;

class cDependentConfig
{
public:
   cDependentConfig(const char * config_file, cAutoConfig * parent);
   virtual ~cDependentConfig();
   cAutoConfig * Config();
   STRING_T Path();
private:
   cPath * _Path;
   cAutoConfig * _Parent;
   cAutoConfig * _Config;
};

#endif
