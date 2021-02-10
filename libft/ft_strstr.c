/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:55:26 by anel-bou          #+#    #+#             */
/*   Updated: 2021/02/10 19:32:23 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char				*ft_strstr(const char *big, const char *small)
{
	char	*ptr;

	ptr = (char *)big;
	while (*ptr || !*small)
	{
		if (!*small || !ft_strncmp(ptr, small, ft_strlen(small)))
			return (ptr);
		ptr++;
	}
	return (NULL);
}

