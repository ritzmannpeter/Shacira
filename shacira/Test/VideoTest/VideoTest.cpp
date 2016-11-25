
#include "FirstHeader.h"
#include "System/Process/cOptions.h"
#include "System/Sys/cFileSystemUtils.h"
#include "System/Process/cSHProcess.h"
#include "System/Config/cConfiguration.h"
#include "System/Config/cConfigurationObject.h"
#include "Orb/cBroker.h"
#include "System/Sys/cSockets.h"
#include "System/Console/cStandardConsole.h"
#include "System/Console/cMemoryConsole.h"
#include "System/Console/cSocketConsole.h"
#include "System/Objects/cState.h"
#include "System/Objects/cInfo.h"
#include "System/Database/cContext.h"
#include "Control/CellProcess/cCellProcess.h"
#include "System/Channel/cLocalChannel.h"
#include "System/Channel/cRemoteBridge.h"
#include "System/Channel/cCOSChannel.h"
#include "System/Channel/cAdapter.h"
#include "System/Channel/cChannelFactory.h"
#include "System/Channel/cAdapterFactory.h"
#include "System/Channel/cConnector.h"
#include "System/Database/cVarDef.h"
#include "System/Database/cMapping.h"
#include "Control/SerialChannel/cSerialChannel.h"
#include "Control/SerialChannel/cSerialBridge.h"
#include "Control/SerialChannel/cMultiplexer.h"
#include "Control/Device/cFM2Device.h"
#include "Control/Device/cGrabberDevice.h"
#include "Control/LocalDatabase/cLocalVariable.h"
#include "System/Memory/cPtrList.h"
#include "base/eb_sema.hpp"
#include "qlayout.h"
#include "grabber.h"
#include "video.h"

static cMutexSem _Sync;
static QApplication * _QApp = NULL;
static Video * _Video1 = NULL;
static Video * _Video2 = NULL;
static Video * _Video3 = NULL;
static Video * _Video4 = NULL;
static Grabber * _Grabber = NULL;

#define ELEMENTS  0x80
#define BUF_SIZE  (ELEMENTS*2)
#define NAME_SIZE 0x20

static DWORD _Ticks = 0;
static SYSTEMTIME _Time = {0};
static void Time(bool print)
{
   DWORD ticks = GetTickCount();
   DWORD diff = ticks - _Ticks;
   if (print) printf("(%ld,%ld)%ld\n", ticks, _Ticks, diff);
   _Ticks = ticks;
   SYSTEMTIME time = {0};
   GetSystemTime(&time);
   if (print) printf("(%d.%d,%d.%d)\n", time.wSecond, time.wMilliseconds, _Time.wSecond, _Time.wMilliseconds);
   _Time = time;
}

typedef cDevice * (*LOADPROC)(cConfigurationObject*); 
static HMODULE _Dll = NULL;
static LOADPROC _LoadDevice = NULL;
static cDevice * LoadDevice(CONST_STRING_T driver_name, cConfigurationObject * driver_obj)
{
   STRING_T library_name = driver_name;
   library_name += "d.dll";
   if (_Dll == NULL) {
      HMODULE module = LoadLibrary(library_name.c_str());
      if (module == NULL) {
         int err = GetLastError();
         printf("cannot load library %s: %d\n", library_name.c_str(), err);
         return NULL;
      } else {
         _Dll = module;
      }
   }
   if (_Dll != NULL && _LoadDevice == NULL) {
      LOADPROC proc = (LOADPROC)GetProcAddress(_Dll, "LoadDevice");
      if (proc == NULL) {
         int err = GetLastError();
         printf("cannot get address of LoadDevice: %d\n", err);
         return NULL;
      } else {
         _LoadDevice = proc;
      }
   }
   if (_Dll != NULL && _LoadDevice != NULL) {
      return _LoadDevice(driver_obj);
   }
   return NULL;
}

static USHORT_T _OldValues[ELEMENTS] = {0};
static void ReadValue(cDevice * device, USHORT_T reg_no)
{
   USHORT_T value = 0;
   device->Read("register", reg_no, 1, &value, sizeof(value));
   if (value != _OldValues[reg_no]) {
      printf("%d: %d\n", reg_no, value);
      _OldValues[reg_no] = value;
   }
}

#define IMAGESIZE 5000000

