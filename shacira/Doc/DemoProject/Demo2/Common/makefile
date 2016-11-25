
include $(shacira)/Targ/specs

all: $(BUILDCFG).depend $(BUILDCFG).build
	$(make) -f $(BUILDCFG).mk all

$(BUILDCFG).build: build.cfg
	abuild -cf $(shacira)/Targ/AutoConfig/configurations/$(BUILDCFG).cfg
	echo "done" >$(BUILDCFG).build
	
$(BUILDCFG).depend:
	abuild -df -cf $(shacira)/Targ/AutoConfig/configurations/$(BUILDCFG).cfg
	echo "done" >$(BUILDCFG).depend
	
clean:
	-$(make) -f $(BUILDCFG).mk cleanall
	-$(rm)  $(BUILDCFG).build
	-$(rm)  $(BUILDCFG).mk
	
cleanall:
	-$(make) -f $(BUILDCFG).mk cleanall
	-$(rm)  $(BUILDCFG).depend
	-$(rm)  $(BUILDCFG).build
	-$(rm)  $(BUILDCFG).mk
	




