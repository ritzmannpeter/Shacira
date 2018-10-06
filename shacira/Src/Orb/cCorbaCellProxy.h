//## begin module%3C4EE681039C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3C4EE681039C.cm

//## begin module%3C4EE681039C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3C4EE681039C.cp

//## Module: cCorbaCellProxy%3C4EE681039C; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Orb\cCorbaCellProxy.h

#ifndef cCorbaCellProxy_h
#define cCorbaCellProxy_h 1

//## begin module%3C4EE681039C.includes preserve=yes

#include "Control.hh"
#include "iCellObject.h"

//## end module%3C4EE681039C.includes

// cCellProxy
#include "System/Process/cCellProxy.h"
// cAlarm
#include "System/Objects/cAlarm.h"

class __DLL_EXPORT__ cJobSpec;
class __DLL_EXPORT__ cBroker;

//## begin module%3C4EE681039C.additionalDeclarations preserve=yes
//## end module%3C4EE681039C.additionalDeclarations


//## begin cCorbaCellProxy%3C4EE681039C.preface preserve=yes
//## end cCorbaCellProxy%3C4EE681039C.preface

//## Class: cCorbaCellProxy%3C4EE681039C
//## Category: Orb%3AC0838100CF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3C517A5B033C;cBroker { -> F}
//## Uses: <unnamed>%4075484D0196;cAlarm { -> }
//## Uses: <unnamed>%41342C96005D;cJobSpec { -> F}

class __DLL_EXPORT__ cCorbaCellProxy : public cCellProxy  //## Inherits: <unnamed>%3DCAA1E10157
{
  //## begin cCorbaCellProxy%3C4EE681039C.initialDeclarations preserve=yes
private:
   CORBA::Object * _CorbaObject;
   Control::iCell_var * _Itf;
   unsigned long _CallTimeout;
public:
  //## end cCorbaCellProxy%3C4EE681039C.initialDeclarations

    //## Constructors (generated)
      cCorbaCellProxy(unsigned long call_timeout = 0);

      cCorbaCellProxy(const cCorbaCellProxy &right);

    //## Destructor (generated)
      virtual ~cCorbaCellProxy();


    //## Other Operations (specified)
      //## Operation: Update%1054547852
      virtual void Update (cProxy *proxy);

      //## Operation: Name%1036694763
      virtual STRING_T Name ();

      //## Operation: GetVarDefs%1049277237
      //	Gets all variable definitions as a list of serialized
      //	objects.
      virtual ULONG_T GetVarDefs (STRING_T &var_defs);

