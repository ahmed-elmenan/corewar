/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 15:18:15 by ahel-men          #+#    #+#             */
/*   Updated: 2019/04/09 21:13:38 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	i = 0;
	if (!*needle)
		return (((char *)haystack));
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] || !needle[j])
		{
			if (!needle[j])
				return (((char *)haystack) + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
