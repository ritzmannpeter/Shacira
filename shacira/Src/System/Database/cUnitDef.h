//## begin module%4224A214030D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4224A214030D.cm

//## begin module%4224A214030D.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4224A214030D.cp

//## Module: cUnitDef%4224A214030D; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cUnitDef.h

#ifndef cUnitDef_h
#define cUnitDef_h 1

//## begin module%4224A214030D.includes preserve=yes
//## end module%4224A214030D.includes

// cUserInfo
#include "System/Objects/cUserInfo.h"

class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cSHVariant;
class __DLL_EXPORT__ cFuncRef;

//## begin module%4224A214030D.additionalDeclarations preserve=yes

#define SET_SOURCE(flags,value)  \
{ \
   flags = flags & 0x00ffffff; \
   flags = flags | (value << 24); \
}
#define SET_DESTINATION(flags,value) \
{ \
   flags = flags & 0xff00ffff; \
   flags = flags | (value << 16); \
}
#define GET_SOURCE(flags)        (flags >> 24)
#define GET_DESTINATION(flags)   ((flags & 0x00ff0000) >> 16)

#define MAX_DIM_DEFINITIONS     10

class cUnitSpec 
{
public:
   cUnitSpec(CONST_STRING_T unit_text, UCHAR_T precision)
   {
      _UnitText = unit_text;
      _Precision = precision;
   };
   virtual ~cUnitSpec() {};
public:
   STRING_T _UnitText;
   UCHAR_T _Precision;
};

typedef cUnitSpec* UNIT_SPEC_ARRAY_T[MAX_DIM_DEFINITIONS];
typedef UCHAR_T STATE_ARRAY_T[IF_MAX];

//## end module%4224A214030D.additionalDeclarations


//## begin cUnitDef%4224A214030D.preface preserve=yes
//## end cUnitDef%4224A214030D.preface

//## Class: cUnitDef%4224A214030D
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%4417DE8703DB;cUserInfo { -> }
//## Uses: <unnamed>%4471DA390273;cSHVariant { -> F}

class __DLL_EXPORT__ cUnitDef 
{
  //## begin cUnitDef%4224A214030D.initialDeclarations preserve=yes
  friend class cLocalVariable;
public:
  //## end cUnitDef%4224A214030D.initialDeclarations

    //## Constructors (generated)
      cUnitDef();

      cUnitDef(const cUnitDef &right);

    //## Constructors (specified)
      //## Operation: cUnitDef%1111233643
      cUnitDef (UCHAR_T data_type, cContext *context);

    //## Destructor (generated)
      virtual ~cUnitDef();


    //## Other Operations (specified)
      //## Operation: SetState%1109759952
      void SetState (UCHAR_T state);

      //## Operation: GetState%1111243133
      UCHAR_T GetState ();

      //## Operation: UnitText%1109759953
      STRING_T UnitText (CHAR_T state = (CHAR_T)-1);

      //## Operation: Precision%1109759954
      UCHAR_T Precision (CHAR_T state = (CHAR_T)-1);

      //## Operation: GetValue%1109759955
      //	Gets the value of a variable reference a  CHAR_T value.
      void GetValue (CHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination = (CHAR_T)-1);

      //## Operation: GetValue%1109759956
      //	Gets the value of a variable reference a U CHAR_T value.
      void GetValue (UCHAR_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination = (CHAR_T)-1);

      //## Operation: GetValue%1109759957
      //	Gets the value of a variable reference a  SHORT_T value.
      void GetValue (SHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination = (CHAR_T)-1);

      //## Operation: GetValue%1109759958
      //	Gets the value of a variable reference a  USHORT_T value.
      void GetValue (USHORT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination = (CHAR_T)-1);

      //## Operation: GetValue%1109759959
      //	Gets the value of a variable reference a  LONG_T value.
      void GetValue (LONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination = (CHAR_T)-1);

