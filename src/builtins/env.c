/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 05:35:14 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/21 05:35:26 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			builtin_env_extra(t_flag_ctrl *flag_ctrl, t_list **new_env,
	int show_env)
{
	if (flag_contain(flag_ctrl, "2"))
		show_env = 0;
	if (show_env)
		read_env(new_env, ft_strdup(flag_ctrl->output));
	delete_flag_ctrl(flag_ctrl);
	return (TRUE);
}

/*
** Execute any process with the set environment except builtins.
** the only builtin that's allow is env it self
**
** @param	env [description]
** @return	[1 if another command has to be execute otherwise return 0]
*/

int					builtin_env(t_list **env, char **av)
{
	int				show_env;
	int				i;
	char			*tmp;
	t_list			**new_env;
	t_flag_ctrl		*flag_ctrl;

	show_env = 1;
	new_env = env;
	tmp = "i u - --ignore-environment --null --unset --help --version";
	flag_ctrl = create_flag_ctrl("env", 0, 0);
	flag_ctrl->list = init_flags(tmp);
	flag_ctrl->has_dash = 1;
	i = set_flag_output_and_get_limit(flag_ctrl, av) - 1;
	if (flag_contain(flag_ctrl, "6") && !(show_env = 0))
	{
		ft_putendl("Usage: please type man help for more information\n");
		ft_putendl("The options are:\n");
		ft_putendl("-i, --ignore-environment, -0, -u\n");
	}
	else if (flag_contain(flag_ctrl, "0") || flag_contain(flag_ctrl, "3"))
		new_env = NULL;
	else if (flag_contain(flag_ctrl, "7") && !(show_env = 0))
		ft_putstr("\nCopyright © 2017 kacoulib.\n\n");
	return (builtin_env_extra(flag_ctrl, new_env, show_env));
}
