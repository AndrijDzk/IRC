/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_necessary_sockets.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 14:32:29 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/11 14:37:19 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

t_sock_arr		choose_necessary_sockets(t_server *server)
{
	t_sock_arr		res;
	int				i;

	res.server = server->socket;
	res.read = server->clients.sockets;
	FD_ZERO(&(res.write));
	FD_ZERO(&(res.error));
	i = 0;
	while (i < FD_SETSIZE)
	{
		if (server->clients.writebuffs[i])
			FD_SET(i, &(res.write));
		i++;
	}
	return (res);
}
