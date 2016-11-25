//## begin module%3FCF50D0002E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3FCF50D0002E.cm

//## begin module%3FCF50D0002E.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%3FCF50D0002E.cp

//## Module: cFM2Device%3FCF50D0002E; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\Control\Device\cFM2Device.cpp

//## begin module%3FCF50D0002E.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%3FCF50D0002E.additionalIncludes

//## begin module%3FCF50D0002E.includes preserve=yes
#define CMD_BUF_SIZE 10
//## end module%3FCF50D0002E.includes

// cStringUtils
#include "System/cStringUtils.h"
// cJobEntry
#include "System/Objects/cJobEntry.h"
// cConvUtils
#include "System/Sys/cConvUtils.h"
// cSerialChannel
#include "Control/SerialChannel/cSerialChannel.h"
// cStringCache
#include "Control/Device/cStringCache.h"
// cCacheControl
#include "Control/Device/cCacheControl.h"
// cCache
#include "Control/Device/cCache.h"
// cFM2Device
#include "Control/Device/cFM2Device.h"
// cNullOperator
#include "Control/Device/cNullOperator.h"
//## begin module%3FCF50D0002E.additionalDeclarations preserve=yes

static char _StringBuffer[0x10000] = {0};
typedef struct _error_entry {
   ULONG_T time;
   long shot;
   char id[0x20];
   BOOL_T start;
}  ERROR_ENTRY_T;
typedef std::vector<ERROR_ENTRY_T*> ERROR_VEC_T;
static ERROR_VEC_T _Errors;
static void AddAlarm(ULONG_T time, long shot, const char * error_id, BOOL_T start)
{
   ERROR_ENTRY_T * error_entry = (ERROR_ENTRY_T*)cSystemUtils::Alloc(sizeof(*error_entry));
   error_entry->time = time;
   error_entry->shot = shot;
   int id_len = strlen(error_id);
   if (id_len > sizeof(error_entry->id) - 1) {
      id_len = sizeof(error_entry->id) - 1;
   }
   memcpy(error_entry->id, error_id, id_len);
   error_entry->start = start;
   int size = _Errors.size();
   _Errors.resize(size + 1);
   _Errors[size] = error_entry;
}

#define COMMAND_TYPE_1	1
#define COMMAND_TYPE_2	2
#define COMMAND_TYPE_3	3

#define READ_TIMEOUT 0

#define END_OF_MESSAGE     -5

#define SUBTRACTING_SHOT_COUNT_VAR "CYX1A_.11"
#define ADDING_SHOT_COUNT_VAR "CYX1A_.4"
#define MAX_CYCBUF_ROWS		20
#define MAX_CYCBUF_COLS		20

#define BLK_RESPONSE_TIMEOUT  30000
#define CHAR_TIMEOUT          1000
#define INTER_CHAR_TIMEOUT    200
#define MAX_BLK_LEN           248
#define BLK_OVERHEAD          10
#define MAX_RETRIES           6

#define START_TEXT   0
#define TEXT_BODY    1
#define EXPECT_LF    2
#define CHECKSUM_0   3
#define CHECKSUM_1   4
#define CHECKSUM_2   5
#define CHECKSUM_3   6
#define EXPECT_ETX   7

// driver object implementations

// cycle buf

cCycleBuf::cCycleBuf()
{
}

cCycleBuf::cCycleBuf(const cCycleBuf &right)
{
_ASSERT_UNCOND
}


cCycleBuf::~cCycleBuf()
{
}

ULONG_T cCycleBuf::Columns ()
{
   return _Names.size();
}

ULONG_T cCycleBuf::Rows ()
{
   if (_Values.size() > 0) {
      STRING_VECTOR_T vector = (*(_Values.begin())).second;
      return vector.size();
   } else {
      return 0;
   }
}

void cCycleBuf::AddColumn (CONST_STRING_T name)
{
   if (!ColumnExists(name)) {
      STRING_VECTOR_T vector;
      _Values[name] = vector;
      int pos = _Names.size();
      _Names.resize(pos+1);
      _Names[pos] = name;
   }
}

STRING_T cCycleBuf::GetColumnName (ULONG_T col)
{
   if (col < _Names.size()) {
      return _Names[col];
   } else {
      char _col[32] = {0};
      throw cError(CYCLEBUF_COLUMN_INDEX_INVALID, 0, cConvUtils::StringValue(col).c_str());
   }
}

STRING_T cCycleBuf::GetValue (CONST_STRING_T col_name, ULONG_T row)
{
   if (ColumnExists(col_name)) {
      STRING_VECTOR_T & vector = ValueVector(col_name);
      if (row < vector.size()) {
         return vector[row];
      } else {
         return "-";
      }
   } else {
      throw cError(CYCLEBUF_COLUMN_NAME_INVALID, 0, col_name);
   }
}

void cCycleBuf::SetValue (CONST_STRING_T col_name, ULONG_T row, CONST_STRING_T value)
{
   if (!ColumnExists(col_name)) {
      AddColumn(col_name);
   }
   STRING_VECTOR_T & vector = ValueVector(col_name);
   if (row >= vector.size()) {
      vector.resize(row+1);
   }
   vector[row] = value;
}

STRING_T cCycleBuf::GetIdent (ULONG_T row)
{
   if (row < Rows()) {
      if (row < _Ident.size()) {
         return _Ident[row];
      } else {
         return "-";
      }
   } else {
      throw cError(CYCLEBUF_ROW_INVALID, 0, cConvUtils::StringValue(row).c_str());
   }
}

void cCycleBuf::SetIdent (ULONG_T row, CONST_STRING_T value)
{
   if (row < Rows()) {
      if (row >= _Ident.size()) {
         _Ident.resize(row+1);
      }
      _Ident[row] = value;
   } else {
      throw cError(CYCLEBUF_ROW_INVALID, 0, cConvUtils::StringValue(row).c_str());
   }
}

INT_T cCycleBuf::GetQuality (ULONG_T row)
{
   if (row < Rows()) {
      if (row < _Quality.size()) {
         return _Quality[row];
      } else {
         return -1;
      }
   } else {
      throw cError(CYCLEBUF_ROW_INVALID, 0, cConvUtils::StringValue(row).c_str());
   }
}

void cCycleBuf::SetQuality (ULONG_T row, INT_T value)
{
   if (row < Rows()) {
      if (row >= _Quality.size()) {
         _Quality.resize(row+1);
      }
      _Quality[row] = value;
   } else {
      throw cError(CYCLEBUF_ROW_INVALID, 0, cConvUtils::StringValue(row).c_str());
   }
}

LONG_T cCycleBuf::GetShot (ULONG_T row)
{
   if (row < Rows()) {
      if (row < _Shot.size()) {
         return _Shot[row];
      } else {
         return -1;
      }
   } else {
      throw cError(CYCLEBUF_ROW_INVALID, 0, cConvUtils::StringValue(row).c_str());
   }
}

void cCycleBuf::SetShot (ULONG_T row, LONG_T value)
{
   if (row < Rows()) {
      if (row >= _Shot.size()) {
         _Shot.resize(row+1);
      }
      _Shot[row] = value;
   } else {
      throw cError(CYCLEBUF_ROW_INVALID, 0, cConvUtils::StringValue(row).c_str());
   }
}

void cCycleBuf::Add (cCycleBuf *cycle_buf)
{
   int cols = cycle_buf->Columns();
   for (int col=0; col<cols; col++) {
      STRING_T col_name = cycle_buf->GetColumnName(col);
      AddColumn(col_name.c_str());
      int rows = cycle_buf->Rows();
      for (int row=0; row<rows; row++) {
         STRING_T value = cycle_buf->GetValue(col_name.c_str(), row);
         SetValue(col_name.c_str(), row, value.c_str());
      }
   }
}

BOOL_T cCycleBuf::ColumnExists (CONST_STRING_T col_name)
{
   int len = _Names.size();
   for (int i=0; i<len; i++) {
      if (strcmp(col_name, _Names[i].c_str()) == 0) return true;
   }
   return false;
}

void cCycleBuf::Invert ()
{
   unsigned long rows = Rows();
   if (rows <= 1) {
      return;
   } else {
      std::map<STRING_T, STRING_VECTOR_T>::const_iterator column = _Values.begin();
      while (column != _Values.end()) {
         STRING_VECTOR_T & values = (STRING_VECTOR_T&)(*column).second;
         unsigned long len = values.size();
         if (len > rows) {
            throw cError(CYCLEBUF_ROW_COUNT, 0,
                         cConvUtils::StringValue(len).c_str(),
                         cConvUtils::StringValue(len).c_str());
         } else if (len < rows) {
            len = rows;
            values.resize(len);
         }
         STRING_VECTOR_T new_values;
         new_values.resize(len);
         for (unsigned long row=0; row<len; row++) {
            new_values[(len-row)-1] = values[row];
         }
// ??
         for (unsigned long row_=0; row_<len; row_++) {
            values[row_] = new_values[row_];
         }
         column++;
      }
   }
}

STRING_VECTOR_T & cCycleBuf::ValueVector (CONST_STRING_T col_name)
{
   return _Values[col_name];
}


// change buf

cChangeBuf::cCBEntry::cCBEntry()
      : _Aggregate(0), _Station(0)
{
}

cChangeBuf::cCBEntry::cCBEntry(const cChangeBuf::cCBEntry &right)
      : _Aggregate(0), _Station(0)
{
   _Name = right._Name;
   _OldValue = right._OldValue;
   _NewValue = right._NewValue;
   _TimeStamp = right._TimeStamp;
   _Aggregate = right._Aggregate;
   _Station = right._Station;
}

cChangeBuf::cCBEntry::~cCBEntry()
{
}

const cChangeBuf::cCBEntry & cChangeBuf::cCBEntry::operator=(const cChangeBuf::cCBEntry &right)
{
   _Name = right._Name;
   _OldValue = right._OldValue;
   _NewValue = right._NewValue;
   _TimeStamp = right._TimeStamp;
   _Aggregate = right._Aggregate;
   _Station = right._Station;
   return right;
}


