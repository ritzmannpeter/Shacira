#include "FirstHeader.h"
#include "System/Objects/cProtocol.h"
#include "System/Objects/cStaticObject.h"
#include "System/Objects/cTransferObject.h"

cProtocol::cProtocol()
{
   _Type = OT_PROTOCOL;
}

cProtocol::cProtocol(cStaticObject *source, CONST_STRING_T msg)
   : cTransientObject(source)
{
   _Type = OT_PROTOCOL;
   _Key = source->get_Name();
   _Msg = msg;
}


cProtocol::~cProtocol()
{
}

STRING_T cProtocol::Serialize()
{
   cTransferObject obj;
   SerializeBase(obj);
   obj.AddAttribute(0, _Msg.c_str(), ObjectBody);
   return obj.Serialize().c_str();
}

BOOL_T cProtocol::Construct (CONST_STRING_T serialized_obj)
{
   cTransferObject obj(serialized_obj);
   if (!ConstructBase(obj)) return false;
   obj.GetAttribute(0, _Msg, ObjectBody);
   return true;
}

STRING_T cProtocol::Msg()
{
   return _Msg;
}

void cProtocol::SetMsg(CONST_STRING_T msg)
{
   _Msg = msg;
}

