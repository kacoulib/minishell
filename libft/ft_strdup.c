/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:09:55 by kacoulib          #+#    #+#             */
/*   Updated: 2016/11/28 19:03:36 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *str)
{
	int		i;
	char	*r;

	i = ft_strlen(str);
	r = (char *)malloc(sizeof(char) * (i + 1));
	if (!r)
		return (NULL);
	r[i] = '\0';
	while (i-- > 0)
		r[i] = str[i];
	return (r);
}
