/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:09:12 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/25 15:57:24 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_param(t_list2 *list, t_data1 *data)
{
	if (list->cnv == 'c')
		data->res = (char)va_arg(data->args, int);
	else if (list->cnv == 's')
	{
		data->str = va_arg(data->args, char *);
		if (!(data->str))
			data->str = "(null)";
	}
	else if (list->cnv == 'p')
		data->u = va_arg(data->args, unsigned long);
	else if (list->cnv == 'd' || list->cnv == 'i')
		ft_detect_length_s(data);
	else if (list->cnv == 'o' || list->cnv == 'u'
			|| list->cnv == 'x' || list->cnv == 'X' || list->cnv == 'b')
		ft_detect_length_u(data);
	else if (list->cnv == 'f' || list->cnv == 'F')
		ft_detect_length_f(data);
	data->length = 0;
}

char	*ft_malloc_len(t_list2 **list)
{
	char *tab;

	*list = NULL;
	if (!(tab = (char *)ft_memalloc(sizeof(char) * (*list)->width + 1)))
		return (NULL);
	tab[(*list)->width] = '\0';
	return (tab);
}

int		ft_check_err(const char *format, t_data1 *data)
{
	return (ft_error_cnv(format, data->i, data) &&
				(!data->pass || data->count--));
}

int		ft_parse(const char *format, t_data1 *data)
{
	t_list2 *head;
	t_list2 *tmp;

	while (format[data->i])
	{
		if (format[data->i] == '%' && ft_check_err(format, data))
		{
			if (!(ft_list_allocate(&tmp, &head, &(data->j))))
				return (0);
			if (format[data->i + 1] == '%')
				data->cnv = '%';
			if (!(ft_stock_format(format, &tmp, &(data->i), data)))
				continue ;
			ft_printf_process(tmp, data);
			if (!format[data->i])
				break ;
		}
		if (format[data->i] == '%' && data->none == 0)
			continue ;
		ft_print_no_type(format, data);
		data->none = 0;
	}
	if (head)
		ft_listdel2(&head);
	return (data->ret);
}

int		ft_printf(const char *format, ...)
{
	t_data1 data;

	ft_bzero(&data, sizeof(t_data1));
	if (!format)
		return (0);
	va_start(data.args, format);
	ft_data1_initializer(&data);
	data.ret = ft_parse(format, &data);
	va_end(data.args);
	return (data.ret);
}
