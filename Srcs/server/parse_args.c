/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adzikovs <adzikovs@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 12:27:44 by adzikovs          #+#    #+#             */
/*   Updated: 2018/09/07 15:36:45 by adzikovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>

#include "libft.h"

#include "typedefs.h"

t_args	parse_args(int argc, char **argv)
{
	t_args	res;
	int		port_tmp;

	if (argc != (ARGS_AM + 1))
		exit(1);
	port_tmp = ft_atoi(argv[ARG_PORT]);
	if (port_tmp <= 0 || port_tmp > USHRT_MAX)
		exit(1);
	res.port = (uint16_t)port_tmp;
	return (res);
}
