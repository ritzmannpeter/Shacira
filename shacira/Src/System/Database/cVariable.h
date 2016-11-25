//## begin module%3C6A7BFD0121.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C6A7BFD0121.cm

//## begin module%3C6A7BFD0121.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C6A7BFD0121.cp

//## Module: cVariable%3C6A7BFD0121; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Database\cVariable.h

#ifndef cVariable_h
#define cVariable_h 1

//## begin module%3C6A7BFD0121.includes preserve=yes
//## end module%3C6A7BFD0121.includes

// cLocalContext
#include "Control/LocalDatabase/cLocalContext.h"

class __DLL_EXPORT__ cDataChange;
class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cUnitDef;
class __DLL_EXPORT__ cPersistenceChannel;

//## begin module%3C6A7BFD0121.additionalDeclarations preserve=yes

#define MAX_DIMENSIONS  4
typedef ULONG_T DIMSIZE_ARRAY_T[MAX_DIMENSIONS];
enum Flags {Header=0x00000001};

class cVariableControl
{
public:
   cVariableControl() {};
   virtual ~cVariableControl() {};
   virtual BOOL_T TargetParameterChange(cContext * file_context, cLocalContext * target_context,
                                        CONST_STRING_T unit_def_name,
                                        CONST_STRING_T var_name, int i1, int i2, int i3, int i4)
   {
      /// this method returns true if parameters concerning the
      /// specific unit differ in file and target, false otherwise
      return true;
   };
};

//## end module%3C6A7BFD0121.additionalDeclarations


//## begin cVariable%3C6A7BFD0121.preface preserve=yes
//## end cVariable%3C6A7BFD0121.preface

//## Class: cVariable%3C6A7BFD0121
//	This class realizes CCS variable access. The class is an
//	abstract base class and cannot be instantiated. The
//	object factory for variables is an object of type c
//	Context.
//## Category: System::Database%3E0030DC0267
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3CFE3367010A;cDataChange { -> F}
//## Uses: <unnamed>%3E0749D903D4;cContext { -> F}
//## Uses: <unnamed>%3EDDE1FD029F;cLocalContext { -> }
//## Uses: <unnamed>%423F1DBE0128;cUnitDef { -> F}

class __DLL_EXPORT__ cVariable 
{
  //## begin cVariable%3C6A7BFD0121.initialDeclarations preserve=yes
public:
  //## end cVariable%3C6A7BFD0121.initialDeclarations

    //## Constructors (generated)
      cVariable();

      cVariable(const cVariable &right);

    //## Constructors (specified)
      //## Operation: cVariable%1015079155
      cVariable (cVarDef *var_def);

    //## Destructor (generated)
      virtual ~cVariable();


    //## Other Operations (specified)
      //## Operation: VarName%1077542661
      //	Returns the variable name of a variable.
      STRING_T VarName ();

      //## Operation: DataType%1077542654
      //	Returns the data type of the elements of a  variable.
      UCHAR_T DataType ();

      //## Operation: VarType%1077542656
      //	Returns the variable type of a variable.
      UCHAR_T VarType ();

      //## Operation: PersistenceType%1077542655
      //	Returns the persistence type of a variable.
      UCHAR_T PersistenceType ();

      //## Operation: Precision%1087412991
      //	Returns the precision specification of the elements of a
      //	variable.
      UCHAR_T Precision ();

      //## Operation: FileName%1077542657
      //	Returns the file name of a sub file where the variable
      //	values are stored under when saved to a file.
      STRING_T FileName ();

      //## Operation: Dims%1077542660
      //	Returns the number of dimensions of a variable.
      ULONG_T Dims ();

      //## Operation: DimSize%1077539621
      //	Returns the size of dimension dim.
      ULONG_T DimSize (ULONG_T dim);

      //## Operation: ValueSize%1077542658
      //	returns the size of one varaible element (value) of the
      //	variable.
      ULONG_T ValueSize ();

      //## Operation: Elements%1077542659
      //	Return the number of elements (values) a variable
      //	contains.
      ULONG_T Elements ();

