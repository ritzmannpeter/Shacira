//## begin module%3B9CF6E3010D.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B9CF6E3010D.cm

//## begin module%3B9CF6E3010D.cp preserve=no
//	Copyright © 2002 by
//	2i Industrial Informatics GmbH
//## end module%3B9CF6E3010D.cp

//## Module: cSimpleFileSystem%3B9CF6E3010D; Pseudo Package specification
//## Source file: e:\usr\prj\Shacira\Src\Dnc\FileSystem\cSimpleFileSystem.h

#ifndef cSimpleFileSystem_h
#define cSimpleFileSystem_h 1

//## begin module%3B9CF6E3010D.includes preserve=yes
//## end module%3B9CF6E3010D.includes

// cToolFileSystem
#include "Dnc/FileSystem/cToolFileSystem.h"

class __DLL_EXPORT__ cCarrierBase;
class __DLL_EXPORT__ cCarrierSource;

//## begin module%3B9CF6E3010D.additionalDeclarations preserve=yes
//## end module%3B9CF6E3010D.additionalDeclarations


//## begin cSimpleFileSystem%3B9CF6E3010D.preface preserve=yes
//## end cSimpleFileSystem%3B9CF6E3010D.preface

//## Class: cSimpleFileSystem%3B9CF6E3010D
//## Category: Dnc::FileSystem%3B97BB4E0106
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3BAB6E1200F1;cCarrierSource { -> F}

class __DLL_EXPORT__ cSimpleFileSystem : public cToolFileSystem  //## Inherits: <unnamed>%3B9CF6F8021B
{
  //## begin cSimpleFileSystem%3B9CF6E3010D.initialDeclarations preserve=yes
  //## end cSimpleFileSystem%3B9CF6E3010D.initialDeclarations

    //## Constructors (generated)
      cSimpleFileSystem();

      cSimpleFileSystem(const cSimpleFileSystem &right);

    //## Constructors (specified)
      //## Operation: cSimpleFileSystem%1000119103
      cSimpleFileSystem (cCarrierSource *file_source, CONST_STRING_T path);

    //## Destructor (generated)
      virtual ~cSimpleFileSystem();


    //## Other Operations (specified)
      //## Operation: Format%1000119104
      INT_T Format (INT_T format);

      //## Operation: Directory%1000119105
      INT_T Directory (STRING_LIST_T &file_names);

      //## Operation: Load%1000119106
      LONG_T Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: Save%1000119107
      LONG_T Save (CONST_STRING_T file_name, void *buf, ULONG_T size);

      //## Operation: Delete%1000119108
      INT_T Delete (CONST_STRING_T file_name);

      //## Operation: FileSize%1000386734
      LONG_T FileSize (CONST_STRING_T file_name);

      //## Operation: File%1000386735
      cFile * File (CONST_STRING_T file_name);

      //## Operation: GetTime%1000456415
      cTimeObject GetTime (CONST_STRING_T file_name);

  public:
    // Additional Public Declarations
      //## begin cSimpleFileSystem%3B9CF6E3010D.public preserve=yes
      //## end cSimpleFileSystem%3B9CF6E3010D.public

  protected:
    // Data Members for Associations

      //## Association: Dnc::FileSystem::<unnamed>%3BA5BAEE01B8
      //## Role: cSimpleFileSystem::Carrier%3BA5BAEF0264
      //## begin cSimpleFileSystem::Carrier%3BA5BAEF0264.role preserve=no  public: cCarrierBase { -> 1RFHN}
      cCarrierBase *_Carrier;
      //## end cSimpleFileSystem::Carrier%3BA5BAEF0264.role

    // Additional Protected Declarations
      //## begin cSimpleFileSystem%3B9CF6E3010D.protected preserve=yes
      //## end cSimpleFileSystem%3B9CF6E3010D.protected

  private:
    // Additional Private Declarations
      //## begin cSimpleFileSystem%3B9CF6E3010D.private preserve=yes
      //## end cSimpleFileSystem%3B9CF6E3010D.private

  private: //## implementation

    //## Other Operations (specified)
      //## Operation: Read%1000195348
      INT_T Read (ULONG_T address, ULONG_T bytes, void *buffer);

      //## Operation: Write%1000195349
      INT_T Write (ULONG_T address, ULONG_T bytes, void *buffer);

      //## Operation: Checksum%1000195350
      UCHAR_T Checksum (const UCHAR_T *buffer, ULONG_T address, ULONG_T offset);

      //## Operation: FMT2_TestChecksum%1000195345
      BOOL_T FMT2_TestChecksum ();

      //## Operation: FMT2_2F_TestChecksum%1000195346
      BOOL_T FMT2_2F_TestChecksum ();

      //## Operation: FMT2_3F_TestChecksum%1000195347
      BOOL_T FMT2_3F_TestChecksum ();

      //## Operation: FMT1_TestChecksum%1000195351
      BOOL_T FMT1_TestChecksum ();

      //## Operation: FX25_TestChecksum%1000195352
      BOOL_T FX25_TestChecksum ();

      //## Operation: FMT2_Directory%1000195353
      INT_T FMT2_Directory (STRING_LIST_T &file_names);

      //## Operation: FMT2_2F_Directory%1000195354
      INT_T FMT2_2F_Directory (STRING_LIST_T &file_names);

      //## Operation: FMT2_3F_Directory%1000195355
      INT_T FMT2_3F_Directory (STRING_LIST_T &file_names);

      //## Operation: FMT1_Directory%1000195356
      INT_T FMT1_Directory (STRING_LIST_T &file_names);

      //## Operation: FX25_Directory%1000195357
      INT_T FX25_Directory (STRING_LIST_T &file_names);

