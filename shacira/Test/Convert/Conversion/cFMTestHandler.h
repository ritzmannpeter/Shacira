
#ifndef _cFMTestHandler_h_
#define _cFMTestHandler_h_

#include "Conversion/cTransformationHandler.h"

class cFMTestHandler : public cTransformationHandler
{
public:
   cFMTestHandler(cFMFatFile * legacy_file, cContext * context);
   virtual ~ cFMTestHandler();
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
};

#endif





