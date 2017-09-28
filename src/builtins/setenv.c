/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 05:36:17 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/21 05:36:31 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** [builtin_setenv description]
**
** @param  env [an array of key pair vaule]
** @param  av     [the arguments]
** @return           [if the key dont exist it's create else it's update
** overwrite is != 0]
*/

int				builtin_setenv(t_list **env, char **av)
{
	int			i;
	t_list		*old;
	char		*key;
	char		*val;

	if (!av || !av[0] || !av[1] || av[2])
		return (set_errors(4, "setenv", NULL));
	key = av[0];
	val = av[1];
	i = -1;
	while (key[++i])
		if (!ft_isalnum(key[i]))
			return (set_errors(15, "setenv", NULL));
	i = -1;
	while (val[++i])
		if (!ft_isalnum(val[i]))
			return (set_errors(15, "setenv", NULL));
	if ((old = ft_getenv_from_list(env, av[0])))
		update_env(old, av[0], av[1]);
	else
		create_env(env, av[0], av[1]);
	return (1);
}
