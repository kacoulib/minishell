/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_indexof.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 06:36:10 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/21 06:36:13 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_last_indexof(char *str, char c)
{
	int				i;

	if (!str)
		return (-1);
	i = ft_strlen(str);
	while (--i > -1)
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}
