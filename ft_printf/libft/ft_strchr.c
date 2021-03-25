/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:10:04 by ahel-men          #+#    #+#             */
/*   Updated: 2019/04/14 00:41:02 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = ft_strlen(((char *)s));
	if (!c)
		return (((char *)s) + i);
	i = 0;
	while (((unsigned char *)s)[i])
	{
		if (((unsigned char *)s)[i] == c)
			return (((char *)s) + i);
		i++;
	}
	return (NULL);
}
