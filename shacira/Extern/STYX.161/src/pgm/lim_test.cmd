# [lim_test.cmd] command description for lim_test.c

Program lim_test -- Scanner test program

doc
  <p>'lim_test' scans the given source file and lists the tokens on stdout.
  The source file must be conform with the language parameter. It uses the image file
  of the scanner table [Language.lim].
  <p>The current version doesn't support the embedded language facility.
cod

Arguments

  #include pgm_arg.inc

Options

  #include pgm_sopt.inc

  tokens   : flag  = true  -- create list of all scanned tokens 
  symbols  : flag  = false -- create list of all symbols in the internal symbol table 

  #include pgm_odoc.inc

Environment

  BINSTYX  : path  = "PATH" -- search environment for [Language.lim] 