cChangeBuf::cChangeBuf()
{
}

cChangeBuf::cChangeBuf(const cChangeBuf &right)
{
_ASSERT_UNCOND
}

cChangeBuf::~cChangeBuf()
{
}

ULONG_T cChangeBuf::Entries ()
{
   return _Entries.size();
}

cTimeObject cChangeBuf::TimeStamp (UINT_T entry)
{
   return _Entries[entry]._TimeStamp;
}

STRING_T cChangeBuf::KeyValue (UINT_T entry)
{
   return _Entries[entry]._KeyValue;
}

STRING_T cChangeBuf::Name (UINT_T entry)
{
   return _Entries[entry]._Name;
}

STRING_T cChangeBuf::OldValue (UINT_T entry)
{
   return _Entries[entry]._OldValue;
}

STRING_T cChangeBuf::NewValue (UINT_T entry)
{
   return _Entries[entry]._NewValue;
}

UINT_T cChangeBuf::Station (UINT_T entry)
{
   return _Entries[entry]._Station;
}

UINT_T cChangeBuf::Aggregate (UINT_T entry)
{
   return _Entries[entry]._Aggregate;
}

void cChangeBuf::SetTimeStamp (ULONG_T entry, cTimeObject &value)
{
   Resize(entry);
   _Entries[entry]._TimeStamp = value;
}

void cChangeBuf::SetKeyValue (ULONG_T entry, CONST_STRING_T value)
{
   Resize(entry);
   _Entries[entry]._KeyValue = value;
}

void cChangeBuf::SetName (ULONG_T entry, CONST_STRING_T value)
{
   Resize(entry);
   _Entries[entry]._Name = value;
}

void cChangeBuf::SetOldValue (ULONG_T entry, CONST_STRING_T value)
{
   Resize(entry);
   _Entries[entry]._OldValue = value;
}

void cChangeBuf::SetNewValue (ULONG_T entry, CONST_STRING_T value)
{
   Resize(entry);
   _Entries[entry]._NewValue = value;
}

void cChangeBuf::SetStation (ULONG_T entry, UINT_T value)
{
   Resize(entry);
   _Entries[entry]._Station = value;
}

void cChangeBuf::SetAggregate (ULONG_T entry, UINT_T value)
{
   Resize(entry);
   _Entries[entry]._Aggregate = value;
}

void cChangeBuf::Resize (UINT_T entry)
{
   if (_Entries.size() <= entry) {
      _Entries.resize(entry+1);
   }
}

// error buf

cErrorBuf::cEBEntry::cEBEntry()
      : _Start(true), _Shot(0)
{
}

cErrorBuf::cEBEntry::cEBEntry(const cErrorBuf::cEBEntry &right)
      : _Start(true), _Shot(0)
{
   _ErrorId = right._ErrorId;
   _Start = right._Start;
   _TimeStamp = right._TimeStamp;
   _Shot = right._Shot;
}

cErrorBuf::cEBEntry::~cEBEntry()
{
}

const cErrorBuf::cEBEntry & cErrorBuf::cEBEntry::operator=(const cErrorBuf::cEBEntry &right)
{
   _ErrorId = right._ErrorId;
   _Start = right._Start;
   _TimeStamp = right._TimeStamp;
   _Shot = right._Shot;
   return right;
}

cErrorBuf::cErrorBuf()
{
}

cErrorBuf::cErrorBuf(const cErrorBuf &right)
{
_ASSERT_UNCOND
}


cErrorBuf::~cErrorBuf()
{
}

ULONG_T cErrorBuf::Entries ()
{
   return _Entries.size();
}

cTimeObject cErrorBuf::TimeStamp (UINT_T entry)
{
   return _Entries[entry]._TimeStamp;
}

STRING_T cErrorBuf::KeyValue (UINT_T entry)
{
   return _Entries[entry]._KeyValue;
}

STRING_T cErrorBuf::ErrorId (UINT_T entry)
{
   return _Entries[entry]._ErrorId;
}

BOOL_T cErrorBuf::Start (UINT_T entry)
{
   return _Entries[entry]._Start;
}

LONG_T cErrorBuf::Shot (UINT_T entry)
{
   return _Entries[entry]._Shot;
}

void cErrorBuf::SetTimeStamp (ULONG_T entry, cTimeObject &value)
{
   Resize(entry);
   _Entries[entry]._TimeStamp = value;
}

void cErrorBuf::SetKeyValue (ULONG_T entry, CONST_STRING_T value)
{
   Resize(entry);
   _Entries[entry]._KeyValue = value;
}

void cErrorBuf::SetErrorId (ULONG_T entry, CONST_STRING_T value)
{
   Resize(entry);
   _Entries[entry]._ErrorId = value;
}

void cErrorBuf::SetStart (ULONG_T entry, BOOL_T value)
{
   Resize(entry);
   _Entries[entry]._Start = value;
}

void cErrorBuf::SetShot (ULONG_T entry, LONG_T value)
{
   Resize(entry);
   _Entries[entry]._Shot = value;
}

void cErrorBuf::Resize (UINT_T entry)
{
   if (_Entries.size() <= entry) {
      _Entries.resize(entry+1);
   }
}

//## end module%3FCF50D0002E.additionalDeclarations


// Class cFM2Device 

















cFM2Device::cFM2Device()
  //## begin cFM2Device::cFM2Device%.hasinit preserve=no
      : _BaudRate(9600), _Parity(Even), _Handshake(NoHandshake), _CharLen(8), _StartBits(1), _StopBits(1), _BufSize(20000), _MachineState(NULL), _SerialChannel(NULL), _VariableCache(NULL), _StateCache(NULL)
  //## end cFM2Device::cFM2Device%.hasinit
  //## begin cFM2Device::cFM2Device%.initialization preserve=yes
  //## end cFM2Device::cFM2Device%.initialization
{
  //## begin cFM2Device::cFM2Device%.body preserve=yes
_ASSERT_UNCOND
  //## end cFM2Device::cFM2Device%.body
}

cFM2Device::cFM2Device(const cFM2Device &right)
  //## begin cFM2Device::cFM2Device%copy.hasinit preserve=no
      : _BaudRate(9600), _Parity(Even), _Handshake(NoHandshake), _CharLen(8), _StartBits(1), _StopBits(1), _BufSize(20000), _MachineState(NULL), _SerialChannel(NULL), _VariableCache(NULL), _StateCache(NULL)
  //## end cFM2Device::cFM2Device%copy.hasinit
  //## begin cFM2Device::cFM2Device%copy.initialization preserve=yes
  //## end cFM2Device::cFM2Device%copy.initialization
{
  //## begin cFM2Device::cFM2Device%copy.body preserve=yes
_ASSERT_UNCOND
  //## end cFM2Device::cFM2Device%copy.body
}

cFM2Device::cFM2Device (cConfigurationObject *config_obj, cCell *cell)
  //## begin cFM2Device::cFM2Device%1070879991.hasinit preserve=no
      : _BaudRate(9600), _Parity(Even), _Handshake(NoHandshake), _CharLen(8), _StartBits(1), _StopBits(1), _BufSize(20000), _MachineState(NULL), _SerialChannel(NULL), _VariableCache(NULL), _StateCache(NULL)
  //## end cFM2Device::cFM2Device%1070879991.hasinit
  //## begin cFM2Device::cFM2Device%1070879991.initialization preserve=yes
  , cDevice(config_obj, cell)
  //## end cFM2Device::cFM2Device%1070879991.initialization
{
  //## begin cFM2Device::cFM2Device%1070879991.body preserve=yes
   DELETE_OBJECT(cBitOperator, _BitOperator)
   _BitOperator = new cNullOperator;
   _VariableCache = new cStringCache(this, "variable");
   SetMemoryInfo("variable", 1, 0, 0, _VariableCache, NULL);
   _StateCache = new cStringCache(this, "mstate");
   SetMemoryInfo("mstate", 1, 0, 0, _StateCache, NULL);
   _TempBuf.Size(_BufSize);
   _InBuf.Size(_BufSize);
   _OutBuf.Size(_BufSize);
   _BaudRate = config_obj->PropertyValue("BaudRate", _BaudRate);
   _Parity = cSerialChannel::ParityType(config_obj->PropertyValue("Parity", "None").c_str());
   _Handshake = cSerialChannel::HandshakeType(config_obj->PropertyValue("Handshake", "None").c_str());
   _CharLen = (UCHAR_T)config_obj->PropertyValue("CharLen", (ULONG_T)_CharLen);
   _StartBits = (UCHAR_T)config_obj->PropertyValue("StartBits", (ULONG_T)_StartBits);
   _StopBits = (UCHAR_T)config_obj->PropertyValue("StopBits", (ULONG_T)_StopBits);
   cConfigurationObject * serial_channel_obj = config_obj->PropertyValue("SerialChannel", NULL_OBJECT);
   _SerialChannel = cSerialChannelFactory::CreateSerialChannel(serial_channel_obj);
   _SerialChannel->Open();
   _SerialChannel->SetBaudRate(_BaudRate);
   _SerialChannel->SetCharLen(_CharLen);
   _SerialChannel->SetStartBits(_StartBits);
   _SerialChannel->SetStopBits(_StopBits);
   _SerialChannel->SetParity(_Parity);
   _SetBuffer = config_obj->PropertyValue("SetBuffer", "CYX1A_.4|CYX1A_.11|CYX1A_.6");
  //## end cFM2Device::cFM2Device%1070879991.body
}


cFM2Device::~cFM2Device()
{
  //## begin cFM2Device::~cFM2Device%.body preserve=yes
   if (_CacheControl != NULL) {
      _CacheControl->Stop();
      DELETE_OBJECT(cCacheControl, _CacheControl)
   }
   if (_VariableCache != NULL) {
      DELETE_OBJECT(cCache, _VariableCache)
   }
   if (_StateCache != NULL) {
      DELETE_OBJECT(cCache, _StateCache)
   }
   if (_SerialChannel != NULL) {
      _SerialChannel->Close();
      DELETE_OBJECT(cSerialChannel, _SerialChannel)
   }
  //## end cFM2Device::~cFM2Device%.body
}



