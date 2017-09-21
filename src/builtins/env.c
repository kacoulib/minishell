/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 05:35:14 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/21 05:35:26 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			builtin_env_extra(t_list **env, char **av)
{
	int				i;
	char			**tmp;

	i = get_args_limit(av) - 1;
	while (av[++i])
	{
		if (ft_indexof(av[i], '=') > 0)
		{
			tmp = ft_strsplit(av[i], '=');
			builtin_setenv(env, tmp);
			free_arr(tmp);
		}
	}
	return (1);
}

/*
** Execute any process with the set environment except builtins.
** the only builtin that's allow is env it self
**
** @param	env [description]
** @return	[1 if another command has to be execute otherwise return 0]
*/

int					builtin_env(t_list **env, char **av)
{
	int				show_env;
	char			*flags[2];

	show_env = 1;
	flags[0] = ft_strdup(" i u - --ignore-environment --null --unset --help --version ");
	if (!(flags[1] = get_glags(flags[0], av, "env")))
		return (0);
	if (ft_strstr(flags[1], " --help ") && (show_env = 0))
	{
		ft_putendl("Usage: please type man help for more information\n");
		ft_putendl("The options are:\n");
		ft_putendl("-i, --ignore-environment, -0, -u\n");
	}
	else if (ft_strstr(flags[1], " -i "))
		show_env = 0;
	else if (ft_strstr(flags[1], " --version ") && (show_env = 0))
		ft_putstr("\nenv (GNU coreutils) 8.21\nCopyright © 2017 kacoulib.\n\n");
	else if ((ft_strstr(flags[1], " --ignore-environment ") ||
		ft_strstr(flags[1], " i ")) && !(show_env = 0))
		ft_lstdel(env, del);
	if (builtin_env_extra(env, av) && show_env)
		read_env(env, flags[1]);
	return (0);
}
