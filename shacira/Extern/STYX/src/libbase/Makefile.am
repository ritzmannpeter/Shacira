## Process this file with automake to generate libbase/Makefile.in

INCLUDES = -I$(top_srcdir)/modstd -I$(top_srcdir)/libutil -I$(top_srcdir)/libbase -I$(top_srcdir)/pgm -I$(top_srcdir)/modext -I$(top_srcdir)/inc

vpath %.h @top_srcdir@/modstd @top_srcdir@/libutil @top_srcdir@/libbase @top_srcdir@/pgm @top_srcdir@/modext @top_srcdir@/inc

noinst_LTLIBRARIES = libdstyx.la

libdstyx_la_SOURCES = symbols.c gstream.c scn_pre.c ctx_app.c prim.c prs_abs.c glo_tab.c binset.c binimg.c cfg_dfn.c scn_io.c prs_io.c cfg_abs.c ptm_pp.c line_scn.c ptm.c otab.c hset.c literal.c scn_abs.c hmap.c sysbase0.c sysbase1.c pathes.c ptm_gen.c scn_base.c prs.c sink.c list.c

include_HEADERS = standard.h ctx_imp.h prs_imp.h styconf0.h syscbhdl.h ctx_dfn.h prs_dfn.h scn_imp.h
