/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_addition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:40:47 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 05:24:53 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_adjust_numbers2(char *tmp, char *arr)
{
	int		i;
	int		len;
	int		k;
	char	*str;

	i = 0;
	k = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	str[ft_strlen(tmp)] = '\0';
	i = ft_strlen(tmp) - ft_strlen(arr);
	len = ft_strlen(arr);
	while (arr[k] || i)
	{
		if (!arr[k])
		{
			str[len++] = '0';
			i--;
		}
		else
		{
			str[k] = arr[k];
			k++;
		}
	}
	return (str);
}

char	*ft_float_addition(char *f1, char *f2)
{
	t_add	add;
	char	*man;

	if (ft_strlen(f1) > ft_strlen(f2) && (add.str2 = ft_strdup(f1)))
		add.str = ft_adjust_numbers2(f1, f2);
	else if (ft_strlen(f2) > ft_strlen(f1) && (add.str2 = ft_strdup(f2)))
		add.str = ft_adjust_numbers2(f2, f1);
	else
		ft_store_string(&add, f1, f2);
	man = ft_man_allocate(&add);
	while (--(add.count) >= 0 || add.carry)
	{
		if (add.count >= 0 && add.str[add.count] == '.')
		{
			ft_handle_add(&add, man);
			break ;
		}
		if (add.count >= 0)
			ft_store_nb(&add);
		ft_make_operation2(man, &add);
	}
	ft_strdel(&add.str);
	ft_strdel(&add.str2);
	return (man);
}
