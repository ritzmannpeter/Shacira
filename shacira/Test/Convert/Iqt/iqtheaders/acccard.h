/*.SH.***********************************************************************
*
*  HEADER-DATEI-NAME:
*     ACCCARD.H
*
*  BESCHREIBUNG:
*
*  HISTORY:                                                          
*     08.11.00 -TSchw- Implementierung                               
*                                                                    
*  VERSION:                                                          
*     VERSION:  1.0              AUTOR:       T.Schwoerer            
*     DATUM:    08.11.2000                                           
*                                                                    
*  UMGEBUNG:                                                         
*     ZIELRECHNER:          Industrie-PC (Provit 2001/5000)          
*     BETRIEBSSYSTEM:       Windows NT / Linux                       
*     PROGRAMMIERSPRACHE:   VC 5 / gcc                               
*
*  BEMERKUNGEN:
*
*.EH.***********************************************************************/

#ifndef _acccard
#define _acccard

#include <devcard.h>

GLOBAL void Accesscard_CheckChange   (void);
GLOBAL int Accesscard_MakeNew        (short int keycode, char *pers_nr);
GLOBAL int Accesscard_DirectReadCard (UWORD keycode_reg,  UWORD accessmask_reg,
                                      UWORD persnr_text,  BOOL  read_fot,
                                      UWORD fotpage1_reg, UWORD fotpage2_reg,
                                      UWORD fotpage3_reg);
GLOBAL void Accesscard_SetLockPage   (int pagenr);

#endif /* _acccard */








