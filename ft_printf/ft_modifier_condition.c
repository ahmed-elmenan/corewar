/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modifier_condition.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 00:14:36 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/25 15:57:24 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_is_j_modifier(char const *format, int *i, t_data1 *data)
{
	return ((ft_strnstr2(format, "j", 1, *i)) &&
			ft_int_max_detected(data, i));
}

int	ft_is_z_modifier(char const *format, int *i, t_data1 *data)
{
	return ((ft_strnstr2(format, "z", 1, *i)) &&
			ft_size_t_detected(data, i));
}

int	ft_is_h_modifier(char const *format, int *i, t_data1 *data)
{
	return ((ft_strnstr2(format, "h", 1, *i)) &&
			ft_short_length_detected(data, i));
}
