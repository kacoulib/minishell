/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 05:36:41 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/21 05:37:00 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			builtin_unsetenv_extra(t_list **env, char **av)
{
	char			*tmp;

	if (!(tmp = av[0] ? ft_strtrim(av[0]) : NULL))
		return (0);
	if (ft_strstr(tmp, "*"))
		ft_lstdel(env, del);
	return (0);
}

/*
** Deletes the variable name and value from the environment.
**
** @param  name [description]
** @return      [return 1 on sucess an 0 on error]
**
** @todo   look for empty env
*/

int					builtin_unsetenv(t_list **env, char **av)
{
	int				i;
	t_list			*tmp;
	t_list			*prev;

	if ((!av || !av[0]))
		return (set_errors(-2, "unsetenv", "NAME"));
	i = ft_strlen(av[0]);
	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, av[0], i) == 0)
		{
			if (((char *)tmp->content)[i] == '=')
			{
				if (!prev && (*env = (*env)->next))
					prev = tmp->next;
				else
					prev->next = tmp->next;
				free(tmp);
				tmp = prev;
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (builtin_unsetenv_extra(env, av));
}