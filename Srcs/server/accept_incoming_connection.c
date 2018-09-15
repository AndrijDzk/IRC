/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accept_incoming_connection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:25:13 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/15 11:56:48 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "typedefs.h"

static t_connection		save_client(t_connection res, t_server *server)
{
	t_channel		*general;

	if (res.socket < 0)
		return (res);
	if (server->channels == NULL)
	{
		close(res.socket);
		ft_printf("%$Cannot connect client - there is no channels!", 2);
		res.socket = -1;
		return (res);
	}
	general = server->channels->data;
	FD_SET(res.socket, &(server->clients.sockets));
	server->clients.names[res.socket] = ft_itoa(res.socket);
	(server->clients.channels)[res.socket] = general;
	FD_SET(res.socket, &(general->users));
	server->connections_am++;
	return (res);
}

t_connection			accept_incoming_connection(t_server *server)
{
	t_connection	res;
	socklen_t		s_addr_len;

	s_addr_len = sizeof(res.s_addr);
	res.socket = accept(server->socket,
						(struct sockaddr*)&(res.s_addr),
						&s_addr_len);
	return (save_client(res, server));
}
