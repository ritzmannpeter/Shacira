//## begin module%414092400109.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%414092400109.cm

//## begin module%414092400109.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%414092400109.cp

//## Module: cGraphicCurve%414092400109; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Structs\cGraphicCurve.h

#ifndef cGraphicCurve_h
#define cGraphicCurve_h 1

//## begin module%414092400109.includes preserve=yes
//## end module%414092400109.includes

// cFlatObject
#include "System/Structs/cFlatObject.h"
//## begin module%414092400109.additionalDeclarations preserve=yes

#include "Pack_1"

#define DIM_LEN   8

typedef struct {
   USHORT_T function;
   USHORT_T function_unit;
   USHORT_T curve_id;
   ULONG_T value_count;
   ULONG_T value_size;
   DOUBLE_T xscale_start;
   DOUBLE_T xscale_end;
   DOUBLE_T yscale_start;
   DOUBLE_T yscale_end;
   DOUBLE_T min_val;
   DOUBLE_T max_val;
   USHORT_T x_precision;
   USHORT_T y_precision;
   char x_dim[DIM_LEN];
   char y_dim[DIM_LEN];
}  GRAPHIC_CURVE_INFO_T;

typedef struct {
   FLAT_OBJECT_HEADER_T header;
   GRAPHIC_CURVE_INFO_T curve_info;
   UCHAR_T free_space[FLAT_OBJECT_HEADER_SIZE - sizeof(FLAT_OBJECT_HEADER_T) - sizeof(GRAPHIC_CURVE_INFO_T)];
}  GRAPHIC_CURVE_HEADER_T;

#include "UnPack"

#define MAX_CURVE_VALUES   500

//## end module%414092400109.additionalDeclarations


//## begin cGraphicCurve%414092400109.preface preserve=yes
//## end cGraphicCurve%414092400109.preface

