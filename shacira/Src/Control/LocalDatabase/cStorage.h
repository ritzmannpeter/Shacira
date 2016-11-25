//## begin module%4039D91C00DA.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4039D91C00DA.cm

//## begin module%4039D91C00DA.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4039D91C00DA.cp

//## Module: cStorage%4039D91C00DA; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cStorage.h

#ifndef cStorage_h
#define cStorage_h 1

//## begin module%4039D91C00DA.includes preserve=yes
//## end module%4039D91C00DA.includes


class __DLL_EXPORT__ cLocalVariable;

//## begin module%4039D91C00DA.additionalDeclarations preserve=yes

#include "System/Database/cVarDef.h"
#include "shacira_version.h"

#define PERSISTENCE_SIGNATURE    0xabcdef

typedef struct data_header {
   ULONG_T signature;
   ULONG_T major;
   ULONG_T minor;
   ULONG_T bug_fix;
   ULONG_T size;
   ULONG_T vars;
   ULONG_T dir_start;
   ULONG_T data_start;
   ULONG_T state_start;
   char filler[0x30];
}  DATA_HEADER_T;

#define MAX_VARNAME_LENGTH 256

typedef struct var_entry {
   CHAR_T var_name[MAX_VARNAME_LENGTH];
   ULONG_T dims;
   ULONG_T dim_size[MAX_DIMENSIONS];
   ULONG_T data_offset;
   ULONG_T data_size;
   ULONG_T state_offset;
   ULONG_T state_size;
   ULONG_T elements;
   ULONG_T element_size;
   ULONG_T data_type;
   char filler[0x10];
}  VAR_ENTRY_T;

typedef std::map<STRING_T,VAR_ENTRY_T*> VAR_ENTRY_MAP_T;

//## end module%4039D91C00DA.additionalDeclarations


//## begin cStorage%4039D91C00DA.preface preserve=yes
//## end cStorage%4039D91C00DA.preface

