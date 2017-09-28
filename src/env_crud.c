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
	free(tmp);
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

	if (!env || !name)
		return (FALSE);
	if (!(tmp = ft_strjoin(name, "=")))
		return (FALSE);
	if (value)
		if (!(tmp = ft_freejoin(tmp, value)))
			return (FALSE);
	if (env->content)
		free(env->content);
	env->content = tmp;
	return (TRUE);
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

int				swap_env(t_list **env, char *s1, char *s2)
{
	t_list		*new;
	t_list		*old;
	char		**n;
	char		**o;

	if (!s1 || !s2)
		return (FALSE);
	new = ft_getenv_from_list(env, s1);
	old = ft_getenv_from_list(env, s2);
	if (!(old) || !new)
		return (FALSE);
	n = ft_strsplit(new->content, '=');
	o = ft_strsplit(old->content, '=');
	if (!n || !o)
		return (FALSE);
	update_env(new, n[0], o[1]);
	update_env(new, o[0], n[1]);
	free_arr(n);
	free_arr(n);
	return (TRUE);
}
