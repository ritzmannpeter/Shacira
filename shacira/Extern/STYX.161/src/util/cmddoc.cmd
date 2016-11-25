# [cmddoc.cmd] command description for [cmddoc.c]

Program cmddoc -- CMD Documentation Generator

doc
  <p>'cmddoc' produces a HTM-like documentation for a command description file [.cmd].
cod

Arguments

  InFile   : path -- path of the command description file
  OutFile  : path -- path of the target file

Options

  Template : path = "/p/styx/pat/pcmddoc_us.htm" -- path list with template files
  RefAlias : string = "&amp;" -- alias for the first character of a pattern reference
  recursiv : flag = false     -- recursive pattern evaluation

Environment

  PATH     : path -- search path for binary images [.lim,.pim]
