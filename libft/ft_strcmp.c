/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:40:02 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/06 17:18:20 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(char *s1, char *s2)
{
	int				i;
	unsigned char	r1;
	unsigned char	r2;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		r1 = s1[i];
		r2 = s2[i];
		if (r1 != r2)
			return (r1 - r2);
		if (r1 == '\0')
			return (-r2);
		if (r2 == '\0')
			return (r1);
		i++;
	}
	return (0);
}
