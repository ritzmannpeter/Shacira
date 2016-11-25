//## begin module%37B1C8E300E0.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%37B1C8E300E0.cm

//## begin module%37B1C8E300E0.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%37B1C8E300E0.cp

//## Module: cState%37B1C8E300E0; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\Objects\cState.cpp

//## begin module%37B1C8E300E0.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%37B1C8E300E0.additionalIncludes

//## begin module%37B1C8E300E0.includes preserve=yes
//## end module%37B1C8E300E0.includes

// cTransferObject
#include "System/Objects/cTransferObject.h"
// cState
#include "System/Objects/cState.h"
//## begin module%37B1C8E300E0.additionalDeclarations preserve=yes
//## end module%37B1C8E300E0.additionalDeclarations


// Class cState 


























cState::cState()
  //## begin cState::cState%.hasinit preserve=no
      : _Connected(false), _Duration(0), _ProductionState(UNDEFINED), _MachineState(UNDEFINED), _UploadRequest(false), _StartRequest(false), _DownloadRequest(false), _StopRequest(false), _AbortRequest(false), _UploadEnabled(false), _DownloadEnabled(false), _ProductionTerminated(false), _ProductionSet(0), _Cavities(0), _GoodCycles(0), _PoorCycles(0), _GoodParts(0), _PoorParts(0), _ShotCount(0), _AddingShotCount(0), _SubtractingShotCount(0), _CycleTime(0)
  //## end cState::cState%.hasinit
  //## begin cState::cState%.initialization preserve=yes
  //## end cState::cState%.initialization
{
  //## begin cState::cState%.body preserve=yes
   _Type = OT_STATE;
  //## end cState::cState%.body
}

cState::cState(const cState &right)
  //## begin cState::cState%copy.hasinit preserve=no
      : _Connected(false), _Duration(0), _ProductionState(UNDEFINED), _MachineState(UNDEFINED), _UploadRequest(false), _StartRequest(false), _DownloadRequest(false), _StopRequest(false), _AbortRequest(false), _UploadEnabled(false), _DownloadEnabled(false), _ProductionTerminated(false), _ProductionSet(0), _Cavities(0), _GoodCycles(0), _PoorCycles(0), _GoodParts(0), _PoorParts(0), _ShotCount(0), _AddingShotCount(0), _SubtractingShotCount(0), _CycleTime(0)
  //## end cState::cState%copy.hasinit
  //## begin cState::cState%copy.initialization preserve=yes
  //## end cState::cState%copy.initialization
{
  //## begin cState::cState%copy.body preserve=yes
_ASSERT_UNCOND;
  //## end cState::cState%copy.body
}

cState::cState (cStaticObject *source)
  //## begin cState::cState%1047639316.hasinit preserve=no
      : _Connected(false), _Duration(0), _ProductionState(UNDEFINED), _MachineState(UNDEFINED), _UploadRequest(false), _StartRequest(false), _DownloadRequest(false), _StopRequest(false), _AbortRequest(false), _UploadEnabled(false), _DownloadEnabled(false), _ProductionTerminated(false), _ProductionSet(0), _Cavities(0), _GoodCycles(0), _PoorCycles(0), _GoodParts(0), _PoorParts(0), _ShotCount(0), _AddingShotCount(0), _SubtractingShotCount(0), _CycleTime(0)
  //## end cState::cState%1047639316.hasinit
  //## begin cState::cState%1047639316.initialization preserve=yes
  , cTransientObject(source)
  //## end cState::cState%1047639316.initialization
{
  //## begin cState::cState%1047639316.body preserve=yes
   _Type = OT_STATE;
  //## end cState::cState%1047639316.body
}


cState::~cState()
{
  //## begin cState::~cState%.body preserve=yes
  //## end cState::~cState%.body
}



