/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:12:14 by anel-bou          #+#    #+#             */
/*   Updated: 2021/02/02 17:26:11 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int	ft_binary_search(char *tab, char c)
{
	int	start;
	int	end;
	int	mid;
	int	res;

	start = 0;
	end = strlen(tab) - 1;
	mid = 0;
	while (start <= end)
	{
		mid = (start + end) / 2;
		res = c  -  tab[mid];
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

	j = -1;
	while (IS_SPACE(line[++j]))
		;
	--j;
	i = j - 1;
	while (line[++i] && line[i] != LABEL_CHAR)
		;
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
	env->lbl->label_name = ft_strsub(line, j, i);
	env->lbl->label_position = current_bytes;
}

int is_label_operation_in_same_line(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != LABEL_CHAR)
		i++;
	while (IS_SPACE(line[++i]))
		;
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
			*current_bytes += get_operation_size(env, &line[i]);
	}
	else if (is_operation(line))
	{
		*current_bytes += get_operation_size(env, line);
	}
}

void	verify_label_chars(char *label)
{
	int i;
    
    i = -1;
	printf("label = %s\n", label);
	while(label[++i])
    {
        if (ft_binary_search(LABEL_CHARS, label[i]) < 0)
        {
            ft_putendl("syntax error: label name contains inappropriate charachter");
			// free
            exit(0);
        }
    }
}

void tokenize_data(t_env *env)
{
	char *line;
	int current_bytes;
	int label_char_index;
	char *label;

	current_bytes = 0;
	// get_next_line(env->src_file, &line);
	
	env->data->line = line;
	env->dt = env->data;
	while (get_next_line(env->src_file, &line))
	{
		if (line[0] == '.')
		{
			ft_putendl("syntax error: command not found");
			// free pointers
			ft_strdel(&line);
			exit(0);
		}
		// if op
		if ((label_char_index = char_index(line, LABEL_CHAR)) >= 0)
		{
			label = ft_strsub(line, 0, label_char_index);
			verify_label_chars(label);
		}
		
		// save_line(env, line, &current_bytes);
		/***/
	}
}
