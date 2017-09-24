/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 14:55:14 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/11 14:55:16 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Get the list that contain the env key
**
** @param  { env }   An array of key pair vaule
** @param  { key }   The key that should be find in the env
**
** @return [return NULL if the key don't exist OR the key and value]
*/

t_list		*ft_getenv_from_list(t_list **env, char *key)
{
	t_list	*tmp;
	int		i;

	i = -1;
	tmp = *env;
	while (tmp)
	{
		if (tmp->content)
		{
			if (ft_strncmp(tmp->content, key, ft_strlen(key)) == 0)
				if (((char *)tmp->content)[ft_strlen(key)] == '=')
					return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

/*
** Get the key and value from the enviroment path depennding on a key
**
** @param  { env }   An array of key pair vaule
** @param  { key }   The key that should be find in the env
**
** @return [return NULL if the key don't exist OR the key and value]
*/

char		*ft_getenv_val(t_list **env, char *key)
{
	int		i;
	char	*tmp;

	if (!(tmp = ft_getenv(env, key)))
		return (NULL);
	i = 0;
	if ((i = ft_indexof(tmp, '=')) > -1)
		return (tmp[i + 1] ? &tmp[i + 1] : NULL);
	return (tmp);
}

char		*ft_getenv(t_list **env, char *key)
{
	t_list *tmp;

	tmp = ft_getenv_from_list(env, key);
	return (tmp ? tmp->content : NULL);
}

/*
** If the param is single dash
** e.g: -en
**
** @param  { flags }    The command flags]
** @param  { av }       The argument pass through the program]
** @param  { command }  The name of the command]
**
** @return
*/

char		*get_single_flags(char *flags[], char *av, char *command)
{
	int		i;
	char	*r;
	char	*tmp;

	i = 0;
	r = NULL;
	while (av[++i] && (tmp = ft_strsub(av, i, 1)))
	{
		if (index_of_array(flags, tmp) >= 0)
		{
			if (!r)
				r = ft_strdup(tmp);
			else
				r = ft_strjoin(r, tmp);
			r = ft_strjoin(r, " ");
		}
		else
		{
			set_errors(1, command, tmp);
			return (NULL);
		}
		free(tmp);
	}
	return (r);
}

/*
** Filter and get all flags passed to the command
** e.g echo -e --version        // the flag -e is passed to the command echo
**
** @param  { except_flags }     The command flags that the command can have
** @param  { av }               The argument pass through the program
** @param  { command }          The name of the command
** @return [return NULL on if error or no flags otherwise return the flags]
*/

char		*get_glags(char *except_flags, char **av, char *command)
{
	int		i;
	char	**flags;
	char	*tmp;
	char	*r;

	i = -1;
	flags = ft_strsplit(except_flags, ' ');
	r = ft_strdup(" ");
	while (av[++i] && av[i][0] == '-' && av[i][1])
	{
		if ((r = ft_strjoin(r, " ")) && av[i][1] != '-')
		{
			if (!(tmp = get_single_flags(flags, av[i], command)))
				return (NULL);
			r = ft_strjoin(r, tmp);
			free(tmp);
		}
		else if (index_of_array(flags, av[i]) >= 0)
			r = ft_strjoin(r, av[i]);
		else
		{
			set_errors(1, command, av[i]);
			return (NULL);
		}
	}
	free_arr(flags);
	return (ft_strjoin(r, " "));
}
