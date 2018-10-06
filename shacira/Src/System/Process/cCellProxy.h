//## begin module%3DCAA12E00EB.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3DCAA12E00EB.cm

//## begin module%3DCAA12E00EB.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3DCAA12E00EB.cp

//## Module: cCellProxy%3DCAA12E00EB; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Process\cCellProxy.h

#ifndef cCellProxy_h
#define cCellProxy_h 1

//## begin module%3DCAA12E00EB.includes preserve=yes
#include "System/Database/cBinaryObject.h"
//## end module%3DCAA12E00EB.includes

// cProxy
#include "System/Objects/cProxy.h"
// cTransferObject
#include "System/Objects/cTransferObject.h"
// cAlarm
#include "System/Objects/cAlarm.h"

class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cBroker;

//## begin module%3DCAA12E00EB.additionalDeclarations preserve=yes
//## end module%3DCAA12E00EB.additionalDeclarations


//## begin cCellProxy%3DCAA12E00EB.preface preserve=yes
//## end cCellProxy%3DCAA12E00EB.preface

//## Class: cCellProxy%3DCAA12E00EB
//## Category: System::Process%3D3FFF4B0086
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3DCAA12E00ED;cBroker { -> F}
//## Uses: <unnamed>%3E5B2B0003B3;cTransferObject { -> }
//## Uses: <unnamed>%3EA6BB0E00DA;cContext { -> F}
//## Uses: <unnamed>%40754855038A;cAlarm { -> }

class __DLL_EXPORT__ cCellProxy : public cProxy  //## Inherits: <unnamed>%3EDCC91C0242
{
  //## begin cCellProxy%3DCAA12E00EB.initialDeclarations preserve=yes
public:
  //## end cCellProxy%3DCAA12E00EB.initialDeclarations

    //## Constructors (generated)
      cCellProxy();

      cCellProxy(const cCellProxy &right);

    //## Destructor (generated)
      virtual ~cCellProxy();


    //## Other Operations (specified)
      //## Operation: Name%1036694746
      virtual STRING_T Name () = 0;

      //## Operation: GetVarDefs%1049277236
      //	Gets all variable definitions as a list of serialized
      //	objects.
      virtual ULONG_T GetVarDefs (STRING_T &var_defs) = 0;

