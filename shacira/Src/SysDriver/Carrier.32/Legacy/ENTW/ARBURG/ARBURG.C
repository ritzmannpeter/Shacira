/*.SM.***********************************************************************
*
*  MODULE-NAME:
*     ARBURG
*
*  BESCHREIBUNG:
*     ARGURG-Zugriffsfunktionen.
*
*  UMGEBUNG:
*     ZIELRECHNER:           PC-AT
*     ENTWICKLUNGSRECHNER:   PC-AT
*     UEBERSETZER:
*     OPTIONEN:
*
*  VERSION:
*     VERSION:    1.00                      DATUM:   18.03.96
*     AUTOR(EN):  Th.H.                     TELEFON: 
*
*  HISTORY:
*
*
*
*  BEMERKUNGEN:
*
*
*---------------------------------------------------------------------------
*
*  EXPORTSCHNITTSTELLE:
*
*  FUNKTIONEN:
*
*      ARBURG_Module
*
*  DATENTYPEN:
*     
*  VARIABLEN:
*
*.EM.***********************************************************************/
/***************************************************************************/
#ifndef __syntax__
#include <syntax.h>
#define __syntax__
#endif
#ifndef __stddef__
#include <stddef.h>
#define __stddef__
#endif
#ifndef __stdlib__
#include <stdlib.h>
#define __stdlib__
#endif
#ifndef __stdio__
#include <stdio.h>
#define __stdio__
#endif
#ifndef __string__
#include <string.h>
#define __string__
#endif
#ifndef __errno__
#include <errno.h>
#define __errno__
#endif
#ifndef __errcode__
#include <errcode.h>
#define __errcode__
#endif
#ifndef __basicio__
#include <basicio.h>
#define __basicio__
#endif
#ifndef __arburg__
#include <arburg.h>
#define __arburg__
#endif
#ifndef __cstdio__
#include <cstdio.h>
#define __cstdio__
#endif
#ifndef __service__
#include <service.h>
#define __service__
#endif
#ifndef __debug__
#include <debug.h>
#define __debug__
#endif
/* Für open */
#ifndef __sysstat__
#include <sys\stat.h>
#define __sysstat__
#endif
#ifndef __fcntl__
#include <fcntl.h>
#define __fcntl__
#endif
/* Für opendir */
#ifndef __direct__
#include <direct.h>
#define __direct__
#endif
#ifndef __io__
#include <io.h>
#define __io__
#endif
/*fuer die file attribute */
#ifndef __dos__
#include <dos.h>
#define __dos__
#endif

/***************************************************************************/

/* Für die Filehandle Verwaltung */
#define MAX_ARBURG_FILES 100

typedef struct arburg_cb
{  
   FILE *fp;                    // Zeiger auf die Datei
   int used;                    // benutzt(1) oder unbenutzt(0)
   long fsize;                  // Dateigröße
   long fno;                    // Dateinummer aus dem arbdir.arb Verzeichnis
   long fpos;                   // Die Aktuelle Dateiposition
   char *filename;              // Der Dateiname wird benötigt um die Attribute zu setzen
}  ARBURG_CB;

LOCAL ARBURG_CB IoBuf[MAX_ARBURG_FILES + 1] = {0};

typedef int USR_HANDLE;

/* Funktionsdeklarationen */
long filesize( FILE *fp );

/* Hilfsfunktionen   */

