/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:45:47 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/25 16:39:46 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_handle_s_precision(t_list2 **list, char *str, t_data1 *data)
{
	char *tab;

	tab = NULL;
	if ((*list)->precision < ft_strlen(str) && !(*list)->is_nb)
	{
		if (!(*list)->precision)
			tab = ft_strdup("\0");
		else
			tab = ft_strsub(str, 0, (*list)->precision);
		data->len = (*list)->width - (*list)->precision;
	}
	else
	{
		tab = ft_strdup(str);
		data->len = (*list)->width - ft_strlen(str);
	}
	return (tab);
}

char	*ft_handle_zero_null_precision(t_list2 **list, t_data1 *data)
{
	char *tab;

	tab = NULL;
	if ((*list)->is_nb == 8 && (*list)->flag & F_HASH)
	{
		tab = ft_strdup("0");
		data->len = (*list)->width - 1;
	}
	else
	{
		tab = ft_strdup("\0");
		data->len = (*list)->width;
	}
	return (tab);
}

char	*ft_handle_nb_null_precision(t_list2 **l, char *s, t_data1 *dt,
			char *s2)
{
	char *tab;

	tab = NULL;
	tab = ft_strdup(s2);
	dt->len = (*l)->width - ft_strlen(s);
	return (tab);
}

char	*ft_handle_less_precision(t_list2 **list, t_data1 *data, char *p)
{
	char *tab;

	tab = NULL;
	tab = ft_strdup(p);
	data->len = (*list)->width - ft_strlen(p);
	return (tab);
}

char	*ft_handle_greather_precision(t_list2 **l, t_data1 *d, char *p,
			char *s2)
{
	char	*tab;
	char	*tmp;
	int		var;

	tab = NULL;
	tmp = NULL;
	var = ft_strlen(p);
	tab = ft_strnew((*l)->precision - var);
	tab = (char *)ft_memseti((void *)tab, '0', (*l)->precision - var, 0);
	tmp = tab;
	tab = ft_strjoin(tab, s2);
	ft_strdel(&tmp);
	d->len = (*l)->width - (*l)->precision;
	return (tab);
}