//## Other Operations (implementation)
STRING_T cState::Serialize ()
{
  //## begin cState::Serialize%1023780975.body preserve=yes
   cTransferObject obj;
   SerializeBase(obj);
   obj.AddAttribute(0, _Connected, ObjectBody);
   obj.AddAttribute(1, _Duration, ObjectBody);
   obj.AddAttribute(2, _ProductionState, ObjectBody);
   obj.AddAttribute(3, _MachineState, ObjectBody);
   obj.AddAttribute(4, _UploadRequest, ObjectBody);
   obj.AddAttribute(5, _DownloadRequest, ObjectBody);
   obj.AddAttribute(6, _StartRequest, ObjectBody);
   obj.AddAttribute(7, _StopRequest, ObjectBody);
   obj.AddAttribute(8, _AbortRequest, ObjectBody);
   obj.AddAttribute(9, _UploadEnabled, ObjectBody);
   obj.AddAttribute(10, _DownloadEnabled, ObjectBody);
   obj.AddAttribute(11, _ProductionTerminated, ObjectBody);
   obj.AddAttribute(12, _ProductionSet, ObjectBody);
   obj.AddAttribute(13, _Cavities, ObjectBody);
   obj.AddAttribute(14, _GoodCycles, ObjectBody);
   obj.AddAttribute(15, _PoorCycles, ObjectBody);
   obj.AddAttribute(16, _GoodParts, ObjectBody);
   obj.AddAttribute(17, _PoorParts, ObjectBody);
   obj.AddAttribute(18, _ShotCount, ObjectBody);
   obj.AddAttribute(19, _AddingShotCount, ObjectBody);
   obj.AddAttribute(20, _SubtractingShotCount, ObjectBody);
   obj.AddAttribute(21, _CycleTime, ObjectBody);
   obj.AddAttribute(22, _OrderNo.c_str(), ObjectBody);
   obj.AddAttribute(23, _ArticleNo.c_str(), ObjectBody);
   return obj.Serialize().c_str();
  //## end cState::Serialize%1023780975.body
}

BOOL_T cState::Construct (CONST_STRING_T serialized_obj)
{
  //## begin cState::Construct%1023780976.body preserve=yes
   cTransferObject obj(serialized_obj);
   if (!ConstructBase(obj)) return false;
   obj.GetAttribute(0, _Connected, ObjectBody);
   obj.GetAttribute(1, _Duration, ObjectBody);
   obj.GetAttribute(2, _ProductionState, ObjectBody);
   obj.GetAttribute(3, _MachineState, ObjectBody);
   obj.GetAttribute(4, _UploadRequest, ObjectBody);
   obj.GetAttribute(5, _DownloadRequest, ObjectBody);
   obj.GetAttribute(6, _StartRequest, ObjectBody);
   obj.GetAttribute(7, _StopRequest, ObjectBody);
   obj.GetAttribute(8, _AbortRequest, ObjectBody);
   obj.GetAttribute(9, _UploadEnabled, ObjectBody);
   obj.GetAttribute(10, _DownloadEnabled, ObjectBody);
   obj.GetAttribute(11, _ProductionTerminated, ObjectBody);
   obj.GetAttribute(12, _ProductionSet, ObjectBody);
   obj.GetAttribute(13, _Cavities, ObjectBody);
   obj.GetAttribute(14, _GoodCycles, ObjectBody);
   obj.GetAttribute(15, _PoorCycles, ObjectBody);
   obj.GetAttribute(16, _GoodParts, ObjectBody);
   obj.GetAttribute(17, _PoorParts, ObjectBody);
   obj.GetAttribute(18, _ShotCount, ObjectBody);
   obj.GetAttribute(19, _AddingShotCount, ObjectBody);
   obj.GetAttribute(20, _SubtractingShotCount, ObjectBody);
   obj.GetAttribute(21, _CycleTime, ObjectBody);
   obj.GetAttribute(22, _OrderNo, ObjectBody);
   obj.GetAttribute(23, _ArticleNo, ObjectBody);
   return true;
  //## end cState::Construct%1023780976.body
}

//## Get and Set Operations for Class Attributes (implementation)

