//## begin module%3FCF50D0002E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FCF50D0002E.cm

//## begin module%3FCF50D0002E.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FCF50D0002E.cp

//## Module: cFM2Device%3FCF50D0002E; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cFM2Device.h

#ifndef cFM2Device_h
#define cFM2Device_h 1

//## begin module%3FCF50D0002E.includes preserve=yes
//## end module%3FCF50D0002E.includes

// cMemoryPtr
#include "System/Memory/cMemoryPtr.h"
// cDevice
#include "Control/Device/cDevice.h"

class __DLL_EXPORT__ cStringUtils;
class __DLL_EXPORT__ cJobEntry;
class __DLL_EXPORT__ cConvUtils;
class __DLL_EXPORT__ cSerialChannel;
class __DLL_EXPORT__ cStringCache;
class __DLL_EXPORT__ cCacheControl;
class __DLL_EXPORT__ cCache;
class __DLL_EXPORT__ cNullOperator;

//## begin module%3FCF50D0002E.additionalDeclarations preserve=yes

class cMachineState 
{
public:
   cMachineState()
   {
      _TimeStamp.Now();
      _Connected = false;
      _Step = 0;
      _ProductionState = 0;
      _MachineState = 0;
      _DataPending = 0;
      _ChangesPending = 0;
      _ErrorsPending = 0;
      _ConfigState = 0;
      _UploadRequest = false;
      _DownloadRequest = false;
      _DownloadFailed = false;
      _StartRequest = false;
      _StopRequest = false;
      _AbortRequest = false;
      _UploadEnabled = false;
      _DownloadEnabled = false;
      _ProductionTerminated = false;
   };
   virtual ~cMachineState() {};
   cTimeObject get_TimeStamp () const {return _TimeStamp;};
   void set_TimeStamp (cTimeObject value) {_TimeStamp = value;};
   BOOL_T get_Connected () const {return _Connected;};
   void set_Connected (BOOL_T value) {_Connected = value;};
   INT_T get_Step () const {return _Step;};
   void set_Step (INT_T value) {_Step = value;};
   INT_T get_ProductionState () const {return _ProductionState;};
   void set_ProductionState (INT_T value) {_ProductionState = value;};
   INT_T get_MachineState () const {return _MachineState;};
   void set_MachineState (INT_T value) {_MachineState = value;};
   INT_T get_DataPending () const {return _DataPending;};
   void set_DataPending (INT_T value) {_DataPending = value;};
   INT_T get_ChangesPending () const {return _ChangesPending;};
   void set_ChangesPending (INT_T value) {_ChangesPending = value;};
   INT_T get_ErrorsPending () const {return _ErrorsPending;};
   void set_ErrorsPending (INT_T value) {_ErrorsPending = value;};
   INT_T get_ConfigState () const {return _ConfigState;};
   void set_ConfigState (INT_T value) {_ConfigState = value;};
   BOOL_T get_UploadRequest () const {return _UploadRequest;};
   void set_UploadRequest (BOOL_T value) {_UploadRequest = value;};
   BOOL_T get_DownloadRequest () const {return _DownloadRequest;};
   void set_DownloadRequest (BOOL_T value) {_DownloadRequest = value;};
   BOOL_T get_DownloadFailed () const {return _DownloadFailed;};
   void set_DownloadFailed (BOOL_T value) {_DownloadFailed = value;};
   BOOL_T get_StartRequest () const {return _StartRequest;};
   void set_StartRequest (BOOL_T value) {_StartRequest = value;};
   BOOL_T get_StopRequest () const {return _StopRequest;};
   void set_StopRequest (BOOL_T value) {_StopRequest = value;};
   BOOL_T get_AbortRequest () const {return _AbortRequest;};
   void set_AbortRequest (BOOL_T value) {_AbortRequest = value;};
   BOOL_T get_UploadEnabled () const {return _UploadEnabled;};
   void set_UploadEnabled (BOOL_T value) {_UploadEnabled = value;};
   BOOL_T get_DownloadEnabled () const {return _DownloadEnabled;};
   void set_DownloadEnabled (BOOL_T value) {_DownloadEnabled = value;};
   BOOL_T get_ProductionTerminated () const {return _ProductionTerminated;};
   void set_ProductionTerminated (BOOL_T value) {_ProductionTerminated = value;};

protected:
      cTimeObject _TimeStamp;
      BOOL_T _Connected;
      INT_T _Step;
      INT_T _ProductionState;
      INT_T _MachineState;
      INT_T _DataPending;
      INT_T _ChangesPending;
      INT_T _ErrorsPending;
      INT_T _ConfigState;
      BOOL_T _UploadRequest;
      BOOL_T _DownloadRequest;
      BOOL_T _DownloadFailed;
      BOOL_T _StartRequest;
      BOOL_T _StopRequest;
      BOOL_T _AbortRequest;
      BOOL_T _UploadEnabled;
      BOOL_T _DownloadEnabled;
      BOOL_T _ProductionTerminated;
};


