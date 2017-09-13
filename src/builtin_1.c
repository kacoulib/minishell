/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:58:43 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/13 12:58:46 by kacoulib         ###   ########.fr       */
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
		print_env(env, flags[1]);
	return (0);
}


static int			builtin_unsetenv_extra(t_list **env, char **av)
{
	char			*tmp;

	if (!(tmp = av[0] ? ft_strtrim(av[0]) : NULL))
		return (0);
	if (ft_strstr(tmp, "*"))
		ft_lstdel(env, del);
	return (0);
}

/*
** Deletes the variable name and value from the environment.
**
** @param  name [description]
** @return      [return 1 on sucess an 0 on error]
**
** @todo   look for empty env
*/

int					builtin_unsetenv(t_list **env, char **av)
{
	int				i;
	t_list			*tmp;
	t_list			*prev;

	if ((!av || !av[0]))
		return (set_errors(-2, "unsetenv", "NAME"));
	i = ft_strlen(av[0]);
	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, av[0], i) == 0)
		{
			if (((char *)tmp->content)[i] == '=')
			{
				if (!prev && (*env = (*env)->next))
					prev = tmp->next;
				else
					prev->next = tmp->next;
				free(tmp);
				tmp = prev;
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (builtin_unsetenv_extra(env, av));
}
