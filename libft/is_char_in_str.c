/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_char_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:39:01 by anel-bou          #+#    #+#             */
/*   Updated: 2021/01/27 11:28:47 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_char_in_str(char c, char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}