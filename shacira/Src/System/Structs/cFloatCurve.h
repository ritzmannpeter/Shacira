//## begin module%4146F94202EE.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4146F94202EE.cm

//## begin module%4146F94202EE.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4146F94202EE.cp

//## Module: cFloatCurve%4146F94202EE; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Structs\cFloatCurve.h

#ifndef cFloatCurve_h
#define cFloatCurve_h 1

//## begin module%4146F94202EE.includes preserve=yes
//## end module%4146F94202EE.includes

// cGraphicCurve
#include "System/Structs/cGraphicCurve.h"
//## begin module%4146F94202EE.additionalDeclarations preserve=yes
//## end module%4146F94202EE.additionalDeclarations


//## begin cFloatCurve%4146F94202EE.preface preserve=yes
//## end cFloatCurve%4146F94202EE.preface

//## Class: cFloatCurve%4146F94202EE
//## Category: System::Structs%411DEC2E032C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cFloatCurve : public cGraphicCurve  //## Inherits: <unnamed>%4146F95A03B9
{
  //## begin cFloatCurve%4146F94202EE.initialDeclarations preserve=yes
public:
  //## end cFloatCurve%4146F94202EE.initialDeclarations

    //## Constructors (generated)
      cFloatCurve();

      cFloatCurve(const cFloatCurve &right);

    //## Constructors (specified)
      //## Operation: cFloatCurve%1095170838
      cFloatCurve (PTR_T data, ULONG_T data_size, ULONG_T value_count);

      //## Operation: cFloatCurve%1095170839
      cFloatCurve (PTR_T data);

    //## Destructor (generated)
      virtual ~cFloatCurve();


    //## Other Operations (specified)
      //## Operation: SetXVal%1095170840
      virtual void SetXVal (FLOAT_T value, ULONG_T index);

      //## Operation: SetYVal%1095170841
      virtual void SetYVal (FLOAT_T value, ULONG_T index);

      //## Operation: GetXVal%1095170842
      virtual void GetXVal (FLOAT_T &value, ULONG_T index);

      //## Operation: GetYVal%1095170843
      virtual void GetYVal (FLOAT_T &value, ULONG_T index);

  public:
    // Additional Public Declarations
      //## begin cFloatCurve%4146F94202EE.public preserve=yes
      //## end cFloatCurve%4146F94202EE.public

  protected:
    // Additional Protected Declarations
      //## begin cFloatCurve%4146F94202EE.protected preserve=yes
      //## end cFloatCurve%4146F94202EE.protected

  private:
    // Additional Private Declarations
      //## begin cFloatCurve%4146F94202EE.private preserve=yes
      //## end cFloatCurve%4146F94202EE.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: XValues%4146FB9E03D8
      //## begin cFloatCurve::XValues%4146FB9E03D8.attr preserve=no  implementation: FLOAT_T * {U} 
      FLOAT_T *_XValues;
      //## end cFloatCurve::XValues%4146FB9E03D8.attr

      //## Attribute: YValues%4146FB9E03D9
      //## begin cFloatCurve::YValues%4146FB9E03D9.attr preserve=no  implementation: FLOAT_T * {U} 
      FLOAT_T *_YValues;
      //## end cFloatCurve::YValues%4146FB9E03D9.attr

    // Additional Implementation Declarations
      //## begin cFloatCurve%4146F94202EE.implementation preserve=yes
      //## end cFloatCurve%4146F94202EE.implementation

};

//## begin cFloatCurve%4146F94202EE.postscript preserve=yes
//## end cFloatCurve%4146F94202EE.postscript

// Class cFloatCurve 

//## begin module%4146F94202EE.epilog preserve=yes
//## end module%4146F94202EE.epilog


#endif
