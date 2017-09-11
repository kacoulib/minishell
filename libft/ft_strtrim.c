/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 15:41:07 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/06 17:16:49 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	int		j;

	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	if (*s == '\0')
		return (ft_strdup(""));
	j = ft_strlen(s);
	if (j == 0)
		return (ft_strdup(""));
	while (s[j - 1] == ' ' || s[j - 1] == '\n' || s[j - 1] == '\t')
		j--;
	return (ft_strsub(s, 0, j));
}
