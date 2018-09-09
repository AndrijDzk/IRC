/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:08:15 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/09 12:52:59 by adzikovs         ###   ########.fr       */
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

int				start_server(t_args *args, t_server *server)
{
	create_main_socket(args, server);
	FD_ZERO(&(server->clients));
	server->connections_am = 0;
	server->channels = NULL;
	return (0);
}
