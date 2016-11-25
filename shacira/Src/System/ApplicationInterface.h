
#ifndef _applicationinterface_h
#define _applicationinterface_h

#include "FirstHeader.h"
#include "System/Database/cContext.h"
#include "System/Database/cFuncRef.h"
#include "System/Database/FuncSpecs.h"
class QWidget;
typedef QWidget * WIDGET_PTR;

/*!
 * The ApplicationInterface module contains a couple of classes
 * functions and macros to easily interface with the
 * SHACIRA framework.
 *
 *
 */

/*!
 * cFunctionFactory acts as factory class for user
 * functions.
 *
 */

typedef std::map<STRING_T,FUNC_ENTRY_T*> FUNC_PTR_MAP_T;

class cFunctionFactory
{
public:
   void RegisterFunctionAddress(CONST_STRING_T func_name, FUNC_T func_ptr, UCHAR_T func_class);
   static FUNC_T GetFunctionAddress(UCHAR_T func_class, CONST_STRING_T func_name);
private:
   static FUNC_PTR_MAP_T * _ModelFunctions;
   static FUNC_PTR_MAP_T * _GUIFunctions;
};

class cFunctionAddress
{
public:
   cFunctionAddress(CONST_STRING_T func_name, FUNC_T func_ptr, int func_class);
private:
   static cFunctionFactory * _Factory;
};

/*!
 * @brief macro REGISTER_FUNCTION(address,class) registers a user function
 * with the SHACIRA runtime system.
 */
#define REGISTER_FUNCTION(f_address,f_class) \
   static cFunctionAddress addr_##f_address(#f_address, (FUNC_T)f_address, f_class);

#endif

/*
 * device and program factories
 */

#include "System/Config//cConfigurationObject.h"
#include "System/Database/cContext.h"
#include "Control/Cell/cCell.h"
#include "Control/Device/cDevice.h"

class cDeviceObject;

typedef std::map<STRING_T,cDeviceObject*> DEVICE_OBJECT_MAP_T;

#define CREATE_DEVICE_OBJECT_MAP() \
   if (_ObjectMap == NULL) { \
      _ObjectMap = new DEVICE_OBJECT_MAP_T; \
   }

class cDeviceObjectFactory
{
public:
   static void AddDeviceObject(const char * type_name, cDeviceObject * device_object)
   {
      CREATE_DEVICE_OBJECT_MAP();
      (*_ObjectMap)[type_name] = device_object;
   };
   static cDeviceObject * DeviceObject(const char * type_name) 
   { 
      CREATE_DEVICE_OBJECT_MAP();
      return (*_ObjectMap)[type_name]; 
   }
   static cDevice * CreateDevice(cConfigurationObject * config_obj, cCell * cell);
private:
   static DEVICE_OBJECT_MAP_T * _ObjectMap;
};

class cDeviceObject
{
public:
   cDeviceObject(const char * type_name) :
      _TypeName(type_name)
   {
      cDeviceObjectFactory::AddDeviceObject(type_name, this);
   }
   virtual cDevice * CreateDevice(cConfigurationObject * config_obj, cCell * cell) = 0;
private:
   STRING_T _TypeName;
};

/*!
 * @brief macro REGISTER_DEVICE(type_name) registers an application specific device class
 * with the SHACIRA runtime system.
 */
#define REGISTER_DEVICE(type_name, class_name) \
   static class devobj_##class_name : public cDeviceObject {\
   public: \
      devobj_##class_name() : cDeviceObject(type_name) {  } \
      cDevice * CreateDevice(cConfigurationObject * config_obj, cCell * cell) \
         { return new class_name(config_obj, cell); } \
   } __devobj_##class_name##__;


class cProgramObject;

typedef std::map<STRING_T,cProgramObject*> PROGRAM_OBJECT_MAP_T;

#define CREATE_PROGRAM_OBJECT_MAP() \
   if (_ObjectMap == NULL) { \
      _ObjectMap = new PROGRAM_OBJECT_MAP_T; \
   }

class cProgramObjectFactory
{
public:
   static void AddProgramObject(const char * type_name, cProgramObject * program_object)
   {
      CREATE_PROGRAM_OBJECT_MAP();
      (*_ObjectMap)[type_name] = program_object;
   };
   static cProgramObject * ProgramObject(const char * type_name) 
   { 
      CREATE_PROGRAM_OBJECT_MAP();
      return (*_ObjectMap)[type_name]; 
   }
   static cProgram * CreateProgram(cConfigurationObject * config_obj, cContext * context);
private:
   static PROGRAM_OBJECT_MAP_T * _ObjectMap;
};

class cProgramObject
{
public:
   cProgramObject(const char * type_name) :
      _TypeName(type_name)
   {
      cProgramObjectFactory::AddProgramObject(type_name, this);
   }
   virtual cProgram * CreateProgram(cConfigurationObject * config_obj, cContext * context) = 0;
private:
   STRING_T _TypeName;
};

/*!
 * @brief macro REGISTER_PROGRAM(type_name) registers an application specific program class
 * with the SHACIRA runtime system.
 */
#define REGISTER_PROGRAM(type_name, class_name) \
   static class progobj_##class_name : public cProgramObject {\
   public: \
      progobj_##class_name() : cProgramObject(type_name) {  } \
      cProgram * CreateProgram(cConfigurationObject * config_obj, cContext * context) \
         { return new class_name(config_obj, context); } \
   } __progobj_##class_name##__;


/*!
 * @brief global function .
 * @param mdl_init_func function address of model init function
 * @param gui_init_func function address of gui init function
 * @param custom_text_func function address application text supplier function
 */
BOOL_T InitializeApplicationInterface(MDL_INIT_FUNC_T mdl_init_func = NULL,
                                      GUI_INIT_FUNC_T gui_init_func = NULL,
                                      GET_CUSTOM_TEXT_FUNC_T custom_text_func = NULL);


