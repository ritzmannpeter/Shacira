/*
 * author schneider
 *
 * This sofware may by copyright protected!
 * 
 */


/** \file
 */

#include "queue_handle.h"

/** Init a queue
 * 
 * sets read_ptr and write ptr to '-1' and the size to Queue_Size
 */
Queue_T InitQueue()
{
	Queue_T q;
	q.read_ptr = q.write_ptr = -1;
	q.size = Queue_Size;
	return q;
}

/** Pointer to the OutQueue
 * 
 * \note To set this up use SetOutQueue()
 */
static Queue_T* out_q;
/** Pointer to the InQueue
 * 
 * \note To set this up use SetInQueue()
 */
static Queue_T* in_q;
/** locally used temp var
 */
static Queue_Element_T tmp;

/** locally used to reset the temporary var tmp
 */
static void ResetTmp()
{
	UINT8 i;
	for(i=0;i<Data_Len_in_Queue;i++) tmp.Data[i]=0;
	tmp.Length = 0;
}

void SetOutQueue(Queue_T* q)
{
	out_q = q;
	*out_q = InitQueue();
}
void SetInQueue(Queue_T* q)
{
	in_q = q;
	*in_q = InitQueue();
}

/** locally used to set up the temporary var tmp with the given data
 */
static void SetTmp(UINT8* data,UINT8 len)
{
	UINT8 i;
	ResetTmp();
	for(i=0; i<len ; i++)
	{
		if(i>Data_Len_in_Queue) break;
		tmp.Data[i] = data[i];
	}
	tmp.Length=i;
}

void AddData2OutQueue(UINT8* data , UINT8 len)
{
	SetTmp(data,len);
	AddQueueElement(out_q,tmp);
}

void AddData2InQueue(UINT8* data , UINT8 len)
{
	SetTmp(data,len);
	AddQueueElement(in_q,tmp);
}


/** Add an element to an existing queue 
 * 
 * 1st arguement is an pointer to the speific queue
 * 2nd arguement is the element which should be added 
 */
int AddQueueElement(Queue_T *q ,Queue_Element_T e)
{
if (q == 0) return 0;
   if( 0 > q->write_ptr )
	{
		q->data[++(q->write_ptr)] = e;
		q->read_ptr = (q->write_ptr)++;
		
		return 1;
	}/*Erstmaliges einschreiben*/
	
	else if( (q->write_ptr+1) != q->read_ptr )
	{
		q->data[(q->write_ptr)] = e;
		if( ++(q->write_ptr) == q->size ) q->write_ptr = 0;
		return 1;
	}
	return -1;//Queue Voll!
}

/** Returns "oldest" element in queue (requestID=0 if queue empty!)
 * 
 * arguement is an pointer to the queue which should be read
 * 
 * increments read_ptr in queue
 */
Queue_Element_T* GetQueueElement(Queue_T *q)
{
	Queue_Element_T *e;
	if( q->read_ptr != (q->write_ptr) )
	{
		e=&(q->data[(q->read_ptr)]);
		if( ++(q->read_ptr) == q->size ) q->read_ptr = 0;
		return e;
	}
	else
	{
		//e.requestID = 0;
		return 0;
	}
}

unsigned char* GetFromOutQueue(unsigned char* ptr)
{
	unsigned char* ret=0;
	Queue_Element_T* z;
	z=GetQueueElement(out_q);
	if(z){
		*ptr=z->Length;
		ret=z->Data;
	}
	return ret;
}

unsigned char* GetFromInQueue(unsigned char* ptr)
{
	unsigned char* ret=0;
	Queue_Element_T* z;
	z=GetQueueElement(in_q);
	if(z){
		*ptr=z->Length;
		ret=z->Data;
	}
	return ret;
}
