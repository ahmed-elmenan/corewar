/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_confirm_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 14:08:53 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 00:25:24 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_size_t_length_detected(t_data *data, int *i)
{
	if (!data->length)
		data->length |= LEN_Z;
	(*i) += 1;
	data->check += 1;
	return (1);
}

char	ft_check_cnv(const char *format, int i, t_data *data)
{
	if (ft_detect_conv(format[i]))
	{
		data->count++;
		data->is_cnv = 1;
	}
	else
	{
		data->is_cnv = 0;
		data->pass = 0;
		data->length = 0;
		data->check -= 1;
	}
	return (format[i]);
}

int		ft_ignore_space(t_data *data, int *i)
{
	(*i) += 1;
	data->check += 1;
	return (1);
}

void	ft_detect_modifier(char const *format, int *i, t_data *data)
{
	while (!ft_detect_conv(format[*i]))
	{
		if ((ft_strnstr2(format, "hh", 2, *i)) &&
				ft_short_short_length_detected(data, i))
			continue ;
		else if (ft_is_h_modifier(format, i, data))
			continue ;
		else if ((ft_strnstr2(format, "ll", 2, *i)) &&
				ft_long_long_length_detected(data, i))
			continue ;
		else if ((ft_strnstr2(format, "l", 1, *i)) &&
				ft_long_length_detected(data, i))
			continue ;
		else if ((ft_strnstr2(format, "L", 1, *i)) &&
				ft_double_length_detected(data, i))
			continue ;
		else if (ft_is_z_modifier(format, i, data))
			continue ;
		else if (ft_is_j_modifier(format, i, data))
			continue ;
		else if (format[*i] == ' ' && ft_ignore_space(data, i))
			continue ;
		else
			break ;
	}
}

void	ft_check_space_d(t_data *data, int *i)
{
	if (data->cnv == 'd' || data->cnv == 'i' ||
			data->cnv == 'f' || data->cnv == 'F')
		data->space_d = 1;
	*i += 1;
}
