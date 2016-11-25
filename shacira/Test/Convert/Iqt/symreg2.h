/*.SM.***********************************************************************
*
*  MODUL-NAME:
*     symreg2.h
*
*  BESCHREIBUNG:                                                     
*     Definition der Kommunikationsregister fuer Prozessgrafik
*
*
*  HISTORY:                                                          
*     12.06.97 -RBie-		Anpassung des Kommunikationsbereichs der Ist- bzw.
*                          Sollkurve.
*
*.EM.***********************************************************************/

#define meas_event   0x050  /* Messung laueft/fertig                         */
#define status       0x051	 /* Status, Bit 0 = 0 Download enable             */
#define startrec     0x052	 /* Start Einzelmessung                           */
 
#define reqblk_ist   0x060	 /* Request-Block Istkurve                        */
#define reqblk_soll  0x070	 /* Request-Block Sollkurve                       */
#define ackblk_ist   0x080	 /* Acknowledge-Block                             */
#define pg_mode      0x090	 /* Betriebsarten (Feld) [Funktion][Unit]         */
#define meastime     0x094	 /* Messzeiten [Funktion][Unit]                   */
#define delay        0x098	 /* Startverzoegerungen [Funktion][Unit]          */
#define interval     0x09c	 /* Messintervalle Zyklen [Funktion][Unit]        */
#define x_scale      0x0a0	 /* Maximale Weg fuer X-Achse [Funktion][Unit]    */
#define tol_switch   0x0a4	 /* Toleranz ein/aus (40) [Funktion][Unit][Kurve] */
#define tolerance    0x0e0	 /* Toleranz[%] (40) [Funktion][Unit][Kurve]      */
#define modework     0x108  /* Mode Arbeitsberechnung [Funktion][Unit]       */
#define startwork    0x10c  /* Beginn Arbeitsberechnung [Funktion][Unit]     */
#define stopwork     0x110  /* Ende Arbeitsberechnung [Funktion][Unit]       */
#define istwork      0x114  /* Arbeit Istwert [Funktion][Unit]               */
#define refwork      0x11c  /* Arbeit Referenz [Funktion][Unit]              */
#define tolwork      0x124  /* Arbeit Toleranz in % [Funktion][Unit]         */
#define pres_area    0x128  /* Schliesskolbenflaeche [Unit]                  */
#define yscal        0x12c  /* Y-Skalierung [Funktion][Unit][Kurve]          */
#define ymax         0x14c  /* Messbereichsendwert [Kanal] d. h. 4 Register  */
#define tol_errs     0x150  /* Anzahl der Toleranueberschreitungen in Folge  */
#define free_reg0    0x151  /* zur freien Verwendung waehrend der Testzeit   */
#define free_reg1    0x152  /* zur freien Verwendung waehrend der Testzeit   */
#define free_reg2    0x153  /* zur freien Verwendung waehrend der Testzeit   */
#define free_reg3    0x154  /* zur freien Verwendung waehrend der Testzeit   */
#define free_reg4    0x155  /* zur freien Verwendung waehrend der Testzeit   */
#define free_reg5    0x156  /* zur freien Verwendung waehrend der Testzeit   */
#define free_reg6    0x157  /* zur freien Verwendung waehrend der Testzeit   */
#define free_reg7    0x158  /* zur freien Verwendung waehrend der Testzeit   */
#define free_reg8    0x159  /* zur freien Verwendung waehrend der Testzeit   */
#define free_reg9    0x15a  /* zur freien Verwendung waehrend der Testzeit   */
#define pg_aggregat  0x15b  /* Prozessgrafik Aggregat fuer Mehrfarbmachinen  */
                         
#define datablk_ist  0x200	 /* Kommunikationsbereich Istkurve  [1024]        */
#define datablk_soll 0x600  /* Kommunikationsbereich Sollkurve [1024]        */

#define next_free	   0xa00

