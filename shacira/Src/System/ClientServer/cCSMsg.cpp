//## begin module%4102753A033C.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%4102753A033C.cm

//## begin module%4102753A033C.cp preserve=no
//	Copyright © 2002 - 2006 by
//	2i Industrial Informatics GmbH
//## end module%4102753A033C.cp

//## Module: cCSMsg%4102753A033C; Pseudo Package body
//## Source file: E:\usr\prj\Shacira\Src\System\ClientServer\cCSMsg.cpp

//## begin module%4102753A033C.additionalIncludes preserve=no
#include "FirstHeader.h"
//## end module%4102753A033C.additionalIncludes

//## begin module%4102753A033C.includes preserve=yes
//## end module%4102753A033C.includes

// cCSMsg
#include "System/ClientServer/cCSMsg.h"
//## begin module%4102753A033C.additionalDeclarations preserve=yes

#define EXTENDED_CS_MAGIC     0xaabbccdd

//## end module%4102753A033C.additionalDeclarations


// Class cCSMsg 










cCSMsg::cCSMsg()
  //## begin cCSMsg::cCSMsg%.hasinit preserve=no
      : _Header(NULL), _Data(NULL), _DataSize(0), _AppData(NULL), _AppDataSize(0), _Allocated(false), _RefCount(0), _ReceivedBlocks(0), _IsComplete(false)
  //## end cCSMsg::cCSMsg%.hasinit
  //## begin cCSMsg::cCSMsg%.initialization preserve=yes
  //## end cCSMsg::cCSMsg%.initialization
{
  //## begin cCSMsg::cCSMsg%.body preserve=yes
   _RefCount++;
  //## end cCSMsg::cCSMsg%.body
}

cCSMsg::cCSMsg(const cCSMsg &right)
  //## begin cCSMsg::cCSMsg%copy.hasinit preserve=no
      : _Header(NULL), _Data(NULL), _DataSize(0), _AppData(NULL), _AppDataSize(0), _Allocated(false), _RefCount(0), _ReceivedBlocks(0), _IsComplete(false)
  //## end cCSMsg::cCSMsg%copy.hasinit
  //## begin cCSMsg::cCSMsg%copy.initialization preserve=yes
  //## end cCSMsg::cCSMsg%copy.initialization
{
  //## begin cCSMsg::cCSMsg%copy.body preserve=yes
   _Header = right._Header;
   _Data = right._Data;
   _DataSize = right._DataSize;
   _AppData = right._AppData;
   _AppDataSize = right._AppDataSize;
   _Allocated = right._Allocated;
   _RefCount = right._RefCount;
   _RefCount++;
  //## end cCSMsg::cCSMsg%copy.body
}

cCSMsg::cCSMsg (PTR_T data, ULONG_T data_size, ULONG_T client_id, ULONG_T request_id, ULONG_T block_no, ULONG_T block_count, ULONG_T msg_size, ULONG_T msg_offset, USHORT_T listener_port)
  //## begin cCSMsg::cCSMsg%1107416646.hasinit preserve=no
      : _Header(NULL), _Data(NULL), _DataSize(0), _AppData(NULL), _AppDataSize(0), _Allocated(false), _RefCount(0), _ReceivedBlocks(0), _IsComplete(false)
  //## end cCSMsg::cCSMsg%1107416646.hasinit
  //## begin cCSMsg::cCSMsg%1107416646.initialization preserve=yes
  //## end cCSMsg::cCSMsg%1107416646.initialization
{
  //## begin cCSMsg::cCSMsg%1107416646.body preserve=yes
   ULONG_T required_size = sizeof(EXTENDED_CS_MSG_T) + data_size;
   _Header = (EXTENDED_CS_MSG_T*)cSystemUtils::Alloc(required_size);
   _Data = _Header;
   _DataSize = required_size;
   _AppData = ((UCHAR_T*)_Header) + sizeof(EXTENDED_CS_MSG_T);
   _AppDataSize = data_size;
   _Allocated = true;
   _Header->magic = EXTENDED_CS_MAGIC;
   _Header->client_id = client_id;
   _Header->request_id = request_id;
   _Header->data_size = data_size;
   _Header->data_offset = sizeof(EXTENDED_CS_MSG_T);
   _Header->msg_size = msg_size;
   _Header->msg_offset = msg_offset;
   _Header->block_no = block_no;
   _Header->block_count = block_count;
   _Header->listener_port = listener_port;
   memcpy(_AppData, data, data_size);
   _RefCount++;
  //## end cCSMsg::cCSMsg%1107416646.body
}

