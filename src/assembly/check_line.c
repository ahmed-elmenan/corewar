/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:36:33 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/24 19:24:33 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		ft_empty_or_comment_line(char c)
{
	return (!c || is_comment_char(c));
}

int		ft_str_is_spaces(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_empty_or_comment_line(str[i]) && !is_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		check_line(char *regular_line)
{
	if (ft_empty_or_comment_line(regular_line[0]))
	{
		ft_strdel(&regular_line);
		return (1);
	}
	return (0);
}

int		check_command(char *trimed_line)
{
	return (trimed_line[0] == '.' &&
			!str_begins_with(trimed_line, NAME_CMD_STRING) &&
			!str_begins_with(trimed_line, COMMENT_CMD_STRING));
}

void	check_error_command(t_env *env, char *trimed_line, char *line)
{
	if (trimed_line[0] == '.')
		ft_command_not_found(trimed_line, line, env);
}

void	verify_single_label_in_line(t_env *env, char *trimed_line, int char_pos)
{
	char *label;

	env->check_eof = TRUE;
	env->label_already_checked = 1;
	label = ft_strsub(trimed_line, 0, char_pos);
	verify_label_chars(env, label);
	ft_strdel(&label);
}
