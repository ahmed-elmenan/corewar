/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:19:15 by ahel-men          #+#    #+#             */
/*   Updated: 2019/04/14 00:15:43 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*dst;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	k = ft_strlen(s) - 1;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	if (!s[i])
		return (ft_strdup(""));
	while (s[k] == ' ' || s[k] == '\n' || s[k] == '\t')
		k--;
	if (!(dst = (char *)malloc((k - i) + 2)))
		return (NULL);
	while (s[i] && i <= k)
		dst[j++] = s[i++];
	dst[j] = '\0';
	return (dst);
}
