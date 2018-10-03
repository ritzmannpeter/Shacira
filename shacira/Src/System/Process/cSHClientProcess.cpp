//## begin module%4312DD580335.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4312DD580335.cm

//## begin module%4312DD580335.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4312DD580335.cp

//## Module: cSHClientProcess%4312DD580335; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cSHClientProcess.cpp

//## begin module%4312DD580335.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4312DD580335.additionalIncludes

//## begin module%4312DD580335.includes preserve=yes
//## end module%4312DD580335.includes

// cSHClientProcess
#include "System/Process/cSHClientProcess.h"
// cProxyReceiver
#include "System/Comm/cProxyReceiver.h"
// cNameSpace
#include "System/Namespace/cNameSpace.h"
// cVarRef
#include "System/Database/cVarRef.h"
// cVarDef
#include "System/Database/cVarDef.h"
// cContext
#include "System/Database/cContext.h"
//## begin module%4312DD580335.additionalDeclarations preserve=yes
//## end module%4312DD580335.additionalDeclarations


// Class cSHClientProcess 




cSHClientProcess::cSHClientProcess()
  //## begin cSHClientProcess::cSHClientProcess%.hasinit preserve=no
      : _OfferNameSpace(false), _NameSpace(NULL)
  //## end cSHClientProcess::cSHClientProcess%.hasinit
  //## begin cSHClientProcess::cSHClientProcess%.initialization preserve=yes
  //## end cSHClientProcess::cSHClientProcess%.initialization
{
  //## begin cSHClientProcess::cSHClientProcess%.body preserve=yes
   if (_OfferNameSpace) {
      _NameSpace = new cNameSpace;
   }
  //## end cSHClientProcess::cSHClientProcess%.body
}

cSHClientProcess::cSHClientProcess(const cSHClientProcess &right)
  //## begin cSHClientProcess::cSHClientProcess%copy.hasinit preserve=no
      : _OfferNameSpace(false), _NameSpace(NULL)
  //## end cSHClientProcess::cSHClientProcess%copy.hasinit
  //## begin cSHClientProcess::cSHClientProcess%copy.initialization preserve=yes
  //## end cSHClientProcess::cSHClientProcess%copy.initialization
{
  //## begin cSHClientProcess::cSHClientProcess%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cSHClientProcess::cSHClientProcess%copy.body
}

cSHClientProcess::cSHClientProcess (LONG_T if_type, BOOL_T offer_namespace)
  //## begin cSHClientProcess::cSHClientProcess%1133172775.hasinit preserve=no
      : _OfferNameSpace(false), _NameSpace(NULL)
  //## end cSHClientProcess::cSHClientProcess%1133172775.hasinit
  //## begin cSHClientProcess::cSHClientProcess%1133172775.initialization preserve=yes
  //## end cSHClientProcess::cSHClientProcess%1133172775.initialization
{
  //## begin cSHClientProcess::cSHClientProcess%1133172775.body preserve=yes
   _IFType = if_type;
   if (_OfferNameSpace) {
      _NameSpace = new cNameSpace;
   }
  //## end cSHClientProcess::cSHClientProcess%1133172775.body
}


cSHClientProcess::~cSHClientProcess()
{
  //## begin cSHClientProcess::~cSHClientProcess%.body preserve=yes
  //## end cSHClientProcess::~cSHClientProcess%.body
}



//## Other Operations (implementation)
void cSHClientProcess::OnCycle ()
{
  //## begin cSHClientProcess::OnCycle%1125306232.body preserve=yes
   if (_NameSpace != NULL) {
      cObjectLock __lock__(&_NameSpaceMutex);
      char path[0x1000] = {0};
      STRING_LIST_T context_names;
      ContextNames(context_names, REMOTE_CONTEXTS);
      STRING_LIST_T::const_iterator i = context_names.cbegin();
      while (i != context_names.cend()) {
         STRING_T context_name = (*i);
         cContext * context = Context(context_name.c_str(), REMOTE_CONTEXTS);
         if (!context->IsActive()) {
            context->Connect();
            context->Create();
            _NameSpace->Remove(context_name.c_str());
            STRING_LIST_T var_names;
            context->VariableNames(var_names);
            STRING_LIST_T::const_iterator j = var_names.cbegin();
            while (j != var_names.cend()) {
               STRING_T var_name = (*j);
               cVarDef * var_def = context->VarDef(var_name.c_str());
               if (var_def != NULL) {
                  SafePrintf(path, sizeof(path), "%s/%s",
                             context->get_Name().c_str(),
                             var_def->_VarName.c_str());
                  _NameSpace->Add(path);
               }
               j++;
            }
         }
         i++;
      }
   }
  //## end cSHClientProcess::OnCycle%1125306232.body
}

cNameSpace * cSHClientProcess::NameSpace ()
{
  //## begin cSHClientProcess::NameSpace%1125306233.body preserve=yes
   if (_NameSpace != NULL) {
      cObjectLock __lock__(&_NameSpaceMutex);
      return _NameSpace;
   } else {
      return NULL;
   }
  //## end cSHClientProcess::NameSpace%1125306233.body
}

// Additional Declarations
  //## begin cSHClientProcess%4312DD580335.declarations preserve=yes
  //## end cSHClientProcess%4312DD580335.declarations

//## begin module%4312DD580335.epilog preserve=yes
//## end module%4312DD580335.epilog
