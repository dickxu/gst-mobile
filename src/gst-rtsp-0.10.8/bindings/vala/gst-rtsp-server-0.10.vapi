/* gst-rtsp-server-0.10.vapi generated by vapigen, do not modify. */

[CCode (cprefix = "Gst", lower_case_cprefix = "gst_")]
namespace Gst {
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-client.h")]
	public class RTSPClient : GLib.Object {
		public weak Gst.RTSPConnection connection;
		public bool is_ipv6;
		public weak Gst.RTSPMedia media;
		public weak string server_ip;
		public weak GLib.List sessions;
		public weak GLib.List streams;
		public weak Gst.RTSPUrl uri;
		public weak Gst.RTSPWatch watch;
		public uint watchid;
		[CCode (has_construct_function = false)]
		public RTSPClient ();
		public bool accept (GLib.IOChannel channel);
		public Gst.RTSPMediaMapping get_media_mapping ();
		public Gst.RTSPSessionPool get_session_pool ();
		public void set_media_mapping (Gst.RTSPMediaMapping mapping);
		public void set_session_pool (Gst.RTSPSessionPool pool);
		public Gst.RTSPMediaMapping media_mapping { get; set; }
		public Gst.RTSPSessionPool session_pool { get; set; }
	}
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-media.h")]
	public class RTSPMedia : GLib.Object {
		public int active;
		public bool buffering;
		public weak GLib.Cond cond;
		public weak GLib.List @dynamic;
		public weak Gst.Element element;
		public bool eos_pending;
		public weak Gst.Element fakesink;
		public uint id;
		public bool is_ipv6;
		public bool is_live;
		public weak GLib.Mutex @lock;
		public Gst.Element pipeline;
		public weak Gst.RTSPTimeRange range;
		public bool reused;
		public weak Gst.Element rtpbin;
		public weak GLib.TimeoutSource source;
		public Gst.RTSPMediaStatus status;
		public weak GLib.Array streams;
		public Gst.State target_state;
		[CCode (has_construct_function = false)]
		public RTSPMedia ();
		public Gst.RTSPLowerTrans get_protocols ();
		public unowned Gst.RTSPMediaStream get_stream (uint idx);
		[NoWrapper]
		public virtual bool handle_message (Gst.Message message);
		public bool is_eos_shutdown ();
		public bool is_prepared ();
		public bool is_reusable ();
		public bool is_shared ();
		public uint n_streams ();
		public bool prepare ();
		public void remove_elements ();
		public bool seek (Gst.RTSPTimeRange range);
		public void set_eos_shutdown (bool eos_shutdown);
		public void set_protocols (Gst.RTSPLowerTrans protocols);
		public void set_reusable (bool reusable);
		public void set_shared (bool shared);
		public bool set_state (Gst.State state, GLib.Array trans);
		public virtual bool unprepare ();
		[NoAccessorMethod]
		public bool eos_shutdown { get; set; }
		public Gst.RTSPLowerTrans protocols { get; set; }
		[NoAccessorMethod]
		public bool reusable { get; set; }
		[NoAccessorMethod]
		public bool shared { get; set; }
		public virtual signal void unprepared ();
	}
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-media-factory.h")]
	public class RTSPMediaFactory : GLib.Object {
		public weak GLib.Mutex @lock;
		public weak GLib.HashTable medias;
		public weak GLib.Mutex medias_lock;
		[CCode (has_construct_function = false)]
		public RTSPMediaFactory ();
		public void collect_streams (Gst.RTSPUrl url, Gst.RTSPMedia media);
		[NoWrapper]
		public virtual void configure (Gst.RTSPMedia media);
		public virtual Gst.RTSPMedia? @construct (Gst.RTSPUrl url);
		[NoWrapper]
		public virtual Gst.Element create_pipeline (Gst.RTSPMedia media);
		[NoWrapper]
		public virtual string gen_key (Gst.RTSPUrl url);
		[NoWrapper]
		public virtual Gst.Element? get_element (Gst.RTSPUrl url);
		public string get_launch ();
		public bool is_eos_shutdown ();
		public bool is_shared ();
		public void set_eos_shutdown (bool eos_shutdown);
		public void set_launch (string launch);
		public void set_shared (bool shared);
		[NoAccessorMethod]
		public bool eos_shutdown { get; set; }
		public string launch { get; set; }
		[NoAccessorMethod]
		public bool shared { get; set; }
	}
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-media-mapping.h")]
	public class RTSPMediaMapping : GLib.Object {
		public weak GLib.HashTable mappings;
		[CCode (has_construct_function = false)]
		public RTSPMediaMapping ();
		public void add_factory (string path, Gst.RTSPMediaFactory factory);
		public Gst.RTSPMediaFactory? find_factory (Gst.RTSPUrl url);
		[NoWrapper]
		public virtual Gst.RTSPMediaFactory? find_media (Gst.RTSPUrl url);
		public void remove_factory (string path);
	}
	[Compact]
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-media.h")]
	public class RTSPMediaStream {
		[CCode (array_length = false)]
		public weak Gst.Element[] appsink;
		[CCode (array_length = false)]
		public weak Gst.Element[] appsrc;
		public weak Gst.Caps caps;
		public ulong caps_sig;
		public weak GLib.List destinations;
		public bool filter_duplicates;
		public weak Gst.Element payloader;
		public bool prepared;
		public weak Gst.Pad recv_rtcp_sink;
		public weak Gst.Pad recv_rtp_sink;
		[CCode (array_length = false)]
		public weak Gst.Element[] selector;
		public weak Gst.Pad send_rtcp_src;
		public weak Gst.Pad send_rtp_sink;
		public weak Gst.Pad send_rtp_src;
		public weak Gst.RTSPRange server_port;
		public weak GLib.Object session;
		public weak Gst.Pad srcpad;
		[CCode (array_length = false)]
		public weak Gst.Element[] tee;
		public weak GLib.List transports;
		[CCode (array_length = false)]
		public weak Gst.Element[] udpsink;
		[CCode (array_length = false)]
		public weak Gst.Element[] udpsrc;
		public Gst.FlowReturn rtcp (Gst.Buffer buffer);
		public Gst.FlowReturn rtp (Gst.Buffer buffer);
	}
	[Compact]
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-media.h")]
	public class RTSPMediaTrans {
		public bool active;
		public uint idx;
		public weak GLib.DestroyNotify ka_notify;
		public void* ka_user_data;
		public weak Gst.RTSPKeepAliveFunc keep_alive;
		public weak GLib.DestroyNotify notify;
		public weak GLib.Object rtpsource;
		public weak Gst.RTSPSendFunc send_rtcp;
		public weak Gst.RTSPSendFunc send_rtp;
		public bool timeout;
		public weak Gst.RTSPTransport transport;
		public void* user_data;
		public void cleanup ();
	}
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-server.h")]
	public class RTSPServer : GLib.Object {
		public weak GLib.IOChannel io_channel;
		public weak GLib.TimeoutSource io_watch;
		public void* server_sin;
		public Gst.PollFD server_sock;
		[CCode (has_construct_function = false)]
		public RTSPServer ();
		[NoWrapper]
		public virtual Gst.RTSPClient? accept_client (GLib.IOChannel channel);
		public uint attach (GLib.MainContext? context);
		public GLib.TimeoutSource? create_watch ();
		public string get_address ();
		public int get_backlog ();
		public GLib.IOChannel? get_io_channel ();
		public Gst.RTSPMediaMapping get_media_mapping ();
		public string get_service ();
		public Gst.RTSPSessionPool get_session_pool ();
		public static bool io_func (GLib.IOChannel channel, GLib.IOCondition condition, Gst.RTSPServer server);
		public void set_address (string address);
		public void set_backlog (int backlog);
		public void set_media_mapping (Gst.RTSPMediaMapping mapping);
		public void set_service (string service);
		public void set_session_pool (Gst.RTSPSessionPool pool);
		public string address { get; set; }
		public int backlog { get; set; }
		public Gst.RTSPMediaMapping media_mapping { get; set; }
		public string service { get; set; }
		public Gst.RTSPSessionPool session_pool { get; set; }
	}
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-session.h")]
	public class RTSPSession : GLib.Object {
		public GLib.TimeVal create_time;
		public int expire_count;
		public GLib.TimeVal last_access;
		public weak GLib.List medias;
		[CCode (has_construct_function = false)]
		public RTSPSession (string sessionid);
		public void allow_expire ();
		public unowned Gst.RTSPSessionMedia get_media (Gst.RTSPUrl uri);
		public unowned string get_sessionid ();
		public uint get_timeout ();
		public bool is_expired (GLib.TimeVal now);
		public unowned Gst.RTSPSessionMedia manage_media (Gst.RTSPUrl uri, owned Gst.RTSPMedia media);
		public int next_timeout (GLib.TimeVal now);
		public void prevent_expire ();
		public bool release_media (Gst.RTSPSessionMedia media);
		public void set_timeout (uint timeout);
		public void touch ();
		public string sessionid { get; construct; }
		public uint timeout { get; set; }
	}
	[Compact]
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-session.h")]
	public class RTSPSessionMedia {
		public uint counter;
		public weak Gst.RTSPMedia media;
		public Gst.RTSPState state;
		public weak GLib.Array streams;
		public weak Gst.RTSPUrl url;
		public bool alloc_channels (Gst.RTSPRange range);
		public unowned Gst.RTSPSessionStream get_stream (uint idx);
		public bool set_state (Gst.State state);
	}
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-session-pool.h")]
	public class RTSPSessionPool : GLib.Object {
		public weak GLib.Mutex @lock;
		public weak GLib.HashTable sessions;
		[CCode (has_construct_function = false)]
		public RTSPSessionPool ();
		public uint cleanup ();
		public Gst.RTSPSession create ();
		[NoWrapper]
		public virtual string create_session_id ();
		public GLib.TimeoutSource create_watch ();
		public GLib.List<Gst.RTSPSession> filter (Gst.RTSPSessionFilterFunc func);
		public Gst.RTSPSession? find (string sessionid);
		public uint get_max_sessions ();
		public uint get_n_sessions ();
		public bool remove (Gst.RTSPSession sess);
		public void set_max_sessions (uint max);
		public uint max_sessions { get; set; }
	}
	[Compact]
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-session.h")]
	public class RTSPSessionStream {
		public weak Gst.RTSPMediaStream media_stream;
		public weak Gst.RTSPMediaTrans trans;
		public void set_callbacks (Gst.RTSPSendFunc send_rtp, Gst.RTSPSendFunc send_rtcp, GLib.DestroyNotify notify);
		public void set_keepalive (Gst.RTSPKeepAliveFunc keep_alive, GLib.DestroyNotify notify);
		public Gst.RTSPTransport set_transport (Gst.RTSPTransport ct);
	}
	[Compact]
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-sdp.h")]
	public class SDPInfo {
		public weak string server_ip;
		public weak string server_proto;
	}
	[CCode (cprefix = "GST_RTSP_FILTER_", has_type_id = false, cheader_filename = "gst/rtsp-server/rtsp-session-pool.h")]
	public enum RTSPFilterResult {
		REMOVE,
		KEEP,
		REF
	}
	[CCode (cprefix = "GST_RTSP_MEDIA_STATUS_", has_type_id = false, cheader_filename = "gst/rtsp-server/rtsp-media.h")]
	public enum RTSPMediaStatus {
		UNPREPARED,
		PREPARING,
		PREPARED,
		ERROR
	}
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-media.h")]
	public delegate void RTSPKeepAliveFunc ();
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-media.h")]
	public delegate bool RTSPSendFunc (Gst.Buffer buffer, uchar channel);
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-session-pool.h")]
	public delegate Gst.RTSPFilterResult RTSPSessionFilterFunc (Gst.RTSPSessionPool pool, Gst.RTSPSession session);
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-session-pool.h")]
	public delegate bool RTSPSessionPoolFunc (Gst.RTSPSessionPool pool);
	[CCode (cheader_filename = "gst/gst.h")]
	public static Gst.RTSPResult rtsp_params_get (Gst.RTSPClient client, Gst.RTSPUrl uri, Gst.RTSPSession session, Gst.RTSPMessage request, Gst.RTSPMessage response);
	[CCode (cheader_filename = "gst/gst.h")]
	public static Gst.RTSPResult rtsp_params_set (Gst.RTSPClient client, Gst.RTSPUrl uri, Gst.RTSPSession session, Gst.RTSPMessage request, Gst.RTSPMessage response);
	[CCode (cheader_filename = "gst/rtsp-server/rtsp-sdp.h")]
	public static bool rtsp_sdp_from_media (ref unowned Gst.SDPMessage sdp, Gst.SDPInfo info, Gst.RTSPMedia media);
}
