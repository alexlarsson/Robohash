/*
 * Copyright (c) 2011, RedHat, Inc
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the <organization> nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Alexander Larsson <alexl@redhat.com>
 */

#include <string.h>
#include "robot_bits.h"
#include <robohash.h>

static GdkPixbuf *
robohash_part_get_pixbuf (int set, int element, int part)
{
  GdkPixbuf *pixbuf;
  GInputStream *stream;
  const char *data;
  gsize size;

  data = robohash_bits_get (set, element, part, &size);
  if (data == NULL)
    return NULL;

  stream = g_memory_input_stream_new_from_data (data, size, NULL);
  pixbuf = gdk_pixbuf_new_from_stream (stream, NULL, NULL);
  g_object_unref (stream);
  return pixbuf;
}

GdkPixbuf *
robohash_create_hash (int robot_set, char *data, int w, int h)
{
  GChecksum *cs;
  guint8 sha1[20];
  gsize len;
  guint64 bits;
  int set, n_sets, n_elements, element, n_parts, part;
  GdkPixbuf *pixbuf, *part_pixbuf, *res;

  /* Only first or any set supported atm */
  if (robot_set >= 0 && robot_set != 0)
    return NULL;

  cs = g_checksum_new (G_CHECKSUM_SHA1);
  g_checksum_update (cs, data, -1);
  len = sizeof (sha1);
  g_checksum_get_digest (cs, sha1, &len);

  bits =
    (guint64)sha1[0] |
    (guint64)sha1[1] << 8 |
    (guint64)sha1[2] << 16 |
    (guint64)sha1[3] << 24 |
    (guint64)sha1[4] << 32 |
    (guint64)sha1[5] << 40 |
    (guint64)sha1[6] << 48 |
    (guint64)sha1[7] << 56;

  if (robot_set < 0)
    n_sets = robohash_bits_get_n_sets ();
  else /* robot_set == 0, pick a color */
    n_sets = ROBOHASH_BITS_N_COLORS;

  set = bits % n_sets;
  bits = bits / n_sets;

  n_elements = robohash_bits_get_n_elements (set);

  pixbuf = NULL;
  for (element = 0; element < n_elements; element++) {
    n_parts = robohash_bits_get_n_parts (set, element);
    part = bits % n_parts;
    bits = bits / n_parts;

    part_pixbuf = robohash_part_get_pixbuf (set, element, part);
    if (pixbuf == NULL) {
      pixbuf = part_pixbuf;
    } else {
      gdk_pixbuf_composite (part_pixbuf, pixbuf,
			    0, 0, gdk_pixbuf_get_width (pixbuf), gdk_pixbuf_get_height (pixbuf),
			    0, 0, 1.0, 1.0,
			    GDK_INTERP_HYPER,
			    255);
      g_object_unref (part_pixbuf);
    }
  }

  res = gdk_pixbuf_scale_simple (pixbuf, w, h, GDK_INTERP_HYPER);
  g_object_unref (pixbuf);

  return res;
}
