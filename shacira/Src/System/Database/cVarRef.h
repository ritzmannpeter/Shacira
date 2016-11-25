//## begin module%3C7E422F03C0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C7E422F03C0.cm

//## begin module%3C7E422F03C0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C7E422F03C0.cp

//## Module: cVarRef%3C7E422F03C0; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cVarRef.h

#ifndef cVarRef_h
#define cVarRef_h 1

//## begin module%3C7E422F03C0.includes preserve=yes
#include "System/Database/cBinaryObject.h"
//## end module%3C7E422F03C0.includes

// cPtrList
#include "System/Memory/cPtrList.h"
// cArgument
#include "System/Database/cArgument.h"

class __DLL_EXPORT__ cDataChange;
class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cVariable;
class __DLL_EXPORT__ cSHVariant;
class __DLL_EXPORT__ cUnitDef;
class __DLL_EXPORT__ cDataControl;
class __DLL_EXPORT__ cDataChangeAdapter;

//## begin module%3C7E422F03C0.additionalDeclarations preserve=yes

#define BACKGROUND_SENSITIVE  0x00010000

//## end module%3C7E422F03C0.additionalDeclarations


//## begin cVarRef%3C7E422F03C0.preface preserve=yes
//## end cVarRef%3C7E422F03C0.preface

//## Class: cVarRef%3C7E422F03C0
//	This class implements a variable reference. A variable
//	reference is realized as a tree with an unlimited number
//	of nodes.
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3D077F1802CD;cDataChange { -> F}
//## Uses: <unnamed>%3E0046120070;cArgument { -> }
//## Uses: <unnamed>%3E2597A2034C;cVarDef { -> F}
//## Uses: <unnamed>%3EDB77270251;cDataChangeAdapter { -> F}
//## Uses: <unnamed>%3EF4523002CE;cSHVariant { -> F}
//## Uses: <unnamed>%417F64520399;cPtrList { -> }
//## Uses: <unnamed>%4248FFAD01C5;cUnitDef { -> F}

class __DLL_EXPORT__ cVarRef 
{
  //## begin cVarRef%3C7E422F03C0.initialDeclarations preserve=yes
public:
  //## end cVarRef%3C7E422F03C0.initialDeclarations

    //## Constructors (generated)
      cVarRef();

      cVarRef(const cVarRef &right);

    //## Constructors (specified)
      //## Operation: cVarRef%1040202775
      cVarRef (cVarDef *var_def, cContext *context);

    //## Destructor (generated)
      virtual ~cVarRef();


    //## Other Operations (specified)
      //## Operation: VarDef%1061797997
      cVarDef * VarDef ();

      //## Operation: DataType%1061797999
      UCHAR_T DataType ();

      //## Operation: ValueSize%1072120985
      ULONG_T ValueSize ();

      //## Operation: Precision%1089187398
      UCHAR_T Precision ();

      //## Operation: VarType%1100622395
      UCHAR_T VarType ();

      //## Operation: SystemFlags%1141722272
      ULONG_T SystemFlags ();

      //## Operation: Flags%1141722273
      ULONG_T Flags ();

      //## Operation: BackgroundVar%1100678879
      BOOL_T BackgroundVar ();

      //## Operation: GetValue%1072120972
      //	Gets the value of a variable reference a  CHAR_T value.
      void GetValue (CHAR_T &value);

      //## Operation: GetValue%1072120973
      //	Gets the value of a variable reference a U CHAR_T value.
      void GetValue (UCHAR_T &value);

      //## Operation: GetValue%1072120974
      //	Gets the value of a variable reference a  SHORT_T value.
      void GetValue (SHORT_T &value);

      //## Operation: GetValue%1072120975
      //	Gets the value of a variable reference a  USHORT_T value.
      void GetValue (USHORT_T &value);

      //## Operation: GetValue%1040202785
      //	Gets the value of a variable reference a  LONG_T value.
      void GetValue (LONG_T &value);

      //## Operation: GetValue%1072120976
      //	Gets the value of a variable reference a  ULONG_T value.
      void GetValue (ULONG_T &value);

      //## Operation: GetValue%1072120977
      //	Gets the value of a variable reference a FLOAT_T value.
      void GetValue (FLOAT_T &value);

      //## Operation: GetValue%1040202786
      //	Gets the value of a variable reference a  DOUBLE_T value.
      void GetValue (DOUBLE_T &value);

      //## Operation: GetValue%1040202784
      //	Gets the value of a variable reference a  STRING_T value.
      void GetValue (STRING_T &value);

