## Process this file with automake to generate gen/Makefile.in

INCLUDES = -I$(top_srcdir)/modstd -I$(top_srcdir)/libutil -I$(top_srcdir)/libbase -I$(top_srcdir)/pgm -I$(top_srcdir)/modext -I$(top_srcdir)/inc

vpath %.h @top_srcdir@/modstd @top_srcdir@/libutil @top_srcdir@/libbase @top_srcdir@/pgm @top_srcdir@/modext @top_srcdir@/inc

noinst_LIBRARIES = libpgm.a
noinst_LTLIBRARIES = libxstyx.la

libxstyx_la_SOURCES = cmd_int.c hpat_int.c cmd_lim.c rexp_lim.c styx_lim.c cmd_pim.c hpat_lim.c hpat_pim.c styx_pim.c styx_int.c

libpgm_a_SOURCES = ctoh_cim.c ccnv_lim.c lim__cim.c styx_cim.c pim__cim.c styp_cim.c styd_cim.c ptm__cim.c

EXTRA_DIST = $(wildcard $(srcdir)/*.abs)
