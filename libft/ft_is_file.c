/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 01:55:57 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/02 01:56:17 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_is_file(char *path)
{
	struct stat		path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}
