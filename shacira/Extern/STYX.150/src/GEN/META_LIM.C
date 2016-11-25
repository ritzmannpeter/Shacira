/* [meta_lim.c] Scanner table for 'meta'  */

#include "scn_io.h"

#include "scn_imp.h"

static short StaEdg[10] =
/* first edge per state */
{
    0,  21,  22,  23,  26,  28,  29,  30,  35,  46
};

static short StaFin[9] =
/* finite token per state */
{
    0,   2,   3,   0,   4,   1,   6,   7,   5
};

static wc_char EdgeC[46] =
/* lowest character per edge */
{ /*State*/
  /*   0 */        123,         97,         96,         95,         91,         65,         60,         59,
                    58,         42,         40,         33,         32,         27,         26,         14,
                    13,         12,         11,         10,          0,
  /*   1 */          0,
  /*   2 */          0,
  /*   3 */         11,         10,          0,
  /*   4 */        256,          0,
  /*   5 */          0,
  /*   6 */          0,
  /*   7 */        255,        128,        127,         32,          0,
  /*   8 */        123,         97,         96,         95,         91,         65,         58,         48,
                    47,         46,          0
};

static short EdgeS[46] =
/* follow (state+1) per edge */
{ /*State*/
  /*   0 */   0,   9,   0,   9,   0,   9,   0,   8,   7,   0,
              7,   0,   6,   0,   5,   0,   4,   3,   0,   2,
              0,
  /*   1 */   0,
  /*   2 */   0,
  /*   3 */   0,   2,   0,
  /*   4 */   0,   5,
  /*   5 */   0,
  /*   6 */   0,
  /*   7 */   0,   8,   0,   8,   0,
  /*   8 */   0,   9,   0,   9,   0,   9,   0,   9,   0,   9,
              0
};

static string Tokens[8] =
/* token -> string */
{
  "[other]",
  "Space",
  "Line",
  "Page",
  "Etx",
  "Ide",
  "Opr",
  "Comment"
};

static byte Flags[8] =
/* token -> newid */
{
  0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00
};

static ConcreteImp(scn_t) Scanner =
/* the scanner structure */
{
  "meta", /* Name    */
   9,     /* States  */
   8,     /* Tokens  */
  StaEdg,
  StaFin,
  EdgeC,
  EdgeS,
  Tokens,
  Flags,
};

void Scn_get_meta(Scn_T *scn)
/* simulates a Scn_get */
{
  *scn = Scn_copy(Scn_ADT(&Scanner));
}
