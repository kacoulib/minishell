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

int				check_access(char *command, char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) != 0)
			return (set_errors(9, command, path));
		return (1);
	}
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
		ft_putchar('\a');
	else if (c == 'b')
		ft_putchar('\b');
	else if (c == 'f')
		ft_putchar('\f');
	else if (c == 'n')
		ft_putchar('\n');
	else if (c == 'r')
		ft_putchar('\r');
	else if (c == 't')
		ft_putchar('\t');
	else if (c == 'v')
		ft_putchar('\v');
	else if (c == '\\')
		ft_putchar('\\');
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
