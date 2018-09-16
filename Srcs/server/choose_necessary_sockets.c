/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_necessary_sockets.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 14:32:29 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 12:46:00 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

t_sock_arr		choose_necessary_sockets(t_server *server)
{
	t_sock_arr		res;
	int				i;

	res.server = server->socket;
	FD_COPY(&(server->clients.sockets), &(res.read));
	FD_ZERO(&(res.write));
	FD_ZERO(&(res.error));
	FD_SET(0, &(res.read));
	i = 0;
	while (i < FD_SETSIZE)
	{
		if (server->clients.writebuffs[i])
			FD_SET(i, &(res.write));
		i++;
	}
	return (res);
}
