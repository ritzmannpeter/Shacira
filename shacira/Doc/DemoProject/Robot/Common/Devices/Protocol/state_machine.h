/*
 * author schneider
 *
 * This sofware may by copyright protected!
 * 
 */


#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "defs.h"
#include "queue_handle.h"
#include "meta.h" //not needed get function pointer to send and rec methods
#include <stdio.h>

/** \def STATE_IDLE
 * \brief Waiting for START
 */

/** \def STATE_DATA
 * \brief Recieving data
 */

/** \def STATE_ESCAPE
 * \brief Escape Sequence comming
 */

/** \def STATE_BUSY
 * \brief working
 */
 
/** \def STATE_OVERFLOW
 * \brief buffer to small
 */
 
/** \def STATE_TIMEOUT
 * \brief timeout between data input
 */

#define STATE_IDLE 0
#define STATE_DATA 1
#define STATE_ESCAPE 2
#define STATE_BUSY 3
#define STATE_OVERFLOW 4
#define STATE_TIMEOUT 5

/** \file state_machine.h
 * 
 * These functions can be used to handle incomming bytes.
 * The state machine follows the definitions made for the protocoll.
 * 
 * The state machine must know what to do when one frame is complete
 * so first the InitStateMachine() must be called with ComputeFrame_f()
 */

void InitStateMachine(ComputeFrame_f comp_frame);

/** Handle the given byte with the state machine
 */
int ComputeByte(unsigned char input);

#ifdef __cplusplus
}
#endif

#endif /*STATE_MACHINE_H_*/
