/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:23:04 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/25 15:57:24 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_stock_format(const char *f, t_list2 **list, int *i, t_data1 *data)
{
	ft_struct_init(list, data);
	while (f[++*i])
	{
		if (f[*i] == ' ')
			ft_check_space_d(data, i);
		(*list)->flag = ft_flag_search(f, list, i);
		if (f[*i] >= '1' && f[*i] <= '9')
			ft_define_width(f, list, i);
		else if (f[*i] == '*' && (*i += 1))
			data->ast_w = 1;
		if (f[*i] == '.' && f[*i + 1] != '*' &&
				ft_define_precision(f, list, i, data))
			continue;
		else if (f[*i] == '.' && f[*i + 1] == '*' && (*i += 2))
			data->ast_p = 1;
		if (ft_isalpha(f[*i]) && ft_place_index(i, data))
			return (1);
		else if (!detect_options(f[*i]) && !ft_isalnum(f[*i]) &&
				(data->none = 1))
			return (1);
	}
	return (1);
}

void	ft_detect_length_s(t_data1 *data)
{
	if (data->length & LEN_L)
		data->d = va_arg(data->args, long);
	else if (data->length & LEN_LL)
		data->d = va_arg(data->args, long long);
	else if (data->length & LEN_H)
		data->d = (short)va_arg(data->args, int);
	else if (data->length & LEN_HH)
		data->d = (char)va_arg(data->args, int);
	else if (data->length & LEN_J)
		data->d = va_arg(data->args, intmax_t);
	else
		data->d = va_arg(data->args, int);
}

void	ft_detect_length_u(t_data1 *data)
{
	if (data->length & LEN_L)
		data->u = va_arg(data->args, unsigned long);
	else if (data->length & LEN_LL)
		data->u = va_arg(data->args, unsigned long long);
	else if (data->length & LEN_H)
		data->u = (unsigned short)va_arg(data->args, unsigned int);
	else if (data->length & LEN_HH)
		data->u = (unsigned char)va_arg(data->args, unsigned int);
	else if (data->length & LEN_Z)
		data->u = va_arg(data->args, size_t);
	else if (data->length & LEN_J)
		data->u = va_arg(data->args, uintmax_t);
	else
		data->u = va_arg(data->args, unsigned int);
}

void	ft_detect_length_f(t_data1 *data)
{
	if (data->length & LEN_LF)
		data->f = va_arg(data->args, long double);
	else
		data->f = va_arg(data->args, double);
}

void	ft_capitalize(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	}
}
