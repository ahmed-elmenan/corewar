/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:42:01 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 05:02:27 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strnstr2(const char *haystack, const char *needle, size_t len, int i)
{
	size_t	j;
	char	*str;

	if (!*needle)
		return (0);
	while (haystack[i] && len)
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j] && len--)
			j++;
		if (!needle[j] || !len)
		{
			str = ft_strdup(haystack + i);
			str[ft_strlen(needle)] = '\0';
			ft_strdel(&str);
			return (1);
		}
		i++;
		len--;
	}
	return (0);
}
