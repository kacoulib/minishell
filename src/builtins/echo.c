/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 05:35:38 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/21 05:35:49 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				builtin_echo(char **av)
{
	int			i;
	t_flag_ctrl	*flag_ctrl;

	if (!av || !av[0])
	{
		ft_putchar('\n');
		return (TRUE);
	}
	flag_ctrl = create_flag_ctrl("echo", 0, 0);
	flag_ctrl->list = init_flags("- n");
	flag_ctrl->step_back_on_error = 1;
	flag_ctrl->reset_after_error = 1;
	i = set_flag_output_and_get_limit(flag_ctrl, av) - 1;
	while (av[++i])
	{
		if (ft_indexof(av[i], '\\') > -1)
			special_char(av[i]);
		else
			ft_putstr(av[i]);
		av[i + 1] ? ft_putchar(' ') : ' ';
	}
	if (!ft_strchr(flag_ctrl->output, '1'))
		ft_putchar('\n');
	delete_flag_ctrl(flag_ctrl);
	return (TRUE);
}
