/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_deciaml_point_index.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 18:24:16 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 04:54:33 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_save_deciaml_point_index(char *str)
{
	int i;
	int count;

	count = 0;
	i = ft_strlen(str);
	while (--i)
	{
		if (str[i] == '.')
			return (count);
		count++;
	}
	return (0);
}

char	*ft_remove_decimal_point(char *str)
{
	char	*res;
	int		len;
	int		y;
	int		i;

	len = ft_strlen(str);
	res = (char *)ft_memalloc(sizeof(char) * len + 1);
	y = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '.')
			continue ;
		res[y++] = str[i];
	}
	return (res);
}

char	*ft_add_decimal_point(t_list2 **list, char *norm, int index)
{
	char	*res;
	int		len;
	int		y;
	int		i;

	len = ft_strlen(norm);
	if (!(*list)->precision)
	{
		res = (char *)ft_memalloc(sizeof(char) * len + 1);
		res[len] = '\0';
	}
	else
	{
		res = (char *)ft_memalloc(sizeof(char) * len + 2);
		res[len + 1] = '\0';
	}
	y = 0;
	i = 0;
	while (norm[i])
	{
		if (i == index)
			res[y++] = '.';
		res[y++] = norm[i++];
	}
	return (res);
}

int		ft_detect_decimal_point(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '.')
			return (++i);
	}
	return (-1);
}
