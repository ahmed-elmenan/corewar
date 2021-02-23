/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 21:38:05 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 05:27:42 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_build_string(char *res, int fract_part_len, long pr)
{
	long len;
	char *tmp2;
	char *tmp;

	len = pr - fract_part_len;
	tmp2 = (char *)ft_memalloc(sizeof(char) * (len + 1));
	tmp2[len] = '\0';
	tmp2 = (char *)ft_memset((char *)tmp2, '0', len);
	tmp = res;
	res = ft_strjoin(res, tmp2);
	ft_strdel(&tmp2);
	ft_strdel(&tmp);
	return (res);
}

char	*ft_build_precision(char *res, int index, long pr, int fract_part_len)
{
	char *tmp;

	if (pr > 0 && pr < 2147100)
	{
		if (pr > fract_part_len)
			res = ft_build_string(res, fract_part_len, pr);
		else
		{
			tmp = res;
			res = ft_strsub(res, 0, index + pr);
			ft_strdel(&tmp);
		}
	}
	else
	{
		if (fract_part_len < 6)
			res = ft_build_string(res, fract_part_len, 6);
		else
		{
			tmp = res;
			res = ft_strsub(res, 0, index + 6);
			ft_strdel(&tmp);
		}
	}
	return (res);
}

int		ft_is_not_zero(char *norm, int len)
{
	while (norm[len])
	{
		if (norm[len] != '0')
			return (1);
		len++;
	}
	return (0);
}

void	ft_build_rounding(t_calc *calc)
{
	if (calc->norm[calc->len] != '5' || (calc->norm[calc->len] == '5' &&
				calc->res[calc->len - 1] == '5') ||
					(calc->norm[calc->len] == '5' &&
						(ft_is_not_zero(calc->norm, ++calc->len) ||
							((calc->res[calc->len - 1] - '0') % 2))))
	{
		calc->tmp = calc->res;
		calc->res = ft_make_addition(calc->res, "1");
		ft_strdel(&calc->tmp);
	}
	if (ft_strlen(calc->res) == calc->len + 1)
		calc->index++;
}

void	ft_calculate_exponent(t_calc *calc)
{
	if (calc->bias < 0)
	{
		calc->bias *= -1;
		calc->neg_sign = 1;
		calc->exp_power = ft_negative_power(calc->bias, 0);
	}
	else
		calc->exp_power = ft_make_infinit_power(ft_strdup("2"), calc->bias, 1);
}
