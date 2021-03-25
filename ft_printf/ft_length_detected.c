/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_length_detected.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 11:14:44 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/25 15:57:24 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_long_long_length_detected(t_data1 *data, int *i)
{
	if (!data->length)
		data->length |= LEN_LL;
	(*i) += 2;
	data->check += 2;
	return (1);
}

int	ft_long_length_detected(t_data1 *data, int *i)
{
	if (!data->length)
		data->length |= LEN_L;
	(*i) += 1;
	data->check += 1;
	return (1);
}

int	ft_double_length_detected(t_data1 *data, int *i)
{
	if (!data->length)
		data->length |= LEN_LF;
	(*i) += 1;
	data->check += 1;
	return (1);
}

int	ft_size_t_detected(t_data1 *data, int *i)
{
	if (!data->length)
		data->length |= LEN_Z;
	(*i) += 1;
	data->check += 1;
	return (1);
}

int	ft_int_max_detected(t_data1 *data, int *i)
{
	if (!data->length)
		data->length |= LEN_J;
	(*i) += 1;
	data->check += 1;
	return (1);
}