BOOL_T cState::get_Connected () const
{
  //## begin cState::get_Connected%3A4B55780130.get preserve=no
  return _Connected;
  //## end cState::get_Connected%3A4B55780130.get
}

void cState::set_Connected (BOOL_T value)
{
  //## begin cState::set_Connected%3A4B55780130.set preserve=no
  _Connected = value;
  //## end cState::set_Connected%3A4B55780130.set
}

ULONG_T cState::get_Duration () const
{
  //## begin cState::get_Duration%3E5B7785028E.get preserve=no
  return _Duration;
  //## end cState::get_Duration%3E5B7785028E.get
}

void cState::set_Duration (ULONG_T value)
{
  //## begin cState::set_Duration%3E5B7785028E.set preserve=no
  _Duration = value;
  //## end cState::set_Duration%3E5B7785028E.set
}

INT_T cState::get_ProductionState () const
{
  //## begin cState::get_ProductionState%3A4B55D302CC.get preserve=no
  return _ProductionState;
  //## end cState::get_ProductionState%3A4B55D302CC.get
}

void cState::set_ProductionState (INT_T value)
{
  //## begin cState::set_ProductionState%3A4B55D302CC.set preserve=no
  _ProductionState = value;
  //## end cState::set_ProductionState%3A4B55D302CC.set
}

INT_T cState::get_MachineState () const
{
  //## begin cState::get_MachineState%3A6ECE130018.get preserve=no
  return _MachineState;
  //## end cState::get_MachineState%3A6ECE130018.get
}

void cState::set_MachineState (INT_T value)
{
  //## begin cState::set_MachineState%3A6ECE130018.set preserve=no
  _MachineState = value;
  //## end cState::set_MachineState%3A6ECE130018.set
}

BOOL_T cState::get_UploadRequest () const
{
  //## begin cState::get_UploadRequest%3C9C9A1E0371.get preserve=no
  return _UploadRequest;
  //## end cState::get_UploadRequest%3C9C9A1E0371.get
}

void cState::set_UploadRequest (BOOL_T value)
{
  //## begin cState::set_UploadRequest%3C9C9A1E0371.set preserve=no
  _UploadRequest = value;
  //## end cState::set_UploadRequest%3C9C9A1E0371.set
}

BOOL_T cState::get_StartRequest () const
{
  //## begin cState::get_StartRequest%3A4B67470096.get preserve=no
  return _StartRequest;
  //## end cState::get_StartRequest%3A4B67470096.get
}

void cState::set_StartRequest (BOOL_T value)
{
  //## begin cState::set_StartRequest%3A4B67470096.set preserve=no
  _StartRequest = value;
  //## end cState::set_StartRequest%3A4B67470096.set
}

BOOL_T cState::get_DownloadRequest () const
{
  //## begin cState::get_DownloadRequest%3A4B561A033C.get preserve=no
  return _DownloadRequest;
  //## end cState::get_DownloadRequest%3A4B561A033C.get
}

void cState::set_DownloadRequest (BOOL_T value)
{
  //## begin cState::set_DownloadRequest%3A4B561A033C.set preserve=no
  _DownloadRequest = value;
  //## end cState::set_DownloadRequest%3A4B561A033C.set
}

BOOL_T cState::get_StopRequest () const
{
  //## begin cState::get_StopRequest%3A4B675800CC.get preserve=no
  return _StopRequest;
  //## end cState::get_StopRequest%3A4B675800CC.get
}

void cState::set_StopRequest (BOOL_T value)
{
  //## begin cState::set_StopRequest%3A4B675800CC.set preserve=no
  _StopRequest = value;
  //## end cState::set_StopRequest%3A4B675800CC.set
}

BOOL_T cState::get_AbortRequest () const
{
  //## begin cState::get_AbortRequest%3A6EC8B3016D.get preserve=no
  return _AbortRequest;
  //## end cState::get_AbortRequest%3A6EC8B3016D.get
}

