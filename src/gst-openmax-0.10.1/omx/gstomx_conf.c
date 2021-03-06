const char *default_config =
"\
"
"\
"
"\
"
"\
"
"\
"
"\
"
"omx_dummy,\
"
"  parent-type=GstOmxDummy,\
"
"  type=GstOmxDummyOne,\
"
"  library-name=libomxil-bellagio.so.0,\
"
"  component-name=OMX.bellagio.dummy,\
"
"  rank=0;\
"
"\
"
"\
"
"omx_dummy_2,\
"
"  parent-type=GstOmxDummy,\
"
"  type=GstOmxDummyTwo,\
"
"  library-name=libomxil-bellagio.so.0,\
"
"  component-name=OMX.st.dummy2,\
"
"  rank=256;\
"
"\
"
"omx_mpeg4dec,\
"
"  type=GstOmxMpeg4Dec,\
"
"  library-name=libomxil-bellagio.so.0,\
"
"  component-name=OMX.st.video_decoder.mpeg4,\
"
"  rank=256;\
"
"\
"
"omx_h264dec,\
"
"  type=GstOmxH264Dec,\
"
"  library-name=libomxil-bellagio.so.0,\
"
"  component-name=OMX.st.video_decoder.avc,\
"
"  rank=256;\
"
"\
"
"omx_h263dec,\
"
"  type=GstOmxH263Dec,\
"
"  library-name=libomxil-bellagio.so.0,\
"
"  component-name=OMX.st.video_decoder.h263,\
"
"  rank=256;\
"
"\
"
"omx_wmvdec,\
"
"  type=GstOmxWmvDec,\
"
"  library-name=libomxil-bellagio.so.0,\
"
"  component-name=OMX.st.video_decoder.wmv,\
"
"  rank=256;\
"
"\
"
"omx_mpeg4enc,\
"
"  type=GstOmxMpeg4Enc,\
"
"  library-name=libomxil-bellagio.so.0,\
"
"  component-name=OMX.st.video_encoder.mpeg4,\
"
"  rank=256;\
"
"\
"
"omx_h264enc,\
"
"  type=GstOmxH264Enc,\
"
"  library-name=libomxil-bellagio.so.0,\
"
"  component-name=OMX.st.video_encoder.avc,\
"
"  rank=256;\
"
"\
"
"omx_h263enc,\
"
"  type=GstOmxH263Enc,\
"
"  library-name=libomxil-bellagio.so.0,\
"
"  component-name=OMX.st.video_encoder.h263,\
"
"  rank=256;\
"
"\
"
"omx_vorbisdec,\
"
"  type=GstOmxVorbisDec,\
"
"  library-name=libomxil-bellagio.so.0,\
"
"  component-name=OMX.st.audio_decoder.ogg.single,\
"
"  rank=128;\
"
"\
"
"omx_mp3dec,\
"
"  type=GstOmxMp3Dec,\
"
"  library-name=libomxil-bellagio.so.0,\
"
"  component-name=OMX.st.audio_decoder.mp3.mad,\
"
"  rank=256;\
"
"omx_audiosink,\
"
"  type=GstOmxAudioSink,\
"
"  library-name=libomxil-bellagio.so.0,\
"
"  component-name=OMX.st.alsa.alsasink,\
"
"  rank=0;\
"
"omx_volume,\
"
"  type=GstOmxVolume,\
"
"  library-name=libomxil-bellagio.so.0,\
"
"  component-name=OMX.st.volume.component,\
"
"  rank=0;\
"
;
