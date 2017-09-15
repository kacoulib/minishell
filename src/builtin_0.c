/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:58:28 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/13 12:58:34 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				builtin_echo(char **av)
{
	int			i;
	t_flag_ctrl	*flag_ctr;

	if (!av || !av[0])
	{
		ft_putchar('\n');
		return (true);
	}
	flag_ctr = create_flag_ctrl(0, 0);
	flag_ctr->list = init_flags("- n");
	flag_ctr->step_back_on_error = 1;
	flag_ctr->reset_after_error = 1;
	i = builtin_echo_args_limit(flag_ctr, av) - 1;
	while (av[++i])
	{
		if (ft_indexof(av[i], '\\') > -1)
			special_char(av[i]);
		else
			ft_putstr(av[i]);
		av[i + 1] ? ft_putchar(' ') : ' ';
	}
	if (!ft_strchr(flag_ctr->output, '1'))
		ft_putchar('\n');
	return (true);
}

static char		*builtin_cd_second_part(t_list **env, char *av, int *error_id)
{
	char **path;

	if (av && ft_strcmp(av, "--") != 0)
	{
		if (ft_strcmp(av, "-") == 0)
		{
			if (swap_env(env, "OLDPWD", "_"))
				*error_id = 2;
			if (!path = ft_getenv(env, "_"))
				return (NULL);
			path = ft_strsplit(*path, '=');
			printf("----------+ %s\n", path);
				return (NULL);
		}
		else
			*path = av;
		return (*path);
	}
	return (NULL);
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
	int			error_id;
	char		*path;

	error_id = -1;
	path = builtin_cd_second_part(env, av[0], &error_id);
	printf("-----------\n");
	if (!path)
	{
		path = ft_strsplit(ft_getenv(env, "HOME"), '=')[1];
		builtin_setenv(env, av);
	}
	if (!path)
		return (set_errors(error_id, NULL, NULL));
	if (chdir(path) < 0 && !(error_id = 0))
		set_errors(error_id, NULL, path);
	return (true);
}

int				print_env(t_list **env, char *flags)
{
	int			i;
	t_list		*tmp;

	i = -1;
	if (!*env)
		return (0);
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, "") != 0)
		{
			if (flags && (ft_strstr(flags, " 0 ") ||
				ft_strstr(flags, " --null ")))
				ft_putstr(tmp->content);
			else
				ft_putendl(tmp->content);
		}
		tmp = tmp->next;
	}
	if (flags)
		free(flags);
	return (true);
}

/*
** [builtin_setenv description]
**
** @param  env [an array of key pair vaule]
** @param  av     [the arguments]
** @return           [if the key dont exist the create else overwrite it if the
** overwrite is != 0]
*/

int				builtin_setenv(t_list **env, char **av)
{
	char		*tmp;
	t_list		*new;

	if (!av || !av[0])
		return (print_env(env, NULL));
	new = ft_getenv_from_list(env, av[0]);
	tmp = ft_strjoin(av[0], "=");
	if (av[1])
		tmp = ft_strjoin(tmp, av[1]);
	if (new)
	{
		free(new->content);
		new->content = tmp;
	}
	else
	{
		if (!*env)
			*env = ft_lstnew(tmp, ft_strlen(tmp) + 1);
		else
			ft_lstpush(*env, ft_lstnew(tmp, ft_strlen(tmp) + 1));
	}
	return (1);
}
