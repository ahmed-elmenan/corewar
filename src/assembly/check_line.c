/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:36:33 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/13 19:15:49 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		check_line(char *trimed_line, char *regular_line)
{
	if (ft_empty_or_comment_line(trimed_line))
	{
		ft_strdel(&regular_line);
		ft_strdel(&trimed_line);
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

	env->label_already_checked = 1;
	label = ft_strsub(trimed_line, 0, char_pos);
	verify_label_chars(env, label);
	ft_strdel(&label);
}

int		ft_empty_or_comment_line(char *str)
{
	return (!str[0] || is_comment_char(str[0]));
}
