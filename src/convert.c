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

char			*convert_home_to_tilde(char *path, char *home)
{
	int			i;
	char		*ret;

	if (!path || !home)
		return (NULL);
	i = ft_strlen(home) - 1;
	if (ft_strncmp(path, home, i) == 0)
		ret = ft_preg_replace(path, home, "~");
	else
		ret = ft_strdup(path);
	return (ret);
}

char			*convert_tilde_to_home(char *path, char *home)
{
	char		*ret;

	if (!path || !home)
		return (NULL);
	ret = ft_preg_replace(path, "~", home);
	return (ret);
}
