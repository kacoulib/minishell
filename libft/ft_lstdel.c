/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:23:52 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/07 15:49:56 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alts, void (*del)(void *, size_t))
{
	t_list	*next;

	while (*alts)
	{
		next = (*alts)->next;
		ft_lstdelone(alts, del);
		*alts = next;
	}
}
