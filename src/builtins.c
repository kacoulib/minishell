/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 16:16:25 by kacoulib          #+#    #+#             */
/*   Updated: 2017/06/30 16:16:27 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Move into a specific folder.
** If the path == "--" or is not specify the path will be the home path.
** Otherwise it will try to move into it.
**
** @param  av  [an array of argument passed to the program]
** @param  env [an array of key pair vaule]
** @return     [if sucess return 1 else print error and return 0]
*/

int			builtin_cd(t_list *env, char **av)
{
	int		error_id;
	char	*path;

	error_id = -1;
	if (av[0] && ft_strcmp(av[0], "--") != 0)
	{
		if (ft_strcmp(av[0], "-") == 0)
		{
			if (swap_env(env, "OLDPWD", "_"))
				error_id = 2;
			path = ft_strsplit(ft_getenv(env, "_"), '=')[1];
		}
		else
			path = av[0];
	}
	else
	{
		path = ft_strsplit(ft_getenv(env, "HOME"), '=')[1];
		builtin_setenv(env, av);
	}
	if (!path)
		return (set_errors(error_id, NULL, NULL));
	if (chdir(path) < 0 && (error_id = 0))
		set_errors(error_id, NULL, path);
	ft_print(ft_strsplit(ft_getenv(env, "PWD"), '=')[1], ":", NULL, NULL);
	return (true);
}

int			builtin_echo(char **av)
{
	int		i;
	char	*flags[2];

	if (!av || !av[0])
	{
		ft_putchar('\n');
		return (true);
	}
	flags[0] = ft_strdup(" n e E --help --version ");
	flags[1] = get_glags(flags[0], av, "echo");
	i = get_args_limit(av) - 1;
	while (av[++i])
	{
		if (ft_indexof(av[i], '\\') > -1)
			special_char(av[i]);
		else
			ft_putstr(av[i]);
		av[i + 1] ? ft_putchar(' ') : ' ';
	}
	if (ft_strlen(flags[1]) == 0 || ft_strstr(flags[1], " n ") == 0)
		ft_putchar('\n');
	free(flags[1]);
	return (true);
}

int			builtin_exit(int status)
{
	exit(status);
	return (true);
}

/*
** Execute any process with the set environment except builtins.
** the only builtin that's allow is env it self
**
** @param	env [description]
** @return	[1 if another command has to be execute otherwise return 0]
*/

int			builtin_env(t_list *env, char **av)
{
	int		show_env;
	char	*flags[2];

	show_env = 1;
	flags[0] = ft_strdup(" i u --ignore-environment --null --unset --help --version ");
	flags[1] = get_glags(flags[0], av, "env");
	if (flags[1])
	{
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
			ft_strstr(flags[1], " i ")) && (show_env = 0))
			env = NULL;
	}
	if (show_env)
		builtin_env_extra(env, av, flags[1]);
	return (0);
}

int			builtin_env_extra(t_list *env, char **av, char *flags)
{
	int		i;

	i = -1;
	// if (ft_strstr(flags, " --help "))
	// printf("____%s, %s, %s\n", flags, av[0], env[0]);
	if (av)
		;
	while (env)
	{
		if (ft_strcmp(env->content, "") != 0)
		{
			if (ft_strstr(flags, " 0 ") || ft_strstr(flags, " --null "))
				ft_putstr(env->content);
			else
				ft_putendl(env->content);
		}
		env = env->next;
	}
	free(flags);
	return (true);
}

int			builtin_env_extra_unset(t_list *env, char **av, char *flags)
{
	int		i;

	i = -1;
	while (av[++i] && av[i][0] == '-' && av[i][1])
	{
		if (ft_strstr(av[i], "--ignore-environment=") || ft_strstr(av[i], "-u="))
		{
			if (flags || env) // to remove
				;
		}
	}
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

int		builtin_setenv(t_list *env, char **av)
{
	char	*tmp;
	char	*key;
	char	*val;
	t_list	*new;

	if (!av || !av[0])
		return (builtin_env(env, av));
	new = ft_getenv_from_list(env, av[0]);
	key = ft_strdup(av[0]);
	val = ft_strdup(av[1] ? av[1] : "");
	tmp = ft_strjoin(key, ft_strjoin("=", (val ? val : "")));
	new = ft_lstnew(tmp, ft_strlen(tmp) + 1);
	if (!env)
		env = copy_env(&tmp);//TODO
	else
		ft_lstpush(env, new);

	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
	return (1);
}

/*
** Deletes the variable name and value from the environment.
**
** @param  name [description]
** @return      [return 1 on sucess an 0 on error]
**
** @todo   look for empty env
*/

int			builtin_unsetenv(t_list *env, char **av)
{
	int		i;
	t_list	*tmp;
	t_list	*prev;

	if ((!av || !av[0]) || !(tmp = env))
		return (set_errors(-2, "unsetenv", "NAME"));
	i = ft_strlen(av[0]);
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, av[0], i) == 0)
		{
			if (((char *)tmp->content)[i] == '=')
			{
				if (!prev && (env = env->next))
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
	return (builtin_unsetenv_extra(env));
}

int			builtin_unsetenv_extra(t_list *env)
{
	
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;	
	}
	return (0);
}


























