/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_incoming_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:59:24 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/15 12:15:31 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "server.h"
#include "common.h"

#include "libft.h"

static void	join_client_msgs(char **readbuffs)
{
	char	*data_tmp;

	if (readbuffs[0] && readbuffs[1])
	{
		data_tmp = ft_strjoin(readbuffs[0], readbuffs[1]);
		free(readbuffs[0]);
		readbuffs[0] = data_tmp;
		free(readbuffs[1]);
		readbuffs[1] = NULL;
	}
	else if (readbuffs[1])
	{
		readbuffs[0] = readbuffs[1];
		readbuffs[1] = NULL;
	}
}

static int	forward_message(int sckt, t_clients_db *clients)
{
	int			i;
	char		*msg;
	char		*tmp;
	t_list		**receiver;
	fd_set		*clients_in_the_same_channel;

	if (sckt < 0 || sckt > FD_SETSIZE || (clients->channels)[sckt] == NULL)
		return (1);
	clients_in_the_same_channel = &((clients->channels)[sckt]->users);
	msg = ft_strjoin(clients->names[sckt], ": ");
	tmp = msg;
	msg = ft_strjoin(msg, (clients->readbuffs)[sckt][0]);
	free(tmp);
	i = 0;
	while (i < FD_SETSIZE)
	{
		if (FD_ISSET(i, clients_in_the_same_channel) && i != sckt)
		{
			receiver = &((clients->writebuffs)[i]);
			t_list_push_back(receiver, ft_strdup(msg), ft_strlen(msg));
		}
		i++;
	}
	free(msg);
	return (0);
}

static int	proceed_input(int sckt, t_server *server)
{
	char				*curr_rb;
	enum e_cl_comm		comm_type;

	if (sckt < 0 || sckt > FD_SETSIZE)
		return (1);
	join_client_msgs(server->clients.readbuffs[sckt]);
	curr_rb = (server->clients.readbuffs)[sckt][0];
	comm_type = is_command(curr_rb);
	if (comm_type == Text)
	{
		ft_printf("%s: %s", server->clients.names[sckt], curr_rb);
		forward_message(sckt, &(server->clients));
	}
	else if (comm_type != Incomplete)
		execute_client_command(server, comm_type, sckt);
	remove_processed_data(comm_type, &(server->clients), sckt);
	return (0);
}

int			process_incoming_data(t_server *server)
{
	int			res;
	int			i;

	res = OK;
	if (process_server_stdin(server) == EXIT)
		res = EXIT;
	i = 0;
	while (i < FD_SETSIZE)
	{
		if (server->clients.readbuffs[i][1])
			proceed_input(i, server);
		i++;
	}
	return (res);
}
