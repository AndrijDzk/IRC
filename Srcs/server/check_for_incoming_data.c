/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_incoming_data.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 15:22:21 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/08 14:23:18 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netdb.h>
#include <sys/select.h>
#include <stdlib.h>

#include <stdio.h>

#include "server.h"

int			check_for_incoming_data(fd_set *clients)
{
	int				ret;
	struct timeval	wait_time;

	wait_time.tv_sec = 10;
	wait_time.tv_usec = 0;
	ret = (select(FD_SETSIZE, clients, NULL, NULL, &wait_time));
	if (ret < 0)
		perror("Read check");
	return (ret);
}
