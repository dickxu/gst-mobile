plugin_LTLIBRARIES = libgstmpeg2dec.la

libgstmpeg2dec_la_SOURCES = gstmpeg2dec.c
libgstmpeg2dec_la_CFLAGS = $(GST_PLUGINS_BASE_CFLAGS) $(GST_CFLAGS) $(MPEG2DEC_CFLAGS)
libgstmpeg2dec_la_LIBADD = $(GST_PLUGINS_BASE_LIBS) $(MPEG2DEC_LIBS) $(GST_LIBS) \
				-lgstvideo-$(GST_MAJORMINOR)
libgstmpeg2dec_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstmpeg2dec_la_LIBTOOLFLAGS = --tag=disable-static

noinst_HEADERS = gstmpeg2dec.h