cCSMsg::cCSMsg (PTR_T data, ULONG_T data_size, BOOL_T copy)
  //## begin cCSMsg::cCSMsg%1090681456.hasinit preserve=no
      : _Header(NULL), _Data(NULL), _DataSize(0), _AppData(NULL), _AppDataSize(0), _Allocated(false), _RefCount(0), _ReceivedBlocks(0), _IsComplete(false)
  //## end cCSMsg::cCSMsg%1090681456.hasinit
  //## begin cCSMsg::cCSMsg%1090681456.initialization preserve=yes
  //## end cCSMsg::cCSMsg%1090681456.initialization
{
  //## begin cCSMsg::cCSMsg%1090681456.body preserve=yes
   EXTENDED_CS_MSG_T * header = (EXTENDED_CS_MSG_T*)data;
   if (header->magic == EXTENDED_CS_MAGIC) {
      _Header = header;
      _Data = _Header;
      _DataSize = data_size;
      _AppData = ((UCHAR_T*)_Data) + _Header->data_offset;
      _AppDataSize = _Header->data_size;
   } else {
      _DataSize = _AppDataSize = data_size;
      if (copy) {
         _AppData = _Data = cSystemUtils::Alloc(_DataSize);
         memcpy(_Data, data, _DataSize);
         _Allocated = true;
      } else {
         _AppData = _Data = data;
      }
   }
   _RefCount++;
  //## end cCSMsg::cCSMsg%1090681456.body
}

cCSMsg::cCSMsg (ULONG_T data_size)
  //## begin cCSMsg::cCSMsg%1090862811.hasinit preserve=no
      : _Header(NULL), _Data(NULL), _DataSize(0), _AppData(NULL), _AppDataSize(0), _Allocated(false), _RefCount(0), _ReceivedBlocks(0), _IsComplete(false)
  //## end cCSMsg::cCSMsg%1090862811.hasinit
  //## begin cCSMsg::cCSMsg%1090862811.initialization preserve=yes
  //## end cCSMsg::cCSMsg%1090862811.initialization
{
  //## begin cCSMsg::cCSMsg%1090862811.body preserve=yes
   _AppDataSize = _DataSize = data_size;
   _AppData = _Data = cSystemUtils::Alloc(_DataSize);
   _Allocated = true;
   _RefCount++;
  //## end cCSMsg::cCSMsg%1090862811.body
}


cCSMsg::~cCSMsg()
{
  //## begin cCSMsg::~cCSMsg%.body preserve=yes
   _RefCount--;
   if (_RefCount == 0) {
      if (_Allocated) {
         if (_Data != NULL) {
//if (DataSize() > 10000) printf("free %d %d\n", RequestId(), DataSize());
            cSystemUtils::Free(_Data);
         }
      }
   } else {
      int dummy = 0;
   }
  //## end cCSMsg::~cCSMsg%.body
}



//## Other Operations (implementation)
PTR_T cCSMsg::Data ()
{
  //## begin cCSMsg::Data%1090681468.body preserve=yes
   return _Data;
  //## end cCSMsg::Data%1090681468.body
}

ULONG_T cCSMsg::DataSize ()
{
  //## begin cCSMsg::DataSize%1090681469.body preserve=yes
   return _DataSize;
  //## end cCSMsg::DataSize%1090681469.body
}

PTR_T cCSMsg::AppData ()
{
  //## begin cCSMsg::AppData%1107416635.body preserve=yes
   return _AppData;
  //## end cCSMsg::AppData%1107416635.body
}

ULONG_T cCSMsg::AppDataSize ()
{
  //## begin cCSMsg::AppDataSize%1090860526.body preserve=yes
   return _AppDataSize;
  //## end cCSMsg::AppDataSize%1090860526.body
}