      //## Operation: FMT2_Load%1000195359
      LONG_T FMT2_Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: FMT2_2F_Load%1000195360
      LONG_T FMT2_2F_Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: FMT2_3F_Load%1000195361
      LONG_T FMT2_3F_Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: FMT1_Load%1000195362
      LONG_T FMT1_Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: FX25_Load%1000195363
      LONG_T FX25_Load (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: FMT2_Save%1000195364
      LONG_T FMT2_Save (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: FMT2_2F_Save%1000195365
      LONG_T FMT2_2F_Save (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: FMT2_3F_Save%1000195366
      LONG_T FMT2_3F_Save (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: FMT1_Save%1000195367
      LONG_T FMT1_Save (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: FX25_Save%1000195368
      LONG_T FX25_Save (CONST_STRING_T file_name, void *buf, ULONG_T buf_size);

      //## Operation: FMT2_Delete%1000195369
      INT_T FMT2_Delete (CONST_STRING_T file_name);

      //## Operation: FMT2_2F_Delete%1000195370
      INT_T FMT2_2F_Delete (CONST_STRING_T file_name);

      //## Operation: FMT2_3F_Delete%1000195371
      INT_T FMT2_3F_Delete (CONST_STRING_T file_name);

      //## Operation: FMT1_Delete%1000195372
      INT_T FMT1_Delete (CONST_STRING_T file_name);

      //## Operation: FX25_Delete%1000195373
      INT_T FX25_Delete (CONST_STRING_T file_name);

      //## Operation: DINT2Long%1000195374
      LONG_T DINT2Long (LONG_T value);

      //## Operation: FileNo%1000195375
      INT_T FileNo (CONST_STRING_T file_name);

      //## Operation: MakeFileName%1000195378
      CONST_STRING_T MakeFileName (CHAR_T *buffer, INT_T file_no);

      //## Operation: FMT2_MakeChecksum%1000724910
      INT_T FMT2_MakeChecksum (INT_T file_no);

      //## Operation: FMT2_2F_MakeChecksum%1000724911
      INT_T FMT2_2F_MakeChecksum (INT_T file_no);

      //## Operation: FMT2_3F_MakeChecksum%1000724912
      INT_T FMT2_3F_MakeChecksum (INT_T file_no);

      //## Operation: FMT1_MakeChecksum%1000724913
      INT_T FMT1_MakeChecksum (INT_T file_no);

      //## Operation: FX25_MakeChecksum%1000724914
      INT_T FX25_MakeChecksum (INT_T file_no);

      //## Operation: FMT2_Format%1000724915
      INT_T FMT2_Format ();

      //## Operation: FMT2_2F_Format%1000724916
      INT_T FMT2_2F_Format ();

      //## Operation: FMT2_3F_Format%1000724917
      INT_T FMT2_3F_Format ();

      //## Operation: FMT1_Format%1000724918
      INT_T FMT1_Format ();

      //## Operation: FX25_Format%1000724919
      INT_T FX25_Format ();

      //## Operation: FMT2_FileSize%1000724920
      LONG_T FMT2_FileSize (CONST_STRING_T file_name);

      //## Operation: FMT2_2F_FileSize%1000724921
      LONG_T FMT2_2F_FileSize (CONST_STRING_T file_name);

      //## Operation: FMT2_3F_FileSize%1000724922
      LONG_T FMT2_3F_FileSize (CONST_STRING_T file_name);

      //## Operation: FMT1_FileSize%1000724923
      LONG_T FMT1_FileSize (CONST_STRING_T file_name);

      //## Operation: FX25_FileSize%1000724924
      LONG_T FX25_FileSize (CONST_STRING_T file_name);

      //## Operation: FMT2_GetTime%1000724925
      cTimeObject FMT2_GetTime (CONST_STRING_T file_name);

      //## Operation: FMT2_2F_GetTime%1000724926
      cTimeObject FMT2_2F_GetTime (CONST_STRING_T file_name);

      //## Operation: FMT2_3F_GetTime%1000724927
      cTimeObject FMT2_3F_GetTime (CONST_STRING_T file_name);

      //## Operation: FMT1_GetTime%1000724928
      cTimeObject FMT1_GetTime (CONST_STRING_T file_name);

      //## Operation: FX25_GetTime%1000724929
      cTimeObject FX25_GetTime (CONST_STRING_T file_name);

      //## Operation: FMT2_CarrierPos%1000195358
      LONG_T FMT2_CarrierPos (INT_T file_no, INT_T area);

      //## Operation: FMT2_2F_CarrierPos%1000724930
      LONG_T FMT2_2F_CarrierPos (INT_T file_no, INT_T area);

      //## Operation: FMT2_3F_CarrierPos%1000724931
      LONG_T FMT2_3F_CarrierPos (INT_T file_no, INT_T area);

      //## Operation: FMT1_CarrierPos%1000724932
      LONG_T FMT1_CarrierPos (INT_T file_no, INT_T area);

      //## Operation: FX25_CarrierPos%1000724933
      LONG_T FX25_CarrierPos (INT_T file_no, INT_T area);

    // Additional Implementation Declarations
      //## begin cSimpleFileSystem%3B9CF6E3010D.implementation preserve=yes
      //## end cSimpleFileSystem%3B9CF6E3010D.implementation

};

//## begin cSimpleFileSystem%3B9CF6E3010D.postscript preserve=yes
//## end cSimpleFileSystem%3B9CF6E3010D.postscript

// Class cSimpleFileSystem 

//## begin module%3B9CF6E3010D.epilog preserve=yes
//## end module%3B9CF6E3010D.epilog


#endif