/*--------------------------------------------------------------------------
|Diese Funktion überprüft ob es sich bei dem Parameter file um eine Arburg
|Datei handelt.
|Vorgehensweise:
|  Dateinummer aus dem Parameter file auslesen (e0000001.arb) 
|  arbdir.dir datei öffnen.
|  überprüfen ob die Dateinummer in der Datei arbdir.dir vorhanden ist
|
----------------------------------------------------------------------------*/
LOCAL long getFileNo(char * file)
{
char full_path[_MAX_PATH];
char drive[_MAX_DRIVE];
char dir[_MAX_DIR];
char fname[_MAX_FNAME];
char ext[_MAX_EXT];

char arb_dir[_MAX_PATH];

FILE *fp;
ARB_DIR_HEADER dir_header;
ARB_DIR_ENTRY dir_entry;

long arb_compIndex;
int ret;
int records;
char dateString[11];    // wird von convert_filedate belegt 

    strcpy(full_path,file);
    _splitpath(full_path,drive,dir,fname,ext);

    // Die Dateinummer auslesen (e*.arb)
    if(sscanf(strlwr(fname), "e%7ld", &arb_compIndex) == EOF){
        return ARB_WRONG_FILENAME;
    }
    if((arb_compIndex > MAX_ARBURG_FILES - 1) || (arb_compIndex < 0)){
        return ARB_WRONG_FILENAME;
    }
    sprintf(arb_dir,"%s%s%s",drive,dir,ARB_DIRECTORY_NAME);
    fp = fopen(arb_dir,"rb");
    if(fp == NULL) {
       return ARB_FILE_NOP;
    }
    ret = ARB_ReadDirHeader(fp, &dir_header);
    if ( ret != NO_ERROR){
        fclose(fp);
        return ret;
    }
    records = dir_header.records;
    if (records ==0) {
        fclose(fp);
        return ARB_DIRECTORY_EMPTY;
    }
    if (records > ARB_MAX_FILES){
        fclose(fp);
        return ARB_INVALID_DIRECTORY_INFO;
    }

    ret = ARB_NilDirEntry(&dir_entry);
    if(ret != NO_ERROR){
        fclose(fp);
        return ret;
    }

    ret = ARB_ReadDirEntry(fp,arb_compIndex,&dir_entry);
    if(ret != NO_ERROR){
        fclose(fp);
        return ret;
    }
    fclose(fp);
    ret = convert_filedate(dir_entry.date,dateString,10,'.');
    if (ret != NO_ERROR)
       return ret ;
    else
       return arb_compIndex;
    

}
/*--------------------------------------------------------------------------
| convert_filedate schreibt das Datum aus dem ascii String
| in den String fileDate der String muß mindestens die Laenge 11
| haben. Wird kein Trennzeichen übergeben kann der String auch die Laenge 9 haben.
----------------------------------------------------------------------------*/
LOCAL int convert_filedate(const char *asciiStr, char *fileDate , int length ,char sep)
{
char c1;
char c2;
char c3;

int yearno = 0;
int monthno = 0;
int dayno = 0;
char year[3] ;
char month[3];
char day[3];

char buffer[11];

   if (length < 1)
      return ARB_WRONG_PARAMETER;

   // Die ASCII-Zeichen auslesen
   sscanf(asciiStr,"%c%c%c",&c1,&c2,&c3);

   sprintf(year,"%02x",c3);
   year[2]='\0';
   yearno = 0;
   sscanf(year,"%d",&yearno);

   sprintf(month,"%02x",c2);
   month[2]='\0';
   sscanf(month,"%d",&monthno);

   sprintf(day,"%02x",c1);
   day[2]='\0';
   sscanf(day,"%d",&dayno);

   if((monthno == 0) && (dayno == 0) && (yearno == 0))
      return ARB_EMPTY_DIR_ENTRY;
   // wenn der Monat < 1 oder groesser 12 ist Fehler zurueckgeben
   if((monthno < 1) || (monthno > 12))
      return ARB_ERR_INVALID_DATE;
   // wenn der Tag < 1 oder groesser 31 ist Fehler zurueckgeben
   if((dayno < 1) || (dayno > 31))
      return ARB_ERR_INVALID_DATE;
   // wenn die Jahreszahl kleiner als 70 ist dann wird das Jahr 2000 genommen
   if(yearno < 70)
      yearno = 20;
   else
      yearno = 19 ;

   // evtl. das Datum mit Trennzeichen zurueckgeben
   if ((sep == '.') || (sep == ',') || (sep == '/') || (sep == '\\') || (sep == ':')){
      sprintf(buffer,"%02x%c%02x%c%d%02x",c1,sep,c2,sep,yearno,c3);
      buffer[10] = '\0';
   }
   else{
      sprintf(buffer,"%02x%02x%d%02x",c1,c2,yearno,c3);
      buffer[8] = '\0';
   }
   // maximal die laenge des buffer kopieren
   if (length > strlen(buffer))
      length = strlen(buffer);

   // Den Parameter belegen
   strncpy(fileDate,buffer,length);
   if (length < strlen(buffer))
      fileDate[length] ='\0';
   else
      fileDate[strlen(buffer)] ='\0';

   return NO_ERROR;
}

