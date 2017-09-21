/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 16:33:00 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/17 16:33:01 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*get_exc_path_last_part(char **env_path, char *command)
{
	int				i;
	char			*tmp;

	i = -1;
	tmp = NULL;
	while (env_path[++i])
	{
		if (check_access(command, env_path[i]) == 1)
		{
			if (tmp)
				tmp = ft_freejoin(env_path[i], "/");
			else
				tmp = ft_strjoin(env_path[i], "/");
			tmp = ft_freejoin(tmp, command);
			if (check_access(command, tmp) == 1)
				return (tmp);
		}
	}
	return (NULL);
}

/*
** Get the executable path from env path
**
** @return	NULL if no path found. Otherwise the path is returned
*/

static char			*get_exeutable_path(char *command, t_list **env)
{
	char			**env_path;
	char			*tmp;

	env_path = (char **)ft_memalloc(sizeof(char));
	if (!(*env_path = ft_getenv(env, "PATH")))
		return (set_errors_r_char(-3, command, NULL));
	else if (access(command, F_OK & X_OK) != -1)
	{
		return (command);
	}
	else if (command[0] == '.' && command[1] == '/'
		&& (ft_print("misihell: no such file or directory: ",
			command, NULL, NULL)))
		return (NULL);
	*env_path = ft_strsub(*env_path, 5, ft_strlen(*env_path));
	env_path = ft_strsplit(*env_path, ':');
	if ((tmp = get_exc_path_last_part(env_path, command)))
		return (tmp);
	return (set_errors_r_char(-3, command, NULL));
}

static int			launch(char *command, char **av, t_list **env)
{
	pid_t			cpid;
	char			*command_path;

	if (is_bultin(command, &av[1], env))
		return (TRUE);
	cpid = fork();
	if (cpid == -1)
		ft_putendl("Error fork not valid pid\n");
	else if (cpid == 0)
	{
		if ((command_path = get_exeutable_path(command, env)))
			execve(command_path, av, convert_list_to_array(*env));
		builtin_exit("1");
	}
	else
		wait(&cpid);
	return (TRUE);
}

static int			ft_parse_args(t_shell_ctrl *shell)
{
	int				i;
	char			*tmp;
	char			**commands;
	char			**args;
	char			buff[PATH_MAX];

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
				launch(tmp, args, &shell->env) && free_arr(args);
			}
			if (i > 0)
				free_arr(commands);
			ft_print_prompt();
		}
	}
	return (1);
}

int					main(int ac, char *av[], char *envp[])
{
	t_shell_ctrl	*shell;

	if (!(shell = init_shell(envp)))
		return (0);
	ft_print_prompt();
	signal_handler();
	ft_parse_args(shell);
	return (ac && av);
}