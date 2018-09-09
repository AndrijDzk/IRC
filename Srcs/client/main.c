/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:00:21 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/08 15:20:25 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#include "common.h"
#include "libft.h"

int		main(int argc, char **argv)
{
	int					sckt;
	struct sockaddr_in	sout;
	ssize_t				ret;
	t_msg				msg;
	char				buff[10];

	if (argc != 3 || ft_atoi(argv[2]) <= 0)
		return (0);
	ft_bzero(buff, 10);
	msg.data = buff;
	msg.size = 10;
	sckt = socket(PF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto);
	sout.sin_family = PF_INET;
	sout.sin_addr.s_addr = inet_addr(argv[1]);
	sout.sin_port = htons(ft_atoi(argv[2]));
	if (connect(sckt, (const struct sockaddr*)&sout, sizeof(sout)))
	{
		close(sckt);
		return (1);
	}
	while ((ret = read(0, buff, 10)) > 0)
	{
		msg.size = (size_t)ret;
		send_msg(sckt, &msg);
		if (ft_strcmp(buff, "dcn\n") == 0 ||
			ft_strcmp(buff, "exit\n") == 0)
			break;
		ft_bzero(buff, (size_t)ret);
	}
	close(sckt);
	return (0);
}
