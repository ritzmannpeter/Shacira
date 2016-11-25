//## begin module%3E0038B30046.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3E0038B30046.cm

//## begin module%3E0038B30046.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3E0038B30046.cp

//## Module: cLocalVariable%3E0038B30046; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cLocalVariable.h

#ifndef cLocalVariable_h
#define cLocalVariable_h 1

//## begin module%3E0038B30046.includes preserve=yes
//## end module%3E0038B30046.includes

// cVariable
#include "System/Database/cVariable.h"
// cSHVariant
#include "System/Database/cSHVariant.h"

class __DLL_EXPORT__ cIniFile;
class __DLL_EXPORT__ cUserInfo;
class __DLL_EXPORT__ cDataChange;
class __DLL_EXPORT__ cBlockBuffer;
class __DLL_EXPORT__ cVarDef;
class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cMapping;
class __DLL_EXPORT__ cFuncRef;
class __DLL_EXPORT__ cArgument;
class __DLL_EXPORT__ cUnitDef;
class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cValueBuffer;
class __DLL_EXPORT__ cPersistenceChannel;
class __DLL_EXPORT__ cDevice;

//## begin module%3E0038B30046.additionalDeclarations preserve=yes

#define MAX_DATASETS    3
#define FOREGROUND_DATASET    0
#define BACKGROUND_DATASET    1
#define SHADOW_DATASET        2

// comparison flags
#define CF_COMPARE_TO_SHADOW        0x00000001

// copy flags
#define CP_FLAG_SUPPRESS_PROGRESS            0x00000001
#define CP_FLAG_NOTCHANGE_DEVBUFFERED_STATE  0x00000002

typedef cValueBuffer * VALUEBUF_ARRAY_T[MAX_DATASETS];
typedef CHAR_T * INPUTSTATE_ARRAY_T[MAX_DATASETS];

typedef struct element_ref {
   cLocalVariable * variable;
   LONG_T i1;
   LONG_T i2;
   LONG_T i3;
   LONG_T i4;
}  ELEMENT_REF_T;

//## end module%3E0038B30046.additionalDeclarations


//## begin cLocalVariable%3E0038B30046.preface preserve=yes
//## end cLocalVariable%3E0038B30046.preface

//## Class: cLocalVariable%3E0038B30046
//	The cLocalVariable class realizes the cVariable
//	intercae, Local variables have resources like memory to
//	store values. They live within a local context that is
//	embedded in a cell object.
//## Category: Control::LocalDatabase%3DFF1FB100C4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E2435F30061;cVarDef { -> F}
//## Uses: <unnamed>%3E245D0D03A4;cMapping { -> F}
//## Uses: <unnamed>%3E25556C02C7;cDataChange { -> F}
//## Uses: <unnamed>%3FDB094F034B;cDevice { -> F}
//## Uses: <unnamed>%400FE9B30222;cFuncRef { -> F}
//## Uses: <unnamed>%40360C870186;cFileSystemUtils { -> F}
//## Uses: <unnamed>%40E6BC93035B;cBlockBuffer { -> F}
//## Uses: <unnamed>%40EA909B02DE;cArgument { -> F}
//## Uses: <unnamed>%419A2A2900CB;cValueBuffer { -> F}
//## Uses: <unnamed>%419A2F7B0109;cUserInfo { -> F}
//## Uses: <unnamed>%4225FD6802EE;cUnitDef { -> F}
//## Uses: <unnamed>%42E638A702BF;cPersistenceChannel { -> F}
//## Uses: <unnamed>%43C2205700AC;cSHVariant { -> }

class __DLL_EXPORT__ cLocalVariable : public cVariable  //## Inherits: <unnamed>%3E0038E80223
{
  //## begin cLocalVariable%3E0038B30046.initialDeclarations preserve=yes
public:
  //## end cLocalVariable%3E0038B30046.initialDeclarations

    //## Constructors (generated)
      cLocalVariable();

      cLocalVariable(const cLocalVariable &right);

    //## Constructors (specified)
      //## Operation: cLocalVariable%1040202755
      cLocalVariable (cVarDef *var_def);

    //## Destructor (generated)
      virtual ~cLocalVariable();


    //## Other Operations (specified)
      //## Operation: UnitText%1111426625
      //	Returns the string that contains the current physical
      //	dimension of a variable.
      virtual STRING_T UnitText (CHAR_T state = -1);

