/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   examine_sockets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 15:29:42 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/08 15:34:01 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include <stdlib.h>

fd_set		examine_sockets(fd_set sockets)
{
	int				ret;
	struct timeval	wait_time;

	wait_time.tv_sec = 10;
	wait_time.tv_usec = 0;
	ret = select(FD_SETSIZE, &sockets, NULL, NULL, &wait_time);
	if (ret <= 0)
		FD_ZERO(&sockets);
	return (sockets);
}

