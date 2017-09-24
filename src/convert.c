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

char			*convert_home_tilde(char *path, char *login)
{
	int			i;
	char		*tmp;

	if (!path || !login || !(tmp = ft_strjoin("/Users/", login)))
		return (NULL);
	i = ft_strlen(login) + 7;
	if (ft_strncmp(path, tmp, i) == 0)
		path = ft_preg_replace(path, tmp, "~");
	free(tmp);
	return (path);
}