      //## Operation: GetValue%1109759960
      //	Gets the value of a variable reference a  ULONG_T value.
      void GetValue (ULONG_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination = (CHAR_T)-1);

      //## Operation: GetValue%1109759961
      //	Gets the value of a variable reference a FLOAT_T value.
      void GetValue (FLOAT_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination = (CHAR_T)-1);

      //## Operation: GetValue%1109759962
      //	Gets the value of a variable reference a  DOUBLE_T value.
      void GetValue (DOUBLE_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination = (CHAR_T)-1);

      //## Operation: GetValue%1151480220
      //	Gets the value of a variable reference a  DOUBLE_T value.
      void GetValue (STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, CHAR_T source, CHAR_T destination = (CHAR_T)-1);

      //## Operation: AddUnitSpec%1111588837
      void AddUnitSpec (CONST_STRING_T unit_text, UCHAR_T precision);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: DataType%4225F1320138
      UCHAR_T get_DataType () const;

      //## Attribute: DeviceState%4225EBAC0196
      UCHAR_T get_DeviceState () const;
public:
      void set_DeviceState (UCHAR_T value);

      //## Attribute: DatasetState%423C14400232
      UCHAR_T get_DatasetState () const;
      void set_DatasetState (UCHAR_T value);

      //## Attribute: TargetDependent%470A5EB9020B
      BOOL_T get_TargetDependent () const;
      void set_TargetDependent (BOOL_T value);

    // Data Members for Class Attributes

      //## Attribute: UnitName%4224A26502FD
      //## begin cUnitDef::UnitName%4224A26502FD.attr preserve=no  public: STRING_T {U} 
      STRING_T _UnitName;
      //## end cUnitDef::UnitName%4224A26502FD.attr

    // Data Members for Associations

      //## Association: System::Database::<unnamed>%42257C0A02EE
      //## Role: cUnitDef::Context%42257C0D005E
      //## begin cUnitDef::Context%42257C0D005E.role preserve=no  public: cContext {0..n -> 1RFHN}
      cContext *_Context;
      //## end cUnitDef::Context%42257C0D005E.role

      //## Association: System::Database::<unnamed>%4224A2C6005D
      //## Role: cUnitDef::FuncRef%4224A2C70203
      //## begin cUnitDef::FuncRef%4224A2C70203.role preserve=no  public: cFuncRef { -> 1RFHN}
      void set_FuncRef(cFuncRef* func_ref);
      void set_DevStateFuncRef(cFuncRef* func_ref);
protected:
      cFuncRef *_FuncRef;
      cFuncRef *_DevStateFuncRef;
      //## end cUnitDef::FuncRef%4224A2C70203.role

  public:
    // Additional Public Declarations
      //## begin cUnitDef%4224A214030D.public preserve=yes
      //## end cUnitDef%4224A214030D.public

  protected:
    // Data Members for Class Attributes

      //## begin cUnitDef::DataType%4225F1320138.attr preserve=no  public: UCHAR_T {U} UNDEFINED
      UCHAR_T _DataType;
      //## end cUnitDef::DataType%4225F1320138.attr

      //## begin cUnitDef::DeviceState%4225EBAC0196.attr preserve=no  public: UCHAR_T {U} 0
      UCHAR_T _DeviceState;
      //## end cUnitDef::DeviceState%4225EBAC0196.attr

      //## begin cUnitDef::DatasetState%423C14400232.attr preserve=no  public: UCHAR_T {U} 0
      UCHAR_T _DatasetState;
      //## end cUnitDef::DatasetState%423C14400232.attr

      //## begin cUnitDef::TargetDependent%470A5EB9020B.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _TargetDependent;
      //## end cUnitDef::TargetDependent%470A5EB9020B.attr

    // Additional Protected Declarations
      //## begin cUnitDef%4224A214030D.protected preserve=yes
      //## end cUnitDef%4224A214030D.protected

