/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:42:17 by ahel-men          #+#    #+#             */
/*   Updated: 2021/02/23 01:42:33 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int	ft_binary_search(char *tab, char c)
{
	int start;
	int end;
	int mid;
	int res;

	start = 0;
	end = strlen(tab) - 1;
	mid = 0;
	while (start <= end)
	{
		mid = (start + end) / 2;
		res = c - tab[mid];
		if (!res)
			return (mid);
		else if (res < 0)
			end = mid - 1;
		else if (res > 0)
			start = mid + 1;
	}
	return (-1);
}

int	ft_binary_search_2d(t_env *env, char *operation, t_op tab[16])
{
	int start;
	int end;
	int mid;
	int res;

	start = 0;
	end = 16;
	mid = 0;
	while (start <= end)
	{
		mid = (start + end) / 2;
		res = strcmp(operation, tab[mid].op_name);
		if (!res)
		{
			env->found_op = &tab[mid];
			return (mid);
		}
		else if (res < 0)
			end = mid - 1;
		else if (res > 0)
			start = mid + 1;
	}
	return (-1);
}
