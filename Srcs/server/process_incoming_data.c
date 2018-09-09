/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_incoming_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 15:38:03 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/08 15:20:40 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "server.h"
#include "common.h"

#include "libft.h"

static void	change_res(char *buff, int *res)
{
	if (ft_strcmp(buff, "exit\n") == 0)
		*res = 1;
	if (ft_strcmp(buff, "conn\n") == 0 && *res == 0)
		*res = 2;
}

static void	proceed_input(int sckt, t_msg *msg, fd_set *dscn, int *res)
{
	change_res(msg->data, res);
	write(1, msg->data, msg->size);
	if (ft_strcmp(msg->data, "dcn\n") == 0 && res == 0)
		FD_SET(sckt, dscn);
	free(msg->data);
	msg->data = NULL;
	msg->size = 0;
}

int			process_incoming_data(t_server *server, fd_set *rd, fd_set *dscn)
{
	int			res;
	int			i;
	int			ret;
	t_msg		msg;

	FD_ZERO(dscn);
	if (FD_ISSET(server->socket, rd))
	{
		accept_incoming_connection(server);
		FD_CLR(server->socket, rd);
	}
	res = 0;
	i = 0;
	while (i < FD_SETSIZE)
	{
		if (FD_ISSET(i, rd))
		{
			if ((ret = receive_msg(i, &msg)) == 0)
				proceed_input(i, &msg, dscn, &res);
		}
		i++;
	}
	return (res);
}
