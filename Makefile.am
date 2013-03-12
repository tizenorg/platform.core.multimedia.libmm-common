lib_LTLIBRARIES = libmmfcommon.la

includelibmmfcommondir = $(includedir)/mmf
includelibmmfcommon_HEADERS = include/mm_attrs.h \
			      include/mm_error.h \
			      include/mm_message.h \
			      include/mm_types.h \
		 	      include/mm_debug.h \
		 	      include/mm.h \
			      include/mm_attrs_private.h 
			      
# PG included
includelibmmfcommon_HEADERS += include/SLP_MultimediaFW_PG.h


libmmfcommon_la_SOURCES = mm_attrs.c \
			  mm_attrs_private.c \
			  mm_list_private.c

libmmfcommon_la_CFLAGS = -I$(srcdir)/include \
			 $(GLIB_CFLAGS)

libmmfcommon_la_LIBADD = -lpthread \
			 $(GLIB_LIBS)

libmmfcommon_la_CFLAGS += $(MMLOG_CFLAGS) -DMMF_LOG_OWNER=0x200 -DMMF_DEBUG_PREFIX=\"MMF-COMMON\"
libmmfcommon_la_LIBADD += $(MMLOG_LIBS)

installspecdir = $(includedir)/mmf

pcfiles = mm-common.pc
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = $(pcfiles)
EXTRA_DIST = $(pcfiles)
