/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ucfirst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 18:00:48 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/07 18:54:44 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_ucfirst(char *s)
{
	char	*r;

	r = (char *)malloc(sizeof(char) * ft_strlen(s));
	if (!s || !r)
		return (NULL);
	r = ft_strcpy(r, s);
	while (ft_isspace(*r))
		r++;
	*r = ft_toupper(*r);
	return (r);
}
