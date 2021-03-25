/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:15:50 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/25 15:57:24 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_verify_nb(t_float flt, t_data1 *data, t_list2 **list)
{
	char *res;
	char *tmp;

	res = NULL;
	if (flt.ieee.mantissa != 0)
		res = ft_handle_nan(data);
	else
	{
		if (data->cnv == 'F')
			res = ft_strdup("INF");
		else if (data->cnv == 'f')
			res = ft_strdup("inf");
		data->inf = 1337;
		if ((*list)->flag & F_PLUS && !flt.ieee.sign)
		{
			tmp = res;
			res = ft_strjoin("+", res);
			ft_strdel(&tmp);
		}
	}
	return (res);
}

void	ft_make_point(t_list2 **list, t_calc *calc)
{
	calc->tmp = calc->res;
	calc->res = ft_add_decimal_point(list, calc->res, calc->index);
	ft_strdel(&calc->tmp);
}

void	ft_make_rounding(t_calc *calc)
{
	calc->len = ft_strlen(calc->res);
	if (calc->len < ft_strlen(calc->norm) && calc->norm[calc->len] >= '5' &&
			calc->norm[calc->len] <= '9')
		ft_build_rounding(calc);
	ft_strdel(&calc->norm);
}

int		ft_hash_condition(t_list2 **list, t_data1 *data)
{
	return (((*list)->flag & F_HASH) && !(*list)->precision &&
			data->inf != 1337 && data->space_d != 1337);
}

char	*ft_build_float(t_list2 **list, t_data1 *data)
{
	t_float	flt;
	t_calc	calc;

	flt.nb = data->f;
	calc.bias = flt.ieee.exponent - 16383;
	if (calc.bias >= 16384)
		calc.res = ft_verify_nb(flt, data, list);
	else
	{
		if (!flt.ieee.mantissa && !flt.ieee.exponent)
			ft_handle_foat_zero(&calc);
		else
			ft_handle_foat_nb(flt, &calc);
		ft_struct_data1_init(flt, &calc, (*list)->precision);
		if (!(*list)->precision)
			ft_handle_precision_zero(&calc);
		ft_make_rounding(&calc);
		ft_make_point(list, &calc);
	}
	if (flt.ieee.sign)
		ft_handle_negative_sign(&calc);
	if (ft_hash_condition(list, data))
		ft_handle_foat_hash_flag(&calc);
	(*list)->precision = -1;
	return (calc.res);
}
