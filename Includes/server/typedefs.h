/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 12:28:39 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/09 12:52:59 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include <stdint.h>
# include <sys/resource.h>
# include <netdb.h>

#include "libft.h"

# define ARGS_AM 1
# define ARG_PORT 1

typedef struct				s_args
{
	uint16_t				port;
}							t_args;

typedef struct				s_channel
{
	char					*name;
	fd_set					users;
}							t_channel;

typedef struct				s_server
{
	int						socket;
	uint16_t				port;
	fd_set					clients;
	int						connections_am;
	t_list					*channels;
}							t_server;

typedef struct				s_connection
{
	int						socket;
	struct sockaddr_in		s_addr;
}							t_connection;

#endif
