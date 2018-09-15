/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_leave_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:24:28 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/15 15:24:28 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

enum e_is_ret			is_leave_command(char *message, size_t len)
{
	size_t		leave_len;
	size_t		cmp_len;

	leave_len = ft_strlen(LEAVE);
	if (len < leave_len)
		cmp_len = len;
	else
		cmp_len = leave_len;
	if (ft_strncmp(message, LEAVE, cmp_len) == 0)
	{
		if (len < leave_len || ft_strchr(message, '\n') == NULL)
			return (Maybe);
		else
			return (Is);
	}
	return (Isnt);
}
