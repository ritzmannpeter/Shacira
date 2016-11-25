
#ifndef __i60prot__
#define __i60prot__

/*.SI.***********************************************************************/
#include <syntax.h>
/*.EI.***********************************************************************/

GLOBAL int PROT_I60Load(int channel, BYTE order, int iscos_no, UWORD reg_addr,
                        UWORD noof_regs, void *inp, UWORD timeout);
GLOBAL int PROT_I60Save(int channel, char order, int iscos_no, UWORD reg_addr,
                        UWORD noof_regs, void *inp, UWORD timeout);
GLOBAL int PROT_I60Bit(int channel, UWORD bit_no, int iscos_no, char function,
                       UWORD timeout);
GLOBAL int PROT_I60Req(int channel, void *inp, void *out, UWORD size,
                       UWORD * inp_size, UWORD timeout);
GLOBAL int PROT_I60Com(int channel, void *inp, void *out, UWORD size,
                       UWORD * inp_size, UWORD timeout);
#define PROT_I60Close(channel)   I60Close(channel)
GLOBAL int PROT_I60Open(int channel, int iscos_no, long baudrate, BYTE parity,
                        BYTE charlen, BYTE stopbits);
#define PROT_I60Error(channel)   I60Error(channel)
#define PROT_I60Version()        I60Version()
#define PROT_I60SetParam(channel, id, param)    I60SetParam(channel, id, param)
#define PROT_I60SetSpsState(channel, state)     I60SetSpsState(channel, state)
#define PROT_I60GetSpsState(channel, state)     I60GetSpsState(channel, state)

#endif /* __i60prot__ */
