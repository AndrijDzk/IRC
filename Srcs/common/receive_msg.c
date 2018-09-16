/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 12:34:35 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 13:45:44 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <stdlib.h>

#include "common.h"

static char		check_msg_header(t_msg_hdr *header)
{
	if (header->magic1 != TRANSFER_MAGIC)
		return (0);
	else if (header->msg_size == 0)
		return (0);
	else if (header->magic2 != TRANSFER_MAGIC)
		return (0);
	else
		return (1);
}

static int		read_header(int sckt, t_msg_hdr *header)
{
	ssize_t		ret;

	ret = recv(sckt, header, sizeof(*header), 0);
	if (ret == 0)
		return (EOF);
	if (ret < 0 || check_msg_header(header) == 0)
		return (WTF);
	return (OK);
}

static int		read_message(int sckt, t_msg *msg)
{
	ssize_t		ret;

	msg->data = malloc(msg->size);
	ret = recv(sckt, msg->data, msg->size, 0);
	if (ret <= 0)
	{
		free(msg->data);
		msg->data = NULL;
		if (ret == 0)
			return (EOF);
		return (WTF);
	}
	else
	{
		msg->size = (size_t)ret;
		return (OK);
	}
}

int				receive_msg(int sckt, t_msg *msg)
{
	ssize_t		ret;
	t_msg_hdr	header;

	if (msg == NULL)
		return (NO_MESSAGE);
	if ((ret = read_header(sckt, &header)) != OK)
		return ((int)ret);
	msg->size = header.msg_size;
	return (read_message(sckt, msg));
}
