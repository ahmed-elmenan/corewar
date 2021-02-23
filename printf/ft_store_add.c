/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 05:19:37 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 05:26:50 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_make_operation2(char *man, t_add *add)
{
	add->res = add->nb1 + add->nb2 + add->carry;
	add->carry = add->res / 10;
	man[add->count] = add->res % 10 + '0';
}

void	ft_handle_add(t_add *add, char *man)
{
	man[add->count--] = '.';
	if (add->carry)
		man[add->count] = add->res / 10 + '0';
	else
		man[add->count] = '0';
}

void	ft_store_nb(t_add *add)
{
	add->nb1 = add->str[add->count] - '0';
	add->nb2 = add->str2[add->count] - '0';
}

void	ft_store_string(t_add *add, char *f1, char *f2)
{
	add->str = ft_strdup(f1);
	add->str2 = ft_strdup(f2);
}

char	*ft_man_allocate(t_add *add)
{
	char	*man;

	man = NULL;
	add->count = ft_strlen(add->str);
	man = (char *)malloc(sizeof(char) * (ft_strlen(add->str) + 1));
	man[ft_strlen(add->str)] = '\0';
	add->carry = 0;
	return (man);
}
