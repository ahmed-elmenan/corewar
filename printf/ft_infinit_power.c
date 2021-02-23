/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infinit_power.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 15:35:52 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 03:38:06 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_make_infinit_power(char *nb, int p, int flag)
{
	char *res;
	char *tmp;

	res = ft_strdup("1");
	tmp = NULL;
	while (p > 0)
	{
		if (1 & p)
		{
			tmp = res;
			res = ft_make_mulitiplication(res, nb, flag);
			if (tmp)
				ft_strdel(&tmp);
		}
		tmp = nb;
		nb = ft_make_mulitiplication(nb, nb, flag);
		if (tmp)
			ft_strdel(&tmp);
		p >>= 1;
	}
	ft_strdel(&nb);
	return (res);
}

int		ft_make_power(int nb, int p)
{
	int res;

	res = 1;
	while (p > 0)
	{
		if (1 & p)
			res *= nb;
		nb *= nb;
		p >>= 1;
	}
	return (res);
}

char	*ft_negative_power(int power, int flag)
{
	char	*res;
	char	*tmp;
	char	*zeros;
	int		len;

	res = ft_make_infinit_power(ft_strdup("5"), power, flag);
	if (power > ft_strlen(res))
	{
		len = power - ft_strlen(res);
		zeros = (char *)malloc(sizeof(char *) * (len + 1));
		zeros[len] = '\0';
		zeros = ft_memset((char *)zeros, '0', len);
		tmp = res;
		res = ft_strjoin(zeros, res);
		ft_strdel(&tmp);
		ft_strdel(&zeros);
	}
	tmp = res;
	res = ft_strjoin("0.", res);
	ft_strdel(&tmp);
	return (res);
}
