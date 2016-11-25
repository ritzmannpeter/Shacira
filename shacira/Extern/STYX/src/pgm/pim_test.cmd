# [pim_test.cmd] command description for pim_test.c

Program pim_test -- Parser test program

doc
  <p>'pim_test' parses the given source file and lists the derivation tree on stdout.
  The source file must be conform with the language parameter. It uses the image files
  of the parser and scanner tables, [Language.lim] and [Language.pim].
  </p>
  <p>In case you specify a start symbol the parsing process starts from this nonterminal,
  provided it is defined in [Language.sty].
  By default the parser takes the first start nonterminal.
cod

Arguments

  #include pgm_arg.inc

Options

  #include pgm_sopt.inc
  #include pgm_popt.inc
  tree     : flag  = true  -- create a derivation tree 

  #include pgm_odoc.inc

Environment

  BINSTYX  : path  = "PATH" -- search environment for [Language.pim] and [Language.lim]
