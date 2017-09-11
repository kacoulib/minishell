/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 15:54:27 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/06 16:49:08 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strrev(char *s)
{
	int		i;
	int		j;
	char	tmp;

	i = -1;
	j = ft_strlen(s);
	while (i++ < (j-- - 1))
	{
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
	return (s);
}

char		*ft_itoa(int n)
{
	int		i;
	int		len;
	int		j;
	char	*r;

	if (n <= -2147483648)
		return (ft_strdup("-2147483648"));
	i = 0;
	r = NULL;
	if ((len = n) < 0)
		n = -n;
	j = len;
	while (len /= 10)
		i++;
	r = ft_strnew(i + ((j < 0) ? 2 : 1));
	if (r == NULL)
		return (NULL);
	r[i] = '\0';
	i = 0;
	r[i++] = n % 10 + '0';
	while ((n /= 10) > 0)
		r[i++] = n % 10 + '0';
	if (j < 0)
		r[i] = '-';
	return (ft_strrev(r));
}
