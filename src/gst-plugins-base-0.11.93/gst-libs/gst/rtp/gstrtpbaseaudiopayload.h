/* GStreamer
 * Copyright (C) <2006> Philippe Khalaf <philippe.kalaf@collabora.co.uk>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GST_RTP_BASE_AUDIO_PAYLOAD_H__
#define __GST_RTP_BASE_AUDIO_PAYLOAD_H__

#include <gst/gst.h>
#include <gst/rtp/gstrtpbasepayload.h>
#include <gst/base/gstadapter.h>

G_BEGIN_DECLS

typedef struct _GstRTPBaseAudioPayload GstRTPBaseAudioPayload;
typedef struct _GstRTPBaseAudioPayloadClass GstRTPBaseAudioPayloadClass;

typedef struct _GstRTPBaseAudioPayloadPrivate GstRTPBaseAudioPayloadPrivate;

#define GST_TYPE_RTP_BASE_AUDIO_PAYLOAD \
  (gst_rtp_base_audio_payload_get_type())
#define GST_RTP_BASE_AUDIO_PAYLOAD(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), \
  GST_TYPE_RTP_BASE_AUDIO_PAYLOAD,GstRTPBaseAudioPayload))
#define GST_RTP_BASE_AUDIO_PAYLOAD_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), \
  GST_TYPE_RTP_BASE_AUDIO_PAYLOAD,GstRTPBaseAudioPayloadClass))
#define GST_IS_RTP_BASE_AUDIO_PAYLOAD(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_RTP_BASE_AUDIO_PAYLOAD))
#define GST_IS_RTP_BASE_AUDIO_PAYLOAD_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_RTP_BASE_AUDIO_PAYLOAD))
#define GST_RTP_BASE_AUDIO_PAYLOAD_CAST(obj) \
  ((GstRTPBaseAudioPayload *) (obj))

struct _GstRTPBaseAudioPayload
{
  GstRTPBasePayload payload;

  GstRTPBaseAudioPayloadPrivate *priv;

  GstClockTime base_ts;
  gint frame_size;
  gint frame_duration;

  gint sample_size;

  /*< private >*/
  gpointer _gst_reserved[GST_PADDING];
};

/**
 * GstRTPBaseAudioPayloadClass:
 * @parent_class: the parent class
 *
 * Base class for audio RTP payloader.
 */
struct _GstRTPBaseAudioPayloadClass
{
  GstRTPBasePayloadClass parent_class;

  /*< private >*/
  gpointer _gst_reserved[GST_PADDING];
};

GType gst_rtp_base_audio_payload_get_type (void);

/* configure frame based */
void            gst_rtp_base_audio_payload_set_frame_based        (GstRTPBaseAudioPayload *rtpbaseaudiopayload);

void            gst_rtp_base_audio_payload_set_frame_options      (GstRTPBaseAudioPayload *rtpbaseaudiopayload,
                                                                   gint frame_duration, gint frame_size);

/* configure sample based */
void            gst_rtp_base_audio_payload_set_sample_based       (GstRTPBaseAudioPayload *rtpbaseaudiopayload);
void            gst_rtp_base_audio_payload_set_sample_options     (GstRTPBaseAudioPayload *rtpbaseaudiopayload,
                                                                   gint sample_size);
void            gst_rtp_base_audio_payload_set_samplebits_options (GstRTPBaseAudioPayload *rtpbaseaudiopayload,
                                                                   gint sample_size);

/* get the internal adapter */
GstAdapter*     gst_rtp_base_audio_payload_get_adapter            (GstRTPBaseAudioPayload *rtpbaseaudiopayload);

/* push and flushing data */
GstFlowReturn   gst_rtp_base_audio_payload_push                   (GstRTPBaseAudioPayload * baseaudiopayload,
                                                                   const guint8 * data, guint payload_len,
                                                                   GstClockTime timestamp);
GstFlowReturn   gst_rtp_base_audio_payload_flush                  (GstRTPBaseAudioPayload * baseaudiopayload,
                                                                   guint payload_len, GstClockTime timestamp);

G_END_DECLS

#endif /* __GST_RTP_BASE_AUDIO_PAYLOAD_H__ */
