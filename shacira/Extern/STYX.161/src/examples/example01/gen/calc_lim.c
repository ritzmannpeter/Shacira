/* [calc_lim.c] Scanner table for 'calc'  */

#include "scn_io.h"

#include "scn_imp.h"

/* scanner group 'calc' */

static long calcStaEdg[8] =
/* first edge per state */
{
          0,        16,        17,        18,        21,        24,
         27,        28
};

static short calcStaFin[7] =
/* finite token per state */
{
    0,   1,   2,   3,   0,   0,   4
};

static wc_char calcEdgeC[28] =
/* lowest character per edge */
{ /*State*/
  /*   0 */        102,        101,         58,         48,         47,         46,
                    45,         44,         40,         33,         32,         14,
                    13,         11,         10,          0,
  /*   1 */          0,
  /*   2 */          0,
  /*   3 */         58,         48,          0,
  /*   4 */        111,        110,          0,
  /*   5 */        101,        100,          0,
  /*   6 */          0
};

static long calcEdgeS[28] =
/* follow (state+1) per edge */
{ /*State*/
  /*   0 */         0,         5,         0,         4,         3,         0,
                    3,         0,         3,         0,         2,         0,
                    2,         0,         2,         0,
  /*   1 */         0,
  /*   2 */         0,
  /*   3 */         0,         4,         0,
  /*   4 */         0,         6,         0,
  /*   5 */         0,         7,         0,
  /*   6 */         0
};

static string calcTokens[5] =
/* token -> string */
{
  "[other]",
  "Ign",
  "Tok",
  "Int",
  "Wrd"
};

static byte calcFlags[5] =
/* token -> newid */
{
  0x00, 0x01, 0x00, 0x00, 0x00
};

static ConcreteImp(scn_t) calcScanner =
/* the scanner structure */
{
  "calc", /* Name    */
   7,     /* States  */
   5,     /* Tokens  */
  calcStaEdg,
  calcStaFin,
  calcEdgeC,
  calcEdgeS,
  calcTokens,
  calcFlags,
   0,     /* Groups  */
  (scn_t*)NULL,
  (short*)NULL,
  0, /* Dyck */
  (short*)NULL,
  (scn_t*)NULL
};


void Scn_get_calc(Scn_T *scn)
/* simulates a Scn_get */
{
  *scn = Scn_copy(Scn_ADT(&calcScanner));
}
