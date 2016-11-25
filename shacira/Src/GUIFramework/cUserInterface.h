//## begin module%40054A77001F.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%40054A77001F.cm

//## begin module%40054A77001F.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%40054A77001F.cp

//## Module: cUserInterface%40054A77001F; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\GUIFramework\cUserInterface.h

#ifndef cUserInterface_h
#define cUserInterface_h 1

//## begin module%40054A77001F.includes preserve=yes
//## end module%40054A77001F.includes

// cCustomFunctions
#include "System/cCustomFunctions.h"
// cConfigurationObject
#include "System/Config/cConfigurationObject.h"
// cContextChooser
#include "GUIFramework/Interface/cContextChooser.h"

class __DLL_EXPORT__ cSHProcess;
class __DLL_EXPORT__ cConsole;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cCCSInterface;
class __DLL_EXPORT__ cNodeList;
class __DLL_EXPORT__ cNode;

//## begin module%40054A77001F.additionalDeclarations preserve=yes
//## end module%40054A77001F.additionalDeclarations


//## begin cUserInterface%40054A77001F.preface preserve=yes
//## end cUserInterface%40054A77001F.preface

//## Class: cUserInterface%40054A77001F
//## Category: GUIFramework%4005256D03D8
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%400551A203C8;cNode { -> F}
//## Uses: <unnamed>%408CF8F60280;cConfigurationObject { -> }
//## Uses: <unnamed>%41680D3F033C;cContextChooser { -> }
//## Uses: <unnamed>%41682777030D;cSHProcess { -> F}
//## Uses: <unnamed>%41ED065B00AB;cCustomFunctions { -> }
//## Uses: <unnamed>%41ED0778006D;cContext { -> F}

class __DLL_EXPORT__ cUserInterface 
{
  //## begin cUserInterface%40054A77001F.initialDeclarations preserve=yes
public:
  //## end cUserInterface%40054A77001F.initialDeclarations

    //## Constructors (generated)
      cUserInterface();

      cUserInterface(const cUserInterface &right);

    //## Constructors (specified)
      //## Operation: cUserInterface%1074088882
      cUserInterface (BOOL_T remote, CONST_STRING_T language, cConsole *console = NULL);

    //## Destructor (generated)
      virtual ~cUserInterface();


    //## Other Operations (specified)
      //## Operation: Initialize%1074088876
      virtual void Initialize (cCCSInterface *ccs_interface, cConsole *console) = 0;

      //## Operation: Start%1074088877
      virtual int Start (BOOL_T success) = 0;

      //## Operation: IsRemote%1097490347
      BOOL_T IsRemote ();

    // Data Members for Associations

      //## Association: GUIFramework::<unnamed>%4168023E0222
      //## Role: cUserInterface::ContextChooser%4168023F0109
      //## begin cUserInterface::ContextChooser%4168023F0109.role preserve=no  public: cContextChooser { -> 0..1RFHN}
      cContextChooser *_ContextChooser;
      //## end cUserInterface::ContextChooser%4168023F0109.role

  public:
    // Additional Public Declarations
      //## begin cUserInterface%40054A77001F.public preserve=yes
      //## end cUserInterface%40054A77001F.public

  protected:

    //## Other Operations (specified)
      //## Operation: GUIInitialize%1106052709
      virtual BOOL_T GUIInitialize (ULONG_T step, cContext *context);

    // Data Members for Class Attributes

      //## Attribute: Process%41682788005D
      //## begin cUserInterface::Process%41682788005D.attr preserve=no  protected: cSHProcess * {U} NULL
      cSHProcess *_Process;
      //## end cUserInterface::Process%41682788005D.attr

      //## Attribute: Remote%416A5F5803A9
      //## begin cUserInterface::Remote%416A5F5803A9.attr preserve=no  protected: BOOL_T {U} false
      BOOL_T _Remote;
      //## end cUserInterface::Remote%416A5F5803A9.attr

      //## Attribute: ActContext%42135FD10177
      //## begin cUserInterface::ActContext%42135FD10177.attr preserve=no  protected: cContext * {U} NULL
      cContext *_ActContext;
      //## end cUserInterface::ActContext%42135FD10177.attr

    // Data Members for Associations

      //## Association: GUIFramework::QTFramework::<unnamed>%40054BD8033C
      //## Role: cUserInterface::NodeList%40054BD901E4
      //## begin cUserInterface::NodeList%40054BD901E4.role preserve=no  public: cNodeList { -> 1RFHN}
      cNodeList *_NodeList;
      //## end cUserInterface::NodeList%40054BD901E4.role

      //## Association: GUIFramework::QTFramework::<unnamed>%40DBF305005D
      //## Role: cUserInterface::CCSInterface%40DBF3060186
      //## begin cUserInterface::CCSInterface%40DBF3060186.role preserve=no  public: cCCSInterface { -> 1RFHN}
      cCCSInterface *_CCSInterface;
      //## end cUserInterface::CCSInterface%40DBF3060186.role

      //## Association: GUIFramework::QTFramework::<unnamed>%40DBF38E008C
      //## Role: cUserInterface::Console%40DBF38E02EE
      //## begin cUserInterface::Console%40DBF38E02EE.role preserve=no  public: cConsole { -> 0..1RFHN}
      cConsole *_Console;
      //## end cUserInterface::Console%40DBF38E02EE.role

    // Additional Protected Declarations
      //## begin cUserInterface%40054A77001F.protected preserve=yes
      //## end cUserInterface%40054A77001F.protected

  private:
    // Additional Private Declarations
      //## begin cUserInterface%40054A77001F.private preserve=yes
      //## end cUserInterface%40054A77001F.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: GUIInitFuncAddress%41ED06AB0148
      //## begin cUserInterface::GUIInitFuncAddress%41ED06AB0148.attr preserve=no  implementation: GUI_INIT_FUNC_T {U} NULL
      GUI_INIT_FUNC_T _GUIInitFuncAddress;
      //## end cUserInterface::GUIInitFuncAddress%41ED06AB0148.attr

    // Additional Implementation Declarations
      //## begin cUserInterface%40054A77001F.implementation preserve=yes
      //## end cUserInterface%40054A77001F.implementation

};

//## begin cUserInterface%40054A77001F.postscript preserve=yes
//## end cUserInterface%40054A77001F.postscript

// Class cUserInterface 

//## begin module%40054A77001F.epilog preserve=yes
//## end module%40054A77001F.epilog


#endif
