#include <glib.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>

#include "gstapi.h"
#include "ALog-priv.h"

extern "C" void gst_static_plugins(void);

static gboolean bus_call (GstBus *bus, GstMessage *msg, gpointer data)
{
    GMainLoop *loop = (GMainLoop *) data;

    switch (GST_MESSAGE_TYPE (msg)) {
        case GST_MESSAGE_EOS:
            g_print ("End of stream\n");
            g_main_loop_quit (loop);
            break;
        case GST_MESSAGE_ERROR: 
        {
            gchar  *debug;
            GError *error;
            gst_message_parse_error (msg, &error, &debug);
            g_free (debug);
            g_printerr ("Error: %s\n", error->message);
            g_error_free (error);
            g_main_loop_quit (loop);
            break;
        }
        default:
        break;
    }

    return TRUE;
}

static void on_pad_added(GstElement *element, GstPad *pad, gpointer data)
{
    GstPad *sinkpad;
    GstElement *decoder = (GstElement *) data;

    /* We can now link this pad with the vorbis-decoder sink pad */
    g_print ("Dynamic pad created, linking demuxer/decoder\n");
    sinkpad = gst_element_get_static_pad (decoder, "sink");
    gst_pad_link (pad, sinkpad);
    gst_object_unref (sinkpad);
}

int ogg_player (const char *location) {

    GMainLoop *loop;
    GstElement *pipeline, *source, *demuxer, *decoder, *conv, *sink;
    GstBus *bus;
    guint bus_watch_id;

    /* Initialisation */
    loop = g_main_loop_new (NULL, FALSE);

    /* Create gstreamer elements */
    pipeline = gst_pipeline_new ("audio-player");
    source   = gst_element_factory_make ("filesrc",       "file-source");
    returnv_assert(source, -1);
    demuxer  = gst_element_factory_make ("oggdemux",      "ogg-demuxer");
    returnv_assert(demuxer, -1);
    decoder  = gst_element_factory_make ("vorbisdec",     "vorbis-decoder");
    returnv_assert(decoder, -1);
    conv     = gst_element_factory_make ("audioconvert",  "converter");
    returnv_assert(conv, -1);
    sink     = gst_element_factory_make ("autoaudiosink", "audio-output");
    returnv_assert(sink, -1);

    if (!pipeline || !source || !demuxer || !decoder || !conv || !sink) {
        g_printerr ("One element could not be created. Exiting.\n");
        return -1;
    }

    /* Set up the pipeline */

    /* we set the input filename to the source element */
    g_object_set (G_OBJECT (source), "location", location, NULL);

    /* we add a message handler */
    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    returnv_assert(bus, -1);
    bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
    gst_object_unref (bus);

    /* we add all elements into the pipeline */
    /* file-source | ogg-demuxer | vorbis-decoder | converter | alsa-output */
    gst_bin_add_many (GST_BIN (pipeline), source, demuxer, decoder, conv, sink, NULL);

    /* we link the elements together */
    /* file-source -> ogg-demuxer ~> vorbis-decoder -> converter -> alsa-output */
    gst_element_link (source, demuxer);
    gst_element_link_many (decoder, conv, sink, NULL);
    g_signal_connect (demuxer, "pad-added", G_CALLBACK (on_pad_added), decoder);

    /* note that the demuxer will be linked to the decoder dynamically.
       The reason is that Ogg may contain various streams (for example
       audio and video). The source pad(s) will be created at run time,
       by the demuxer when it detects the amount and nature of streams.
       Therefore we connect a callback function which will be executed
       when the "pad-added" is emitted.*/

    /* Set the pipeline to "playing" state*/
    g_print ("Now playing: %s\n", location);
    gst_element_set_state (pipeline, GST_STATE_PLAYING);

    /* Iterate */
    g_print ("Running...\n");
    g_main_loop_run (loop);

    /* Out of the main loop, clean up nicely */
    g_print ("Returned, stopping playback\n");
    gst_element_set_state (pipeline, GST_STATE_NULL);

    g_print ("Deleting pipeline\n");
    gst_object_unref (GST_OBJECT (pipeline));
    g_source_remove (bus_watch_id);
    g_main_loop_unref (loop);

    return 0;
}

