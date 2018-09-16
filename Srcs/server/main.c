/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:01:39 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 12:40:35 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <unistd.h>

#include "libft.h"

void			close_all_sockets(fd_set *clients)
{
	int		i;

	i = 0;
	while (i < FD_SETSIZE)
	{
		if (FD_ISSET(i, clients))
			close(i);
		i++;
	}
}

static void		tick(t_server *server)
{
	t_sock_arr		ready_sockets;
	int				ret;

	ready_sockets = choose_necessary_sockets(server);
	examine_sockets(&ready_sockets);
	read_incoming_data(server, &(ready_sockets.read));
	ret = process_incoming_data(server);
	send_data_to_clients(&(server->clients), ready_sockets.write);
	disconnect_clients(server, &(ready_sockets.error));
	if (ret == EXIT)
	{
		close_all_sockets(&(server->clients.sockets));
		close(server->socket);
		exit(0);
	}
}

int				main(int arc, char **argv)
{
	t_args			args;
	t_server		server;

	args = parse_args(arc, argv);
	if (start_server(&args, &server))
		return (0);
	while (1)
		tick(&server);
}
