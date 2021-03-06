LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

GST_INDEX_SRC:= 	\
    gstindex.c		\
    gstindexfactory.c

GST_TRACE_SRC:= \
    gsttrace.c

GST_URI_SRC:= \
    gsturi.c

GST_REGISTRY_SRC:= \
    gstregistrybinary.c

GST_LOADSAVE_SRC:=

GST_MAJORMINOR:= 0.10

LOCAL_SRC_FILES:= 			\
    gst.c            			\
    gstobject.c        			\
    gstbin.c        			\
    gstbuffer.c        			\
    gstbus.c        			\
    gstcaps.c        			\
    gstchildproxy.c        		\
    gstclock.c        			\
    gstdebugutils.c        		\
    gstelement.c        		\
    gstelementfactory.c    		\
    gsterror.c        			\
    gstevent.c        			\
    gstfilter.c        			\
    gstformat.c        			\
    gstghostpad.c        		\
    $(GST_INDEX_SRC)    		\
    gstinfo.c        			\
    gstinterface.c        		\
    gstiterator.c        		\
    gstmessage.c        		\
    gstminiobject.c        		\
    gstpad.c        			\
    gstpadtemplate.c    		\
    gstparamspecs.c        		\
    gstpipeline.c        		\
    gstplugin.c        			\
    gstpluginfeature.c    		\
    gstpoll.c        			\
    gstpreset.c          		\
    gstquark.c        			\
    gstquery.c        			\
    gstregistry.c        		\
    gstsegment.c        		\
    gststructure.c        		\
    gstsystemclock.c    		\
    gsttaglist.c        		\
    gsttagsetter.c        		\
    gsttask.c        			\
    $(GST_TRACE_SRC)    		\
    gsttypefind.c        		\
    gsttypefindfactory.c    		\
    $(GST_URI_SRC)        		\
    gstutils.c        			\
    gstvalue.c        			\
    gstparse.c        			\
    $(GST_REGISTRY_SRC)    		\
    $(GST_LOADSAVE_SRC)     		\
    ./android/gst/gstenumtypes.c        \
    ./android/gst/gstmarshal.c          \
    ./android/gst/parse/grammar.tab.c   \
    ./android/gst/parse/lex._gst_parse_yy.c

LOCAL_STATIC_LIBRARIES := 	\
    glib-2.0             	\
    gthread-2.0          	\
    gmodule-2.0          	\
    gobject-2.0

LOCAL_MODULE:= gstreamer-$(GST_MAJORMINOR)

LOCAL_CFLAGS :=					\
	-I$(LOCAL_PATH)           		\
	-I$(GSTREAMER_TOP)			\
	-I$(GSTREAMER_TOP)/android       	\
	-I$(LOCAL_PATH)/android   		\
	-I$(LOCAL_PATH)/android/gst   		\
	-I$(LOCAL_PATH)/android/gst/parse   	\
	-I$(LOCAL_PATH)/parse           	\
	-I$(GSTREAMER_TOP)/../glib				\
	-I$(GSTREAMER_TOP)/../glib/android			\
	-I$(GSTREAMER_TOP)/../glib/glib			\
	-I$(GSTREAMER_TOP)/../glib/gmodule			\
	-I$(GSTREAMER_TOP)/../glib/gobject			\
	-I$(GSTREAMER_TOP)/../glib/gthread

LOCAL_CFLAGS += \
    -D_GNU_SOURCE                                   \
    -DG_LOG_DOMAIN=g_log_domain_gstreamer         \
    -DGST_MAJORMINOR=\""$(GST_MAJORMINOR)"\"     \
    -DGST_DISABLE_DEPRECATED                        \
    -DHAVE_CONFIG_H            

include $(BUILD_STATIC_LIBRARY)
