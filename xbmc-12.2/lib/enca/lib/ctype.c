/*
  @(#) $Id: ctype.c,v 1.1 2004/05/11 16:14:02 yeti Exp $
  convert charset and surface names to internal representation and back

  Copyright (C) 2000-2003 David Necas (Yeti) <yeti@physics.muni.cz>
  Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
  and the GLib team.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as published
  by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
*/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif /* HAVE_CONFIG_H */

#include "internal.h"

/* Basically taken from GLib, some more flags were added.
 * Note glibc says isspace('\v'), GLib says it is not.  */
const short int enca_ctype_data[0x100] = {
  0x1004, 0x1004, 0x1004, 0x1004, 0x1004, 0x1004, 0x1004, 0x1004, /* 0x00 */
  0x1004, 0x0104, 0x0104, 0x1004, 0x0104, 0x0104, 0x1004, 0x1004, /* 0x08 */
  0x1004, 0x1004, 0x1004, 0x1004, 0x1004, 0x1004, 0x1004, 0x1004, /* 0x10 */
  0x1004, 0x1004, 0x1004, 0x1004, 0x1004, 0x1004, 0x1004, 0x1004, /* 0x18 */
  0x0140, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0, /* 0x20 */
  0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x08d0, 0x08d0, 0x08d0, /* 0x28 */
  0x0c59, 0x0c59, 0x0c59, 0x0c59, 0x0c59, 0x0c59, 0x0c59, 0x0c59, /* 0x30 */
  0x0c59, 0x0c59, 0x08d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x00d0, /* 0x38 */
  0x00d0, 0x2e53, 0x2e53, 0x2e53, 0x2e53, 0x2e53, 0x2e53, 0x2a53, /* 0x40 */
  0x2a53, 0x2a53, 0x2a53, 0x2a53, 0x2a53, 0x2a53, 0x2a53, 0x2a53, /* 0x48 */
  0x2a53, 0x2a53, 0x2a53, 0x2a53, 0x2a53, 0x2a53, 0x2a53, 0x2a53, /* 0x50 */
  0x2a53, 0x2a53, 0x2a53, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x08d0, /* 0x58 */
  0x00d0, 0x2c73, 0x2c73, 0x2c73, 0x2c73, 0x2c73, 0x2c73, 0x2873, /* 0x60 */
  0x2873, 0x2873, 0x2873, 0x2873, 0x2873, 0x2873, 0x2873, 0x2873, /* 0x68 */
  0x2873, 0x2873, 0x2873, 0x2873, 0x2873, 0x2873, 0x2873, 0x2873, /* 0x70 */
  0x2873, 0x2873, 0x2873, 0x00d0, 0x00d0, 0x00d0, 0x00d0, 0x1004, /* 0x78 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0x80 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0x88 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0x90 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0x98 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0xa0 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0xa8 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0xb0 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0xb8 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0xc0 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0xc8 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0xd0 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0xd8 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0xe0 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0xe8 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0xf0 */
  0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, /* 0xf8 */
};

