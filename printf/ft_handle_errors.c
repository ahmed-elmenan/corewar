/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:45:32 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 03:12:18 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_detect_conv(char c)
{
	static char	*cnv = "cspdiouxXfFb";
	int			i;

	i = -1;
	while (cnv[++i])
	{
		if (cnv[i] == c)
			return (1);
	}
	return (0);
}

int		ft_detect_conv_pr(char c)
{
	static char *cnv = "diouxXfFb";
	int			i;

	i = -1;
	while (cnv[++i])
	{
		if (cnv[i] == c)
			return (1);
	}
	return (0);
}

int		detect_options(char c)
{
	static char *str = " .+-*#";
	int			j;

	j = -1;
	while (str[++j])
	{
		if (str[j] == c)
			return (1);
	}
	return (0);
}

int		ft_error_cnv(const char *format, int i, t_data *data)
{
	if (data->check && format[i] != '%')
		return (0);
	while (format[i] && !ft_isalpha(format[i]))
		i++;
	ft_detect_modifier(format, &i, data);
	data->cnv = ft_check_cnv(format, i, data);
	return (1);
}

int		ft_get_length(const char *format, int i)
{
	int			j;

	j = i;
	j++;
	while (format[j] && ft_isdigit(format[j]))
		j++;
	return (j);
}