/*--------------------------------------------------------------------------
|Setzt die Attribute der uebergebenen Datei auf Normal
----------------------------------------------------------------------------*/
LOCAL int ARB_SetFileAttr(char *file, int permission)
{
   if( chmod(file, permission) == -1 )
      return ARB_ATTR_ERR;
   else
      return NO_ERROR;
      
   /*ret = _dos_setfileattr(file,_A_NORMAL); S_IRUSR | S_IWUSR 
   if (ret != 0) 
      return ARB_ATTR_ERR;
   else
      return NO_ERROR;
   */
}
/*--------------------------------------------------------------------------
|Setzt die Attribute der uebergebenen Datei auf ReadOnly und Archive
----------------------------------------------------------------------------*/
LOCAL int ARB_ResetFileAttr(char *dir_file)
{unsigned ret;
   ret = _dos_setfileattr( dir_file,_A_RDONLY | _A_ARCH ); 
   if (ret != 0)
      return ARB_ATTR_ERR;
   else
      return NO_ERROR;
}
/*----------------------------------------------------------------------------
|Schreibt den uebergebenen dir_header in die Datei fp
----------------------------------------------------------------------------*/
LOCAL int ARB_WriteDirHeader(FILE *fp, ARB_DIR_HEADER dir_header)
{
int err;
    err = fseek(fp, 0L , SEEK_SET);
    if (err != 0){
       return ARB_FSEEK_ERR;
    }
    err = fwrite(&dir_header,sizeof(dir_header),1,fp);
    if ((err < 1) && (!feof(fp)))
       return ARB_WRITE_DIR_ERR;
    else
       return NO_ERROR;
}
/*----------------------------------------------------------------------------
|Initilasiert den dir_entry fuer das loeschen 
----------------------------------------------------------------------------*/
LOCAL int ARB_NilDirEntry(ARB_DIR_ENTRY *dir_entry)
{
    strcpy(dir_entry->Id,"                ");
    dir_entry->date[0] = '\0';
    dir_entry->date[1] = '\0';
    dir_entry->date[2] = '\0';
    dir_entry->time[0] = '\0';
    dir_entry->time[1] = '\0';
    dir_entry->time[2] = '\0';

   return NO_ERROR;
}
/*----------------------------------------------------------------------------
| Einen Eintrag aus dem dir_file entfernen und den Headereintrag 
| record um eins vermindern
----------------------------------------------------------------------------*/
LOCAL int ARB_EraseDirEntry (char *dir_file , long index)
{
int ret ;
int ret_temp;
FILE *fp;
ARB_DIR_ENTRY dir_entry;
ARB_DIR_HEADER dir_header;
   
    ret = ARB_SetFileAttr(dir_file);                     // Datei Attribute setzen
    If (ret != NO_ERROR) Then
        return ret;
    Endif
    fp = fopen(dir_file,"rb+");                          // Datei zum aendern oeffnen
    if(fp == NULL){
       return ARB_FILE_NOP;
    }
    ret = ARB_NilDirEntry(&dir_entry);                   // dir_entry loeschen
    If (ret != NO_ERROR) Then
      fclose(fp);
      ret_temp = ARB_ResetFileAttr(dir_file);
      return ret;
    Endif
    
    ret = ARB_WriteDirEntry(fp, index, dir_entry);       // Leere Eintrag eintragen
    If (ret != NO_ERROR) Then
      fclose(fp);
      ret_temp = ARB_ResetFileAttr(dir_file);
      return ret;
    Endif
    
    // Jetzt muss noch der Recordcounter im Header um eins vermindert werden.
    If (ret == NO_ERROR) Then
        ret = ARB_ReadDirHeader(fp, &dir_header);        // Header von arbdir.dir lesen
        If (ret != NO_ERROR) Then
            fclose(fp);
            ret_temp = ARB_ResetFileAttr(dir_file);
            return ret;
        Endif
        If (dir_header.records > 0) Then                 
            dir_header.records = dir_header.records - 1;
        Else
            fclose(fp);
            ret = ARB_ResetFileAttr(dir_file);
            return ARB_DIRECTORY_EMPTY;
        Endif
        ret = ARB_WriteDirHeader(fp, dir_header);
        If (ret != NO_ERROR )Then
            fclose(fp);
            ret_temp = ARB_ResetFileAttr(dir_file);
            return ret;
        Endif        
    Endif
    fclose(fp);
    ret = ARB_ResetFileAttr(dir_file);
    return ret;
}
/*----------------------------------------------------------------------------
| Liefert das offset anhand des index fuer den DIR_ENTRY
----------------------------------------------------------------------------*/
LOCAL long ARB_DirOffset(long index)
{
   return 10 + (22 * index);
}
/*----------------------------------------------------------------------------
|Schreibt den uebergebenen dir_entry in die Datei fp 
----------------------------------------------------------------------------*/
LOCAL int ARB_WriteDirEntry (FILE *fp, long index , ARB_DIR_ENTRY dir_entry)
{
long offset ;
int err;
long file_length;
    offset = ARB_DirOffset(index);       // offset fuer den Eintrag ermitteln
    file_length = filesize(fp);
   // Überprüfen ob die Positionierung inerhalb des gueltigen Bereichs liegt
   if((offset > file_length) || (offset < ARB_DirOffset(0)) ){
      return ARB_WRONG_FILE_POS ;
   }
   err = fseek(fp, offset, SEEK_SET);   // Den Seek-Zeiger auf offset Byte setzen
   if (err != 0){
      return ARB_FSEEK_ERR;
   }
   err = fwrite(&dir_entry,sizeof(dir_entry),1,fp);
   if ((err < 1) && (!feof(fp)))
        return ARB_WRITE_DIR_ERR;
   else
     return NO_ERROR;
}

