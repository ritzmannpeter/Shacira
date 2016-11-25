
#include "FirstHeader.h"
#include "cHeatText.h"
#include "cHeatGroup.h"
#include "cFMFatFile.h"

cHeatText::cHeatText(cFMFatFile * file, cSubfile * sub_file, int reg_no, int ind1, int ind2, const char * text)
{
   _File = file;
   _Subfile = sub_file;
   _RegNo = reg_no;
   _Ind1 = ind1;
   _Ind1 = ind2;
   _Text = text;
   int group_id = cHeatGroup::GroupId(reg_no);
   cHeatGroup * heat_group = _File->HeatGroup(group_id);
   cHeatZone * heat_zone = heat_group->Zone(ind2, ind1);
   if (heat_zone != NULL) {
      heat_zone->_ZoneName = text;
   }
}

cHeatText::~cHeatText()
{
}

void cHeatText::Print(STRING_T & doc)
{
}

STRING_T cHeatText::Text()
{
   return _Text;
}

