/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_connect_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 12:06:50 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 12:13:48 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define CONNECT "/connect "

char	*get_word(char *command, size_t *i)
{
	size_t		pos;

	while (command[*i] == ' ')
		(*i)++;
	if (command[*i] == 0 || command[*i] == '\n')
		return (NULL);
	pos = *i;
	while (command[*i] != ' ')
	{
		if (command[*i] == 0 || command[*i] == '\n')
			return (NULL);
		(*i)++;
	}
	return (ft_strndup(command + pos, *i - pos));
}

int		is_connect_command(char *command, char **res)
{
	size_t		i;

	if (command == NULL || res == NULL)
		return (0);
	i = ft_strlen(CONNECT);
	if (ft_strncmp(CONNECT, command, i))
		return (0);
	if ((res[0] = get_word(command, &i)) == NULL)
		return (0);
	if ((res[1] = get_word(command, &i)) == NULL)
	{
		free(res[0]);
		return (0);
	}
	return (1);
}