/*----------------------------------------------------------------------------
|Liest den ARB_DIR_HEADER (arbdir.arb Datei)
----------------------------------------------------------------------------*/
LOCAL int ARB_ReadDirHeader (FILE *fp, ARB_DIR_HEADER *dir_header) 
{
int err;
   err = fseek(fp, 0L, SEEK_SET);
   if (err != 0){
      return ARB_FSEEK_ERR;
   }
   err = fread(dir_header,sizeof(*dir_header),1,fp);
   if((err < 1) && !feof(fp))
     return ARB_READ_DIR_ERR;
   else
      return NO_ERROR;
}
/*----------------------------------------------------------------------------
|Liest den ARBURG_HEADER (e*.arb Datei)
----------------------------------------------------------------------------*/
LOCAL int ARB_ReadFileHeader (FILE *fp, ARBURG_HEADER *arb_header) 
{
int err;
   err = fseek(fp, 0L, SEEK_SET);
   if (err != 0){
      return ARB_FSEEK_ERR;
   }
   err = fread(arb_header,sizeof(*arb_header),1,fp);
   if((err < 1) && !feof(fp))
      return ARB_READ_FILE_ERR;
   else
      return NO_ERROR;
 }

/*----------------------------------------------------------------------------
|Liest ein Verzeichniseintrag (aus der arbdir.arb Datei)
----------------------------------------------------------------------------*/
LOCAL int ARB_ReadDirEntry (FILE *fp, long index, ARB_DIR_ENTRY *dir_entry) 
{
long offset;
int err;
long fBasis = 0;   /*vom Dateianfang */
long file_length;
long ret;

   offset = ARB_DirOffset(index);
   file_length = filesize(fp);

   /* Überprüfen ob die Positionierung inerhalb der Dateigröße liegt*/
   if( ((fBasis + offset) > file_length) || ((fBasis + offset) < 0) ){
      return ARB_WRONG_FILE_POS ;
   }
   err = fseek(fp, offset, SEEK_SET);
   if (err != 0){
      return ARB_FSEEK_ERR;
   }
   ret = fread(dir_entry,sizeof(*dir_entry),1,fp);
   if((ret < 1) && !feof(fp))
      return ARB_READ_DIR_ERR;
   else
      return NO_ERROR;
}

