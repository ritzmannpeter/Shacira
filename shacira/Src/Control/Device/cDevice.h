//	Copyright © 2002 - 2007 by
//	2i Industrial Informatics GmbH

#ifndef cDevice_h
#define cDevice_h 1

/*! \mainpage CCS API Documentation
 *
 * CCS (Core Control Services) is the runtime environment of SHACIRA applications.
 * It comes with a couple of services, that can be used by SHACIRA applications
 * to mamage data, persistence, events distributed objects, ....
 * <p>This document describes the concepts and the API that can be used
 * to develop applications that rely on SHACIRA CCS.
 * <p>
 * <p>
 *
 * \ref devices
 *
 * etc...
 */

#include "System/Objects/cObjectLock.h"
#include "System/Objects/cAlarm.h"
#include "System/Objects/cStaticObject.h"
#include "System/Config/cConfigurationObject.h"
#include "System/Database/cMapping.h"
#include "Control/SerialChannel/cSerialChannelFactory.h"

class __DLL_EXPORT__ cProgress;
class __DLL_EXPORT__ cPtrList;
class __DLL_EXPORT__ cCell;
class __DLL_EXPORT__ cLocalVariable;
class __DLL_EXPORT__ cElementRefs;
class __DLL_EXPORT__ cCacheControl;
class __DLL_EXPORT__ cCache;
class __DLL_EXPORT__ cBitOperator;

typedef struct memory_info {
   UCHAR_T granularity;
   ULONG_T ident;
   ULONG_T command;
   cCache * cache;
   cCache * buffer;
}  MEMORY_INFO;
typedef std::map<STRING_T,MEMORY_INFO*> MEMORY_INFO_MAP_T;

typedef enum {Active, Inactive} WorkingState;
typedef enum {Connected, NotConnected} OperatingState;

class cDeviceControl;

