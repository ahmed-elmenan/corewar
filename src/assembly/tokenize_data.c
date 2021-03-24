/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:12:14 by anel-bou          #+#    #+#             */
/*   Updated: 2021/03/24 19:52:02 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	save_line(t_env *env, char *line, int *current_bytes)
{
	int i;

	if (!env->flag)
	{
		env->data->line = line;
		env->flag = TRUE;
	}
	else
	{
		env->dt->next = (t_data *)ft_memalloc(sizeof(t_data));
		env->dt = env->dt->next;
		env->dt->line = line;
		env->dt->current_octets = *current_bytes;
	}
	if (is_label(line))
	{
		save_label_position(line, *current_bytes, env);
		if ((i = is_label_operation_in_same_line(line)) > 0)
			*current_bytes += get_operation_size(&line[i]);
	}
	else if (is_operation(line))
		*current_bytes += get_operation_size(line);
}

void	verify_item_name(char *op, int i, int *is_op, t_env *env)
{
	char	*tmp;

	tmp = op + i - 1;
	if (ft_binary_search_2d(env, env->sub_op, g_op_tab) >= 0 &&
		tmp[0] != LABEL_CHAR)
	{
		operation_parsing(env, is_op, op, i);
		return ;
	}
	else if (!env->label_already_checked &&
			verify_label_chars(env, env->sub_op))
	{
		label_parsing(env, env->sub_op, tmp);
		env->save_op = ft_strtrim(op + i);
		check_if_operation_or_label(env->save_op, env);
	}
	else
	{
		ft_printf("Syntax Error[%d]: Operation <%s> not found\n",
				env->line_counter, env->sub_op);
		exit(0);
	}
}

void	check_if_operation_or_label(char *op, t_env *env)
{
	int		i;
	int		is_op;

	is_op = 0;
	env->check_eof = TRUE;
	i = skip_white_spaces_and_arg_chars(op);
	env->sub_op = ft_strsub(op, 0, i);
	if (is_comment_char(env->sub_op[0]))
	{
		ft_strdel(&env->sub_op);
		return ;
	}
	verify_item_name(op, i + 1, &is_op, env);
}

void	tokenize_data(t_env *env)
{
	char	*line;
	char	*trimed_line;
	int		char_pos;
	int		current_bytes;
	int		ret;

	env->check_eof = FALSE;
	env->flag = FALSE;
	current_bytes = 0;
	env->dt = env->data;
	while ((ret = get_next_line(env->src_file, &line)) > 0)
	{
		env->line_counter += 1;
		env->label_already_checked = 0;
		trimed_line = ft_strtrim(line);
		if (check_line(trimed_line))
		{
			ft_strdel(&line);
			continue;
		}
		check_error_command(env, trimed_line, line);
		if ((char_pos = char_index(trimed_line, LABEL_CHAR)) >= 0 &&
			!trimed_line[char_pos + 1])
			verify_single_label_in_line(env, trimed_line, char_pos);
		else
			check_if_operation_or_label(trimed_line, env);
		save_line(env, line, &current_bytes);
		ft_strdel(&trimed_line);
		if (ret == 2)
		{
			ft_printf("file doesn't end with a new line\n");
			exit(0);
		}
	}
	ft_strdel(&line);
	if (!env->check_eof)
	{
		ft_printf("Syntax Error:File doesn't contain any label or operation\n");
		exit(0);
	}
}
