/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accept_incoming_connection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:25:13 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/08 15:20:25 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include <stdlib.h>

#include <stdio.h>

#include "typedefs.h"

t_connection		accept_incoming_connection(t_server *server)
{
	t_connection	res;
	socklen_t		s_addr_len;

	s_addr_len = sizeof(res.s_addr);
	res.socket = accept(server->socket,
						(struct sockaddr*)&(res.s_addr),
						&s_addr_len);
	FD_SET(res.socket, &(server->clients));
	server->connections_am++;
	return (res);
}