# if USE_DXR3
# DXR3_DIR=dxr3
# else
# DXR3_DIR=
# endif

# if USE_QCAM
# QCAM_DIR=qcam
# else
# QCAM_DIR=
# endif

if USE_VCD
VCD_DIR=vcd
else
VCD_DIR=
endif

# if USE_CDROM
#  CDROM_DIR=cdrom
# else
# CDROM_DIR=
# endif

if USE_DIRECTDRAW
DIRECTDRAW_DIR=directdraw
else
DIRECTDRAW_DIR=
endif

if USE_DIRECTSOUND
DIRECTSOUND_DIR=directsound
else
DIRECTSOUND_DIR=
endif

if USE_FBDEV
FBDEV_DIR=fbdev
else
FBDEV_DIR=
endif

if USE_DVB
DVB_DIR=dvb
else
DVB_DIR=
endif

if USE_APPLE_MEDIA
APPLE_MEDIA_DIR=applemedia
else
APPLE_MEDIA_DIR=
endif

if USE_OSX_VIDEO
OSX_VIDEO_DIR=osxvideo
else
OSX_VIDEO_DIR=
endif

if USE_QUICKTIME
QT_DIR=qtwrapper
else
QT_DIR=
endif

if USE_WININET
WININET_DIR=wininet
else
WININET_DIR=
endif

if USE_ACM
ACM_DIR=acmenc acmmp3dec
else
ACM_DIR=
endif

if USE_VDPAU
VDPAU_DIR=vdpau
else
VDPAU_DIR=
endif

if USE_SHM
SHM_DIR=shm
else
SHM_DIR=
endif

SUBDIRS = $(ACM_DIR) $(APPLE_MEDIA_DIR) $(DIRECTDRAW_DIR) $(DIRECTSOUND_DIR) $(DVB_DIR) $(FBDEV_DIR) $(OSX_VIDEO_DIR) $(QT_DIR) $(SHM_DIR) $(VCD_DIR) $(VDPAU_DIR) $(WININET_DIR)

DIST_SUBDIRS = acmenc acmmp3dec applemedia directdraw directsound dvb fbdev dshowdecwrapper dshowsrcwrapper dshowvideosink \
		osxvideo qtwrapper shm vcd vdpau wasapi wininet winks winscreencap

include $(top_srcdir)/common/parallel-subdirs.mak
