/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_no_precision.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 19:06:51 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 15:44:16 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_handle_no_precision(t_list2 **lst, char *s, t_data *dt, char *p)
{
	char *tab;

	tab = NULL;
	if (s[0] == '-' && (*lst)->is_nb)
		(*lst)->clean = 1;
	if ((*lst)->cnv == 'c')
		dt->len = (*lst)->width - 1;
	else
		dt->len = (*lst)->width - ft_strlen(p);
	tab = ft_strdup(p);
	return (tab);
}

char	*ft_add_hexa_prefix(t_list2 **list, t_data *data, char *tab)
{
	char *tmp;

	tmp = NULL;
	tmp = tab;
	if ((*list)->cnv == 'X')
		tab = ft_strjoin("0X", tab);
	else
		tab = ft_strjoin("0x", tab);
	data->len -= 2;
	(*list)->hex_sign = 1;
	ft_strdel(&tmp);
	return (tab);
}

char	*ft_handle_null_precision(t_list2 **lst, char *s, t_data *dt, char *s2)
{
	char *tab;

	tab = NULL;
	if (s[0] == '0' && !s[1])
		tab = ft_handle_zero_null_precision(lst, dt);
	else
		tab = ft_handle_nb_null_precision(lst, s, dt, s2);
	return (tab);
}

void	ft_ignore_sign(t_list2 **list, char *str, t_data *data, char **tab)
{
	data->p = str;
	if (str[0] == '-' && (*list)->is_nb && data->inf != 1337)
		data->p = str + 1;
	*tab = NULL;
}
