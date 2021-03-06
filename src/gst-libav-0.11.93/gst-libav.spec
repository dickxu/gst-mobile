%define majorminor  1.0
%define gstreamer   gstreamer011
%define gst_minver  0.11.0
%define gst_majorminor  1.0

Name: 		%{gstreamer}-libav
Version: 	0.11.93
Release:	1	
Summary: 	GStreamer Streaming-media framework plug-in using libav (FFmpeg).
Group: 		Libraries/Multimedia
License: 	LGPL
URL:		http://gstreamer.net/
Vendor:		GStreamer Backpackers Team <package@gstreamer.net>
Source:		http://gstreamer.freedesktop.org/src/gst-ffmpeg/gst-ffmpeg/gst-libav-%{version}.tar.xz
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

Requires:  	%{gstreamer} >= 0.9.7
BuildRequires: 	%{gstreamer}-devel >= 0.9.7
BuildRequires: 	%{gstreamer}-plugins-base-devel >= 0.9.7

%description
GStreamer is a streaming-media framework, based on graphs of filters which
operate on media data. Applications using this library can do anything
from real-time sound processing to playing videos, and just about anything
else media-related. Its plugin-based architecture means that new data
types or processing capabilities can be added simply by installing new
plug-ins.

This plugin contains the libav (formerly FFmpeg) codecs, containing codecs for most popular
multimedia formats.

%prep
%setup -q -n gst-libav-%{version}

%build
%configure

make

%install
rm -rf $RPM_BUILD_ROOT

%makeinstall
rm -f $RPM_BUILD_ROOT%{_libdir}/gstreamer-%{gst_majorminor}/*.la
rm -f $RPM_BUILD_ROOT%{_libdir}/gstreamer-%{gst_majorminor}/*.a

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-, root, root, -)
%doc AUTHORS COPYING README gst-libav.doap
%{_libdir}/gstreamer-%{gst_majorminor}/libgstlibav.so
%{_libdir}/gstreamer-%{gst_majorminor}/libgstpostproc.so
%{_libdir}/gstreamer-%{gst_majorminor}/libgstavscale.so


%changelog
* Fri Aug 03 2012 Christian Schaller <uraeus@linuxrising.org>
- update for 1.0 release and libav rename

* Fri Dec 15 2006 Thomas Vander Stichele <thomas at apestaart dot org>
- clean up
- add doap file

* Wed Oct 05 2004 Christian Schaller <christian at fluendo dot com>
- Update SPEC file to fit the times

* Sat Feb 14 2004 Thomas Vander Stichele <thomas at apestaart dot org>
- Clean up spec file

* Wed Jan 21 2004 Christian Schaller <Uraeus@gnome.org>
- First version of spec
