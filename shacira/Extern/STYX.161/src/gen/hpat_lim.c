/* [hpat_lim.c] Scanner table for 'hpat'  */

#include "scn_io.h"

#include "scn_imp.h"

/* scanner group 'hpat' */

static long hpatStaEdg[19] =
/* first edge per state */
{
          0,         5,        14,        21,        32,        37,
         42,        43,        48,        53,        58,        63,
         68,        75,        78,        93,        94,       111,
        112
};

static short hpatStaFin[18] =
/* finite token per state */
{
    0,   0,   0,   0,   0,   0,   3,   0,   0,   0,
    0,   0,   0,   0,   0,   2,   0,   1
};

static wc_char hpatEdgeC[112] =
/* lowest character per edge */
{ /*State*/
  /*   0 */         61,         60,         39,         38,          0,
  /*   1 */        123,         97,         96,         95,         91,         65,
                    58,         48,          0,
  /*   2 */        105,        104,         73,         72,         48,         47,
                     0,
  /*   3 */        123,         97,         96,         95,         91,         65,
                    60,         59,         58,         48,          0,
  /*   4 */        105,        104,         73,         72,          0,
  /*   5 */        113,        112,         81,         80,          0,
  /*   6 */          0,
  /*   7 */        113,        112,         81,         80,          0,
  /*   8 */         98,         97,         66,         65,          0,
  /*   9 */         98,         97,         66,         65,          0,
  /*  10 */        117,        116,         85,         84,          0,
  /*  11 */        117,        116,         85,         84,          0,
  /*  12 */         33,         32,         14,         13,         11,          9,
                     0,
  /*  13 */         63,         62,          0,
  /*  14 */        123,         97,         96,         95,         91,         65,
                    58,         48,         33,         32,         14,         13,
                    11,          9,          0,
  /*  15 */          0,
  /*  16 */        123,         97,         96,         95,         91,         65,
                    63,         62,         58,         48,         33,         32,
                    14,         13,         11,          9,          0,
  /*  17 */          0
};

static long hpatEdgeS[112] =
/* follow (state+1) per edge */
{ /*State*/
  /*   0 */         0,         3,         0,         2,         0,
  /*   1 */         0,         4,         0,         4,         0,         4,
                    0,         4,         0,
  /*   2 */         0,         6,         0,         6,         0,         5,
                    0,
  /*   3 */         0,         4,         0,         4,         0,         4,
                    0,         7,         0,         4,         0,
  /*   4 */         0,         8,         0,         8,         0,
  /*   5 */         0,         9,         0,         9,         0,
  /*   6 */         0,
  /*   7 */         0,        10,         0,        10,         0,
  /*   8 */         0,        11,         0,        11,         0,
  /*   9 */         0,        12,         0,        12,         0,
  /*  10 */         0,        13,         0,        13,         0,
  /*  11 */         0,        14,         0,        14,         0,
  /*  12 */         0,        15,         0,        15,         0,        15,
                    0,
  /*  13 */         0,        16,         0,
  /*  14 */         0,        17,         0,        17,         0,        17,
                    0,        17,         0,        15,         0,        15,
                    0,        15,         0,
  /*  15 */         0,
  /*  16 */         0,        17,         0,        17,         0,        17,
                    0,        18,         0,        17,         0,        17,
                    0,        17,         0,        17,         0,
  /*  17 */         0
};

static string hpatTokens[4] =
/* token -> string */
{
  "[other]",
  "PatBgn",
  "PatEnd",
  "PatRef"
};

static byte hpatFlags[4] =
/* token -> newid */
{
  0x00, 0x00, 0x00, 0x00
};

static ConcreteImp(scn_t) hpatScanner =
/* the scanner structure */
{
  "hpat", /* Name    */
  18,     /* States  */
   4,     /* Tokens  */
  hpatStaEdg,
  hpatStaFin,
  hpatEdgeC,
  hpatEdgeS,
  hpatTokens,
  hpatFlags,
   0,     /* Groups  */
  (scn_t*)NULL,
  (short*)NULL,
  0, /* Dyck */
  (short*)NULL,
  (scn_t*)NULL
};


void Scn_get_hpat(Scn_T *scn)
/* simulates a Scn_get */
{
  *scn = Scn_copy(Scn_ADT(&hpatScanner));
}
