/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_detect_conditions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 09:22:35 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 01:39:55 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_plus_flag_condition(t_list2 **list, char *str, char *tab)
{
	return ((*list)->flag & F_PLUS && str[0] != '-' &&
		(*list)->is_nb == 10 && ((*list)->width <= ft_strlen(tab) ||
			(*list)->flag & F_MINUS || ((*list)->flag & F_ZERO &&
				(*list)->width > ft_strlen(tab) &&
					(*list)->precision == -1)));
}

int		ft_negative_nb_condition(t_list2 **lst, char *s, t_data *dt, char *tab)
{
	return (s[0] == '-' && (((*lst)->is_nb && dt->len <= 0) ||
		((*lst)->flag & F_ZERO && (*lst)->precision == -1 &&
			(*lst)->width > ft_strlen(tab) && (dt->len)--)));
}

int		ft_octal_sign_condition(t_list2 **list, char *str, t_data *data)
{
	return ((*list)->flag & F_HASH && (*list)->is_nb == 8 &&
			!((*list)->flag & F_MINUS) && ((*list)->precision > 0 ||
				data->u) && data->y == ((*list)->width - ft_strlen(str) - 1));
}

int		ft_zero_flag_condition(t_list2 **list)
{
	return ((*list)->flag & F_ZERO && !((*list)->flag & F_MINUS) &&
			((*list)->precision == -1 &&
				((*list)->is_nb || (*list)->cnv == 's')));
}

int		ft_plus_in_width_condition(t_list2 **lt, char *s, t_data *dt, char *r)
{
	return ((*lt)->flag & F_PLUS && dt->y == dt->len - 1 && s[0] != '-' &&
			(*lt)->is_nb == 10 && !((*lt)->flag & F_MINUS)
				&& (!((*lt)->flag & F_ZERO) || (*lt)->width > ft_strlen(r)));
}
