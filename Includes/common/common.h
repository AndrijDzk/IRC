/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 10:59:31 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/08 13:05:01 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# define TRANSFER_MAGIC -42

# include <unistd.h>

typedef struct	s_msg_hdr
{
	int			magic1;
	size_t		msg_size;
	int			magic2;
}				t_msg_hdr;

typedef struct	s_msg
{
	size_t		size;
	void		*data;
}				t_msg;

int				send_msg(int sckt, t_msg *msg);

int				receive_msg(int sck, t_msg *msg);

#endif
