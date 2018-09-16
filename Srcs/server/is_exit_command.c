/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_exit_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 10:58:33 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 10:58:33 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

enum e_is_ret			is_exit_command(char *message, size_t len)
{
	size_t		exit_len;
	size_t		cmp_len;

	exit_len = ft_strlen(CLIENT_EXIT);
	if (len < exit_len)
		cmp_len = len;
	else
		cmp_len = exit_len;
	if (ft_strncmp(message, CLIENT_EXIT, cmp_len) == 0)
	{
		if (len < exit_len)
			return (Maybe);
		else
			return (Is);
	}
	return (Isnt);
}