static cLocalVariable * MakeVariable(cDevice * device ,CONST_STRING_T channel)
{
   cVarDef * var_def = new cVarDef;;
   var_def->_DataType = SH_BYTE;
   var_def->_Length = IMAGESIZE;
   MAP_ITEM_T * map_item = (MAP_ITEM_T*)cSystemUtils::Alloc(sizeof(*map_item));
   map_item->device = device;
   map_item->buf_spec = channel;
   map_item->name = "Image";
   map_item->address = -1;
   map_item->bit_pos_b = -1;
   map_item->bit_pos_e = -1;
   map_item->data_type = SH_BYTE;
   map_item->size = IMAGESIZE;
   map_item->var_def = var_def;
   cMapping * mapping = new cMapping;
   mapping->SetItem(0, map_item);
   var_def->SetMapping(mapping);
   return new cLocalVariable(var_def);
}

void CreateGrabber(cConfigurationObject * cell_obj)
{
   cConfigurationObject * device_obj = NULL;
   CONFOBJ_VECTOR_T obj_vec;
   cell_obj->PropertyValue("Devices", obj_vec);
   int device_count = obj_vec.size();
   if (device_count > 0) {
      for (int i=0; i<device_count; i++) {
         device_obj = obj_vec[i];
         STRING_T device_name = device_obj->get_Name().c_str();
         int device_index = 0;
         int params = sscanf(device_name.c_str(), "Camera%d", &device_index);
         if (params == 1) {
            cDevice * device = new cGrabberDevice(device_obj, NULL);
            if (device != NULL) {
               device->Start();
               _Grabber->SetDevice(device, device_index - 1);
            }
         }
      }
   }
}

unsigned long NanoSeconds(unsigned long seconds)
{
   return seconds * 10000;
}


int main(int argc, char* argv[])
{
MAINFUNC_PROLOG("CCS")
   try {
      int idle_time = 0;
      if (argc == 2) {
         idle_time = atol(argv[1]);
      }
      cResources resources(argc, argv);
		cSockets::Initialize();
		cBroker::Initialize();
      cConfiguration * config = NULL;
      try {
         STRING_T config_file = cFileSystemUtils::AppendPath(cResources::ConfigPath().c_str(),
                                                                  cConfiguration::DefaultConfigFile());
         config = new cConfiguration(config_file.c_str());
      } catch (cError & e) {
         ErrorPrintf("%s\n", (const char *)e);
         return -9;
      }
      STRING_T root_name = "LocalNelaProcess";
      cConfigurationObject * process_obj = config->Object(root_name.c_str());
      if (process_obj != NULL) {
         cSHProcess process(process_obj);
         process.set_Path(argv[0]);
   		process.Start();
         cResources::RegisterProcess(&process);
         CONFOBJ_VECTOR_T obj_vec;
         process_obj->PropertyValue("Cells", obj_vec);
		   int cell_count = obj_vec.size();
		   if (cell_count == 0) {
            printf("no cells\n");
            return 0;
         }
         cConfigurationObject * cell_obj = obj_vec[0];
         _QApp = new QApplication(argc, argv);
         _Grabber = new Grabber(&_Sync, idle_time);
         CreateGrabber(cell_obj);
         QWidget * widget = new QWidget;
         QGridLayout * layout = new QGridLayout(widget);
         _Video1 = new Video(widget, _Grabber, &_Sync, 0);
         layout->addWidget(_Video1, 0, 0);
         _Video2 = new Video(widget, _Grabber, &_Sync, 1);
         layout->addWidget(_Video2, 0, 1);
         _Video3 = new Video(widget, _Grabber, &_Sync, 2);
         layout->addWidget(_Video3, 1, 0);
         _Video4 = new Video(widget, _Grabber, &_Sync, 3);
         layout->addWidget(_Video4, 1, 1);
         _QApp->setMainWidget(widget);
         widget->setMinimumSize(800, 600);
         widget->show();
         _Grabber->Start();
         _QApp->exec();
      } else {
         ErrorPrintf("Root object %s not found\n", root_name.c_str());
      }
      return 0;
   } catch (cError & e) {
      ErrorPrintf("%s\n", (const char*) e);
      return -11;
   } catch (...) {
      ErrorPrintf("Unhandled exception in main Thread\n");
      return -12;
   }
MAINFUNC_EPILOG
   return 0;
}