class cCycleBuf 
{
public:
      cCycleBuf();
      cCycleBuf(const cCycleBuf &right);
      virtual ~cCycleBuf();
      ULONG_T Columns ();
      ULONG_T Rows ();
      void AddColumn (CONST_STRING_T name);
      STRING_T GetColumnName (ULONG_T col);
      STRING_T GetValue (CONST_STRING_T col_name, ULONG_T row);
      void SetValue (CONST_STRING_T col_name, ULONG_T row, CONST_STRING_T value);
      STRING_T GetIdent (ULONG_T row);
      void SetIdent (ULONG_T row, CONST_STRING_T value);
      INT_T GetQuality (ULONG_T row);
      void SetQuality (ULONG_T row, INT_T value);
      LONG_T GetShot (ULONG_T row);
      void SetShot (ULONG_T row, LONG_T value);
      void Add (cCycleBuf *cycle_buf);
      BOOL_T ColumnExists (CONST_STRING_T col_name);
      void Invert ();

private:
      STRING_VECTOR_T & ValueVector (CONST_STRING_T col_name);
      LONG_VECTOR_T _Shot;
      STRING_VECTOR_T _Names;
      std::map<STRING_T, STRING_VECTOR_T> _Values;
      STRING_VECTOR_T _Ident;
      INT_VECTOR_T _Quality;
};

class cChangeBuf 
{
public:
    class __DLL_EXPORT__ cCBEntry 
    {
public:
          cCBEntry();
          cCBEntry(const cCBEntry &right);
          virtual ~cCBEntry();
          const cCBEntry & operator=(const cCBEntry &right);
          STRING_T _KeyValue;
          STRING_T _Name;
          STRING_T _OldValue;
          STRING_T _NewValue;
          cTimeObject _TimeStamp;
          UINT_T _Aggregate;
          UINT_T _Station;
    };
      cChangeBuf();
      cChangeBuf(const cChangeBuf &right);
      virtual ~cChangeBuf();
      ULONG_T Entries ();
      cTimeObject TimeStamp (UINT_T entry);
      STRING_T KeyValue (UINT_T entry);
      STRING_T Name (UINT_T entry);
      STRING_T OldValue (UINT_T entry);
      STRING_T NewValue (UINT_T entry);
      UINT_T Station (UINT_T entry);
      UINT_T Aggregate (UINT_T entry);
      void SetTimeStamp (ULONG_T entry, cTimeObject &value);
      void SetKeyValue (ULONG_T entry, CONST_STRING_T value);
      void SetName (ULONG_T entry, CONST_STRING_T value);
      void SetOldValue (ULONG_T entry, CONST_STRING_T value);
      void SetNewValue (ULONG_T entry, CONST_STRING_T value);
      void SetStation (ULONG_T entry, UINT_T value);
      void SetAggregate (ULONG_T entry, UINT_T value);

private:
      void Resize (UINT_T entry);
      std::vector<cCBEntry> _Entries;
};


class cErrorBuf 
{
public:
    class __DLL_EXPORT__ cEBEntry 
    {
public:
          cEBEntry();
          cEBEntry(const cEBEntry &right);
          virtual ~cEBEntry();
          const cEBEntry & operator=(const cEBEntry &right);
          cTimeObject _TimeStamp;
          STRING_T _KeyValue;
          STRING_T _ErrorId;
          BOOL_T _Start;
          LONG_T _Shot;
    };

