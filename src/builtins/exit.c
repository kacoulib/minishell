/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 05:38:11 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/21 05:38:22 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				builtin_exit(char *av)
{
	int			i;

	i = -1;
	av = ft_strtrim(av);
	if (av && !ft_isdigit(av[0]))
		return (TRUE + set_errors(11, "exit", NULL));
	while (av && av[++i])
		if (!ft_isdigit(av[i]))
			return (TRUE + set_errors(12, "exit", NULL));
	exit(ft_atoi(av));
	return (TRUE);
}
