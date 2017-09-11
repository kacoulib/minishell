/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:52:02 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/07 17:36:23 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*r;

	i = 0;
	if (!s)
		return (NULL);
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (r == NULL)
		return (r);
	while (s[start] && len > 0)
	{
		r[i] = s[start];
		i++;
		len--;
		start++;
	}
	r[i] = '\0';
	return (r);
}