//## Other Operations (implementation)
void cFM2Device::Start ()
{
  //## begin cFM2Device::Start%1104923754.body preserve=yes
   if (_VariableCache != NULL) _VariableCache->Done();
   if (_StateCache != NULL) _StateCache->Done();
   _CacheControl = new cCacheControl(this);
   _CacheControl->SetCache(_VariableCache);
   _CacheControl->SetCache(_StateCache);
   _CacheControl->Start();
   _CacheControlId = _CacheControl->get_ThreadId();
  //## end cFM2Device::Start%1104923754.body
}

void cFM2Device::Stop ()
{
  //## begin cFM2Device::Stop%1104923755.body preserve=yes
   if (_CacheControl != NULL) {
      _CacheControl->Stop();
   }
  //## end cFM2Device::Stop%1104923755.body
}

void cFM2Device::Cache (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value)
{
  //## begin cFM2Device::Cache%1104923756.body preserve=yes
   cCache * cache = SelectCache(buf_spec);
   if (cache != NULL) {
      cache->Cache(name, size, refresh_type, refresh_value);
   }
  //## end cFM2Device::Cache%1104923756.body
}

void cFM2Device::Buffer (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T size)
{
  //## begin cFM2Device::Buffer%1104923757.body preserve=yes
   cCache * cache = SelectCache(buf_spec);
   if (cache != NULL) {
      cache->Buffer(name, size);
   }
  //## end cFM2Device::Buffer%1104923757.body
}

void cFM2Device::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T &value, ULONG_T flags)
{
  //## begin cFM2Device::Get%1104919503.body preserve=yes
   ULONG_T lval = 0;
   Get(buf_spec, name, lval, flags);
   value = (UCHAR_T)lval;
  //## end cFM2Device::Get%1104919503.body
}

void cFM2Device::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, USHORT_T &value, ULONG_T flags)
{
  //## begin cFM2Device::Get%1104919504.body preserve=yes
   ULONG_T lval = 0;
   Get(buf_spec, name, lval, flags);
   value = (USHORT_T)lval;
  //## end cFM2Device::Get%1104919504.body
}

void cFM2Device::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T &value, ULONG_T flags)
{
  //## begin cFM2Device::Get%1071681174.body preserve=yes
   STRING_T sval;
   Get(buf_spec, name, sval, flags);
   value = strtoul(sval.c_str(), NULL, 0);
  //## end cFM2Device::Get%1071681174.body
}

void cFM2Device::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, FLOAT_T &value, ULONG_T flags)
{
  //## begin cFM2Device::Get%1104919505.body preserve=yes
   DOUBLE_T dval = 0;
   Get(buf_spec, name, dval, flags);
   value = (FLOAT_T)dval;
  //## end cFM2Device::Get%1104919505.body
}

void cFM2Device::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, DOUBLE_T &value, ULONG_T flags)
{
  //## begin cFM2Device::Get%1104919506.body preserve=yes
   STRING_T sval;
   Get(buf_spec, name, sval, flags);
   value = atof(sval.c_str());
  //## end cFM2Device::Get%1104919506.body
}

void cFM2Device::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, STRING_T &value, ULONG_T flags)
{
  //## begin cFM2Device::Get%1071480836.body preserve=yes
   cObjectLock __lock__(&_DeviceMutex);
   memset(_StringBuffer, 0, sizeof(_StringBuffer));
   Read(buf_spec, name, sizeof(_StringBuffer), _StringBuffer, sizeof(_StringBuffer), flags);
   SetVarInfo(name, _StringBuffer);
   value = _StringBuffer;
  //## end cFM2Device::Get%1071480836.body
}

void cFM2Device::Get (CONST_STRING_T buf_spec, CONST_STRING_T name, WSTRING_T &value, ULONG_T flags)
{
  //## begin cFM2Device::Get%1104919507.body preserve=yes
  //## end cFM2Device::Get%1104919507.body
}

void cFM2Device::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T value, ULONG_T flags)
{
  //## begin cFM2Device::Set%1104919508.body preserve=yes
   Set(buf_spec, name, (ULONG_T)value, flags);
  //## end cFM2Device::Set%1104919508.body
}

void cFM2Device::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, USHORT_T value, ULONG_T flags)
{
  //## begin cFM2Device::Set%1104919509.body preserve=yes
   Set(buf_spec, name, (ULONG_T)value, flags);
  //## end cFM2Device::Set%1104919509.body
}

void cFM2Device::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T value, ULONG_T flags)
{
  //## begin cFM2Device::Set%1104919510.body preserve=yes
   char v[64] = {0};
   SafePrintf(v, sizeof(v), "%d", value);
   Set(buf_spec, name, v, flags);
  //## end cFM2Device::Set%1104919510.body
}

void cFM2Device::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, FLOAT_T value, ULONG_T flags)
{
  //## begin cFM2Device::Set%1104919511.body preserve=yes
   Set(buf_spec, name, (DOUBLE_T)value, flags);
  //## end cFM2Device::Set%1104919511.body
}

void cFM2Device::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, DOUBLE_T value, ULONG_T flags)
{
  //## begin cFM2Device::Set%1104919512.body preserve=yes
   char v[128] = {0};
   int precision = Precision(name);
   switch (precision) {
   case 0:
      SafePrintf(v, sizeof(v), "%.d", (ULONG_T)value);
      break;
   case 1:
      SafePrintf(v, sizeof(v), "%.1f", value);
      break;
   case 2:
      SafePrintf(v, sizeof(v), "%.2f", value);
      break;
   case 3:
      SafePrintf(v, sizeof(v), "%.3f", value);
      break;
   case 4:
      SafePrintf(v, sizeof(v), "%.4f", value);
      break;
   default:
      SafePrintf(v, sizeof(v), "%f", value);
   }
   Set(buf_spec, name, v);
  //## end cFM2Device::Set%1104919512.body
}

void cFM2Device::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, CONST_STRING_T value, ULONG_T flags)
{
  //## begin cFM2Device::Set%1104919513.body preserve=yes
   Write(buf_spec, name, strlen(value), (void*)value, flags);
  //## end cFM2Device::Set%1104919513.body
}

void cFM2Device::Set (CONST_STRING_T buf_spec, CONST_STRING_T name, CONST_WSTRING_T value, ULONG_T flags)
{
  //## begin cFM2Device::Set%1104919514.body preserve=yes
  //## end cFM2Device::Set%1104919514.body
}

void cFM2Device::Read (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
  //## begin cFM2Device::Read%1104919515.body preserve=yes
   if (strcmp(buf_spec, "mstate") == 0) {
      ReadState(buf_spec, name, len, buf, flags);
      return;
   }
   if (strcmp(buf_spec, "errorbuf") == 0) {
      ReadErrorBuf((char*)buf, buf_size);
      return;
   }
   if (!(flags && VF_DEVICE)) {
      cCache * cache = SelectCache(buf_spec);
      if (cache != NULL) {
         if (cache->Cached(name)) {
            cache->Read(name, buf_size, buf, buf_size);
            return;
         }
      }
   }
   if (!_Connected) {
      ULONG_T thread_id = cSystemUtils::ThreadId();
      if (thread_id != _CacheControlId) {
         cSystemUtils::Suspend(10);
         throw cError(DEVICE_NOT_CONNECTED, 0, _Name.c_str());
      }
   }
   cObjectLock __lock__(&_DeviceMutex);
   TV(name, (char*)buf, buf_size);
  //## end cFM2Device::Read%1104919515.body
}

void cFM2Device::Write (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T flags)
{
  //## begin cFM2Device::Write%1104919516.body preserve=yes
   if (!_Connected) {
      ULONG_T thread_id = cSystemUtils::ThreadId();
      if (thread_id != _CacheControlId) {
         cSystemUtils::Suspend(10);
         throw cError(DEVICE_NOT_CONNECTED, 0, _Name.c_str());
      }
   }
   cObjectLock __lock__(&_DeviceMutex);
   TV(name, (const char *)buf);
   cCache * cache = SelectCache(buf_spec);
   if (cache != NULL) {
      cache->Write(name, (const char *)buf);
   }
  //## end cFM2Device::Write%1104919516.body
}

void cFM2Device::MS (CHAR_T *inbuf, LONG_T buf_size)
{
  //## begin cFM2Device::MS%1071317839.body preserve=yes
   char cmd[CMD_BUF_SIZE] = "MS";
   int rcv_len = Transmit(cmd, strlen(cmd), _InBuf, _InBuf.Size());
   CopyReceiveBuffer(cmd, inbuf, buf_size, _InBuf, rcv_len);
  //## end cFM2Device::MS%1071317839.body
}

void cFM2Device::TB (CHAR_T *inbuf, LONG_T buf_size)
{
  //## begin cFM2Device::TB%1071317840.body preserve=yes
   char cmd[CMD_BUF_SIZE] = "TB 01";
	int rcv_len = Transmit(cmd, strlen(cmd), _InBuf, _InBuf.Size());
   CopyReceiveBuffer(cmd, inbuf, buf_size, _InBuf, rcv_len);
  //## end cFM2Device::TB%1071317840.body
}

void cFM2Device::UD (CHAR_T *inbuf, LONG_T buf_size)
{
  //## begin cFM2Device::UD%1071317841.body preserve=yes
   char cmd[CMD_BUF_SIZE] = "UD";
	int rcv_len = Transmit(cmd, strlen(cmd), _InBuf, _InBuf.Size());
   CopyReceiveBuffer(cmd, inbuf, buf_size, ((char *)_InBuf)+3, rcv_len);
  //## end cFM2Device::UD%1071317841.body
}

