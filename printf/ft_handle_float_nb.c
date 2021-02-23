/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_float_nb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 20:52:41 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 03:16:06 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_handle_nan(t_data *data)
{
	char *res;

	res = NULL;
	if (data->cnv == 'F')
		res = ft_strdup("NAN");
	else if (data->cnv == 'f')
		res = ft_strdup("nan");
	data->space_d = 1337;
	return (res);
}

void	ft_handle_foat_hash_flag(t_calc *calc)
{
	calc->tmp = calc->res;
	calc->res = ft_strjoin(calc->res, ".");
	ft_strdel(&calc->tmp);
}

void	ft_handle_foat_zero(t_calc *calc)
{
	calc->norm = ft_strdup("00");
	calc->res = ft_strdup("00");
	calc->index = 1;
	calc->len = 1337;
}

void	ft_handle_foat_nb(t_float flt, t_calc *calc)
{
	ft_calc_mantissa(calc, flt);
	calc->mantissa[0] = flt.ieee.int_part + '0';
	ft_calculate_exponent(calc);
	ft_handle_decimal_point(calc);
	ft_build_number(calc);
}

void	ft_handle_decimal_point(t_calc *calc)
{
	char *tmp;

	calc->index = ft_save_deciaml_point_index(calc->mantissa) +
		ft_save_deciaml_point_index(calc->exp_power);
	calc->integer = ft_remove_decimal_point(calc->mantissa);
	calc->tmp = calc->exp_power;
	tmp = calc->exp_power;
	calc->exp_power = ft_remove_decimal_point(calc->exp_power);
	ft_strdel(&tmp);
	ft_strdel(&calc->mantissa);
}
