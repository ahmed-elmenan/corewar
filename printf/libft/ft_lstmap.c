/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:37:36 by ahel-men          #+#    #+#             */
/*   Updated: 2019/04/19 23:33:03 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*fresh;

	if (!lst || !f)
		return (NULL);
	fresh = f(lst);
	tmp = fresh;
	while (lst->next)
	{
		if (!(fresh->next = f(lst->next)))
		{
			ft_lstdel(&tmp, &ft_lsterase);
			return (NULL);
		}
		fresh = fresh->next;
		lst = lst->next;
	}
	fresh->next = NULL;
	return (tmp);
}
