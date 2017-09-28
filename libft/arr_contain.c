/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_contain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:13:20 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/28 16:13:34 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					arr_contain(char **arr, char *str)
{
	int				i;

	if (!arr || !str)
		return (0);
	i = -1;
	while (arr[++i])
		if (ft_strcmp(arr[i], str) == 0)
			return (1);
	return (0);
}
