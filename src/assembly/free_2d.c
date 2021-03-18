/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:46:23 by aybouras          #+#    #+#             */
/*   Updated: 2021/03/18 15:07:22 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	free_2d(char **array, int len)
{
	int row;

	row = 0;
	if (array)
	{
		while (row < len)
		{
			ft_strdel(&array[row]);
			row++;
		}
		free(array);
		array = NULL;
	}
}