void cCSMsg::SetAppDataSize (ULONG_T size)
{
  //## begin cCSMsg::SetAppDataSize%1090860527.body preserve=yes
   _AppDataSize = size;
   if (_Header != NULL) {
      _Header->data_size = _AppDataSize;
   }
  //## end cCSMsg::SetAppDataSize%1090860527.body
}

cCSMsg * cCSMsg::CopyMsg ()
{
  //## begin cCSMsg::CopyMsg%1107416633.body preserve=yes
   return NULL;
  //## end cCSMsg::CopyMsg%1107416633.body
}

ULONG_T cCSMsg::ClientId ()
{
  //## begin cCSMsg::ClientId%1107416636.body preserve=yes
   if (_Header != NULL) {
      return _Header->client_id;
   } else {
      return 0;
   }
  //## end cCSMsg::ClientId%1107416636.body
}

ULONG_T cCSMsg::RequestId ()
{
  //## begin cCSMsg::RequestId%1107416637.body preserve=yes
   if (_Header != NULL) {
      return _Header->request_id;
   } else {
      return 0;
   }
  //## end cCSMsg::RequestId%1107416637.body
}

ULONG_T cCSMsg::MsgSize ()
{
  //## begin cCSMsg::MsgSize%1107416638.body preserve=yes
   if (_Header != NULL) {
      return _Header->msg_size;
   } else {
      return 0;
   }
  //## end cCSMsg::MsgSize%1107416638.body
}

ULONG_T cCSMsg::MsgOffset ()
{
  //## begin cCSMsg::MsgOffset%1107416639.body preserve=yes
   if (_Header != NULL) {
      return _Header->msg_offset;
   } else {
      return 0;
   }
  //## end cCSMsg::MsgOffset%1107416639.body
}

ULONG_T cCSMsg::BlockNo ()
{
  //## begin cCSMsg::BlockNo%1107416640.body preserve=yes
   if (_Header != NULL) {
      return _Header->block_no;
   } else {
      return 0;
   }
  //## end cCSMsg::BlockNo%1107416640.body
}

ULONG_T cCSMsg::BlockCount ()
{
  //## begin cCSMsg::BlockCount%1107416641.body preserve=yes
   if (_Header != NULL) {
      return _Header->block_count;
   } else {
      return 0;
   }
  //## end cCSMsg::BlockCount%1107416641.body
}

USHORT_T cCSMsg::ListenerPort ()
{
  //## begin cCSMsg::ListenerPort%1107780743.body preserve=yes
   if (_Header != NULL) {
      return _Header->listener_port;
   } else {
      return 0;
   }
  //## end cCSMsg::ListenerPort%1107780743.body
}

void cCSMsg::SetBlockNo (ULONG_T block_no)
{
  //## begin cCSMsg::SetBlockNo%1107869859.body preserve=yes
   if (_Header != NULL) {
      _Header->block_no = block_no;
   }
  //## end cCSMsg::SetBlockNo%1107869859.body
}

void cCSMsg::SetMsgOffset (ULONG_T msg_offset)
{
  //## begin cCSMsg::SetMsgOffset%1107869860.body preserve=yes
   if (_Header != NULL) {
      _Header->msg_offset = msg_offset;
   }
  //## end cCSMsg::SetMsgOffset%1107869860.body
}

void cCSMsg::SetRequestId (ULONG_T request_id)
{
  //## begin cCSMsg::SetRequestId%1107939282.body preserve=yes
   if (_Header != NULL) {
      _Header->request_id = request_id;
   }
  //## end cCSMsg::SetRequestId%1107939282.body
}

cCSMsg * cCSMsg::Copy (ULONG_T &offset, ULONG_T size)
{
  //## begin cCSMsg::Copy%1107416642.body preserve=yes
   if (_Data != NULL) {
#ifdef lassma
      EXTENDED_CS_MSG_T * header = (EXTENDED_CS_MSG_T*)_Data;
      void * data = _Data + offset;
      ULONG_T block_count = (DataSize() / BLOCK_SIZE) + 1;
      ULONG_T block_no = block_count / BLOCK_SIZE;
      cExtendedMsg * msg =
         new cCSMsg(data, size, ClientId(), RequestId(), BLOCK_SIZE, offset, block_no, block_count);
      offset += BLOCK_SIZE;
      return msg;
#endif
      return NULL;
   } else {
      return NULL;
   }
  //## end cCSMsg::Copy%1107416642.body
}

