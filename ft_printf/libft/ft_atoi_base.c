/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 15:59:26 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/27 19:12:12 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_power(int nb, int power)
{
	int n;
	int i;

	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	i = 1;
	n = 1;
	while (i <= power)
	{
		n = n * nb;
		i++;
	}
	return (n);
}

char	*convert_tolower(char *str)
{
	int		i;
	char	*dest;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	dest = ft_strcpy(dest, str);
	i = -1;
	while (dest[++i] != '\0')
	{
		if (dest[i] >= 'A' && dest[i] <= 'Z')
			dest[i] = dest[i] + 32;
	}
	return (dest);
}

int		get_index(char *str, char *tab)
{
	static	int	i;
	int			j;

	if (!i)
		i = ft_strlen(str);
	while (str[--i])
	{
		j = -1;
		while (tab[++j])
		{
			if (str[i] == tab[j])
				return (j);
		}
	}
	return (0);
}

int		ft_atoi_base(int base, char *str)
{
	int			res;
	int			len;
	char		*dest;
	static char	*tab = "0123456789abcdef";
	int			x;

	x = 0;
	res = 0;
	dest = convert_tolower(str);
	len = ft_strlen(dest);
	while (len > 0)
	{
		res += get_index(dest, tab) * ft_power(base, x++);
		len--;
	}
	return (res);
}
