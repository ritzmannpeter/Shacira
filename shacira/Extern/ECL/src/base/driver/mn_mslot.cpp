
#ifndef __linux__

// ===========================================================================
// base/driver/mn_mslot.cpp                                     ______ /  ECL
// Autor: Thomas Epting                                        /__ ___/  
// ---------------------------------------------------------- /___/  /_____ --
//                                                               /_____
// 
// ===========================================================================


// Interface header
#include "base/driver/mn_mslot.h"

// Platform dependant header
#if defined __ECL_W32__
   #include <windows.h>
#endif




namespace ecl {




// Konstanten der Masken fuer __ECL_ASSERT__ etc.
const unsigned long IPC_ERROR = cBase::dbgError | cBase::dbgIpc;
const unsigned long IPC_WARN  = cBase::dbgWarn  | cBase::dbgIpc;

// Implementierung cMsgNodeMSLOT
// ===========================================================================

#define MAX_MAILSLOT_MSG_SIZE 512

cMsgNodeMSLOT::cMsgNodeMSLOT(cString name, int send_mode) :
   cMsgNode(name, send_mode)
{
   __ECL_STATISTIC__("cMsgNodeMSLOT")
   _write_mslot = _read_mslot = 0;
}

bool cMsgNodeMSLOT::ping()
{
   //__ECL_RELEASE_TEXT__(IPC_ERROR, "Win32: cMsgBox::ping() not implemented for Mailslots");
   cString fn = getFullName();
   HANDLE port = CreateFile(getFullName(),
      0, FILE_SHARE_READ|FILE_SHARE_WRITE, 0,
      OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
   if ( port == INVALID_HANDLE_VALUE ) {
      return false;
   } else {
      CloseHandle(port);
      return true;
   }
}

void cMsgNodeMSLOT::createChannel(int /*msg_count*/, int /*msg_size*/)
{
   _read_mslot = CreateMailslot(getFullName(), MAX_MAILSLOT_MSG_SIZE,
      getWait() ? MAILSLOT_WAIT_FOREVER : 0, 0);
   if ( _read_mslot == INVALID_HANDLE_VALUE ) {
      __ECL_RELEASE_PRINTF__(IPC_ERROR, ("Win32: Could not create mailslot '%s'", (const char *)getFullName()));
      throw cErrMsg(cErrMsg::errCreateChannel, getFullName());
   }
}

void cMsgNodeMSLOT::closeChannel()
{
   if ( _read_mslot != 0 ) {
      CloseHandle(_read_mslot);
      _read_mslot = 0;
   }
}

void cMsgNodeMSLOT::connectToChannel()
{
   HANDLE port = CreateFile(getFullName(),
      GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, 0,
      OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
   if ( port == INVALID_HANDLE_VALUE ) {
      __ECL_RELEASE_PRINTF__(IPC_ERROR, ("Win32: Could not open mailslot '%s'", (const char *)getFullName()));
      throw cErrMsg(cErrMsg::errOpenChannel, getFullName());
   }
   _write_mslot = port;
}

void cMsgNodeMSLOT::disconnectFromChannel()
{
   if ( _write_mslot != 0 ) {
      CloseHandle(_write_mslot);
      _write_mslot = 0;
   }
}

cString cMsgNodeMSLOT::getFullName() const
{
   return "\\\\" + getAddress() + "\\mailslot\\ecl\\" + getName();
}

void cMsgNodeMSLOT::sendMsg(cMsg msg)
{
   int retries = 2;
   BOOL ok = FALSE;
   DWORD bytes_written = 0;

   if ( _write_mslot == 0 )
      connectToChannel();

   while ( retries-- > 0 ) {
      ok = WriteFile(_write_mslot, getMsg(msg),
         getMsgLen(msg), &bytes_written, 0);
      if ( ok && bytes_written == (DWORD)getMsgLen(msg) )
         break;
      connectToChannel();
      ok = FALSE;
   }

   if ( !ok ) {
      __ECL_RELEASE_PRINTF__(IPC_ERROR, ("Win32: WriteFile failed (err=%x, written=%d, expected=%d)", GetLastError(), bytes_written, getMsgLen(msg)));
      throw cErrMsg(cErrMsg::errSendToChannel, getFullName());
   }
}

cMsg cMsgNodeMSLOT::callMsg(cMsg msg, int /*timeout*/)
{
   __ECL_RELEASE_TEXT__(IPC_WARN, "Win32: Warning: Ignoring cMsgRecipient::call() for Mailslots");
   return cMsg();
}

cMsg cMsgNodeMSLOT::receiveMsg()
{
   DWORD current_timeout, sizeof_next_msg, number_of_msgs, bytes_read;
   DWORD desired_timeout = getWait() ? MAILSLOT_WAIT_FOREVER : 0;

   BOOL ok = GetMailslotInfo(_read_mslot, 0,
      &sizeof_next_msg, &number_of_msgs, &current_timeout);

   if ( !ok ) {
      __ECL_RELEASE_TEXT__(IPC_ERROR, "Win32: GetMailslotInfo failed");
      throw cErrMsg(cErrMsg::errReceiveFromChannel, getFullName());
   }
   if ( current_timeout != desired_timeout
     && !SetMailslotInfo(_read_mslot, desired_timeout) )
   {
      __ECL_RELEASE_TEXT__(IPC_ERROR, "Win32: SetMailslotInfo failed");
      throw cErrMsg(cErrMsg::errReceiveFromChannel, getFullName());
   }

   if ( number_of_msgs == 0 && desired_timeout == 0 )
      return cMsg();   // Legaler Zustand: Keine Meldung vorhanden

   char mem[MAX_MAILSLOT_MSG_SIZE];
   ok = ReadFile(_read_mslot, mem, MAX_MAILSLOT_MSG_SIZE, &bytes_read, 0);
   cMsg msg = newMsg(mem);

   if ( !ok ) {
      __ECL_RELEASE_PRINTF__(IPC_ERROR, ("Win32: ReadFile failed (read only %d bytes of %d)", bytes_read, sizeof_next_msg));
      throw cErrMsg(cErrMsg::errReceiveFromChannel, getFullName());
   } else if ( !msg.isValid() ) {
      __ECL_RELEASE_TEXT__(IPC_ERROR, "Win32: Received an invalid memory block");
      throw cErrMsg(cErrMsg::errInvalidMsg, getFullName());
   }

   return msg;
}

bool cMsgNodeMSLOT::mustReplyMsg(const cMsg& /*msg_to_reply*/)
{
   return false;
}

void cMsgNodeMSLOT::replyMsg(const cMsg& /*msg_to_reply*/, cMsg reply_msg)
{
   __ECL_RELEASE_TEXT__(IPC_WARN, "Win32: Ignoring cMsgBox::reply() for Mailslots");
}




}; // namespace ecl

#endif

