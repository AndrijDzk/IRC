/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_incoming_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 11:12:03 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 13:36:01 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "server.h"
#include "common.h"

#include "libft.h"

static void	save_input(int sckt, t_msg *msg, t_clients_db *clients)
{
	if ((clients->readbuffs)[sckt][1] == NULL)
	{
		(clients->readbuffs)[sckt][1] = (char*)malloc(msg->size + 1);
		ft_strncpy((clients->readbuffs)[sckt][1], msg->data, msg->size);
		free(msg->data);
		msg->data = NULL;
		msg->size = 0;
	}
	else
	{
		ft_printf("%$Cannot save message from client %d - "
			"buffer is busy", 2, sckt);
		free(msg->data);
		msg->data = NULL;
		msg->size = 0;
	}
}

static void	save_server_stdin(t_clients_db *clients)
{
	char	**server_stdin_buff;
	int		ret;

	if (clients == NULL)
		return ;
	server_stdin_buff = &((clients->readbuffs)[0][0]);
	if (*server_stdin_buff == NULL)
	{
		*server_stdin_buff = (char*)malloc(20);
		if ((ret = read(0, *server_stdin_buff, 20)) <= 0)
		{
			free(*server_stdin_buff);
			*server_stdin_buff = NULL;
		}
		if (ret >= 20)
			ret = 19;
		(*server_stdin_buff)[ret] = 0;
	}
}

static void	read_data_from_clients(t_server *server, fd_set *rd)
{
	int			i;
	int			ret;
	t_msg		msg;

	i = 0;
	while (i < FD_SETSIZE)
	{
		if (FD_ISSET(i, rd))
		{
			if ((ret = receive_msg(i, &msg)) == OK)
				save_input(i, &msg, &(server->clients));
			else if (ret == EOF)
				disconnect_client(&(server->clients), i);
		}
		i++;
	}
}

int			read_incoming_data(t_server *server, fd_set *rd)
{
	if (FD_ISSET(server->socket, rd))
	{
		accept_incoming_connection(server);
		FD_CLR(server->socket, rd);
	}
	if (FD_ISSET(0, rd))
	{
		save_server_stdin(&(server->clients));
		FD_CLR(0, rd);
	}
	read_data_from_clients(server, rd);
	return (0);
}
