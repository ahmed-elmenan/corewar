/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_mantissa.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:11:31 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/25 15:57:25 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_struct_data1_init(t_float flt, t_calc *calc, int pr)
{
	char *tmp;

	tmp = NULL;
	calc->p_pos = ft_strlen(calc->norm) - calc->index;
	tmp = calc->res;
	calc->res = ft_strdup(calc->norm);
	if (!flt.ieee.mantissa && !flt.ieee.exponent)
		ft_strdel(&tmp);
	calc->fract_part_len = calc->index;
	calc->index = ft_strlen(calc->norm) - calc->index;
	calc->res = ft_build_precision(calc->res, calc->index, pr,
			calc->fract_part_len);
}

void	ft_calc_mantissa(t_calc *calc, t_float flt)
{
	if (!flt.ieee.mantissa)
		calc->mantissa = ft_strdup("0");
	else
		calc->mantissa = ft_calculate_mantissa(flt.ieee.mantissa);
	calc->mantissa[0] = flt.ieee.int_part + '0';
	calc->neg_sign = 0;
}

void	ft_build_number(t_calc *calc)
{
	if (calc->neg_sign)
		calc->norm = ft_make_mulitiplication(calc->integer, calc->exp_power, 0);
	else
		calc->norm = ft_make_mulitiplication(calc->integer, calc->exp_power, 1);
	ft_strdel(&calc->exp_power);
	ft_strdel(&calc->integer);
}

void	ft_handle_precision_zero(t_calc *calc)
{
	calc->tmp = calc->res;
	calc->res = ft_strsub(calc->res, 0, calc->index);
	ft_strdel(&calc->tmp);
}

void	ft_handle_negative_sign(t_calc *calc)
{
	calc->tmp = calc->res;
	calc->res = ft_strjoin("-", calc->res);
	ft_strdel(&calc->tmp);
}
