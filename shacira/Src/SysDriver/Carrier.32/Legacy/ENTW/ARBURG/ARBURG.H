#ifndef _arburg
#define _arburg

/*.SI.***********************************************************************/
#ifndef __syntax__
#include <syntax.h>
#define __syntax__
#endif
#ifndef __cstdio__
#include <cstdio.h>
#define __cstdio__
#endif
#ifndef __direct__
#include <direct.h>
#define __direct__
#endif
/*.EI.***********************************************************************/

#define ARB_MAX_FILES           100             // Maximale Anzahl der Dateien in einem Arburgverzeichnis 
#define ARB_DIRECTORY_NAME      "arbdir.arb"    // Name des Arburgverzeichnisses 


#define ARBURG_C                200             // Die Version
#define ARBURG_C_FAT            2               // Das Format


/* Fehlerkonstante */
/*#define ARB_FORMAT_IMPOSSIBLE   -100            // Benutzt  fertig
#define ARB_WRONG_FILE_POS      -101            // Positionierng ist ausserhalb der Datei
#define ARB_WRONG_FILEHANDLE    -102            // Falscher File-handle 
#define ARB_EMPTY_DIR_ENTRY     -103            // Leerer Verzeichnis-Eintrag in der Datei arbdir.arb
#define ARB_INVALID_DIRECTORY_INFO -104         // Ungueltiger Verzeichnis-Eintrag in der Datei arbdir.arb
#define ARB_DIRECTORY_EMPTY     -105            // Alle Eintraege in der Datei arbdir.arb sind geloescht
#define ARB_WRONG_FILENAME      -106            // Falscher Dateiname bzw. nicht zwishcen 'e0000000.arb' bis 'e0000099.arb'
#define ARB_WRONG_PARAMETER     -107            // Falscher Parameter
#define ARB_ERR_PAST_END        -108            // Es wurde versucht ueber die Datei hinaus zu schreiben
#define ARB_ERR_INVALID_DATE    -109            // Beim konvertieren von ASCII-String wurde ein ungeultiges Datum festgestellt
#define ARB_NO_MEMORY           -110            // Kein Speicher mehr frei
#define ARB_FILE_NOP            -111            // Datei ist nicht geoeffnet oder konnte nicht geoeffnet werden
#define ARB_WRITE_DIR_ERR       -112            // Fehler beim schreiben in die Datei arbdir.arb mit fwrite
#define ARB_WRITE_FILE_ERR      -113            // Fehler beim schreiben mit fwrite in der Funktion ARBURG_WriteFile 
#define ARB_REMOVE_FILE_ERR     -114            // Datei konnet nicht geloescht werden
#define ARB_ATTR_ERR            -115            // Datei-Attribute konnten nicht veraendert werden
#define ARB_READ_FILE_ERR       -116            // Fehler beim lesen mit fread 
#define ARB_READ_DIR_ERR        -117            // Fehler beim lesen mit fread 
#define ARB_NO_HND_FREE         -118            // Alle File-handel sind belegt
#define ARB_FSEEK_ERR           -119            // Fehler bei der Fkt. fseek
*/


/*   Spezieller Arburg Header der Datei "E... .ARB"             */
 typedef struct {
    int      id;              // Kennung           Laenge 2    Summe 2  
    int      version1;        // Version           Laenge 2    Summe 4  
    long     length;          // Laenge            Laenge 4    Summe 8
    int      mach_size;       // Maschinen Groesse Laenge 2    Summe 10
    USR_BYTE mach_type0;      // Maschinen Typ     Laenge 2    Summe 12  
    USR_BYTE mach_type1;      // zu oben
    char    intern_mach_size[16];// Inter. Masch.G.Laenge 16   Summe 28
    float   version2;         // Version           Laenge 4    Summe 32
    float   spec;             // Sonderausfuehrung Laenge 4    Summe 36
    float   screw_diam;       // Schneckendurchmes.Laenge 4    Summe 40
    char    program1[16];     // Programmbez. 1    Laenge 16   Summe 56
    char    program2[16];     // Programmbez. 2    Laenge 16   Summe 72
    /*Die naechsten zwei Komponenten sind laut Arburg-Spezifikation */
    /*gegen die Praxiserfahrungen bei TRW */
    char    material[16];     // Werkzeugbez.      Laenge 16   Summe 88
    char    tool[16];         // Materialbez.      Laenge 16   Summe 104
    char    cylinder[16];     // Zylinderbez.      Laenge 16   Summe 120
    int     tool_code;        // Werkzeugcode.     Laenge 2    Summe 122
    int     cylinder_code;    // Zylindercode.     Laenge 2    Summe 124
    int     w_length;         // WORD Laenge       Laenge 2    Summe 126
    int     dw_length;        // DWORD Laenge      Laenge 2    Summe 128
    int     r_length;         // REAL Laenge       Laenge 2    Summe 130
    int     t_length;         // TEXT Laenge       Laenge 2    Summe 132
   }ARBURG_HEADER;
   /* Ehemals FILE_HEADER   */

/*   Spezieller Header des Arburgverzeichnisses "ARBDIR.ARB"        */
/*   Das Arburgverzeichnis ist eine DOS-Datei mit zusaetzlichen     */
/*   Verzeichnisinformationen.                                      */

typedef struct {
    char    filler1[8];
    int     records ;
    } ARB_DIR_HEADER;
    
/*   Verzeichniseintrag in "ARBDIR.ARB"                             */

typedef struct{
    char Id[16];
    char date[3];
    char time[3];
    } ARB_DIR_ENTRY;

GLOBAL DRIVE_MODULE * ARBURG_Module();

#endif /* ifndef _arburg */
