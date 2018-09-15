/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_who_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 14:49:09 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/15 14:49:41 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

int			execute_who_command(t_server *srv, int sckt)
{
	t_channel	*curr_channel;
	t_list		**curr_writebuff;
	size_t		len;
	char		*name;
	size_t		i;

	if (sckt < 0 || sckt >= FD_SETSIZE)
		return (1);
	curr_channel = srv->clients.channels[sckt];
	if (curr_channel == NULL || curr_channel->name == NULL)
		return (1);
	curr_writebuff = &(srv->clients.writebuffs[sckt]);
	len = ft_strlen("Users in channel ");
	t_list_push_back(curr_writebuff, ft_strdup("Users in channel "), len);
	len = ft_strlen(curr_channel->name);
	t_list_push_back(curr_writebuff, ft_strdup(curr_channel->name), len);
	len = ft_strlen(":\n");
	t_list_push_back(curr_writebuff, ft_strdup(":\n"), len);
	if (curr_channel)
	{
		i = 0;
		while (i < FD_SETSIZE)
		{
			if (FD_ISSET(i, &(curr_channel->users)))
			{
				name = ft_strjoin(srv->clients.names[i], "\n");
				t_list_push_back(curr_writebuff, name, ft_strlen(name));
			}
			i++;
		}
	}
	return (0);
}
