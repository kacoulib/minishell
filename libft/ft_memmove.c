/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 18:17:55 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/06 17:07:00 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t		i;

	if (dst < src)
	{
		i = 0;
		while (i < n)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	else if (dst > src)
	{
		while (n > 0)
		{
			n--;
			((char *)dst)[n] = ((char *)src)[n];
		}
	}
	return (dst);
}
