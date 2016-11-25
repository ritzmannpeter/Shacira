
-include environment.inc

all:
	$(make) -C AutoBuild all
	$(make) -C AutoConfig build

build:
	$(make) -C AutoConfig build

depend: 
	$(make) -C AutoConfig depend

clean:
	-$(make) -C AutoBuild clean
	-$(make) -C AutoConfig clean


