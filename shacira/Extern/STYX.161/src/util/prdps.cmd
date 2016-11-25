# [prdps.cmd] command description for [prdps.c]

Program prdps -- Dependency analysis

doc
  <P>'prdps' evaluates a project definition [project.nmk] based on the 
  STYX grammar [cprj.sty]. 
  <P>It keeps track to the specified translation rules, targets, sources 
  and their dependencies.
  <br>
  <P>Its main task is to produce a control file [project.nmk] for the 
  nanomake-facility 'prnmk'.

cod

Arguments

  project  : string         -- project definition file [project.prj]
  vargs    : string         -- project definition parameter

doc
cod

Options

  diagnose : string = ""      -- path of diagnose information file
  changes  : flag   = true    -- show files changed
  lexsort  : flag   = false   -- order rules by name ( default: by position )
  strict   : flag   = false   -- errors on inference failures ( else warnings )
  multisrc : flag   = false   -- allow identical sources in multiple targets
  warnings : flag   = true    -- print warnings
  makeNANO : flag   = true    -- produce the control file [project.nmk]
  makeLIST : flag   = true    -- produce a project list [project.lst]
  replace  : string = ""      -- path output substitution: <old>=<new> ; ...
  pathsep  : string = ";"     -- possible path separator characters 
  premac   : string = ""      -- standard preprocessing:  pre-defined macro , ...

doc
  <p>The option 'makeLIST' isn't implemented yet.
  <p>The option 'replace' can be used to keep the pathes in the control file
  variable. If the old-pattern starts with the character '^' the following
  sequence is interpreted as start sequence condition.
  <p>The path separators will be evaluated in the given order. 
  ( option 'pathsep' )

cod

Environment

  PRDPS : path   -- pathes for the project definition files

doc
cod

