//## begin module%42CBD3270232.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%42CBD3270232.cm

//## begin module%42CBD3270232.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%42CBD3270232.cp

//## Module: cProgress%42CBD3270232; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cProgress.h

#ifndef cProgress_h
#define cProgress_h 1

//## begin module%42CBD3270232.includes preserve=yes
//## end module%42CBD3270232.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"
//## begin module%42CBD3270232.additionalDeclarations preserve=yes

#define DEVICE_DOWNLOAD_PROGRESS       1
#define DEVICE_UPLOAD_PROGRESS         2
#define FILE_READ_PROGRESS             3
#define FILE_WRITE_PROGRESS            4
#define COPY_FGBG_DATA_PROGRESS        5 // HA 230805

#define USER_DEFINED_INDICATORS        1000

//## end module%42CBD3270232.additionalDeclarations


//## begin cProgress%42CBD3270232.preface preserve=yes
//## end cProgress%42CBD3270232.preface

//## Class: cProgress%42CBD3270232
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cProgress : public cTransientObject  //## Inherits: <unnamed>%42CBD3470000
{
  //## begin cProgress%42CBD3270232.initialDeclarations preserve=yes
public:
  //## end cProgress%42CBD3270232.initialDeclarations

    //## Constructors (generated)
      cProgress();

      cProgress(const cProgress &right);

    //## Constructors (specified)
      //## Operation: cProgress%1120654321
      cProgress (cStaticObject *source, ULONG_T indicator_id, ULONG_T value = 0);

    //## Destructor (generated)
      virtual ~cProgress();


    //## Other Operations (specified)
      //## Operation: Serialize%1120654322
      virtual STRING_T Serialize ();

      //## Operation: Construct%1120654323
      virtual BOOL_T Construct (CONST_STRING_T serialized_obj);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: IndicatorId%42CBD3B601E4
      ULONG_T get_IndicatorId () const;
      void set_IndicatorId (ULONG_T value);

      //## Attribute: Value%42CBD3D8009C
      ULONG_T get_Value () const;
      void set_Value (ULONG_T value);

  public:
    // Additional Public Declarations
      //## begin cProgress%42CBD3270232.public preserve=yes
      //## end cProgress%42CBD3270232.public

  protected:
    // Data Members for Class Attributes

      //## begin cProgress::IndicatorId%42CBD3B601E4.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _IndicatorId;
      //## end cProgress::IndicatorId%42CBD3B601E4.attr

      //## begin cProgress::Value%42CBD3D8009C.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Value;
      //## end cProgress::Value%42CBD3D8009C.attr

    // Additional Protected Declarations
      //## begin cProgress%42CBD3270232.protected preserve=yes
      //## end cProgress%42CBD3270232.protected

  private:
    // Additional Private Declarations
      //## begin cProgress%42CBD3270232.private preserve=yes
      //## end cProgress%42CBD3270232.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cProgress%42CBD3270232.implementation preserve=yes
      //## end cProgress%42CBD3270232.implementation

};

//## begin cProgress%42CBD3270232.postscript preserve=yes
//## end cProgress%42CBD3270232.postscript

// Class cProgress 

//## begin module%42CBD3270232.epilog preserve=yes
//## end module%42CBD3270232.epilog


#endif
