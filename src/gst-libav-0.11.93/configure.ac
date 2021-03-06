AC_PREREQ(2.62)

dnl initialize autoconf
dnl when going to/from release please set the nano (fourth number) right !
dnl releases only do Wall, cvs and prerelease does Werror too
AC_INIT(GStreamer libav, 0.11.93,
    http://bugzilla.gnome.org/enter_bug.cgi?product=GStreamer,
    gst-libav)

AG_GST_INIT

dnl initialize automake
AM_INIT_AUTOMAKE([-Wno-portability 1.11 no-dist-gzip dist-xz tar-ustar])

dnl define PACKAGE_VERSION_* variables
AS_VERSION

dnl check if this is a release version
AS_NANO(GST_GIT="no", GST_GIT="yes")

dnl can autoconf find the source ?
AC_CONFIG_SRCDIR([ext/ffmpeg/gstffmpeg.c])

dnl define the output header for config
AM_CONFIG_HEADER([config.h])

dnl AM_MAINTAINER_MODE only provides the option to configure to enable it
AM_MAINTAINER_MODE([enable])

dnl sets host_* variables
AC_CANONICAL_HOST

dnl use pretty build output with automake >= 1.11
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])],
  [AM_DEFAULT_VERBOSITY=1
   AC_SUBST(AM_DEFAULT_VERBOSITY)])

dnl our libraries and install dirs use major.minor as a version
GST_API_VERSION=$PACKAGE_VERSION_MAJOR.$PACKAGE_VERSION_MINOR
dnl we override it here if we need to for the release candidate of new series
GST_API_VERSION=1.0
AC_SUBST(GST_API_VERSION)

AG_GST_LIBTOOL_PREPARE
AS_LIBTOOL(GST, 0, 0, 0)

dnl *** required versions of GStreamer stuff ***
GST_REQ=0.11.93
ORC_REQ=0.4.16

dnl *** autotools stuff ****

dnl allow for different autotools
AS_AUTOTOOLS_ALTERNATE

dnl Add parameters for aclocal
AC_SUBST(ACLOCAL_AMFLAGS, "-I m4 -I common/m4")

dnl *** check for arguments to configure ***

AG_GST_ARG_DISABLE_FATAL_WARNINGS

AG_GST_ARG_WITH_PKG_CONFIG_PATH
AG_GST_ARG_WITH_PACKAGE_NAME
AG_GST_ARG_WITH_PACKAGE_ORIGIN
AG_GST_ARG_VALGRIND

dnl *** checks for platform ***

dnl * hardware/architecture *

dnl common/m4/gst-arch.m4
dnl check CPU type
AG_GST_ARCH

dnl *** checks for programs ***

dnl find a compiler
AC_PROG_CC
AC_PROG_CC_STDC

dnl check if the compiler supports '-c' and '-o' options
AM_PROG_CC_C_O

AC_PATH_PROG(VALGRIND_PATH, valgrind, no)
AM_CONDITIONAL(HAVE_VALGRIND, test ! "x$VALGRIND_PATH" = "xno")

dnl check for documentation tools
AG_GST_DOCBOOK_CHECK
GTK_DOC_CHECK([1.3])
AS_PATH_PYTHON([2.1])
AG_GST_PLUGIN_DOCS([1.3],[2.1])

dnl *** checks for libraries ***

dnl check for libm, for sin()
LT_LIB_M
AC_SUBST(LIBM)

dnl *** checks for header files ***

dnl check if we have ANSI C header files
AC_HEADER_STDC

dnl *** checks for types/defines ***

dnl *** checks for structures ***

dnl *** checks for compiler characteristics ***

dnl *** checks for library functions ***

dnl *** checks for dependancy libraries ***

dnl checks for gstreamer
dnl uninstalled is selected preferentially -- see pkg-config(1)
AG_GST_CHECK_GST($GST_API_VERSION, [$GST_REQ])
AG_GST_CHECK_GST_BASE($GST_API_VERSION, [$GST_REQ])
AG_GST_CHECK_GST_PLUGINS_BASE($GST_API_VERSION, [$GST_REQ])
AG_GST_CHECK_GST_CHECK($GST_API_VERSION, [$GST_REQ], no)
AM_CONDITIONAL(HAVE_GST_CHECK, test "x$HAVE_GST_CHECK" = "xyes")

AC_MSG_NOTICE(Using GStreamer Core Plugins in $GST_PLUGINS_DIR)
AC_MSG_NOTICE(Using GStreamer Base Plugins in $GSTPB_PLUGINS_DIR)

dnl orc is required for cpu detection for libpostproc
ORC_CHECK([$ORC_REQ])

dnl *** set variables based on configure arguments ***

dnl set location of plugin directory
AG_GST_SET_PLUGINDIR

