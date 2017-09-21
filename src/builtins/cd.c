/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 05:33:02 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/21 05:33:21 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		builtin_cd_change_env(t_list **env, char *path)
{
	char		**tmp;

	if ((tmp = ft_strsplit(ft_getenv(env, "PWD"), '=')))
		tmp[1] = path;
	else
	{
		tmp	= (char **)ft_memalloc(sizeof(char) * 2);
		tmp[0] = ft_strdup("PWD");
		tmp[1] = path;
	}
	return (builtin_setenv(env, tmp));
}

static int		builtin_cd_second_part(t_list **env, char *av, char **path)
{
	char **tmp;

	if (av && ft_strcmp(av, "--") != 0)
	{
		if (ft_strcmp(av, "-") == 0)
		{
			if (swap_env(env, "OLDPWD", "PWD"))
				*path = ft_getenv(env, "PWD");
			else
				*path = ft_getenv(env, "USER");
			if (*path || !(tmp = ft_strsplit(*path, '=')))
				return (FALSE);
			*path = tmp[1];
		}
		else
			*path = av;
		return (TRUE);
	}
	*path = NULL;
	return (FALSE);
}

/*
** Move into a specific folder.
** If the path == "--" or is not specify the path will be the home path.
** Otherwise it will try to move into it.
**
** @param  av  [an array of argument passed to the program]
** @param  env [an array of key pair vaule]
** @return     [if sucess return 1 else print error and return 0]
*/

int				builtin_cd(t_list **env, char **av)
{
	char		**tmp;
	char		*path;

	builtin_cd_second_part(env, av[0], &path);
	if (!check_access("cd", path))
		return (FALSE);
	if (!path)
	{
		if ((tmp = ft_strsplit(ft_getenv(env, "HOME"), '=')))
			path = tmp[1];
		builtin_setenv(env, av);
	}
	if (!path)
		return (set_errors(-1, NULL, NULL));
	if (chdir(path) < 0)
		set_errors(0, NULL, path);
	return (builtin_cd_change_env(env, path));
}
