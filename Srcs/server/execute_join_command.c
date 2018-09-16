/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_join_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 13:46:01 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/15 13:55:55 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

static t_channel	*find_channel_by_name(t_list *begin, char *name)
{
	t_channel	*tmp;

	while (begin)
	{
		tmp = begin->data;
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		begin = begin->next;
	}
	return (NULL);
}

static char			*get_name_from_command(char *command)
{
	size_t		i;
	size_t		start;

	i = ft_strlen(JOIN);
	if (i >= ft_strlen(command))
		return (NULL);
	start = i;
	while (command[i])
	{
		if (command[i] == '\n')
			return (ft_strndup(command + start, i - start));
		i++;
	}
	return (ft_strdup(command + start));
}

int					execute_join_command(t_server *srv, int sckt)
{
	char		*name;
	t_channel	*new_channel;

	if (sckt < 0 || sckt >= FD_SETSIZE)
		return (1);
	name = get_name_from_command((srv->clients.readbuffs)[sckt][0]);
	if (name && name[0])
	{
		new_channel = find_channel_by_name(srv->channels, name);
		if (new_channel == NULL)
			return (1);
		if ((srv->clients.channels)[sckt])
			FD_CLR(sckt, &(srv->clients.channels[sckt]->users));
		srv->clients.channels[sckt] = new_channel;
		FD_SET(sckt, &(new_channel->users));
	}
	return (0);
}
