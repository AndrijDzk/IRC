/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:04:49 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 11:00:55 by adzikovs         ###   ########.fr       */
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

int				process_incoming_data(t_server *server);

int				process_server_stdin(t_server *server);

int				send_data_to_clients(t_clients_db *clients, fd_set write_ready);

int				disconnect_client(t_clients_db *clients, int id);

void			disconnect_clients(t_server *server, fd_set *dscn);

enum e_cl_comm	is_command(char *message);

enum e_is_ret	is_who_command(char *message, size_t len);

enum e_is_ret	is_leave_command(char *message, size_t len);

enum e_is_ret	is_msg_command(char *message, size_t len);

enum e_is_ret	is_exit_command(char *message, size_t len);

int				execute_client_command(t_server *srv,
										enum e_cl_comm type, int sckt);

int				execute_nick_command(t_server *srv, int sckt);

int				execute_join_command(t_server *srv, int sckt);

int				execute_leave_command(t_server *srv, int sckt);

int				execute_who_command(t_server *srv, int sckt);

int				execute_msg_command(t_server *srv, int sckt);

int				execute_exit_command(t_server *srv, int sckt);

void			remove_processed_data(enum e_cl_comm type,
										t_clients_db *clients, int sckt);

#endif
