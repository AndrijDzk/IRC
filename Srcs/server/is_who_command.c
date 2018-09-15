/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_who_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 14:47:03 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/15 14:47:03 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

enum e_is_ret			is_who_command(char *message, size_t len)
{
	size_t		who_len;
	size_t		cmp_len;

	who_len = ft_strlen(WHO);
	if (len < who_len)
		cmp_len = len;
	else
		cmp_len = who_len;
	if (ft_strncmp(message, WHO, cmp_len) == 0)
	{
		if (len < who_len || ft_strchr(message, '\n') == NULL)
			return (Maybe);
		else
			return (Is);
	}
	return (Isnt);
}
