/******************************************************************************
*  Dateiname : sprinter.h
*
*  HISTORY
*     02.03.00 -TSchw-  Implementierung
*
*  Beschreibung :
******************************************************************************/


#ifndef __sprinter__
#define __sprinter__

int SPRINTER_Implemented ();
int SPRINTER_EnumPrinter (char ***printer_list, int *num_printer);
int SPRINTER_SelectPrinter (int printer_index);
int SPRINTER_PrintText (char *text, int len);
int SPRINTER_PrintString (char *text);
int SPRINTER_PrintBitmap (void *buf);
void SPRINTER_Lf ();
void SPRINTER_Cr ();
void SPRINTER_CrLf ();
void SPRINTER_Ff ();
int SPRINTER_SetColor (int color);
int SPRINTER_SetBgColor (int color);
int SPRINTER_SetFontWide ();
int SPRINTER_SetFontNarrow ();

#endif /* __sprinter__ */