void cFM2Device::DD (CONST_STRING_T outbuf, LONG_T buf_size)
{
  //## begin cFM2Device::DD%1071317842.body preserve=yes
   SafePrintf(_OutBuf, _OutBuf.Size(), "DD %s", outbuf);
	int rcv_len = Transmit(_OutBuf, strlen(_OutBuf), _InBuf, _InBuf.Size());
   if (buf_size <= rcv_len) throw cError(DRIVER_RCV_BUF_TOO_SMALL, 0, _Name.c_str());
  //## end cFM2Device::DD%1071317842.body
}

void cFM2Device::EB (CHAR_T *inbuf, LONG_T buf_size)
{
  //## begin cFM2Device::EB%1071317843.body preserve=yes
   char cmd[CMD_BUF_SIZE] = "EB";
	int rcv_len = Transmit(cmd, strlen(cmd), _InBuf, _InBuf.Size());
   CopyReceiveBuffer(cmd, inbuf, buf_size, _InBuf, rcv_len);
  //## end cFM2Device::EB%1071317843.body
}

void cFM2Device::CB (CHAR_T *inbuf, LONG_T buf_size)
{
  //## begin cFM2Device::CB%1071317844.body preserve=yes
   char cmd[CMD_BUF_SIZE] = "CB";
	int rcv_len = Transmit(cmd, strlen(cmd), _InBuf, _InBuf.Size());
   CopyReceiveBuffer(cmd, inbuf, buf_size, _InBuf, rcv_len);
  //## end cFM2Device::CB%1071317844.body
}

void cFM2Device::TP (CONST_STRING_T page_no, CHAR_T *inbuf, LONG_T buf_size)
{
  //## begin cFM2Device::TP%1071317845.body preserve=yes
   SafePrintf(_OutBuf, _OutBuf.Size(), "TP %s", page_no);
	int rcv_len = Transmit(_OutBuf, strlen(_OutBuf), _InBuf, _InBuf.Size());
   CopyReceiveBuffer(_OutBuf, inbuf, buf_size, _InBuf, rcv_len);
  //## end cFM2Device::TP%1071317845.body
}

void cFM2Device::SB (CONST_STRING_T variables)
{
  //## begin cFM2Device::SB%1071317846.body preserve=yes
   SafePrintf(_OutBuf, _OutBuf.Size(), "SB %s", variables);
	int rcv_len = Transmit(_OutBuf, strlen(_OutBuf), _InBuf, _InBuf.Size());
  //## end cFM2Device::SB%1071317846.body
}

void cFM2Device::DB ()
{
  //## begin cFM2Device::DB%1071317847.body preserve=yes
   char cmd[CMD_BUF_SIZE] = "DB";
	int rcv_len = Transmit(cmd, strlen(cmd), _InBuf, _InBuf.Size());
  //## end cFM2Device::DB%1071317847.body
}

void cFM2Device::TV (CONST_STRING_T var_name, CONST_STRING_T value)
{
  //## begin cFM2Device::TV%1071317848.body preserve=yes
   SafePrintf(_OutBuf, _OutBuf.Size(), "TV %s %s", var_name, value);
   int rcv_len = Transmit(_OutBuf, strlen(_OutBuf), _InBuf, _InBuf.Size());
  //## end cFM2Device::TV%1071317848.body
}

void cFM2Device::TV (CONST_STRING_T var_name, CHAR_T *inbuf, LONG_T buf_size)
{
  //## begin cFM2Device::TV%1071317849.body preserve=yes
   SafePrintf(_OutBuf, _OutBuf.Size(), "TV %s", var_name);
   int rcv_len = Transmit(_OutBuf, strlen(_OutBuf), _InBuf, _InBuf.Size());
   CopyReceiveBuffer(_OutBuf, inbuf, buf_size, _InBuf, rcv_len, true);
  //## end cFM2Device::TV%1071317849.body
}

LONG_T cFM2Device::ReadBlock (CHAR_T *buffer, LONG_T buf_len)
{
  //## begin cFM2Device::ReadBlock%1071317850.body preserve=yes
#define STATE_CHANGE(state, new_state)    {state = new_state;}

	unsigned char c;
   unsigned short checksum = 0x0000;
   char read_checksum[7] = "0x0000";
   int state = START_TEXT;
   char * buf_ptr = buffer;
   int text_len = 0;
   long timeout = BLK_RESPONSE_TIMEOUT;

   STATE_CHANGE(state, START_TEXT)
   while (true) {
      if ((c = GetChar(timeout)) != READ_TIMEOUT) {
         timeout = INTER_CHAR_TIMEOUT;
         if (c == EOT) {
            return -FM_RCV_COMM_ABORTED;
         } else if (c == ETB) {
            return END_OF_MESSAGE;
         } else {
            switch (state) {
            case START_TEXT:
               if (c == STX) {
                  STATE_CHANGE(state, TEXT_BODY)
               }
               break;
            case TEXT_BODY:
               if (c == CR) {
                  STATE_CHANGE(state, EXPECT_LF)
               } else {
                  *buf_ptr++ = (char)c;
                  text_len++;
                  if (text_len == buf_len) {
                     return -DRIVER_RCV_BUF_TOO_SMALL;
                  }
               }
               checksum += c;
               break;
            case EXPECT_LF:
               if (c == LF) {
                  checksum += c;
                  STATE_CHANGE(state, CHECKSUM_0)
               } else {
                  return -FM_CR_LF_ERROR;
               }
               break;
            case CHECKSUM_0:
               checksum = 0xFFFF - checksum;
               read_checksum[2] = c;
               STATE_CHANGE(state, CHECKSUM_1)
               break;
            case CHECKSUM_1:
               read_checksum[3] = c;
               STATE_CHANGE(state, CHECKSUM_2)
               break;
            case CHECKSUM_2:
               read_checksum[4] = c;
               STATE_CHANGE(state, CHECKSUM_3)
               break;
            case CHECKSUM_3:
               read_checksum[5] = c;
               STATE_CHANGE(state, EXPECT_ETX)
               break;
            case EXPECT_ETX:
               if (c == ETX) {
                  unsigned short hex_checksum = 0;
                  hex_checksum = (unsigned short)strtoul(read_checksum, NULL, 16);
                  if (hex_checksum != checksum) {
                     return -FM_CHECKSUM_ERROR;
                  } else {
                     *buf_ptr = '\0';
                     return text_len;
                  }
               } else {
                  return -FM_MISSING_ETX;
               }
               break;
            }
         }
      } else {
         return -FM_RCV_CHAR_TIMEOUT;
      }
   }
  //## end cFM2Device::ReadBlock%1071317850.body
}

void cFM2Device::WriteBlock (CONST_STRING_T buffer, LONG_T len)
{
  //## begin cFM2Device::WriteBlock%1071317851.body preserve=yes
_ASSERT_COND(_SerialChannel != NULL)
	int i;
   unsigned short checksum = 0x0000;
   char write_checksum[5] = {0};
   char out_buffer[MAX_BLK_LEN + BLK_OVERHEAD];
   char * outbuf_ptr = out_buffer;
   int out_len = 0;
   char c;

   *outbuf_ptr++ = STX;
   out_len++;
   for (i=0; i<len; i++) {
      c = buffer[i];
      checksum += c;
      *outbuf_ptr++ = c;
      out_len++;
   }
   checksum += CR;
   *outbuf_ptr++ = CR;
   out_len++;
   checksum += LF;
   *outbuf_ptr++ = LF;
   out_len++;
   checksum = 0xFFFF - checksum;
   SafePrintf(write_checksum, sizeof(write_checksum), "%04x", checksum);
   strupr(write_checksum);
   for (i=0; i<4; i++) {
      *outbuf_ptr++ = write_checksum[i];
      out_len++;
	}
   *outbuf_ptr++ = ETX;
   out_len++;
	_SerialChannel->Write((unsigned char *)out_buffer, out_len);
   out_buffer[out_len] = '\0';
  //## end cFM2Device::WriteBlock%1071317851.body
}

LONG_T cFM2Device::MasterTransmission (CONST_STRING_T cmd, LONG_T cmd_len, CHAR_T *rcv_buf, LONG_T buf_len)
{
  //## begin cFM2Device::MasterTransmission%1071317852.body preserve=yes
#define STATE2_CHANGE(state, new_state)   {/*printf("%d->", state);*/\
                                           /*printf("%d\n", new_state);*/\
                                           state = new_state;}
