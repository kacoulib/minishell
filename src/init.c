/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 14:02:20 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/13 14:02:31 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*
// **	0 = echo
// **	1 = cd
// **	2 = setenv
// **	3 = unsetenv
// **	4 = env
// **	5 = exit
// */

// char		*int_flags_or_get_flag(int id)
// {
// 	static char		*flags[15];

// 	flags[id] = "echo";

// 	return (flags[id]);
// }

char		*check_and_get_flag(char *builtin, char **av)
{
	char	*tmp;

	if (ft_strcmp(builtin, "echo") == 0)
		tmp = ft_strdup(" n e E --help --version ");
	else
		return (NULL);
	return (get_glags(tmp, av, builtin));
}