dnl define an ERROR_CFLAGS Makefile variable
AG_GST_SET_ERROR_CFLAGS($FATAL_WARNINGS, [
    -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wundef
    -Wwrite-strings -Wformat-nonliteral -Wformat-security -Wold-style-definition
    -Winit-self -Wmissing-include-dirs -Waddress
    -Waggregate-return -Wno-multichar -Wnested-externs ])

dnl define correct level for debugging messages
AG_GST_SET_LEVEL_DEFAULT($GST_GIT)

dnl *** finalize CFLAGS, LDFLAGS, LIBS ***

dnl Overview:
dnl GST_OPTION_CFLAGS:  common flags for profiling, debugging, errors, ...
dnl GST_*:              flags shared by built objects to link against GStreamer
dnl GST_ALL_LDFLAGS:    linker flags shared by all
dnl GST_LIB_LDFLAGS:    additional linker flags for all libaries
dnl GST_LT_LDFLAGS:     library versioning of our libraries
dnl GST_PLUGIN_LDFLAGS: flags to be used for all plugins

dnl GST_OPTION_CFLAGS
if test "x$USE_DEBUG" = xyes; then
   PROFILE_CFLAGS="-g"
fi
AC_SUBST(PROFILE_CFLAGS)

if test "x$GST_GIT" = "xyes"; then
  DEPRECATED_CFLAGS="-DGST_DISABLE_DEPRECATED"
else
  DEPRECATED_CFLAGS=""
fi
AC_SUBST(DEPRECATED_CFLAGS)

dnl every flag in GST_OPTION_CFLAGS can be overridden at make time
GST_OPTION_CFLAGS="\$(WARNING_CFLAGS) \$(ERROR_CFLAGS) \$(DEBUG_CFLAGS) \$(PROFILE_CFLAGS) \$(GCOV_CFLAGS) \$(OPT_CFLAGS) \$(DEPRECATED_CFLAGS)"

AC_SUBST(GST_OPTION_CFLAGS)

dnl FIXME: do we want to rename to GST_ALL_* ?
dnl prefer internal headers to already installed ones
dnl also add builddir include for enumtypes and marshal
dnl add GST_OPTION_CFLAGS, but overridable
GST_CFLAGS="$GST_CFLAGS -DGST_USE_UNSTABLE_API"
GST_CFLAGS="-I\$(top_srcdir)/gst-libs -I\$(top_builddir)/gst-libs $GST_CFLAGS $GLIB_EXTRA_CFLAGS \$(GST_OPTION_CFLAGS)"
AC_SUBST(GST_CFLAGS)
AC_SUBST(GST_LIBS)

GST_ALL_LDFLAGS="-no-undefined"
AC_SUBST(GST_ALL_LDFLAGS)

dnl this really should only contain flags, not libs - they get added before
dnl whatevertarget_LIBS and -L flags here affect the rest of the linking
GST_PLUGIN_LDFLAGS="-module -avoid-version -export-symbols-regex '^[_]*gst_plugin_desc.*' $GST_ALL_LDFLAGS"
AC_SUBST(GST_PLUGIN_LDFLAGS)

dnl Add MacOSX specific flags
AC_CANONICAL_HOST
case $host_os in
     darwin*)
	DARWIN_LDFLAGS="-Wl,-read_only_relocs,suppress"
	;;
     *)
        DARWIN_LDFLAGS=""
	;;
esac
AC_SUBST(DARWIN_LDFLAGS)

dnl *** Check for bz2
AG_GST_CHECK_LIBHEADER(BZ2, bz2, BZ2_bzlibVersion, , bzlib.h, have_bz2=yes, have_bz2=no)
AM_CONDITIONAL(HAVE_BZ2, test "x$have_bz2" = "xyes")
if test "x$have_bz2" = "xno"; then
  AC_WARN([libbz2 not found, matroska demuxer will not be able to read bz2 tracks])
fi

AC_ARG_ENABLE(lgpl,
              [AC_HELP_STRING([--enable-lgpl], [build a LGPL licensed gst-libav])])
AM_CONDITIONAL(GST_LIBAV_ENABLE_LGPL, test "x$enable_lgpl" = "xyes")
if test "x$enable_lgpl" = "xyes"; then
  AC_DEFINE([GST_LIBAV_ENABLE_LGPL], [], [Defined if building a LGPL-only version of gst-libav])
fi

dnl *** configure external libs ***

HAVE_LIBAV_UNINSTALLED=1

AC_ARG_WITH(system-libav,
            [AC_HELP_STRING([--with-system-libav], [use system Libav libraries])])

