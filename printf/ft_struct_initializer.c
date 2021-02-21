/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_initializer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 11:37:15 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 05:03:54 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_data_initializer(t_data *data)
{
	data->i = 0;
	data->j = 0;
	data->print_count = 0;
	data->length = 0;
	data->count = 0;
	data->pass = 1;
	data->check = 0;
	data->ret = 0;
	data->space_d = 0;
	data->minus = 0;
	data->none = 0;
	data->inf = 0;
}

void	ft_conversion_builder(t_list2 *tmp, t_data *data)
{
	if (tmp->cnv == 'c')
		data->ret = ft_make_str(&tmp, &(data->res), data);
	else if (tmp->cnv == 's')
		data->ret = ft_make_str(&tmp, data->str, data);
	else if (tmp->cnv == 'p')
		data->ret = ft_make_hexa(&tmp, data);
	else if (tmp->cnv == 'd' || tmp->cnv == 'i')
		data->ret = ft_make_number(&tmp, data);
	else if (tmp->cnv == 'o')
		data->ret = ft_make_number(&tmp, data);
	else if (tmp->cnv == 'b')
		data->ret = ft_make_number(&tmp, data);
	else if (tmp->cnv == 'u')
		data->ret = ft_make_number(&tmp, data);
	else if (tmp->cnv == 'x' || tmp->cnv == 'X')
		data->ret = ft_make_hexa(&tmp, data);
	else if (tmp->cnv == 'f' || tmp->cnv == 'F')
		data->ret = ft_make_float(&tmp, data);
}

void	ft_detect_asterisk(t_list2 *tmp, t_data *data)
{
	if (data->ast_w && data->pass)
	{
		tmp->width = va_arg(data->args, int);
		if (tmp->width < 0)
		{
			tmp->width *= -1;
			tmp->flag |= F_MINUS;
		}
	}
	if (data->ast_p && data->pass)
		tmp->precision = va_arg(data->args, int);
}

t_list2	*ft_list_allocate(t_list2 **tmp, t_list2 **head, int *j)
{
	if (!(*j))
	{
		if (!(*head = (t_list2 *)ft_memalloc(sizeof(t_list2))))
			return (NULL);
		*tmp = *head;
		(*j)++;
	}
	else
	{
		if (!((*tmp)->next = (t_list2 *)ft_memalloc(sizeof(t_list2))))
			return (NULL);
		(*tmp) = (*tmp)->next;
	}
	(*tmp)->next = NULL;
	return (*tmp);
}

void	ft_list_initializer(t_list2 *tmp, t_data *data)
{
	tmp->cnv = data->cnv;
	tmp->is_nb = 0;
}