class __DLL_EXPORT__ cDevice : public cStaticObject
{
friend class __DLL_EXPORT__ cCacheControl;
public:
   /*!
    * \brief standard constructor
    */
   cDevice();
   /*!
    * \brief constructor
    * @param config_object a configuration object that holds additional properties that are examined in the constructor
    * @param cell a pointer to the cell that holds the device
    * <p>Typical properties that can be specified for a device at runtime are serial line parametrs
    * for devices that communicate via serial interfaces or port and protocol informations
    * for devices that communicate via tcp/ip.
    */
   cDevice(cConfigurationObject *config_obj, cCell *cell);
   virtual ~cDevice();
   /*!
    * \brief Starts a devices additional services
    * This method should start additional services (threads) like caching if needed.
    * If no additional services are implemented by the device, the Start method
    * nust not be reimplemented.
    */
   virtual void Start();
   /*!
    * \brief Stops a devices additional services if so
    */
   virtual void Stop();
   virtual void Kill(bool wait=false);
   /*!
    * \brief Informs a device about an address that must be cached
    * This method will be called for every address the device must cache.
    * @param buf_spec additional identifier to identify the requested data item (name space)
    * @param address address to identify the requested data item (address mapped data items only)
    * @param size specifies the size of the data item to be cached 
    * @param refresh_type specifies the refresh policy for this data item
    * @param refresh_value specifies the interval value in case of cyclic refresh types 
    */
   virtual void Cache(CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);
   /*!
    * \brief Informs a device about a name that must be cached
    * This method will be called for every name the device must cache.
    * @param buf_spec additional identifier to identify the requested data item (name space)
    * @param name name to identify the requested data item (name mapped data items only)
    * @param size specifies the size of the data item to be cached 
    * @param refresh_type specifies the refresh policy for this data item
    * @param refresh_value specifies the interval value in case of cyclic refresh types 
    */
   virtual void Cache(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T size, UCHAR_T refresh_type, ULONG_T refresh_value);
   /*!
    * \brief Informs a device about an address that must be buffered
    * This method will be called for every address the device must buffer.
    * @param buf_spec additional identifier to identify the requested data item (name space)
    * @param address address to identify the requested data item (address mapped data items only)
    * @param size specifies the size of the data item to be cached
    */
   virtual void Buffer(CONST_STRING_T buf_spec, ULONG_T address, ULONG_T size);
   /*!
    * \brief Informs a device about a map item that must be buffered
    * This method will be called for every map item the device must buffer.
    * @param map_item pointer to a map item
    */
   virtual void Buffer(MAP_ITEM_T * map_item);
   /*!
    * \brief Informs a device about a name that must be buffered
    * This method will be called for every name the device must buffer.
    * @param buf_spec additional identifier to identify the requested data item (name space)
    * @param name name to identify the requested data item (name mapped data items only)
    * @param size specifies the size of the data item to be cached 
    */
   virtual void Buffer(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T size);
   /*!
    * \brief General read operation to get data from the device for address mapped data
    * The data must be placed into a supplied buffer with a specific size.
    * The amount of data to be read is specified through the parameter len.
    * @param buf_spec additional identifier to identify the requested data item (name space)
    * @param address address to identify the requested data item (address mapped data items only)
    * @param len specifies the size of the data item to be read
    * @param buf buffer to receive read data
    * @param buf_size size of the buffer
    * @param flags additional flags to control the data exchange behaviour of a device
    */
   virtual void Read(CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);
   virtual void Read(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T buf_size, ULONG_T flags = 0);
   virtual void Write(CONST_STRING_T buf_spec, ULONG_T address, ULONG_T len, void *buf, ULONG_T flags = 0);
   virtual void Write(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T len, void *buf, ULONG_T flags = 0);
   virtual void Process();
   virtual void Control();
   virtual BOOL_T GetBit(CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T pos);
   virtual void SetBit(CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T pos, BOOL_T state);
   virtual void Get(CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, ULONG_T address, USHORT_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, ULONG_T address, ULONG_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, ULONG_T address, FLOAT_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, ULONG_T address, DOUBLE_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, ULONG_T address, STRING_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, ULONG_T address, WSTRING_T &value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, ULONG_T address, USHORT_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, ULONG_T address, ULONG_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, ULONG_T address, FLOAT_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, ULONG_T address, DOUBLE_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, ULONG_T address, CONST_STRING_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, ULONG_T address, CONST_WSTRING_T value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, CONST_STRING_T name, USHORT_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, CONST_STRING_T name, FLOAT_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, CONST_STRING_T name, DOUBLE_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, CONST_STRING_T name, STRING_T &value, ULONG_T flags = 0);
   virtual void Get(CONST_STRING_T buf_spec, CONST_STRING_T name, WSTRING_T &value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, CONST_STRING_T name, USHORT_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, CONST_STRING_T name, FLOAT_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, CONST_STRING_T name, DOUBLE_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, CONST_STRING_T name, CONST_STRING_T value, ULONG_T flags = 0);
   virtual void Set(CONST_STRING_T buf_spec, CONST_STRING_T name, CONST_WSTRING_T value, ULONG_T flags = 0);
   virtual void Cast(CONST_STRING_T buf_spec, UCHAR_T data_type, UCHAR_T &value);
   virtual void Cast(CONST_STRING_T buf_spec, UCHAR_T data_type, USHORT_T &value);
   virtual void Cast(CONST_STRING_T buf_spec, UCHAR_T data_type, ULONG_T &value);
   virtual void Cast(CONST_STRING_T buf_spec, UCHAR_T data_type, FLOAT_T &value);
   virtual void Cast(CONST_STRING_T buf_spec, UCHAR_T data_type, DOUBLE_T &value);
   virtual ULONG_T GetPattern(CONST_STRING_T buf_spec, UCHAR_T data_type, UCHAR_T &value, UCHAR_T start_pos, UCHAR_T end_pos, ULONG_T flags = 0);
   virtual ULONG_T GetPattern(CONST_STRING_T buf_spec, UCHAR_T data_type, USHORT_T &value, UCHAR_T start_pos, UCHAR_T end_pos, ULONG_T flags = 0);
   virtual ULONG_T GetPattern(CONST_STRING_T buf_spec, UCHAR_T data_type, ULONG_T &value, UCHAR_T start_pos, UCHAR_T end_pos, ULONG_T flags = 0);
   virtual void SetPattern(CONST_STRING_T buf_spec, UCHAR_T data_type, UCHAR_T &value, UCHAR_T start_pos, UCHAR_T end_pos, ULONG_T pattern, ULONG_T flags = 0);
   virtual void SetPattern(CONST_STRING_T buf_spec, UCHAR_T data_type, USHORT_T &value, UCHAR_T start_pos, UCHAR_T end_pos, ULONG_T pattern, ULONG_T flags = 0);
   virtual void SetPattern(CONST_STRING_T buf_spec, UCHAR_T data_type, ULONG_T &value, UCHAR_T start_pos, UCHAR_T end_pos, ULONG_T pattern, ULONG_T flags = 0);
   virtual void Save(UCHAR_T refresh_type, ULONG_T refresh_value);
   virtual void Download();
   virtual void Upload();
   void SetProgress(ULONG_T indicator, ULONG_T value);
   virtual BOOL_T MappingValid(CONST_STRING_T buf_spec, ULONG_T address, UCHAR_T data_type);
   virtual BOOL_T MappingValid(CONST_STRING_T buf_spec, CONST_STRING_T name, UCHAR_T data_type);
   cMutexSem * DeviceMutex();

   virtual void * GetObject(CONST_STRING_T buf_spec, ULONG_T address, ULONG_T flags = 0);
   virtual void * GetObject(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T flags = 0);

