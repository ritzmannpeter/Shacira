
#include "FirstHeader.h"
#include "cProcessGraphic.h"
#include "cFMFatFile.h"

cProcessGraphic::cProcessGraphic(cFMFatFile * file, cSubfile * sub_file, SOLL_INFO * pg_info, unsigned_8 * curve_buffer)
{
   _File = file;
   _Subfile = sub_file;
   _Mode = pg_info->mode_info.mode;
   _Delay = pg_info->mode_info.delay;
   _Time = pg_info->mode_info.time;
   _Mint = pg_info->mode_info.mint;
   _Vinter = pg_info->mode_info.vinter;
   _Soll_chan[0] = pg_info->soll_chan[0];
   _Soll_chan[1] = pg_info->soll_chan[1];
   _Soll_max[0] = pg_info->soll_max[0]; 
   _Soll_max[1] = pg_info->soll_max[1]; 
   _Tol[0] = pg_info->tol[0];
   _Tol[1] = pg_info->tol[1];
   memcpy(&_Curve1[0], curve_buffer, sizeof(_Curve1));
   curve_buffer += sizeof(_Curve1);
   memcpy(&_Curve2[0], curve_buffer, sizeof(_Curve2));
   _Subfile->SetProcessGraphic(this);
}

cProcessGraphic::~cProcessGraphic()
{
}

void cProcessGraphic::Print(STRING_T & doc)
{
}


