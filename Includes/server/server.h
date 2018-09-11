/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:04:49 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/11 14:37:19 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_SERVER_H
# define CLIENT_SERVER_H

# include "typedefs.h"

t_args			parse_args(int argc, char **argv);

int				start_server(t_args *args, t_server *server);

t_sock_arr		choose_necessary_sockets(t_server *server);

int				examine_sockets(t_sock_arr *sockets);

int				read_incoming_data(t_server *srv, fd_set *rd);

t_connection	accept_incoming_connection(t_server *server);

int				process_incoming_data(t_clients_db *clients, fd_set *dscn);

int				send_data_to_clients(t_clients_db *clients, fd_set write_ready);

void			disconnect_clients(t_server *server, fd_set *dscn);

#endif
