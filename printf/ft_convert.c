/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 08:23:08 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 00:44:30 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	ft_get_index(int res)
{
	int			i;
	static char	*tab = "0123456789abcdef";

	i = -1;
	while (tab[++i])
	{
		if (i == res)
			return (tab[i]);
	}
	return (0);
}

char	*ft_convert(unsigned long long n, int s, int m)
{
	int					res;
	unsigned long long	tmp;
	int					len;
	char				*str;

	len = 0;
	tmp = n;
	while (tmp)
	{
		tmp >>= s;
		len++;
	}
	if (!len)
		len = 1;
	str = ft_strnew(len);
	str[len] = '\0';
	while (len)
	{
		res = n & m;
		str[len - 1] = ft_get_index(res);
		n = n >> s;
		len--;
	}
	return (str);
}
