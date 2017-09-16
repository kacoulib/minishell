/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 16:21:31 by kacoulib          #+#    #+#             */
/*   Updated: 2017/06/30 16:21:34 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	@param [command] The command that is checking the function.
**
**	@Return :
**				-1	: if the file doesn't exist
**				0	: if the file exist and we don't have the permission
**				1	: if the file exist and we have the permission
*/

int				check_path_access(char *command, char *path)
{
	if (access(path, F_OK) == 0)
		return ((access(path, X_OK) != 0) ? set_errors(9, command, path) : 1);
	return (-1);
}

int				get_args_limit(char **av)
{
	int			i;

	i = -1;
	while (av[++i] && av[i][0] == '-' && av[i][1])
		;
	return (i);
}

int				free_arr(char **arr)
{
	int			i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	return (TRUE);
}

int				index_of_array(char **arr, char *key)
{
	int			i;

	i = -1;
	while (arr[++i])
		if (ft_strcmp(arr[i], key) == 0)
			return (i);
	return (-1);
}

static int		special_char_extra(char c)
{
	if (c == 'a')
		putchar('\a');
	else if (c == 'b')
		putchar('\b');
	else if (c == 'f')
		putchar('\f');
	else if (c == 'n')
		putchar('\n');
	else if (c == 'r')
		putchar('\r');
	else if (c == 't')
		putchar('\t');
	else if (c == 'v')
		putchar('\v');
	else if (c == '\\')
		putchar('\\');
	printf("--\n");
	return (TRUE);
}

int				special_char(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i++;
			if (ft_indexof("abcfnrtv", str[i]))
				special_char_extra(str[i]);
			else
				ft_putchar(str[i]);
		}
		else
			ft_putchar(str[i]);
	}
	return (TRUE);
}
