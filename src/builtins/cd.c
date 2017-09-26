/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 05:33:02 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/24 12:00:31 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_set_old_and_new_pwd(t_list **env, char *old_path)
{
	t_list		*pwd;
	t_list		*old_pwd;
	char		new_path[256];

	ft_bzero(new_path, 256);
	if (!getcwd(new_path, 256))
		return (FALSE);
	if (!(pwd = ft_getenv_from_list(env, "PWD")))
	{
		if (!create_env(env, "PWD", new_path))
			return (set_errors(100, NULL, "cd error"));
		pwd = ft_getenv_from_list(env, "PWD");
	}
	if (!(old_pwd = ft_getenv_from_list(env, "OLDPWD")))
	{
		if (!create_env(env, "OLDPWD", old_path))
			return (set_errors(100, NULL, "cd error"));
		old_pwd = ft_getenv_from_list(env, "OLDPWD");
	}
	// return (1);
	update_env(pwd, "PWD", new_path);
	update_env(old_pwd, "OLDPWD", old_path);
	return (TRUE);
}

static char		*ft_get_path_from_av(t_list **env, char **av)
{
	char		*path;
	char		*tmp;

	path = NULL;
	if ((!av || !av[0]) && !(path = ft_getenv_val(env, "HOME")))
		return (NULL);
	if (!path)
	{
		if ((path = av[0]))
		{
			if (ft_strcmp(path, "-") == 0)
			{
				if (!(path = ft_getenv_val(env, "OLDPWD")))
					if (!(path = ft_getenv_val(env, "HOME")))
						return (NULL);
			}
			else if (path[0] == '~')
			{
				if (!(tmp = ft_getenv_val(env, "USER")))
					return (NULL);
				path = convert_tilde_to_home(path, tmp);
			}
		}
	}
	return (path);
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
	char		*path;
	char		*old_path;

	if (av && av[0] && av[1])
		return (set_errors(4, "cd", NULL));
	if (!(path = ft_get_path_from_av(env, av)))
		return (set_errors(-1, NULL, NULL));
	if (!check_access("cd", path))
		return (FALSE);
	old_path = ft_getenv_val(env, "PWD");
	if (chdir(path) < 0)
		return (set_errors(0, NULL, path));
	return (ft_set_old_and_new_pwd(env, old_path));
}
