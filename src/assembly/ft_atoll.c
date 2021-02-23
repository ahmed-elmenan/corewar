/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:41:30 by ahel-men          #+#    #+#             */
/*   Updated: 2021/02/23 01:41:57 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static long long	ascii_to_int(const char *str, int index)
{
	long long	result;

	result = 0;
	while (ft_isdigit(str[index]))
	{
		result = result * 10 + (str[index] - '0');
		index++;
	}
	return (result);
}

t_boolean			ft_atoll(const char *str)
{
	long long	result;
	int			sign;
	int			index;

	result = 0;
	sign = 1;
	index = 0;
	while (IS_SPACE(str[index]))
		index++;
	if (str[index] == '-')
	{
		sign = -1;
		index++;
	}
	else if (str[index] == '+')
	{
		sign = 1;
		index++;
	}
	result = ascii_to_int(str, index);
	if (result > INT_MAX || (result * sign) < INT_MIN)
		return (TRUE);
	return (FALSE);
}
