/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 07:06:16 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/22 07:06:18 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*ft_preg_replace(char *str, char *to_replace, char *replace)
{
	int			i;
	char		j;
	char		*tmp;
	char		*ret;

	tmp = ft_strstr(str, to_replace);
	if (!tmp)
		return (NULL);
	i = &tmp - &str;
	// i = 12;
	j = (ft_strlen(str) - ft_strlen(to_replace)) + ft_strlen(replace);
	ret = (char *)ft_memalloc(j + 1);
	// ft_strncpy(ret, str, i);			// before
	// ft_strcpy(&tmp[i], replace);	// during
	// i += ft_strlen(replace);
	// ft_strcpy(&tmp[i], &str[i]);		// after

	printf("%s .%d\n", replace, i);
	// 01 234 56
	//    789   
	// 01 789 56
	// if (i == 0)
	// {

	// }
	// else
	// {

	// }

	// ft_strcpy(tmp, replace);
	// i = ft_strlen(replace);
	// ft_strcpy(tmp, &str[i]);
	// printf("---%s\n", tmp);
	return (NULL);
}

char			*convert_home_tilde(char *path, char *login)
{
	int			i;
	char		*tmp;

	ft_preg_replace(path, "/Users/kacoulib", "/ka");
	if (ft_strncmp(path, "/Users/", 7) == 0)
	{
		i = ft_strlen(login) - 1;
		if (ft_strncmp(&path[7], login, i) == 0)
		{
			tmp = ft_memalloc(((ft_strlen(path) - 7) - i) + 1);
			tmp[0] = '~';
			ft_strcpy(&tmp[1], &path[7 + (i) + 1]);
			return (tmp);
		}
	}
	return (path);
}
