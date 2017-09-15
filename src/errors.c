/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 13:51:59 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/13 13:52:11 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Display errors depennding on an id
**
** @param  { id }        The id for the error]
** @param  { command }   The name of the command]
** @param  { name }      The error name]
**
** @return      [return 0]
*/

static int		set_errors_second(int id, char *command, char *name)
{
	if (id == 9)
		ft_print("command\033[0m ", command, " \033[1;31mpermission denied: ", name);
	return (false);
}
int				set_errors(int id, char *command, char *name)
{
	if (id != 1 || ft_strcmp(command, "echo") != 0)
		ft_putstr("\033[1;31mMisihell: ");
	// printf("%d %s\n", id, command);
	if (id == -3)
		ft_print("command\033[0m ", command, " \033[1;31mnot found", NULL);
	else if (id == -2)
		ft_print(command, " \033[0m<< ", name, " >>\033[1;31m not defined\n");
	else if (id == -1)
		printf("cd error no path to home\n");
	else if (id == 0)
		ft_print("minishel: cd: ", name, ":  No such file or directory", NULL);
	else if (id == 1 && ft_strcmp(command, "echo") != 0)
		ft_print(command, ": unrecognized option '", name,
			"'\n Try 'command --help' for more information.");
	else if (id == 3)
		ft_putstr("name is NULL, points to a string of length 0, or contains an '=' character.");
	else if (id == 4)
		ft_print(command, ": to many args.", "See --help for more information.", NULL);
	ft_putstr("\033[0m");
	return (set_errors_second(id, command, name));
}
char				*set_errors_r_char(int id, char *command, char *name)
{
	if (!set_errors(id, command, name))
		return (NULL);
	return ("true");
}
