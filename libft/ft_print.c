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
	char	*tmp;

	tmp = NULL;
	if (s1 && s2)
		tmp = ft_strjoin(s1, s2);
	if (s3)
		tmp = ft_strjoin(tmp, s3);
	if (s4)
		tmp = ft_strjoin(tmp, s4);
	if (tmp)
	{
		ft_putendl(tmp);
		free(tmp);
	}
	return (1);
}
