/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_detect_options.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 11:25:51 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/25 15:57:24 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_detect_plus(t_list2 **list, char *tab, char *str, t_data1 *data)
{
	if (ft_plus_flag_condition(list, str, tab))
	{
		data->ret += 1;
		ft_putchar('+');
		data->len--;
	}
	else if (ft_negative_nb_condition(list, str, data, tab) &&
			data->inf != 1337)
	{
		data->ret += 1;
		ft_putchar('-');
		(*list)->sign = 1;
	}
}

void	ft_detect_minus(t_list2 **list, char *tab, char *str, t_data1 *data)
{
	if (ft_minus_flag_with_negative_nb_condition(list, str) &&
			data->inf != 1337)
	{
		if ((*list)->precision != 0)
			(data->len)--;
		ft_putchar('-');
		data->ret += 1;
		(*list)->clean = 0;
	}
	ft_print_string(list, tab, data);
}

void	ft_detect_width(t_list2 **list, char *tab, char *str, t_data1 *data)
{
	data->y = -1;
	while (++(data->y) < data->len)
	{
		if (ft_octal_sign_condition(list, str, data))
			ft_putchar('0');
		else if (ft_zero_flag_condition(list) &&
				data->space_d != 1337 && data->inf != 1337)
			ft_putchar('0');
		else if (ft_negative_sign_after_width(list, str, data) &&
				data->inf != 1337)
		{
			data->minus = 1;
			ft_putchar('-');
		}
		else if (ft_plus_in_width_condition(list, str, data, tab) &&
				data->space_d != 1337 && data->inf != 1337)
			ft_putchar('+');
		else
			ft_putchar(' ');
		data->ret += 1;
	}
}

void	ft_detect_negative_nb(t_list2 **lst, char *tab, char *s, t_data1 *dt)
{
	if (ft_ng_sign_condition(lst, s, dt, tab))
	{
		ft_putchar('-');
		dt->ret += 1;
	}
}

void	ft_print_string(t_list2 **list, char *tab, t_data1 *data)
{
	if ((*list)->cnv != 'c')
	{
		data->ret += ft_strlen(tab);
		ft_putstri(tab, 0);
	}
	else
		ft_putchar(tab[0]);
}
