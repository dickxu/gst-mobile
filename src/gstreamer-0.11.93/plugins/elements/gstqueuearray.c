/* GStreamer
 * Copyright (C) 2009 Edward Hervey <bilboed@bilboed.com>
 *
 * gstqueuearray.c:
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

#include <string.h>
#include <gst/gst.h>
#include "gstqueuearray.h"

void
gst_queue_array_init (GstQueueArray * array, guint initial_size)
{
  array->size = initial_size;
  array->array = g_new0 (gpointer, initial_size);
  array->head = 0;
  array->tail = 0;
  array->length = 0;

}

GstQueueArray *
gst_queue_array_new (guint initial_size)
{
  GstQueueArray *array;

  array = g_new (GstQueueArray, 1);
  gst_queue_array_init (array, initial_size);
  return array;
}

gpointer
gst_queue_array_pop_head (GstQueueArray * array)
{
  gpointer ret;

  /* empty array */
  if (G_UNLIKELY (array->length == 0))
    return NULL;
  ret = array->array[array->head];
  array->head++;
  array->head %= array->size;
  array->length--;
  return ret;
}

void
gst_queue_array_push_tail (GstQueueArray * array, gpointer data)
{
  /* Check if we need to make room */
  if (G_UNLIKELY (array->length == array->size)) {
    /* newsize is 50% bigger */
    guint newsize = (3 * array->size) / 2;

    /* copy over data */
    if (array->tail != 0) {
      gpointer *array2 = g_new0 (gpointer, newsize);
      guint t1 = array->head;
      guint t2 = array->size - array->head;

      /* [0-----TAIL][HEAD------SIZE]
       *
       * We want to end up with
       * [HEAD------------------TAIL][----FREEDATA------NEWSIZE]
       *
       * 1) move [HEAD-----SIZE] part to beginning of new array
       * 2) move [0-------TAIL] part new array, after previous part
       */

      memcpy (array2, &array->array[array->head], t2 * sizeof (gpointer));
      memcpy (&array2[t2], array->array, t1 * sizeof (gpointer));

      g_free (array->array);
      array->array = array2;
      array->head = 0;
    } else {
      /* Fast path, we just need to grow the array */
      array->array = g_renew (gpointer, array->array, newsize);
    }
    array->tail = array->size;
    array->size = newsize;
  }

  array->array[array->tail] = data;
  array->tail++;
  array->tail %= array->size;
  array->length++;
}

gboolean
gst_queue_array_is_empty (GstQueueArray * array)
{
  return (array->length == 0);
}

void
gst_queue_array_clear (GstQueueArray * array)
{
  g_free (array->array);
}

void
gst_queue_array_free (GstQueueArray * array)
{
  gst_queue_array_clear (array);
  g_free (array);
}

void
gst_queue_array_drop_element (GstQueueArray * array, guint idx)
{
  if (idx == array->head) {
    /* just move the head */
    array->head++;
    array->head %= array->size;
    return;
  }
  if (idx == array->tail - 1) {
    /* just move the tail */
    array->tail = (array->tail - 1 + array->size) % array->size;
    return;
  }
  /* drop the element #idx... and readjust the array */
  if (array->head < array->tail) {
    /* Make sure it's within the boundaries */
    g_assert (array->head < idx && idx <= array->tail);
    /* ends not wrapped */
    /* move head-idx to head+1 */
    memcpy (&array->array[array->head + 1],
        &array->array[array->head], (idx - array->head) * sizeof (gpointer));
    array->tail--;
  } else {
    /* ends are wrapped */
    if (idx < array->tail) {
      /* move idx-tail backwards one */
      memcpy (&array->array[idx - 1],
          &array->array[idx], (array->tail - idx) * sizeof (gpointer));
      array->tail--;
    } else if (idx >= array->head) {
      /* move head-idx forwards one */
      memcpy (&array->array[array->head],
          &array->array[array->head + 1],
          (idx - array->head) * sizeof (gpointer));
      array->head++;
    } else
      g_assert_not_reached ();
  }
}

guint
gst_queue_array_find (GstQueueArray * array, GCompareFunc func, gpointer data)
{
  guint i;

  /* Scan from head to tail */
  for (i = array->head; i < array->length; i = (i + 1) % array->size)
    if (func (array->array[i], data) == 0)
      return i;
  return -1;
}
