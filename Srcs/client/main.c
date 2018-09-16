/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:00:21 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 13:45:44 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#include "common.h"
#include "client.h"
#include "libft.h"

int		connect_to_server(char *addr, char *port)
{
	struct sockaddr_in	sout;
	int					sckt;

	sckt = socket(PF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto);
	sout.sin_family = PF_INET;
	sout.sin_addr.s_addr = inet_addr(addr);
	sout.sin_port = htons(ft_atoi(port));
	if (connect(sckt, (const struct sockaddr*)&sout, sizeof(sout)))
	{
		close(sckt);
		return (-1);
	}
	return (sckt);
}

int		try_to_connect_to_server(int sckt, char *addr, char *port)
{
	t_msg				msg;

	msg.data = "/exit\n";
	msg.size = ft_strlen(msg.data);
	send_msg(sckt, &msg);
	if (sckt >= 0)
		close(sckt);
	sckt = connect_to_server(addr, port);
	if (sckt < 0)
		ft_printf("Failed to connect to server %s:%s", addr, port);
	return (sckt);
}

int		read_stdin(int *sckt)
{
	ssize_t				ret;
	t_msg				msg;
	char				buff[31];
	char				*args[2];

	ft_bzero(buff, 31);
	msg.data = buff;
	msg.size = 30;
	ret = read(0, buff, 30);
	msg.size = (size_t)ret;
	if (is_connect_command(buff, args))
	{
		*sckt = try_to_connect_to_server(*sckt, args[0], args[1]);
		if (*sckt < 0)
			return (-1);
		return (1);
	}
	if (*sckt < 0)
		return (-1);
	if (send_msg(*sckt, &msg))
		return (-1);
	if (ft_strncmp(buff, "/exit\n", 6) == 0)
		return (1);
	return (0);
}

int		read_serv(int sckt)
{
	t_msg				msg;

	if (sckt < 0)
		return (-1);
	if (receive_msg(sckt, &msg))
		return (-1);
	write(1, msg.data, msg.size);
	free(msg.data);
	return (0);
}

int		main(int argc, char **argv)
{
	int					sckt;
	fd_set				read_set;

	if (argc != 3 || ft_atoi(argv[2]) <= 0)
		return (0);
	sckt = connect_to_server(argv[1], argv[2]);
	while (1)
	{
		FD_ZERO(&read_set);
		FD_SET(0, &read_set);
		if (sckt >= 0)
			FD_SET(sckt, &read_set);
		if (select(FD_SETSIZE, &read_set, NULL, NULL, NULL) > 0)
		{
			if (FD_ISSET(0, &read_set) && read_stdin(&sckt) == 1)
				break ;
			if (FD_ISSET(sckt, &read_set))
				read_serv(sckt);
		}
	}
	close(sckt);
	return (0);
}
