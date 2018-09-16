/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_msg_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 09:09:52 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 13:36:01 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

int				find_client_by_name(t_clients_db *clients, char *name)
{
	int			i;

	if (clients == NULL || name == NULL)
		return (-1);
	i = 0;
	while (i < FD_SETSIZE)
	{
		if (FD_ISSET(i, &(clients->sockets)) && clients->names[i] &&
			ft_strcmp(clients->names[i], name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int		get_nick_and_msg_pos(char *command, size_t *res)
{
	size_t		pos;

	if (command == NULL || res == NULL)
		return (1);
	pos = ft_strlen(MSG);
	if (pos >= ft_strlen(command))
		return (1);
	while (command[pos] == ' ')
		pos++;
	if (command[pos] == 0 || command[pos] == '\n')
		return (1);
	res[0] = pos;
	while (command[pos] != ' ' && command[pos] != 0 && command[pos] != '\n')
		pos++;
	if (command[pos] == 0 || command[pos] == '\n')
		return (1);
	while (command[pos] == ' ')
		pos++;
	if (command[pos] == 0 || command[pos] == '\n')
		return (1);
	res[1] = pos;
	return (0);
}

static int		get_nick_and_msg(char *command, char **res)
{
	size_t		positions[2];
	size_t		end;

	if (command == NULL || res == NULL)
		return (1);
	if (get_nick_and_msg_pos(command, positions) == 1)
		return (1);
	end = positions[1];
	while ((end - 1) >= positions[0] && command[end - 1] == ' ')
		end--;
	res[0] = ft_strndup(command + positions[0], end - positions[0]);
	res[1] = ft_strdup(command + positions[1]);
	return (0);
}

static void		send_private_msg(t_server *srv, int reciver_socket,
									char **params)
{
	char		*msg;
	char		*to_join[4];
	t_list		**writebuff;
	size_t		len;

	writebuff = &(srv->clients.writebuffs[reciver_socket]);
	to_join[0] = "Private message from ";
	to_join[1] = params[0];
	to_join[2] = ": ";
	to_join[3] = params[1];
	msg = ft_multistrjoin(to_join, 4);
	len = ft_strlen(msg);
	t_list_push_back(writebuff, msg, len);
	free(params[0]);
	free(params[1]);
}

int				execute_msg_command(t_server *srv, int sckt)
{
	char		*params[2];
	int			reciver_socket;

	if (sckt < 0 || sckt >= FD_SETSIZE)
		return (1);
	if (get_nick_and_msg(srv->clients.readbuffs[sckt][0], params))
		return (1);
	if ((reciver_socket = find_client_by_name(&(srv->clients), params[0])) < 0)
	{
		free(params[0]);
		free(params[1]);
		return (1);
	}
	send_private_msg(srv, reciver_socket, params);
	return (0);
}
