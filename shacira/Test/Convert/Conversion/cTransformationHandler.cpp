
#include "FirstHeader.h"
#include "cTransformationHandler.h"

extern void Out(const char * text);

#define APP_ERROR(e) \
   Out(e);
#define UNHANDLED_ERROR() \
   Out("unhandled exception");

cTransformationHandler::cTransformationHandler(cFMFatFile * legacy_file, cContext * context)
{
   _LegacyFile = legacy_file;
   _Context = context;
}

cTransformationHandler::~cTransformationHandler()
{
}

BOOL_T cTransformationHandler::Process()
{
   cHeader * header = _LegacyFile->Header();
   HandleHeader(header);
   SUBFILE_LIST_T subfiles;
   _LegacyFile->Subfiles(subfiles);
   SUBFILE_LIST_T::const_iterator i = subfiles.begin();
   while (i != subfiles.end()) {
      cSubfile * subfile = (*i);
      if (subfile != NULL) {
         HEATGROUP_MAP_T heatgroup_map;
         subfile->HeatGroupMap(heatgroup_map);
         HEATGROUP_MAP_T::const_iterator k = heatgroup_map.begin();
         while (k != heatgroup_map.end()) {
            cHeatGroup * heat_group = (*k).second;
            if (heat_group != NULL) {
               ZONE_MAP_T zone_map;
               heat_group->ZoneMap(zone_map);
               ZONE_MAP_T::const_iterator z = zone_map.begin();
               while (z != zone_map.end()) {
                  cHeatZone * heat_zone = (*z).second;
                  if (heat_zone != NULL) {
                     HandleHeatZone(header, subfile, heat_group, heat_zone);
                  }
                  z++;
               }
            }
            k++;
         }
         REGISTER_MAP_T reg_map;
         subfile->RegisterMap(reg_map);
         REGISTER_MAP_T::const_iterator i = reg_map.begin();
         while (i != reg_map.end()) {
            cRegister * reg = (*i).second;
            if (reg != NULL) {
               HandleRegister(header, subfile, reg);
            }
            i++;
         }
         TEXTVAR_MAP_T textvar_map;
         subfile->TextVarMap(textvar_map);
         TEXTVAR_MAP_T::const_iterator j = textvar_map.begin();
         while (j != textvar_map.end()) {
            cTextVar * text_var = (*j).second;
            if (text_var != NULL) {
               HandleTextVar(header, subfile, text_var);
            }
            j++;
         }
         HEATTEXT_MAP_T heattext_map;
         subfile->HeatTextMap(heattext_map);
         HEATTEXT_MAP_T::const_iterator l = heattext_map.begin();
         while (l != heattext_map.end()) {
            cHeatText * heat_text = (*l).second;
            if (heat_text != NULL) {
               HandleHeatText(header, subfile, NULL, heat_text);
            }
            l++;
         }
         cProcessGraphic * process_graphic = subfile->ProcessGraphic();
         if (process_graphic != NULL) {
            HandleProcessGraphic(header, subfile, process_graphic);
         }
         cNewProcessGraphic * new_process_graphic = subfile->NewProcessGraphic();
         if (process_graphic != NULL) {
            HandleNewProcessGraphic(header, subfile, new_process_graphic);
         }
         cEM17Data * em17_data = subfile->EM17Data();
         if (em17_data != NULL) {
            HandleEM17Data(header, subfile, em17_data);
         }
      }
      i++;
   }
   return true;
}

BOOL_T cTransformationHandler::HandleHeader(cHeader * header)
{
   return true;
}

BOOL_T cTransformationHandler::HandleRegister(cHeader * header, cSubfile * subfile,
                                              cRegister * reg)
{
   return true;
}

BOOL_T cTransformationHandler::HandleTextVar(cHeader * header, cSubfile * subfile,
                                             cTextVar * textvar)
{
   return true;
}

BOOL_T cTransformationHandler::HandleHeatZone(cHeader * header, cSubfile * subfile,
                                              cHeatGroup * heatgroup, cHeatZone * heatzone)
{
   return true;
}