#define ABORT_IF_TIMED_OUT

   int bytes_to_write;
   const char * blk1_ptr = NULL, * blk3_ptr = NULL;
   char * rcv_ptr = NULL;
   int blk1_len = 0, blk3_len = 0;
   char cmd_buf[8] = {0};
   char blk_buf[256];
   bool blk_rcv = false;
   int rcv_len = 0;
   int state = 1;
   int retries = 0;
   unsigned char c = 0;
   int nread = 0;
   int rc = 0;
   long timeout = CHAR_TIMEOUT;
   int command_type = CommandType(cmd);

      switch (command_type) {
      case COMMAND_TYPE_1:
         blk1_ptr = cmd;
         blk1_len = cmd_len;
         break;
      case COMMAND_TYPE_2:
         memcpy(cmd_buf, cmd, 2);
         blk1_ptr = cmd_buf;
         blk1_len = 2;
         blk3_ptr = &cmd[3];
         bytes_to_write = cmd_len - 3;
         if (bytes_to_write > MAX_BLK_LEN) {
            blk3_len = MAX_BLK_LEN;
            bytes_to_write -= MAX_BLK_LEN;
         } else {
            blk3_len = bytes_to_write;
            bytes_to_write = 0;
         }
         break;
      case COMMAND_TYPE_3:
         blk1_ptr = cmd;
         blk1_len = cmd_len;
         break;
      }
      rcv_ptr = rcv_buf, rcv_len = 0;
      retries = 0;
      while (true) {
         switch (state) {
         case 0:
            SendChar(EOT);
            STATE2_CHANGE(state,1)
            if (rc != 0) {
//               return rc;
               return -rc;
            } else {
               return rcv_len;
		      }
            break;
         case 1:
            SendChar(EOT);
            SendChar(ENQ);
            STATE2_CHANGE(state,3)
            break;
         case 2:
            retries++;
            SendChar(EOT);
            STATE2_CHANGE(state,1)
            break;
         case 3:
            if (retries > MAX_RETRIES) {
                rc = FM_CONTACT_RETRIES;
                STATE2_CHANGE(state,0)
            } else {
               retries++;
               if ((c = GetChar(timeout)) == READ_TIMEOUT) {
                  STATE2_CHANGE(state,2)
               } else if (c == ACK) {
                  STATE2_CHANGE(state,4)
               } else {
                  STATE2_CHANGE(state,2)
               }
            }
            break;
         case 4:
            retries = 0;
            WriteBlock(blk1_ptr, blk1_len);
            STATE2_CHANGE(state,5);
            break;
         case 5:
            if (retries > MAX_RETRIES) {
               rc = FM_BLK_RETRIES_1;
               STATE2_CHANGE(state,0)
            } else {
               if ((c = GetChar(timeout)) == 0) {
                  rc = FM_CHAR_TIMEOUT_5;
                  STATE2_CHANGE(state,0)
               } else if (c == ACK) {
                  STATE2_CHANGE(state,7)
               } else if (c == NAK) {
                  STATE2_CHANGE(state,6)
               } else {
                  rc = FM_UNDEF_CHAR_5;
                  STATE2_CHANGE(state,0)
               }
            }
            break;
         case 6:
            retries++;
            WriteBlock(blk1_ptr, blk1_len);
            STATE2_CHANGE(state,5);
            break;
         case 7:
            retries = 0;
            if ((nread = ReadBlock(blk_buf, sizeof(blk_buf))) < 0) {
#ifdef ABORT_IF_TIMED_OUT
               rc = nread;
               STATE2_CHANGE(state,0)
#else
               blk_rcv = false;
               STATE2_CHANGE(state,8)
#endif
            } else {
               TestReceiveBuffer(blk_buf, cmd);
               int space = (buf_len - rcv_len);
               if (space < nread) {
                  rc = DRIVER_RCV_BUF_TOO_SMALL;
                  memcpy(rcv_ptr, blk_buf, space);
                  rcv_ptr += space;
                  rcv_len += space;
               } else {
                  memcpy(rcv_ptr, blk_buf, nread);
                  rcv_ptr += nread;
                  rcv_len += nread;
               }
               blk_rcv = true;
               STATE2_CHANGE(state,8)
            }
            break;
         case 8:
            if (blk_rcv) {
               SendChar(ACK);
               switch (command_type) {
               case COMMAND_TYPE_1:
                  STATE2_CHANGE(state,10)
                  break;
               case COMMAND_TYPE_2:
                  STATE2_CHANGE(state,11)
                  break;
               case COMMAND_TYPE_3:
                  STATE2_CHANGE(state,12)
                  break;
               }
            } else {
               SendChar(NAK);
               STATE2_CHANGE(state,9)
            }
            break;
         case 9:
            if (retries > MAX_RETRIES) {
               rc = FM_BLK_RETRIES_2;
               STATE2_CHANGE(state,0)
            } else {
              retries++;
               if ((nread = ReadBlock(blk_buf, sizeof(blk_buf))) < 0) {
#ifdef ABORT_IF_TIMED_OUT
                  rc = nread;
                  STATE2_CHANGE(state,0)
#else
                  blk_rcv = false;
#endif
               } else {
                  int space = (buf_len - rcv_len);
                  if (space < nread) {
                     rc = DRIVER_RCV_BUF_TOO_SMALL;
                     memcpy(rcv_ptr, blk_buf, space);
                     rcv_ptr += space;
                     rcv_len += space;
                  } else {
                     memcpy(rcv_ptr, blk_buf, nread);
                     rcv_ptr += nread;
                     rcv_len += nread;
                  }
                  blk_rcv = true;
                  STATE2_CHANGE(state,8)
               }
            }
            break;
         case 10:
            if ((c = GetChar(timeout)) == READ_TIMEOUT) {
               rc = FM_CHAR_TIMEOUT_10;
               STATE2_CHANGE(state,0)
            } else if (c == ETB) {
               STATE2_CHANGE(state,0)
            } else {
               rc = FM_UNDEF_CHAR_10;
               STATE2_CHANGE(state,0)
            }
            break;
         case 11:
            if (blk3_ptr) {
               retries = 0;
               WriteBlock(blk3_ptr, blk3_len);
               STATE2_CHANGE(state,13);
            } else {

// This wait will enable IQT 350 terminals to get the SB command right.
// if this Suspend is missing nothing will happen (no error or anything else),
// but the command will not be executed by the terminal.
//

               cSystemUtils::Suspend(100);
               SendChar(ETB);
               STATE2_CHANGE(state,15)
            }
            break;
         case 12:
            retries = 0;
            if ((nread = ReadBlock(blk_buf, sizeof(blk_buf))) < 0) {
               if (nread == END_OF_MESSAGE) {
                  STATE2_CHANGE(state,19)
               } else {
#ifdef ABORT_IF_TIMED_OUT
                  rc = nread;
                  STATE2_CHANGE(state,0)
#else
                  blk_rcv = false;
                  STATE2_CHANGE(state,17)
#endif
               }
            } else {
               int space = (buf_len - rcv_len);
               if (space < nread) {
                  rc = DRIVER_RCV_BUF_TOO_SMALL;
                  memcpy(rcv_ptr, blk_buf, space);
                  rcv_ptr += space;
                  rcv_len += space;
               } else {
                  memcpy(rcv_ptr, blk_buf, nread);
                  rcv_ptr += nread;
                  rcv_len += nread;
               }
               blk_rcv = true;
               STATE2_CHANGE(state,17)
            }
            break;
         case 13:
            if (retries > MAX_RETRIES) {
               rc = FM_BLK_RETRIES_3;
               STATE2_CHANGE(state,0)
            } else {
               if ((c = GetChar(timeout)) == READ_TIMEOUT) {
                  STATE2_CHANGE(state,0)
               } else if (c == ACK) {
                  if (bytes_to_write == 0) {
                     blk3_ptr = NULL;
                     blk3_len = 0;
                  } else if (bytes_to_write <= MAX_BLK_LEN) {
                     blk3_ptr += blk3_len;
                     blk3_len = bytes_to_write;
                     bytes_to_write = 0;
                  } else {
                     blk3_ptr += MAX_BLK_LEN;
                     blk3_len = MAX_BLK_LEN;
                     bytes_to_write -= MAX_BLK_LEN;
                  }
                  STATE2_CHANGE(state,11)
               } else if (c == NAK) {
                  STATE2_CHANGE(state,14)
               } else {
                  rc = FM_UNDEF_CHAR_13;
                  STATE2_CHANGE(state,0)
               }
            }
            break;
         case 14:
            retries++;
            WriteBlock(blk3_ptr, blk3_len);
            STATE2_CHANGE(state,13);
            break;
         case 15:
            if ((c = GetChar(timeout)) == READ_TIMEOUT) {
               rc = FM_CHAR_TIMEOUT_15;
               STATE2_CHANGE(state,0)
            } else if (c == ACK) {
               STATE2_CHANGE(state,16)
            } else {
               rc = FM_UNDEF_CHAR_15;
               STATE2_CHANGE(state,0)
            }
            break;
         case 16:
            STATE2_CHANGE(state,0)
            break;
         case 17:
            if (retries > MAX_RETRIES) {
               rc = FM_BLK_RETRIES_4;
               STATE2_CHANGE(state,0)
            } else {
               if (blk_rcv) {
                  SendChar(ACK);
                  STATE2_CHANGE(state,12)
               } else {
                  SendChar(NAK);
                  STATE2_CHANGE(state,18)
               }
            }
            break;
         case 18:
            retries++;
            if ((nread = ReadBlock(blk_buf, sizeof(blk_buf))) < 0) {
#ifdef ABORT_IF_TIMED_OUT
               rc = nread;
               STATE2_CHANGE(state,0)
#else
               blk_rcv = false;
               STATE2_CHANGE(state,17)
#endif
            } else {
               int space = (buf_len - rcv_len);
               if (space < nread) {
                  rc = DRIVER_RCV_BUF_TOO_SMALL;
                  memcpy(rcv_ptr, blk_buf, space);
                  rcv_ptr += space;
                  rcv_len += space;
               } else {
                  memcpy(rcv_ptr, blk_buf, nread);
                  rcv_ptr += nread;
                  rcv_len += nread;
               }
               blk_rcv = true;
               STATE2_CHANGE(state,17)
            }
            break;
         case 19:
            STATE2_CHANGE(state,0)
            break;
         default:
_ASSERT_UNCOND
         }
       }
_ASSERT_UNCOND
  //## end cFM2Device::MasterTransmission%1071317852.body
}

INT_T cFM2Device::Transmit (CONST_STRING_T cmd_buf, LONG_T cmd_len, CHAR_T *rcv_buf, LONG_T buf_len)
{
  //## begin cFM2Device::Transmit%1071317853.body preserve=yes
   long nread, rc;
   _SerialChannel->FlushInput();
   if ((nread = MasterTransmission(cmd_buf, cmd_len, rcv_buf, buf_len)) < 0) {
      int err_code = -nread;
      if (err_code == FM_CONTACT_RETRIES) {
         if (_Connected) {
            _Connected = false;
            cAlarm * alarm = new cAlarm(this, 0x00000001, true, NOT_CONNECTED);
            alarm->set_Param1(_Name);
            alarm->set_Severity(SevError);
            RaiseEvent(alarm);
            alarm->Release();
         }
      }
      throw cError(err_code, 0, _Name.c_str());
   } else {
      if (!_Connected) {
         _Connected = true;
         cAlarm * alarm = new cAlarm(this, 0x00000001, false);
         RaiseEvent(alarm);
         alarm->Release();
      }
      TestReceiveBuffer(rcv_buf, cmd_buf);
      return nread;
   }
  //## end cFM2Device::Transmit%1071317853.body
}

