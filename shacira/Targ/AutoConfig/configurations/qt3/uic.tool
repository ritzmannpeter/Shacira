
.name uic
.description Qt User interface Compiler
.command_line uic $< -o$(*D)/$(*F).h
.command_line uic $< -o$(*D)/$(*F).cpp -i $(*D)/$(*F).h
.target %s.h:moc
.target %s.cpp


