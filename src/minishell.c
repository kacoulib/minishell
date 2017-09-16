/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 15:49:46 by kacoulib          #+#    #+#             */
/*   Updated: 2017/06/30 15:49:47 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			builtin_exit(int status)
{
	exit(status);
	return (TRUE);
}

/*
** Check if the command is an builtin. If then, execute it
**
** @param	{ command } The name of the command that should be check
** @param	{ av }
** @param	{ env }
**
** @return	NULL if no path found. Otherwize return the path
*/

int					is_bultin(char *command, char **av, t_list **env)
{
	int				r;

	r = 2;
	if (ft_strcmp(command, "env") == 0)
		r = builtin_env(env, av);
	if (r)
	{
		if (ft_strcmp(command, "cd") == 0)
			builtin_cd(env, av);
		else if (ft_strcmp(command, "echo") == 0)
			builtin_echo(av);
		else if (ft_strcmp(command, "setenv") == 0)
			builtin_setenv(env, av);
		else if (ft_strcmp(command, "unsetenv") == 0)
			builtin_unsetenv(env, av);
		else if (ft_strcmp(command, "exit") == 0)
			builtin_exit(TRUE);
		else
			return (r == 1 ? r : 0);
	}
	return (TRUE);
}

/*
** Get the executable path from env path
**
** @return	NULL if no path found. Otherwise the path is returned
*/

char				*get_exeutable_path(char *command, t_list **env)
{
	int				i;
	char			**env_path;
	char			*tmp;

	env_path = (char **)ft_memalloc(sizeof(char));
	if (!(*env_path = ft_getenv(env, "PATH")))
		return (set_errors_r_char(-3, command, NULL));
	else if (access(command, F_OK & X_OK) != -1)
		return (command);
	else if (command[0] == '.' && command[1] == '/'
		&& (ft_print("misihell: no such file or directory: ",
			command, NULL, NULL)))
		return (NULL);
	*env_path = ft_strsub(*env_path, 5, ft_strlen(*env_path));
	env_path = ft_strsplit(*env_path, ':');
	i = -1;
	while (env_path[++i])
	{
		tmp = ft_strjoin(env_path[i], "/");
		tmp = ft_strjoin(tmp, command);
		if (check_path_access(command, tmp) == 1)
			return (tmp);
	}
	return (set_errors_r_char(-3, command, NULL));
}

int					launch(char *command, char **av, t_list **env)
{
	pid_t			cpid;
	char			*command_path;

	if (is_bultin(command, &av[1], env))
		return (TRUE);
	cpid = fork();
	if (cpid == -1)
		printf("Error fork not valid pid\n");
	else if (cpid == 0)
	{
		if ((command_path = get_exeutable_path(command, env)))
			execve(command_path, av, convert_list_to_array(*env));
		builtin_exit(TRUE);
	}
	else
		wait(&cpid);
	return (TRUE);
}

int					main(int ac, char *av[], char *envp[])
{
	int				i;
	char			*tmp;
	char			**commands;
	char			**args;
	char			buff[PATH_MAX];
	t_list			*env;

	env = copy_env(envp);
	ft_putstr("\033[1;36m$> \033[0m");
	while (read(0, buff, PATH_MAX) > 0)
	{
		if ((i = ft_indexof(buff, '\n')) > -1)
		{
			tmp = ft_strsub(buff, 0, i);
			commands = ft_strsplit(tmp, ';');
			i = -1;
			while (commands[++i])
			{
				args = ft_strsplit(commands[i], ' ');
				tmp = args[0] ? args[0] : ft_strtrim(buff);
				launch(tmp, args, &env) && free_arr(args);
			}
			ft_putstr("\033[1;36m$> \033[0m");
		}
	}
	return (ac && av);
}
