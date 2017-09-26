/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 07:06:16 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/22 07:06:18 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*convert_home_to_tilde(char *path, char *login)
{
	int			i;
	char		*tmp;

	if (!path || !login || !(tmp = ft_strjoin("/Users/", login)))
		return (NULL);
	i = ft_strlen(tmp) - 1;
	if (ft_strncmp(path, tmp, i) == 0)
		path = ft_preg_replace(path, tmp, "~");
	free(tmp);
	return (path);
}

char			*convert_tilde_to_home(char *path, char *login)
{
	char		*tmp;
	char		*ret;

	if (!path || !login || path[0] != '~')
		return (NULL);
	if (!(tmp = ft_strjoin("/Users/", login)))
		return (NULL);
	ret = ft_preg_replace(path, "~", tmp);
	free(tmp);
	return (path);
}
