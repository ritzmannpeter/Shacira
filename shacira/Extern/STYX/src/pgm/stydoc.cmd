# [stydoc.cmd] command description for stydoc.c

Program stydoc -- STYX Documentation Generator

doc
  <p>'stydoc' produces a HTML-like reference documentation for a STYX grammar [.sty].
  <p>Comments not starting with ';;' will also be included.
cod

Arguments

  InFile   : path -- path of the STYX grammar [.sty]
  Template : path -- path of the template file (eg. tstydoc_us.htm)

doc
  <p>The target file 'OutFile' should contain the language name so that 
     embedded languages can be referenced, too.
cod

Options

  OutFile  : path = ""        -- path of the target file (default: stdout)
  StyxPath : path = "."       -- path of STYX grammar include files
  RefAlias : string = "&amp;" -- alias for the first character of a pattern reference
  recursiv : flag = false     -- recursive pattern evaluation
  prodcom  : flag = false     -- print production comments
  keepNTs  : string = ""      -- NTs which shouldn't be expanded ( NT ; ... )
  noClass  : string = ""      -- split NT Classes ( NT ; ... )
  exProds  : string = ""      -- hide NT Productions ( NT . Prod ; ... )
  ignRRef  : string = ""      -- ignore recursive references ( NT ; ... )

Environment

  BINSTYX  : path   = "PATH"  -- search environment for the parse table image [.pim]
