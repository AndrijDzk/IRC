/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_processed_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:10:03 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/13 14:55:01 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "typedefs.h"

static void		remove_all_data(t_clients_db *clients, int sckt)
{
	if (clients->readbuffs[sckt][0])
	{
		free(clients->readbuffs[sckt][0]);
		clients->readbuffs[sckt][0] = NULL;
	}
}

static void		remove_to_nl(t_clients_db *clients, int sckt)
{
	char		*nl_pos;
	size_t		i;
	char		*curr_rb;

	curr_rb = (clients->readbuffs)[sckt][0];
	if (curr_rb)
	{
		nl_pos = ft_strchr(curr_rb, '\n');
		if (nl_pos && *(nl_pos + 1))
		{
			nl_pos++;
			i = 0;
			while (*nl_pos)
			{
				curr_rb[i] = *nl_pos;
				i++;
				nl_pos++;
			}
			curr_rb[i] = 0;
		}
		else
			remove_all_data(clients, sckt);
	}
}

void			remove_processed_data(enum e_cl_comm type,
									t_clients_db *clients, int sckt)
{
	if ((clients->readbuffs)[sckt][0])
	{
		if (type != Incomplete)
			remove_to_nl(clients, sckt);
	}
}
