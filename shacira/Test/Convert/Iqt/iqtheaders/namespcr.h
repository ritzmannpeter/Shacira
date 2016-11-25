// Namesp.h  -  Deklarationen fuer den OPC (und Corba) Namespace

#ifndef _namespcr_
#define _namespcr_

#include <namesp.h>

extern "C" {
#include <hostenum.h>
}


//
// Folgende Struktur wird an die Funktionen aus dem OPC- bzw. CORBA-Objekt
// uebergeben, die das jeweilige ITEM erstellen.
//
typedef int (*IQTVAR_READREG_F)   (REG_ACCESS_T *acc,  long *val);
typedef int (*IQTVAR_READTEXT_F)  (TEXT_ACCESS_T *acc, char *buf, int bufsize);
typedef int (*IQTVAR_WRITEREG_F)  (REG_ACCESS_T *acc,  long val);
typedef int (*IQTVAR_WRITETEXT_F) (TEXT_ACCESS_T *acc, char *buf);

// WICHTIGER HINWEIS: Jede Funktion vom Typ BIN_READ_F gibt den Zeiger auf
// einen Puffer zurueck, der hier mit malloc allociert wurde und vom Aufrufer
// mit free freigegeben werden muss.
//
typedef int (*BIN_READ_F)         (BIN_ACCESS_T *acc,  BYTE **buf, int *bufsize);
typedef int (*BIN_WRITE_F)        (BIN_ACCESS_T *acc,  BYTE *buf, int bufsize);


enum ItemInfoType {
   ITEMTYPE_REGVAR_ITEM,      // Element ist REGVAR_ITEM_T (IQT-Register)
   ITEMTYPE_TEXTVAR_ITEM,     // Element ist TEXTVAR_ITEM_T (IQT variabler Text)
   ITEMTYPE_BINARY_ITEM       // Element ist BINARY_ITEM_T (anonymer Puffer)
};


#pragma pack(8)
typedef struct {
        REG_ACCESS_T      access;
   IQTVAR_READREG_F  read_func;
   IQTVAR_WRITEREG_F write_func;
} REGVAR_ITEM_T;

#pragma pack(8)
typedef struct {
        TEXT_ACCESS_T      access;
   IQTVAR_READTEXT_F  read_func;
   IQTVAR_WRITETEXT_F write_func;
} TEXTVAR_ITEM_T;

#pragma pack(8)
typedef struct {
        BIN_ACCESS_T      access;
   BIN_READ_F        read_func;
   BIN_WRITE_F       write_func;
} BINARY_ITEM_T;
   
#pragma pack(8)
typedef struct {
        char * name;               // Voll qualifizierter Namespacename des Items     
                              // (Zeiger auf den Stack, zum sofortigen Verbrauch)
        int data_type;             // COMM_TYPE_...
        int permissions;           // COMM_PERM_...
   ItemInfoType type;
   union {
      REGVAR_ITEM_T regvar;
      TEXTVAR_ITEM_T textvar;
      BINARY_ITEM_T binvar;
   } info;
} ITEM_INFO_T;

#pragma pack()


//
// Callbackfunktion, die von OPC bzw. CORBA zur Verfuegung gestellt wird
// und jeweils ein Item erzeugt. Der void Pointer obj wird von der OPC
// bzw. CORBA-Schicht zusammen mit dem Zeiger auf die Callbackfunktion
// zur Verfuegung gestellt und wird beim Aufruf zurueckgegeben.
// Die Callbackfunktion gibt ein Handle fuer das erzeugte Item zurueck.
//
typedef long (* pCreateItemCallback) (void *obj, ITEM_INFO_T *item_info);


//
// Funktion zum Erzeugen des Namespace
//
void MakeNameSpace      (NameSpaceHandleType hndtype,
                         pCreateItemCallback callback, void *callback_data);
void MakeOPCNameSpace   (pCreateItemCallback opc_callback, void *opc_data);
void MakeCORBANameSpace (pCreateItemCallback corba_callback, void *corba_data);

//
// Funktion zum Anlegen eines neuen Browse-Objekts
//
NameSpaceBrowse *MakeNewNameSpaceBrowse ();

#endif // _namespcr_

