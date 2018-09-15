/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_nick_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 13:40:03 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/13 13:45:26 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

static char	*get_nick_from_command(char *command)
{
	size_t		i;
	size_t		start;

	i = ft_strlen(NICK);
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

int			execute_nick_command(t_server *srv, int sckt)
{
	char	*new_nick;

	if (sckt < 0 || sckt >= FD_SETSIZE)
		return (1);
	new_nick = get_nick_from_command((srv->clients.readbuffs)[sckt][0]);
	if (new_nick && new_nick[0])
	{
		free((srv->clients.names)[sckt]);
		(srv->clients.names)[sckt] = new_nick;
	}
	return (0);
}
