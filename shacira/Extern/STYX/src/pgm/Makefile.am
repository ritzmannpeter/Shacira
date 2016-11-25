## Process this file with automake to create pgm/Makefile.in

vpath %.h $(top_srcdir)/modstd $(top_srcdir)/libutil $(top_srcdir)/libbase $(top_srcdir)/pgm $(top_srcdir)/modext $(top_srcdir)/inc

INCLUDES = -I$(top_srcdir)/modstd -I$(top_srcdir)/libutil -I$(top_srcdir)/libbase -I$(top_srcdir)/pgm -I$(top_srcdir)/modext -I$(top_srcdir)/inc

include_HEADERS = pgm_popt.h pgm_sopt.h 
noinst_LIBRARIES = libpgm.a
libpgm_a_SOURCES = ctoh.c lim_test.c styx.c pim_test.c stypp.c stydoc.c ptm_img.c lim2dot.c pim2dot.c

EXTRA_DIST = $(wildcard $(srcdir)/*.cmd) $(wildcard $(srcdir)/*.inc)
