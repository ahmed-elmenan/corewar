/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:12:14 by anel-bou          #+#    #+#             */
/*   Updated: 2021/02/16 19:40:00 by ahel-men         ###   ########.fr       */
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

int ft_binary_search_2d(t_env *env, char *operation, t_op tab[16])
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
		{
			env->found_op = &tab[mid];
			return (mid);
		}
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

int verify_label_chars(t_env *env, char *label)
{
	int i;

	i = -1;
	while (label[++i])
	{
		if (ft_binary_search(LABEL_CHARS, label[i]) < 0)
		{
			printf("Syntax Error[%d]: label <%s> contains inappropriate charachter\n", env->line_counter, label);
			// free
			exit(0);
		}
	}
	return (1);
}

int arr_len_2d(char **str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		// printf("str[%d] = <%s>\n", i, ft_strtrim(str[i])); // trim
		;
	}
	return (i);
}

void ft_check_args_len(t_env *env, int len)
{
	if (env->found_op->arg_len < len)
	{
		printf("Error[%d]: too many arguments to operation <%s>\n", env->line_counter, env->found_op->op_name);
		// free da3wa
		exit(0);
	}
	else if (!len)
	{
		printf("Error[%d]: the operation <%s> has no arguments\n", env->line_counter, env->found_op->op_name);
		// free da3wa
		exit(0);
	}
	else if (env->found_op->arg_len > len)
	{
		printf("Error[%d]: too few arguments to operation <%s>\n", env->line_counter, env->found_op->op_name);
		// free da3wa
		exit(0);
	}
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

void error_passing_indirect(t_env *env, char *str)
{
	if (str[0] == LABEL_CHAR || ft_is_string_number(str))
	{
		// free
		// free trimed_str
		printf("Error[%d]: Passing indirect argument to <%s> operation\n", env->line_counter, env->found_op->op_name);
		exit(0);
	}
}

void error_passing_direct(t_env *env, char c)
{
	if (c == DIRECT_CHAR)
	{
		// free
		// free trimed_str
		printf("Error[%d]: Passing direct argument to <%s> operation\n", env->line_counter, env->found_op->op_name);
		exit(0);
	}
}

void error_passing_registry(t_env *env, char c)
{
	if (c == 'r')
	{
		// free
		// free trimed_str
		printf("Error[%d]: Passing registry argument to <%s> operation\n", env->line_counter, env->found_op->op_name);
		exit(0);
	}
}

void error_big_reg_value(t_env *env)
{
	printf("Error[%d]: Registery value is bigger than 16\n", env->line_counter);
	// free
	exit(0);
}

void error_reg_value_not_digit(t_env *env)
{
	printf("Error[%d]: Registery value is not a digit\n", env->line_counter);
	// free
	exit(0);
}

void error_reg_value_is_negative(t_env *env)
{
	printf("Error[%d]: Registery value is negative\n", env->line_counter);
	// free
	exit(0);
}

void error_value_contains_positive_sign(t_env *env, char *arg_type)
{
	printf("Error[%d]: %s value contains positive sign\n", env->line_counter, arg_type);
	// free
	exit(0);
}

void error_overflow_or_underflow_int(t_env *env, char *arg_type)
{
	printf("Error[%d]: %s value is bigger or less than int limits\n", env->line_counter, arg_type);
	// free
	exit(0);
}

void handle_int_errors(t_env *env, char *arg, char *arg_type)
{
	if (ft_is_string_number(arg + 1))
		if (ft_atoll(arg + 1) == TRUE)
			error_overflow_or_underflow_int(env, arg_type);
}

void	handle_number_error(t_env *env, char *arg, char *arg_type)
{
	if (arg[1] == '+')
			error_value_contains_positive_sign(env, arg_type);
		if (ft_is_string_number(arg + 1))
			handle_int_errors(env, arg, arg_type);
}

void check_argument_value(t_env *env, char *trimed_str)
{
	int i;
	int reg_value;

	i = 0;
	printf("tri = %s\n", trimed_str);
	if (trimed_str[0] == 'r')
	{
		reg_value = ft_atoi(trimed_str + 1);
		if (reg_value > REG_NUMBER)
			error_big_reg_value(env);
		if (reg_value < 0)
			error_reg_value_is_negative(env);
		if (trimed_str[1] == '+')
			error_value_contains_positive_sign(env, "Registery");
		while (trimed_str[++i])
		{
			if (!ft_isdigit(trimed_str[i]))
				error_reg_value_not_digit(env);
		}
	}
	else if (trimed_str[0] == DIRECT_CHAR)
		handle_number_error(env, trimed_str, "Direct");
	else if (trimed_str[0] == LABEL_CHAR || ft_is_string_number(trimed_str))
		handle_number_error(env, trimed_str, "Indirect");
}

void check_args_type(t_env *env, char **args)
{
	int i;
	int res;
	char *trimed_str;

	i = -1;
	while (args[++i])
	{
		res = env->found_op->arg[i];
		trimed_str = ft_strtrim(args[i]);
		// printf("res = %d\n", res);
		// printf("args[i][0] = %c\n", trimed_str[0]);
		if (res == 1)
		{
			error_passing_direct(env, trimed_str[0]);
			error_passing_indirect(env, trimed_str);
		}
		else if (res == 2)
		{
			error_passing_registry(env, trimed_str[0]);
			error_passing_indirect(env, trimed_str);
		}
		else if (res == 3)
			error_passing_indirect(env, trimed_str);
		else if (res == 6)
			error_passing_registry(env, trimed_str[0]);
		if (trimed_str[0] != LABEL_CHAR && trimed_str[0] != DIRECT_CHAR && trimed_str[0] != 'r' && !ft_is_string_number(trimed_str))
		{
			printf("Error[%d]: Passing unknown argument to operation <%s>\n", env->line_counter, env->found_op->op_name);
			ft_strdel(&trimed_str);
			exit(0);
		}
		// starting the parse of each argument
		
		check_argument_value(env, trimed_str);
		ft_strdel(&trimed_str);
		// exit(0);
	}
}

void verify_item_name(char *str, char *op, int i, int *is_op, t_env *env)
{
	char *tmp;
	char *args_tmp;
	char **args;
	int args_len;

	tmp = op + i - 1;
	printf("s = <%s>\n", str);
	printf("|tmp| = <%s>\n", tmp);

	if (ft_binary_search_2d(env, str, op_tab) >= 0 && tmp[0] != LABEL_CHAR)
	{
		*is_op = 1;
		args_tmp = op + i - 1;
		if (args_tmp[ft_strlen(args_tmp) - 1] == SEPARATOR_CHAR)
		{
			printf("Syntax Error[%d]: Found separator at the end of the operation <%s>'s arguments\n", env->line_counter, str);
			//free
			exit(0);
		}
		args = ft_strsplit(args_tmp, SEPARATOR_CHAR);
		args_len = arr_len_2d(args); // let the trim and delete the print
		printf("found_op = %s\n", env->found_op->op_name);
		// printf("len = %d\n", args_len);
		ft_check_args_len(env, args_len);
		check_args_type(env, args);
		// ft_strdel(&tmp);
		return;
	}
	else if (!env->label_already_checked && verify_label_chars(env, str))
	{
		if (tmp[0] != LABEL_CHAR)
		{
			printf("Error[%d]: Invalid instruction at <%s>\n", env->line_counter, str);
			// free
			exit(0);
		}
		env->label_already_checked = 1;
		printf("<%s> is a label\n", str);
		ft_strdel(&str);
		check_if_operation(ft_strtrim(op + i), env);
	}
	else
	{

		printf("Syntax Error[%d]: Operation <%s> not found\n", env->line_counter, str);
		// free
		// ft_strdel(&tmp);
		exit(0);
	}
}

int skip_white_spaces_and_arg_chars(char *str)
{
	int i;
	i = 0;
	while (str[i] && !IS_SPACE(str[i]) &&
		   str[i] != LABEL_CHAR && str[i] != DIRECT_CHAR)
		i++;
	return (i);
}

void check_if_operation(char *op, t_env *env)
{
	int i;
	char *sub_op;
	char *args;
	int is_op;

	is_op = 0;
	i = skip_white_spaces_and_arg_chars(op);
	sub_op = ft_strsub(op, 0, i);
	if (IS_COMMENT_CHAR(sub_op[0]))
	{
		ft_strdel(&sub_op);
		return; // to free
	}
	args = ft_strtrim(op + i); // free this
	verify_item_name(sub_op, op, i + 1, &is_op, env);
}

void tokenize_data(t_env *env)
{
	char *line;
	char *label;
	char *trimed_line;
	int char_pos;
	int i;

	env->data->line = line;
	env->dt = env->data;
	while (get_next_line(env->src_file, &line))
	{
		env->line_counter += 1;
		env->label_already_checked = 0;
		trimed_line = ft_strtrim(line);
		if (ft_empty_or_comment_line(trimed_line))
		{
			ft_strdel(&line);
			ft_strdel(&trimed_line);
			continue;
		}
		if (trimed_line[0] == '.')
			ft_command_not_found(trimed_line, env);
		if ((char_pos = char_index(trimed_line, LABEL_CHAR)) >= 0 && !trimed_line[char_pos + 1])
		{
			env->label_already_checked = 1;
			label = ft_strsub(trimed_line, 0, char_pos);
			verify_label_chars(env, label);
			// printf("<%s> is a label\n", label);
		}
		else
			check_if_operation(trimed_line, env);

		// save_line(env, line, &current_bytes);
		ft_strdel(&line);
		ft_strdel(&trimed_line);
	}
}