      //## Operation: GetValue%1036694750
      //	Gets the value of a variable specified by variable name
      //	and indices as string value.
      virtual void GetValue (CONST_STRING_T var_name, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: GetValue%1036694751
      //	Gets the value of a variable specified by variable name
      //	and indices as integer value.
      virtual void GetValue (CONST_STRING_T var_name, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: GetValue%1036694752
      //	Gets the value of a variable specified by variable name
      //	and indices as floating point value.
      virtual void GetValue (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: RefreshValue%1133172778
      //	Refreshes a variable value
      virtual void RefreshValue (CONST_STRING_T var_name, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: SetValue%1036694753
      //	Sets the value of a variable specified by variable name
      //	and indices as string value.
      virtual void SetValue (CONST_STRING_T var_name, CONST_STRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: SetValue%1036694754
      //	Sets the value of a variable specified by variable name
      //	and indices as integer value.
      virtual void SetValue (CONST_STRING_T var_name, LONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetValue%1036694755
      //	Sets the value of a variable specified by variable name
      //	and indices as floating point value.
      virtual void SetValue (CONST_STRING_T var_name, DOUBLE_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: GetParam%1078912339
      //	Gets the parameter value specified by parameter name as
      //	string value. The target object is adressed within the
      //	parameter name.
      virtual void GetParam (CONST_STRING_T param_name, STRING_T &value) = 0;

      //## Operation: GetParam%1078912340
      //	Gets the parameter value specified by parameter name as
      //	integer value. The target object is adressed within the
      //	parameter name.
      virtual void GetParam (CONST_STRING_T param_name, LONG_T &value) = 0;

      //## Operation: GetParam%1078912341
      //	Gets the parameter value specified by parameter name as
      //	floating point value. The target object is adressed
      //	within the parameter name.
      virtual void GetParam (CONST_STRING_T param_name, DOUBLE_T &value) = 0;

      //## Operation: SetParam%1078912342
      //	Sets the parameter value specified by parameter name as
      //	string value. The target object is adressed within the
      //	parameter name.
      virtual void SetParam (CONST_STRING_T param_name, CONST_STRING_T value) = 0;

      //## Operation: SetParam%1078912343
      //	Sets the parameter value specified by parameter name as
      //	integer value. The target object is adressed within the
      //	parameter name.
      virtual void SetParam (CONST_STRING_T param_name, LONG_T value);

      //## Operation: SetParam%1078912344
      //	Sets the parameter value specified by parameter name as
      //	floating point value. The target object is adressed
      //	within the parameter name.
      virtual void SetParam (CONST_STRING_T param_name, DOUBLE_T value) = 0;

      //## Operation: ReadFile%1078912351
      //	Reads a file specified by file name.
      virtual void ReadFile (CONST_STRING_T file_name, CONST_STRING_T sub_files, STRING_T &buf) = 0;

      virtual void ExportVariables(STRING_T &buf, CONST_STRING_T sub_file, CONST_STRING_T separator) = 0;

      //## Operation: WriteFile%1078912352
      //	Writes a file specified by file name.
      virtual void WriteFile (CONST_STRING_T file_name, CONST_STRING_T sub_files, CONST_STRING_T buf) = 0;

      //## Operation: GetId%1078912353
      //	Gets the id of a variable specified by variable name.
      virtual LONG_T GetId (CONST_STRING_T var_name) = 0;

      //## Operation: GetValue%1078912354
      //	Gets the value of a variable specified by variable id
      //	and indices as string value.
      virtual void GetValue (LONG_T var_id, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: GetValue%1078912355
      //	Gets the value of a variable specified by id name and
      //	indices as integer value.
      virtual void GetValue (LONG_T var_id, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: GetValue%1078912356
      //	Gets the value of a variable specified by variable id
      //	and indices as floating point value.
      virtual void GetValue (LONG_T var_id, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: SetValue%1078912357
      //	Sets the value of a variable specified by variable  id
      //	and indices as string value.
      virtual void SetValue (LONG_T var_id, CONST_STRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: SetValue%1078912358
      //	Sets the value of a variable specified by variable id
      //	and indices as integer value.
      virtual void SetValue (LONG_T var_id, LONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetValue%1078912359
      //	Sets the value of a variable specified by variable id
      //	and indices as floating point value.
      virtual void SetValue (LONG_T var_id, DOUBLE_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0) = 0;

      //## Operation: Alarms%1081425834
      virtual ULONG_T Alarms (ULONG_T selection) = 0;

      //## Operation: Alarms%1089103359
      virtual ULONG_T Alarms (ULONG_T selection, ALARM_MAP_T &alarms) = 0;

      //## Operation: ClearAlarm%1081425835
      virtual void ClearAlarm (ULONG_T ident) = 0;

      //## Operation: ClearAlarms%1081425836
      virtual void ClearAlarms () = 0;

      //## Operation: GetDeviceValue%1082984456
      //	Retrieves a value of a variable directly from a device.
      virtual void GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, STRING_T &value) = 0;

      //## Operation: SetDeviceValue%1082984457
      virtual void SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, CONST_STRING_T value) = 0;

      //## Operation: GetMinimum%1089103327
      //	Gets the minimum value of a variable specified by
      //	variable name.
      virtual void GetMinimum (CONST_STRING_T var_name, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) = 0;

      //## Operation: GetMinimum%1089103328
      //	Gets the minimum value of a variable specified by
      //	variable name.
      virtual void GetMinimum (CONST_STRING_T var_name, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true) = 0;

      //## Operation: GetMinimum%1089103329
      //	Gets the minimum value of a variable specified by
      //	variable name.
      virtual void GetMinimum (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) = 0;

      //## Operation: GetMinimum%1089103330
      //	Gets the minimum value of a variable specified by
      //	variable id.
      virtual void GetMinimum (LONG_T var_id, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) = 0;

      //## Operation: GetMinimum%1089103331
      //	Gets the minimum value of a variable specified by
      //	variable id.
      virtual void GetMinimum (LONG_T var_id, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true) = 0;

      //## Operation: GetMinimum%1089103332
      //	Gets the minimum value of a variable specified by
      //	variable id.
      virtual void GetMinimum (LONG_T var_id, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) = 0;

      //## Operation: GetMaximum%1089103333
      //	Gets the maximum value of a variable specified by
      //	variable name.
      virtual void GetMaximum (CONST_STRING_T var_name, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) = 0;

      //## Operation: GetMaximum%1089103334
      //	Gets the maximum value of a variable specified by
      //	variable name.
      virtual void GetMaximum (CONST_STRING_T var_name, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true) = 0;

      //## Operation: GetMaximum%1089103335
      //	Gets the maximum value of a variable specified by
      //	variable name.
      virtual void GetMaximum (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) = 0;

      //## Operation: GetMaximum%1089103336
      //	Gets the maximum value of a variable specified by
      //	variable id.
      virtual void GetMaximum (LONG_T var_id, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) = 0;

      //## Operation: GetMaximum%1089103337
      //	Gets the maximum value of a variable specified by
      //	variable id.
      virtual void GetMaximum (LONG_T var_id, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true) = 0;

      //## Operation: GetMaximum%1089103338
      //	Gets the maximum value of a variable specified by
      //	variable id.
      virtual void GetMaximum (LONG_T var_id, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1) = 0;

      //## Operation: ExecuteCommand%1089292611
      //	Executes a command on a program owned by the cell. The
      //	program is denoted by program name.
      virtual void ExecuteCommand (CONST_STRING_T program_name, ULONG_T command) = 0;

      //## Operation: ExecuteRequest%1133771772
      virtual void ExecuteRequest (CONST_STRING_T program_name, STRING_T &reply, CONST_STRING_T request) = 0;

      //## Operation: SetJob%1093930665
      virtual void SetJob (cJobSpec *job_spec) = 0;

      //## Operation: GetJobSpec%1093930666
      virtual cJobSpec * GetJobSpec (CONST_STRING_T job_name) = 0;

      //## Operation: Login%1121785247
      virtual ULONG_T Login (CONST_STRING_T user_name, CONST_STRING_T password) = 0;

      virtual ULONG_T LoginIfType (CONST_STRING_T user_name, CONST_STRING_T password, ULONG_T if_type=0) = 0;	  

      //## Operation: Logout%1121785248
      virtual void Logout () = 0;

      //## Operation: GetEvent%1121785249
      virtual cTransientObject * GetEvent () = 0;

      //## Operation: GetMemory%1122544051
      virtual void GetMemory (BUF_T buf, PTR_T address, ULONG_T size) = 0;

      //## Operation: SendObject%1121785250
      virtual void SendObject (cTransientObject *object) = 0;

      //## Operation: GetObject%1238436650
      virtual ULONG_T GetObject (cBinaryObject &object, CONST_STRING_T var_name, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetObject%1238436651
      virtual void SetObject (const cBinaryObject &object, CONST_STRING_T var_name, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Ping%1134227773
      virtual BOOL_T Ping ();

      //## Operation: Request%1242995031
      virtual STRING_T Request (CONST_STRING_T request);

      //## Operation: GetRing%1242995035
      virtual STRING_T GetRing (CONST_STRING_T var_name, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: ExecuteJob%1244547097
      //	Executes a command on a program owned by the context.
      //	The program is denoted by program name.
      virtual void ExecuteJob (CONST_STRING_T program_name, CONST_STRING_T job, BOOL_T async = false);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: ClientId%438767AE030C
      LONG_T get_ClientId () const;
      void set_ClientId (LONG_T value);

      //## Attribute: IFType%438AD80C01CE
      LONG_T get_IFType () const;
      void set_IFType (LONG_T value);

  public:
    // Additional Public Declarations
      //## begin cCellProxy%3DCAA12E00EB.public preserve=yes
      //## end cCellProxy%3DCAA12E00EB.public

  protected:
    // Data Members for Class Attributes

      //## begin cCellProxy::ClientId%438767AE030C.attr preserve=no  public: LONG_T {U} 0
      LONG_T _ClientId;
      //## end cCellProxy::ClientId%438767AE030C.attr

      //## begin cCellProxy::IFType%438AD80C01CE.attr preserve=no  public: LONG_T {U} IF_PROPRIETARY
      LONG_T _IFType;
      //## end cCellProxy::IFType%438AD80C01CE.attr

    // Additional Protected Declarations
      //## begin cCellProxy%3DCAA12E00EB.protected preserve=yes
      //## end cCellProxy%3DCAA12E00EB.protected

  private:
    // Additional Private Declarations
      //## begin cCellProxy%3DCAA12E00EB.private preserve=yes
      //## end cCellProxy%3DCAA12E00EB.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCellProxy%3DCAA12E00EB.implementation preserve=yes
      //## end cCellProxy%3DCAA12E00EB.implementation

};

//## begin cCellProxy%3DCAA12E00EB.postscript preserve=yes
//## end cCellProxy%3DCAA12E00EB.postscript

// Class cCellProxy 

//## begin module%3DCAA12E00EB.epilog preserve=yes
//## end module%3DCAA12E00EB.epilog


#endif
