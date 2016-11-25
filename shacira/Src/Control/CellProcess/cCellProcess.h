//## begin module%3A791D8600CA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3A791D8600CA.cm

//## begin module%3A791D8600CA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3A791D8600CA.cp

//## Module: cCellProcess%3A791D8600CA; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\CellProcess\cCellProcess.h

#ifndef cCellProcess_h
#define cCellProcess_h 1

//## begin module%3A791D8600CA.includes preserve=yes
//## end module%3A791D8600CA.includes

// cSHProcess
#include "System/Process/cSHProcess.h"

class __DLL_EXPORT__ cConfigurationObject;
class __DLL_EXPORT__ cProxySender;
class __DLL_EXPORT__ cSysProcess;
class __DLL_EXPORT__ cCell;
class __DLL_EXPORT__ cBackupThread;
class __DLL_EXPORT__ cLocalContext;
class __DLL_EXPORT__ cRemoteContext;

//## begin module%3A791D8600CA.additionalDeclarations preserve=yes

typedef std::list<cCell*> CELL_LIST_T;
//typedef void * ADD_VARIABLES_CLOSURE_T;
//typedef void * SET_VARIABLES_CLOSURE_T;
typedef void (*ADD_VARIABLES_CLOSURE_T)(cLocalContext * local_context);
typedef void (*SET_VARIABLES_CLOSURE_T)(cLocalContext * local_context);

//## end module%3A791D8600CA.additionalDeclarations


//## begin cCellProcess%3A791D8600CA.preface preserve=yes
//## end cCellProcess%3A791D8600CA.preface

//## Class: cCellProcess%3A791D8600CA
//## Category: Control::CellProcess%3A791D71001F
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3A791E67020E;cConfigurationObject { -> F}
//## Uses: <unnamed>%3AA3B2FB002A;cCell { -> F}
//## Uses: <unnamed>%3B17AF00035B;cSysProcess { -> F}
//## Uses: <unnamed>%3E146B38033A;cProxySender { -> F}
//## Uses: <unnamed>%42E7479F03C8;cRemoteContext { -> F}
//## Uses: <unnamed>%42E747B0030D;cLocalContext { -> F}

class __DLL_EXPORT__ cCellProcess : public cSHProcess  //## Inherits: <unnamed>%3EDDAAEC01D4
{
  //## begin cCellProcess%3A791D8600CA.initialDeclarations preserve=yes
public:
  //## end cCellProcess%3A791D8600CA.initialDeclarations

    //## Constructors (generated)
      cCellProcess();

      cCellProcess(const cCellProcess &right);

    //## Constructors (specified)
      //## Operation: cCellProcess%981016466
      cCellProcess (cConfigurationObject *config_obj);
      cCellProcess (int context_count, const char * base_context_name, ADD_VARIABLES_CLOSURE_T add_closure, SET_VARIABLES_CLOSURE_T set_closure);

    //## Destructor (generated)
      virtual ~cCellProcess();


    //## Other Operations (specified)
      //## Operation: Start%1072710117
      virtual void Start ();

      //## Operation: Stop%1072710118
      virtual void Stop ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: BaseDir%3AE931C60337
      STRING_T get_BaseDir () const;

  public:
    // Additional Public Declarations
      //## begin cCellProcess%3A791D8600CA.public preserve=yes
      //## end cCellProcess%3A791D8600CA.public

  protected:
    // Data Members for Class Attributes

      //## begin cCellProcess::BaseDir%3AE931C60337.attr preserve=no  public: STRING_T {U} 
      STRING_T _BaseDir;
      //## end cCellProcess::BaseDir%3AE931C60337.attr

    // Data Members for Associations

      //## Association: Control::CellProcess::<unnamed>%3AE92B530184
      //## Role: cCellProcess::Backup%3AE92B550263
      //## begin cCellProcess::Backup%3AE92B550263.role preserve=no  public: cBackupThread {1 -> 1RFHN}
      cBackupThread *_Backup;
      //## end cCellProcess::Backup%3AE92B550263.role

    // Additional Protected Declarations
      //## begin cCellProcess%3A791D8600CA.protected preserve=yes
      //## end cCellProcess%3A791D8600CA.protected

  private:
    // Additional Private Declarations
      //## begin cCellProcess%3A791D8600CA.private preserve=yes
      //## end cCellProcess%3A791D8600CA.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCellProcess%3A791D8600CA.implementation preserve=yes
      //## end cCellProcess%3A791D8600CA.implementation

};

//## begin cCellProcess%3A791D8600CA.postscript preserve=yes
//## end cCellProcess%3A791D8600CA.postscript

// Class cCellProcess 

//## begin module%3A791D8600CA.epilog preserve=yes
//## end module%3A791D8600CA.epilog


#endif
