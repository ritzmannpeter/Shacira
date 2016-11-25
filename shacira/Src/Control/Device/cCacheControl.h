//## begin module%3FD5A20402AF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FD5A20402AF.cm

//## begin module%3FD5A20402AF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FD5A20402AF.cp

//## Module: cCacheControl%3FD5A20402AF; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cCacheControl.h

#ifndef cCacheControl_h
#define cCacheControl_h 1

//## begin module%3FD5A20402AF.includes preserve=yes
//## end module%3FD5A20402AF.includes

// cControlThread
#include "System/Threads/cControlThread.h"

class __DLL_EXPORT__ cObjectLock;
class __DLL_EXPORT__ cDevice;
class __DLL_EXPORT__ cCache;

//## begin module%3FD5A20402AF.additionalDeclarations preserve=yes
//## end module%3FD5A20402AF.additionalDeclarations


//## begin cCacheControl%3FD5A20402AF.preface preserve=yes
//## end cCacheControl%3FD5A20402AF.preface

//## Class: cCacheControl%3FD5A20402AF
//## Category: Control::Device%3FCF205002CE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3FD5ADA2000F;cObjectLock { -> F}

class __DLL_EXPORT__ cCacheControl : public cControlThread  //## Inherits: <unnamed>%3FD5A25B00EA
{
  //## begin cCacheControl%3FD5A20402AF.initialDeclarations preserve=yes
public:
  //## end cCacheControl%3FD5A20402AF.initialDeclarations

    //## Constructors (generated)
      cCacheControl();

      cCacheControl(const cCacheControl &right);

    //## Constructors (specified)
      //## Operation: cCacheControl%1070963657
      cCacheControl (cDevice *device);

    //## Destructor (generated)
      virtual ~cCacheControl();


    //## Other Operations (specified)
      //## Operation: SetCache%1070963658
      void SetCache (cCache *cache);

      //## Operation: ControlFunc%1070963659
      virtual INT_T ControlFunc ();

      //## Operation: MinIdleTime%1084967064
      virtual ULONG_T MinIdleTime ();

  public:
    // Additional Public Declarations
      //## begin cCacheControl%3FD5A20402AF.public preserve=yes
      //## end cCacheControl%3FD5A20402AF.public

  protected:
    // Data Members for Associations

      //## Association: Control::Device::<unnamed>%3FD5D554003E
      //## Role: cCacheControl::Device%3FD5D555005E
      //## begin cCacheControl::Device%3FD5D555005E.role preserve=no  public: cDevice {0..1 -> 1RFHN}
      cDevice *_Device;
      //## end cCacheControl::Device%3FD5D555005E.role

      //## Association: Control::Device::<unnamed>%3FD5A7DE01E4
      //## Role: cCacheControl::Caches%3FD5A7DF01D4
      //## Qualifier: name%3FD5A829000F; STRING_T
      //## begin cCacheControl::Caches%3FD5A7DF01D4.role preserve=no  public: cCache { -> 0..nRFHN}
      std::map<STRING_T, cCache*> _Caches;
      //## end cCacheControl::Caches%3FD5A7DF01D4.role

    // Additional Protected Declarations
      //## begin cCacheControl%3FD5A20402AF.protected preserve=yes
      //## end cCacheControl%3FD5A20402AF.protected

  private:
    // Additional Private Declarations
      //## begin cCacheControl%3FD5A20402AF.private preserve=yes
      //## end cCacheControl%3FD5A20402AF.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCacheControl%3FD5A20402AF.implementation preserve=yes
      //## end cCacheControl%3FD5A20402AF.implementation

};

//## begin cCacheControl%3FD5A20402AF.postscript preserve=yes
//## end cCacheControl%3FD5A20402AF.postscript

// Class cCacheControl 

//## begin module%3FD5A20402AF.epilog preserve=yes
//## end module%3FD5A20402AF.epilog


#endif