   virtual void OptimizeBuffers();
   virtual void OptimizeCaches();

   virtual DOUBLE_T GetParameter(CONST_STRING_T parameter_id) const;
   virtual STRING_T GetParameterString(CONST_STRING_T parameter_id) const;
   virtual void SetParameter(CONST_STRING_T parameter_id, DOUBLE_T value);
   virtual void SetParameterString(CONST_STRING_T parameter_id, const STRING_T & value);

   BOOL_T get_Verbose() const;
   void set_Verbose(BOOL_T value);
   BOOL_T get_Simulated() const;
   void set_Simulated(BOOL_T value);
   BOOL_T get_InterfaceMode() const;
   void set_InterfaceMode(BOOL_T value);
   BOOL_T get_Buffered() const;
   void set_Buffered(BOOL_T value);
   BOOL_T get_Cached() const;
   void set_Cached(BOOL_T value);
   BOOL_T get_Verify() const;
   void set_Verify(BOOL_T value);
   BOOL_T get_TimingProtocol () const;
   void set_TimingProtocol (BOOL_T value);
   ULONG_T get_DebugLevel() const;

   BOOL_T _Active;
   BOOL_T _Started;
   BOOL_T _Connected;
   BOOL_T _TimingProtocol;
   cMutexSem _DeviceMutex;

public:
   virtual void Changed(CONST_STRING_T buf_spec, ULONG_T address, ULONG_T flags = 0);
   virtual void Changed(CONST_STRING_T buf_spec, CONST_STRING_T name, ULONG_T flags = 0);
protected:
   void SetMemoryInfo(CONST_STRING_T buf_spec, UCHAR_T granularity, ULONG_T command, ULONG_T ident, cCache *cache, cCache *buffer);
   MEMORY_INFO * MemoryInfo(CONST_STRING_T buf_spec);
   cCache * SelectCache(CONST_STRING_T buf_spec);
   cCache * SelectBuffer(CONST_STRING_T buf_spec);
private:
   void Changed(cPtrList *element_refs, ULONG_T flags = 0);
   cPtrList * GetVariables(CONST_STRING_T buf_spec, ULONG_T address);
   cPtrList * GetVariables(CONST_STRING_T buf_spec, CONST_STRING_T name);
   cElementRefs * GetRefs(CONST_STRING_T buf_spec);
   void SetAddresses(CONST_STRING_T buf_spec, cElementRefs *element_refs, MAP_ITEM_T *map_item, cLocalVariable *variable, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);
protected:
   BOOL_T _Verbose;
   BOOL_T _Simulated;
   BOOL_T _InterfaceMode;
   BOOL_T _Buffered;
   BOOL_T _Cached;
   BOOL_T _Verify;
   MEMORY_INFO_MAP_T _InfoMap;
   ULONG_T _CacheControlId;
   std::map<STRING_T, cElementRefs*> _ElementRefs;
   cCell *_Cell;
   cCacheControl *_CacheControl;
   cBitOperator *_BitOperator;
   cDeviceControl * _DeviceControl;
   BOOL_T _TestMode;
   ULONG_T _TestState;
   cMutexSem _BitOperatorMutex;
   ULONG_T _DebugLevel;
private:
   BOOL_T _Locked;
public:
   virtual void SetVariable(MAP_ITEM_T *map_item, cLocalVariable *variable, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);
   inline cBitOperator * get_BitOperator () {return _BitOperator;};
   inline void set_BitOperator (cBitOperator * value) {_BitOperator = value;};
};

class cDeviceControl: public cControlThread
{
public:
   cDeviceControl(cDevice * device, ULONG_T idle_time)
   {
      _Device = device;
      _IdleTime = idle_time;
      if (_IdleTime < 10) {
         _IdleTime = 10;
      }
   };
   
   virtual ~cDeviceControl() {};
   
   INT_T ControlFunc()
   {
       _Device->Control();
       return 0;
   };
private:
   cDevice * _Device;
};

/*! \class cDevice cDevice.h "Control/Device/cDevice.h"
 *  \brief The cDevice class is the base class for all CCS device objects.
 *
 * CCS device objects handle data exchange between SHACIRA applications
 * and external devices.
 * <p> General information about device objects \ref devices
 */

/*! \page devices CCS device objects
 *
 * CCS device objects handle data exchange between SHACIRA applications
 * and external devices. They can be referred to in CCS data models,
 * to map device data to CCS variables. In a data model device mappings are
 * specified in a declarative, non procedural way, whereas data exchange with
 * devices is a highly dynamic process.
 * <p>
 * A device object must put both views on data exchange together.
 * <p>
 * All CCS device objects are deviated from the base clas cDevice. Every device must inherit
 * from cDevice or from a subclass of cDevice. 
 */

#endif
