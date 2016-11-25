
#include "FirstHeader.h"
#include "cFMTestHandler.h"
#include "iqtreg.h"
#include "iqtbit.h"
#include "iscosreg.h"
#include "iscosbit.h"
#include "textvar.h"

typedef DOUBLE_T (*CONV_FUNC)(DOUBLE_T value, cHeader * header, int function_unit);

/// conversion table for registers
typedef struct {
   /// source description
   int reg_no;        /// register number (iqtreg.h, iscosreg.h)
   int index;         /// in case of array types (10, 20)
   int precision;     /// fixed decimal precision
   int function_unit; /// function unit -1 = no function unit
   /// destination description
   const char * var_name;
   int i1;
   int i2;
   int i3;
   int i4;
   CONV_FUNC conv_func;
} CONVERT_REGISTER_T;

/// conversion table for texts
typedef struct {
   /// source description
   int text_id;      /// text ident (textvar.h)
   /// destination description
   const char * var_name;
   int i1;
   int i2;
   int i3;
   int i4;
} CONVERT_TEXT_T;

DOUBLE_T Value(int value, cHeader * header, UCHAR_T precision, int function_unit)
{
   DOUBLE_T result = 0;
   if (precision > 0) {
      result = (((DOUBLE_T)value) / ((DOUBLE_T)precision*10));
   } else {
      result = value;
   }
   return result;
}

static DOUBLE_T vol (DOUBLE_T way, long diameter)
{
   DOUBLE_T Q = 0;
   DOUBLE_T D = diameter;
   DOUBLE_T V = way;
   D *= D*355;
   Q = D / 452;
   V /= 1000;
   DOUBLE_T ret = (Q == 0) ? 0 : (FLOAT_T)(V * Q);
   return ret;
}

DOUBLE_T Volume(DOUBLE_T value, cHeader * header, int function_unit)
{
   return vol(value, header->_Diameter[0]);
}

static const CONVERT_REGISTER_T _ConvertRegisterTable[] =
{
   /// Plastifizierweg Aggregat 1
   {XSSDOS1, -1, 1, 0, "SetStrPlstShotSize", 0, -1, -1, -1, Volume},
   /// Plastifizierweg Aggregat 2
   {XSSDOS2, -1, 1, 1, "SetStrPlstShotSize", 1, -1, -1, -1, Volume}
};
#define REG_ENTRIES (sizeof(_ConvertRegisterTable)/sizeof(CONVERT_REGISTER_T))

const CONVERT_REGISTER_T * RegConvTableEntry(int reg_no, int index)
{
   const CONVERT_REGISTER_T * entry = NULL;
   int i = 0;
   for (i=0; i<REG_ENTRIES; i++) {
      entry = &(_ConvertRegisterTable[i]);
      if (entry->reg_no == reg_no) {
         if (entry->index == -1 ||
             entry->index == index) {
            return entry;
         }
      }
   }
   return NULL;
}

static const CONVERT_TEXT_T _ConvertTextTable[] =
{
   /// frei beschreibbare Seite 1
   {TEXTVAR_FREEPAGE1, "SetNoteTxt", -1, -1, -1, -1},
   /// frei beschreibbare Seite 2
   {TEXTVAR_FREEPAGE2, "SetNoteTxt", -1, -1, -1, -1}
};
#define TEXT_ENTRIES (sizeof(_ConvertTextTable)/sizeof(CONVERT_TEXT_T))

const CONVERT_TEXT_T * TextConvTableEntry(int text_id)
{
   const CONVERT_TEXT_T * entry = NULL;
   int i = 0;
   for (i=0; i<REG_ENTRIES; i++) {
      entry = &(_ConvertTextTable[i]);
      if (entry->text_id == text_id) {
         return entry;
      }
   }
   return NULL;
}

DOUBLE_T ConvValue(cHeader * header, const CONVERT_REGISTER_T * entry, LONG_T value)
{
   DOUBLE_T result = value;
   UCHAR_T precision = entry->precision;
   if (precision > 0) {
      result = result / (DOUBLE_T)(precision * 10);
   } 
   CONV_FUNC func = entry->conv_func;
   if (func != NULL) {
      result = func(result, header, entry->function_unit);
   }
   return result;
}


cFMTestHandler::cFMTestHandler(cFMFatFile * legacy_file, cContext * context)
   : cTransformationHandler(legacy_file, context)
{
}

cFMTestHandler::~cFMTestHandler()
{
}

BOOL_T cFMTestHandler::HandleHeader(cHeader * header)
{
   /// mark header usage
   SetFlag("MashineNr", Header, true);
   SetFlag("SetDescMachMldName", Header, true);
   SetFlag("SetDescMachTxtMaterial", Header, true);
   SetFlag("SetStsMldDatasetVersion", Header, true);
   SetFlag("SetCfgMachUseScrewDiameter", Header, true);

   /// set data
   SetVar("MashineNr", header->_MashType.c_str());
   SetVar("SetDescMachMldName", header->_ToolNr.c_str());
   int agg_count = header->_MaxAgg;
   int aggregat = 0;
   for (aggregat=0; aggregat<agg_count; aggregat++) {
      SetVar("SetDescMachTxtMaterial", header->_MatNr.c_str(), aggregat);
      SetVar("SetCfgMachUseScrewDiameter", (LONG_T)header->_Diameter[0], aggregat);
   }
   return true;
}

