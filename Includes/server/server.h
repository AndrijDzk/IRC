/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:04:49 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/08 15:39:56 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_SERVER_H
# define CLIENT_SERVER_H

# include "typedefs.h"

t_args			parse_args(int argc, char **argv);

int				start_server(t_args *args, t_server *server);

t_connection	accept_incoming_connection(t_server *server);

void			disconnect_clients(t_server *server, fd_set *dscn);

int				check_for_incoming_data(fd_set *clients);

int				process_incoming_data(t_server *srv, fd_set *rd, fd_set *dscn);

fd_set			examine_sockets(fd_set sockets);

#endif
