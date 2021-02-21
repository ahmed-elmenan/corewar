/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:22:01 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 05:01:22 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flag_search(char const *format, t_list2 **list, int *i)
{
	if (format[*i] == '+')
		(*list)->flag |= F_PLUS;
	else if (format[*i] == '-')
		(*list)->flag |= F_MINUS;
	else if (format[*i] == '0')
		(*list)->flag |= F_ZERO;
	else if (format[*i] == '#')
		(*list)->flag |= F_HASH;
	return ((*list)->flag);
}

void	ft_struct_init(t_list2 **list, t_data *data)
{
	(*list)->flag = 0;
	(*list)->width = 0;
	(*list)->precision = -1;
	(*list)->is_nb = 0;
	data->ast_w = 0;
	data->ast_p = 0;
	data->len = 0;
}

int		ft_define_precision(char const *f, t_list2 **list, int *i, t_data *d)
{
	int		len;
	char	*str;

	if (!(ft_isdigit(f[*i + 1]) && d->u != 'u'))
		(*list)->precision = 0;
	len = ft_get_length(f, *i);
	++*i;
	str = ft_strsub(f, *i, len - *i);
	(*list)->precision = ft_atoi(str);
	ft_memdel((void **)&str);
	*i = len - 1;
	return (1);
}

int		ft_define_width(char const *format, t_list2 **list, int *i)
{
	int		len;
	char	*str;

	len = ft_get_length(format, *i);
	str = ft_strsub(format, *i, len - *i);
	(*list)->width = ft_atoi(str);
	if ((*list)->width == (int)2147483649)
		(*list)->width = 0;
	ft_memdel((void **)&str);
	*i = len;
	return (1);
}

int		ft_place_index(int *i, t_data *data)
{
	if (data->check)
		*i += data->check + 1;
	else
		*i += 1;
	data->check = 0;
	data->pass = 1;
	return (1);
}
