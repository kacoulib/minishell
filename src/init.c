/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 14:02:20 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/13 14:02:31 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*check_and_get_flag(char *builtin, char **av) // to replace with the new builtin_echo_args_limit
{
	char	*tmp;

	if (ft_strcmp(builtin, "echo") == 0)
		tmp = ft_strdup(" n e E --help --version ");
	else
		return (NULL);
	return (get_glags(tmp, av, builtin));
}

int			check_flag(t_list *flag, int id)
{
	while (flag)
	{
		if ((int)flag->content_size == id)
			return (1);
		flag = flag->next;
	}
	return (0);
}

t_list		*init_flags(char *flags)
{
	int		i;
	int		j;
	char	**str;
	t_list	*head;
	t_list	*new;

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
	return (head);
}

t_flag_ctrl				*create_flag_ctrl(int has_dash, int has_error)
{
	t_flag_ctrl	*ctr;

	if (!(ctr = (t_flag_ctrl *)malloc(sizeof(t_flag_ctrl) + 1)))
		return (NULL);
	ctr->has_dash = has_dash;
	ctr->has_error = has_error;
	ft_memset(ctr->output, '\0', 256);
	ctr->list = NULL;
	return (ctr);
}

static int			get_long_flag_id(t_flag_ctrl *flag_ctrl, char *av)
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
			return (flag_list->content_size);
		}
		flag_list = flag_list->next;
	}
	if (flag_ctrl->has_error)
		printf("errror : %s not a valid flag\n", av); // to rm
	return (-1);
}

static int			get_single_flag_id(t_flag_ctrl *flag_ctrl, char *av)
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

/*
**	@param [has_dash] If true then the single '-' is consider as en parameter
**						e.g : ls -
*/

int			builtin_echo_args_limit(t_flag_ctrl *flag_ctrl, char **av)
{
	int			i;
	int			j;
	int			k;

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
