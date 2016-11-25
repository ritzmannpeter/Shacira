
#ifndef _txtvar
#define _txtvar

/*.SI.***********************************************************************/
#include <syntax.h>
#include <dstruct.h>
/*.EI.***********************************************************************/

GLOBAL int TXTVAR_Init(BYTE init_bbram);
GLOBAL int TXTVAR_Read(char * buffer, int textind, int row, int rows, int buflen);
GLOBAL int TXTVAR_ReadElement(char * buffer, ELEMENT * element, int buflen);
GLOBAL int TXTVAR_Write(char * buffer, int textind, int row, int rows, int buflen);
GLOBAL int TXTVAR_WriteElement(char * buffer, ELEMENT * element, int buflen);
GLOBAL int TXTVAR_Size(int textind);
GLOBAL int TXTVAR_RowSize(int textind);
GLOBAL int TXTVAR_ColSize(int textind);
GLOBAL int TXTVAR_CarrierInfo(int textind);
GLOBAL int TXTVAR_Entries(void);
GLOBAL int far TXTVAR_ReadHeatText(char * buffer, int buflen,
                                   UWORD regnr, UWORD ind1, UWORD ind2);
GLOBAL int far TXTVAR_WriteHeatText(char * buffer, int buflen,
                                    UWORD regnr, UWORD ind1, UWORD ind2);

#endif /* _txtvar */

