/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 11:10:58 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/16 09:39:06 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include "libft.h"

typedef enum e_is_ret	(*t_is_fp)(char *, size_t);

enum e_is_ret			is_nick_command(char *message, size_t len)
{
	size_t		nick_len;
	size_t		cmp_len;

	nick_len = ft_strlen(NICK);
	if (len < nick_len)
		cmp_len = len;
	else
		cmp_len = nick_len;
	if (ft_strncmp(message, NICK, cmp_len) == 0)
	{
		if (len < nick_len || ft_strchr(message, '\n') == NULL)
			return (Maybe);
		else
			return (Is);
	}
	return (Isnt);
}

enum e_is_ret			is_join_command(char *message, size_t len)
{
	size_t		join_len;
	size_t		cmp_len;

	join_len = ft_strlen(JOIN);
	if (len < join_len)
		cmp_len = len;
	else
		cmp_len = join_len;
	if (ft_strncmp(message, JOIN, cmp_len) == 0)
	{
		if (len < join_len || ft_strchr(message, '\n') == NULL)
			return (Maybe);
		else
			return (Is);
	}
	return (Isnt);
}

static void				init_arrays(t_is_fp *is_f_array, enum e_cl_comm *rets)
{
	is_f_array[COMMAND_NICK] = &is_nick_command;
	rets[COMMAND_NICK] = Nick;
	is_f_array[COMMAND_JOIN] = &is_join_command;
	rets[COMMAND_JOIN] = Join;
	is_f_array[COMMAND_WHO] = &is_who_command;
	rets[COMMAND_WHO] = Who;
	is_f_array[COMMAND_LEAVE] = &is_leave_command;
	rets[COMMAND_LEAVE] = Leave;
	is_f_array[COMMAND_MSG] = &is_msg_command;
	rets[COMMAND_MSG] = Msg;
	is_f_array[COMMAND_EXIT] = &is_exit_command;
	rets[COMMAND_EXIT] = Exit;
}

enum e_cl_comm			is_command(char *message)
{
	t_is_fp			is_f_array[COMMANDS_AM];
	enum e_cl_comm	rets[COMMANDS_AM];
	size_t			len;
	enum e_is_ret	ret;
	size_t			i;

	init_arrays(is_f_array, rets);
	len = ft_strlen(message);
	if (len == 0)
		return (Incomplete);
	i = 0;
	while (i < COMMANDS_AM)
	{
		ret = (*is_f_array[i])(message, len);
		if (ret == Is)
			return (rets[i]);
		else if (ret == Maybe)
			return (Incomplete);
		i++;
	}
	if (ft_strchr(message, '\n'))
		return (Text);
	return (Incomplete);
}