      //## Operation: Get%1071244159
      virtual void Get (CHAR_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244160
      virtual void Get (UCHAR_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244161
      virtual void Get (SHORT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244162
      virtual void Get (USHORT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244163
      virtual void Get (LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244164
      virtual void Get (ULONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244165
      virtual void Get (FLOAT_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244166
      virtual void Get (DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244167
      virtual void Get (STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244168
      virtual void Get (WSTRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1071244169
      virtual void Get (BUF_T &buf, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);
      virtual void Get (BUF_T &buf, ULONG_T & size, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Get%1077626056
      virtual void Get (BUF_T buf, ULONG_T len, ULONG_T buf_size, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Refresh%1092218361
      virtual void Refresh (LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244171
      virtual void Set (CHAR_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244172
      virtual void Set (UCHAR_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244173
      virtual void Set (SHORT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244174
      virtual void Set (USHORT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244175
      virtual void Set (LONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244176
      virtual void Set (ULONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244177
      virtual void Set (FLOAT_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244178
      virtual void Set (DOUBLE_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244179
      virtual void Set (CONST_STRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1071244180
      virtual void Set (CONST_WSTRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Set%1077626057
      virtual void Set (CONST_BUF_T buf, ULONG_T len, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      // change variable mapping at position
      MAP_ITEM_T * MapItem(LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) const;
      BOOL_T MappingEnabled(LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);
      BOOL_T EnableMapping(ULONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);
      BOOL_T EnableCompleteMapping(ULONG_T value);

      //## Operation: GetMinimum%1089103312
      //	Gets the minimum value of a variable.
      virtual void GetMinimum (ULONG_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMinimum%1089103311
      //	Gets the minimum value of a variable.
      virtual void GetMinimum (LONG_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMinimum%1089103313
      //	Gets the minimum value of a variable.
      virtual void GetMinimum (FLOAT_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1089103314
      //	Gets the minimum value of a variable.
      virtual void GetMinimum (DOUBLE_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1089203186
      //	Gets the minimum value of a variable.
      virtual void GetMinimum (STRING_T &minimum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103315
      //	Gets the maximum value of a variable.
      virtual void GetMaximum (LONG_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMaximum%1089103316
      //	Gets the maximum value of a variable.
      virtual void GetMaximum (ULONG_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMaximum%1089103317
      //	Gets the maximum value of a variable.
      virtual void GetMaximum (FLOAT_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103318
      //	Gets the maximum value of a variable.
      virtual void GetMaximum (DOUBLE_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089203187
      //	Gets the maximum value of a variable.
      virtual void GetMaximum (STRING_T &maximum, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: IsBackgroundSensitive%1138360005
      virtual BOOL_T IsBackgroundSensitive ();

      //## Operation: Save%1071741889
      //	"Saves" the value of a variable element. This method
      //	applies to local variables that are mapped to a device.
      //	In this case the element value is read from the device
      //	(saved) and the element value is updated. The element of
      //	the variable is specified by an index quadrupel supplied
      //	to the method.
      void Save (LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SaveVariable%1084445991
      //	SaveVariable "saves" all elements of a local variable.
      void SaveVariable (ULONG_T flags = 0);

      //## Operation: Load%1071741890
      //	"Loads" the value of a variable element. This method
      //	applies to local variables that are mapped to a device.
      //	In this case the element value is written to  the device
      //	(loaded)  The element of the variable is specified by an
      //	index quadrupel supplied to the method.
      void Load (LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: LoadVariable%1084445992
      //	LoadVariable "loads" all elements of a local variable.
      void LoadVariable (ULONG_T flags = 0);

      //## Operation: GetBuf%1077613262
      //	Returns the start of the internal buffer where the
      //	values of local variables are stored.
      BUF_T GetBuf ();

      //## Operation: GetBufSize%1077613263
      //	Returns the size of the internal buffer where the
      //	variable values are stored.
      ULONG_T GetBufSize ();

      //## Operation: CopyCommand%1100714614
      virtual void CopyCommand (ULONG_T src, ULONG_T dst, BOOL_T exchange, ULONG_T copy_flags = 0);

      //## Operation: Compare%1108566003
      //	LoadVariable "loads" all elements of a local variable.
      BOOL_T Compare (STRING_T &result, ULONG_T flags);

      //## Operation: Set%1191857007
      void SetUnitSensitive (DOUBLE_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags, UCHAR_T state, BOOL_T suppress_data_change);

      //## Operation: GetRaw%1191857008
      void GetRaw (UCHAR_T &state, STRING_T &value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

      //## Operation: SetUnitCode%1191857009
      void SetUnitCode (ULONG_T pos, UCHAR_T value);

      //## Operation: UnitCode%1191857010
      UCHAR_T UnitCode (ULONG_T pos);

      //## Operation: EmitChanges%1191857011
      void EmitChanges ();

      //## Operation: ResetShadowBuffer%1191857012
      virtual void ResetShadowBuffer ();

      //## Operation: GetBuf%1191857013
      //	Returns the start of the internal buffer where the
      //	values of local variables are stored.
      BUF_T GetBuf (ULONG_T dataset);

      //## Operation: SetUnitCode%1191857014
      void SetUnitCode (ULONG_T pos, UCHAR_T value, ULONG_T dataset);

      //## Operation: UnitCode%1191857015
      UCHAR_T UnitCode (ULONG_T pos, ULONG_T dataset);

      //## Operation: CheckShadowDataset%1191857016
      void CheckShadowDataset (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Initialized%43D9C4610140
      BOOL_T get_Initialized () const;
      void set_Initialized (BOOL_T value);

    // Data Members for Class Attributes

      //## Attribute: VariableMutex%42DCB6480157
      //## begin cLocalVariable::VariableMutex%42DCB6480157.attr preserve=no  protected: cMutexSem {U} 
      cMutexSem _VariableMutex;
      //## end cLocalVariable::VariableMutex%42DCB6480157.attr

  public:
    // Additional Public Declarations
      //## begin cLocalVariable%3E0038B30046.public preserve=yes
      void Test(int param);
      //## end cLocalVariable%3E0038B30046.public

  protected:

    //## Other Operations (specified)
      //## Operation: DataChanged%1040202762
      //	The DataChanged method is called when a specific element
      //	of a local variable changes his value. This methods
      //	emits a data change event throughout the system. This
      //	specific form is called for numeric and string typed
      //	variables.
      void DataChanged (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags = 0);

      //## Operation: DataChanged%1128418515
      //	The DataChanged method is called when a specific element
      //	of a local variable changes his value. This methods
      //	emits a data change event throughout the system. This
      //	specific form is called for numeric and string typed
      //	variables.
      void DataChanged (CONST_STRING_T old_value, CONST_STRING_T new_value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags = 0);

      //## Operation: BufChanged%1073929900
      //	The BufChanged method is called when a specific element
      //	of a local variable changes his value. This methods
      //	emits a data change event throughout the system. This
      //	specific form is called for byte and object typed
      //	variables.
      void BufChanged (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags = 0);

    // Data Members for Class Attributes

      //## begin cLocalVariable::Initialized%43D9C4610140.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _Initialized;
      //## end cLocalVariable::Initialized%43D9C4610140.attr

    // Data Members for Associations

      //## Association: System::Database::<unnamed>%3FDA1036004E
      //## Role: cLocalVariable::Accu%3FDA103603B9
      //## begin cLocalVariable::Accu%3FDA103603B9.role preserve=no  public: cSHVariant { -> 1RFHN}
      cSHVariant *_Accu;
      //## end cLocalVariable::Accu%3FDA103603B9.role

      //## Association: Control::LocalDatabase::<unnamed>%403611770186
      //## Role: cLocalVariable::IniFile%4036117800FA
      //## begin cLocalVariable::IniFile%4036117800FA.role preserve=no  public: cIniFile { -> 1RFHN}
      cIniFile *_IniFile;
      //## end cLocalVariable::IniFile%4036117800FA.role

      //## Association: Control::LocalDatabase::<unnamed>%42E637450109
      //## Role: cLocalVariable::Context%42E637460196
      //## begin cLocalVariable::Context%42E637460196.role preserve=no  public: cContext { -> 0..1RFHN}
      cContext *_Context;
      //## end cLocalVariable::Context%42E637460196.role

    // Additional Protected Declarations
      //## begin cLocalVariable%3E0038B30046.protected preserve=yes
      //## end cLocalVariable%3E0038B30046.protected

  private:
    // Additional Private Declarations
      //## begin cLocalVariable%3E0038B30046.private preserve=yes
      //## end cLocalVariable%3E0038B30046.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: GetBuffer%1042559816
      //	This method reads data from the mapped device and stores
      //	this data in the accu of the local variable.
      void GetBuffer (ULONG_T pos, ULONG_T len = 0);

      //## Operation: GetBuffer%1136794166
      void GetBuffer (ULONG_T pos, BUF_T &buf);

      //## Operation: SetBuffer%1042559817
      //	This method writes data from the accu of the local
      //	variable to the mapped device.
      BOOL_T SetBuffer (ULONG_T pos, ULONG_T len = 0);

      //## Operation: FormatOut%1042559822
      void FormatOut (DOUBLE_T &value, ULONG_T pos, ULONG_T flags = 0);

      //## Operation: FormatOut%1071244306
      void FormatOut (FLOAT_T &value, ULONG_T pos, ULONG_T flags = 0);

      //## Operation: FormatOut%1042559821
      void FormatOut (LONG_T &value, ULONG_T pos, ULONG_T flags = 0);

      //## Operation: FormatOut%1042559820
      void FormatOut (STRING_T &value, ULONG_T pos, ULONG_T flags = 0);

      //## Operation: FormatOut%1071244307
      void FormatOut (WSTRING_T &value, ULONG_T pos, ULONG_T flags = 0);

      //## Operation: FormatIn%1042559823
      void FormatIn (STRING_T &value, ULONG_T pos, ULONG_T flags = 0);

      //## Operation: FormatIn%1042559824
      void FormatIn (LONG_T &value, ULONG_T pos, ULONG_T flags = 0);

      //## Operation: FormatIn%1121085449
      void FormatIn (FLOAT_T &value, ULONG_T pos, ULONG_T flags = 0);

      //## Operation: FormatIn%1042559825
      void FormatIn (DOUBLE_T &value, ULONG_T pos, ULONG_T flags = 0);

      //## Operation: FormatIn%1071244308
      void FormatIn (WSTRING_T &value, ULONG_T pos, ULONG_T flags = 0);

      //## Operation: ReadConversion%1051713135
      void ReadConversion (ULONG_T pos, ULONG_T flags);

      //## Operation: WriteConversion%1071498211
      void WriteConversion (ULONG_T pos, ULONG_T flags);

      //## Operation: ReadFilter%1074783623
      BOOL_T ReadFilter (ULONG_T pos, ULONG_T flags, ULONG_T * size = 0);

      //## Operation: WriteFilter%1074783624
      BOOL_T WriteFilter (ULONG_T pos, ULONG_T flags, ULONG_T * size = 0);

      //## Operation: GetDevice%1071317836
      void GetDevice (ULONG_T pos, ULONG_T flags = 0);

      //## Operation: GetDevice%1075382074
      void GetDevice (cDevice *device, CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T data_type, ULONG_T size, ULONG_T flags = 0);

      //## Operation: GetDevice%1075382076
      void GetDevice (cDevice *device, CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T data_type, ULONG_T size, ULONG_T flags = 0);

      //## Operation: GetDevice%1075382075
      void GetDevice (cDevice *device, CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T data_type, UCHAR_T bit_pos_b, UCHAR_T bit_pos_e, ULONG_T flags = 0);

      //## Operation: GetDevice%1075382077
      void GetDevice (cDevice *device, CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T data_type, UCHAR_T bit_pos_b, UCHAR_T bit_pos_e, ULONG_T flags = 0);

      //## Operation: SetDevice%1071317837
      BOOL_T SetDevice (ULONG_T pos, ULONG_T flags = 0);

      //## Operation: SetDevice%1075491276
      BOOL_T SetDevice (ULONG_T pos, cDevice *device, CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T data_type, ULONG_T size, ULONG_T flags = 0);

      //## Operation: SetDevice%1075491277
      BOOL_T SetDevice (ULONG_T pos, cDevice *device, CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T data_type, ULONG_T size, ULONG_T flags = 0);

      //## Operation: SetDevice%1075491278
      BOOL_T SetDevice (ULONG_T pos, cDevice *device, CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T data_type, UCHAR_T bit_pos_b, UCHAR_T bit_pos_e, ULONG_T flags = 0);

      //## Operation: SetDevice%1075491279
      BOOL_T SetDevice (ULONG_T pos, cDevice *device, CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T data_type, UCHAR_T bit_pos_b, UCHAR_T bit_pos_e, ULONG_T flags = 0);

      //## Operation: GetMemoryType%1092208311
      //	This method filters string based get access to memory
      //	type variables.
      BOOL_T GetMemoryType (STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetMemoryType%1092208312
      //	This method filters string based set access to memory
      //	type variables.
      BOOL_T SetMemoryType (CONST_STRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetInput%1111256533
      void SetInput (ULONG_T pos, ULONG_T flags);

      //## Operation: SetInputState%1111243134
      void SetInputState (ULONG_T pos, CHAR_T value);

      //## Operation: GetInputState%1111243135
      UCHAR_T GetInputState (ULONG_T pos);

      //## Operation: HandleUnit%1111243132
      void HandleUnit (STRING_T &value, ULONG_T pos, ULONG_T flags);

      //## Operation: HandleUnit%1111256534
      void HandleUnit (FLOAT_T &value, ULONG_T pos, ULONG_T flags);

      //## Operation: HandleUnit%1111388587
      void HandleUnit (DOUBLE_T &value, ULONG_T pos, ULONG_T flags);

      //## Operation: ConvertToNative%1111388586
      void ConvertToNative (cUnitDef *unit_def, FLOAT_T &value, UCHAR_T source, ULONG_T pos);

      //## Operation: ConvertToNative%1126246271
      void ConvertToNative (cUnitDef *unit_def, DOUBLE_T &value, UCHAR_T source, ULONG_T pos);

      //## Operation: ConvertToDevice%1111426863
      void ConvertToDevice (cUnitDef *unit_def, FLOAT_T &value, UCHAR_T source, ULONG_T pos);

      //## Operation: ConvertToDevice%1126246272
      void ConvertToDevice (cUnitDef *unit_def, DOUBLE_T &value, UCHAR_T source, ULONG_T pos);

      //## Operation: ConvertToDataset%1111388584
      void ConvertToDataset (cUnitDef *unit_def, FLOAT_T &value, UCHAR_T source, ULONG_T pos);

      //## Operation: ConvertToDataset%1126246273
      void ConvertToDataset (cUnitDef *unit_def, DOUBLE_T &value, UCHAR_T source, ULONG_T pos);

      //## Operation: ConvertToState%1111388585
      void ConvertToState (cUnitDef *unit_def, FLOAT_T &value, UCHAR_T source, ULONG_T pos);

      //## Operation: ConvertToState%1126246274
      void ConvertToState (cUnitDef *unit_def, DOUBLE_T &value, UCHAR_T source, ULONG_T pos);

      //## Operation: ReadAccessFilter%1133185466
      BOOL_T ReadAccessFilter (ULONG_T pos, ULONG_T flags);

      //## Operation: WriteAccessFilter%1133185467
      BOOL_T WriteAccessFilter (ULONG_T pos, ULONG_T flags);

      //## Operation: Break%1191857017
      void Break (LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: FormatOut%1191857018
      void FormatOut (STRING_T &value, UCHAR_T precision);

      //## Operation: ReadFilter%1191857019
      BOOL_T ReadFilter (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags, ULONG_T * size = 0);

      //## Operation: WriteFilter%1191857020
      BOOL_T WriteFilter (LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags, ULONG_T * size = 0);

    // Data Members for Class Attributes

      //## Attribute: FilterFuncRef%400FE80E0261
      //## begin cLocalVariable::FilterFuncRef%400FE80E0261.attr preserve=no  implementation: cFuncRef * {U} NULL
      cFuncRef *_FilterFuncRef;
      //## end cLocalVariable::FilterFuncRef%400FE80E0261.attr

      //## Attribute: ConvFuncRef%40A3551402BF
      //## begin cLocalVariable::ConvFuncRef%40A3551402BF.attr preserve=no  implementation: cFuncRef * {U} NULL
      cFuncRef *_ConvFuncRef;
      //## end cLocalVariable::ConvFuncRef%40A3551402BF.attr

      //## Attribute: AccessFuncRef%438B0B300356
      //## begin cLocalVariable::AccessFuncRef%438B0B300356.attr preserve=no  implementation: cFuncRef * {U} NULL
      cFuncRef *_AccessFuncRef;
      //## end cLocalVariable::AccessFuncRef%438B0B300356.attr

      //## Attribute: MinArg%40EA8D830119
      //## begin cLocalVariable::MinArg%40EA8D830119.attr preserve=no  implementation: cArgument * {U} NULL
      cArgument *_MinArg;
      //## end cLocalVariable::MinArg%40EA8D830119.attr

      //## Attribute: MaxArg%40EA8DA0035B
      //## begin cLocalVariable::MaxArg%40EA8DA0035B.attr preserve=no  implementation: cArgument * {U} NULL
      cArgument *_MaxArg;
      //## end cLocalVariable::MaxArg%40EA8DA0035B.attr

      //## Attribute: DataSets%419A2A530128
      //## begin cLocalVariable::DataSets%419A2A530128.attr preserve=no  implementation: VALUEBUF_ARRAY_T {U} 
      VALUEBUF_ARRAY_T _DataSets;
      //## end cLocalVariable::DataSets%419A2A530128.attr

      //## Attribute: Values%419A2C09038A
      //## begin cLocalVariable::Values%419A2C09038A.attr preserve=no  implementation: cValueBuffer * {U} 
      cValueBuffer *_Values;
      //## end cLocalVariable::Values%419A2C09038A.attr

      //## Attribute: PreviousValue%41AC64FB03B9
      //## begin cLocalVariable::PreviousValue%41AC64FB03B9.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _PreviousValue;
      //## end cLocalVariable::PreviousValue%41AC64FB03B9.attr

      //## Attribute: InputStates%423C40BD03A9
      //## begin cLocalVariable::InputStates%423C40BD03A9.attr preserve=no  implementation: INPUTSTATE_ARRAY_T {U} 
      INPUTSTATE_ARRAY_T _InputStates;
      //## end cLocalVariable::InputStates%423C40BD03A9.attr

      //## Attribute: States%42414618003E
      //## begin cLocalVariable::States%42414618003E.attr preserve=no  implementation: CHAR_T * {U} NULL
      CHAR_T *_States;
      //## end cLocalVariable::States%42414618003E.attr

      //## Attribute: ShadowChanges%470A4B3D0114
      //## begin cLocalVariable::ShadowChanges%470A4B3D0114.attr preserve=no  implementation: UCHAR_T * {U} NULL
      UCHAR_T *_ShadowChanges;
      //## end cLocalVariable::ShadowChanges%470A4B3D0114.attr

    // Additional Implementation Declarations
      //## begin cLocalVariable%3E0038B30046.implementation preserve=yes
      void cLocalVariable::BufChanged (BUF_T old_buf, BUF_T new_buf, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4, ULONG_T flags);
      virtual ULONG_T GetObject (cBinaryObject &object, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);
      virtual void SetObject (const cBinaryObject &object, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);
      void Persist();
      void Persist(cPersistenceManager * manager, int i1, int i2, int i3, int i4, UCHAR_T persistence_type, ULONG_T dataset);

      // accu management
      // the "accu" is used to store values retrieved in subordinated
      // methods like GetDevice, ...
      // the accu then holds the value of the variable until this value is returned to
      // the calling function
      // when a Getvar or a similar call is interrupted within the period of setting the accu value
      // and returning the accu value back to the caller, an invalid value for the GetVar call may result in this
      // this situation occurs for example when two threads call GetVar on the same variable with different indices
      // the solution to avoid this problem is to maintain an accu not only for a variable, but one accu per variable
      // and thread
      // this is implemented using not one accu but an accu map, that contains an accu for every thread
      typedef std::map<int,cSHVariant*> ACCU_MAP_T;
      cMutexSem _AccuMutex;
      ACCU_MAP_T _AccuMap;
      // return the correct accu for this variable and this thread
      inline cSHVariant * Accu()
      {
         // protect accu procurement 
         cObjectLock __lock__(&_AccuMutex);
         int thread_id = cSystemUtils::ThreadId();
         ACCU_MAP_T::const_iterator i = _AccuMap.find(thread_id);
         if (i != _AccuMap.end()) {
            // accu for this thread and this variable already instantiated
            return (*i).second;
         } else {
            // instantiate a new accu for this thread and this variable
            cSHVariant * accu = new cSHVariant(_VarDef->_DataType);
            _AccuMap[thread_id] = accu;
            return accu;
         }
      };

      BOOL_T StoreIndices(int i1, int i2, int i3, int i4);
      BOOL_T StoreIndices(int pos);
      void SetDeviceStates();

      // Local Variable Limit Checker
public:
   class LimitChecker
      {
      public:
         virtual int CheckLimits(cLocalVariable * variable, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4) = 0;
         virtual int CheckLimits(cLocalVariable * variable, UCHAR_T method_type) = 0;
      };

      friend class LimitChecker;
      static LimitChecker * _LimitChecker;
      static void SetLimitChecker(LimitChecker * checker)
      {
         _LimitChecker = checker;
      };

      //## end cLocalVariable%3E0038B30046.implementation
};

//## begin cLocalVariable%3E0038B30046.postscript preserve=yes
//## end cLocalVariable%3E0038B30046.postscript

// Class cLocalVariable 

//## begin module%3E0038B30046.epilog preserve=yes
//## end module%3E0038B30046.epilog


#endif