      //## Operation: GetValue%1088693724
      //	Gets the value of a variable reference a  WSTRING_T
      //	value.
      void GetValue (WSTRING_T &value);

      //## Operation: GetValue%1073740507
      //	Gets the value of a variable reference as a pointer
      //	value.
      void GetValue (BUF_T &buf_ptr);

      //## Operation: GetValue%1072120984
      //	Reads the value of a variable reference into a buffer.
      void GetValue (BUF_T buf, ULONG_T len, ULONG_T buf_size);

      //## Operation: SetValue%1072120978
      void SetValue (CHAR_T value);

      //## Operation: SetValue%1072120979
      void SetValue (UCHAR_T value);

      //## Operation: SetValue%1072120980
      void SetValue (SHORT_T value);

      //## Operation: SetValue%1072120981
      void SetValue (USHORT_T value);

      //## Operation: SetValue%1040202788
      void SetValue (LONG_T value);

      //## Operation: SetValue%1072120982
      void SetValue (ULONG_T value);

      //## Operation: SetValue%1072120983
      void SetValue (FLOAT_T value);

      //## Operation: SetValue%1040202789
      void SetValue (DOUBLE_T value);

      //## Operation: SetValue%1040202787
      void SetValue (CONST_STRING_T value);

      //## Operation: SetValue%1088693725
      void SetValue (CONST_WSTRING_T value);

      //## Operation: SetValue%1073929899
      void SetValue (BUF_T buf, ULONG_T len);

      //## Operation: SetValue%1088693726
      void SetValue (BUF_T &buf);

      //## Operation: NewValue%1041261882
      void NewValue (CONST_STRING_T value, ULONG_T time_offset, ULONG_T value_size, ULONG_T data_set);

      //## Operation: NewValue%1073907455
      void NewValue (BUF_T buf, ULONG_T time_offset, ULONG_T value_size, ULONG_T data_set);

      //## Operation: NewValue%1140790764
      void NewValue (ULONG_T dataset);

      //## Operation: SetIndex%1040202776
      void SetIndex (ULONG_T pos, cArgument *index);

      //## Operation: VarName%1135947274
      STRING_T VarName ();

      //## Operation: GetIndices%1041261885
      void GetIndices (LONG_T &i1, LONG_T &i2, LONG_T &i3, LONG_T &i4);

      //## Operation: Indices%1040202777
      ULONG_T Indices ();

      //## Operation: Register%1042646893
      void Register (cDataChangeAdapter *adapter);

      //## Operation: UnRegister%1042646894
      void UnRegister (cDataChangeAdapter *adapter);

      //## Operation: Matches%1042646895
      BOOL_T Matches (cDataChange *change);

      //## Operation: AddControl%1043311227
      void AddControl (cDataControl *control);

      //## Operation: RemoveControl%1109600057
      void RemoveControl (cDataControl *control);

      //## Operation: GetMinimum%1089103295
      //	Gets the minimum value of a variable reference.
      void GetMinimum (LONG_T &minimum);

      //## Operation: GetMinimum%1089103296
      //	Gets the minimum value of a variable reference.
      void GetMinimum (ULONG_T &minimum);

      //## Operation: GetMinimum%1089103297
      //	Gets the minimum value of a variable reference.
      void GetMinimum (FLOAT_T &minimum);

      //## Operation: GetMinimum%1089103298
      //	Gets the minimum value of a variable reference.
      void GetMinimum (DOUBLE_T &minimum);

      //## Operation: GetMinimum%1089203188
      //	Gets the minimum value of a variable reference.
      void GetMinimum (STRING_T &minimum);

      //## Operation: GetMaximum%1089103299
      //	Gets the maximum value of a variable reference.
      void GetMaximum (LONG_T &maximum);

      //## Operation: GetMaximum%1089103300
      //	Gets the maximum value of a variable reference.
      void GetMaximum (ULONG_T &maximum);

      //## Operation: GetMaximum%1089103301
      //	Gets the maximum value of a variable reference.
      void GetMaximum (FLOAT_T &maximum);

      //## Operation: GetMaximum%1089103302
      //	Gets the maximum value of a variable reference.
      void GetMaximum (DOUBLE_T &maximum);

      //## Operation: GetMaximum%1089203189
      //	Gets the maximum value of a variable reference.
      void GetMaximum (STRING_T &maximum);

      //## Operation: Refresh%1098867705
      virtual void Refresh ();

      //## Operation: IsBackgroundSensitive%1138360004
      BOOL_T IsBackgroundSensitive ();

