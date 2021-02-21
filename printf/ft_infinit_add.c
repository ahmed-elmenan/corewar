/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infinit_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 14:13:22 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 15:49:30 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_listdel2(t_list2 **alst)
{
	t_list2 *tmp;

	if (!alst)
		return ;
	while (*alst != NULL)
	{
		tmp = (*alst)->next;
		free(*alst);
		*alst = tmp;
	}
	*alst = NULL;
}

char	*store_number_in_array(t_list3 *list, t_add *add)
{
	t_list3 *tmp;

	tmp = NULL;
	add->str = (char *)malloc(sizeof(char) * (ft_list_len(list) + 1));
	add->str[ft_list_len(list)] = '\0';
	tmp = list;
	add->count = ft_list_len(list);
	while (tmp)
	{
		add->str[--add->count] = tmp->nb;
		tmp = tmp->next;
	}
	return (add->str);
}

void	ft_make_operation(t_list3 **tmp, t_add *add)
{
	add->res = add->nb1 + add->nb2 + add->carry;
	add->carry = add->res / 10;
	(*tmp)->nb = add->res % 10 + '0';
}

t_list3	*store_number_in_linked_list(t_add *add)
{
	t_list3 *tmp;
	t_list3 *list;

	list = (t_list3 *)ft_memalloc(sizeof(t_list3));
	tmp = list;
	while (--(add->count) >= 0 || add->carry)
	{
		if (add->count >= 0)
		{
			add->nb1 = add->str[add->count] - '0';
			add->nb2 = add->str2[add->count] - '0';
		}
		else if (add->count == -1)
		{
			add->nb1 = 0;
			add->nb2 = 0;
		}
		ft_make_operation(&tmp, add);
		if (!add->carry && add->count <= 0)
			break ;
		tmp->next = (t_list3 *)ft_memalloc(sizeof(t_list3));
		tmp = tmp->next;
	}
	tmp->next = NULL;
	return (list);
}

char	*ft_make_addition(char *s1, char *s2)
{
	t_add	add;
	t_list3 *list;

	list = NULL;
	add.carry = 0;
	if (ft_strlen(s1) > ft_strlen(s2) && (add.str2 = ft_strdup(s1)))
		add.str = ft_adjust_numbers1(s1, s2);
	else if (ft_strlen(s2) > ft_strlen(s1) && (add.str2 = ft_strdup(s2)))
		add.str = ft_adjust_numbers1(s2, s1);
	else
	{
		add.str = ft_strdup(s1);
		add.str2 = ft_strdup(s2);
	}
	add.count = ft_strlen(add.str);
	list = store_number_in_linked_list(&add);
	ft_strdel(&add.str);
	ft_strdel(&add.str2);
	add.str = store_number_in_array(list, &add);
	ft_listdel(&list);
	return (add.str);
}
