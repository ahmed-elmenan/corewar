/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 01:07:12 by ahel-men          #+#    #+#             */
/*   Updated: 2019/04/18 11:46:50 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_words_count(const char *str, char c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	if (!str[i])
		return (0);
	if (str[0] != c)
		count++;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] != c && str[i - 1] == c)
			count++;
		i++;
	}
	return (count);
}
