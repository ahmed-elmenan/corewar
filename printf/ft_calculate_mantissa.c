/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_mantissa.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:31:47 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/06 23:46:15 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_calculate_mantissa(unsigned long mantissa)
{
	char	*mts;
	char	*tmp;
	char	*power_res;
	int		i;

	mts = ft_strdup("0.0");
	i = 63;
	while (i >= 1)
	{
		if (1 & mantissa)
		{
			power_res = ft_negative_power(i, 1);
			tmp = mts;
			mts = ft_float_addition(mts, power_res);
			ft_strdel(&power_res);
			ft_strdel(&tmp);
		}
		mantissa >>= 1;
		i--;
	}
	return (mts);
}