/*---------------------------------------------------------------------------
| Hier werden size Byte aus der Datei (hnd) in den buffer (buf) gelesen
----------------------------------------------------------------------------*/
LOCAL int ARBURG_ReadFile(int hnd, void * buf, int size)
{
size_t ret;
long akt_pos;
long last_pos;
long pos_to_read;
FILE *fp;
  
   if ((hnd < 1) || (hnd > MAX_ARBURG_FILES))
      return ARB_WRONG_FILEHANDLE;

   if (IoBuf[hnd-1].used == 0)
      return ARB_WRONG_FILEHANDLE;

   if (size < 1)
      return ARB_WRONG_PARAMETER;

   fp = IoBuf[hnd-1].fp;
   if (fp != NULL) {
      akt_pos = IoBuf[hnd-1].fpos;
      last_pos = IoBuf[hnd-1].fsize;
      pos_to_read = akt_pos + size;
      if( pos_to_read > last_pos)
         return ARB_ERR_PAST_END;
      ret = fread(buf,size,1,fp);
      if ((ret < 1) && (!feof(fp)))
         return ARB_READ_FILE_ERR;
      else
         return NO_ERROR;
   }
   else{
      return ARB_FILE_NOP;
   } 
}
/*---------------------------------------------------------------------------
| Hier wird der buffer in die Datei (hnd) geschrieben
----------------------------------------------------------------------------*/
LOCAL int ARBURG_WriteFile(int hnd, void * buf, int size)
{
size_t ret;
FILE *fp;
long pos_to_read;
long akt_pos;
long last_pos;
   
   if ((hnd > MAX_ARBURG_FILES) || (hnd < 1))
   {
      return ARB_WRONG_FILEHANDLE;
   }
   if (IoBuf[hnd-1].used == 0){
      return ARB_WRONG_FILEHANDLE;
   }
   if (size < 1)
      return ARB_WRONG_PARAMETER;

   fp = IoBuf[hnd-1].fp ;
   if (fp != NULL) {
      akt_pos = IoBuf[hnd-1].fpos;
      last_pos = IoBuf[hnd-1].fsize;
      pos_to_read = akt_pos + size;
      if( pos_to_read > last_pos)
         return ARB_ERR_PAST_END;
      ret = fwrite(buf,size,1,fp);
      if ((ret < 1) && (!feof(fp)))
         return ARB_WRITE_FILE_ERR;
      else
         return NO_ERROR;
   }
   else{
      return ARB_FILE_NOP;
   }
}
/*---------------------------------------------------------------------------
|Die Datei löschen und den Eintrag aus der arbdir.dir entfernen
----------------------------------------------------------------------------*/
LOCAL int ARBURG_RemoveFile(char *file)
{
/*Loescht eine Arburgdatei auf einem Arburgdatentraeger  */
/*  mit allem drum und dran                              */
char full_path[_MAX_PATH];
char drive[_MAX_DRIVE];
char dir[_MAX_DIR];
char fname[_MAX_FNAME];
char ext[_MAX_EXT];

char arb_dir[_MAX_PATH];
char arb_file[_MAX_PATH];
long arb_compIndex;
int ret;

    // Den Dateinamen ueberpruefen
    strcpy(full_path,file);
    _splitpath(full_path,drive,dir,fname,ext);
    sprintf(arb_dir,"%s%s%s",drive,dir,ARB_DIRECTORY_NAME);
    sprintf(arb_file,"%s%s%s%s",drive,dir,fname,ext);

    // Die Dateinummer auslesen (e*.arb)
    if(sscanf(strlwr(fname), "e%7ld", &arb_compIndex) == EOF){
        return ARB_WRONG_FILENAME;
    }
    
    // Aus dem Arburg-Directorie den Eintrage der Datei entfernen  
    ret = ARB_EraseDirEntry(arb_dir, arb_compIndex);
    if (ret != NO_ERROR) {
        return ret; 
    }
    // Dateiattribute setzen
    ret = ARB_SetFileAttr(arb_file);
    if (ret != NO_ERROR ){
        return ret; 
    }
    // Datei loeschen
    ret = remove(arb_file);
    if(ret == 0){
       return NO_ERROR;
    }
    else{
       return ARB_REMOVE_FILE_ERR;
    }
}
/*---------------------------------------------------------------------------
|Hier wird die Datei arbdir.dir ausgelesen und die Dateien e*.arb in 
|die Struktur DIR **dir geschrieben
----------------------------------------------------------------------------*/
LOCAL int ARBURG_Directory(DIR ** dir)
{
ARBURG_HEADER arb_header;
struct find_t  fileinfo;
unsigned rc;        /* return code */
int file_count;
int ret; 
FILE *fp;
long fileno;
char full_path[_MAX_PATH];

   *dir = (DIR *)malloc(sizeof(DIR) * MAX_ARBURG_FILES);
   if(*dir == NULL)
      return ARB_NO_MEMORY;
   file_count = 0;
   rc = _dos_findfirst("A:\\e*.arb", _A_NORMAL, &fileinfo );
   while( rc == 0 ) {
      strcpy(full_path,"A:\\");
      strcat(full_path,fileinfo.name);
      fileno = getFileNo(full_path);   // Test ob es eine Arburg Datei ist
      if(0 <= fileno ){
         fp = fopen(full_path,"rb");
         if (fp != NULL) {
            ret = ARB_ReadFileHeader(fp,&arb_header);
            fclose(fp);
            if (ret != NO_ERROR){
               free(*dir); // muss evtl. noch geandert werden
               return ret;
            }
            DebugPrintf(VERBOSE, "ID %d Version1 %d length %ld mach_size %d Programm1 %.16s\n",
               arb_header.id,
               arb_header.version1,
               arb_header.length,
               arb_header.mach_size,
               arb_header.program1);
            DebugPrintf(VERBOSE, "Version2 %f Material %.16s tool %.16s Programm2 %.16s\n",
               arb_header.version2,
               arb_header.material,
               arb_header.tool,
               arb_header.program2);
            
            // Testausgabe muss beim integrieren entfern werden
            /*printf("%d\n"  ,arb_header.id);
            printf("%d\n"  ,arb_header.version1);
            printf("%ld\n" ,arb_header.length);
            printf("%d\n"  ,arb_header.mach_size);
            printf("%c\n"  ,arb_header.mach_type0);  // Char
            printf("%c\n"  ,arb_header.mach_type1);  // Char
            printf("%.16s\n",arb_header.intern_mach_size);
            printf("%f\n"  ,arb_header.version2);
            printf("%f\n"  ,arb_header.spec);
            printf("%f\n"  ,arb_header.screw_diam);
            printf("%.16s\n",arb_header.program1);
            printf("%.16s\n",arb_header.program2);
            printf("%.16s\n",arb_header.material);
            printf("%.16s\n",arb_header.tool);
            */
            sprintf((*dir)[file_count].d_name,"%s",fileinfo.name);
            (*dir)[file_count].d_size = fileinfo.size;
            file_count ++;
         }
         else{
            free(*dir); // muss evtl. noch geandert werden
            return ARB_FILE_NOP;
         }
      }
      rc = _dos_findnext( &fileinfo );
   }
   // free(*dir);
#if defined(__OS2__)
  _dos_findclose( &fileinfo );
#endif
 return file_count;

}
/*---------------------------------------------------------------------------
| hier wird ueberprueft ob die die richtige disk vorliegt
| und es werden die Parameter für driveinfo belegt.
----------------------------------------------------------------------------*/
LOCAL int ARBURG_DriveInfo(DRIVE_INFO * driveinfo)
{  DIR * dir = NULL;
   int dir_entries;
   dir_entries = ARBURG_Directory(&dir);
   If (dir_entries < 0) Then
      if (dir != NULL) free(dir);
      return dir_entries;
   Else
      if (dir != NULL) free(dir);
      driveinfo->format = ARBURG_C_FAT;
      driveinfo->version = 0;
      driveinfo->module = ARBURG_Module();
      return NO_ERROR;
   Endif
}

