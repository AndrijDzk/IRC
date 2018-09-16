/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_msg_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:38:17 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 09:33:41 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

static enum e_is_ret	check_params(char *message, size_t pos)
{
	size_t		len;

	len = ft_strlen(message);
	if (pos >= len)
		return (Isnt);
	while (message[pos] == ' ')
		pos++;
	while (message[pos] != ' ' && message[pos] == 0 && message[pos] == '\n')
		pos++;
	if (message[pos] == 0 || message[pos] == '\n')
		return (Isnt);
	while (message[pos] == ' ')
		pos++;
	if (message[pos] == 0 || message[pos] == '\n')
		return (Isnt);
	return (Is);
}

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
			return (check_params(message, msg_len));
	}
	return (Isnt);
}
