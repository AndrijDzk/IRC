/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_leave_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:27:04 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/15 15:30:13 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

int					execute_leave_command(t_server *srv, int sckt)
{
	if (sckt < 0 || sckt >= FD_SETSIZE)
		return (1);
	if ((srv->clients.channels)[sckt])
		FD_CLR(sckt, &(srv->clients.channels[sckt]->users));
	srv->clients.channels[sckt] = NULL;
	return (0);
}
