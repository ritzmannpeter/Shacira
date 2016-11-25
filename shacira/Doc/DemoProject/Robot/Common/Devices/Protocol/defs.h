/*
 * author schneider
 *
 * This sofware may by copyright protected!
 * 
 */


#ifndef DEFS_H_
#define DEFS_H_

/** \file defs.h
 * \brief Header-file for including the needed definitions for the
 * framed protocol. Also including the setup definitions for the Robot.
 * 
 * 
 */

/** \def START
 * \brief Start sequence
 * 
 * This Byte indicates the start of one protocol frame.
 */

/** \def STOP
 * \brief Stop sequence
 * 
 * This byte indicates the end of one protocol frame.
 */

/** \def ESCAPE
 * \brief Escape sequence
 * 
 * This byte will be put before a data byte, when the data byte is equal to one of
 * \li START
 * \li STOP
 * \li ESCAPE
 * 
 * \note The escaped data byte will also be XORed with 0x80!
 */
#define START 0xF8//0xCC
#define STOP 0xFE//0x33
#define ESCAPE 0xFC//0xA6

#define SET_COMMAND 0xA5
#define REQ_COMMAND 0x5A
#define RESP_COMMAND 0x0F

#define ID_DESCR 0xFD
/** \def ERROR_RESPONSE
 * \brief Error response command
 */
#define ERROR_RESPONSE 0xFA /*FAilure*/
/** \def ERR_CHECKSUM
 * \brief Error in checksum
 */
#define ERR_CHECKSUM 0xF0
/** \def ERR_UNKNOWN_COMMAND
 * \brief Error: command unknown
 */
#define ERR_UNKNOWN_COMMAND 0xF1
/** \def ERR_BUFFER_OVERFLOW
 * \brief Error: buffer overflow
 */
#define ERR_BUFFER_OVERFLOW 0xF2
/** \def ERR_INCOMPLETE_FRAME
 * \brief Err: Frame incomplete
 */
#define ERR_INCOMPLETE_FRAME 0xF3
/** \def ERR_TIMEOUT
 * \brief Error: timeout
 */
#define ERR_TIMEOUT 0xF4
/** \def ERR_BUSY
 * \brief Error: reciever is busy
 */
#define ERR_BUSY 0xF5

/** \def PARAMETER_ID
 * \brief ParameterID of aplication
 */
#define PARAMETER_ID 0xFD
/** \todo must be set
 */
#define ID_MAGIC /*Asuro ID*/
/** \todo must be set
 */
#define ID_VERSION
/** \todo must be set
 */
#define ID_SERIAL
/** \todo must be set
 */
#define ID_SERIAL
/** \todo must be set
 */
#define ID_FRAME_LIMIT

/** \var typedef unsigned char UINT8
 * \brief Typedefing unsigned char to UINT8
 */
typedef unsigned char UINT8;

/** \def Queue_Size
 * \brief defines the size of the queue
 */
/** \def Data_Len_in_Queue
 * \brief defines the length of the data stored in queue
 */ 
#define Queue_Size 5
#define Data_Len_in_Queue 40

/** \typedef typedef unsigned char (*RecByte_f)()
 * 
 * Function Ponter to unsigned char FKT()
 */
 
/** \typedef typedef void (*SendByte_f)(UINT8)
 * 
 * Function Ponter to void FKT(unsigned char)
 */
 
 /** \typedef void (*ComputeFrame_f)(UINT8*,UINT8);
 * 
 * Function Ponter to voidFKT(UINT8*,UINT8)
 */
  
typedef unsigned char (*RecByte_f)();
typedef void (*SendByte_f)(UINT8);
typedef void (*ComputeFrame_f)(UINT8*,UINT8);

#endif /*DEFS_H_*/
/*! \mainpage 2i framed protocol deocumentation 
 *
 * \section intro_sec Einführung
 *
 * Diese Bibliothek ermöglicht die Kommunikation unter der Verwendung
 * eines geframten Protokolls. Im Folgenden wird der generelle Aufbau
 * eines Frames beschrieben und auf spezielle Kommandos hingewiesen.
 * 
 * \section framing_sec Framing-Protokoll
 *  
 * Jeder Frame besteht dabei im wesentclichen
 * aus drei Teilen:
 * \li Start-Sequenz
 * \li Datenblock der Anwendung
 * \li Stop- bzw. End-Sequenz
 * 
 * Wobei START einen neuen Frame einleitet, während STOP ihn beendet.
 * Diese Zeichen dürfen folglich im Dateblock nicht mehr auftreten.
 * Sollten sie dort jedoch auftreten wird ihnen ein ESCAPE-Zeichen vorangestellt und
 * der Wert selbst mit 0x80 "ge-XOR-ed". Das gleiche gilt auch für eventuell anfallende 
 * Daten, die gleich dem ESCAPE Zeichen sind.
 * 
 * \dotfile "frame.dotfile" "Aufbau eines Frames"
 * 
 * \dotfile "tst1.dotfile" "Testfile"
 *
 * \section send_rec Sende- und Empfangs-Aufbau
 * 
 * \subsection send Sendevorschrift
 * 
 * Das Senden aines Datenblocks gliedert sich wie folgt:
 * \li START senden
 * \li für jedes Byte des Datenblocks:\n
 * (Byte == START) || (Byte == STOP) || (Byte == ESCAPE) ==> Sende ESCAPE und Byte^0x80\n
 * sonst ==> Sende Byte 
 * \li STOP senden
 * 
 * 
 * 
 * 
 */
