//## begin module%37B1C8E300E0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%37B1C8E300E0.cm

//## begin module%37B1C8E300E0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%37B1C8E300E0.cp

//## Module: cState%37B1C8E300E0; Pseudo Package specification
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cState.h

#ifndef cState_h
#define cState_h 1

//## begin module%37B1C8E300E0.includes preserve=yes
//## end module%37B1C8E300E0.includes

// cTransientObject
#include "System/Objects/cTransientObject.h"

class __DLL_EXPORT__ cTransferObject;

//## begin module%37B1C8E300E0.additionalDeclarations preserve=yes
//## end module%37B1C8E300E0.additionalDeclarations


//## begin cState%37B1C8E300E0.preface preserve=yes
//## end cState%37B1C8E300E0.preface

//## Class: cState%37B1C8E300E0
//## Category: System::Objects%3DC816ED01FF
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3E5A57CA01FE;cTransferObject { -> F}

class __DLL_EXPORT__ cState : public cTransientObject  //## Inherits: <unnamed>%3E5A4FEA00F1
{
  //## begin cState%37B1C8E300E0.initialDeclarations preserve=yes
public:
  //## end cState%37B1C8E300E0.initialDeclarations

    //## Constructors (generated)
      cState();

      cState(const cState &right);

    //## Constructors (specified)
      //## Operation: cState%1047639316
      cState (cStaticObject *source);

    //## Destructor (generated)
      virtual ~cState();


    //## Other Operations (specified)
      //## Operation: Serialize%1023780975
      virtual STRING_T Serialize ();

      //## Operation: Construct%1023780976
      virtual BOOL_T Construct (CONST_STRING_T serialized_obj);

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: Connected%3A4B55780130
      BOOL_T get_Connected () const;
      void set_Connected (BOOL_T value);

      //## Attribute: Duration%3E5B7785028E
      ULONG_T get_Duration () const;
      void set_Duration (ULONG_T value);

      //## Attribute: ProductionState%3A4B55D302CC
      INT_T get_ProductionState () const;
      void set_ProductionState (INT_T value);

      //## Attribute: MachineState%3A6ECE130018
      INT_T get_MachineState () const;
      void set_MachineState (INT_T value);

      //## Attribute: UploadRequest%3C9C9A1E0371
      BOOL_T get_UploadRequest () const;
      void set_UploadRequest (BOOL_T value);

      //## Attribute: StartRequest%3A4B67470096
      BOOL_T get_StartRequest () const;
      void set_StartRequest (BOOL_T value);

      //## Attribute: DownloadRequest%3A4B561A033C
      BOOL_T get_DownloadRequest () const;
      void set_DownloadRequest (BOOL_T value);

      //## Attribute: StopRequest%3A4B675800CC
      BOOL_T get_StopRequest () const;
      void set_StopRequest (BOOL_T value);

      //## Attribute: AbortRequest%3A6EC8B3016D
      BOOL_T get_AbortRequest () const;
      void set_AbortRequest (BOOL_T value);

      //## Attribute: UploadEnabled%3A6EC9D201DE
      BOOL_T get_UploadEnabled () const;
      void set_UploadEnabled (BOOL_T value);

      //## Attribute: DownloadEnabled%3A6EC9E5020E
      BOOL_T get_DownloadEnabled () const;
      void set_DownloadEnabled (BOOL_T value);

      //## Attribute: ProductionTerminated%3A6ECA0C0250
      BOOL_T get_ProductionTerminated () const;
      void set_ProductionTerminated (BOOL_T value);

      //## Attribute: ProductionSet%3E5B78DD0347
      ULONG_T get_ProductionSet () const;
      void set_ProductionSet (ULONG_T value);

      //## Attribute: Cavities%3E5B78DD0348
      ULONG_T get_Cavities () const;
      void set_Cavities (ULONG_T value);

      //## Attribute: GoodCycles%3E5B78DD0351
      ULONG_T get_GoodCycles () const;
      void set_GoodCycles (ULONG_T value);

      //## Attribute: PoorCycles%3E5B78DD0352
      ULONG_T get_PoorCycles () const;
      void set_PoorCycles (ULONG_T value);

      //## Attribute: GoodParts%3E5B78DD0353
      ULONG_T get_GoodParts () const;
      void set_GoodParts (ULONG_T value);

      //## Attribute: PoorParts%3E5B78DD035B
      ULONG_T get_PoorParts () const;
      void set_PoorParts (ULONG_T value);

      //## Attribute: ShotCount%3E5B78DD035C
      ULONG_T get_ShotCount () const;
      void set_ShotCount (ULONG_T value);

      //## Attribute: AddingShotCount%3E5B78DD0365
      ULONG_T get_AddingShotCount () const;
      void set_AddingShotCount (ULONG_T value);

      //## Attribute: SubtractingShotCount%3E5B78DD0366
      ULONG_T get_SubtractingShotCount () const;
      void set_SubtractingShotCount (ULONG_T value);

      //## Attribute: CycleTime%3E5B78DD0367
      DOUBLE_T get_CycleTime () const;
      void set_CycleTime (DOUBLE_T value);

      //## Attribute: OrderNo%3ECB6055038A
      STRING_T get_OrderNo () const;
      void set_OrderNo (STRING_T value);