      cErrorBuf();
      cErrorBuf(const cErrorBuf &right);
      virtual ~cErrorBuf();
      ULONG_T Entries ();
      cTimeObject TimeStamp (UINT_T entry);
      STRING_T KeyValue (UINT_T entry);
      STRING_T ErrorId (UINT_T entry);
      BOOL_T Start (UINT_T entry);
      LONG_T Shot (UINT_T entry);
      void SetTimeStamp (ULONG_T entry, cTimeObject &value);
      void SetKeyValue (ULONG_T entry, CONST_STRING_T value);
      void SetErrorId (ULONG_T entry, CONST_STRING_T value);
      void SetStart (ULONG_T entry, BOOL_T value);
      void SetShot (ULONG_T entry, LONG_T value);

private:

      void Resize (UINT_T entry);
      std::vector<cEBEntry> _Entries;
};


class cCommAborted
{
public:
   cCommAborted() {};
   virtual ~cCommAborted() {};
};

#define UNDEFINED_SPEC  -1
#define isnum(c) \
  ((c>47) && (c<58)) || c == '.'

class cVarInfo {
private:
   int _Precision;
   int _Length;
public:
   cVarInfo(CONST_STRING_T value)
   {
      _Precision = UNDEFINED_SPEC;
      _Length = UNDEFINED_SPEC;
      SetInfo(value);
   };
   void SetInfo(CONST_STRING_T value)
   {
      if (_Precision != UNDEFINED_SPEC || _Length != UNDEFINED_SPEC) {
         return;
      }
      int len = strlen(value);
      char c = 0;
      for (int i=0; i<len; i++) {
         c = value[i];
         if (!isnum(c)) {
            if (c != '.') {
               _Length = len;
               break;
            }
         }
      }
      if (_Length == UNDEFINED_SPEC) {
         int dec_points = 0;
         int dec_point_pos = -1;
         for (int i=0; i<len; i++) {
            c = value[i];
            if (c == '.') {
               dec_points++;
               dec_point_pos = i;
            }
         }
         if (dec_points == 1) {
            _Precision = (len - dec_point_pos - 1);
         }
         if (dec_points == 0) {
            _Precision = 0;
         }
      }
   };
   int Precision()
   {
      return _Precision;
   };
   int Length()
   {
      return _Length;
   };
};

typedef std::map<STRING_T, cVarInfo*> VAR_INFO_MAP_T;

//## end module%3FCF50D0002E.additionalDeclarations


//## begin cFM2Device%3FCF50D0002E.preface preserve=yes
//## end cFM2Device%3FCF50D0002E.preface

//## Class: cFM2Device%3FCF50D0002E
//## Category: Control::Device%3FCF205002CE
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3FD456770399;cConvUtils { -> F}
//## Uses: <unnamed>%3FDB2B08037A;cMemoryPtr { -> }
//## Uses: <unnamed>%41DBCC5B029F;cNullOperator { -> F}
//## Uses: <unnamed>%41DBFEC10177;cStringCache { -> F}
//## Uses: <unnamed>%41DC008C0109;cCacheControl { -> F}
//## Uses: <unnamed>%41DFD22F000F;cStringUtils { -> F}
//## Uses: <unnamed>%41E24C35006D;cJobEntry { -> F}

class __DLL_EXPORT__ cFM2Device : public cDevice  //## Inherits: <unnamed>%3FD437E00251
{
  //## begin cFM2Device%3FCF50D0002E.initialDeclarations preserve=yes
public:
  //## end cFM2Device%3FCF50D0002E.initialDeclarations

    //## Constructors (generated)
      cFM2Device();

      cFM2Device(const cFM2Device &right);

    //## Constructors (specified)
      //## Operation: cFM2Device%1070879991
      cFM2Device (cConfigurationObject *config_obj, cCell *cell);

    //## Destructor (generated)
      virtual ~cFM2Device();


    //## Other Operations (specified)
      //## Operation: Start%1104923754
      virtual void Start ();

      //## Operation: Stop%1104923755
      virtual void Stop ();

      //## Operation: Cache%1104923756
      virtual void Cache (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);

      //## Operation: Buffer%1104923757
      virtual void Buffer (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T size);

