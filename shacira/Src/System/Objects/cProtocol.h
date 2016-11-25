#ifndef cProtocol_h
#define cProtocol_h 1

#include "System/Objects/cTransientObject.h"

class __DLL_EXPORT__ cTransferObject;

class __DLL_EXPORT__ cProtocol : public cTransientObject
{
public:
   cProtocol();
   cProtocol(cStaticObject *source, CONST_STRING_T msg);
   virtual ~cProtocol();
   virtual STRING_T Serialize();
   virtual BOOL_T Construct(CONST_STRING_T serialized_obj);
   STRING_T Msg();
   void SetMsg(CONST_STRING_T msg);

protected:
   STRING_T _Msg;
};

#endif
