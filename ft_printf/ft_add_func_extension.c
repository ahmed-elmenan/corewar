/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_func_extension.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:46:23 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/25 15:57:24 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_adjust_numbers1(char *tmp, char *arr)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	k = 0;
	str = (char *)ft_memalloc(sizeof(char) * (ft_strlen(tmp) + 1));
	str[ft_strlen(tmp)] = '\0';
	while (tmp[i])
	{
		if (i < ft_strlen(tmp) - ft_strlen(arr))
			str[i++] = '0';
		else
			str[i++] = arr[k++];
	}
	return (str);
}

int		ft_list_len(t_list3 *list)
{
	t_list3	*tmp;
	int		count;

	count = 0;
	tmp = list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	ft_listdel(t_list3 **alst)
{
	t_list3 *tmp;

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

int		ft_short_short_length_detected(t_data1 *data, int *i)
{
	if (!data->length)
		data->length |= LEN_HH;
	(*i) += 2;
	data->check += 2;
	return (1);
}

int		ft_short_length_detected(t_data1 *data, int *i)
{
	if (!data->length)
		data->length |= LEN_H;
	(*i) += 1;
	data->check += 1;
	return (1);
}
