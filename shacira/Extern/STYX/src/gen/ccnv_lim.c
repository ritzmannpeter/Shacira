/* [ccnv_lim.c] Scanner table for 'ccnv'  */

#include "scn_io.h"

#include "scn_imp.h"

/* scanner group 'ccnv' */

static long ccnvStaEdg[22] =
/* first edge per state */
{
          0,        12,        13,        16,        21,        30,
         33,        37,        43,        46,        52,        58,
         61,        62,        65,        68,        71,        76,
         85,        94,        95,       104
};

static short ccnvStaFin[21] =
/* finite token per state */
{
    0,   4,   4,   4,   1,   0,   0,   0,   0,   0,
    3,   0,   3,   0,   0,   0,   0,   0,   0,   2,
    2
};

static wc_char ccnvEdgeC[104] =
/* lowest character per edge */
{ /*State*/
  /*   0 */        256,        123,         97,         96,         95,         91,
                    65,         48,         47,         36,         35,          0,
  /*   1 */          0,
  /*   2 */        106,        105,          0,
  /*   3 */         48,         47,         43,         42,          0,
  /*   4 */        123,         97,         96,         95,         91,         65,
                    58,         48,          0,
  /*   5 */        111,        110,          0,
  /*   6 */        256,         43,         42,          0,
  /*   7 */        256,         14,         13,         11,         10,          0,
  /*   8 */        100,         99,          0,
  /*   9 */        256,         48,         47,         43,         42,          0,
  /*  10 */        256,         14,         13,         11,         10,          0,
  /*  11 */        109,        108,          0,
  /*  12 */          0,
  /*  13 */        118,        117,          0,
  /*  14 */        101,        100,          0,
  /*  15 */        102,        101,          0,
  /*  16 */         33,         32,         10,          9,          0,
  /*  17 */         61,         60,         35,         34,         33,         32,
                    10,          9,          0,
  /*  18 */        256,        128,        127,         63,         62,         35,
                    34,         33,          0,
  /*  19 */          0,
  /*  20 */        256,        128,        127,         63,         62,         35,
                    34,         33,          0
};

static long ccnvEdgeS[104] =
/* follow (state+1) per edge */
{ /*State*/
  /*   0 */         0,         2,         5,         2,         5,         2,
                    5,         2,         4,         2,         3,         2,
  /*   1 */         0,
  /*   2 */         0,         6,         0,
  /*   3 */         0,         8,         0,         7,         0,
  /*   4 */         0,         5,         0,         5,         0,         5,
                    0,         5,         0,
  /*   5 */         0,         9,         0,
  /*   6 */         0,         7,        10,         7,
  /*   7 */         0,         8,        11,         8,        11,         8,
  /*   8 */         0,        12,         0,
  /*   9 */         0,         7,        13,         7,        10,         7,
  /*  10 */         0,         8,        11,         8,        11,         8,
  /*  11 */         0,        14,         0,
  /*  12 */         0,
  /*  13 */         0,        15,         0,
  /*  14 */         0,        16,         0,
  /*  15 */         0,        17,         0,
  /*  16 */         0,        18,         0,        18,         0,
  /*  17 */         0,        19,         0,        19,         0,        18,
                    0,        18,         0,
  /*  18 */         0,        19,         0,        19,        21,        19,
                   20,        19,         0,
  /*  19 */         0,
  /*  20 */         0,        19,         0,        19,        21,        19,
                   20,        19,         0
};

static string ccnvTokens[5] =
/* token -> string */
{
  "[other]",
  "Ide",
  "Inc",
  "Com",
  "Other"
};

static byte ccnvFlags[5] =
/* token -> newid */
{
  0x00, 0x00, 0x00, 0x00, 0x00
};

static ConcreteImp(scn_t) ccnvScanner =
/* the scanner structure */
{
  "ccnv", /* Name    */
  21,     /* States  */
   5,     /* Tokens  */
  ccnvStaEdg,
  ccnvStaFin,
  ccnvEdgeC,
  ccnvEdgeS,
  ccnvTokens,
  ccnvFlags,
   0,     /* Groups  */
  (scn_t*)NULL,
  (short*)NULL,
  0, /* Dyck */
  (short*)NULL,
  (scn_t*)NULL
};


void Scn_get_ccnv(Scn_T *scn)
/* simulates a Scn_get */
{
  *scn = Scn_copy(Scn_ADT(&ccnvScanner));
}
