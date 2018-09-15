/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:08:15 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/15 11:44:21 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <netdb.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>

#include "typedefs.h"

static void		create_main_socket(t_args *args, t_server *server)
{
	struct protoent		*pe;
	struct sockaddr_in	sin;

	pe = getprotobyname("tcp");
	server->socket = socket(PF_INET, SOCK_STREAM, pe->p_proto);
	server->port = args->port;
	sin.sin_family = PF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(server->port);
	if (bind(server->socket, (struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
		close(server->socket);
		exit(1);
	}
	if (listen(server->socket, 42) < 0)
	{
		close(server->socket);
		exit(1);
	}
}

static void		clients_db_init(t_server *server)
{
	FD_ZERO(&(server->clients.sockets));
	ft_bzero(server->clients.names,
				sizeof(*(server->clients.names)) * FD_SETSIZE);
	ft_bzero(server->clients.readbuffs,
				sizeof(*(server->clients.readbuffs)) * FD_SETSIZE * 2);
	ft_bzero(server->clients.writebuffs,
				sizeof(*(server->clients.writebuffs)) * FD_SETSIZE);
	ft_bzero(server->clients.channels,
				sizeof(*(server->clients.channels)) * FD_SETSIZE);
}

static void		channels_init(t_server *server)
{
	t_channel	*general;
	size_t		size;

	size = sizeof(*general);
	general = (t_channel*)malloc(size);
	general->name = ft_strdup("General");
	FD_ZERO(&(general->users));
	t_list_push_back(&(server->channels), general, size);
}

int				start_server(t_args *args, t_server *server)
{
	size_t		size;

	size = sizeof(*(server->clients.readbuffs));
	create_main_socket(args, server);
	clients_db_init(server);
	server->connections_am = 0;
	channels_init(server);
	return (0);
}
