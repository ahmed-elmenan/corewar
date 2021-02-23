/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:33:32 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 03:40:38 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_intlen_u(unsigned long long n)
{
	size_t count;

	count = 0;
	while (n)
	{
		if (n / 10)
		{
			count++;
			n /= 10;
		}
		else if (n / 10 == 0)
			break ;
	}
	return (count + 1);
}

char	*ft_itoa_u(unsigned long long nb)
{
	char	*tab;
	size_t	i;
	size_t	count;

	i = 0;
	count = ft_intlen_u(nb);
	tab = ft_strnew(count);
	tab[count] = '\0';
	if (!tab)
		return (NULL);
	while (count-- && nb / 10 != 0)
	{
		tab[count] = (nb % 10) + 48;
		nb /= 10;
	}
	tab[count] = nb + 48;
	return (tab);
}
