
#ifndef _keypos
#define _keypos

/*.SI.***********************************************************************/
#include <syntax.h>
#include <stddef.h>
/*.EI.***********************************************************************/

#define SETKEYPOS 1
#define KEYPOS 2

typedef struct keypos_msg_type {
BYTE id;
int keypos;
} KEYPOS_MSG_TYPE;

GLOBAL int Tid_KeyPos = 0;

GLOBAL void InitKeyPos ()
{       int retries = 10;

        While ((Tid_KeyPos==0) &&(retries)) Do
                Tid_KeyPos = name_locate( "keypos", My_nid, sizeof(KEYPOS_MSG_TYPE) );
                retries--;
        Endwhile
        return;
}

#define INIT_KEYPOS if (Tid_KeyPos==0) InitKeyPos();

GLOBAL void SetKeyPos(int pos)
{       KEYPOS_MSG_TYPE msg;
        int rep;
 
        INIT_KEYPOS
                                                                
        msg.id = SETKEYPOS;
        msg.keypos = pos;
        send(Tid_KeyPos, (void *) &msg, (void *) &rep,
                 sizeof(KEYPOS_MSG_TYPE), sizeof(int));
        return;
}

GLOBAL int KeyPos()
{       KEYPOS_MSG_TYPE msg;
        int rep;

        INIT_KEYPOS

        msg.id = KEYPOS;
        send(Tid_KeyPos, (void *) &msg, (void *) &rep,
         sizeof(KEYPOS_MSG_TYPE), sizeof(int));
        return rep;
}

#endif /* _keypos */

