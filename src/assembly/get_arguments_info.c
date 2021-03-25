/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 11:24:14 by anel-bou          #+#    #+#             */
/*   Updated: 2021/03/23 14:49:42 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		get_next_argum_index(char *line, int i)
{
	while (line[i] && line[i] != SEPARATOR_CHAR && !is_comment_char(line[i]))
		i++;
	line[i] == SEPARATOR_CHAR ? i++ : 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (is_arg_first_char(line, i))
		return (i);
	return (-1);
}

int		get_all_arguments_size(char *line, int opr)
{
	int i;
	int argums_size;

	argums_size = 0;
	i = -1;
	while (line[++i] && (!is_space(line[i])) && line[i + 1] != '%')
		;
	while (is_space(line[i]))
		i++;
	while (i >= 0 && line[i] && !is_comment_char(line[i]))
	{
		argums_size += get_this_arg_size(line, i, opr);
		i = get_next_argum_index(line, i);
	}
	return (argums_size);
}

int		get_this_arg_size(char *line, int i, int op)
{
	if (line[i] == 'r')
		return (1);
	else if (line[i] == '%')
		return (get_t_dir_size(op));
	else
		return (2);
}

int		get_current_argument_code(char *line)
{
	if (line[0] == 'r')
		return (0b01);
	else if (line[0] == '%')
		return (0b10);
	else
		return (0b11);
}

void	verify_direct_value(t_env *env, char *trimed_str)
{
	if (ft_is_string_number(trimed_str + 1) || trimed_str[1] == '-'
			|| trimed_str[1] == '+')
		handle_number_error(env, trimed_str, "Direct");
	else if (trimed_str[1] == LABEL_CHAR && ft_isalnum(trimed_str[2]))
	{
		verify_label_chars(env, trimed_str + 2);
	}
	else
	{
		ft_printf("Lexical Error[%d]: ", env->line_counter);
		ft_printf("Argument contains inappropriate characters <%s>\n",
			trimed_str);
		exit(0);
	}
}
