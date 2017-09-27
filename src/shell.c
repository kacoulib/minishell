/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 19:10:15 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/20 19:10:28 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell_ctrl			*get_shell(void)
{
	static t_shell_ctrl	*shell = NULL;

	if (!shell)
		shell = (t_shell_ctrl *)ft_memalloc(sizeof(t_shell_ctrl) + 1);
	return (shell);
}

t_shell_ctrl			*init_shell(char *envp[])
{
	t_shell_ctrl		*shell;

	if (!envp || !envp[0])
		return ((t_shell_ctrl *)set_errors_r_char(13, "shell", NULL));
	if (!(shell = get_shell()))
		return (NULL);
	shell->env = copy_env(envp);
	return (shell);
}

int						delete_shell(void)
{
	t_shell_ctrl		*shell;
	t_list				*env;

	if (!(shell = get_shell()))
		return (FALSE);
	env = shell->env;
	ft_lstdel(&env, (void *)del_env);
	free(shell);
	return (TRUE);
}
