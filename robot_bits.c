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

#include "robot_bits.h"
#include "robot_data.h"

int
robohash_bits_get_n_sets (void)
{
  return sizeof (all_sets) / sizeof (RobohashSet *);
}

int
robohash_bits_get_n_elements (int set)
{
  if (set < 0 || set >= robohash_bits_get_n_sets ())
    return -1;

  return all_sets[set]->n_elements;
}

int
robohash_bits_get_n_parts (int set, int element)
{
  if (element < 0 || element >= robohash_bits_get_n_elements (set))
    return -1;
  return all_sets[set]->elements[element]->n_parts;
}

const char *
robohash_bits_get (int set, int element, int part, size_t *size)
{
  const RobohashPart *part_data;

  if (part < 0 || part >= robohash_bits_get_n_parts (set, element))
    return NULL;
  part_data = &all_sets[set]->elements[element]->parts[part];
  *size = part_data->size;
  return robot_data + part_data->offset;
}
