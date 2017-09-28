/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 13:04:58 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/28 13:05:12 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					flag_contain(t_flag_ctrl *flag_ctrl, char *str)
{
	if (!flag_ctrl)
		return (0);
	return (ft_strstr(flag_ctrl->output, str) != NULL);
}

/*
**	@param [has_dash] If TRUE then the single '-' is consider as en parameter
**						e.g : ls -
*/

int					set_flag_output_and_get_limit(t_flag_ctrl *flag_ctrl,
	char **av)
{
	int				i;
	int				j;
	int				k;

	i = -1;
	while (av[++i] && av[i][0] == '-')
	{
		k = ft_strlen(flag_ctrl->output);
		if (av[i][1] && av[i][1] == '-')
			j = get_long_flag_id(flag_ctrl, av[i]);
		else
		{
			if (av[i][1] || flag_ctrl->has_dash)
				j = get_single_flag_id(flag_ctrl, av[i]);
		}
		if (j == -1 && flag_ctrl->reset_after_error)
			ft_memset(&flag_ctrl->output[k], '\0', 256);
		if (j == -1 && flag_ctrl->step_back_on_error)
			return (i);
	}
	return (i);
}

int					get_long_flag_id(t_flag_ctrl *flag_ctrl, char *av)
{
	char			*tmp;
	t_list			*flag_list;

	flag_list = flag_ctrl->list;
	while (flag_list)
	{
		if (ft_strcmp(flag_list->content, av) == 0)
		{
			tmp = ft_itoa(flag_list->content_size);
			if (ft_indexof(flag_ctrl->output, tmp[0]) < 0)
				ft_strcat(flag_ctrl->output, tmp);
			free(tmp);
			return (flag_list->content_size);
		}
		flag_list = flag_list->next;
	}
	if (flag_ctrl->show_error)
		set_errors(10, flag_ctrl->program_name, av);
	return (-1);
}

int					get_single_flag_id(t_flag_ctrl *flag_ctrl, char *av)
{
	int				i;
	int				j;
	char			*tmp;

	i = -1;
	while (av[++i])
	{
		tmp = ft_strsub(av, i, 1);
		j = get_long_flag_id(flag_ctrl, tmp);
		free(tmp);
	}
	return (j);
}
