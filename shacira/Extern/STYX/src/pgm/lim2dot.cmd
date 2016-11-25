# [lim2dot.cmd] command description for lim2dot.c

Program lim2dot -- Scanner table visualisation

doc
  <p>'lim2dot' converts a styx scanner table [Language.lim] into the graph file language 'dot'.
  <p>The current version doesn't support the embedded language facility.
cod

Arguments

  Img      : path -- path of the scanner table image [Language.lim]

Options

  OutFile  : path = ""    -- path of the target file (default: stdout)
  Template : path = ""    -- path of the template file 

doc
  <p>The template file can be used to specify default graph, node or edge attributes.
cod

Environment