BOOL_T cFMTestHandler::HandleRegister(cHeader * header, cSubfile * subfile,
                                      cRegister * reg)
{
   int elements = reg->_Elements;
   int index = 0;
   for (index=0; index<elements; index++) {
      const CONVERT_REGISTER_T * entry = RegConvTableEntry(reg->_RegNo, index);
      if (entry != NULL) {
         LONG_T lval = reg->LongValue(index);
         if (entry->precision > 0 ||
             entry->conv_func != NULL) {
            DOUBLE_T dval = ConvValue(header, entry, lval);
            SetVar(entry->var_name,
                   dval,
                   entry->i1,
                   entry->i2,
                   entry->i3,
                   entry->i4);
         } else {
            SetVar(entry->var_name,
                   lval,
                   entry->i1,
                   entry->i2,
                   entry->i3,
                   entry->i4);
         }
      } else {
         /// not found in mapping
         int dummy = 0;
      }
   }
   return true;
}

BOOL_T cFMTestHandler::HandleTextVar(cHeader * header, cSubfile * subfile,
                                     cTextVar * textvar)
{
   const CONVERT_TEXT_T * entry = TextConvTableEntry(textvar->_TextId);
   if (entry != NULL) {
      STRING_T text = textvar->Text();
      SetVar(entry->var_name,
             text.c_str(),
             entry->i1,
             entry->i2,
             entry->i3,
             entry->i4);
   } else {
      /// not found in mapping
      int dummy = 0;
   }
   return true;
}

BOOL_T cFMTestHandler::HandleHeatZone(cHeader * header, cSubfile * subfile,
                                      cHeatGroup * heatgroup, cHeatZone * heatzone)
{
   /// zone related data
   LONG_T set = heatzone->Set() / 10;
   LONG_T tol_up_narrow = heatzone->TolUpNarrow() / 10;
   LONG_T tol_down_narrow = heatzone->TolDownNarrow() / 10;
   LONG_T tol_up_wide = heatzone->TolUpWide() / 10;
   LONG_T tol_down_wide = heatzone->TolDownWide() / 10;
   /// no of heating zone
   LONG_T zone = heatzone->_ZoneId;
   /// no of unit starts with 1 in legacy files
   LONG_T unit = heatzone->_UnitId - 1;
   char var_name[0x100] = {0};
   int id = heatgroup->_GroupId;
   if (id == BARREL_GROUP) {
      SetVar("SetTmpBrlZn", set, zone, unit);
      SetVar("TolTmpBrlZnHdevNarrow", tol_up_narrow, zone, unit);
      SetVar("TolTmpBrlZnLdevNarrow", tol_down_narrow, zone, unit);
      SetVar("TolTmpBrlZnHdevWide", tol_up_wide, zone, unit);
      SetVar("TolTmpBrlZnLdevWide", tol_down_wide, zone, unit);
   } else if (id == TOOL_GROUP) {
      SetVar("SetTmpToolZn", set, zone, unit);
      SetVar("TolTmpToolZnHdevNarrow", tol_up_narrow, zone, unit);
      SetVar("TolTmpToolZnLdevNarrow", tol_down_narrow, zone, unit);
      SetVar("TolTmpToolZnHdevWide", tol_up_wide, zone, unit);
      SetVar("TolTmpToolZnLdevWide", tol_down_wide, zone, unit);
   } else if (id == TEMP_GROUP) {
      SetVar("SetTmpTempZn", set, zone, unit);
      SetVar("TolTmpTempZnHdevNarrow", tol_up_narrow, zone, unit);
      SetVar("TolTmpTempZnLdevNarrow", tol_down_narrow, zone, unit);
      SetVar("TolTmpTempZnHdevWide", tol_up_wide, zone, unit);
      SetVar("TolTmpTempZnLdevWide", tol_down_wide, zone, unit);
   } else if (id == OIL_GROUP) {
      SetVar("SetTmpOilZn", set);
      SetVar("TolTmpOilZnHdevNarrow", tol_up_narrow);
      SetVar("TolTmpOilZnLdevNarrow", tol_down_narrow);
      SetVar("TolTmpOilZnHdevWide", tol_up_wide);
      SetVar("TolTmpOilZnLdevWide", tol_down_wide);
   }
   return true;
}

BOOL_T cFMTestHandler::HandleHeatText(cHeader * header, cSubfile * subfile,
                                      cHeatGroup * heatgroup, cHeatText * heattext)
{
   return true;
}

BOOL_T cFMTestHandler::HandleProcessGraphic(cHeader * header, cSubfile * subfile,
                                            cProcessGraphic * processgraphic)
{
   return true;
}

