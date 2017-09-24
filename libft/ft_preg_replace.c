/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preg_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 22:13:28 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/23 22:13:30 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_preg_replace(char *str, char *to_replace, char *replace)
{
	int			i;
	int			k;
	char		j;
	char		*tmp;
	char		*ret;

	if (!ft_strlen(str) || !ft_strlen(to_replace) || !ft_strlen(replace))
		return (NULL);
	if (!(tmp = ft_strstr(str, to_replace)))
		return (NULL);
	i = tmp - str;
	k = i + ft_strlen(to_replace);
	j = (ft_strlen(str) - ft_strlen(to_replace)) + ft_strlen(replace);
	ret = (char *)ft_memalloc(j + 1);
	ft_strncpy(ret, str, i);
	ft_strcpy(&ret[i], replace);
	i += ft_strlen(replace);
	ft_strcpy(&ret[i], &str[k]);
	return (ret);
}
