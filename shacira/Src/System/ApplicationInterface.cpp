
#include "System/ApplicationInterface.h"

/*
 * function address factories
 */

FUNC_PTR_MAP_T * cFunctionFactory::_ModelFunctions = NULL;

FUNC_PTR_MAP_T * cFunctionFactory::_GUIFunctions = NULL;

cFunctionFactory * cFunctionAddress::_Factory = NULL; 

void cFunctionFactory::RegisterFunctionAddress(CONST_STRING_T func_name, FUNC_T func_ptr, UCHAR_T func_class)
{
   if (_ModelFunctions == NULL) {
      _ModelFunctions = new FUNC_PTR_MAP_T;
   }
   if (_GUIFunctions == NULL) {
      _GUIFunctions = new FUNC_PTR_MAP_T;
   }
   FUNC_ENTRY_T * func_entry = (FUNC_ENTRY_T*)cSystemUtils::Alloc(sizeof(FUNC_ENTRY_T));
   func_entry->func_name = func_name;
   func_entry->func_ptr = func_ptr;
   func_entry->func_class = func_class;
   if (IS_MODEL_FUNCTION(func_class)) {
      (*_ModelFunctions)[func_name] = func_entry;
   } else if (IS_GUI_FUNCTION(func_class)) {
      (*_GUIFunctions)[func_name] = func_entry;
   }
}

FUNC_T cFunctionFactory::GetFunctionAddress(UCHAR_T func_class, CONST_STRING_T func_name)
{
   if (_ModelFunctions == NULL) {
      _ModelFunctions = new FUNC_PTR_MAP_T;
   }
   if (_GUIFunctions == NULL) {
      _GUIFunctions = new FUNC_PTR_MAP_T;
   }
   if (IS_MODEL_FUNCTION(func_class)) {
      FUNC_PTR_MAP_T::const_iterator i = _ModelFunctions->find(func_name);
      if (i != _ModelFunctions->cend()) {
         return (*i).second->func_ptr;
      }
   } else if (IS_GUI_FUNCTION(func_class)) {
      FUNC_PTR_MAP_T::const_iterator i = _GUIFunctions->find(func_name);
      if (i != _GUIFunctions->cend()) {
         return (*i).second->func_ptr;
      }
   }
   return NULL;
}

VOID_FUNC_T _MdlFuncDefaultFactory(UCHAR_T func_class, CONST_STRING_T func_name)
{
   VOID_FUNC_T func_address = (VOID_FUNC_T)cFunctionFactory::GetFunctionAddress(func_class, func_name);
   return func_address;
}

VOID_FUNC_T _GUIFuncDefaultFactory(UCHAR_T func_class, CONST_STRING_T func_name)
{
   VOID_FUNC_T func_address = (VOID_FUNC_T)cFunctionFactory::GetFunctionAddress(func_class, func_name);
   return func_address;
}

cFunctionAddress::cFunctionAddress(CONST_STRING_T func_name, FUNC_T func_ptr, int func_class)
{
   if (_Factory == NULL) {
      _Factory = new cFunctionFactory;
   }
   _Factory->RegisterFunctionAddress(func_name, func_ptr, func_class);
}

/*
 * device and program factories
 */

cDevice * cDeviceObjectFactory::CreateDevice(cConfigurationObject * config_obj, cCell * cell)
{
   STRING_T type_name = config_obj->PropertyValue("DeviceType", "", true);
   cDeviceObject * device_object = DeviceObject(type_name.c_str());
   if (device_object != NULL) {
      return device_object->CreateDevice(config_obj, cell);
   }
   return NULL;
}

cProgram * cProgramObjectFactory::CreateProgram(cConfigurationObject * config_obj, cContext * context)
{
   STRING_T type_name = config_obj->PropertyValue("ProgramType", "", true);
   cProgramObject * program_object = ProgramObject(type_name.c_str());
   if (program_object != NULL) {
      return program_object->CreateProgram(config_obj, context);
   }
   return NULL;
}

DEVICE_OBJECT_MAP_T * cDeviceObjectFactory::_ObjectMap = NULL;
cDevice * _DeviceFactory(cConfigurationObject * config_obj, cCell * cell)
{
   return cDeviceObjectFactory::CreateDevice(config_obj, cell);
}


PROGRAM_OBJECT_MAP_T * cProgramObjectFactory::_ObjectMap = NULL;
cProgram * _ProgramFactory(cConfigurationObject * config_obj, cContext * context)
{
   return cProgramObjectFactory::CreateProgram(config_obj, context);
}


BOOL_T InitializeApplicationInterface(MDL_INIT_FUNC_T mdl_init_func,
                                      GUI_INIT_FUNC_T gui_init_func,
                                      GET_CUSTOM_TEXT_FUNC_T custom_text_func)
{
   cCustomFunctions::GUIFuncFactoryAddress(_GUIFuncDefaultFactory);
   cCustomFunctions::MdlFuncFactoryAddress(_MdlFuncDefaultFactory);
   cCustomFunctions::MdlInitFuncAddress(mdl_init_func);
   cCustomFunctions::GUIInitFuncAddress(gui_init_func);
   cCustomFunctions::GetCustomTextFuncAddress(custom_text_func);
   cCustomFunctions::DeviceCreatorFuncAddress(_DeviceFactory);
   cCustomFunctions::ProgramCreatorFuncAddress(_ProgramFactory);
   return true;
}


