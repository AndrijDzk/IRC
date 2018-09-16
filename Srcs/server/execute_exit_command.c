/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 11:01:13 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 11:01:13 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			execute_exit_command(t_server *srv, int sckt)
{
	t_channel	*curr_channel;

	if (sckt < 0 || sckt >= FD_SETSIZE)
		return (1);
	curr_channel = srv->clients.channels[sckt];
	if (curr_channel != NULL)
		FD_CLR(sckt, &(curr_channel->users));
	return (disconnect_client(&(srv->clients), sckt));
}
