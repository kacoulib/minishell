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

static int			builtin_unsetenv_extra(t_list **env, t_list *tmp, char **av)
{
	t_list			*current;

	current = *env;
	while (current != NULL)
	{
		if (current->next && current->next == tmp)
		{
			current->next = tmp->next;
			ft_lstdelone(&tmp, (void *)del);
			return (1);
		}
		current = current->next;
	}
	if (ft_strstr(av[0], "*"))
		ft_lstdel(env, (void *)del);
	return (FALSE);
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
	t_list			*tmp;

	if ((!av || !av[0]) || av[1])
		return (set_errors(-2, "unsetenv", "NAME"));
	if (!env || !*env)
		return (1);
	tmp = ft_getenv_from_list(env, av[0]);
	if (*env == tmp)
	{
		*env = tmp->next;
		ft_lstdelone(&tmp, (void *)del);
		return (1);
	}
	return (builtin_unsetenv_extra(env, tmp, av));
}
