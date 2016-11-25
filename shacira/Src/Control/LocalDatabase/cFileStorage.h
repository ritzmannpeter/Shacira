//## begin module%403A0EB402BF.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%403A0EB402BF.cm

//## begin module%403A0EB402BF.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%403A0EB402BF.cp

//## Module: cFileStorage%403A0EB402BF; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\Control\LocalDatabase\cFileStorage.h

#ifndef cFileStorage_h
#define cFileStorage_h 1

//## begin module%403A0EB402BF.includes preserve=yes
//## end module%403A0EB402BF.includes

// cLocalVariable
#include "Control/LocalDatabase/cLocalVariable.h"
// cStorage
#include "Control/LocalDatabase/cStorage.h"

class __DLL_EXPORT__ cContext;
class __DLL_EXPORT__ cSHFile;
class __DLL_EXPORT__ cFileSystemUtils;
class __DLL_EXPORT__ cPersistentVariable;

//## begin module%403A0EB402BF.additionalDeclarations preserve=yes
//## end module%403A0EB402BF.additionalDeclarations


//## begin cFileStorage%403A0EB402BF.preface preserve=yes
//## end cFileStorage%403A0EB402BF.preface

//## Class: cFileStorage%403A0EB402BF
//## Category: Control::LocalDatabase%3DFF1FB100C4
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%403A2F520271;cFileSystemUtils { -> F}
//## Uses: <unnamed>%444726B203AB;cContext { -> F}
//## Uses: <unnamed>%44472823034F;cPersistentVariable { -> F}
//## Uses: <unnamed>%470A54C30188;cLocalVariable { -> }

class __DLL_EXPORT__ cFileStorage : public cStorage  //## Inherits: <unnamed>%403B223400BB
{
  //## begin cFileStorage%403A0EB402BF.initialDeclarations preserve=yes
public:
  //## end cFileStorage%403A0EB402BF.initialDeclarations

    //## Constructors (generated)
      cFileStorage();

      cFileStorage(const cFileStorage &right);

    //## Constructors (specified)
      //## Operation: cFileStorage%1122619256
      cFileStorage (CONST_STRING_T name, BOOL_T persistence_file = false, ULONG_T dataset = FOREGROUND_DATASET);

    //## Destructor (generated)
      virtual ~cFileStorage();


    //## Other Operations (specified)
      //## Operation: SetUp%1077542666
      virtual void SetUp ();

      //## Operation: WriteThrough%1077548346
      virtual void WriteThrough (BUF_T buffer, ULONG_T address, ULONG_T size);

      //## Operation: Parse%1145513554
      virtual cContext * Parse ();

      //## Operation: DataFile%1191857030
      static STRING_T DataFile (CONST_STRING_T name = "CCSDATA", ULONG_T dataset = FOREGROUND_DATASET);

      //## Operation: BackupFile%1191857031
      static STRING_T BackupFile (CONST_STRING_T name = "CCSDATA", ULONG_T dataset = FOREGROUND_DATASET);
      static STRING_T TempFile (CONST_STRING_T name = "CCSTEMP", ULONG_T dataset = FOREGROUND_DATASET);

      //## Operation: FlushOutput%1191857033
      virtual void Flush ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Name%42E9CF1C01A5
      STRING_T get_Name () const;

  public:
    // Additional Public Declarations
      //## begin cFileStorage%403A0EB402BF.public preserve=yes
      //## end cFileStorage%403A0EB402BF.public
      void Clear();

  protected:
    // Data Members for Class Attributes

      //## begin cFileStorage::Name%42E9CF1C01A5.attr preserve=no  public: STRING_T {U} 
      STRING_T _Name;
      //## end cFileStorage::Name%42E9CF1C01A5.attr

    // Data Members for Associations

      //## Association: Control::LocalDatabase::<unnamed>%403A281000AB
      //## Role: cFileStorage::File%403A2811006D
      //## begin cFileStorage::File%403A2811006D.role preserve=no  public: cSHFile { -> 1RFHN}
      cMutexSem _FileMutex;
      cSHFile *_File;
      //## end cFileStorage::File%403A2811006D.role

    // Additional Protected Declarations
      //## begin cFileStorage%403A0EB402BF.protected preserve=yes
      //## end cFileStorage%403A0EB402BF.protected

  private:
    // Additional Private Declarations
      //## begin cFileStorage%403A0EB402BF.private preserve=yes
      //## end cFileStorage%403A0EB402BF.private

  private: //## implementation
    // Data Members for Class Attributes

      //## Attribute: DataFileName%403A2EB200DA
      //## begin cFileStorage::DataFileName%403A2EB200DA.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _DataFileName;
      //## end cFileStorage::DataFileName%403A2EB200DA.attr

      //## Attribute: BackupFile%45BF85E9006D
      //## begin cFileStorage::BackupFile%45BF85E9006D.attr preserve=no  implementation: STRING_T {U} 
      STRING_T _BackupFile;
      STRING_T _TempFile;
      //## end cFileStorage::BackupFile%45BF85E9006D.attr

    // Additional Implementation Declarations
      //## begin cFileStorage%403A0EB402BF.implementation preserve=yes
      //## end cFileStorage%403A0EB402BF.implementation

};

//## begin cFileStorage%403A0EB402BF.postscript preserve=yes
//## end cFileStorage%403A0EB402BF.postscript

// Class cFileStorage 

//## begin module%403A0EB402BF.epilog preserve=yes
//## end module%403A0EB402BF.epilog


#endif
