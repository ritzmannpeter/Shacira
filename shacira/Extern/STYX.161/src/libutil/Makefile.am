## Process this file with automake to generate libutil/Makefile.in

INCLUDES = -I$(top_srcdir)/modstd -I$(top_srcdir)/libutil -I$(top_srcdir)/libbase -I$(top_srcdir)/pgm -I$(top_srcdir)/modext -I$(top_srcdir)/inc

vpath %.h @top_srcdir@/modstd @top_srcdir@/libutil @top_srcdir@/libbase @top_srcdir@/pgm @top_srcdir@/modext @top_srcdir@/inc

noinst_LTLIBRARIES = libxstyx.la

libxstyx_la_SOURCES = ctx.c charlib.c dict.c olist.c dicts.c com_get.c hpat.c pgm_base.c