void cCSMsg::Paste (cCSMsg *msg)
{
  //## begin cCSMsg::Paste%1107416643.body preserve=yes
   if (_Data == NULL) {
      ULONG_T required_size = sizeof(EXTENDED_CS_MSG_T) + msg->MsgSize();
      _Header = (EXTENDED_CS_MSG_T*)cSystemUtils::Alloc(required_size);
      _Data = _Header;
      _DataSize = required_size;
      _AppData = ((UCHAR_T*)_Data) + sizeof(EXTENDED_CS_MSG_T);
      _AppDataSize = required_size - sizeof(EXTENDED_CS_MSG_T);
      _Allocated = true;
      _Header->magic = EXTENDED_CS_MAGIC;
      _Header->client_id = msg->ClientId();
      _Header->request_id = msg->RequestId();
      _Header->data_size = msg->MsgSize();
      _Header->data_offset = sizeof(EXTENDED_CS_MSG_T);
      _Header->msg_size = msg->MsgSize();
      _Header->msg_offset = msg->MsgOffset();
      _Header->block_count = msg->BlockCount();
      _Header->listener_port = msg->ListenerPort();
   } else {
      if (_Header != NULL) {
         if (msg->RequestId() != _Header->request_id) {
            ErrorPrintf("request_id mismatch (%d != %d)\n", msg->RequestId(), _Header->request_id);
            ULONG_T required_size = sizeof(EXTENDED_CS_MSG_T) + msg->MsgSize();
            cSystemUtils::Free(_Header);
            _Header = (EXTENDED_CS_MSG_T*)cSystemUtils::Alloc(required_size);
            _Data = _Header;
            _DataSize = required_size;
            _AppData = ((UCHAR_T*)_Data) + sizeof(EXTENDED_CS_MSG_T);
            _AppDataSize = required_size - sizeof(EXTENDED_CS_MSG_T);
            _Allocated = true;
            _Header->magic = EXTENDED_CS_MAGIC;
            _Header->client_id = msg->ClientId();
            _Header->request_id = msg->RequestId();
            _Header->data_size = msg->MsgSize();
            _Header->data_offset = sizeof(EXTENDED_CS_MSG_T);
            _Header->msg_size = msg->MsgSize();
            _Header->msg_offset = msg->MsgOffset();
            _Header->block_count = msg->BlockCount();
            _Header->listener_port = msg->ListenerPort();
            _ReceivedBlocks = 0;
            _IsComplete = false;
         }
      }
   }
   ULONG_T offset = msg->MsgOffset();
   ULONG_T size = msg->DataSize();
   BUF_T dst_ptr = ((UCHAR_T*)_AppData) + msg->MsgOffset();
   BUF_T src_ptr = (BUF_T)msg->AppData();
   memcpy(dst_ptr, src_ptr, msg->AppDataSize());
   _ReceivedBlocks++;
//printf("paste %p ri %d no %d blocks %d received %d\n", this, msg->RequestId(), msg->BlockNo(), msg->BlockCount(), _ReceivedBlocks);
   if (_ReceivedBlocks == _Header->block_count) {
//printf("%d is complete\n", _Header->request_id);
      _IsComplete = true;
   }
  //## end cCSMsg::Paste%1107416643.body
}

BOOL_T cCSMsg::IsComplete ()
{
  //## begin cCSMsg::IsComplete%1107416644.body preserve=yes
   return _IsComplete;
  //## end cCSMsg::IsComplete%1107416644.body
}

// Additional Declarations
  //## begin cCSMsg%4102753A033C.declarations preserve=yes
  //## end cCSMsg%4102753A033C.declarations

//## begin module%4102753A033C.epilog preserve=yes
//## end module%4102753A033C.epilog
