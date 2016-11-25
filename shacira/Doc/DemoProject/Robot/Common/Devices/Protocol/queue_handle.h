/*
 * author schneider
 *
 * This sofware may by copyright protected!
 * 
 */


#ifndef QUEUE_HANDLE_H_
#define QUEUE_HANDLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "defs.h"
/** \file queue_handle.h
 * 
 * These functions and typedefed structeres can be used tu handle queues. 
 *  
 * There are two special queues for communication purposes:
 * \li InQueue
 * \li OutQueue
 * 
 * These two can bes set with the functions:
 * \li SetInQueue()
 * \li SetOutQueue()
 * 
 * To easily get data from one of these or to easily put data there you can
 * use one of these functons:
 * \li GetFromOutQueue()
 * \li GetFromInQueue()
 * \li AddData2InQueue()
 * \li AddData2OutQueue()
 */

/** typedef struct Queue_Element_T 
 * 
 * \todo REPLACEABLE by an array!!!! TO DO
 */
typedef struct queue_element_t{
	/** Data array with length defined in defs.h
	 */
	UINT8 Data[Data_Len_in_Queue];
	/** the real length of the data
	 */
	UINT8 Length;
		
}Queue_Element_T;

/** typedef struct queue Queue_T
 * \brief Queue structure
 * Use the given functions to handle the queue!
 * 
 */
typedef struct queue_t{
	/** Index of the next element to read
	 */
	short read_ptr;
	/** Index of the next element to write
	 */
	short write_ptr;
	/** Size of the queue
	 * 
	 * \note Will be set when InitQueue() is called
	 * 
	 * The size will be what is defined in defs.h
	 */
	unsigned short size;
	/** the data-block
	 */
	Queue_Element_T data[Queue_Size];	
}Queue_T;


/** Init a queue
 * 
 * sets \a read_ptr and \a write ptr to '-1' and the size to \a Queue_Size
 */
Queue_T InitQueue();

/** Add an element to an existing queue 
 * 
 * 1st arguement is an pointer to the speific queue
 * 2nd arguement is the element which should be added 
 */
int AddQueueElement(Queue_T *q ,Queue_Element_T e);

/** Sets queue to which the parameter points as outgoing queue
 * 
 * \todo work whith malloc to allocate space
 * for something like Queue_T* out = OutQue();
 */
void SetOutQueue(Queue_T* q);

/** Sets queue to which the parameter points as incomming queue
 * 
 * \todo work whith malloc to allocate space
 * for something like Queue_T* in = InQue();
 */
void SetInQueue(Queue_T* q);

/** Add a data stream with given length to the out-queue
 * 
 * \note The out-queue must be set with SetOutQueue()
 */
void AddData2OutQueue(UINT8* data , UINT8 len);

/** Add a data stream with given length to the in-queue
 * 
 * \note The in-queue must be set with SetInQueue()
 */
void AddData2InQueue(UINT8* data , UINT8 len);

/** Returns a pointer to "oldest" element in queue
 * 
 * arguement is an pointer to the queue which should be read
 * 
 * increments read_ptr in queue
 */
Queue_Element_T* GetQueueElement(Queue_T *q);

/** Use this to get a pointer to next data in out-queue
 * 
 * \return Pointer to data array
 * 
 * \note the submitted referenced unsigned char will store the data-length 
 */
unsigned char* GetFromOutQueue(unsigned char* ptr);
/** Use this to get a pointer to next data in in-queue
 * 
 * \return Pointer to data array
 * 
 * \note the submitted referenced unsigned char will store the data-length 
 */
 unsigned char* GetFromInQueue(unsigned char* ptr);

#ifdef __cplusplus
}
#endif

#endif /*QUEUE_HANDLE_H_*/
