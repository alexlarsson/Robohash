NULL =

INCLUDES =							\
	-I$(top_builddir)/src -I$(top_srcdir)/src		\
	$(WARN_CFLAGS)						\
	$(NULL)

SET1_PNGS := $(wildcard blue/*/*.png brown/*/*.png green/*/*.png grey/*/*.png orange/*/*.png pink/*/*.png purple/*/*.png red/*/*.png white/*/*.png yellow/*/*.png)
BGS_PNGS := $(wildcard bg1/*.png bg2/*.png)

robot_data.h: generate_data.py $(SET1_PNGS) $(BGS_PNGS)
	$(PYTHON) $(srcdir)/generate_data.py > robot_data.h

lib_LTLIBRARIES = librobohash.la

librobohash_ladir = $(includedir)/robohash

librobohash_la_HEADERS =						\
	robohash.h							\
	$(NULL)

librobohash_la_SOURCES =						\
	robohash.h							\
	robohash.c							\
	robot_bits.c							\
	robot_bits.h							\
	robot_data.h							\
	$(NULL)

librobohash_la_CFLAGS =						\
	$(ROBOHASH_CFLAGS)					\
	$(NULL)

librobohash_la_LIBADD =						\
	$(ROBOHASH_LIBS)					\
	$(NULL)

noinst_PROGRAMS = test-robohash

test_robohash_SOURCES =						\
	test-robohash.c						\
	$(NULL)

test_robohash_CFLAGS = \
	$(ROBOHASH_CFLAGS)					\
	$(NULL)

test_robohash_LDADD = \
	$(ROBOHASH_LIBS)					\
	librobohash.la						\
	$(NULL)

pkgconfig_in = librobohash.pc.in
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = $(pkgconfig_in:.in=)

vapidir = $(datadir)/vala/vapi
vapi_DATA = librobohash.vapi


EXTRA_DIST =							\
	generate_data.py					\
	$(pkgconfig_in)						\
	$(vapi_DATA)						\
	$(SET1_PNGS)						\
	$(BGS_PNGS)						\
	$(NULL)