      //## Operation: GetValue%1023444138
      virtual void GetValue (CONST_STRING_T var_name, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetValue%1023444139
      virtual void GetValue (CONST_STRING_T var_name, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetValue%1023444140
      //	This method returns the value of the item specified by
      //	item_name. The value of the item is returned using an
      //	object of type STRING_T &.
      virtual void GetValue (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: RefreshValue%1133172779
      //	Refreshes a variable value
      virtual void RefreshValue (CONST_STRING_T var_name, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetValue%1023444141
      virtual void SetValue (CONST_STRING_T var_name, CONST_STRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetValue%1023444142
      virtual void SetValue (CONST_STRING_T var_name, LONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetValue%1023444143
      virtual void SetValue (CONST_STRING_T var_name, DOUBLE_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetParam%1078912345
      virtual void GetParam (CONST_STRING_T param_name, STRING_T &value);

      //## Operation: GetParam%1078912346
      virtual void GetParam (CONST_STRING_T param_name, LONG_T &value);

      //## Operation: GetParam%1078912347
      virtual void GetParam (CONST_STRING_T param_name, DOUBLE_T &value);

      //## Operation: SetParam%1078912348
      virtual void SetParam (CONST_STRING_T param_name, CONST_STRING_T value);

      //## Operation: SetParam%1078912349
      virtual void SetParam (CONST_STRING_T param_name, LONG_T value);

      //## Operation: SetParam%1078912350
      virtual void SetParam (CONST_STRING_T param_name, DOUBLE_T value);

      //## Operation: ReadFile%1078912360
      virtual void ReadFile (CONST_STRING_T file_name, CONST_STRING_T sub_files, STRING_T &buf);

      virtual void ExportVariables(STRING_T &buf, CONST_STRING_T sub_file, CONST_STRING_T separator);

      //## Operation: WriteFile%1078912361
      virtual void WriteFile (CONST_STRING_T file_name, CONST_STRING_T sub_files, CONST_STRING_T buf);

      //## Operation: GetId%1078912362
      virtual LONG_T GetId (CONST_STRING_T var_name);

      //## Operation: GetValue%1078912363
      virtual void GetValue (LONG_T var_id, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetValue%1078912364
      virtual void GetValue (LONG_T var_id, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: GetValue%1078912365
      virtual void GetValue (LONG_T var_id, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetValue%1078912366
      virtual void SetValue (LONG_T var_id, CONST_STRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetValue%1078912367
      virtual void SetValue (LONG_T var_id, LONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetValue%1078912368
      virtual void SetValue (LONG_T var_id, DOUBLE_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: Alarms%1089103360
      virtual ULONG_T Alarms (ULONG_T selection);

      //## Operation: Alarms%1081425837
      virtual ULONG_T Alarms (ULONG_T selection, ALARM_MAP_T &alarms);

      //## Operation: ClearAlarm%1081425838
      virtual void ClearAlarm (ULONG_T ident);

      //## Operation: ClearAlarms%1081425839
      virtual void ClearAlarms ();

      //## Operation: GetDeviceValue%1082984458
      //	Retrieves a value of a variable directly from a device.
      virtual void GetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, STRING_T &value);

      //## Operation: SetDeviceValue%1082984459
      virtual void SetDeviceValue (CONST_STRING_T buf_spec, CONST_STRING_T address, CONST_STRING_T value);

      //## Operation: GetMinimum%1089103339
      //	Gets the minimum value of a variable specified by
      //	variable name.
      virtual void GetMinimum (CONST_STRING_T var_name, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1089103340
      //	Gets the minimum value of a variable specified by
      //	variable name.
      virtual void GetMinimum (CONST_STRING_T var_name, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMinimum%1089103341
      //	Gets the minimum value of a variable specified by
      //	variable name.
      virtual void GetMinimum (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1089103342
      //	Gets the minimum value of a variable specified by
      //	variable id.
      virtual void GetMinimum (LONG_T var_id, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMinimum%1089103343
      //	Gets the minimum value of a variable specified by
      //	variable id.
      virtual void GetMinimum (LONG_T var_id, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMinimum%1089103344
      //	Gets the minimum value of a variable specified by
      //	variable id.
      virtual void GetMinimum (LONG_T var_id, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103345
      //	Gets the maximum value of a variable specified by
      //	variable name.
      virtual void GetMaximum (CONST_STRING_T var_name, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103346
      //	Gets the maximum value of a variable specified by
      //	variable name.
      virtual void GetMaximum (CONST_STRING_T var_name, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMaximum%1089103347
      //	Gets the maximum value of a variable specified by
      //	variable name.
      virtual void GetMaximum (CONST_STRING_T var_name, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103348
      //	Gets the maximum value of a variable specified by
      //	variable id.
      virtual void GetMaximum (LONG_T var_id, STRING_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: GetMaximum%1089103349
      //	Gets the maximum value of a variable specified by
      //	variable id.
      virtual void GetMaximum (LONG_T var_id, LONG_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, BOOL_T fixed_decimal_representation = true);

      //## Operation: GetMaximum%1089103350
      //	Gets the maximum value of a variable specified by
      //	variable id.
      virtual void GetMaximum (LONG_T var_id, DOUBLE_T &value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);

      //## Operation: ExecuteCommand%1089292612
      //	Executes a command on a program owned by the context.
      //	The program is denoted by program name.
      virtual void ExecuteCommand (CONST_STRING_T program_name, ULONG_T command);

      //## Operation: ExecuteRequest%1133771773
      virtual void ExecuteRequest (CONST_STRING_T program_name, STRING_T &reply, CONST_STRING_T request);

      //## Operation: SetJob%1093930667
      virtual void SetJob (cJobSpec *job_spec);

      //## Operation: GetJobSpec%1093930668
      virtual cJobSpec * GetJobSpec (CONST_STRING_T job_name);

      //## Operation: Login%1121785251
      virtual ULONG_T Login (CONST_STRING_T user_name, CONST_STRING_T password);

      virtual ULONG_T LoginIfType (CONST_STRING_T user_name, CONST_STRING_T password, ULONG_T if_type);	  

      //## Operation: Logout%1121785252
      virtual void Logout ();

      //## Operation: GetEvent%1121785253
      virtual cTransientObject * GetEvent ();

      //## Operation: GetMemory%1122544052
      virtual void GetMemory (BUF_T buf, PTR_T address, ULONG_T size);

      //## Operation: SendObject%1121785254
      virtual void SendObject (cTransientObject *object);

      //## Operation: GetObject%1238436652
      virtual ULONG_T GetObject (cBinaryObject &object, CONST_STRING_T var_name, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetObject%1238436653
      virtual void SetObject (const cBinaryObject &object, CONST_STRING_T var_name, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: SetItf%1054632839
      void SetItf ();

      //## Operation: ReleaseItf%1054632840
      void ReleaseItf ();

      //## Operation: Ping%1134227774
      virtual BOOL_T Ping ();

      //## Operation: Request%1242995033
      virtual STRING_T Request (CONST_STRING_T request);

      //## Operation: GetRing%1242995034
      virtual STRING_T GetRing (CONST_STRING_T var_name, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1, ULONG_T flags = 0);

      //## Operation: ExecuteJob%1244547096
      //	Executes a job on a program owned by the context. The
      //	program is denoted by program name.
      virtual void ExecuteJob (CONST_STRING_T program_name, CONST_STRING_T job, BOOL_T async = false);

  public:
    // Additional Public Declarations
      //## begin cCorbaCellProxy%3C4EE681039C.public preserve=yes
      //## end cCorbaCellProxy%3C4EE681039C.public

  protected:
    // Additional Protected Declarations
      //## begin cCorbaCellProxy%3C4EE681039C.protected preserve=yes
      //## end cCorbaCellProxy%3C4EE681039C.protected

  private:
    // Additional Private Declarations
      //## begin cCorbaCellProxy%3C4EE681039C.private preserve=yes
      //## end cCorbaCellProxy%3C4EE681039C.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cCorbaCellProxy%3C4EE681039C.implementation preserve=yes
      //## end cCorbaCellProxy%3C4EE681039C.implementation

};

//## begin cCorbaCellProxy%3C4EE681039C.postscript preserve=yes
//## end cCorbaCellProxy%3C4EE681039C.postscript

// Class cCorbaCellProxy 

//## begin module%3C4EE681039C.epilog preserve=yes
//## end module%3C4EE681039C.epilog


#endif
