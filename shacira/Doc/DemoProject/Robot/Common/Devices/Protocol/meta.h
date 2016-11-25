/*
 * author schneider
 *
 * This sofware may by copyright protected!
 * 
 */

#ifndef META_H_
#define META_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "defs.h"
#include "queue_handle.h"

/** Function-pointer to the function to write one byte
 * 
 * \note Can be set with SetCommunication()
 */
SendByte_f SendByte;
/** Function-pointer to the function to read one byte
 * 
 * \note Can be set with SetCommunication()
 */
RecByte_f RecByte;


/** \file meta.h
 * \brief Meta functions for communication
 * 
 * These functions act as meta layer between any device which can read or 
 * write single bytes. The devices must have functions to which can be poited with:
 * \li SendByte
 * \li RecByte
 * 
 * These pointers can be set with SetCommunication()
 * 
 * To use the SendFromOutQueue() function an out-queue must be set.
 * See the documentation of queue_handle.h
 */

/** \fn void SendStream(UINT8* stream, UINT8 len)
 * \brief Sends \a len bytes (UINT8) as framed protocol
 * 
 * START - "escaped" stream - STOP
 * 
 * more about the protocol in documentation or source!
 * 
 * Calls the function SendByte() points to, for every byte to send
 */

void SendStream(UINT8* stream, UINT8 len);

/** \fn void SendString(UINT8* string)
 * \brief Send a string of \a UINT8 which ends with char-zero
 * 
 * START - "escaped" stream - STOP
 * 
 * more about the protocol in documentation or source!
 * 
 * Calls the function SendByte() points to, for every byte to send
 */

void SendString(UINT8* string);

/** \brief send an errorcode
 * 
 * Puts a ERROR_RESPONSE before the errorcode
 */
void SendError(UINT8);

/** Init the Communication functions
 */
void SetCommunication(SendByte_f send_fkt , RecByte_f rec_fkt);

/** \brief Send data from the out-queue
 * 
 * \note To use this function the out-queue mus be set with SetOutQueue()
 * 
 * See queue_handle.h for details. 
 */

void SendFromOutQueue();

#ifdef __cplusplus
}
#endif

#endif /*META_H_*/