if test "x$with_system_libav" = "xyes"; then
  PKG_CHECK_MODULES(LIBAV, libavformat libavcodec libavutil) 
  if test "x$enable_lgpl" != "xyes"; then
    PKG_CHECK_MODULES(POSTPROC, libpostproc libavcodec libavutil)
  fi
  PKG_CHECK_MODULES(SWSCALE, libswscale libavutil)
  saved_CPPFLAGS="$CPPFLAGS"
  CPPFLAGS="$CPPFLAGS $LIBAV_CFLAGS"
  AC_CHECK_HEADERS([avi.h])
  CPPFLAGS="$saved_CPPFLAGS"
  AC_DEFINE([LIBAV_SOURCE], ["system install"], [Describes where the Libav libraries come from.])
  HAVE_LIBAV_UNINSTALLED=0
  AC_MSG_NOTICE([Using system-installed libav code])
  AC_MSG_WARN([
  ======================================================================
   WARNING: you have chosen to build gst-libav against a random
   external version of Libav instead of building it against the tested
   internal Libav snapshot that is included with gst-libav.
   
   This is a very bad idea.  So bad in fact that words cannot express
   just how bad it is.  Suffice to say that it is BAD.
   
   The GStreamer developers cannot and will not support a gst-libav
   built this way.  Any bug reports that indicate there is an external
   version of Libav involved will be closed immediately without further
   investigation.
   
   The reason such a setup can't be supported is that the Libav API
   and ABI is in constant flux, yet there aren't any official releases
   of the Libav library to develop against.  This makes it impossible
   to guarantee that gst-libav will work reliably, or even compile,
   with a randomly picked version Libav.  Even if gst-libav compiles
   and superficially appears to work fine against your chosen external
   Libav version, that might just not be the case on other systems, or
   even the same system at a later time, or when using decoders,
   encoders, demuxers or muxers that have not been tested.
   
   Please do not create or distribute binary packages of gst-Libav
   that link against an external libav. Thank you!
  ======================================================================
  ])

  dnl No, this is not too extreme, we want people to see and read the above
  sleep 15
