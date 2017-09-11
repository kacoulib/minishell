/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 02:04:08 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/02 02:04:22 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_putfile(char *str, int type, char *link)
{
	if (type == 10)
	{
		ft_putstr(COLOR_LINK);
		ft_putstr(str);
		ft_putstr(COLOR_RESET);
		if (link)
		{
			ft_putstr(" -> ");
			ft_putstr(link);
		}
		return (1);
	}
	if (type == 4)
		ft_putstr(COLOR_FOLDER);
	else if (type == 16)
		ft_putstr(COLOR_RED);
	else if (type == 32)
		ft_putstr(COLOR_GREEN);
	ft_putstr(str);
	ft_putstr(COLOR_RESET);
	return (1);
}
