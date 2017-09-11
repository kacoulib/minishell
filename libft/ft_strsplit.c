/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 16:32:02 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/06 16:39:26 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcount(char const *s, char c)
{
	int		in_word;
	size_t	n_word;
	size_t	i;

	in_word = 0;
	n_word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!in_word)
				n_word++;
			in_word = 1;
		}
		else
			in_word = 0;
		i++;
	}
	return (n_word);
}

static char		*ft_wordpicker(char *str, char **ptr, char c)
{
	size_t	word_begin;
	size_t	word_end;
	char	*word;

	word_begin = 0;
	word_end = 0;
	while (str[word_begin] == c)
		word_begin++;
	word_end = word_begin;
	while (str[word_end] && str[word_end] != c)
		word_end++;
	word = ft_strsub(str, word_begin, word_end - word_begin);
	*ptr = word;
	return (str + word_end);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	n_word;
	char	**ptr;
	char	*str;
	size_t	i;

	ptr = NULL;
	i = 0;
	if (s)
	{
		str = (char*)s;
		n_word = ft_wordcount(s, c);
		ptr = (char**)ft_memalloc((n_word + 1) * sizeof(char*));
		if (!ptr)
			return (NULL);
		while (i < n_word)
			str = ft_wordpicker(str, ptr + i++, c);
		ptr[n_word] = 0;
	}
	return (ptr);
}
