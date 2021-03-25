/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:11:19 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/25 15:57:24 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_pr(t_list2 **list, t_data1 *data)
{
	if ((*list)->precision >= 2147483647)
	{
		if ((*list)->is_nb)
			exit(0);
		else if (data->cnv == 's')
			(*list)->precision = ft_strlen(data->str);
	}
	return (1);
}