/*---------------------------------------------------------------------------
|Wenn die Disketten formatiert werden sollen dann muß das Verzeichnis arbdir.dir
|ausgelesen werden und die Anzahl der Dateien auf 0 gesetzt werden.
|außerdem sollten die Dateien gelöschen werden.
|
|Laut Spezifikation können die Datenträger nur an den Maschinen formatiert werden.
----------------------------------------------------------------------------*/
LOCAL int ARBURG_Format(int param)
{
   return ARB_FORMAT_IMPOSSIBLE;
}
/*---------------------------------------------------------------------------
|Anhand des headers den Typ von Arburg festlegen
|hier muesste noch eine genauere Ueberpruefung statfinden.
----------------------------------------------------------------------------*/
LOCAL int ARBURG_FileInfo(char * path, FILE_INFO * fileinfo)
{
   ARBURG_HEADER * header;
   int version;
   FILE * stream;
   long fileno;
   int ret_temp;
   int ret;
   
   memset(fileinfo, 0, sizeof(FILE_INFO));
   header = (ARBURG_HEADER *)malloc(sizeof(ARBURG_HEADER));
   if (header == NULL) return ARB_NO_MEMORY;

   // Die Dateinummer aus der Datei auslesen                                       
   fileno = getFileNo(path);    
   if ( fileno < 0){
      return fileno;
   }
   // Dateiattribute setzen
   ret = ARB_SetFileAttr(path);
   if (ret != NO_ERROR ){
       return ret; 
   }
   If ((stream = fopen(path, "rb")) != NULL) Then
      ret = ARB_ReadFileHeader(stream,header);
      If (ret != NO_ERROR) Then
         fclose(stream);
         free(header);
         ret_temp = ARB_ResetFileAttr(path);
         return ret;
      Else
         If ((version = ARBURG_Version(header)) < 0) Then
            fclose(stream);
            free(header);
            ret_temp = ARB_ResetFileAttr(path);
            return version;
         Else
            fclose(stream);
            free(header);
            fileinfo->format = ARBURG_C_FAT;
            fileinfo->version = version;
            ret_temp = ARB_ResetFileAttr(path);
            return NO_ERROR;
         Endif
      Endif
  Else        
      free(header);
      ret_temp = ARB_ResetFileAttr(path);
      return ARB_FILE_NOP;
  Endif               
}

