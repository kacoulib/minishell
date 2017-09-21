/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 18:25:47 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/20 18:25:58 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			ft_show_git_branch(void)
{
	char			*line;
	int				i;

	if ((i = open(".git/HEAD", O_RDONLY)) > -1)
	{
		line = (char *)ft_memalloc(sizeof (char *) + 1);
		if (get_next_line(i, &line) > -1)
		{
			i = ft_last_indexof(line, '/');
			if (line[++i])
			{
				ft_putfile(":", 37, NULL);
				ft_putfile(&line[i], 35, NULL);
			}
			free(line);
		}
	}
	ft_putstr("]\n$ ");
	return (TRUE);
}

static int			ft_show_pwd(t_list **env)
{
	char			*tmp;

	if ((tmp = ft_getenv_val(env, "PWD")))
	{
		ft_putfile(":", 37, NULL);
		ft_putfile(tmp, 32, NULL);
	}
	return (ft_show_git_branch());
}

static int			ft_show_login(t_list **env)
{
	char			*tmp;

	if ((tmp = ft_getenv_val(env, "USER")))
		ft_putfile(tmp, 31, NULL);
	return (ft_show_pwd(env));
}

int					ft_print_prompt(void)
{
	int				i;
	t_shell_ctrl	*shell;

	shell = get_shell();
	if (!shell)
		return (FALSE);
	ft_bzero(shell->pwd, ft_strlen(shell->pwd)); // to remove
	ft_putchar('[');
	i = 1;
	return (ft_show_login(&shell->env));
}
