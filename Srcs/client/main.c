/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:00:21 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/11 15:34:11 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#include "common.h"
#include "libft.h"

int		read_stdin(int sckt)
{
	ssize_t				ret;
	t_msg				msg;
	char				buff[10];

	msg.data = buff;
	msg.size = 10;
	ret = read(0, buff, 10);
	msg.size = (size_t)ret;
	if (send_msg(sckt, &msg))
		return (-1);
	if (ft_strncmp(buff, "dcn\n", 4) == 0 ||
		ft_strncmp(buff, "exit\n", 4) == 0)
		return (1);
	ft_bzero(buff, (size_t)ret);
	return (0);
}

int		read_serv(int sckt)
{
	t_msg				msg;

	if (receive_msg(sckt, &msg))
		return (-1);
	write(1, msg.data, msg.size);
	free(msg.data);
	return (0);
}

int		main(int argc, char **argv)
{
	int					sckt;
	struct sockaddr_in	sout;
	fd_set				read_set;

	if (argc != 3 || ft_atoi(argv[2]) <= 0)
		return (0);
	sckt = socket(PF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto);
	sout.sin_family = PF_INET;
	sout.sin_addr.s_addr = inet_addr(argv[1]);
	sout.sin_port = htons(ft_atoi(argv[2]));
	if (connect(sckt, (const struct sockaddr*)&sout, sizeof(sout)))
	{
		close(sckt);
		return (1);
	}
	while (1)
	{
		FD_ZERO(&read_set);
		FD_SET(0, &read_set);
		FD_SET(sckt, &read_set);
		if (select(FD_SETSIZE, &read_set, NULL, NULL, NULL) > 0)
		{
			if (FD_ISSET(0, &read_set) && read_stdin(sckt) == 1)
				break ;
			if (FD_ISSET(sckt, &read_set))
				read_serv(sckt);
		}
	}
	close(sckt);
	return (0);
}
