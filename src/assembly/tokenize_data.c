/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:12:14 by anel-bou          #+#    #+#             */
/*   Updated: 2021/02/12 18:01:46 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int ft_binary_search(char *tab, char c)
{
	int start;
	int end;
	int mid;
	int res;

	start = 0;
	end = strlen(tab) - 1;
	mid = 0;
	while (start <= end)
	{
		mid = (start + end) / 2;
		res = c - tab[mid];
		if (!res)
			return (mid);
		else if (res < 0)
			end = mid - 1;
		else if (res > 0)
			start = mid + 1;
	}
	return (-1);
}

int ft_binary_search_2d(char *operation, t_op tab[16])
{
	int start;
	int end;
	int mid;
	int res;

	start = 0;
	end = 16;
	mid = 0;
	while (start <= end)
	{
		mid = (start + end) / 2;
		res = strcmp(operation, tab[mid].op_name);
		if (!res)
			return (mid);
		else if (res < 0)
			end = mid - 1;
		else if (res > 0)
			start = mid + 1;
	}

	return (-1);
}

void save_label_position(char *line, int current_bytes, t_env *env)
{
	int i;
	int j;

	if (!env->label)
	{
		env->label = (t_label *)ft_memalloc(sizeof(t_label));
		env->lbl = env->label;
	}
	else
	{
		env->lbl->next = (t_label *)ft_memalloc(sizeof(t_label));
		env->lbl = env->lbl->next;
	}
	env->lbl->label_name = "label";
	env->lbl->label_position = current_bytes;
}

int is_label_operation_in_same_line(char *line)
{
	int i;

	i = 0;
	while (line[i] && !IS_COMMENT_CHAR(line[i]) && line[i] != LABEL_CHAR)
		i++;
	line[i] == LABEL_CHAR ? i++ : 0;
	while (IS_SPACE(line[i]))
		i++;
	if (is_operation(&line[i]))
		return (i);
	return (0);
}

void save_line(t_env *env, char *line, int *current_bytes)
{
	int i;

	env->dt->next = (t_data *)ft_memalloc(sizeof(t_data));
	env->dt = env->dt->next;
	env->dt->line = line;

	env->dt->current_octets = *current_bytes;
	if (is_label(line))
	{
		save_label_position(line, *current_bytes, env);
		if ((i = is_label_operation_in_same_line(line)) > 0)
			*current_bytes += get_operation_size(&line[i]);
	}
	else if (is_operation(line))
		*current_bytes += get_operation_size(line);
}

int verify_label_chars(char *label)
{
	int i;

	i = -1;
	while (label[++i])
	{
		if (ft_binary_search(LABEL_CHARS, label[i]) < 0)
		{
			ft_putendl("syntax error: label name contains inappropriate charachter");
			// free
			exit(0);
		}
	}
	return (1);
}

void verify_operation_name(char *operation, char *op, int i, int *is_op)
{
	if (ft_binary_search_2d(operation, op_tab) >= 0)
	{
		printf("<%s> is an operation\n", operation);
		*is_op = 1;
		return;
	}
	else if (verify_label_chars(operation))
	{
		printf("<%s> is a label\n", operation);
		check_if_operation(ft_strtrim(op + i));
		
	}
	// printf("syntax error: operation <%s> not found\n", operation);
	// // free
	// exit(0);
}

int skip_white_spaces_and_arg_chars(char *str)
{
	int i;
	i = 0;
	while (str[i] && !IS_SPACE(str[i]) && str[i] != LABEL_CHAR && str[i] != DIRECT_CHAR)
		i++;
	return (i);
}

void check_if_operation(char *op)
{
	int i;
	char *sub_op;
	char *args;
	int is_op;

	is_op = 0;
	i = skip_white_spaces_and_arg_chars(op);
	sub_op = ft_strsub(op, 0, i);
	verify_operation_name(sub_op, op, i + 1, &is_op);
	// printf("op = %s\n", sub_op);
	if (is_op)
	{
		args = ft_strtrim(op + i);
		printf("args = %s\n", args);
	}
}

void tokenize_data(t_env *env)
{
	char *line;
	int char_pos;
	char *label;
	char *trimed_line;

	int i;

	get_next_line(env->src_file, &line);
	env->data->line = line;
	env->dt = env->data;
	while (get_next_line(env->src_file, &line))
	{
		trimed_line = ft_strtrim(line);
		if (!trimed_line[0] || trimed_line[0] == COMMENT_CHAR ||
			trimed_line[0] == ALT_COMMENT_CHAR)
			continue;
		if (line[0] == '.')
			ft_command_not_found(trimed_line);

		if ((char_pos = char_index(trimed_line, LABEL_CHAR)) >= 0 && !trimed_line[char_pos + 1])
		{
			label = ft_strsub(trimed_line, 0, char_pos);
			verify_label_chars(label);
			printf("<%s> is a label\n", label);

			// else if (trimed_line[char_pos - 1] == DIRECT_CHAR)
			// {
			// 	printf("op = %s\n", trimed_line + i);
			// 	exit(0);
			// }
			// check the op after the label
			continue;
		}
		// handle label: op ...
		// else if ((char_pos = char_index(trimed_line, LABEL_CHAR)) >= 0 && !trimed_line[char_pos + 1])
		else
		{
			check_if_operation(trimed_line);
		}

		// else if ()

		// else if (verify op name it could be without label)
		// save_line(env, line, &current_bytes);
		ft_strdel(&line);
		/***/
	}
	// printf("\n");
}
