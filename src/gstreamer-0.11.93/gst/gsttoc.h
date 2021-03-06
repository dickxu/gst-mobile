/* GStreamer
 * (c) 2010, 2012 Alexander Saprykin <xelfium@gmail.com>
 *
 * gsttoc.h: generic TOC API declaration
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

#ifndef __GST_TOC_H__
#define __GST_TOC_H__

#include <gst/gstconfig.h>
#include <gst/gstminiobject.h>
#include <gst/gststructure.h>
#include <gst/gsttaglist.h>
#include <gst/gstformat.h>

G_BEGIN_DECLS

#define GST_TYPE_TOC (gst_toc_get_type ())
#define GST_TYPE_TOC_ENTRY (gst_toc_entry_get_type ())

typedef struct _GstTocEntry GstTocEntry;
typedef struct _GstToc GstToc;

/**
 * GstTocScope:
 * @GST_TOC_SCOPE_GLOBAL: global TOC representing all selectable options
 *     (this is what applications are usually interested in)
 * @GST_TOC_SCOPE_CURRENT: TOC for the currently active/selected stream
 *     (this is a TOC representing the current stream from start to EOS,
 *     and is what a TOC writer / muxer is usually interested in; it will
 *     usually be a subset of the global TOC, e.g. just the chapters of
 *     the current title, or the chapters selected for playback from the
 *     current title)
 *
 * The scope of a TOC.
 */
typedef enum {
  GST_TOC_SCOPE_GLOBAL = 1,
  GST_TOC_SCOPE_CURRENT = 2
} GstTocScope;

/**
 * GstTocEntryType:
 * @GST_TOC_ENTRY_TYPE_ANGLE: entry is an angle (i.e. an alternative)
 * @GST_TOC_ENTRY_TYPE_VERSION: entry is a version (i.e. alternative)
 * @GST_TOC_ENTRY_TYPE_EDITION: entry is an edition (i.e. alternative)
 * @GST_TOC_ENTRY_TYPE_INVALID: invalid entry type value
 * @GST_TOC_ENTRY_TYPE_TITLE: entry is a title (i.e. a part of a sequence)
 * @GST_TOC_ENTRY_TYPE_TRACK: entry is a track (i.e. a part of a sequence)
 * @GST_TOC_ENTRY_TYPE_CHAPTER: entry is a chapter (i.e. a part of a sequence)
 *
 * The different types of TOC entries (see #GstTocEntry).
 *
 * There are two types of TOC entries: alternatives or parts in a sequence.
 */
typedef enum {
  GST_TOC_ENTRY_TYPE_ANGLE       = -3,
  GST_TOC_ENTRY_TYPE_VERSION     = -2,
  GST_TOC_ENTRY_TYPE_EDITION     = -1,
  GST_TOC_ENTRY_TYPE_INVALID     = 0,
  GST_TOC_ENTRY_TYPE_TITLE       = 1,
  GST_TOC_ENTRY_TYPE_TRACK       = 2,
  GST_TOC_ENTRY_TYPE_CHAPTER     = 3,
} GstTocEntryType;

#define GST_TOC_ENTRY_TYPE_IS_ALTERNATIVE(entry_type)  (entry_type < 0)
#define GST_TOC_ENTRY_TYPE_IS_SEQUENCE(entry_type)     (entry_type > 0)

/* functions to return type structures */
GType           gst_toc_get_type                (void);
GType           gst_toc_entry_get_type          (void);

/* functions to create, ref and unref/free TOCs */
GstToc *           gst_toc_new                     (GstTocScope scope);

GstTocScope        gst_toc_get_scope               (const GstToc *toc);

void               gst_toc_set_tags                (GstToc *toc, GstTagList * tags);
void               gst_toc_merge_tags              (GstToc *toc, GstTagList *tags, GstTagMergeMode mode);
GstTagList *       gst_toc_get_tags                (const GstToc *toc);

void               gst_toc_append_entry               (GstToc *toc, GstTocEntry *entry);
GList *            gst_toc_get_entries             (const GstToc *toc);

void               gst_toc_dump                    (GstToc *toc);

#define gst_toc_ref(toc)            (GstToc*)gst_mini_object_ref(GST_MINI_OBJECT_CAST(toc))
#define gst_toc_unref(toc)          gst_mini_object_unref(GST_MINI_OBJECT_CAST(toc))
#define gst_toc_copy(toc)           (GstToc*)gst_mini_object_copy(GST_MINI_OBJECT_CAST(toc))
#define gst_toc_make_writable(toc)  (GstToc*)gst_mini_object_make_writable(GST_MINI_OBJECT_CAST(toc))

/* functions to create, ref and unref/free TOC entries */
GstTocEntry *   gst_toc_entry_new               (GstTocEntryType type, const gchar *uid);

#define gst_toc_entry_ref(entry)            (GstTocEntry*)gst_mini_object_ref(GST_MINI_OBJECT_CAST(entry))
#define gst_toc_entry_unref(entry)          gst_mini_object_unref(GST_MINI_OBJECT_CAST(entry))
#define gst_toc_entry_copy(entry)           (GstTocEntry*)gst_mini_object_copy(GST_MINI_OBJECT_CAST(entry))
#define gst_toc_entry_make_writable(entry)  (GstTocEntry*)gst_mini_object_make_writable(GST_MINI_OBJECT_CAST(entry))

GstTocEntry *      gst_toc_find_entry                    (const GstToc *toc, const gchar *uid);

GstTocEntryType    gst_toc_entry_get_entry_type          (const GstTocEntry *entry);
const gchar *      gst_toc_entry_get_uid                 (const GstTocEntry *entry);

void               gst_toc_entry_append_sub_entry           (GstTocEntry *entry, GstTocEntry *subentry);
GList *            gst_toc_entry_get_sub_entries         (const GstTocEntry *entry);

void               gst_toc_entry_set_tags                (GstTocEntry *entry, GstTagList *tags);
void               gst_toc_entry_merge_tags              (GstTocEntry *entry, GstTagList *tags, GstTagMergeMode mode);
GstTagList *       gst_toc_entry_get_tags                (const GstTocEntry *entry);

gboolean           gst_toc_entry_is_alternative          (const GstTocEntry *entry);
gboolean           gst_toc_entry_is_sequence             (const GstTocEntry *entry);

void               gst_toc_entry_set_start_stop_times    (GstTocEntry *entry, gint64 start, gint64 stop);
gboolean           gst_toc_entry_get_start_stop_times    (const GstTocEntry *entry, gint64 *start, gint64 *stop);

GstToc *           gst_toc_entry_get_toc                 (GstTocEntry *entry);
GstTocEntry *      gst_toc_entry_get_parent              (GstTocEntry *entry);


const gchar *      gst_toc_entry_type_get_nick     (GstTocEntryType type);

G_END_DECLS

#endif /* __GST_TOC_H__ */