      //## Operation: Get%1104919503
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T &value, ULONG_T flags = 0);

      //## Operation: Get%1104919504
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, USHORT_T &value, ULONG_T flags = 0);

      //## Operation: Get%1071681174
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T &value, ULONG_T flags = 0);

      //## Operation: Get%1104919505
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, FLOAT_T &value, ULONG_T flags = 0);

      //## Operation: Get%1104919506
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, DOUBLE_T &value, ULONG_T flags = 0);

      //## Operation: Get%1071480836
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, STRING_T &value, ULONG_T flags = 0);

      //## Operation: Get%1104919507
      virtual void Get (CONST_STRING_T buf_spec, CONST_STRING_T name, WSTRING_T &value, ULONG_T flags = 0);

      //## Operation: Set%1104919508
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T value, ULONG_T flags = 0);

      //## Operation: Set%1104919509
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, USHORT_T value, ULONG_T flags = 0);

      //## Operation: Set%1104919510
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T value, ULONG_T flags = 0);

      //## Operation: Set%1104919511
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, FLOAT_T value, ULONG_T flags = 0);

      //## Operation: Set%1104919512
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, DOUBLE_T value, ULONG_T flags = 0);

      //## Operation: Set%1104919513
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, CONST_STRING_T value, ULONG_T flags = 0);

      //## Operation: Set%1104919514
      virtual void Set (CONST_STRING_T buf_spec, CONST_STRING_T name, CONST_WSTRING_T value, ULONG_T flags = 0);

      //## Operation: Read%1104919515
      virtual void Read (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);

      //## Operation: Write%1104919516
      virtual void Write (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T flags = 0);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: BaudRate%3FD45C2101B5
      ULONG_T get_BaudRate () const;
      void set_BaudRate (ULONG_T value);

      //## Attribute: Parity%3FD45C2101C5
      ParityTypes get_Parity () const;
      void set_Parity (ParityTypes value);

      //## Attribute: Handshake%3FD45C2101C6
      HandshakeTypes get_Handshake () const;
      void set_Handshake (HandshakeTypes value);

      //## Attribute: CharLen%3FD45C2101C7
      UCHAR_T get_CharLen () const;
      void set_CharLen (UCHAR_T value);

      //## Attribute: StartBits%3FD45C2101D4
      UCHAR_T get_StartBits () const;
      void set_StartBits (UCHAR_T value);

      //## Attribute: StopBits%3FD45C2101D5
      UCHAR_T get_StopBits () const;
      void set_StopBits (UCHAR_T value);

  public:
    // Additional Public Declarations
      //## begin cFM2Device%3FCF50D0002E.public preserve=yes
      //## end cFM2Device%3FCF50D0002E.public

  protected:
    // Data Members for Class Attributes

      //## begin cFM2Device::BaudRate%3FD45C2101B5.attr preserve=no  public: ULONG_T {U} 9600
      ULONG_T _BaudRate;
      //## end cFM2Device::BaudRate%3FD45C2101B5.attr

      //## begin cFM2Device::Parity%3FD45C2101C5.attr preserve=no  public: ParityTypes {U} Even
      ParityTypes _Parity;
      //## end cFM2Device::Parity%3FD45C2101C5.attr

      //## begin cFM2Device::Handshake%3FD45C2101C6.attr preserve=no  public: HandshakeTypes {U} NoHandshake
      HandshakeTypes _Handshake;
      //## end cFM2Device::Handshake%3FD45C2101C6.attr

      //## begin cFM2Device::CharLen%3FD45C2101C7.attr preserve=no  public: UCHAR_T {U} 8
      UCHAR_T _CharLen;
      //## end cFM2Device::CharLen%3FD45C2101C7.attr

      //## begin cFM2Device::StartBits%3FD45C2101D4.attr preserve=no  public: UCHAR_T {U} 1
      UCHAR_T _StartBits;
      //## end cFM2Device::StartBits%3FD45C2101D4.attr

      //## begin cFM2Device::StopBits%3FD45C2101D5.attr preserve=no  public: UCHAR_T {U} 1
      UCHAR_T _StopBits;
      //## end cFM2Device::StopBits%3FD45C2101D5.attr

    // Data Members for Associations

      //## Association: Control::Device::<unnamed>%3FD45BE500AB
      //## Role: cFM2Device::SerialChannel%3FD45BE6008C
      //## begin cFM2Device::SerialChannel%3FD45BE6008C.role preserve=no  public: cSerialChannel { -> 1RFHN}
      cSerialChannel *_SerialChannel;
      //## end cFM2Device::SerialChannel%3FD45BE6008C.role

      //## Association: Control::Device::<unnamed>%41DBFE390000
      //## Role: cFM2Device::VariableCache%41DBFE39035B
      //## begin cFM2Device::VariableCache%41DBFE39035B.role preserve=no  public: cCache { -> 1RFHN}
      cCache *_VariableCache;
      //## end cFM2Device::VariableCache%41DBFE39035B.role

      //## Association: Control::Device::<unnamed>%41DBFE7403C8
      //## Role: cFM2Device::StateCache%41DBFE760138
      //## begin cFM2Device::StateCache%41DBFE760138.role preserve=no  public: cCache { -> 1RFHN}
      cCache *_StateCache;
      //## end cFM2Device::StateCache%41DBFE760138.role

    // Additional Protected Declarations
      //## begin cFM2Device%3FCF50D0002E.protected preserve=yes
      //## end cFM2Device%3FCF50D0002E.protected

  private:

    //## Other Operations (specified)
      //## Operation: MS%1071317839
      virtual void MS (CHAR_T *inbuf, LONG_T buf_size);

      //## Operation: TB%1071317840
      virtual void TB (CHAR_T *inbuf, LONG_T buf_size);

      //## Operation: UD%1071317841
      virtual void UD (CHAR_T *inbuf, LONG_T buf_size);

      //## Operation: DD%1071317842
      virtual void DD (CONST_STRING_T outbuf, LONG_T buf_size);

      //## Operation: EB%1071317843
      virtual void EB (CHAR_T *inbuf, LONG_T buf_size);

      //## Operation: CB%1071317844
      virtual void CB (CHAR_T *inbuf, LONG_T buf_size);

      //## Operation: TP%1071317845
      virtual void TP (CONST_STRING_T page_no, CHAR_T *inbuf, LONG_T buf_size);

      //## Operation: SB%1071317846
      virtual void SB (CONST_STRING_T variables);

      //## Operation: DB%1071317847
      void DB ();

      //## Operation: TV%1071317848
      virtual void TV (CONST_STRING_T var_name, CONST_STRING_T value);

      //## Operation: TV%1071317849
      virtual void TV (CONST_STRING_T var_name, CHAR_T *inbuf, LONG_T buf_size);

      //## Operation: ReadBlock%1071317850
      virtual LONG_T ReadBlock (CHAR_T *buffer, LONG_T buf_len);

      //## Operation: WriteBlock%1071317851
      virtual void WriteBlock (CONST_STRING_T buffer, LONG_T len);

      //## Operation: MasterTransmission%1071317852
      virtual LONG_T MasterTransmission (CONST_STRING_T cmd, LONG_T cmd_len, CHAR_T *rcv_buf, LONG_T buf_len);

      //## Operation: Transmit%1071317853
      INT_T Transmit (CONST_STRING_T cmd_buf, LONG_T cmd_len, CHAR_T *rcv_buf, LONG_T buf_len);

      //## Operation: TestReceiveBuffer%1071317854
      virtual void TestReceiveBuffer (CONST_STRING_T receive_buf, CONST_STRING_T request_buf);

      //## Operation: CopyReceiveBuffer%1071317855
      virtual void CopyReceiveBuffer (CONST_STRING_T cmd, CHAR_T *dst_buf, INT_T dst_buf_len, CHAR_T *rcv_buf, INT_T rcv_len, bool skip_echo = false);

      //## Operation: GetChar%1071317856
      UCHAR_T GetChar (LONG_T timeout);

      //## Operation: SendChar%1071317857
      void SendChar (UCHAR_T c);

      //## Operation: ParseMS%1071317858
      virtual cMachineState * ParseMS (CONST_STRING_T ms);

      //## Operation: ParseTB%1071317859
      virtual cCycleBuf * ParseTB (CONST_STRING_T tb);

      //## Operation: ParseCB%1071317860
      virtual cChangeBuf * ParseCB (CONST_STRING_T cb);

      //## Operation: ParseEB%1071317861
      virtual cErrorBuf * ParseEB (CONST_STRING_T eb);

      //## Operation: SetTransmitBuffer%1071317862
      virtual void SetTransmitBuffer ();

    // Additional Private Declarations
      //## begin cFM2Device%3FCF50D0002E.private preserve=yes
      //## end cFM2Device%3FCF50D0002E.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: CommandType%1071317863
      INT_T CommandType (CONST_STRING_T command);

      //## Operation: VarInfo%1104923762
      cVarInfo * VarInfo (CONST_STRING_T var_name);

      //## Operation: SetVarInfo%1104923759
      void SetVarInfo (CONST_STRING_T var_name, CONST_STRING_T value);

      //## Operation: Precision%1104923760
      int Precision (CONST_STRING_T var_name);

      //## Operation: Length%1104923761
      int Length (CONST_STRING_T var_name);

      //## Operation: ReadState%1105117219
      void ReadState (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);

      //## Operation: UpdateState%1105117220
      void UpdateState ();

      //## Operation: UpdateCycleBuf%1105186360
      void UpdateCycleBuf ();

      //## Operation: UpdateChangeBuf%1105186361
      void UpdateChangeBuf ();

      //## Operation: UpdateErrorBuf%1105186362
      void UpdateErrorBuf ();

      //## Operation: ReadErrorBuf%1152293605
      void ReadErrorBuf (char *buf, ULONG_T buf_size);

    // Data Members for Class Attributes

      //## Attribute: InBuf%3FDB2AF4037A
      //## begin cFM2Device::InBuf%3FDB2AF4037A.attr preserve=no  implementation: cMemoryPtr {U} 
      cMemoryPtr _InBuf;
      //## end cFM2Device::InBuf%3FDB2AF4037A.attr

      //## Attribute: OutBuf%3FDB2AF4037B
      //## begin cFM2Device::OutBuf%3FDB2AF4037B.attr preserve=no  implementation: cMemoryPtr {U} 
      cMemoryPtr _OutBuf;
      //## end cFM2Device::OutBuf%3FDB2AF4037B.attr

      //## Attribute: TempBuf%3FDB2AF40399
      //## begin cFM2Device::TempBuf%3FDB2AF40399.attr preserve=no  implementation: cMemoryPtr {U} 
      cMemoryPtr _TempBuf;
      //## end cFM2Device::TempBuf%3FDB2AF40399.attr

      //## Attribute: BufSize%3FDB2AF403A9
      //## begin cFM2Device::BufSize%3FDB2AF403A9.attr preserve=no  implementation: ULONG_T {U} 20000
      ULONG_T _BufSize;
      //## end cFM2Device::BufSize%3FDB2AF403A9.attr

      //## Attribute: VarInfos%41DC2BE9035B
      //## begin cFM2Device::VarInfos%41DC2BE9035B.attr preserve=no  implementation: VAR_INFO_MAP_T {U} 
      VAR_INFO_MAP_T _VarInfos;
      //## end cFM2Device::VarInfos%41DC2BE9035B.attr

      //## Attribute: MachineState%41DECDB40222
      //## begin cFM2Device::MachineState%41DECDB40222.attr preserve=no  implementation: cMachineState * {U} NULL
      cMachineState *_MachineState;
      //## end cFM2Device::MachineState%41DECDB40222.attr

      //## Attribute: SetBuffer%41EF7EA10222
      //## begin cFM2Device::SetBuffer%41EF7EA10222.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _SetBuffer;
      //## end cFM2Device::SetBuffer%41EF7EA10222.attr

    // Additional Implementation Declarations
      //## begin cFM2Device%3FCF50D0002E.implementation preserve=yes
      //## end cFM2Device%3FCF50D0002E.implementation

};

//## begin cFM2Device%3FCF50D0002E.postscript preserve=yes
//## end cFM2Device%3FCF50D0002E.postscript

// Class cFM2Device 

//## begin module%3FCF50D0002E.epilog preserve=yes
//## end module%3FCF50D0002E.epilog


#endif
