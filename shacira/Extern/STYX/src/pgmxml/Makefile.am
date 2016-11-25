## Process this file with automake to create pgmxml/Makefile.in

vpath %.h $(top_srcdir)/modstd $(top_srcdir)/libutil $(top_srcdir)/libbase $(top_srcdir)/libxml $(top_srcdir)/pgmxml $(top_srcdir)/modext $(top_srcdir)/inc $(top_srcdir)/incxml

INCLUDES = -I$(top_srcdir)/modstd -I$(top_srcdir)/libutil -I$(top_srcdir)/libbase -I$(top_srcdir)/libxml -I$(top_srcdir)/pgmxml -I$(top_srcdir)/modext -I$(top_srcdir)/inc -I$(top_srcdir)/incxml

noinst_LIBRARIES = libpgmxml.a
libpgmxml_a_SOURCES = xml_test.c

EXTRA_DIST = $(wildcard $(srcdir)/*.cmd) $(srcdir)/xml_io.c
