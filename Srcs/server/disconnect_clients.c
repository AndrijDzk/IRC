/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect_clients.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 10:23:29 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/08 10:26:42 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "typedefs.h"

void			disconnect_clients(t_server *server, fd_set *dscn)
{
	int		i;

	i = 0;
	while (i < FD_SETSIZE)
	{
		if (FD_ISSET(i, dscn))
		{
			close(i);
			FD_CLR(i, &(server->clients));
			server->connections_am--;
		}
		i++;
	}
}
