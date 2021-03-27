/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:12:14 by anel-bou          #+#    #+#             */
/*   Updated: 2021/03/27 18:25:49 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm_inc/corewar.h"

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
	char	*trimed_line;

	init_vars(env);
	while ((env->ret = get_next_line(env->src_file, &env->line)) > 0)
	{
		env->line_counter += 1;
		env->label_already_checked = 0;
		trimed_line = ft_strtrim(env->line);
		if (check_line(trimed_line))
		{
			ft_strdel(&env->line);
			continue;
		}
		check_error_command(env, trimed_line, env->line);
		if ((env->char_pos = char_index(trimed_line, LABEL_CHAR)) >= 0 &&
			!trimed_line[env->char_pos + 1])
			verify_single_label_in_line(env, trimed_line, env->char_pos);
		else
			check_if_operation_or_label(trimed_line, env);
		save_line(env, env->line, &env->current_bytes);
		ft_strdel(&trimed_line);
		is_newline_at_eof(env);
	}
	ft_strdel(&env->line);
	is_empty_body(env);
}
