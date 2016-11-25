## Process this file with automake to generate spexml/Makefile.in

spedir = $(sampledir)/spe

edit = $(SED) -e 's,$$(datadir),$(datadir),'

spe_DATA = xml1.lex xml2.lex xml.sty dtd.sty xmllit.sty

install-data-hook:
	$(edit) xxml.in >xxml
	$(INSTALL_SCRIPT) xxml $(DESTDIR)$(spedir)/xxml 

clean-generic:
	rm -f xxml

EXTRA_DIST = $(spe_DATA)

