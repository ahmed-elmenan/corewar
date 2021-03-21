/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 03:13:25 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/21 14:56:29 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int arr_len_2d(t_env *env, char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_is_string_number(char *str)
{
	int i;

	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int char_index(char *str, char c)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

void free_pointers(char *trimed_line, char *line)
{
	// ft_strdel(&line);
	ft_strdel(&trimed_line);
}

int skip_white_spaces_and_arg_chars(char *str)
{
	int i;

	i = 0;
	while (str[i] && !is_space(str[i]) &&
		   str[i] != LABEL_CHAR && str[i] != DIRECT_CHAR)
		i++;
	return (i);
}
