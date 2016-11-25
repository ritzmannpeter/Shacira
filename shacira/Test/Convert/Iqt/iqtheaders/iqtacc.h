// iqtacc.h  -  Deklarationen von IQT-Zugriffsfunktionen fuer OPC und Corba

#ifndef _iqtacc_
#define _iqtacc_

#include <hostenum.h>

int FM2RegRead             (REG_ACCESS_T  *acc, long *val);
int FM2TextRead            (TEXT_ACCESS_T *acc, char *buf, int bufsize);
int FM2RegWrite            (REG_ACCESS_T  *acc, long val);
int FM2TextWrite           (TEXT_ACCESS_T *acc, char *buf);

int DataSetRead            (BIN_ACCESS_T  *acc, BYTE **buf, int *buflen);
int DataSetWrite           (BIN_ACCESS_T  *acc, BYTE *buf, int buflen);

int FM2Upload              (BIN_ACCESS_T *acc,  BYTE **buf, int *buflen);
int FM2Download            (BIN_ACCESS_T *acc,  BYTE *buf, int buflen);

int FM2ChangeBufRead       (TEXT_ACCESS_T *acc, char *buf, int bufsize);
int FM2ChangeBufCountRead  (REG_ACCESS_T  *acc, long *val);
int FM2ChangeBufDelete     (REG_ACCESS_T  *acc, long val);

int FM2ErrBufRead          (TEXT_ACCESS_T *acc, char *buf, int bufsize);
int FM2ErrBufCountRead     (REG_ACCESS_T *acc, long *val);
int FM2ErrBufDelete        (REG_ACCESS_T *acc, long val);

int ReadModeOfOperation    (REG_ACCESS_T *acc, long *val);
int ReadMoldClosed         (REG_ACCESS_T *acc, long *val);
int ReadStandstillMsg      (REG_ACCESS_T *acc, long *val);

#endif // _namespcr_

