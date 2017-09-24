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

/*
**	0	white
**	37	white	background
**
**	10	yellow
**	31	yellow	background
**
**	4	blue
**	35	blue	background
**
**	16	red
**
**	30	magenta
**	31	yellow	background
**
**	32	green
**	33	green	background
*/

static int			ft_putfile_second_part(char *str, int type)
{
	if (type == 30)
		ft_putstr(ANSI_COLOR_MAGENTA);
	if (type == 31)
		ft_putstr(COLOR_YELLOW);
	else if (type == 35)
		ft_putstr(COLOR_BLUE);
	else if (type == 37)
		ft_putstr(COLOR_WHITE);
	ft_putstr(str);
	ft_putstr(COLOR_RESET);
	return (1);
}

int					ft_putfile(char *str, int type, char *link)
{
	if (!str)
		return (0);
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
		ft_putstr(ANSI_COLOR_BLUE);
	else if (type == 16)
		ft_putstr(COLOR_RED);
	else if (type == 32)
		ft_putstr(ANSI_COLOR_GREEN);
	return (ft_putfile_second_part(str, type));
}
