//## begin module%41469323034B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%41469323034B.cm

//## begin module%41469323034B.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%41469323034B.cp

//## Module: cShortCurve%41469323034B; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Structs\cShortCurve.h

#ifndef cShortCurve_h
#define cShortCurve_h 1

//## begin module%41469323034B.includes preserve=yes
//## end module%41469323034B.includes

// cGraphicCurve
#include "System/Structs/cGraphicCurve.h"
//## begin module%41469323034B.additionalDeclarations preserve=yes
//## end module%41469323034B.additionalDeclarations


//## begin cShortCurve%41469323034B.preface preserve=yes
//## end cShortCurve%41469323034B.preface

//## Class: cShortCurve%41469323034B
//## Category: System::Structs%411DEC2E032C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cShortCurve : public cGraphicCurve  //## Inherits: <unnamed>%41469352036B
{
  //## begin cShortCurve%41469323034B.initialDeclarations preserve=yes
public:
  //## end cShortCurve%41469323034B.initialDeclarations

    //## Constructors (generated)
      cShortCurve();

      cShortCurve(const cShortCurve &right);

    //## Constructors (specified)
      //## Operation: cShortCurve%1095144427
      cShortCurve (PTR_T data, ULONG_T data_size, ULONG_T value_count);

      //## Operation: cShortCurve%1095144428
      cShortCurve (PTR_T data);

    //## Destructor (generated)
      virtual ~cShortCurve();


    //## Other Operations (specified)
      //## Operation: SetXVal%1095144433
      virtual void SetXVal (SHORT_T value, ULONG_T index);

      //## Operation: SetYVal%1095144434
      virtual void SetYVal (SHORT_T value, ULONG_T index);

      //## Operation: GetXVal%1095144435
      virtual void GetXVal (SHORT_T &value, ULONG_T index);

      //## Operation: GetYVal%1095144436
      virtual void GetYVal (SHORT_T &value, ULONG_T index);

  public:
    // Additional Public Declarations
      //## begin cShortCurve%41469323034B.public preserve=yes
      //## end cShortCurve%41469323034B.public

  protected:
    // Additional Protected Declarations
      //## begin cShortCurve%41469323034B.protected preserve=yes
      //## end cShortCurve%41469323034B.protected

  private:
    // Additional Private Declarations
      //## begin cShortCurve%41469323034B.private preserve=yes
      //## end cShortCurve%41469323034B.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: XValues%414695CF0000
      //## begin cShortCurve::XValues%414695CF0000.attr preserve=no  implementation: SHORT_T * {U} 
      SHORT_T *_XValues;
      //## end cShortCurve::XValues%414695CF0000.attr

      //## Attribute: YValues%414695EE00BB
      //## begin cShortCurve::YValues%414695EE00BB.attr preserve=no  implementation: SHORT_T * {U} 
      SHORT_T *_YValues;
      //## end cShortCurve::YValues%414695EE00BB.attr

    // Additional Implementation Declarations
      //## begin cShortCurve%41469323034B.implementation preserve=yes
      //## end cShortCurve%41469323034B.implementation

};

//## begin cShortCurve%41469323034B.postscript preserve=yes
//## end cShortCurve%41469323034B.postscript

// Class cShortCurve 

//## begin module%41469323034B.epilog preserve=yes
//## end module%41469323034B.epilog


#endif
