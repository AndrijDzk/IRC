/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_server_stdin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 12:59:31 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/15 13:43:22 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

int			create_channel(t_server *server, char *command)
{
	size_t		name_start;
	t_channel	*new_channel;

	name_start = ft_strlen(CC_COMMAND);
	if (name_start >= ft_strlen(command))
		return (1);
	new_channel = (t_channel*)malloc(sizeof(*new_channel));
	new_channel->name = ft_strdup(command + name_start);
	FD_ZERO(&(new_channel->users));
	t_list_push_back(&(server->channels), new_channel, sizeof(*new_channel));
	return (0);
}

int			process_server_stdin(t_server *server)
{
	char	**server_input;

	if ((server->clients.readbuffs)[0][1])
	{
		ft_printf("%$Junk in server_stdin readbuff!", 2);
		exit(0);
	}
	server_input = &(server->clients.readbuffs[0][0]);
	if (*server_input == NULL)
		return (0);
	if (ft_strcmp(*server_input, EXIT_COMMAND_LITERAL) == 0)
	{
		free(*server_input);
		*server_input = NULL;
		return (EXIT);
	}
	if (ft_strncmp(*server_input, CC_COMMAND, ft_strlen(CC_COMMAND)) == 0)
	{
		create_channel(server, *server_input);
		free(*server_input);
		*server_input = NULL;
		return (0);
	}
	return (0);
}