      //## Operation: DeviceName%1079186865
      //	Returns the name of the device the variable is mapped to.
      STRING_T DeviceName ();

      //## Operation: DatabaseName%1092050721
      //	Returns the database name of the database that contains
      //	the variable.
      STRING_T DatabaseName ();

      //## Operation: UnitText%1111426861
      //	Returns the string that contains the current physical
      //	dimension of a variable.
      virtual STRING_T UnitText (CHAR_T state = -1);

      //## Operation: Get%1071244110
      //	The class cVariable offers this getter method to
      //	retrieve variable values. The getter method is abstract
      //	and appears in different forms to retrieve different
      //	value types. Every derived class must overload these
      //	getter methods.
      virtual void Get (CHAR_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Get%1071244111
      virtual void Get (UCHAR_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Get%1071244112
      virtual void Get (SHORT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Get%1071244113
      virtual void Get (USHORT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Get%1071244114
      virtual void Get (LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Get%1071244115
      virtual void Get (ULONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Get%1071244116
      //	.
      virtual void Get (FLOAT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Get%1071244117
      virtual void Get (DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Get%1071244118
      virtual void Get (STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Get%1071244119
      virtual void Get (WSTRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Get%1071244120
      virtual void Get (BUF_T &buf, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;
      virtual void Get (BUF_T &buf, ULONG_T & size, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Get%1071244121
      virtual void Get (BUF_T buf, ULONG_T len, ULONG_T buf_size, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Refresh%1092218360
      virtual void Refresh (LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244122
      //	The class cVariable offers this setter method to set
      //	variable values. The setter method is abstract and
      //	appears in different forms to set different value types.
      //	Every derived class must overload these setter methods.
      virtual void Set (CHAR_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Set%1071244123
      virtual void Set (UCHAR_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Set%1071244124
      virtual void Set (SHORT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Set%1071244125
      virtual void Set (USHORT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Set%1071244126
      virtual void Set (LONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Set%1071244127
      virtual void Set (ULONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Set%1071244128
      virtual void Set (FLOAT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Set%1071244129
      virtual void Set (DOUBLE_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Set%1071244130
      virtual void Set (CONST_STRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Set%1071244131
      virtual void Set (CONST_WSTRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Set%1071244132
      virtual void Set (CONST_BUF_T buf, ULONG_T len, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: GetMinimum%1089103303
      //	Retrieves a minimum for the variable value of a specific
      //	element of the variable. The element is denoted by a
      //	quadrupel of indices. Comparable to the getter and
      //	setter methods there are a couple of GetMinimum methods
      //	to deal with different data types.
      virtual void GetMinimum (LONG_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true) = 0;

      //## Operation: GetMinimum%1089103304
      virtual void GetMinimum (ULONG_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true) = 0;

      //## Operation: GetMinimum%1089103305
      virtual void GetMinimum (FLOAT_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) = 0;

      //## Operation: GetMinimum%1089103306
      virtual void GetMinimum (DOUBLE_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) = 0;

      //## Operation: GetMinimum%1089203192
      virtual void GetMinimum (STRING_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) = 0;

      //## Operation: GetMaximum%1089103307
      //	Retrieves a maximum for the variable value of a specific
      //	element of the variable. The element is denoted by a
      //	quadrupel of indices. Comparable to the getter and
      //	setter methods there are a couple of GetMaximum methods
      //	to deal with different data types.
      virtual void GetMaximum (LONG_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true) = 0;

      //## Operation: GetMaximum%1089103308
      virtual void GetMaximum (ULONG_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true) = 0;

      //## Operation: GetMaximum%1089103309
      virtual void GetMaximum (FLOAT_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) = 0;

      //## Operation: GetMaximum%1089103310
      virtual void GetMaximum (DOUBLE_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) = 0;

      //## Operation: GetMaximum%1089203193
      virtual void GetMaximum (STRING_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) = 0;

      //## Operation: Copy%1091957521
      //	This method copies all values of a variable to a second
      //	variable dst_variable. The copy operation applies
      //	structural and type transformations if necessary and
      //	applicable.
      virtual void Copy (cVariable *dst_variable, BOOL_T show_errors=true);

      //## Operation: CopyCommand%1100714613
      virtual void CopyCommand (ULONG_T src, ULONG_T dst, BOOL_T exchange);

      //## Operation: SetFlags%1102166610
      void SetFlags (ULONG_T flags);

      //## Operation: GetFlags%1102166611
      ULONG_T GetFlags ();

      //## Operation: SetFlag%1102166612
      BOOL_T SetFlag (ULONG_T flag_pos, BOOL_T state);

      //## Operation: GetFlag%1102166613
      BOOL_T GetFlag (ULONG_T flag_pos);

      //## Operation: IsBackgroundSensitive%1138360003
      virtual BOOL_T IsBackgroundSensitive ();

      //## Operation: SetVariableControl%1191857021
      static void SetVariableControl (cVariableControl *variable_control);

      //## Operation: CopyUnitSensitive%1191857022
      BOOL_T CopyUnitSensitive (CONST_STRING_T spec, cLocalVariable *dst_variable);

      //## Operation: ResetShadowBuffer%1191857023
      virtual void ResetShadowBuffer ();

      //## Operation: GetObject%1238436638
      virtual ULONG_T GetObject (cBinaryObject &object, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: SetObject%1238436639
      virtual void SetObject (const cBinaryObject &object, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: VarId%3D085CD7007A
      LONG_T get_VarId () const;
      void set_VarId (LONG_T value);

    // Data Members for Associations

      //## Association: System::Database::<unnamed>%3E0032500226
      //## Role: cVariable::VarDef%3E003251008D
      //## begin cVariable::VarDef%3E003251008D.role preserve=no  public: cVarDef {1 -> 1RFHN}
      cVarDef *_VarDef;
      //## end cVariable::VarDef%3E003251008D.role

  public:
    // Additional Public Declarations
      //## begin cVariable%3C6A7BFD0121.public preserve=yes
      //## end cVariable%3C6A7BFD0121.public

  protected:
    // Data Members for Class Attributes

      //## begin cVariable::VarId%3D085CD7007A.attr preserve=no  public: LONG_T {U} -1
      LONG_T _VarId;
      //## end cVariable::VarId%3D085CD7007A.attr

      //## Attribute: Flags%41B1B9C70203
      //## begin cVariable::Flags%41B1B9C70203.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _Flags;
      //## end cVariable::Flags%41B1B9C70203.attr

      //## Attribute: VariableControl%470A5FBB01BE
      //## begin cVariable::VariableControl%470A5FBB01BE.attr preserve=no  protected: static cVariableControl * {U} NULL
      static cVariableControl *_VariableControl;
      //## end cVariable::VariableControl%470A5FBB01BE.attr

    // Data Members for Associations

      //## Association: System::Database::<unnamed>%42E636230232
      //## Role: cVariable::PersistenceChannel%42E636240138
      //## begin cVariable::PersistenceChannel%42E636240138.role preserve=no  public: cPersistenceChannel { -> 0..1RFHN}
      cPersistenceChannel *_PersistenceChannel;
      //## end cVariable::PersistenceChannel%42E636240138.role

    // Additional Protected Declarations
      //## begin cVariable%3C6A7BFD0121.protected preserve=yes
      //## end cVariable%3C6A7BFD0121.protected

  private:
    // Additional Private Declarations
      //## begin cVariable%3C6A7BFD0121.private preserve=yes
      //## end cVariable%3C6A7BFD0121.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cVariable%3C6A7BFD0121.implementation preserve=yes
      //## end cVariable%3C6A7BFD0121.implementation
};

//## begin cVariable%3C6A7BFD0121.postscript preserve=yes
//## end cVariable%3C6A7BFD0121.postscript

// Class cVariable 

//## begin module%3C6A7BFD0121.epilog preserve=yes
//## end module%3C6A7BFD0121.epilog


#endif
