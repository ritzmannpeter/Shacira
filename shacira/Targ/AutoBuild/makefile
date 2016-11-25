
-include $(shacira)/Targ/environment.inc

all:
	$(make) -f abuild.$(ctools) all
	$(make) -C wrappers -f styxw.$(ctools) all
	$(make) -C wrappers -f pp.$(ctools) all

clean:
	-$(make) -f abuild.$(ctools) clean
	-$(make) -C wrappers -f styxw.$(ctools) clean
	-$(make) -C wrappers -f pp.$(ctools) clean