void cState::set_AbortRequest (BOOL_T value)
{
  //## begin cState::set_AbortRequest%3A6EC8B3016D.set preserve=no
  _AbortRequest = value;
  //## end cState::set_AbortRequest%3A6EC8B3016D.set
}

BOOL_T cState::get_UploadEnabled () const
{
  //## begin cState::get_UploadEnabled%3A6EC9D201DE.get preserve=no
  return _UploadEnabled;
  //## end cState::get_UploadEnabled%3A6EC9D201DE.get
}

void cState::set_UploadEnabled (BOOL_T value)
{
  //## begin cState::set_UploadEnabled%3A6EC9D201DE.set preserve=no
  _UploadEnabled = value;
  //## end cState::set_UploadEnabled%3A6EC9D201DE.set
}

BOOL_T cState::get_DownloadEnabled () const
{
  //## begin cState::get_DownloadEnabled%3A6EC9E5020E.get preserve=no
  return _DownloadEnabled;
  //## end cState::get_DownloadEnabled%3A6EC9E5020E.get
}

void cState::set_DownloadEnabled (BOOL_T value)
{
  //## begin cState::set_DownloadEnabled%3A6EC9E5020E.set preserve=no
  _DownloadEnabled = value;
  //## end cState::set_DownloadEnabled%3A6EC9E5020E.set
}

BOOL_T cState::get_ProductionTerminated () const
{
  //## begin cState::get_ProductionTerminated%3A6ECA0C0250.get preserve=no
  return _ProductionTerminated;
  //## end cState::get_ProductionTerminated%3A6ECA0C0250.get
}

void cState::set_ProductionTerminated (BOOL_T value)
{
  //## begin cState::set_ProductionTerminated%3A6ECA0C0250.set preserve=no
  _ProductionTerminated = value;
  //## end cState::set_ProductionTerminated%3A6ECA0C0250.set
}

ULONG_T cState::get_ProductionSet () const
{
  //## begin cState::get_ProductionSet%3E5B78DD0347.get preserve=no
  return _ProductionSet;
  //## end cState::get_ProductionSet%3E5B78DD0347.get
}

void cState::set_ProductionSet (ULONG_T value)
{
  //## begin cState::set_ProductionSet%3E5B78DD0347.set preserve=no
  _ProductionSet = value;
  //## end cState::set_ProductionSet%3E5B78DD0347.set
}

ULONG_T cState::get_Cavities () const
{
  //## begin cState::get_Cavities%3E5B78DD0348.get preserve=no
  return _Cavities;
  //## end cState::get_Cavities%3E5B78DD0348.get
}

void cState::set_Cavities (ULONG_T value)
{
  //## begin cState::set_Cavities%3E5B78DD0348.set preserve=no
  _Cavities = value;
  //## end cState::set_Cavities%3E5B78DD0348.set
}

ULONG_T cState::get_GoodCycles () const
{
  //## begin cState::get_GoodCycles%3E5B78DD0351.get preserve=no
  return _GoodCycles;
  //## end cState::get_GoodCycles%3E5B78DD0351.get
}

void cState::set_GoodCycles (ULONG_T value)
{
  //## begin cState::set_GoodCycles%3E5B78DD0351.set preserve=no
  _GoodCycles = value;
  //## end cState::set_GoodCycles%3E5B78DD0351.set
}

ULONG_T cState::get_PoorCycles () const
{
  //## begin cState::get_PoorCycles%3E5B78DD0352.get preserve=no
  return _PoorCycles;
  //## end cState::get_PoorCycles%3E5B78DD0352.get
}

void cState::set_PoorCycles (ULONG_T value)
{
  //## begin cState::set_PoorCycles%3E5B78DD0352.set preserve=no
  _PoorCycles = value;
  //## end cState::set_PoorCycles%3E5B78DD0352.set
}

ULONG_T cState::get_GoodParts () const
{
  //## begin cState::get_GoodParts%3E5B78DD0353.get preserve=no
  return _GoodParts;
  //## end cState::get_GoodParts%3E5B78DD0353.get
}

