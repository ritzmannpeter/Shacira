# [pim2dot.cmd] command description for pim2dot.c

Program pim2dot -- Parse table visualisation

doc
  <p>'pim2dot' converts a styx parse table [Language.pim] into the graph file language 'dot'.
  <p>The current version doesn't support the embedded language facility.
cod

Arguments

  Img      : path -- path of the parse table image [Language.pim]

Options

  DiaType  : string = "T" -- diagram type T=parse table (default), R=nonterminal relation, A=class relation
  OutFile  : path   = ""  -- path of the target file (default: stdout)
  Template : path   = ""  -- path of the template file 

doc
  <p>The template file can be used to specify default graph, node or edge attributes.
cod

Environment

