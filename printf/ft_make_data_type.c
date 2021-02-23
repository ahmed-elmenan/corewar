/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_data_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 10:38:04 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 16:52:30 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_precision_condition(t_list2 **list, t_data *data)
{
	return ((*list)->precision >= 0 && data->cnv != 'f'
		&& data->cnv != 'F' && data->cnv != 'p');
}

char	*ft_make_precision(t_list2 **list, char *str, t_data *data)
{
	char *tab;
	char *str2;

	ft_ignore_sign(list, str, data, &tab);
	str2 = ft_strdup(data->p);
	if (ft_precision_condition(list, data) && ft_check_pr(list, data))
	{
		if ((*list)->precision >= 0 && (*list)->cnv == 's')
			tab = ft_handle_s_precision(list, str, data);
		else if ((*list)->precision >= 0 && (*list)->is_nb)
		{
			if (!(*list)->precision && (*list)->is_nb)
				tab = ft_handle_null_precision(list, str, data, str2);
			else if (ft_strlen(str) > (*list)->precision)
				tab = ft_handle_less_precision(list, data, data->p);
			else if ((*list)->precision > 0 && (*list)->is_nb)
				tab = ft_handle_greather_precision(list, data, data->p, str2);
		}
	}
	else
		tab = ft_handle_no_precision(list, str, data, data->p);
	if (ft_hash_hexa_condition(list, data, tab))
		tab = ft_add_hexa_prefix(list, data, tab);
	ft_strdel(&str2);
	return (tab);
}

int		ft_make_str(t_list2 **list, char *str, t_data *data)
{
	int		i;
	char	*tab;
	int		x;

	i = 0;
	tab = NULL;
	x = ft_strlen(str);
	ft_detect_precision(list, &tab, str, data);
	ft_detect_space_d(list, str, data);
	if ((*list)->flag & F_HASH && data->u)
		ft_detect_hash(list, str, data, x);
	if ((*list)->is_nb && (str[0] == '-' || (*list)->flag & F_PLUS) &&
			data->space_d != 1337 && data->inf != 1337)
		ft_detect_plus(list, tab, str, data);
	if ((*list)->flag & F_MINUS)
		ft_detect_minus(list, tab, str, data);
	if (data->len > 0)
		ft_detect_width(list, tab, str, data);
	if ((*list)->is_nb)
		ft_detect_negative_nb(list, tab, str, data);
	if (!((*list)->flag & F_MINUS))
		ft_print_string(list, tab, data);
	if ((*list)->cnv != 'c')
		ft_strdel(&tab);
	return (data->ret);
}

int		ft_make_number(t_list2 **list, t_data *data)
{
	char	*str;
	int		ret;

	str = NULL;
	if ((*list)->cnv == 'o' && ((*list)->is_nb = 8))
		str = ft_convert(data->u, 3, 7);
	else if ((*list)->cnv == 'b')
	{
		str = ft_convert(data->u, 1, 1);
		(*list)->is_nb = 2;
	}
	else if ((*list)->cnv == 'u')
	{
		str = ft_itoa_u(data->u);
		(*list)->is_nb = 11;
	}
	else if ((*list)->cnv == 'd' || (*list)->cnv == 'i')
	{
		str = ft_itoa2(data->d);
		(*list)->is_nb = 10;
	}
	ret = ft_make_str(list, str, data);
	ft_strdel(&str);
	return (ret);
}

int		ft_make_hexa(t_list2 **list, t_data *data)
{
	char	*sv;
	char	*str;
	int		ret;

	sv = NULL;
	if ((*list)->cnv == 'x' || (*list)->cnv == 'X')
		(*list)->is_nb = 15;
	str = ft_convert(data->u, 4, 15);
	if ((*list)->cnv == 'X')
		ft_capitalize(str);
	if ((*list)->cnv == 'p')
	{
		sv = str;
		if (!(*list)->precision && *str == '0' && !*(str + 1))
			str = ft_strjoin("0x", "");
		else
			str = ft_strjoin("0x", str);
		ft_strdel(&sv);
	}
	ret = ft_make_str(list, str, data);
	ft_strdel(&str);
	return (ret);
}