else

  AC_MSG_NOTICE([Using local Libav snapshot])
  
  dnl libgstlibav.la: include dirs
  LIBAV_CFLAGS="-I \$(top_srcdir)/gst-libs/ext/libav/libavutil \
  		 -I \$(top_srcdir)/gst-libs/ext/libav/libavformat \
                 -I \$(top_srcdir)/gst-libs/ext/libav/libavcodec \
		 -I \$(top_srcdir)/gst-libs/ext/libav \
		 -I \$(top_builddir)/gst-libs/ext/libav \
                 -Wno-deprecated-declarations"

  dnl libgstlibav.la: libs to statically link to        
  LIBAV_LIBS="\$(top_builddir)/gst-libs/ext/libav/libavformat/libavformat.a \
               \$(top_builddir)/gst-libs/ext/libav/libavcodec/libavcodec.a \
               \$(top_builddir)/gst-libs/ext/libav/libavutil/libavutil.a"
  dnl
  POSTPROC_CFLAGS="-I \$(top_srcdir)/gst-libs/ext/libav/libpostproc	\
                   -I \$(top_srcdir)/gst-libs/ext/libav/libavutil 	\
                   -I \$(top_srcdir)/gst-libs/ext/libav/libavcodec 	\
                   -I \$(top_srcdir)/gst-libs/ext/libav 	\
		   -I \$(top_builddir)/gst-libs/ext/libav \
                   -Wno-deprecated-declarations"

  dnl libgstpostproc.la: libs to statically link to
  POSTPROC_LIBS="\$(top_builddir)/gst-libs/ext/libav/libpostproc/libpostproc.a \
  		 \$(top_builddir)/gst-libs/ext/libav/libavutil/libavutil.a"
  				 
  dnl
  SWSCALE_CFLAGS="-I \$(top_srcdir)/gst-libs/ext/libav/libswscale	\
                  -I \$(top_srcdir)/gst-libs/ext/libav/libavutil 	\
                  -I \$(top_srcdir)/gst-libs/ext/libav 	\
		   -I \$(top_builddir)/gst-libs/ext/libav \
                  -Wno-deprecated-declarations"

  dnl libgstswscale.la: libs to statically link to
  SWSCALE_LIBS="\$(top_builddir)/gst-libs/ext/libav/libswscale/libswscale.a \
                \$(top_builddir)/gst-libs/ext/libav/libavutil/libavutil.a"

  LIBAV_SUBDIRS=gst-libs
  AC_DEFINE(HAVE_AVI_H)
  AC_DEFINE([LIBAV_SOURCE], ["local snapshot"], [Describes where the Libav libraries come from.])

  AC_ARG_WITH(libav-extra-configure, 
      AC_HELP_STRING([--with-libav-extra-configure="xxx"],
      [extra configure options for internal libav ./configure script]),,
      with_libav=no)

  # basic arguments
  emblibav_configure_args="--prefix=$prefix"

  # Enable pic and static so that we get .a files, but with PIC code.
  emblibav_configure_args="$emblibav_configure_args --disable-avserver --disable-avplay\
        --disable-ffmpeg --disable-avprobe --enable-static --enable-pic \
	--disable-encoder=flac --disable-decoder=cavs --disable-protocols --disable-devices\
	--disable-network --disable-hwaccels --disable-filters --disable-doc\
	--enable-optimizations"

  if test "x$enable_lgpl" != "xyes"; then
    emblibav_configure_args="$emblibav_configure_args --enable-postproc \
        --enable-gpl"
  fi

  # if we are cross-compiling, tell libav so
  target_os=`echo $host_os | sed 's/-gnu//'`
  if test "x$cross_compiling" = xyes; then
    emblibav_configure_args="$emblibav_configure_args --enable-cross-compile \
        --target-os=$target_os --arch=$host_cpu --cross-prefix=$host_alias-"
  fi

  case $host_os in
    # Unfortunately, in Mac OS 10.5 the current rev of libav builds
    # some non-PIC code into the .a file. See
    # http://trac.macosforge.org/projects/macports/ticket/13725 for more
    # info.
    darwin*) 
      emblibav_configure_args="$emblibav_configure_args --disable-mmx --disable-altivec"
      ;;
    mingw32*)
      emblibav_configure_args="$emblibav_configure_args --enable-memalign-hack"
      WIN32_LIBS="-lws2_32"
      ;;
    *)
      WIN32_LIBS=
      ;;
  esac

  dnl checks for extra enable/disable flags
  LIBAV_OPTS="(cd $srcdir/gst-libs/ext/libav && ./configure --help)"
  # Let's check if we can disable the building of the libav binary
  can_disable=`echo "$LIBAV_OPTS" | grep 'disable-ffmpeg'`
  if test "$can_disable" != ""; then
    emblibav_configure_args="$emblibav_configure_args --disable-ffmpeg"
  fi
  dnl check if libswscale needs enabling explicitly
  can_enable=`echo "$LIBAV_OPTS" | grep 'enable-swscale'`
  if test "$can_enable" != ""; then
    emblibav_configure_args="$emblibav_configure_args --enable-swscale"
  fi

  # append extra configure options to emblibav_configure_args if needed
  if test "x$with_libav_extra_configure" != "xno"; then
    emblibav_configure_args="$emblibav_configure_args $with_libav_extra_configure"
  fi

  AC_SUBST(LIBAV_CO_DIR)
  AC_SUBST(LIBAV_SVN)
  AC_SUBST(LIBAV_REVISION)
  AC_SUBST(LIBAV_EXTERNALS_REVISION)
  AC_CONFIG_COMMANDS([configure-embedded-libav],
    [echo "Configuring included Libav instance with args $emblibav_configure_args"
     origdir=`pwd`
     dnl Don't put path on the configure call when not needed, as FFmpeg's configure relies on it
     dnl to detect out-of-tree builds
     if test -z "$srcdir" -o "$srcdir" = .; then
       confcmd=./configure
     else
       confcmd="$ac_abs_top_srcdir"/gst-libs/ext/libav/configure
     fi

     AS_MKDIR_P(["$ac_top_build_prefix"gst-libs/ext/libav])
     cd "$ac_top_build_prefix"gst-libs/ext/libav &&
         eval "$confcmd $emblibav_configure_args" ||
         AC_MSG_ERROR([Failed to configure embedded Libav tree])
     cd "$origdir"
    ],
    [emblibav_configure_args="$emblibav_configure_args"])
  AC_MSG_NOTICE([Using included Libav code])
fi

AC_SUBST(LIBAV_CFLAGS)
AC_SUBST(LIBAV_LIBS)
AC_SUBST(LIBAV_SUBDIRS)
AC_SUBST(POSTPROC_CFLAGS)
AC_SUBST(POSTPROC_LIBS)
AC_SUBST(SWSCALE_CFLAGS)
AC_SUBST(SWSCALE_LIBS)
AC_SUBST(WIN32_LIBS)
 
if test x$HAVE_LIBAV_UNINSTALLED = x1; then
  AC_DEFINE(HAVE_LIBAV_UNINSTALLED, [], [Defined if building against uninstalled Libav source])
fi
AM_CONDITIONAL(HAVE_LIBAV_UNINSTALLED, test x$HAVE_LIBAV_UNINSTALLED = x1)

AC_CONFIG_FILES(
Makefile
common/Makefile
common/m4/Makefile
gst-libav.spec
ext/Makefile
ext/ffmpeg/Makefile
ext/libpostproc/Makefile
ext/libswscale/Makefile
gst-libs/Makefile
gst-libs/ext/Makefile
docs/Makefile
docs/version.entities
tests/Makefile
tests/check/Makefile
tests/files/Makefile
)
AC_OUTPUT

ORC_OUTPUT
