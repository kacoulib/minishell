/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:47:52 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/07 17:14:37 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*next;
	t_list	*r;

	if (!lst || !f)
		return (NULL);
	r = ft_lstnew(lst->content, lst->content_size);
	if (!(r))
		return (NULL);
	r = f(r);
	while (lst->next)
	{
		lst = lst->next;
		next = ft_lstnew(lst->content, lst->content_size);
		if (!next)
			return (NULL);
		ft_lstpush(r, f(next));
	}
	return (r);
}
