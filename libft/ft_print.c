/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 03:09:30 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/02 03:09:42 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_print(char *s1, char *s2, char *s3, char *s4)
{
	if (s1 && s2)
	{
		ft_putstr(s1);
		ft_putstr(s2);
	}
	if (s3)
		ft_putstr(s3);
	if (s4)
		ft_putstr(s4);
	ft_putchar('\n');
	return (1);
}
