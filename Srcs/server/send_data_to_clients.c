/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_data_to_clients.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 14:40:20 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 13:19:13 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

#include "server.h"

static int	send_data_to_client(t_clients_db *clients, int id)
{
	t_list	*tmp;
	t_msg	msg;
	int		ret;

	tmp = (clients->writebuffs)[id];
	while (tmp)
	{
		msg.data = tmp->data;
		msg.size = tmp->size;
		if ((ret = send_msg(id, &msg)) != OK)
		{
			if (ret == EOF)
				disconnect_client(clients, id);
			return (-1);
		}
		tmp = tmp->next;
	}
	t_list_clear(clients->writebuffs + id);
	return (0);
}

int			send_data_to_clients(t_clients_db *clients, fd_set write_ready)
{
	int		i;

	i = 0;
	while (i < FD_SETSIZE)
	{
		if (clients->writebuffs[i] && FD_ISSET(i, &write_ready))
			send_data_to_client(clients, i);
		i++;
	}
	return (0);
}
