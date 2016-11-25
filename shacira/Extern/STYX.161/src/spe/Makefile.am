## Process this file with automake to generate spe/Makefile.in

spedir = $(sampledir)/spe

edit = $(SED) -e 's,$$(datadir),$(datadir),'

spe_DATA = ccnv.sty cdps.sty cmd.sty cprj.sty estyx.sty hpat.sty meta.sty rexp.sty styx.sty 

install-data-hook:
	$(edit) xsty.in >xsty
	$(INSTALL_SCRIPT) xsty $(DESTDIR)$(spedir)/xsty 

clean-generic:
	rm -f xsty

EXTRA_DIST = $(spe_DATA)

