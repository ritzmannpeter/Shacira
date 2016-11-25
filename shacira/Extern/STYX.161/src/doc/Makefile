# Makefile.in generated automatically by automake 1.4-p5 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999, 2001 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.


SHELL = /bin/sh

srcdir = .
top_srcdir = ..

prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/styx
pkglibdir = $(libdir)/styx
pkgincludedir = $(includedir)/styx

top_builddir = ..

ACLOCAL = aclocal
AUTOCONF = autoconf
AUTOMAKE = automake
AUTOHEADER = autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL} $(AM_INSTALL_PROGRAM_FLAGS)
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}
transform = s,x,x,

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
host_alias = 
host_triplet = i686-pc-cygwin
AR = ar
AS = @AS@
AWK = gawk
CC = gcc
CPP = gcc -E
CXX = g++
CXXCPP = g++ -E
DLLTOOL = @DLLTOOL@
ECHO = echo
EGREP = grep -E
EXEEXT = .exe
F77 = 
GCJ = @GCJ@
GCJFLAGS = @GCJFLAGS@
HAVE_LIB = @HAVE_LIB@
LIB = @LIB@
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LN_S = ln -s
LTLIB = @LTLIB@
MAKEINFO = makeinfo
OBJDUMP = @OBJDUMP@
OBJEXT = o
PACKAGE = styx
RANLIB = ranlib
RC = @RC@
SED = /usr/bin/sed
STRIP = strip
VERSION = 1.6.1
htmldir = $(datadir)/doc
sampledir = $(datadir)/examples
sgmldir = $(datadir)/doc

sgml_DATA = pl0.abs.sgml pl0.c.sgml pl0.sty.sgml styx.sgml testpl0.pl.sgml 

html_DATA = styx-1.html styx-10.html styx-11.html styx-12.html styx-2.html styx-3.html styx-4.html styx-5.html styx-6.html styx-7.html styx-8.html styx-9.html styx.html bin__cim.htm binimg.htm binset.htm bnf.htm ccnv_lim.htm cdps_lim.htm cfg_abs.htm cfg_dfn.htm charlib.htm cmd_ptm_img.htm cmd__cim.htm cmd_ant.htm cmd_ctoh.htm cmd_int.htm cmd_lim.htm cmd_lim_test.htm cmd_pim.htm cmd_pim_test.htm cmd_stydoc.htm cmd_stypp.htm cmd_styx.htm cmda_cim.htm cmdd_cim.htm cmd_xml_test.htm xml_dfn.htm xml_base.htm xml_int.htm xml_pim.htm xml_lim.htm xml_cfg.htm dtd_cfg.htm dtd_int.htm dtd_pim.htm dtd_lim.htm xmllit_lim.htm  cmdlib.htm com_cim.htm com_get.htm cprj_ant.htm cprj_int.htm cprj_lim.htm cprj_pim.htm ctoh_cim.htm ctx.htm ctx_app.htm ctx_dfn.htm ctx_imp.htm date.htm dict.htm dicts.htm dps_cim.htm esty_ant.htm esty_int.htm esty_lim.htm esty_pim.htm estyx_ant.htm estyx_int.htm genm_cim.htm glo_tab.htm gls.htm gls_abs.htm gstream.htm hmap.htm hpat.htm hpat_ant.htm hpat_int.htm hpat_lim.htm hpat_pim.htm hset.htm integer.htm lim__cim.htm line_scn.htm list.htm literal.htm mem_base.htm meta_ant.htm meta_cim.htm meta_exp.htm meta_int.htm meta_lim.htm meta_pim.htm meta_prs.htm nmk_cim.htm olist.htm otab.htm pathes.htm pgm_base.htm pim__cim.htm prdp_cim.htm pre.htm prim.htm prjfun.htm prs.htm prs_abs.htm prs_dfn.htm prs_gen.htm prs_imp.htm prs_io.htm ptm.htm ptm__cim.htm ptm_gen.htm ptm_pp.htm rational.htm refo_cim.htm reg_exp.htm rexp_lim.htm scn_abs.htm scn_base.htm scn_gen.htm scn_imp.htm scn_io.htm scn_pre.htm shmain.htm sink.htm standard.htm stdosx.htm styconf0.htm styd_cim.htm styp_cim.htm styx_ant.htm styx_cfg.htm styx_cim.htm styx_gen.htm styx_hdl.htm styx_int.htm styx_lim.htm styx_pim.htm symbols.htm sysbase0.htm sysbase1.htm syscbhdl.htm term.htm xmem_imp.htm xstdosx.htm

