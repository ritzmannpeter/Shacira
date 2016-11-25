## Process this file with automake to generate libxml/Makefile.in

INCLUDES = -I$(top_srcdir)/modstd -I$(top_srcdir)/libutil -I$(top_srcdir)/libbase -I$(top_srcdir)/genxml -I$(top_srcdir)/pgmxml -I$(top_srcdir)/modext -I$(top_srcdir)/inc -I$(top_srcdir)/incxml

vpath %.h @top_srcdir@/modstd @top_srcdir@/libutil @top_srcdir@/libbase @top_srcdir@/genxml @top_srcdir@/pgmxml @top_srcdir@/modext @top_srcdir@/inc @top_srcdir@/incxml

noinst_LTLIBRARIES = libdxml.la

libdxml_la_SOURCES = xml_base.c

include_HEADERS = xml_dfn.h
