/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_detect_conditions2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 10:04:12 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 01:42:22 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_negative_sign_after_width(t_list2 **list, char *str, t_data *data)
{
	return (str[0] == '-' && data->y == data->len - 1 &&
			(*list)->precision && !((*list)->flag & F_MINUS) && (*list)->is_nb);
}

int		ft_ng_sign_condition(t_list2 **lst, char *str, t_data *dt, char *tab)
{
	return (str[0] == '-' && !(*lst)->precision && !((*lst)->flag & F_MINUS)
			&& (dt->len > ft_strlen(tab) || ((*lst)->width > ft_strlen(str))));
}

int		ft_minus_flag_with_negative_nb_condition(t_list2 **list, char *str)
{
	return ((*list)->is_nb && !(*list)->sign && ((*list)->clean ||
			(str[0] == '-' && (*list)->width > (*list)->precision)));
}

int		ft_hash_hexa_condition(t_list2 **list, t_data *data, char *tab)
{
	return ((*list)->is_nb == 15 && data->u && (*list)->flag & F_HASH
		&& !((*list)->flag & F_MINUS) && (!(((*list)->flag & F_ZERO))
			|| (*list)->precision >= 0) && (*list)->width > ft_strlen(tab));
}
