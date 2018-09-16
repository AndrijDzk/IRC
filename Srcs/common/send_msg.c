/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 11:05:54 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 13:16:46 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <errno.h>

#include "common.h"

int		send_msg(int sckt, t_msg *msg)
{
	ssize_t		ret;
	t_msg_hdr	header;

	if (msg == NULL || msg->size == 0)
		return (NO_MESSAGE);
	header.magic1 = TRANSFER_MAGIC;
	header.msg_size = msg->size;
	header.magic2 = TRANSFER_MAGIC;
	ret = send(sckt, &header, sizeof(header), 0);
	if (ret <= 0)
	{
		if (ret < 0 && errno == ECONNRESET)
			return (EOF);
		return (WTF);
	}
	ret = send(sckt, msg->data, msg->size, 0);
	if (ret <= 0)
	{
		if (ret < 0 && errno == ECONNRESET)
			return (EOF);
		return (WTF);
	}
	else
		return (OK);
}
