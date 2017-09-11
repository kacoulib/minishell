/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 21:57:33 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/03 21:57:45 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_is_dir(char *path)
{
	struct stat		path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}
