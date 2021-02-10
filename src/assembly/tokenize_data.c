/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:12:14 by anel-bou          #+#    #+#             */
/*   Updated: 2021/02/10 19:39:56 by ahel-men         ###   ########.fr       */
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

int	ft_binary_search_2d(char **tab, char *vertex_name, int len)
{
	int	start;
	int	end;
	int	mid;
	int	res;

	start = 0;
	end = len - 1;
	mid = 0;
	while (start <= end)
	{
		mid = (start + end) / 2;
		res = strcmp(vertex_name, tab[mid]);
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

void verify_label_chars(char *label)
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
}

char  *verify_operation_name(char *operation)
{
	int i;
	char *str;

	i = -1;
	while (op_tab[++i].op_name)
	{
		if ((str = ft_strstr(operation, op_tab[i].op_name)))
		{
			return(str);
		}	
	}
	ft_putendl("syntax error: label name contains inappropriate charachter");
	// free
	exit(0);
	return (NULL);
}

void tokenize_data(t_env *env)
{
	char *line;
	int current_bytes;
	int char_pos;
	int char_label;
	char *str;
	char *label;
	char *op;
	char *trimed_line;

	int i;

	current_bytes = 0;
	get_next_line(env->src_file, &line);
	env->data->line = line;
	env->dt = env->data;
	while (get_next_line(env->src_file, &line))
	{
		trimed_line = ft_strtrim(line);
		if (line[0] == '.')
			ft_command_not_found(trimed_line);
		
		if ((char_pos = char_index(trimed_line, DIRECT_CHAR)) >= 0)
		{
			str = ft_strsub(trimed_line, 0, char_pos);
			if ((char_label = char_index(str, LABEL_CHAR)) >= 0)
			{
				label = ft_strsub(trimed_line, 0, char_label);
				verify_label_chars(label);
				
			}
			char_label = char_label > -1? char_label : 0;
			op = ft_strtrim(str + char_label);
			op = verify_operation_name(op);
			printf("o00p = %s\n", op);
		}
		else if ((char_pos = char_index(trimed_line, LABEL_CHAR)) >= 0)
		{
			label = ft_strsub(trimed_line, 0, char_pos);
			verify_label_chars(label);
				printf("label = %s\n", label);
			// check the op after the label
		}
		// else if (verify op name it could be without label)
		// save_line(env, line, &current_bytes);
		ft_strdel(&line);
		/***/
	}
	// printf("\n");
}
