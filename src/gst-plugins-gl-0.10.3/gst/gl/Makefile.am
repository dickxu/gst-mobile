
plugin_LTLIBRARIES = libgstopengl.la

AM_CFLAGS = $(GST_PLUGINS_BASE_CFLAGS) $(GST_BASE_CFLAGS) $(GST_CFLAGS)
AM_LIBS = $(GST_BASE_LIBS)

# full opengl required
if GL_IS_OPENGL
OPENGL_SOURCES =  \
	gstglfiltershader.c \
	gstglfiltershader.h \
	gstglfilterblur.c \
	gstglfilterblur.h \
	gstglfiltersobel.c \
	gstglfiltersobel.h \
	gstglfilterlaplacian.c \
	gstglfilterlaplacian.h \
	gstglfilterglass.c \
	gstglfilterglass.h \
	gstglfilterapp.c \
	gstglfilterapp.h \
	gstglfilterreflectedscreen.c \
	gstglfilterreflectedscreen.h \
	gstglcolorscale.c \
	gstglcolorscale.h \
	gstgldeinterlace.c \
	gstgldeinterlace.h \
	gltestsrc.c \
	gltestsrc.h \
	gstgltestsrc.c \
	gstgltestsrc.h \
	gstglmosaic.c \
	gstglmosaic.h \
	effects/gstgleffectscurves.h \
	effects/gstgleffectstretch.c \
	effects/gstgleffecttunnel.c \
	effects/gstgleffectfisheye.c \
	effects/gstgleffecttwirl.c \
	effects/gstgleffectbulge.c \
	effects/gstgleffectsquare.c \
	effects/gstgleffectlumatocurve.c \
	effects/gstgleffectlumatocurve.h \
	effects/gstgleffectrgbtocurve.c \
	effects/gstgleffectsin.c \
	effects/gstgleffectglow.c \
	effects/gstgleffectxray.c

if HAVE_PNG
OPENGL_SOURCES += \
	gstglbumper.c \
	gstglbumper.h \
	gstgldifferencematte.c \
	gstgldifferencematte.h
if HAVE_JPEG
OPENGL_SOURCES += \
	gstgloverlay.c \
	gstgloverlay.h
endif
endif
endif

libgstopengl_la_SOURCES = \
	gstopengl.c \
	gstglimagesink.c \
	gstglimagesink.h \
	gstglupload.c \
	gstglupload.h \
	gstgldownload.c \
	gstgldownload.h \
	gstglfiltercube.c \
	gstglfiltercube.h \
	gstgleffects.c \
	gstgleffects.h \
	effects/gstgleffectssources.c \
	effects/gstgleffectssources.h \
	effects/gstgleffectidentity.c \
	effects/gstgleffectmirror.c \
	effects/gstgleffectsqueeze.c \
	$(OPENGL_SOURCES)

# check order of CFLAGS and LIBS, shouldn't the order be the other way around
# (like in AM_CFLAGS)?
libgstopengl_la_CFLAGS = $(GST_CFLAGS) $(X_CFLAGS) $(GST_BASE_CFLAGS) \
	$(GST_PLUGINS_BASE_CFLAGS) $(GL_CFLAGS) $(LIBPNG_CFLAGS) \
	-I$(top_srcdir)/gst-libs \
	-I$(top_srcdir)/gst-libs/gst/gl \
	-I$(top_srcdir)/gst/gl/effects

libgstopengl_la_LIBADD = \
	$(top_builddir)/gst-libs/gst/gl/libgstgl-$(GST_MAJORMINOR).la \
	$(GST_BASE_LIBS) \
	$(GST_PLUGINS_BASE_LIBS) -lgstvideo-$(GST_MAJORMINOR) -lgstinterfaces-$(GST_MAJORMINOR) \
	$(GL_LIBS) \
	$(LIBPNG_LIBS) \
        $(JPEG_LIBS) \
	$(LIBM)

libgstopengl_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)