void cFM2Device::TestReceiveBuffer (CONST_STRING_T receive_buf, CONST_STRING_T request_buf)
{
  //## begin cFM2Device::TestReceiveBuffer%1071317854.body preserve=yes
   if (receive_buf[0] == 'E' && receive_buf[1] == 'R') {
      char err_string[3] = {0};
      char request[64] = {0};
      memcpy(err_string, receive_buf + 3, 2);
      int len = _MIN_(sizeof(request)-5, strlen(request_buf));
      memcpy(request, request_buf, len);
      throw cError(FM_MACHINE_ERROR, 0, _Name.c_str(), err_string, request);
   }
  //## end cFM2Device::TestReceiveBuffer%1071317854.body
}

void cFM2Device::CopyReceiveBuffer (CONST_STRING_T cmd, CHAR_T *dst_buf, INT_T dst_buf_len, CHAR_T *rcv_buf, INT_T rcv_len, bool skip_echo)
{
  //## begin cFM2Device::CopyReceiveBuffer%1071317855.body preserve=yes
   if (skip_echo) {
      int echo_len = strlen(cmd) + 1;
      if (echo_len >= rcv_len) {
     		throw cError(FM_ECHO, 0, _Name.c_str());
      } else {
         int cpy_len = rcv_len - echo_len;
         char * cpy_ptr = &rcv_buf[echo_len];
         if (dst_buf_len <= cpy_len) {
        		throw cError(DRIVER_RCV_BUF_TOO_SMALL, 0, _Name.c_str());
         } else {
            memcpy(dst_buf, cpy_ptr, cpy_len);
            dst_buf[cpy_len] = '\0';
         }
      }
   } else {
      if (dst_buf_len <= rcv_len) {
     		throw cError(DRIVER_RCV_BUF_TOO_SMALL, 0, _Name.c_str());
      } else {
         memcpy(dst_buf, rcv_buf, rcv_len);
         dst_buf[rcv_len] = '\0';
      }
   }
  //## end cFM2Device::CopyReceiveBuffer%1071317855.body
}

UCHAR_T cFM2Device::GetChar (LONG_T timeout)
{
  //## begin cFM2Device::GetChar%1071317856.body preserve=yes
_ASSERT_COND(_SerialChannel != NULL)
   unsigned char c = 0x00;
	if (_SerialChannel->Read(&c, 1, timeout) != 1) {
		return READ_TIMEOUT;
   }
   if (c == EOT) {
      throw cCommAborted();
   } else if (c == 0x01) {
      throw cCommAborted();
   } else {
      return c;
   }
  //## end cFM2Device::GetChar%1071317856.body
}

void cFM2Device::SendChar (UCHAR_T c)
{
  //## begin cFM2Device::SendChar%1071317857.body preserve=yes
_ASSERT_COND(_SerialChannel != NULL)
   _SerialChannel->Write(&c, 1);
  //## end cFM2Device::SendChar%1071317857.body
}

cMachineState * cFM2Device::ParseMS (CONST_STRING_T ms)
{
  //## begin cFM2Device::ParseMS%1071317858.body preserve=yes
   cMachineState * machine_state = new cMachineState;
   unsigned int _word[17] = {0};
   unsigned short word[17] = {0};
   machine_state->set_Connected(true);
   if (sscanf(ms, "MS %02x %02x %02d %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
              &_word[1],
              &_word[2],
              &_word[3],
              &_word[4],
              &_word[5],
              &_word[6],
              &_word[7],
              &_word[8],
              &_word[9],
              &_word[10],
              &_word[11],
              &_word[12],
              &_word[13],
              &_word[14],
              &_word[15],
              &_word[16]) == 16) {
   } else if (sscanf(ms, "MS %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
                  &_word[1],
                  &_word[2],
                  &_word[3],
                  &_word[4],
                  &_word[5],
                  &_word[6],
                  &_word[7],
                  &_word[8],
                  &_word[9],
                  &_word[10],
                  &_word[11],
                  &_word[12],
                  &_word[13],
                  &_word[14],
                  &_word[15],
                  &_word[16]) == 16) {
   } else {
      delete machine_state;
  		throw cError(FM_MS_SYNTAX, 0, _Name.c_str(), ms);
   }
   int i = 0;
   for (i=0; i<17; i++) {
      word[i] = (unsigned short)_word[i];
   }
   machine_state->set_ErrorsPending(word[1]);
   machine_state->set_Step(word[2]);
   if (word[3] != 0xFF && word[3] != 0) {
      if (word[3] == 0xFF) {
         machine_state->set_DataPending(-1);
      } else {
         machine_state->set_DataPending(word[3]);
      }
   }
   if (word[4] != 0) {
      if (word[4] == 1) {
         machine_state->set_UploadEnabled(true);
      } else {
         machine_state->set_DownloadEnabled(true);
      }
   }
   machine_state->set_ChangesPending(word[5]);
   switch (word[6]) {
   case 0: machine_state->set_ProductionState(SH_STOPPED); break;
   case 1: machine_state->set_ProductionState(SH_SETUP); break;
   case 2: machine_state->set_ProductionState(SH_MANUAL); break;
   case 3: machine_state->set_ProductionState(SH_SEMI_AUTOMATIC); break;
   case 4: machine_state->set_ProductionState(SH_AUTOMATIC); break;
   default: machine_state->set_ProductionState(UNDEFINED); break;
   }
   if (word[7] != 0) {
      if (word[7] == 1) {
         machine_state->set_ProductionTerminated(true);
      } else if (word[7] == 2) {
         machine_state->set_StopRequest(true);
      } else if (word[7] == 3) {
         machine_state->set_AbortRequest(true);
      }
   }
   // word[8] application specific
   // word[9] no interest
#define xxx(w) (w)
   if (word[10] != 0) {
      machine_state->set_MachineState(xxx(word[10]));
   }
   // word[11] application specific
   if (word[12] == 2) {
      machine_state->set_DownloadFailed(true);
   }
   if (word[13] != 0) {
      if (word[13] == 0xFF) {
         machine_state->set_ConfigState(SH_NOT_CONFIGURED);
      } else {
         machine_state->set_ConfigState(word[13]);
      }
   } else {
      machine_state->set_ConfigState(SH_CONFIGURED);
   }
   if (word[14] != 0) {
      machine_state->set_StartRequest(true);
   }
   return machine_state;
  //## end cFM2Device::ParseMS%1071317858.body
}

cCycleBuf * cFM2Device::ParseTB (CONST_STRING_T tb)
{
  //## begin cFM2Device::ParseTB%1071317859.body preserve=yes
#define WHITE_SPACES " |"
   try {
      cCycleBuf * cycle_buf = new cCycleBuf;
      STRING_T current_name;
      int pos = -1, entry = -1;
      const char * token = NULL;
      char * buf_ptr = (char*)tb;
      if (strncmp(tb, "TB 01", 4) == 0) {
         buf_ptr = (char*)(tb + 6);
      } else {
         delete cycle_buf;
         throw cError(FM_ECHO, 0, _Name.c_str(), tb);
      }
      cTokenizer tokenizer(buf_ptr, strlen(buf_ptr));
      token = tokenizer.GetToken(WHITE_SPACES);
      while (token) {
         if (isdigit(token[0]) || token[0] == '-') {
            entry++;
            cycle_buf->SetValue(current_name.c_str(), entry, token);
         } else if (isalpha(token[0])) {
            pos++;
            entry = -1;
            current_name = token;
            cycle_buf->AddColumn(token);
         } else {
            delete cycle_buf;
            throw cError(FM_TB_SYNTAX, 0, _Name.c_str(), tb);
         }
         token = tokenizer.GetToken(WHITE_SPACES);
      }
      return cycle_buf;
   } catch (...) {
      throw cError(FM_TB_ERROR, 0, _Name.c_str(), tb);
   }
  //## end cFM2Device::ParseTB%1071317859.body
}

