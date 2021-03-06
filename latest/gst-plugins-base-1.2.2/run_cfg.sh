if test -z $ROOT; then
    ROOT=/opt/zdisk/zerox/android/android-ndk-r9
    CCROOT=$ROOT/toolchains/arm-linux-androideabi-4.6/prebuilt/linux-x86
    SYSROOT=$ROOT/platforms/android-14/arch-arm/
    HOST=arm-linux-androideabi
    CACHE_FILE=./arm-linux.cache

    #export AR="$CCROOT/bin/$HOST-ar --sysroot=$SYSROOT"
    export CC="$CCROOT/bin/$HOST-gcc --sysroot=$SYSROOT"
    export CXX="$CCROOT/bin/$HOST-g++ --sysroot=$SYSROOT"
    export STRIP="$CCROOT/bin/$HOST-strip --sysroot=$SYSROOT"
    #export RANLIB="$CCROOT/bin/$HOST-ranlib --sysroot=$SYSROOT"
fi
export CFLAGS=""
export LDFLAGS=""


PWD=`pwd`
export GLIB_CFLAGS="-I$PWD/../groot/include/glib-2.0 -I$PWD/../groot/lib/glib-2.0/include"
export GLIB_LIBS="-L$PWD/../groot/lib -lglib-2.0 -lgobject-2.0 -lgmodule-2.0 -lm"
export GIO_CFLAGS="-I$PWD/../groot/include/glib-2.0"
export GIO_LIBS="-L$PWD/../groot/lib -lgio-2.0"

export GST_CFLAGS="-I$PWD/../groot/include/gstreamer-1.0"
export GST_LIBS="-L$PWD/../groot/lib -lgstreamer-1.0"
export GST_BASE_CFLAGS="-I$PWD/../groot/include/gstreamer-1.0"
export GST_BASE_LIBS="-L$PWD/../groot/lib -lgstbase-1.0"
export GST_CONTROLLER_CFLAGS="-I$PWD/../groot/include/gstreamer-1.0"
export GST_CONTROLLER_LIBS="-L$PWD/../groot/lib -lgstcontroller-1.0"

export GST_TOOLS_DIR="$PWD/../groot/bin"
export GST_PLUGINS_DIR="$PWD/../groot/lib/gstreamer-1.0"

export OGG_CFLAGS="-I$PWD/../groot/include"
export OGG_LIBS="-L$PWD/../groot/lib -logg"
export VORBIS_CFLAGS="-I$PWD/../groot/include"
export VORBIS_LIBS="-L$PWD/../groot/lib -lvorbis -logg"
export THEORA_CFLAGS="-I$PWD/../groot/include"
export THEORA_LIBS="-L$PWD/../groot/lib -ltheora -logg"

export CFLAGS="$CFLAGS $GLIB_CFLAGS $GIO_CFLAGS $GST_CFLAGS $OGG_CFLAGS $VORBIS_CFLAGS $THEORA_CFLAGS"
export LDFLAGS="$LDFLAGS $GLIB_LIBS $GIO_LIBS $GST_LIBS $OGG_LIBS $VORBIS_LIBS $THEORA_LIBS"

##
## start configure
mkdir -p oldbld
cd oldbld

PREFIX=`pwd`/../../groot
mkdir -p $PREFIX

#--disable-examples
#--disable-external
#--disable-largefile
#--disable-ogg
#--disable-vorbis
#--disable-theora
../configure \
    --prefix=$PREFIX \
    --host=arm-linux-androideabi  \
    --disable-nls --disable-rpath \
    --disable-debug \
    --disable-valgrind \
    --disable-Bsymbolic \
    --enable-static \
    --disable-shared \
    --enable-static-plugins \
    --disable-x --disable-xvideo --disable-xshm \
    --disable-alsa \
    --disable-pango \
    --disable-freetypetest \
    --without-libiconv-prefix \
    --without-libintl-prefix

make && make install
