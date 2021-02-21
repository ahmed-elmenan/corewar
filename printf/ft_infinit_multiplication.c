/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infinit_multiplication.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 08:43:05 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 05:51:01 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_make_mulitiplication(char *num1, char *num2, int flag)
{
	t_mlp	mlp;

	if ((*num1 == '0' && !*(num1 + 1)) || (*num2 == '0' && !*(num2 + 1)))
		return (ft_strdup("0"));
	ft_struct_init3(num1, num2, &mlp);
	while (--mlp.i >= 0)
	{
		ft_find_curr_pos(num1, &mlp);
		while (--mlp.j >= 0)
		{
			mlp.product = (num1[mlp.i] - '0') * (num2[mlp.j] - '0');
			mlp.sum = mlp.carry + mlp.product +
				((mlp.result[mlp.curr_postion] - '0'));
			if ((mlp.result[mlp.curr_postion] = (char)(mlp.sum % 10 + '0')))
				mlp.count++;
			mlp.carry = mlp.sum / 10;
			mlp.curr_postion--;
		}
		if (mlp.carry > 0 && mlp.count++)
			mlp.result[mlp.curr_postion] = mlp.carry + '0';
	}
	ft_handle_special_cases(&mlp, num1, num2, flag);
	ft_strdel(&mlp.tmp);
	return (mlp.result);
}
