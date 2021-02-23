/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:50:46 by ahel-men          #+#    #+#             */
/*   Updated: 2019/11/13 17:53:01 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(int size)
{
	char *tab;

	if (!(tab = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(tab, size + 1);
	return (tab);
}
