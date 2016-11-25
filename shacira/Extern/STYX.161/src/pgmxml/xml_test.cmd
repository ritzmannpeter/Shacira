# [xml_test.cmd] command cription for xml_test.c


Program xml_test -- XML Parser test program

doc
  'xml_test' parses XML and DTD sources and lists the derivation trees on stdout.
cod

Arguments

Options

  file : string = ""           -- source file (default: stdin)
  cset : string = "ISO-8859-1" -- source file character set ( UTF-8, UCS4, ... )
  all  : flag   = false        -- parse references
  dtd  : flag   = false        -- 'file' contains DTD definitions

Environment

