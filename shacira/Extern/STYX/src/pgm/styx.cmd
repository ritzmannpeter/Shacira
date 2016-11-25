# [styx.cmd] command description for [styx.c]

Program styx -- A combined parser and scanner generator

doc
  <p>'styx' translates the token and syntax description for a language in [$SPESTYX/Language.sty] 
  into scanner and parser tables and a functional interface to the abstract derivation tree.
  </p>
  <p>The generated tables have to be applied to the actual scanner and parser function which are part of the 
  styx library. The result of the parser function will be a derivation tree which can be accessed through 
  the above mentioned interface.
cod

Arguments

  Language  : name        -- language name

Options

  diagnose  : flag = false -- additional diagnose and information
  verbose   : flag = false -- progress information
  conflicts : flag = true  -- prevent parse table generation in case of conflicts

  makeIMG   : flag = false -- create binary table images
  makeINT   : flag = false -- create interface c source
  makeANT   : flag = false -- create abstract interface c source
  makeC     : flag = false -- create table c sources
  export    : flag = false -- export table definitions
  exportTMPL: string = ""  -- export template file
  shortform : flag = false -- use short form of language name

doc
  <p>Dependant on the given options different source and image files will be created: 

  <ol>
  <li><b>-makeIMG</b><br>
      For an interpretative execution you may only need the binary
      [$BINSTYX/Language.pim] and [$BINSTYX/Language.lim] image files which 
      contain the parser and scanner tables.

  <li><b>-makeINT</b><br>
      To process the derivation tree within your c/c++ program it's useful to 
      create the interface c source [$GENSTYX/Language(1,4)_int.c].

  <li><b>-makeANT</b><br>
      To process a derivation tree variant optimized wrt. memory usage it's useful 
      to create the special interface c source [$GENSTYX/Language(1,4)_ant.c].

  <li><b>-makeC</b><br>
      Instead of using the table image files you can include the c sources
      [$GENSTYX/Language(1,4)_pim.c] and [$GENSTYX/Language(1,4)_lim.c]. 
      This option implies '-makeINT'.

  <li><b>-export</b><br>
      In order to use the C++ scanner and parser classes you may only need the 
      file [$BINSTYX/Language.ltbl] which contains the scanner table definition and.
      [$BINSTYX/Language.ptbl] which contains the parse table definition.

  <li><b>-exportTMPL=template file</b><br>
      The given template file will be used for the export of the scanner and parse table
      as constant string definitions in the format of the preferred programming language. 
      The placeholder @TABLE@ will be replaced by the concatenation of table type and 
      language ID.
      The line containing the placeholder @LINE@ will be replicated for each 
      line of the current definition. Before substituting a quoted placeholder @LINE@ 
      the actual definition line will be converted applying C-style quoting rules.
  </ol>
cod

Environment

  BINSTYX : path = "."     -- [.pim], [.lim] and [.ltbl] target directory
  GENSTYX : path = "."     -- [.c] target directory
  SPESTYX : path = "."     -- [.sty] source directory