cChangeBuf * cFM2Device::ParseCB (CONST_STRING_T cb)
{
  //## begin cFM2Device::ParseCB%1071317860.body preserve=yes
   try {
      cTimeObject time;
      time.Now();
      cChangeBuf * change_buf = new cChangeBuf;
      int year = time.Get(cTimeObject::YEAR),
          month = time.Get(cTimeObject::MONTH),
          day = time.Get(cTimeObject::DAY),
          hour = 0, minute = 0, second = 0;
      char token_buf[512];
      int entry = -1;
      const char * token = NULL;
      char * buf_ptr = (char*)cb;
      if (strncmp(cb, "CB", 2) == 0) {
         buf_ptr = (char*)(cb + 3);
      } else {
         delete change_buf;
         throw cError(FM_ECHO, 0, _Name.c_str(), cb);
      }
      cTokenizer tokenizer(buf_ptr, strlen(buf_ptr));
      token = tokenizer.GetToken(" ");
      while (token) {
         // station
         if (isdigit(token[0])) {
            entry++;
            change_buf->SetStation(entry, strtoul(token, NULL, 0));
         } else {
            delete change_buf;
            throw cError(FM_CB_SYNTAX, 0, _Name.c_str(), cb);
         }
         // aggregate
         token = tokenizer.GetToken(" ");
         if (token == NULL) {
            delete change_buf;
            throw cError(FM_CB_SYNTAX, 0, _Name.c_str(), cb);
         }
         if (isdigit(token[0])) {
            change_buf->SetAggregate(entry, strtoul(token, NULL, 0));
         } else {
            delete change_buf;
            throw cError(FM_CB_SYNTAX, 0, _Name.c_str(), cb);
         }
         // name
         token = tokenizer.GetToken(" ");
         if (token == NULL) {
            delete change_buf;
            throw cError(FM_CB_SYNTAX, 0, _Name.c_str(), cb);
         }
         const char * name = cStringUtils::Trim(token, token_buf, sizeof(token_buf));
         if (name != NULL) {
            change_buf->SetName(entry, name);
         }
         // old value
         token = tokenizer.GetToken("\\");
         if (token == NULL) {
            delete change_buf;
            throw cError(FM_CB_SYNTAX, 0, _Name.c_str(), cb);
         }
//      const char * old_value = cStringUtils::Trim(token, token_buf, sizeof(token_buf));
         const char * old_value = token;
         if (old_value != NULL) {
            change_buf->SetOldValue(entry, old_value);
         }
         // new value and time
         token = tokenizer.GetToken("|");
         if (token == NULL) {
            delete change_buf;
            throw cError(FM_CB_SYNTAX, 0, _Name.c_str(), cb);
         }
         int value_len = strlen(token) - 5;
         if (value_len < 0) {
            delete change_buf;
            throw cError(FM_CB_SYNTAX, 0, _Name.c_str(), cb);
         }
         const char * time_ptr = token + value_len;
         char * eov = (char*)time_ptr - 1;
         *eov = '\0';
         if (sscanf(time_ptr, "%02d:%02d", &hour, &minute) == 2) {
//         const char * new_value = cStringUtils::Trim(token, token_buf, sizeof(token_buf));
            const char * new_value = token;
            change_buf->SetNewValue(entry, new_value);
         } else {
            delete change_buf;
            throw cError(FM_CB_SYNTAX, 0, _Name.c_str(), cb);
         }
         time.Set(cTimeObject::HOUR, hour);
         time.Set(cTimeObject::MINUTE, minute);
         change_buf->SetTimeStamp(entry, time);
         // next entry
         token = tokenizer.GetToken(" ");
      }
      return change_buf;
   } catch (...) {
      throw cError(FM_CB_ERROR, 0, _Name.c_str(), cb);
   }
  //## end cFM2Device::ParseCB%1071317860.body
}

cErrorBuf * cFM2Device::ParseEB (CONST_STRING_T eb)
{
  //## begin cFM2Device::ParseEB%1071317861.body preserve=yes
   try {
      cTimeObject time;
      time.Now();
      int year = time.Get(cTimeObject::YEAR),
          month = time.Get(cTimeObject::MONTH),
          day = time.Get(cTimeObject::DAY),
          hour = 0, minute = 0, second = 0;
      long shot = 0;
      long date = 0;
      BOOL_T start = true;
      char err_type[32] = {0};
      char err_code[32] = {0};
      cErrorBuf * error_buf = new cErrorBuf;
      cTokenizer tokenizer(eb, strlen(eb));
      const char * token = NULL;
      if ((token = tokenizer.GetToken("|")) == NULL) {
         delete error_buf;
         throw cError(FM_EB_SYNTAX, 0, _Name.c_str(), eb);
      } else {
         if (strcmp(token, "EB") != 0) {
            delete error_buf;
            throw cError(FM_ECHO, 0, _Name.c_str(), eb);
         }
      }
//EB|****** **:**:** EL01 0950 0000000 011006 15:46:36|****** **:**:** EL01 0951 0000000 011006 15:46:36|011006 15:46:38 EL01 0952 0000000 ****** **:**:**|011006 15:46:38 EL01 0953 0000000 ****** **:**:**
      int entry = 0;
      while ((token = tokenizer.GetToken("|")) != NULL) {
         int params = 0;
         if ((params = sscanf(token,
                    "****** **:**:** %s %s %ld %ld %d:%d:%d",
                    err_type, err_code, &shot,
                    &date, &hour, &minute, &second)) == 7) {
            start = false;
            year += 2000;
         } else if ((params = sscanf(token,
                    "%ld %d:%d:%d %s %s %ld ****** **:**:**",
                    &date, &hour, &minute, &second,
                    err_type, err_code, &shot)) == 7) {
            start = true;
            year += 2000;
         } else {
            delete error_buf;
            throw cError(FM_EB_SYNTAX, 0, _Name.c_str(), eb);
         }
         char error_id[32] = {0};
         SafePrintf(error_id, sizeof(error_id), "%s%s", err_type, err_code);
         year = (date / (10000)) + 2000;
         month = (date % (10000)) / 100;
         day = date % (100);
         time.Set(cTimeObject::YEAR, year);
         time.Set(cTimeObject::MONTH, month);
         time.Set(cTimeObject::DAY, day);
         time.Set(cTimeObject::HOUR, hour);
         time.Set(cTimeObject::MINUTE, minute);
         time.Set(cTimeObject::SECOND, second);
         error_buf->SetTimeStamp(entry, time);
         error_buf->SetShot(entry, shot);
         error_buf->SetErrorId(entry, error_id);
         error_buf->SetStart(entry, start);
         AddAlarm((ULONG_T)time, shot, error_id, start);
         entry++;
      }
      return error_buf;
   } catch (...) {
      throw cError(FM_EB_ERROR, 0, _Name.c_str(), eb);
   }
  //## end cFM2Device::ParseEB%1071317861.body
}

void cFM2Device::SetTransmitBuffer ()
{
  //## begin cFM2Device::SetTransmitBuffer%1071317862.body preserve=yes
   DB();
   STRING_T variables = _SetBuffer;
   SB(variables.c_str());

#ifdef lassma
   if (_CycleSpec != NULL) {
      cSystemUtils::Suspend(1000);
      STRING_T var_list = VarList();
      if (var_list.size() > 0) SB(var_list.c_str());
   }
#endif
  //## end cFM2Device::SetTransmitBuffer%1071317862.body
}

INT_T cFM2Device::CommandType (CONST_STRING_T command)
{
  //## begin cFM2Device::CommandType%1071317863.body preserve=yes
   switch (command[0]) {
   case 'M':
      switch (command[1]) {
      case 'S': return COMMAND_TYPE_1;
      }
   case 'T':
      switch (command[1]) {
      case 'V': return COMMAND_TYPE_1;
      case 'B':
         if (command[3] == '0' && command[4] == '1') return COMMAND_TYPE_3;
      case 'P': return COMMAND_TYPE_3;
      }
   case 'D':
      switch (command[1]) {
      case 'D': return COMMAND_TYPE_2;
      case 'B': return COMMAND_TYPE_1;
      }
   case 'S':
      switch (command[1]) {
      case 'B': return COMMAND_TYPE_2;
      }
   case 'E':
      switch (command[1]) {
      case 'B': return COMMAND_TYPE_3;
      }
   case 'C':
      switch (command[1]) {
      case 'B': return COMMAND_TYPE_3;
      }
   case 'U':
      switch (command[1]) {
      case 'D': return COMMAND_TYPE_3;
      }
   }
   throw cError(FM_UNKNOWN_COMMAND, 0, command, _Name.c_str());
  //## end cFM2Device::CommandType%1071317863.body
}

cVarInfo * cFM2Device::VarInfo (CONST_STRING_T var_name)
{
  //## begin cFM2Device::VarInfo%1104923762.body preserve=yes
   VAR_INFO_MAP_T::const_iterator i = _VarInfos.find(var_name);
   if (i == _VarInfos.end()) {
      return NULL;
   } else {
      return (*i).second;
   }
  //## end cFM2Device::VarInfo%1104923762.body
}

void cFM2Device::SetVarInfo (CONST_STRING_T var_name, CONST_STRING_T value)
{
  //## begin cFM2Device::SetVarInfo%1104923759.body preserve=yes
   cVarInfo * var_info = VarInfo(var_name);
   if (var_info == NULL) {
      cVarInfo * var_info = new cVarInfo(value);
      _VarInfos[var_name] = var_info;
   } else {
      var_info->SetInfo(value);
   }
  //## end cFM2Device::SetVarInfo%1104923759.body
}

int cFM2Device::Precision (CONST_STRING_T var_name)
{
  //## begin cFM2Device::Precision%1104923760.body preserve=yes
   cVarInfo * var_info = VarInfo(var_name);
   if (var_info == NULL) {
      return UNDEFINED_SPEC;
   } else {
      return var_info->Precision();
   }
  //## end cFM2Device::Precision%1104923760.body
}

int cFM2Device::Length (CONST_STRING_T var_name)
{
  //## begin cFM2Device::Length%1104923761.body preserve=yes
   cVarInfo * var_info = VarInfo(var_name);
   if (var_info == NULL) {
      return UNDEFINED_SPEC;
   } else {
      return var_info->Length();
   }
  //## end cFM2Device::Length%1104923761.body
}

void cFM2Device::ReadState (CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags)
{
  //## begin cFM2Device::ReadState%1105117219.body preserve=yes
   cObjectLock __lock__(&_DeviceMutex);
   char value[0x200] = {0};
   if (strcmp(name, "MS") == 0) {
      UpdateState();
      SafePrintf(value, sizeof(value),  "0");
   } else {
      if (_MachineState != NULL) {
         if (strcmp(name, "ProductionState") == 0) {
            SafePrintf(value, sizeof(value),  "%d", _MachineState->get_ProductionState());
         } else if (strcmp(name, "MachineState") == 0) {
            SafePrintf(value, sizeof(value),  "%d", _MachineState->get_MachineState());
         } else if (strcmp(name, "UploadRequest") == 0) {
            SafePrintf(value, sizeof(value),  "%d", _MachineState->get_UploadRequest());
         } else if (strcmp(name, "StartRequest") == 0) {
            SafePrintf(value, sizeof(value),  "%d", _MachineState->get_StartRequest());
         } else if (strcmp(name, "DownloadRequest") == 0) {
            SafePrintf(value, sizeof(value),  "%d", _MachineState->get_DownloadRequest());
         } else if (strcmp(name, "StopRequest") == 0) {
            SafePrintf(value, sizeof(value),  "%d", _MachineState->get_StopRequest());
         } else if (strcmp(name, "AbortRequest") == 0) {
            SafePrintf(value, sizeof(value),  "%d", _MachineState->get_AbortRequest());
         } else if (strcmp(name, "UploadEnabled") == 0) {
            SafePrintf(value, sizeof(value),  "%d", _MachineState->get_UploadEnabled());
         } else if (strcmp(name, "DownloadEnabled") == 0) {
            SafePrintf(value, sizeof(value),  "%d", _MachineState->get_DownloadEnabled());
         } else if (strcmp(name, "ProductionTerminated") == 0) {
            SafePrintf(value, sizeof(value),  "%d", _MachineState->get_ProductionTerminated());
         } else {
            SafePrintf(value, sizeof(value),  "0");
         }
      }
   }
   int size = _MIN_(strlen(value)+1, len);
   memcpy(buf, value, size);
  //## end cFM2Device::ReadState%1105117219.body
}

