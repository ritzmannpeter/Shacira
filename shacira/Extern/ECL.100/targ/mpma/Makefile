#
# root makefile controling build of the ECL library
#

.PHONY:  ECL

all: ECL

ECL:
	$(MAKE) -C mods/lib_base
	$(MAKE) -C mods/lib_store
	$(MAKE) -C mods/lib_tom
	$(MAKE) -C mods/lib_dbi
