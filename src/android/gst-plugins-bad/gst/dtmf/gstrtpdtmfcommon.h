
#ifndef __GST_RTP_DTMF_COMMON_H__
#define __GST_RTP_DTMF_COMMON_H__


typedef struct
{
  unsigned event:8;             /* Current DTMF event */
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
  unsigned volume:6;            /* power level of the tone, in dBm0 */
  unsigned r:1;                 /* Reserved-bit */
  unsigned e:1;                 /* End-bit */
#elif G_BYTE_ORDER == G_BIG_ENDIAN
  unsigned e:1;                 /* End-bit */
  unsigned r:1;                 /* Reserved-bit */
  unsigned volume:6;            /* power level of the tone, in dBm0 */
#else
#error "G_BYTE_ORDER should be big or little endian."
#endif
  unsigned duration:16;         /* Duration of digit, in timestamp units */
} GstRTPDTMFPayload;

#endif /* __GST_RTP_DTMF_COMMON_H__ */
