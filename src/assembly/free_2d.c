/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:46:23 by aybouras          #+#    #+#             */
/*   Updated: 2021/03/13 16:06:18 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
