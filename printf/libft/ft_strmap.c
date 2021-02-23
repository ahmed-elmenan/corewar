/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 22:03:44 by ahel-men          #+#    #+#             */
/*   Updated: 2019/04/10 02:30:01 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*tab;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	if (!(tab = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[i])
	{
		tab[i] = f(s[i]);
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
