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
#include <typedefs.h>

int		examine_sockets(t_sock_arr *sockets)
{
	int				ret;
	struct timeval	wait_time;

	wait_time.tv_sec = 10;
	wait_time.tv_usec = 0;
	FD_SET(sockets->server, &(sockets->read));
	ret = select(FD_SETSIZE, &(sockets->read),
				&(sockets->write), &(sockets->error), &wait_time);
	return (ret);
}
