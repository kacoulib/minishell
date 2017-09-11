/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 16:33:59 by kacoulib          #+#    #+#             */
/*   Updated: 2016/11/27 13:31:36 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *s1, const char *s2, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i] && i < size)
		i++;
	j = i;
	while (s2[i - j] && i < size - 1)
	{
		s1[i] = s2[i - j];
		i++;
	}
	if (j < size)
		s1[i] = '\0';
	return (j + ft_strlen(s2));
}