namespace eau
{

gboolean CGstPlayback::handle_message (GstBus *bus, GstMessage *msg, void *data)
{
    CGstPlayback *thiz = (CGstPlayback *)data;
    if (thiz)
        return thiz->HandleMessage(bus, msg);
    return false;
}

CGstPlayback::CGstPlayback()
{
    m_sink = NULL;
    m_playbin = NULL;
    m_audio_sink = NULL;
    m_video_sink = NULL;
    m_main_loop = NULL;
    m_bus_msg_thread = NULL;
}

CGstPlayback::~CGstPlayback()
{
    Uninit();
}

bool CGstPlayback::Init()
{
    returnv_assert(!m_playbin, true);

    g_print("%s, begin", __func__);

    m_playbin = gst_element_factory_make ("playbin", "playbin");
    returnb_assert(m_playbin);

    GstBus *bus = gst_pipeline_get_bus (GST_PIPELINE(m_playbin));
    returnb_assert(bus);
    gst_bus_add_watch (bus, (GstBusFunc)handle_message, this);
    gst_object_unref (bus);

    //m_audio_sink = gst_element_factory_make("autoaudiosink", NULL);
    //returnb_assert(m_audio_sink);
    //g_object_set (GST_OBJECT(m_playbin), "audio-sink", m_audio_sink, NULL);

    //m_video_sink = gst_element_factory_make("eglglessink", NULL);
    //returnb_assert(m_video_sink);
    //g_object_set (GST_OBJECT(m_playbin), "video-sink", m_video_sink, NULL);

    g_print("%s, end", __func__);

    return true;
}

bool CGstPlayback::SetOption()
{
    returnb_assert(m_playbin);

    ALOGI("%s, set flags", __func__);
    g_object_get (m_playbin, "flags", &m_flags, NULL);
    m_flags |= GST_PLAY_FLAG_AUDIO | GST_PLAY_FLAG_VIDEO;
    m_flags &= ~GST_PLAY_FLAG_TEXT;
    g_object_set (m_playbin, "flags", m_flags, NULL);
    //g_object_set (m_playbin, "connection-speed", 56, NULL);
    return true;
}

bool CGstPlayback::SetUri(const char *uri)
{
    returnb_assert(m_playbin);

    g_print("%s, set uri=%s", __func__, uri);
    g_object_set (m_playbin, "uri", uri, NULL);
    return true;
}

bool CGstPlayback::SetWindow(void *window)
{
    returnb_assert(m_playbin);

    g_print("%s, get GST_TYPE_VIDEO_OVERLAY", __func__);
    m_video_sink = gst_bin_get_by_interface(GST_BIN(m_playbin), GST_TYPE_VIDEO_OVERLAY);
    returnb_assert(m_video_sink);

    g_print("%s, set native window=(%x)", __func__, window);
    gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (m_video_sink), (guintptr)window);
    return true;
}

bool CGstPlayback::Prepare()
{
    returnb_assert(m_playbin);

    g_print("%s, set ready state", __func__);
    // Set the pipeline to READY, so it can already accept a window handle, if we have one
    gint iret = gst_element_set_state(m_playbin, GST_STATE_READY);
    if (iret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the ready state.\n");
        return false;
    }

    return true;
}

bool CGstPlayback::Play()
{
    returnb_assert(m_playbin);

    g_print("%s, begin", __func__);
    gint iret = gst_element_set_state (m_playbin, GST_STATE_PLAYING);
    if (iret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
        return false;
    }

    if (!m_main_loop) {
        m_main_loop = g_main_loop_new (NULL, FALSE);
    }

    returnb_assert(m_main_loop);
    m_bus_msg_thread = g_thread_create ((GThreadFunc)g_main_loop_run, m_main_loop, TRUE, NULL);
    returnb_assert(m_bus_msg_thread);

    return true;
}

bool CGstPlayback::Pause()
{
    returnb_assert(m_playbin);

    g_print("%s, begin", __func__);
    gint iret = gst_element_set_state (m_playbin, GST_STATE_PAUSED);
    if (iret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
        return false;
    }
    return true;
}

bool CGstPlayback::Stop()
{
    returnb_assert(m_playbin);

    g_print("%s, begin", __func__);
    gint iret = gst_element_set_state (m_playbin, GST_STATE_READY);
    if (iret == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Unable to set the pipeline to the playing state.\n");
        return false;
    }
    return true;
}

void CGstPlayback::Uninit()
{
    g_print("%s, begin", __func__);
    gst_element_set_state (m_playbin, GST_STATE_NULL);

    //g_thread_join(m_bus_msg_thread);
    g_thread_unref(m_bus_msg_thread);
    m_bus_msg_thread = NULL;

    gst_object_unref (GST_OBJECT(m_playbin));
    m_playbin = NULL;

    gst_object_unref (GST_OBJECT(m_audio_sink));
    m_audio_sink = NULL;

    gst_object_unref (GST_OBJECT(m_video_sink));
    m_video_sink = NULL;

    g_main_loop_unref (m_main_loop);
    m_main_loop = NULL;
    g_print("%s, end", __func__);
}

