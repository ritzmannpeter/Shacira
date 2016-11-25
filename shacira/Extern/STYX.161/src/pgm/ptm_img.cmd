# [ptm_img.cmd] command description for ptm_img.c

Program ptm_img -- Term Put&Get

doc
  <p>'ptm_img' translates the given source file into a binary format and reverse. 
  In the reverse case it lists the derivation tree on stdout.
  <p>The source file must be conform with the language parameter. It uses the image files
  of the parser and scanner tables, [Language.lim] and [Language.pim].
  <p>In case you specify a start symbol the parsing process starts from this nonterminal.
  The symbol must be specified as valid start nonterminal in [Language.sty].
  If the option is omitted the parser takes the first start nonterminal.
cod

Arguments

  Language : name -- language name
  Img      : path -- path of the binary format

Options

  FileName : path   = ""  -- path of source file to parse
  #include pgm_sopt.inc
  #include pgm_popt.inc

  #include pgm_odoc.inc

Environment

  BINSTYX  : path = "PATH" -- search environment for [Language.pim] and [Language.lim]

