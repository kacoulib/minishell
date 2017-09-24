/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 14:55:27 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/11 14:55:29 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*copy_env(char *env[])
{
	int		i;
	t_list	*tmp;
	t_list	*r;

	if (!env[0])
		return (ft_lstnew(NULL, sizeof(t_list) + 1));
	i = 0;
	r = ft_lstnew(env[0], ft_strlen(env[0]) + 1);
	while (env[++i])
	{
		tmp = ft_lstnew(env[i], ft_strlen(env[i]) + 1);
		ft_lstadd(&r, tmp);
	}
	return (r);
}

int			list_length(t_list *list)
{
	int		i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

char		**convert_list_to_array(t_list *list)
{
	int		i;
	char	**r;

	i = list_length(list);
	if (!i)
		return (0);
	i = sizeof(char *) * (i + 1);
	if (!(r = (char **)malloc(i)))
		return (NULL);
	ft_bzero(r, i);
	i = 0;
	while (list)
	{
		r[i] = list->content;
		list = list->next;
		i++;
	}
	return (r);
}

void		del(void *content, size_t len)
{
	if (content)
		free(content);
	if (len)
		;
}