/*---------------------------------------------------------------------------
|Hier muß die Version überprüft werden.
----------------------------------------------------------------------------*/
LOCAL int ARBURG_Version(ARBURG_HEADER * header)
{  
  return ARBURG_C;
}
/*---------------------------------------------------------------------------
| Hier wird die Datei geöffnet und ein handle auf die Datei zurückgegeben.
| die flags werden noch nicht berücksichtigt es wird jede Datei binaer
| zum lesen und schreiben geoeffnet.
----------------------------------------------------------------------------*/
LOCAL USR_HANDLE ARBURG_OpenFile(USR_WORD flags, char * filename)
{
FILE *fp;
int fh_free;
int i;
long fileno;
int ret;

   fh_free = FALSE;
   for(i = 0; i < MAX_ARBURG_FILES; i++)
   {
      if (IoBuf[i].used == 0){
         fh_free = TRUE;
         break;
      }
   }
   if(fh_free == FALSE){
      return ARB_NO_HND_FREE;
   }
   fileno = getFileNo(filename);    // Die Dateinummer aus der Datei auslesen                                       
   if ( fileno < 0){
      return fileno;
   }
   // Dateiattribute setzen
   ret = ARB_SetFileAttr(filename);
   if (ret != NO_ERROR ){
       return ret; 
   }
   If (flags & _READ) Then
      fp = fopen(filename,"rb");
      if (fp == NULL) 
         return ARB_FILE_NOP;
   Elseif (flags & _WRITE) Then
      fp = fopen(filename,"rb+");
      if (fp == NULL) 
         return ARB_FILE_NOP;
   Endif
   if (fp != NULL) {
      IoBuf[i].filename = (char *)malloc(strlen(filename)+1);
      if( IoBuf[i].filename != NULL ) {
         strcpy(IoBuf[i].filename,filename);
         IoBuf[i].fp = fp;             // Zeiger auf die Datei
         IoBuf[i].used = 1;            // benutzt(1) oder unbenutzt(0)
         IoBuf[i].fsize = filesize(fp);// Dateigröße
         IoBuf[i].fno = fileno;        // Dateinummer aus dem arbdir.arb Verzeichnis
         IoBuf[i].fpos = 0;            // Die aktuelle Dateiposition
      }
      else{
         return ARB_NO_MEMORY;
      }
   }
   else{
      return ARB_FILE_NOP;
   }
   return i + 1;

}
/*---------------------------------------------------------------------------
|Hier wird die Datei geschlossen
----------------------------------------------------------------------------*/
LOCAL int ARBURG_CloseFile(int hnd)
{
int ret;
   if ((hnd > MAX_ARBURG_FILES) || (hnd < 1))
   {
      return ARB_WRONG_FILEHANDLE;
   }
   if (IoBuf[hnd-1].used == 1){ 
      fclose(IoBuf[hnd-1].fp);
      IoBuf[hnd-1].used = 0;
      IoBuf[hnd-1].fsize = 0;
      IoBuf[hnd-1].fno = 0;
      IoBuf[hnd-1].fpos = 0;
      ret = ARB_ResetFileAttr(IoBuf[hnd-1].filename);
      free(IoBuf[hnd-1].filename);
      return ret;
   }
   else{
      return ARB_WRONG_FILEHANDLE;
   }
}

