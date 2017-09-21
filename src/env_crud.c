/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_crud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 18:58:20 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/16 18:58:36 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				create_env(t_list **env, char *name, char *value)
{
	char		*tmp;

	if (!name)
		return (0);
	if (!env)
		return (0);
	if (!(tmp = ft_strjoin(name, "=")))
		return (0);
	if (value)
		if (!(tmp = ft_freejoin(tmp, value)))
			return (0);
	if (!*env)
		*env = ft_lstnew(tmp, ft_strlen(tmp) + 1);
	else
		ft_lstpush(*env, ft_lstnew(tmp, ft_strlen(tmp) + 1));
	return (TRUE);
}

int				read_env(t_list **env, char *flags)
{
	int			i;
	t_list		*tmp;

	i = -1;
	if (!env || !*env)
		return (0);
	tmp = *env;
	while (tmp)
	{
		if (tmp->content && ft_strcmp(tmp->content, "") != 0)
		{
			if (flags && (ft_strstr(flags, " --null ")))
				ft_putstr(tmp->content);
			else
				ft_putendl(tmp->content);
		}
		tmp = tmp->next;
	}
	if (flags)
		free(flags);
	return (TRUE);
}

int				update_env(t_list *env, char *name, char *value)
{
	char		*tmp;

	if (!env)
		return (0);
	if (!(tmp = ft_strjoin(name, "=")))
		return (0);
	if (value)
		if (!(tmp = ft_freejoin(tmp, value)))
			return (0);
	free(env->content);
	env->content = tmp;
	return (TRUE);
}

// int				delete_env(t_list *env)
// {
// 	if (ft_strncmp(tmp->content, av[0], i) == 0)
// 	{
// 		if (((char *)tmp->content)[i] == '=')
// 		{
// 			if (!prev && (*env = (*env)->next))
// 				prev = tmp->next;
// 			else
// 				prev->next = tmp->next;
// 			free(tmp);
// 			tmp = prev;
// 		}
// 	}
// 	return (TRUE);
// }
