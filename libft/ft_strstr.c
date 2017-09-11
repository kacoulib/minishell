/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 18:50:11 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/02 22:19:52 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int	i;

	i = ft_strlen(s2);
	if (*s2 == '\0')
		return ((char *)s1);
	while (*s1)
	{
		if (!ft_memcmp(s1++, s2, i))
			return ((char *)(s1 - 1));
	}
	return (NULL);
}
