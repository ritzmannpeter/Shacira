## Process this file with automake to generate Makefile.in

INCLUDES = -I$(top_srcdir)/modstd -I$(top_srcdir)/libutil -I$(top_srcdir)/libbase -I$(top_srcdir)/libxml -I$(top_srcdir)/pgm -I$(top_srcdir)/pgmxml -I$(top_srcdir)/modext -I$(top_srcdir)/inc -I$(top_srcdir)/incxml

htmldir = @htmldir@
sgmldir = @sgmldir@
sampledir = @sampledir@

lib_LTLIBRARIES = libdstyx.la libxstyx.la libdxml.la
bin_PROGRAMS = styx stydoc stypp ctoh lim_test pim_test ptm_img xml_test

libdstyx_la_LDFLAGS = -version-info 2:0:0
libxstyx_la_LDFLAGS = -version-info 2:0:0
libdxml_la_LDFLAGS = -version-info 1:0:0

libdstyx.la: libbase/libdstyx.la modstd/libdstyx.la
	$(LINK) -rpath $(libdir) $(libdstyx_la_LDFLAGS) \
	 $(wildcard libbase/*.lo) $(wildcard modstd/*.lo) $(LIBS)

libxstyx.la: gen/libxstyx.la libstyx/libxstyx.la libutil/libxstyx.la libdstyx.la
	$(LINK) -rpath $(libdir) $(libxstyx_la_LDFLAGS) \
	 $(wildcard libstyx/*.lo) $(wildcard libutil/*.lo) \
	 gen/cmd_int.lo gen/cmd_lim.lo gen/cmd_pim.lo \
	 gen/hpat_int.lo gen/hpat_lim.lo gen/hpat_pim.lo \
	 gen/styx_int.lo gen/styx_lim.lo gen/styx_pim.lo \
	 gen/rexp_lim.lo \
	 libdstyx.la $(LIBS)

libdxml.la: genxml/libdxml.la libxml/libdxml.la libxstyx.la
	$(LINK) -rpath $(libdir) $(libdxml_la_LDFLAGS) \
	 $(wildcard libxml/*.lo) \
	 $(wildcard genxml/*_[ilp]*.lo) \
	 libxstyx.la $(LIBS)

## Explicitly clear primaries, since automake defaults to
## xxx_SOURCES = xxx.c
libdstyx_la_SOURCES =
libxstyx_la_SOURCES =
libdxml_la_SOURCES  =
styx_SOURCES        =
stydoc_SOURCES      =
stypp_SOURCES       =
ctoh_SOURCES        =
lim_test_SOURCES    =
pim_test_SOURCES    =
ptm_img_SOURCES     =
xml_test_SOURCES     =
## Adding this forces automake to generate a working toplevel
## Makefile.in even in the absence of real sources.
noinst_LTLIBRARIES = libfoolam.la
libfoolam_la_SOURCES = foolam.c

styx$(EXEEXT): pgm/libpgm.a gen/libpgm.a libxstyx.la
	$(LINK) pgm/styx.o gen/styx_cim.o libxstyx.la $(LIBS)

stydoc$(EXEEXT): pgm/libpgm.a gen/libpgm.a libxstyx.la
	$(LINK) pgm/stydoc.o gen/styd_cim.o libxstyx.la $(LIBS)

stypp$(EXEEXT): pgm/libpgm.a gen/libpgm.a libxstyx.la
	$(LINK) pgm/stypp.o gen/styp_cim.o libxstyx.la $(LIBS)

ctoh$(EXEEXT): pgm/libpgm.a gen/libpgm.a libxstyx.la
	$(LINK) pgm/ctoh.o gen/ctoh_cim.o gen/ccnv_lim.o libxstyx.la $(LIBS)

lim_test$(EXEEXT): pgm/libpgm.a gen/libpgm.a libxstyx.la
	$(LINK) pgm/lim_test.o gen/lim__cim.o libxstyx.la $(LIBS)

pim_test$(EXEEXT): pgm/libpgm.a gen/libpgm.a libxstyx.la
	$(LINK) pgm/pim_test.o gen/pim__cim.o libxstyx.la $(LIBS)

ptm_img$(EXEEXT): pgm/libpgm.a gen/libpgm.a libxstyx.la
	$(LINK) pgm/ptm_img.o gen/ptm__cim.o libxstyx.la $(LIBS)

xml_test$(EXEEXT): pgmxml/libpgmxml.a genxml/libpgmxml.a libdxml.la libxstyx.la
	$(LINK) pgmxml/xml_test.o genxml/xml_test_cim.o libdxml.la libxstyx.la $(LIBS)

SUBDIRS = gen libbase libstyx libutil modext modstd pgm inc doc examples spe pat libxml incxml pgmxml genxml spexml
## mak prj release util

EXTRA_DIST = LICENSE bootstrap util windows libc++
