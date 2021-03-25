/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:43:11 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 03:39:45 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa2(long long n)
{
	char				*tab;
	size_t				i;
	size_t				count;
	unsigned long long	nb;

	i = 0;
	count = ft_intlen2(n);
	tab = ft_strnew(count);
	tab[count] = '\0';
	if (!tab)
		return (NULL);
	if (n < 0 && (nb = n * -1))
		tab[i++] = '-';
	else
		nb = n;
	while (count-- && nb / 10 != 0)
	{
		tab[count] = (nb % 10) + 48;
		nb /= 10;
	}
	tab[count] = nb + 48;
	return (tab);
}
