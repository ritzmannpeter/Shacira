
#ifndef _cTransformationHandler_h_
#define _cTransformationHandler_h_

#include "Conversion/cFMFatFile.h"
#include "Conversion/cSubfile.h"
#include "Conversion/cHeader.h"
#include "Conversion/cHeatGroup.h"
#include "Conversion/cHeatZone.h"
#include "Conversion/cHeatText.h"
#include "Conversion/cProcessGraphic.h"
#include "Conversion/cNewProcessGraphic.h"
#include "Conversion/cRegister.h"
#include "Conversion/cTextVar.h"
#include "System/Database/cContext.h"
#include "System/Database/cVariable.h"

class cContext;

class cTransformationHandler {
public:
   cTransformationHandler(cFMFatFile * legacy_file, cContext * context);
   virtual ~ cTransformationHandler();
   BOOL_T Process();
   virtual BOOL_T HandleHeader(cHeader * header); 
   virtual BOOL_T HandleRegister(cHeader * header, cSubfile * subfile,
                                 cRegister * reg);
   virtual BOOL_T HandleTextVar(cHeader * header, cSubfile * subfile,
                                cTextVar * textvar);
   virtual BOOL_T HandleHeatZone(cHeader * header, cSubfile * subfile,
                                 cHeatGroup * heatgroup, cHeatZone * heatzone);
   virtual BOOL_T HandleHeatText(cHeader * header, cSubfile * subfile,
                                 cHeatGroup * heatgroup, cHeatText * heattext);
   virtual BOOL_T HandleProcessGraphic(cHeader * header, cSubfile * subfile,
                                       cProcessGraphic * processgraphic);
   virtual BOOL_T HandleNewProcessGraphic(cHeader * header, cSubfile * subfile,
                                          cNewProcessGraphic * processgraphic);
   virtual BOOL_T HandleEM17Data(cHeader * header, cSubfile * subfile,
                                 cEM17Data * em17_data);
protected:
   BOOL_T SetFlag(CONST_STRING_T var_name, Flags flag, BOOL_T value);
   BOOL_T GetVar(CONST_STRING_T var_name, LONG_T & value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);
   BOOL_T GetVar(CONST_STRING_T var_name, DOUBLE_T & value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);
   BOOL_T GetVar(CONST_STRING_T var_name, STRING_T & value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);
   BOOL_T SetVar(CONST_STRING_T var_name, LONG_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);
   BOOL_T SetVar(CONST_STRING_T var_name, DOUBLE_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);
   BOOL_T SetVar(CONST_STRING_T var_name, CONST_STRING_T value, LONG_T i1 = -1, LONG_T i2 = -1, LONG_T i3 = -1, LONG_T i4 = -1);
protected:
   cFMFatFile * _LegacyFile;
   cContext * _Context;
};

#endif





