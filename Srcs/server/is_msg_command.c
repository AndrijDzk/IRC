/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_msg_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:38:17 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/15 15:38:17 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

enum e_is_ret			is_msg_command(char *message, size_t len)
{
	size_t		msg_len;
	size_t		cmp_len;

	msg_len = ft_strlen(MSG);
	if (len < msg_len)
		cmp_len = len;
	else
		cmp_len = msg_len;
	if (ft_strncmp(message, MSG, cmp_len) == 0)
	{
		if (len < msg_len || ft_strchr(message, '\n') == NULL)
			return (Maybe);
		else
			return (Is);
	}
	return (Isnt);
}
