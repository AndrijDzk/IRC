/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:01:39 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/08 15:43:47 by adzikovs         ###   ########.fr       */
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

fd_set			my_fd_set(int fd, fd_set set)
{
	FD_SET(fd, &set);
	return (set);
}

static void		tick(t_server *server)
{
	fd_set			read_ready;
	fd_set			disconnect;
	int				ret;

	read_ready = examine_sockets(my_fd_set(server->socket, server->clients));
	ret = process_incoming_data(server, &read_ready, &disconnect);
	disconnect_clients(server, &disconnect);
	if (ret == 1)
	{
		close_all_sockets(&(server->clients));
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
