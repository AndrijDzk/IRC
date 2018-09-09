/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 12:34:35 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/08 13:13:16 by adzikovs         ###   ########.fr       */
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

int				receive_msg(int sckt, t_msg *msg)
{
	ssize_t		ret;
	t_msg_hdr	header;

	if (msg == NULL)
		return (-1);
	ret = recv(sckt, &header, sizeof(header), 0);
	if (ret <= 0 || check_msg_header(&header) == 0)
		return (-1);
	msg->size = header.msg_size;
	msg->data = malloc(msg->size);
	ret = recv(sckt, msg->data, msg->size, 0);
	if (ret <= 0)
	{
		free(msg->data);
		msg->data = NULL;
		return (-1);
	}
	else
	{
		msg->size = (size_t)ret;
		return (0);
	}
}
