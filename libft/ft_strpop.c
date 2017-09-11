/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 04:19:01 by kacoulib          #+#    #+#             */
/*   Updated: 2017/01/11 13:30:40 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strpop(char **s, char c)
{
	int		i;
	int		j;
	char	*r;

	if (!*s)
		return (NULL);
	if ((i = ft_indexof(*s, c)) < 0)
	{
		r = ft_strdup(*s);
		*s = NULL;
		return (r);
	}
	else if (i == 0)
	{
		(*s)++;
		return (ft_strpop(s, c));
	}
	if (!(r = ft_memalloc(i)))
		return (NULL);
	j = -1;
	ft_strncpy(r, *s, i);
	while (++j < i && (**s))
		(*s)++;
	return (r);
}