      //## Attribute: ArticleNo%3ECB606E01D4
      STRING_T get_ArticleNo () const;
      void set_ArticleNo (STRING_T value);

  public:
    // Additional Public Declarations
      //## begin cState%37B1C8E300E0.public preserve=yes
      //## end cState%37B1C8E300E0.public

  protected:
    // Data Members for Class Attributes

      //## begin cState::Connected%3A4B55780130.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _Connected;
      //## end cState::Connected%3A4B55780130.attr

      //## begin cState::Duration%3E5B7785028E.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Duration;
      //## end cState::Duration%3E5B7785028E.attr

      //## begin cState::ProductionState%3A4B55D302CC.attr preserve=no  public: INT_T {U} UNDEFINED
      INT_T _ProductionState;
      //## end cState::ProductionState%3A4B55D302CC.attr

      //## begin cState::MachineState%3A6ECE130018.attr preserve=no  public: INT_T {U} UNDEFINED
      INT_T _MachineState;
      //## end cState::MachineState%3A6ECE130018.attr

      //## begin cState::UploadRequest%3C9C9A1E0371.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _UploadRequest;
      //## end cState::UploadRequest%3C9C9A1E0371.attr

      //## begin cState::StartRequest%3A4B67470096.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _StartRequest;
      //## end cState::StartRequest%3A4B67470096.attr

      //## begin cState::DownloadRequest%3A4B561A033C.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _DownloadRequest;
      //## end cState::DownloadRequest%3A4B561A033C.attr

      //## begin cState::StopRequest%3A4B675800CC.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _StopRequest;
      //## end cState::StopRequest%3A4B675800CC.attr

      //## begin cState::AbortRequest%3A6EC8B3016D.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _AbortRequest;
      //## end cState::AbortRequest%3A6EC8B3016D.attr

      //## begin cState::UploadEnabled%3A6EC9D201DE.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _UploadEnabled;
      //## end cState::UploadEnabled%3A6EC9D201DE.attr

      //## begin cState::DownloadEnabled%3A6EC9E5020E.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _DownloadEnabled;
      //## end cState::DownloadEnabled%3A6EC9E5020E.attr

      //## begin cState::ProductionTerminated%3A6ECA0C0250.attr preserve=no  public: BOOL_T {U} false
      BOOL_T _ProductionTerminated;
      //## end cState::ProductionTerminated%3A6ECA0C0250.attr

      //## begin cState::ProductionSet%3E5B78DD0347.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _ProductionSet;
      //## end cState::ProductionSet%3E5B78DD0347.attr

      //## begin cState::Cavities%3E5B78DD0348.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _Cavities;
      //## end cState::Cavities%3E5B78DD0348.attr

      //## begin cState::GoodCycles%3E5B78DD0351.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _GoodCycles;
      //## end cState::GoodCycles%3E5B78DD0351.attr

      //## begin cState::PoorCycles%3E5B78DD0352.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _PoorCycles;
      //## end cState::PoorCycles%3E5B78DD0352.attr

      //## begin cState::GoodParts%3E5B78DD0353.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _GoodParts;
      //## end cState::GoodParts%3E5B78DD0353.attr

      //## begin cState::PoorParts%3E5B78DD035B.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _PoorParts;
      //## end cState::PoorParts%3E5B78DD035B.attr

      //## begin cState::ShotCount%3E5B78DD035C.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _ShotCount;
      //## end cState::ShotCount%3E5B78DD035C.attr

      //## begin cState::AddingShotCount%3E5B78DD0365.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _AddingShotCount;
      //## end cState::AddingShotCount%3E5B78DD0365.attr

      //## begin cState::SubtractingShotCount%3E5B78DD0366.attr preserve=no  public: ULONG_T {U} 0
      ULONG_T _SubtractingShotCount;
      //## end cState::SubtractingShotCount%3E5B78DD0366.attr

      //## begin cState::CycleTime%3E5B78DD0367.attr preserve=no  public: DOUBLE_T {U} 0
      DOUBLE_T _CycleTime;
      //## end cState::CycleTime%3E5B78DD0367.attr

      //## begin cState::OrderNo%3ECB6055038A.attr preserve=no  public: STRING_T {U} 
      STRING_T _OrderNo;
      //## end cState::OrderNo%3ECB6055038A.attr

      //## begin cState::ArticleNo%3ECB606E01D4.attr preserve=no  public: STRING_T {U} 
      STRING_T _ArticleNo;
      //## end cState::ArticleNo%3ECB606E01D4.attr

    // Additional Protected Declarations
      //## begin cState%37B1C8E300E0.protected preserve=yes
      //## end cState%37B1C8E300E0.protected

  private:
    // Additional Private Declarations
      //## begin cState%37B1C8E300E0.private preserve=yes
      //## end cState%37B1C8E300E0.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin cState%37B1C8E300E0.implementation preserve=yes
      //## end cState%37B1C8E300E0.implementation

};

//## begin cState%37B1C8E300E0.postscript preserve=yes
//## end cState%37B1C8E300E0.postscript

// Class cState 

//## begin module%37B1C8E300E0.epilog preserve=yes
//## end module%37B1C8E300E0.epilog


#endif