//## Class: cGraphicCurve%414092400109
//## Category: System::Structs%411DEC2E032C
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cGraphicCurve : public cFlatObject  //## Inherits: <unnamed>%41413EA600FA
{
  //## begin cGraphicCurve%414092400109.initialDeclarations preserve=yes
public:
  //## end cGraphicCurve%414092400109.initialDeclarations

    //## Constructors (generated)
      cGraphicCurve();

      cGraphicCurve(const cGraphicCurve &right);

    //## Constructors (specified)
      //## Operation: cGraphicCurve%1094751266
      cGraphicCurve (PTR_T data, ULONG_T data_size, ULONG_T value_count, ULONG_T value_size = 2);

      //## Operation: cGraphicCurve%1094751267
      cGraphicCurve (PTR_T data);

    //## Destructor (generated)
      virtual ~cGraphicCurve();


    //## Other Operations (specified)
      //## Operation: GetValueCount%1094795554
      virtual ULONG_T GetValueCount ();

      //## Operation: GetValueSize%1094795555
      virtual ULONG_T GetValueSize ();

      //## Operation: GetXScaleStart%1094795557
      virtual DOUBLE_T GetXScaleStart ();

      //## Operation: GetXScaleEnd%1094795556
      virtual DOUBLE_T GetXScaleEnd ();

      //## Operation: SetXScaleStart%1095952121
      virtual void SetXScaleStart (DOUBLE_T value);

      //## Operation: SetXScaleEnd%1095952122
      virtual void SetXScaleEnd (DOUBLE_T value);

      //## Operation: GetYScaleStart%1095952123
      virtual DOUBLE_T GetYScaleStart ();

      //## Operation: GetYScaleEnd%1095952124
      virtual DOUBLE_T GetYScaleEnd ();

      //## Operation: SetYScaleStart%1095952125
      virtual void SetYScaleStart (DOUBLE_T value);

      //## Operation: SetYScaleEnd%1095952126
      virtual void SetYScaleEnd (DOUBLE_T value);

      //## Operation: GetMinVal%1094795558
      virtual DOUBLE_T GetMinVal ();

      //## Operation: GetMaxVal%1094795559
      virtual DOUBLE_T GetMaxVal ();

      //## Operation: GetFunction%1094890789
      virtual USHORT_T GetFunction ();

      //## Operation: GetFunctionUnit%1094890790
      virtual USHORT_T GetFunctionUnit ();

      //## Operation: GetCurveId%1094890791
      virtual USHORT_T GetCurveId ();

      //## Operation: SetFunction%1094890792
      virtual void SetFunction (USHORT_T function);

      //## Operation: SetFunctionUnit%1094890793
      virtual void SetFunctionUnit (USHORT_T function_unit);

      //## Operation: SetCurveId%1094890794
      virtual void SetCurveId (USHORT_T curve_id);

      //## Operation: SetXVal%1095144429
      virtual void SetXVal (SHORT_T value, ULONG_T index);

      //## Operation: SetYVal%1095144430
      virtual void SetYVal (SHORT_T value, ULONG_T index);

      //## Operation: GetXVal%1095170832
      virtual void GetXVal (SHORT_T &value, ULONG_T index);

      //## Operation: GetYVal%1095170833
      virtual void GetYVal (SHORT_T &value, ULONG_T index);

      //## Operation: SetXVal%1095170834
      virtual void SetXVal (FLOAT_T value, ULONG_T index);

      //## Operation: SetYVal%1095170835
      virtual void SetYVal (FLOAT_T value, ULONG_T index);

      //## Operation: GetXVal%1095170836
      virtual void GetXVal (FLOAT_T &value, ULONG_T index);

      //## Operation: GetYVal%1095170837
      virtual void GetYVal (FLOAT_T &value, ULONG_T index);

      //## Operation: SetValueCount%1096448298
      virtual void SetValueCount (ULONG_T value_count);

      //## Operation: SetMinVal%1102922391
      virtual void SetMinVal (DOUBLE_T value);

      //## Operation: SetMaxVal%1102922392
      virtual void SetMaxVal (DOUBLE_T value);

      //## Operation: SetXPrecision%1103015088
      virtual void SetXPrecision (USHORT_T value);

      //## Operation: SetYPrecision%1103015089
      virtual void SetYPrecision (USHORT_T value);

      //## Operation: GetXPrecision%1103015090
      virtual USHORT_T GetXPrecision ();

      //## Operation: GetYPrecision%1103015091
      virtual USHORT_T GetYPrecision ();

      //## Operation: SetXDim%1103015443
      virtual void SetXDim (CONST_STRING_T value);

      //## Operation: SetYDim%1103015444
      virtual void SetYDim (CONST_STRING_T value);

      //## Operation: GetXDim%1103015445
      virtual CONST_STRING_T GetXDim ();

      //## Operation: GetYDim%1103015446
      virtual CONST_STRING_T GetYDim ();

  public:
    // Additional Public Declarations
      //## begin cGraphicCurve%414092400109.public preserve=yes
      //## end cGraphicCurve%414092400109.public

  protected:
    // Data Members for Class Attributes

      //## Attribute: CurveHeader%4142B4F201C5
      //## begin cGraphicCurve::CurveHeader%4142B4F201C5.attr preserve=no  protected: GRAPHIC_CURVE_HEADER_T * {U} NULL
      GRAPHIC_CURVE_HEADER_T *_CurveHeader;
      //## end cGraphicCurve::CurveHeader%4142B4F201C5.attr

    // Additional Protected Declarations
      //## begin cGraphicCurve%414092400109.protected preserve=yes
      //## end cGraphicCurve%414092400109.protected

  private:
    // Additional Private Declarations
      //## begin cGraphicCurve%414092400109.private preserve=yes
      //## end cGraphicCurve%414092400109.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cGraphicCurve%414092400109.implementation preserve=yes
      //## end cGraphicCurve%414092400109.implementation

};

//## begin cGraphicCurve%414092400109.postscript preserve=yes
//## end cGraphicCurve%414092400109.postscript

// Class cGraphicCurve 

//## begin module%414092400109.epilog preserve=yes
//## end module%414092400109.epilog


#endif
