/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_incoming_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 11:12:03 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/11 11:18:03 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "server.h"
#include "common.h"

#include "libft.h"

static void	save_input(int sckt, t_msg *msg, t_clients_db *clients)
{
	t_list_push_back(&(clients->readbuffs[sckt]), msg->data, msg->size);
	msg->data = NULL;
	msg->size = 0;
}

int			read_incoming_data(t_server *server, fd_set *rd)
{
	int			i;
	int			ret;
	t_msg		msg;

	if (FD_ISSET(server->socket, rd))
	{
		accept_incoming_connection(server);
		FD_CLR(server->socket, rd);
	}
	i = 0;
	while (i < FD_SETSIZE)
	{
		if (FD_ISSET(i, rd))
		{
			if ((ret = receive_msg(i, &msg)) == 0)
				save_input(i, &msg, &(server->clients));
		}
		i++;
	}
	return (0);
}
