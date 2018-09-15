/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_client_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 13:34:05 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/15 15:16:29 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

typedef int	(*t_cl_comm_fp)(t_server *, int);

static void	init_arrays(t_cl_comm_fp *funcs_array, enum e_cl_comm *ids)
{
	funcs_array[COMMAND_NICK] = &execute_nick_command;
	ids[COMMAND_NICK] = Nick;
	funcs_array[COMMAND_JOIN] = &execute_join_command;
	ids[COMMAND_JOIN] = Join;
	funcs_array[COMMAND_WHO] = &execute_who_command;
	ids[COMMAND_WHO] = Who;
	funcs_array[COMMAND_LEAVE] = &execute_leave_command;
	ids[COMMAND_LEAVE] = Leave;
}

int			execute_client_command(t_server *srv, enum e_cl_comm type, int sckt)
{
	t_cl_comm_fp		command_functions[COMMANDS_AM];
	enum e_cl_comm		command_ids[COMMANDS_AM];
	size_t				i;

	init_arrays(command_functions, command_ids);
	i = 0;
	while (i < COMMANDS_AM)
	{
		if (command_ids[i] == type)
			return ((*command_functions[i])(srv, sckt));
		i++;
	}
	return (-1);
}