/*---------------------------------------------------------------------------
|Hier werden evtl. initialisierungen aufgerufen
----------------------------------------------------------------------------*/
LOCAL int ARBURG_Init()
{  
   return NO_ERROR;
}

/*---------------------------------------------------------------------------
|Die Dateigröße ermitteln
----------------------------------------------------------------------------*/
LOCAL long ARBURG_GetSize(int hnd)
{
   if ((hnd > MAX_ARBURG_FILES) || (hnd < 1))
   {
      return ARB_WRONG_FILEHANDLE;
   }
   if (IoBuf[hnd-1].used == 1){ 
       return IoBuf[hnd-1].fsize;
   }
   else{
      return ARB_WRONG_FILEHANDLE ;
   }
}
/*---------------------------------------------------------------------------
|Die Position in der Datei auslesen 
----------------------------------------------------------------------------*/
LOCAL long ARBURG_GetPos(int hnd)
{
long pos;

   if ((hnd > MAX_ARBURG_FILES) || (hnd < 1))
   {
      return ARB_WRONG_FILEHANDLE;
   }
   if (IoBuf[hnd-1].used == 1){ 
        pos = IoBuf[hnd-1].fpos;
        return pos;
   }
   else{
      return ARB_WRONG_FILEHANDLE;
   }
   
}
/*---------------------------------------------------------------------------
|Die Dateilaenge ermitteln
----------------------------------------------------------------------------*/
long filesize( FILE *fp )
{
 long save_pos;
 long size_of_file;
    if (fp != NULL) {
        save_pos = ftell( fp );
        fseek( fp, 0L, SEEK_END );
        size_of_file = ftell( fp );
        fseek( fp, save_pos, SEEK_SET );
        return size_of_file;
    }
    else{
        return ARB_FILE_NOP;
    }
}

/*---------------------------------------------------------------------------
|Die Position in der Datei setzen
|
|Status: muss noch getestet werden
----------------------------------------------------------------------------*/
LOCAL int ARBURG_SetPos(int hnd, long pos)
{
   int err;
   long fBasis = 0;   /*vom Dateianfang */
   long file_length; 

   if ((hnd > MAX_ARBURG_FILES) || (hnd < 1))
   {
      return ARB_WRONG_FILEHANDLE;
   }
   if (IoBuf[hnd-1].used == 1){ 
       file_length = filesize(IoBuf[hnd-1].fp);
   }
   if(file_length < 0){
      return ARB_WRONG_FILEHANDLE ;
   }
   /* Überprüfen ob die Positionierung inerhalb der Dateigröße liegt*/
   if( ((fBasis + pos) > file_length) || ((fBasis + pos) < 0) ){
      return ARB_WRONG_FILE_POS ;
   }
   err = fseek(IoBuf[hnd-1].fp, pos, SEEK_SET );
   if (err != 0){
      return err;
   }
   else{
      IoBuf[hnd-1].fpos = pos;
      return NO_ERROR;
   }  
}
/*---------------------------------------------------------------------------
|
----------------------------------------------------------------------------*/
LOCAL const DRIVE_MODULE ARBURG_DriveModule =
{
   ARBURG_OpenFile,        
   ARBURG_CloseFile,       
   ARBURG_ReadFile,        
   ARBURG_WriteFile,       
   ARBURG_GetSize,         
   ARBURG_GetPos,          
   ARBURG_SetPos,          
   ARBURG_RemoveFile,      
   ARBURG_Directory,       
   ARBURG_Format,          
   ARBURG_Init,            
   ARBURG_DriveInfo,       
   ARBURG_FileInfo
};

GLOBAL const DRIVE_MODULE * ARBURG_Module()
{
   return &ARBURG_DriveModule;
}

