/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 05:59:00 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/21 05:59:17 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			builtin_exit(av[0]);
		else
			return (r == 1 ? r : 0);
	}
	return (TRUE);
}
