/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 23:10:00 by ahel-men          #+#    #+#             */
/*   Updated: 2019/04/18 11:46:22 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		sv;
	int		len;

	if (!s || !(arr = ft_newtab(ft_words_count(s, c))))
		return (NULL);
	sv = ft_words_count(s, c);
	i = 0;
	len = 0;
	while (i < sv)
	{
		while (s[len] == c)
			len++;
		j = len;
		while (s[len++])
		{
			if ((s[len] == c || !s[len]) && (arr[i] = ft_strsub(s, j, len - j)))
				break ;
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