      //## Operation: GetObject%1238436636
      //	Reads the value of a variable reference iin binary
      //	representation.
      ULONG_T GetObject (cBinaryObject &object);

      //## Operation: SetObject%1238436637
      //	Writes the value of a variable reference iin binary
      //	representation.
      void SetObject (const cBinaryObject &object);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Cached%4215C68B001F
      BOOL_T get_Cached () const;
      void set_Cached (BOOL_T value);

      //## Attribute: Flags%43FDF5BB009D
      ULONG_T get_Flags () const;
      void set_Flags (ULONG_T value);

    // Data Members for Class Attributes

      //## Attribute: Name%3E00463402F0
      //## begin cVarRef::Name%3E00463402F0.attr preserve=no  public: STRING_T {U} 
      STRING_T _Name;
      //## end cVarRef::Name%3E00463402F0.attr

      //## Attribute: Spec%40229C6E01C5
      //## begin cVarRef::Spec%40229C6E01C5.attr preserve=no  public: STRING_T {U} 
      STRING_T _Spec;
      //## end cVarRef::Spec%40229C6E01C5.attr

      //## Attribute: VarId%3E106CCD0302
      //## begin cVarRef::VarId%3E106CCD0302.attr preserve=no  public: LONG_T {U} -1
      LONG_T _VarId;
      //## end cVarRef::VarId%3E106CCD0302.attr

    // Data Members for Associations

      //## Association: System::Database::<unnamed>%3E073656011E
      //## Role: cVarRef::Variable%3E073659021D
      //## begin cVarRef::Variable%3E073659021D.role preserve=no  public: cVariable { -> 1RFHN}
      cVariable *_Variable;
      //## end cVarRef::Variable%3E073659021D.role

      //## Association: System::Database::<unnamed>%3E25959F01C5
      //## Role: cVarRef::Context%3E2595A00221
      //## begin cVarRef::Context%3E2595A00221.role preserve=no  public: cContext { -> 1RFHN}
      cContext *_Context;
      //## end cVarRef::Context%3E2595A00221.role

  public:
    // Additional Public Declarations
      //## begin cVarRef%3C7E422F03C0.public preserve=yes
      //## end cVarRef%3C7E422F03C0.public

  protected:
    // Data Members for Class Attributes

      //## begin cVarRef::Cached%4215C68B001F.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _Cached;
      //## end cVarRef::Cached%4215C68B001F.attr

      //## begin cVarRef::Flags%43FDF5BB009D.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Flags;
      //## end cVarRef::Flags%43FDF5BB009D.attr

    // Data Members for Associations

      //## Association: System::Database::<unnamed>%3F3A2FD60203
      //## Role: cVarRef::VarDef%3F3A2FD802BF
      //## begin cVarRef::VarDef%3F3A2FD802BF.role preserve=no  public: cVarDef { -> 1RFHN}
      cVarDef *_VarDef;
      //## end cVarRef::VarDef%3F3A2FD802BF.role

      //## Association: System::Comm::<unnamed>%3D07768D01D7
      //## Role: cVarRef::Control%3D07768E0297
      //## begin cVarRef::Control%3D07768E0297.role preserve=no  public: cDataControl {1 -> 1RFHN}
      cDataControl *_Control;
      //## end cVarRef::Control%3D07768E0297.role

    // Additional Protected Declarations
      //## begin cVarRef%3C7E422F03C0.protected preserve=yes
      //## end cVarRef%3C7E422F03C0.protected

  private:
    // Additional Private Declarations
      //## begin cVarRef%3C7E422F03C0.private preserve=yes
      //## end cVarRef%3C7E422F03C0.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: ControlList%417F642D01C5
      //## begin cVarRef::ControlList%417F642D01C5.attr preserve=no  protected: cPtrList * {U} NULL
      cPtrList *_ControlList;
      //## end cVarRef::ControlList%417F642D01C5.attr

      //## Attribute: IndexVec%3E00466F002E
      //## begin cVarRef::IndexVec%3E00466F002E.attr preserve=no  implementation: ARG_VECTOR_T {U} 
      ARG_VECTOR_T _IndexVec;
      //## end cVarRef::IndexVec%3E00466F002E.attr

    // Additional Implementation Declarations
      //## begin cVarRef%3C7E422F03C0.implementation preserve=yes
      //## end cVarRef%3C7E422F03C0.implementation

};

//## begin cVarRef%3C7E422F03C0.postscript preserve=yes
//## end cVarRef%3C7E422F03C0.postscript

// Class cVarRef 

//## begin module%3C7E422F03C0.epilog preserve=yes
//## end module%3C7E422F03C0.epilog


#endif
