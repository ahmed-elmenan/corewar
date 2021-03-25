/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:01:20 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/25 15:57:24 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_make_float(t_list2 **list, t_data1 *data)
{
	char	*str;
	int		ret;

	(*list)->is_nb = 10;
	str = ft_build_float(list, data);
	ret = ft_make_str(list, str, data);
	ft_strdel(&str);
	return (ret);
}
