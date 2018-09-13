/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 12:28:39 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/13 14:58:00 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

# include <stdint.h>
# include <sys/resource.h>
# include <netdb.h>

# include "libft.h"

# define ARGS_AM 1
# define ARG_PORT 1

# define COMMANDS_AM 1
# define COMMAND_NICK 0

# define NICK "/nick"

enum						e_is_ret {Is = 0, Isnt = 1, Maybe = 2};

enum						e_cl_comm {Text = 0, Incomplete = 1, Nick = 2};

typedef struct				s_args
{
	uint16_t				port;
}							t_args;

typedef struct				s_sock_arr
{
	int						server;
	fd_set					read;
	fd_set					write;
	fd_set					error;
}							t_sock_arr;

typedef struct				s_channel
{
	char					*name;
	fd_set					users;
}							t_channel;

typedef struct				s_clients_db
{
	fd_set					sockets;
	char					*names[FD_SETSIZE];
	char					*readbuffs[FD_SETSIZE][2];
	t_list					*writebuffs[FD_SETSIZE];
}							t_clients_db;

typedef struct				s_server
{
	int						socket;
	uint16_t				port;
	t_clients_db			clients;
	int						connections_am;
	t_list					*channels;
}							t_server;

typedef struct				s_connection
{
	int						socket;
	struct sockaddr_in		s_addr;
}							t_connection;

#endif
