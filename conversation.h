/* conversation.h
 * Routines for building lists of packets that are part of a "conversation"
 *
 * $Id: conversation.h,v 1.6 2000/08/07 03:20:20 guy Exp $
 *
 * Ethereal - Network traffic analyzer
 * By Gerald Combs <gerald@zing.org>
 * Copyright 1998 Gerald Combs
 *
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef __CONVERSATION_H__
#define __CONVERSATION_H__

#include "packet.h"		/* for conversation dissector type */
/*
 * Data structure representing a conversation.
 */
typedef struct conversation {
	struct conversation *next;	/* pointer to next conversation on hash chain */
	guint32	index;	/* unique ID for conversation */
	void	*data;	/* data our client can associate with a conversation */
	gboolean is_old_dissector;	/* XXX - nuke when everybody tvbuffified */
	union {
		old_dissector_t	old;
		dissector_t	new;
	} dissector; 			/* protocol dissector client can associate with conversation */
} conversation_t;

extern void conversation_init(void);
conversation_t *conversation_new(address *src, address *dst, port_type ptype,
    guint32 src_port, guint32 dst_port, void *data);
conversation_t *find_conversation(address *src, address *dst, port_type ptype,
    guint32 src_port, guint32 dst_port);

gboolean
old_try_conversation_dissector(address *src, address *dst, port_type ptype,
    guint32 src_port, guint32 dst_port, const u_char *pd, int offset,
    frame_data *fd, proto_tree *tree);
gboolean
try_conversation_dissector(address *src, address *dst, port_type ptype,
    guint32 src_port, guint32 dst_port, tvbuff_t *tvb, packet_info *pinfo,
    proto_tree *tree);

#endif /* conversation.h */
