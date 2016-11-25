# [stypp.cmd] command description for stypp.c

Program stypp -- Pretty Printer

doc
  <p>'stypp' serves as a pretty printer for source files written in a styx-conform language.
  Beside that it can be used to port source files, provided that the abstract syntax of the 
  source and target language are equivalent. The conversion includes all comments. A user-defined
  token conversion handler can be applied.
  <p>The work on this program, especially on the pretty printer layout, ist still in progress.
  The current version doesn't support the embedded language facility.
cod

Arguments

  srclang  : name -- source language name
  dstlang  : name -- target language name
  filename : path -- path of source file to transform

Options

  #macro EXCLUDE_OPTION_BINMODE
  #include pgm_sopt.inc
  #include pgm_popt.inc
  ppfun    : string = ""    -- user-defined token conversion: Function@Library ( see [ptm_pp] )

  #include pgm_odoc.inc

Environment

  BINSTYX  : path = "PATH" 
              -- search environment for [srclang.pim], [srclang.lim], [dstlang.pim] and [dstlang.lim]
