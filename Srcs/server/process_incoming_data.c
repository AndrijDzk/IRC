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

static void join_client_msgs(t_list **readbuffs)
{
	char	*data_tmp;
	t_list	*node_tmp;

	while (readbuffs && *readbuffs && (*readbuffs)->next)
	{
		data_tmp = ft_strjoin((*readbuffs)->data, (*readbuffs)->next->data);
		node_tmp = (*readbuffs)->next;
		(*readbuffs)->next = (*readbuffs)->next->next;
		free(node_tmp->data);
		node_tmp->data = NULL;
		node_tmp->size = 0;
		free(node_tmp);
		free((*readbuffs)->data);
		(*readbuffs)->data = data_tmp;
		(*readbuffs)->size = ft_strlen((*readbuffs)->data);
	}
}

static int	forward_message(int sckt, t_clients_db *clients)
{
	int			i;
	char		*msg;
	char		*tmp;
	t_list		**receiver;

	if (sckt < 0 || sckt > FD_SETSIZE)
		return (1);
	tmp = ft_itoa(sckt);
	msg = ft_strjoin(tmp, ": ");
	free(tmp);
	tmp = msg;
	msg = ft_strjoin(msg, (clients->readbuffs)[sckt]->data);
	free(tmp);
	i = 0;
	while (i < FD_SETSIZE)
	{
		if (FD_ISSET(i, &(clients->sockets)) && i != sckt)
		{
			receiver = &((clients->writebuffs)[i]);
			t_list_push_back(receiver, ft_strdup(msg), ft_strlen(msg));
		}
		i++;
	}
	free(msg);
	return (0);
}

static int	proceed_input(int sckt, t_clients_db *clients,
							fd_set *dscn, int *res)
{
	t_list		**curr_rb;
	t_list		**curr_wb;

	if (sckt < 0 || sckt > FD_SETSIZE)
		return (1);
	curr_rb = &((clients->readbuffs)[sckt]);
	curr_wb = &((clients->writebuffs)[sckt]);
	join_client_msgs(curr_rb);
	change_res((*curr_rb)->data, res);
	ft_printf("%s: %s\n", clients->names[sckt], (*curr_rb)->data);
	forward_message(sckt, clients);
	if (ft_strcmp((*curr_rb)->data, "dcn\n") == 0 && res == 0)
		FD_SET(sckt, dscn);
	t_list_clear(curr_rb);
	return (0);
}

int			process_incoming_data(t_clients_db *clients, fd_set *dscn)
{
	int			res;
	int			i;

	FD_ZERO(dscn);
	res = 0;
	i = 0;
	while (i < FD_SETSIZE)
	{
		if (clients->readbuffs[i])
				proceed_input(i, clients, dscn, &res);
		i++;
	}
	return (res);
}
