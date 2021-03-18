/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_begins_with.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:13:06 by anel-bou          #+#    #+#             */
/*   Updated: 2021/03/18 16:28:51 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		str_begins_with(char *str, char *begin_part)
{
	int i;

	i = -1;
	if (!(*str) || !(*begin_part))
		return (0);
	while (str[++i] && begin_part[i] && str[i] == begin_part[i])
		;
	if (!begin_part[i])
		return (1);
	return (0);
}
