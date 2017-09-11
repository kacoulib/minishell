/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 18:43:14 by kacoulib          #+#    #+#             */
/*   Updated: 2016/11/27 14:35:46 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*r;

	r = (char *)malloc(size + 1);
	if (r == NULL)
		return (NULL);
	while (size > 0)
	{
		r[size] = '\0';
		size--;
	}
	r[0] = '\0';
	return (r);
}