  private:
    // Additional Private Declarations
      //## begin cUnitDef%4224A214030D.private preserve=yes
      //## end cUnitDef%4224A214030D.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: UnitSpec%1111588838
      cUnitSpec * UnitSpec (UCHAR_T state);

      //## Operation: SetCurrentState%1142413728
      void SetCurrentState (UCHAR_T state);

      //## Operation: GetCurrentState%1142413729
      UCHAR_T GetCurrentState ();

    // Data Members for Class Attributes

      //## Attribute: CurrentState%423C143E03B9
      //## begin cUnitDef::CurrentState%423C143E03B9.attr preserve=no  implementation: UCHAR_T {U} 0
      UCHAR_T _CurrentState;
      //## end cUnitDef::CurrentState%423C143E03B9.attr

      //## Attribute: UnitSpecs%4241819D005D
      //## begin cUnitDef::UnitSpecs%4241819D005D.attr preserve=no  implementation: UNIT_SPEC_ARRAY_T {U} 
      UNIT_SPEC_ARRAY_T _UnitSpecs;
      //## end cUnitDef::UnitSpecs%4241819D005D.attr

      //## Attribute: UnitSpecCount%4241842502CE
      //## begin cUnitDef::UnitSpecCount%4241842502CE.attr preserve=no  implementation: ULONG_T {U} 0
      ULONG_T _UnitSpecCount;
      //## end cUnitDef::UnitSpecCount%4241842502CE.attr

      //## Attribute: CurrentStates%4417E0250010
      //## begin cUnitDef::CurrentStates%4417E0250010.attr preserve=no  implementation: STATE_ARRAY_T {U} 
      STATE_ARRAY_T _CurrentStates;
      //## end cUnitDef::CurrentStates%4417E0250010.attr

    // Additional Implementation Declarations
      //## begin cUnitDef%4224A214030D.implementation preserve=yes
      class cCurrentModelIndices
      {
      public:
         cCurrentModelIndices()
            : _i1(-1), _i2(-1), _i3(-1), _i4(-1), _Initialized(false)
         {
         };
         inline void Set(int i1 = -1, int i2 = -1, int i3 = -1, int i4 = -1)
         {
            _Initialized = true;
            _i1 = i1;
            _i2 = i2;
            _i3 = i3;
            _i4 = i4;
         };
         inline void Get(int & i1, int & i2, int & i3, int & i4) const
         {
            if (!_Initialized) {
               int dummy = 0;
            }
            i1 = _i1;
            i2 = _i2;
            i3 = _i3;
            i4 = _i4;
         };
      private:
         BOOL_T _Initialized;
         int _i1;
         int _i2;
         int _i3;
         int _i4;
      };
      cCurrentModelIndices _CurrentModelIndices;
   public:
#define NO_INLINE
#ifndef NO_INLINE
      inline BOOL_T StoreIndices(int i1 = -1, int i2 = -1, int i3 = -1, int i4 = -1)
      {
         _CurrentModelIndices->Set(i1, i2, i3, i4);
         return true;
      }
      inline BOOL_T RestoreIndices(int & i1, int & i2, int & i3, int & i4) const
      {
         _CurrentModelIndices.Get(i1, i2, i3, i4);
         return true;
      }
#else
      BOOL_T StoreIndices(int i1 = -1, int i2 = -1, int i3 = -1, int i4 = -1);
      BOOL_T RestoreIndices(int & i1, int & i2, int & i3, int & i4) const;
#endif
      UCHAR_T get_DeviceState(int i1, int i2, int i3, int i4);
      BOOL_T HasDeviceStateFunction() const {return (_DevStateFuncRef != NULL);};
      //## end cUnitDef%4224A214030D.implementation

};

//## begin cUnitDef%4224A214030D.postscript preserve=yes
//## end cUnitDef%4224A214030D.postscript

// Class cUnitDef 

//## begin module%4224A214030D.epilog preserve=yes
//## end module%4224A214030D.epilog


#endif
