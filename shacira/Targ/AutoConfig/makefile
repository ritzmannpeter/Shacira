
-include ../environment.inc

all: configure build

depend: 
	abuild -df -bf all.cfg

configure: 
	abuild -bf all.cfg

build:
	$(make) -C shexplorer -f $(BUILDCFG).mk all
	$(make) -C icons -f $(BUILDCFG).mk all
	$(make) -C scons -f $(BUILDCFG).mk all
	$(make) -C mdlc -f $(BUILDCFG).mk all
	$(make) -C test/ttest -f $(BUILDCFG).mk all

clean:
	-$(make) -C shexplorer -f $(BUILDCFG).mk cleanall
	-$(make) -C icons -f $(BUILDCFG).mk cleanall
	-$(make) -C scons -f $(BUILDCFG).mk cleanall
	-$(make) -C mdlc -f $(BUILDCFG).mk cleanall
	-$(make) -C test/ttest -f $(BUILDCFG).mk cleanall