void cFM2Device::UpdateState ()
{
  //## begin cFM2Device::UpdateState%1105117220.body preserve=yes
   if (_MachineState != NULL) {
      delete _MachineState;
      _MachineState = NULL;
   }
   char inbuf[0x200] = {0};
   try {
      MS(inbuf, sizeof(inbuf));
      if (_MachineState != NULL) {
         delete _MachineState;
         _MachineState = NULL;
      }
      _MachineState = ParseMS(inbuf);
static BOOL_T _BufferSet = false;
      if (_MachineState->get_ConfigState() == 0xff || !_BufferSet) {
         SetTransmitBuffer();
         _BufferSet = true;
      } else {
         UpdateCycleBuf();
         UpdateChangeBuf();
         UpdateErrorBuf();
      }
   } catch (cError & e) {
      ErrorPrintf("Fehler Maschinenstatus: %s\n", (const char *)e);
   } catch (...) {
      ErrorPrintf("Unbekannter Fehler Maschinenstatus\n");
   }
  //## end cFM2Device::UpdateState%1105117220.body
}

void cFM2Device::UpdateCycleBuf ()
{
  //## begin cFM2Device::UpdateCycleBuf%1105186360.body preserve=yes
   if (_MachineState->get_DataPending()) {
      char inbuf[0x2000] = {0};
      try {
         TB(inbuf, sizeof(inbuf));
//InfoPrintf("TB:\n");
//InfoPrintf("%s\n", inbuf);
         cCycleBuf * cycle_buf = ParseTB(inbuf);
         if (cycle_buf != NULL) {
            ULONG_T columns = cycle_buf->Columns();
            STRING_T name;
            STRING_T value;
            ULONG_T shot = 0;
            LONG_T quality = 0;
            for (ULONG_T i=0; i<columns; i++) {
               name = cycle_buf->GetColumnName(i);
               value = cycle_buf->GetValue(name.c_str(), 0);
               if (value.size() > 0) {
                  _VariableCache->Write(name.c_str(), value.c_str());
//InfoPrintf("cache write %s = %s\n", name.c_str(), value.c_str());
                  Changed("variable", name.c_str());
                  if (strcmp("CYX1A_.4", name.c_str()) == 0) {
                     shot = strtoul(value.c_str(), NULL, 0);
                  }
               }
            }
            cJobEntry * job_entry = new cJobEntry;
            job_entry->set_Shot(shot);
            job_entry->set_Quality(quality);
            RaiseEvent(job_entry);
            job_entry->Release();
            delete cycle_buf;
         }
      } catch (cError & e) {
         ErrorPrintf("Fehler Zykluspuffer: %s\n", (const char *)e);
      } catch (...) {
         ErrorPrintf("Unbekannter Fehler Zykluspuffer\n");
      }
   }
  //## end cFM2Device::UpdateCycleBuf%1105186360.body
}

void cFM2Device::UpdateChangeBuf ()
{
  //## begin cFM2Device::UpdateChangeBuf%1105186361.body preserve=yes
   if (_MachineState->get_ChangesPending()) {
      char inbuf[0x2000] = {0};
      try {
         CB(inbuf, sizeof(inbuf));
         cChangeBuf * change_buf = ParseCB(inbuf);
         if (change_buf != NULL) {
            ULONG_T entries = change_buf->Entries();
            for (ULONG_T i=0; i<entries; i++) {
               STRING_T name = change_buf->Name(i);
               STRING_T value = change_buf->NewValue(i);
               if (value.size() > 0) {
                  _VariableCache->Write(name.c_str(), value.c_str());
                  Changed("variable", name.c_str());
               }
            }
            delete change_buf;
         }
      } catch (cError & e) {
         ErrorPrintf("Fehler Änderungspuffer: %s\n", (const char *)e);
      } catch (...) {
         ErrorPrintf("Unbekannter Fehler Änderungspuffer\n");
      }
   }
  //## end cFM2Device::UpdateChangeBuf%1105186361.body
}

void cFM2Device::UpdateErrorBuf ()
{
  //## begin cFM2Device::UpdateErrorBuf%1105186362.body preserve=yes
   if (_MachineState->get_ErrorsPending()) {
      char inbuf[0x2000] = {0};
      try {
         EB(inbuf, sizeof(inbuf));
         cErrorBuf * error_buf = ParseEB(inbuf);
         if (error_buf != NULL) {
            // ...
            delete error_buf;
         }
      } catch (cError & e) {
         ErrorPrintf("Fehler Fehlerpuffer: %s\n", (const char *)e);
      } catch (...) {
         ErrorPrintf("Unbekannter Fehler Fehlerpuffer\n");
      }
   }
  //## end cFM2Device::UpdateErrorBuf%1105186362.body
}

void cFM2Device::ReadErrorBuf (char *buf, ULONG_T buf_size)
{
  //## begin cFM2Device::ReadErrorBuf%1152293605.body preserve=yes
   ULONG_T pos = 0;
   memset(buf, 0, buf_size);
   ULONG_T entries = _Errors.size();
   ULONG_T i = 0;
   for (i=0; i<entries; i++) {
      ERROR_ENTRY_T * error_entry = _Errors[i];
      char estr[0x200] = {0};
      SafePrintf(estr, sizeof(estr), "%d;%d;%s;%s;\n",
              error_entry->time,
              error_entry->shot,
              error_entry->id,
              error_entry->start ? "1" : "0");
      memcpy(&buf[pos], estr, strlen(estr));
      pos += strlen(estr);
   }
   for (i=0; i<entries; i++) {
      ERROR_ENTRY_T * error_entry = _Errors[i];
      cSystemUtils::Free(error_entry);
   }
   _Errors.clear();
  //## end cFM2Device::ReadErrorBuf%1152293605.body
}

//## Get and Set Operations for Class Attributes (implementation)

ULONG_T cFM2Device::get_BaudRate () const
{
  //## begin cFM2Device::get_BaudRate%3FD45C2101B5.get preserve=no
  return _BaudRate;
  //## end cFM2Device::get_BaudRate%3FD45C2101B5.get
}

void cFM2Device::set_BaudRate (ULONG_T value)
{
  //## begin cFM2Device::set_BaudRate%3FD45C2101B5.set preserve=no
  _BaudRate = value;
  //## end cFM2Device::set_BaudRate%3FD45C2101B5.set
}

ParityTypes cFM2Device::get_Parity () const
{
  //## begin cFM2Device::get_Parity%3FD45C2101C5.get preserve=no
  return _Parity;
  //## end cFM2Device::get_Parity%3FD45C2101C5.get
}

void cFM2Device::set_Parity (ParityTypes value)
{
  //## begin cFM2Device::set_Parity%3FD45C2101C5.set preserve=no
  _Parity = value;
  //## end cFM2Device::set_Parity%3FD45C2101C5.set
}

HandshakeTypes cFM2Device::get_Handshake () const
{
  //## begin cFM2Device::get_Handshake%3FD45C2101C6.get preserve=no
  return _Handshake;
  //## end cFM2Device::get_Handshake%3FD45C2101C6.get
}

void cFM2Device::set_Handshake (HandshakeTypes value)
{
  //## begin cFM2Device::set_Handshake%3FD45C2101C6.set preserve=no
  _Handshake = value;
  //## end cFM2Device::set_Handshake%3FD45C2101C6.set
}

UCHAR_T cFM2Device::get_CharLen () const
{
  //## begin cFM2Device::get_CharLen%3FD45C2101C7.get preserve=no
  return _CharLen;
  //## end cFM2Device::get_CharLen%3FD45C2101C7.get
}

void cFM2Device::set_CharLen (UCHAR_T value)
{
  //## begin cFM2Device::set_CharLen%3FD45C2101C7.set preserve=no
  _CharLen = value;
  //## end cFM2Device::set_CharLen%3FD45C2101C7.set
}

UCHAR_T cFM2Device::get_StartBits () const
{
  //## begin cFM2Device::get_StartBits%3FD45C2101D4.get preserve=no
  return _StartBits;
  //## end cFM2Device::get_StartBits%3FD45C2101D4.get
}

void cFM2Device::set_StartBits (UCHAR_T value)
{
  //## begin cFM2Device::set_StartBits%3FD45C2101D4.set preserve=no
  _StartBits = value;
  //## end cFM2Device::set_StartBits%3FD45C2101D4.set
}

UCHAR_T cFM2Device::get_StopBits () const
{
  //## begin cFM2Device::get_StopBits%3FD45C2101D5.get preserve=no
  return _StopBits;
  //## end cFM2Device::get_StopBits%3FD45C2101D5.get
}

void cFM2Device::set_StopBits (UCHAR_T value)
{
  //## begin cFM2Device::set_StopBits%3FD45C2101D5.set preserve=no
  _StopBits = value;
  //## end cFM2Device::set_StopBits%3FD45C2101D5.set
}

// Additional Declarations
  //## begin cFM2Device%3FCF50D0002E.declarations preserve=yes
  //## end cFM2Device%3FCF50D0002E.declarations

//## begin module%3FCF50D0002E.epilog preserve=yes
//## end module%3FCF50D0002E.epilog

