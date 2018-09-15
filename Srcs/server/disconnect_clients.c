/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect_clients.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 10:23:29 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/08 10:26:42 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "typedefs.h"

static int		clear_client_data(t_clients_db *clients, int id)
{
	if (id < 0 || id >= FD_SETSIZE)
		return (1);
	FD_CLR(id, &(clients->sockets));
	if (clients->names[id])
	{
		free(clients->names[id]);
		clients->names[id] = NULL;
	}
	if (clients->readbuffs[id][0])
	{
		free(clients->readbuffs[id][0]);
		clients->readbuffs[id][0] = NULL;
	}
	if (clients->readbuffs[id][1])
	{
		free(clients->readbuffs[id][1]);
		clients->readbuffs[id][1] = NULL;
	}
	t_list_clear(&(clients->writebuffs[id]));
	if ((clients->channels)[id])
	{
		FD_CLR(id, &((clients->channels)[id]->users));
		(clients->channels)[id] = NULL;
	}
	return (0);
}

void			disconnect_clients(t_server *server, fd_set *dscn)
{
	int		i;

	i = 0;
	while (i < FD_SETSIZE)
	{
		if (FD_ISSET(i, dscn))
		{
			close(i);
			clear_client_data(&(server->clients), i);
			if (server->connections_am > 0)
				server->connections_am--;
			else
				ft_printf("%$Error: wrong connections amount!", 2);
		}
		i++;
	}
}
