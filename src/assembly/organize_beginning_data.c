/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_beginning_data.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:14:49 by anel-bou          #+#    #+#             */
/*   Updated: 2021/02/02 15:34:57 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

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

void check_string_length(int item_len, int max_len, char *item)
{
	if (item_len > max_len)
	{
		ft_putstr("The champion ");
		ft_putstr(item);
		ft_putstr(" exceed ");
		ft_putnbr(max_len);
		ft_putendl(" character");
		// free the pointer to struct
		exit(0);
	}
}

void missing_last_quotes_error(char *item, int quotes_index)
{
	if (quotes_index == -1)
	{
		ft_putstr("Couldn't find the ending quotes of the ");
		ft_putstr(item);
		ft_putendl(" string");
		// free the pointer to struct
		exit(0);
	}
}

void extract_multiline_string(t_env *env, char *joinned_str, int item_length, char (*item_container)[item_length], char *item)
{
	int quotes_index;
	char *newline_str;
	char *line;
	char *tmp;

	joinned_str = ft_strdup(joinned_str);
	while (get_next_line(env->src_file, &line) > 0)
	{
		tmp = joinned_str;
		newline_str = ft_strjoin("\n", line);
		joinned_str = ft_strjoin(joinned_str, newline_str);
		ft_strdel(&newline_str);
		ft_strdel(&tmp);
		if ((quotes_index = char_index(joinned_str, '"')) >= 0)
		{
			joinned_str[quotes_index] = '\0';
			ft_strdel(&line);
			break;
		}
		ft_strdel(&line);
	}
	missing_last_quotes_error(item, quotes_index);
	check_string_length(ft_strlen(joinned_str), item_length, item);
	ft_strcpy(*item_container, joinned_str);
	ft_memdel((void **)&joinned_str);
}

void extract_signleline_string(t_env *env, char *str, int i, int item_length, char (*item_container)[item_length], char *item)
{
	int j;

	check_string_length(ft_strlen(str) - 2, item_length, item);
	j = i;
	++i;
	while (str[++j] && str[j] != '"')
		;
	ft_strncpy(*item_container, &str[i], j - i);
}

void content_not_found_error(char *item)
{
		ft_putstr(item);
		ft_putendl(" content not found");
		// free 
		exit(0);
}

void set_champ_info(t_env *env, char *str, int item_length, char (*item_container)[item_length], char *item)
{
	int i;
	char *content_arr;
	char *tmp;
	int last_quotes_index;

	i = -1;
	while (str[++i] && str[i] != '"')
		;
	if (i == ft_strlen(str))
		content_not_found_error(item);
	if (ft_strequ(str + i, "\"\""))
	{
		(*item_container)[0] = '\0';
		return;
	}
	content_arr = str + i + 1;
	if ((last_quotes_index = char_index(content_arr, '"')) >= 0)
		content_arr[last_quotes_index + 1] = '\0';

	if (content_arr[ft_strlen(content_arr) - 1] != '"') // find another solution here
		extract_multiline_string(env, content_arr, item_length, item_container, item);
	else // single line in stirng name
		extract_signleline_string(env, str, i, item_length, item_container, item);
}

void ft_check_name_and_comment_existence(int checker, char *item)
{
	if (!checker)
	{
		ft_putstr(item);
		ft_putendl(" not found");
		// free the pointer to struct
		exit(0);
	}
}

void organize_beginning_data(t_env *env)
{
	char *line;
	env->hdr.magic = ((COREWAR_EXEC_MAGIC & 0xff) << 24) |
					 (COREWAR_EXEC_MAGIC << 8 & 0xff0000) | (COREWAR_EXEC_MAGIC >> 8 & 0xff00);
	while (get_next_line(env->src_file, &line) > 0)
	{
		if (str_begins_with(line, NAME_CMD_STRING))
		{
			set_champ_info(env, line, PROG_NAME_LENGTH, &env->hdr.prog_name, "name");
			env->check_name |= 1;
		}
		else if (str_begins_with(line, COMMENT_CMD_STRING))
		{
			set_champ_info(env, line, COMMENT_LENGTH, &env->hdr.comment, "comment");
			env->check_comment |= 1;
		}
		if (env->check_name && env->check_comment)
		{
			ft_strdel(&line);
			break;
		}
		ft_strdel(&line);
	}
	// printf("env->hdr.prog_name = %s\n", env->hdr.prog_name); // DEL
	// printf("env->hdr.comment = %s\n", env->hdr.comment); // DEL
	ft_check_name_and_comment_existence(env->check_name, "name");
	ft_check_name_and_comment_existence(env->check_comment, "comment");
}
/************************************print*******************************************/

void write_bgn_data(t_env *env)
{
}

void write_beginning_data(t_env *env)
{
	int null;

	null = 0;
	organize_beginning_data(env);
	write(env->dst_file, &(env->hdr.magic), 4);
	write(env->dst_file, &(env->hdr.prog_name), PROG_NAME_LENGTH);
	write(env->dst_file, &null, 4);
	write(env->dst_file, &null, 4);							   /*temporaire dial executable size*/
	write(env->dst_file, &(env->hdr.comment), COMMENT_LENGTH); /* flheader dayrin CMNT_LEN+1 tanchof 3lach daroha */
	write(env->dst_file, &null, 4);
}
