/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:33:03 by kacoulib          #+#    #+#             */
/*   Updated: 2017/02/24 09:15:43 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*r;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	r = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!r)
		return (NULL);
	while (s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		r[i] = s2[j];
		i++;
		j++;
	}
	r[i] = '\0';
	return (r);
}
