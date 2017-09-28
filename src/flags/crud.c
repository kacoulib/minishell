/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 13:03:39 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/28 13:03:56 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list				*init_flags(char *flags)
{
	int				i;
	int				j;
	char			**str;
	t_list			*head;
	t_list			*new;

	if (!flags)
		return (0);
	str = ft_strsplit(flags, ' ');
	i = -1;
	j = 0;
	while (str[++i])
	{
		new = ft_lstnew(str[i], ft_strlen(str[i]));
		new->content_size = j;
		if (j == 0)
			head = new;
		else
			ft_lstpush(head, new);
		j++;
	}
	if (str)
		free_arr(str);
	return (head);
}

t_flag_ctrl			*create_flag_ctrl(char *program_name, int has_dash,
	int show_error)
{
	t_flag_ctrl		*ctrl;

	if (!(ctrl = (t_flag_ctrl *)ft_memalloc(sizeof(t_flag_ctrl))))
		return (NULL);
	ft_bzero(ctrl->program_name, 256);
	ft_memcpy(ctrl->program_name, program_name, ft_strlen(program_name));
	ctrl->has_dash = has_dash;
	ctrl->show_error = show_error;
	ft_bzero(ctrl->output, 256);
	ctrl->list = NULL;
	return (ctrl);
}

int					delete_flag_ctrl(t_flag_ctrl *ctrl)
{
	if (!ctrl)
		return (FALSE);
	if (ctrl->list)
		ft_lstdel(&ctrl->list, (void *)del);
	free(ctrl);
	ctrl = NULL;
	return (TRUE);
}