EXTRA_DIST = $(sgml_DATA) $(html_DATA)
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = ../config.h
CONFIG_CLEAN_FILES = 
DATA =  $(html_DATA) $(sgml_DATA)

DIST_COMMON =  Makefile.am Makefile.in


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = tar
GZIP_ENV = --best
all: all-redirect
.SUFFIXES:
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --foreign --include-deps doc/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status


install-htmlDATA: $(html_DATA)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(htmldir)
	@list='$(html_DATA)'; for p in $$list; do \
	  if test -f $(srcdir)/$$p; then \
	    echo " $(INSTALL_DATA) $(srcdir)/$$p $(DESTDIR)$(htmldir)/$$p"; \
	    $(INSTALL_DATA) $(srcdir)/$$p $(DESTDIR)$(htmldir)/$$p; \
	  else if test -f $$p; then \
	    echo " $(INSTALL_DATA) $$p $(DESTDIR)$(htmldir)/$$p"; \
	    $(INSTALL_DATA) $$p $(DESTDIR)$(htmldir)/$$p; \
	  fi; fi; \
	done

uninstall-htmlDATA:
	@$(NORMAL_UNINSTALL)
	list='$(html_DATA)'; for p in $$list; do \
	  rm -f $(DESTDIR)$(htmldir)/$$p; \
	done

install-sgmlDATA: $(sgml_DATA)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(sgmldir)
	@list='$(sgml_DATA)'; for p in $$list; do \
	  if test -f $(srcdir)/$$p; then \
	    echo " $(INSTALL_DATA) $(srcdir)/$$p $(DESTDIR)$(sgmldir)/$$p"; \
	    $(INSTALL_DATA) $(srcdir)/$$p $(DESTDIR)$(sgmldir)/$$p; \
	  else if test -f $$p; then \
	    echo " $(INSTALL_DATA) $$p $(DESTDIR)$(sgmldir)/$$p"; \
	    $(INSTALL_DATA) $$p $(DESTDIR)$(sgmldir)/$$p; \
	  fi; fi; \
	done

uninstall-sgmlDATA:
	@$(NORMAL_UNINSTALL)
	list='$(sgml_DATA)'; for p in $$list; do \
	  rm -f $(DESTDIR)$(sgmldir)/$$p; \
	done
tags: TAGS
TAGS:


distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)

subdir = doc

distdir: $(DISTFILES)
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    cp -pr $$d/$$file $(distdir)/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	    || cp -p $$d/$$file $(distdir)/$$file || :; \
	  fi; \
	done
info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am:
install-exec: install-exec-am

install-data-am: install-htmlDATA install-sgmlDATA
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am: uninstall-htmlDATA uninstall-sgmlDATA
uninstall: uninstall-am
all-am: Makefile $(DATA)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:
	$(mkinstalldirs)  $(DESTDIR)$(htmldir) $(DESTDIR)$(sgmldir)


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
mostlyclean-am:  mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-generic mostlyclean-am

clean: clean-am

distclean-am:  distclean-generic clean-am
	-rm -f libtool

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-generic distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: uninstall-htmlDATA install-htmlDATA uninstall-sgmlDATA \
install-sgmlDATA tags distdir info-am info dvi-am dvi check check-am \
installcheck-am installcheck install-exec-am install-exec \
install-data-am install-data install-am install uninstall-am uninstall \
all-redirect all-am all installdirs mostlyclean-generic \
distclean-generic clean-generic maintainer-clean-generic clean \
mostlyclean distclean maintainer-clean


# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