//## Class: cStorage%4039D91C00DA
//## Category: Control::LocalDatabase%3DFF1FB100C4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class __DLL_EXPORT__ cStorage 
{
  //## begin cStorage%4039D91C00DA.initialDeclarations preserve=yes
public:
  //## end cStorage%4039D91C00DA.initialDeclarations

    //## Constructors (generated)
      cStorage();

      cStorage(const cStorage &right);

    //## Destructor (generated)
      virtual ~cStorage();


    //## Other Operations (specified)
      //## Operation: AddVariable%1191857034
      void AddVariable (cLocalVariable *variable);

      //## Operation: Initialize%1191857035
      void Initialize ();

      //## Operation: SetUp%1191857036
      virtual void SetUp () = 0;

      //## Operation: Load%1191857037
      void Load ();

      //## Operation: Save%1191857038
      void Save ();

      //## Operation: Write%1191857039
      virtual void Write (CONST_STRING_T var_name, ULONG_T pos, CONST_BUF_T buffer, ULONG_T len, UCHAR_T unit_code);

      //## Operation: WriteThrough%1191857040
      virtual void WriteThrough (BUF_T buffer, ULONG_T address, ULONG_T size) = 0;

      //## Operation: FlushOutput%1191857042
      virtual void Flush ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: DataInitialized%470A567F02EF
      BOOL_T get_DataInitialized () const;

  public:
    // Additional Public Declarations
      //## begin cStorage%4039D91C00DA.public preserve=yes
      virtual void Clear();
      void SetBuffered(BOOL_T state);
      //## end cStorage%4039D91C00DA.public

  protected:
    // Data Members for Class Attributes

      //## begin cStorage::DataInitialized%470A567F02EF.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _DataInitialized;
      //## end cStorage::DataInitialized%470A567F02EF.attr

      //## Attribute: DataSize%470A567F02F0
      //## begin cStorage::DataSize%470A567F02F0.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _DataSize;
      //## end cStorage::DataSize%470A567F02F0.attr

      //## Attribute: StateSize%470A567F02FF
      //## begin cStorage::StateSize%470A567F02FF.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _StateSize;
      //## end cStorage::StateSize%470A567F02FF.attr

      //## Attribute: BufSize%470A567F0300
      //## begin cStorage::BufSize%470A567F0300.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _BufSize;
      //## end cStorage::BufSize%470A567F0300.attr

      //## Attribute: Buffer%470A567F030F
      //## begin cStorage::Buffer%470A567F030F.attr preserve=no  protected: BUF_T {U} NULL
      BUF_T _Buffer;
      //## end cStorage::Buffer%470A567F030F.attr

      //## Attribute: CmpBufSize%470A567F031E
      //## begin cStorage::CmpBufSize%470A567F031E.attr preserve=no  protected: ULONG_T {U} 0
      ULONG_T _CmpBufSize;
      //## end cStorage::CmpBufSize%470A567F031E.attr

      //## Attribute: CmpBuffer%470A567F031F
      //## begin cStorage::CmpBuffer%470A567F031F.attr preserve=no  protected: BUF_T {U} NULL
      BUF_T _CmpBuffer;
      //## end cStorage::CmpBuffer%470A567F031F.attr

      //## Attribute: VarEntries%470A567F032E
      //## begin cStorage::VarEntries%470A567F032E.attr preserve=no  protected: VAR_ENTRY_MAP_T {U} 
      VAR_ENTRY_MAP_T _VarEntries;
      //## end cStorage::VarEntries%470A567F032E.attr

      //## Attribute: ShadowDataset%470A567F033E
      //## begin cStorage::ShadowDataset%470A567F033E.attr preserve=no  protected: BOOL_T {U} false
      BOOL_T _ShadowDataset;
      //## end cStorage::ShadowDataset%470A567F033E.attr

    // Data Members for Associations

      //## Association: Control::LocalDatabase::<unnamed>%403B2A3D03A9
      //## Role: cStorage::Variables%403B2A3E02EE
      //## Qualifier: name%403B2A5E0000; STRING_T
      //## begin cStorage::Variables%403B2A3E02EE.role preserve=no  public: cLocalVariable { -> 0..nRFHN}
      std::map<STRING_T, cLocalVariable*> _Variables;
      //## end cStorage::Variables%403B2A3E02EE.role

    // Additional Protected Declarations
      //## begin cStorage%4039D91C00DA.protected preserve=yes
      BOOL_T _Buffered;
      //## end cStorage%4039D91C00DA.protected

  private:
    // Additional Private Declarations
      //## begin cStorage%4039D91C00DA.private preserve=yes
      //## end cStorage%4039D91C00DA.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: GetAddress%1191857043
      ULONG_T GetAddress (CONST_STRING_T var_name, ULONG_T pos);

      //## Operation: GetElementSize%1191857044
      ULONG_T GetElementSize (CONST_STRING_T var_name);

      //## Operation: DirEntry%1191857045
   protected:
      VAR_ENTRY_T * DirEntry (CONST_STRING_T var_name);
   private:

      //## Operation: BufAddress%1191857046
      BUF_T BufAddress (ULONG_T address);

      //## Operation: DataAddress%1191857047
      ULONG_T DataAddress (ULONG_T address);

      //## Operation: Variable%1191857048
      cLocalVariable * Variable (CONST_STRING_T var_name);

      //## Operation: LoadShadowDataset%1191857049
      void LoadShadowDataset ();

      //## Operation: SaveShadowDataset%1191857050
      void SaveShadowDataset ();

    // Additional Implementation Declarations
      //## begin cStorage%4039D91C00DA.implementation preserve=yes
      //## end cStorage%4039D91C00DA.implementation

};

//## begin cStorage%4039D91C00DA.postscript preserve=yes
//## end cStorage%4039D91C00DA.postscript

// Class cStorage 

//## begin module%4039D91C00DA.epilog preserve=yes
//## end module%4039D91C00DA.epilog


#endif
