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
	free(clients->names[id]);
	clients->names[id] = NULL;
	t_list_clear(&(clients->readbuffs[id]));
	t_list_clear(&(clients->writebuffs[id]));
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
