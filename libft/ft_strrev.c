/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 06:10:11 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/21 06:10:21 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	if (!str)
		return (NULL);
	i = -1;
	j = ft_strlen(str);
	while (i++ < (j-- - 1))
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
	return (str);
}
