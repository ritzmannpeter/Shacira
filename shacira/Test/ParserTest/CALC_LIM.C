/* [calc_lim.c] Scanner table for 'calc'  */

#include "scn_io.h"

#include "scn_imp.h"

static short StaEdg[8] =
/* first edge per state */
{
    0,  16,  17,  18,  21,  24,  27,  28
};

static short StaFin[7] =
/* finite token per state */
{
    0,   1,   2,   3,   0,   0,   4
};

static wc_char EdgeC[28] =
/* lowest character per edge */
{ /*State*/
  /*   0 */        102,        101,         58,         48,         47,         46,         45,         44,
                    40,         33,         32,         14,         13,         11,         10,          0,
  /*   1 */          0,
  /*   2 */          0,
  /*   3 */         58,         48,          0,
  /*   4 */        111,        110,          0,
  /*   5 */        101,        100,          0,
  /*   6 */          0
};

static short EdgeS[28] =
/* follow (state+1) per edge */
{ /*State*/
  /*   0 */   0,   5,   0,   4,   3,   0,   3,   0,   3,   0,
              2,   0,   2,   0,   2,   0,
  /*   1 */   0,
  /*   2 */   0,
  /*   3 */   0,   4,   0,
  /*   4 */   0,   6,   0,
  /*   5 */   0,   7,   0,
  /*   6 */   0
};

static string Tokens[5] =
/* token -> string */
{
  "[other]",
  "Ign",
  "Tok",
  "Int",
  "Wrd"
};

static byte Flags[5] =
/* token -> newid */
{
  0x00, 0x01, 0x00, 0x00, 0x00
};

static ConcreteImp(scn_t) Scanner =
/* the scanner structure */
{
  "calc", /* Name    */
   7,     /* States  */
   5,     /* Tokens  */
  StaEdg,
  StaFin,
  EdgeC,
  EdgeS,
  Tokens,
  Flags,
};

void Scn_get_calc(Scn_T *scn)
/* simulates a Scn_get */
{
  *scn = Scn_copy(Scn_ADT(&Scanner));
};
