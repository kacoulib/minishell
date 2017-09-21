/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 14:59:26 by kacoulib          #+#    #+#             */
/*   Updated: 2017/08/24 14:59:28 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check(char **file, char **line, char **tmp)
{
	int i;

	if (tmp == NULL)
	{
		*line = ft_strdup(*file);
		free(*file);
		*file = NULL;
	}
	else
	{
		i = ft_strchr((const char*)*file, '\n') - *file;
		*line = ft_strsub(*file, 0, i);
		*tmp = *file;
		*file = ft_strdup(*tmp + (i + 1));
		free(*tmp);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	int				i;
	char			*tmp;
	char			*chr;
	static char		*file;
	char			buff[BUFF_SIZE + 1];

	if (fd < 0 || !line)
		return (-1);
	if (!file && (!(file = ft_strnew(0))))
		return (-1);
	while (!(chr = ft_strchr((const char *)file, '\n')) &&
			(i = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[i] = '\0';
		tmp = file;
		file = ft_strjoin((char const*)tmp, (char const*)buff);
		free(tmp);
	}
	if (i == -1)
		return (-1);
	if (chr)
		return (check(&file, line, &tmp));
	if (i == 0 && ft_strlen(file) > 0)
		return (check(&file, line, NULL));
	return (0);
}
