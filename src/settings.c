/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 15:58:39 by kacoulib          #+#    #+#             */
/*   Updated: 2017/06/30 15:58:40 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Get the key and value from the enviroment path depennding on a key
**
** @param  { env }   An array of key pair vaule
** @param  { key }   The key that should be find in the env
**
** @return [return NULL if the key don't exist OR the key and value]
*/

char		*ft_getenv(char *env[], char *key)
{
	int		i;

	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0)
			if (ft_indexof(key, '=') > -1)
				return (env[i]);
	return (NULL);
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

int			swap_env(char *env[], char *s1, char *s2)
{
	int		i;
	char	*old;
	char	*new;
	char	**r1;
	char	**r2;

	new = ft_getenv(env, s1);
	if (!new || !(old = ft_getenv(env, s2)))
		return (false);
	r1 = ft_strsplit(new, '=');
	r2 = ft_strsplit(old, '=');
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], s1, ft_strlen(s1)) == 0)
			env[i] = ft_strjoin(s1, r2[1]);
		else if (ft_strncmp(env[i], s2, ft_strlen(s2)) == 0)
			env[i] = ft_strjoin(s2, r1[1]);
	}
	return (true);
}

int			get_args_limit(char **av)
{
	int		i;

	i = -1;
	while (av[++i] && av[i][0] == '-' && av[i][1])
		;
	return (i);
}

int			free_arr(char **arr)
{
	int		i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	return (true);
}

int			index_of_array(char **arr, char *key)
{
	int i;

	i = -1;
	while (arr[++i])
		if (ft_strcmp(arr[i], key) == 0)
			return (i);
	return (-1);
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

/*
** Display errors depennding on an id
**
** @param  { id }        The id for the error]
** @param  { command }   The name of the command]
** @param  { name }      The error name]
**
** @return      [return 0]
*/

int			set_errors(int id, char *command, char *name)
{
	if (id == -2)
	{
		ft_putstr("Minishel: ");
		ft_print(command, " << ", name, " >> not defined\n");
	}
	if (id == -1)
		printf("cd error no path to home\n");
	if (id == 0)
		ft_print("minishel: cd: ", name, ":  No such file or directory", NULL);
	if (id == 1 && ft_strcmp(command, "echo") != 0)
		ft_print(command, ": unrecognized option '", name,
			"'\n Try 'command --help' for more information.");
	if (id == 3)
		ft_putstr("name is NULL, points to a string of length 0, or contains an '=' character.");
	if (id == 4)
	{
		ft_print("minishel: ", command, ": to many args.", NULL);
		ft_putstr("See --help for more information.");
	}
	return (false);
}
