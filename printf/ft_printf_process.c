/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 10:16:33 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 04:50:07 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_process(t_list2 *tmp, t_data *data)
{
	ft_list_initializer(tmp, data);
	ft_detect_asterisk(tmp, data);
	ft_param(tmp, data);
	ft_conversion_builder(tmp, data);
}

void	ft_print_no_type(const char *format, t_data *data)
{
	ft_putchar(format[data->i]);
	data->ret += 1;
	(data->i)++;
}

void	ft_detect_precision(t_list2 **list, char **tab, char *str, t_data *data)
{
	if ((*list)->cnv == 'c')
	{
		*tab = str;
		data->len = (*list)->width - 1;
		data->ret += 1;
	}
	else
		*tab = ft_make_precision(list, str, data);
}

void	ft_detect_space_d(t_list2 **list, char *str, t_data *data)
{
	if (data->space_d == 1 && !((*list)->flag & F_PLUS) && str[0] != '-')
	{
		ft_putchar(' ');
		(data->len)--;
		data->space_d = 0;
		data->ret += 1;
	}
}

void	ft_detect_hash(t_list2 **list, char *str, t_data *data, int x)
{
	if ((*list)->is_nb == 8 && (*list)->precision <= x &&
			((*list)->width <= ft_strlen(str) ||
				((*list)->flag & F_MINUS && (data->len)--)))
	{
		if ((*list)->width == 1)
			data->len = 0;
		data->ret += 1;
		ft_putchar('0');
	}
	else if ((*list)->is_nb == 15 && !(*list)->hex_sign && (data->len -= 2))
	{
		data->ret += 2;
		if ((*list)->cnv == 'X')
			ft_putstr("0X");
		else
			ft_putstr("0x");
	}
}
