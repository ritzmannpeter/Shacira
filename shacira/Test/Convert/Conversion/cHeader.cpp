
#include "FirstHeader.h"
#include "cHeader.h"

static ULONG_T MakeDate(ULONG_T date)
{
   return 0;
}

cHeader::cHeader(cFMFatFile * file, FILE_HEADER_T * header)
{
   _File = file;
   char buf[0x100] = {0};
   _Version = header->Version;
   _HeaderSize = header->HeaderSize;
   _FileType  = header->FileType;
   _Date = MakeDate(header->Date);
   _RegType = header->RegType;
   memset(buf, 0, sizeof(buf));
   memcpy(buf, header->InfoText, sizeof(header->InfoText));
   _InfoText = buf;
   memset(buf, 0, sizeof(buf));
   memcpy(buf, header->MashType, sizeof(header->MashType));
   _MashType = buf;
   memset(buf, 0, sizeof(buf));
   memcpy(buf, header->MatNr, sizeof(header->MatNr));
   _MatNr = buf;
   memset(buf, 0, sizeof(buf));
   memcpy(buf, header->ToolNr, sizeof(header->ToolNr));
   _ToolNr = buf;
   _ProgNr = header->ProgNr;
   _MashSize = header->MashSize;
   _MouldOpWay = header->MouldOpWay;
   _VersMash = header->VersMash;
   _VersStruct = header->VersStruct;
   _VersExtra = header->VersExtra;
   _MaxAgg = header->MaxAgg;

   memset(_MouldInPres, 0, sizeof(_MouldInPres));
   memset(_MaxSpritzDruck, 0, sizeof(_MaxSpritzDruck));
   memset(_Diameter, 0, sizeof(_Diameter));
   memset(_PresConst, 0, sizeof(_PresConst));
   memset(_Aggregat, 0, sizeof(_Aggregat));
   memset(_HeatZoneCount, 0, sizeof(_HeatZoneCount));
   memset(_ScrewSuckBack, 0, sizeof(_ScrewSuckBack));
   memset(_PlastWay, 0, sizeof(_PlastWay));

   _MouldInPres[0] = header->MouldInPres;
   _MaxSpritzDruck[0] = header->MaxSpritzDruck;
   _Diameter[0] = header->Diameter;
   _PresConst[0] = header->PresConst;
   _Aggregat[0] = header->Aggregat;
   _HeatZoneCount[0] = header->HeatZoneCount;
   _ScrewSuckBack[0] = header->ScrewSuckBack;
   _PlastWay[0] = header->PlastWay;

   if (_MaxAgg < 2) {
      return;
   }
   _MouldInPres[1] = header->MouldInPres2;
   _MaxSpritzDruck[1] = header->MaxSpritzDruck2;
   _Diameter[1] = header->Diameter2;
   _PresConst[1] = header->PresConst2;
   _Aggregat[1] = header->Aggregat2;
   _HeatZoneCount[1] = header->HeatZoneCount2;
   _ScrewSuckBack[1] = header->ScrewSuckBack2;
   _PlastWay[1] = header->PlastWay2;

   if (_MaxAgg < 3) {
      return;
   }
   _MouldInPres[2] = header->MouldInPres3;
   _MaxSpritzDruck[2] = header->MaxSpritzDruck3;
   _Diameter[2] = header->Diameter3;
   _PresConst[2] = header->PresConst3;
   _Aggregat[2] = header->Aggregat3;
   _HeatZoneCount[2] = header->HeatZoneCount3;
   _ScrewSuckBack[2] = header->ScrewSuckBack3;
   _PlastWay[2] = header->PlastWay3;

   if (_MaxAgg < 4) {
      return;
   }
   _MouldInPres[3] = header->MouldInPres4;
   _MaxSpritzDruck[3] = header->MaxSpritzDruck4;
   _Diameter[3] = header->Diameter4;
   _PresConst[3] = header->PresConst4;
   _Aggregat[3] = header->Aggregat4;
   _HeatZoneCount[3] = header->HeatZoneCount4;
   _ScrewSuckBack[3] = header->ScrewSuckBack4;
   _PlastWay[3] = header->PlastWay4;

   if (_MaxAgg < 5) {
      return;
   }
   _MouldInPres[4] = header->MouldInPres5;
   _MaxSpritzDruck[4] = header->MaxSpritzDruck5;
   _Diameter[4] = header->Diameter5;
   _PresConst[4] = header->PresConst5;
   _Diameter[4] = header->PresConst5;
   _Aggregat[4] = header->Aggregat5;
   _HeatZoneCount[4] = header->HeatZoneCount5;
   _ScrewSuckBack[4] = header->ScrewSuckBack5;
   _PlastWay[4] = header->PlastWay5;

   if (_MaxAgg < 6) {
      return;
   }
   _MouldInPres[5] = header->MouldInPres6;
   _MaxSpritzDruck[5] = header->MaxSpritzDruck6;
   _Diameter[5] = header->Diameter6;
   _PresConst[5] = header->PresConst6;
   _Aggregat[5] = header->Aggregat6;
   _HeatZoneCount[5] = header->HeatZoneCount6;
   _ScrewSuckBack[5] = header->ScrewSuckBack6;
   _PlastWay[5] = header->PlastWay6;

   if (_MaxAgg < 7) {
      return;
   }
   _MouldInPres[6] = header->MouldInPres7;
   _MaxSpritzDruck[6] = header->MaxSpritzDruck7;
   _Diameter[6] = header->Diameter7;
   _PresConst[6] = header->PresConst7;
   _Aggregat[6] = header->Aggregat7;
   _HeatZoneCount[6] = header->HeatZoneCount7;
   _ScrewSuckBack[6] = header->ScrewSuckBack7;
   _PlastWay[6] = header->PlastWay7;

   if (_MaxAgg < 8) {
      return;
   }
   _MouldInPres[7] = header->MouldInPres8;
   _MaxSpritzDruck[7] = header->MaxSpritzDruck8;
   _Diameter[7] = header->Diameter8;
   _PresConst[7] = header->PresConst8;
   _Aggregat[7] = header->Aggregat8;
   _HeatZoneCount[7] = header->HeatZoneCount8;
   _ScrewSuckBack[7] = header->ScrewSuckBack8;
   _PlastWay[7] = header->PlastWay8;

}

cHeader::~cHeader()
{
}

void cHeader::Print(STRING_T & doc)
{
}