void cState::set_GoodParts (ULONG_T value)
{
  //## begin cState::set_GoodParts%3E5B78DD0353.set preserve=no
  _GoodParts = value;
  //## end cState::set_GoodParts%3E5B78DD0353.set
}

ULONG_T cState::get_PoorParts () const
{
  //## begin cState::get_PoorParts%3E5B78DD035B.get preserve=no
  return _PoorParts;
  //## end cState::get_PoorParts%3E5B78DD035B.get
}

void cState::set_PoorParts (ULONG_T value)
{
  //## begin cState::set_PoorParts%3E5B78DD035B.set preserve=no
  _PoorParts = value;
  //## end cState::set_PoorParts%3E5B78DD035B.set
}

ULONG_T cState::get_ShotCount () const
{
  //## begin cState::get_ShotCount%3E5B78DD035C.get preserve=no
  return _ShotCount;
  //## end cState::get_ShotCount%3E5B78DD035C.get
}

void cState::set_ShotCount (ULONG_T value)
{
  //## begin cState::set_ShotCount%3E5B78DD035C.set preserve=no
  _ShotCount = value;
  //## end cState::set_ShotCount%3E5B78DD035C.set
}

ULONG_T cState::get_AddingShotCount () const
{
  //## begin cState::get_AddingShotCount%3E5B78DD0365.get preserve=no
  return _AddingShotCount;
  //## end cState::get_AddingShotCount%3E5B78DD0365.get
}

void cState::set_AddingShotCount (ULONG_T value)
{
  //## begin cState::set_AddingShotCount%3E5B78DD0365.set preserve=no
  _AddingShotCount = value;
  //## end cState::set_AddingShotCount%3E5B78DD0365.set
}

ULONG_T cState::get_SubtractingShotCount () const
{
  //## begin cState::get_SubtractingShotCount%3E5B78DD0366.get preserve=no
  return _SubtractingShotCount;
  //## end cState::get_SubtractingShotCount%3E5B78DD0366.get
}

void cState::set_SubtractingShotCount (ULONG_T value)
{
  //## begin cState::set_SubtractingShotCount%3E5B78DD0366.set preserve=no
  _SubtractingShotCount = value;
  //## end cState::set_SubtractingShotCount%3E5B78DD0366.set
}

DOUBLE_T cState::get_CycleTime () const
{
  //## begin cState::get_CycleTime%3E5B78DD0367.get preserve=no
  return _CycleTime;
  //## end cState::get_CycleTime%3E5B78DD0367.get
}

void cState::set_CycleTime (DOUBLE_T value)
{
  //## begin cState::set_CycleTime%3E5B78DD0367.set preserve=no
  _CycleTime = value;
  //## end cState::set_CycleTime%3E5B78DD0367.set
}

STRING_T cState::get_OrderNo () const
{
  //## begin cState::get_OrderNo%3ECB6055038A.get preserve=no
  return _OrderNo;
  //## end cState::get_OrderNo%3ECB6055038A.get
}

void cState::set_OrderNo (STRING_T value)
{
  //## begin cState::set_OrderNo%3ECB6055038A.set preserve=no
  _OrderNo = value;
  //## end cState::set_OrderNo%3ECB6055038A.set
}

STRING_T cState::get_ArticleNo () const
{
  //## begin cState::get_ArticleNo%3ECB606E01D4.get preserve=no
  return _ArticleNo;
  //## end cState::get_ArticleNo%3ECB606E01D4.get
}

void cState::set_ArticleNo (STRING_T value)
{
  //## begin cState::set_ArticleNo%3ECB606E01D4.set preserve=no
  _ArticleNo = value;
  //## end cState::set_ArticleNo%3ECB606E01D4.set
}

// Additional Declarations
  //## begin cState%37B1C8E300E0.declarations preserve=yes
  //## end cState%37B1C8E300E0.declarations

//## begin module%37B1C8E300E0.epilog preserve=yes
//## end module%37B1C8E300E0.epilog
