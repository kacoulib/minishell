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

void				del_env(t_list *env, size_t len)
{
	if (env)
		free(env);
	(void)len;
}

/*
** Switch two env
**
** @param  { env }   An array of key pair vaule]
** @param  { s1 }    The first key in env that should replace]
** @param  { s1 }    The second key in env that should replace]
**
** @return     [return 1 on success otherwise return 0]
*/

int			swap_env(t_list **env, char *s1, char *s2)
{
	t_list	*tmp;
	char	*old;
	char	*new;
	char	**r1;
	char	**r2;

	if (!(new = ft_getenv(env, s1)) || !(old = ft_getenv(env, s2)))
		return (FALSE);
	r1 = ft_strsplit(new, '=');
	r2 = ft_strsplit(old, '=');
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, s1, ft_strlen(s1)) == 0)
		{
			tmp->content = ft_strjoin(s1, "=");
			tmp->content = ft_freejoin(tmp->content, r2[1]);
		}
		else if (ft_strncmp(tmp->content, s2, ft_strlen(s2)) == 0)
		{
			tmp->content = ft_strjoin(s2, "=");
			tmp->content = ft_freejoin(tmp->content, r1[1]);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}