void CGstPlayback::AnalyzeStreams()
{
    return_assert(m_playbin);

    g_print("%s, begin", __func__);
    g_object_get (m_playbin, "n-video", &m_numVideo, NULL);
    g_object_get (m_playbin, "n-audio", &m_numAudio, NULL);
    g_object_get (m_playbin, "n-text", &m_numText, NULL);   

    for (gint i = 0; i < m_numVideo; i++) {
        GstTagList *tags = NULL;
        gchar *str = NULL;
        /* Retrieve the stream's video tags */
        g_signal_emit_by_name (m_playbin, "get-video-tags", i, &tags);
        if (tags) {
            g_print ("video stream %d:\n", i);
            gst_tag_list_get_string (tags, GST_TAG_VIDEO_CODEC, &str);
            g_print ("  codec: %s\n", str ? str : "unknown");
            g_free (str);
            gst_tag_list_free (tags);
        }
    }

    for (gint i = 0; i < m_numAudio; i++) {
        GstTagList *tags = NULL;
        gchar *str = NULL;
        guint rate = 0;
        /* Retrieve the stream's audio tags */
        g_signal_emit_by_name (m_playbin, "get-audio-tags", i, &tags);
        if (tags) {
            g_print ("audio stream %d:\n", i);
            if (gst_tag_list_get_string (tags, GST_TAG_AUDIO_CODEC, &str)) {
                g_print ("  codec: %s\n", str);
                g_free (str);
            }
            if (gst_tag_list_get_string (tags, GST_TAG_LANGUAGE_CODE, &str)) {
                g_print ("  language: %s\n", str);
                g_free (str);
            }
            if (gst_tag_list_get_uint (tags, GST_TAG_BITRATE, &rate)) {
                g_print ("  bitrate: %d\n", rate);
            }
            gst_tag_list_free (tags);
        }
    }

    for (gint i = 0; i < m_numText; i++) {
        GstTagList *tags = NULL;
        gchar *str = NULL;
        /* Retrieve the stream's subtitle tags */
        g_signal_emit_by_name (m_playbin, "get-text-tags", i, &tags);
        if (tags) {
            g_print ("subtitle stream %d:\n", i);
            if (gst_tag_list_get_string (tags, GST_TAG_LANGUAGE_CODE, &str)) {
                g_print ("  language: %s\n", str);
                g_free (str);
            }
            gst_tag_list_free (tags);
        }
    }

    g_object_get (GST_OBJECT(m_playbin), "current-video", &m_curVideo, NULL);
    g_object_get (GST_OBJECT(m_playbin), "current-audio", &m_curAudio, NULL);
    g_object_get (GST_OBJECT(m_playbin), "current-text", &m_curText, NULL);
}

gboolean CGstPlayback::HandleMessage(GstBus *bus, GstMessage *msg)
{
    switch (GST_MESSAGE_TYPE (msg)) {
        case GST_MESSAGE_EOS:
            g_print ("End of stream");
            if (m_sink)
                m_sink->onCompletion();
            //g_main_loop_quit (m_main_loop);
            break;
        case GST_MESSAGE_STATE_CHANGED: {
            GstState state = GST_STATE_NULL;
            gint iret = gst_element_get_state(m_playbin, &state, NULL, NULL);
            if (iret != GST_STATE_CHANGE_FAILURE && m_sink) {
                m_sink->onPlayState(state);
            }
            g_print("state changed to=%d", (gint)state);
            break;
        }
        case GST_MESSAGE_ERROR: {
            gchar  *debug;
            GError *error;
            gst_message_parse_error (msg, &error, &debug);
            g_printerr ("Error: %s", error->message);
            if (m_sink)
                m_sink->onError(error->code, error->message);
            g_free (debug);
            g_error_free (error);
            //g_main_loop_quit (m_main_loop);
            break;
        }
        case GST_MESSAGE_INFO: {
            gchar  *debug;
            GError *error;
            gst_message_parse_info (msg, &error, &debug);
            g_printerr ("Info: %s", error->message);
            if (m_sink)
                m_sink->onInfo(error->code, error->message);
            g_free (debug);
            g_error_free (error);
            break;
        }
        default:
            break;
    }

    return TRUE;
}

} // namespace eau
