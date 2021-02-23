/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 00:44:16 by ahel-men          #+#    #+#             */
/*   Updated: 2019/04/14 00:45:37 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	void *tmp;

	tmp = ft_memchr(src, c, n);
	if (tmp)
	{
		dst = ft_memcpy(dst, src, tmp - src + 1);
		return (ft_memchr(dst, c, n) + 1);
	}
	ft_memcpy(dst, src, n);
	return (NULL);
}
