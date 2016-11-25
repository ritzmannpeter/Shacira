
#ifndef cSetupStorage_h
#define cSetupStorage_h 1

#include "Control/LocalDatabase/cFileStorage.h"

class __DLL_EXPORT__ cSetupStorage : public cFileStorage
{
public:
   cSetupStorage(CONST_STRING_T file_name = "Setup");
   virtual ~cSetupStorage();
};

#endif