BOOL_T cTransformationHandler::HandleHeatText(cHeader * header, cSubfile * subfile,
                                              cHeatGroup * heatgroup, cHeatText * heattext)
{
   return true;
}

BOOL_T cTransformationHandler::HandleProcessGraphic(cHeader * header, cSubfile * subfile,
                                                    cProcessGraphic * processgraphic)
{
   return true;
}

BOOL_T cTransformationHandler::HandleNewProcessGraphic(cHeader * header, cSubfile * subfile,
                                                       cNewProcessGraphic * processgraphic)
{
   return true;
}

BOOL_T cTransformationHandler::HandleEM17Data(cHeader * header, cSubfile * subfile,
                                              cEM17Data * em17_data)
{
   return true;
}

BOOL_T cTransformationHandler::SetFlag(CONST_STRING_T var_name, Flags flag, BOOL_T value)
{
   try {
      cVariable * variable = _Context->Variable(var_name);
      if (variable == NULL) {
         return false;
      } else {
         variable->SetFlag(Header, true);
      }
   } catch (cError & e) {
      APP_ERROR(e);
      return false;
   } catch (...) {
      UNHANDLED_ERROR();
      return false;
   }
   return true;
}

BOOL_T cTransformationHandler::GetVar(CONST_STRING_T var_name, LONG_T & value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   try {
      cVariable * variable = _Context->Variable(var_name);
      if (variable == NULL) {
         return false;
      } else {
         variable->Get(value, i1, i2, i3, i4);
      }
   } catch (cError & e) {
      APP_ERROR(e);
      return false;
   } catch (...) {
      UNHANDLED_ERROR();
      return false;
   }
   return true;
}

BOOL_T cTransformationHandler::GetVar(CONST_STRING_T var_name, DOUBLE_T & value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   try {
      cVariable * variable = _Context->Variable(var_name);
      if (variable == NULL) {
         return false;
      } else {
         variable->Get(value, i1, i2, i3, i4);
      }
   } catch (cError & e) {
      APP_ERROR(e);
      return false;
   } catch (...) {
      UNHANDLED_ERROR();
      return false;
   }
   return true;
}

BOOL_T cTransformationHandler::GetVar(CONST_STRING_T var_name, STRING_T & value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   try {
      cVariable * variable = _Context->Variable(var_name);
      if (variable == NULL) {
         return false;
      } else {
         variable->Get(value, i1, i2, i3, i4);
      }
   } catch (cError & e) {
      APP_ERROR(e);
      return false;
   } catch (...) {
      UNHANDLED_ERROR();
      return false;
   }
   return true;
}

BOOL_T cTransformationHandler::SetVar(CONST_STRING_T var_name, LONG_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   try {
      cVariable * variable = _Context->Variable(var_name);
      if (variable == NULL) {
         return false;
      } else {
         variable->Set(value, i1, i2, i3, i4);
      }
   } catch (cError & e) {
      APP_ERROR(e);
      return false;
   } catch (...) {
      UNHANDLED_ERROR();
      return false;
   }
   return true;
}

BOOL_T cTransformationHandler::SetVar(CONST_STRING_T var_name, DOUBLE_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   try {
      cVariable * variable = _Context->Variable(var_name);
      if (variable == NULL) {
         return false;
      } else {
         variable->Set(value, i1, i2, i3, i4);
      }
   } catch (cError & e) {
      APP_ERROR(e);
      return false;
   } catch (...) {
      UNHANDLED_ERROR();
      return false;
   }
   return true;
}

BOOL_T cTransformationHandler::SetVar(CONST_STRING_T var_name, CONST_STRING_T value, LONG_T i1, LONG_T i2, LONG_T i3, LONG_T i4)
{
   try {
      cVariable * variable = _Context->Variable(var_name);
      if (variable == NULL) {
         return false;
      } else {
         variable->Set(value, i1, i2, i3, i4);
      }
   } catch (cError & e) {
      APP_ERROR(e);
      return false;
   } catch (...) {
      UNHANDLED_ERROR();
      return false;
   }
   return true;
}

