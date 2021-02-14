/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_beginning_data.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:14:49 by anel-bou          #+#    #+#             */
/*   Updated: 2021/02/10 18:50:52 by ahel-men         ###   ########.fr       */
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

void check_string_length(t_env *env, int item_len, int max_len, char *item)
{
	if (item_len > max_len)
	{
		printf("Error[%d]: The champion %s exceed %d character\n", env->line_counter, item, max_len);
		// free the pointer to struct
		exit(0);
	}
}

void check_missing_last_quotes_error(t_env *env, char *item, int quotes_index)
{
	if (quotes_index == -1)
	{
		printf("syntax error[%d]: Couldn't find the ending quotes of the %s string\n", env->line_counter, item);
		// free the pointer to struct
		exit(0);
	}
}

void check_characters_after_last_quotes(t_env *env, char *str, char *item, int line_counter)
{
	int i;
	int comment_index;
	int alt_comment_index;
	int res;
	char *tmp;
	char *tmp2;

	i = -1;
	printf("str = %s\n", str);
	tmp = ft_strtrim(str);
	comment_index = char_index(tmp, COMMENT_CHAR) > -1 ? char_index(tmp, COMMENT_CHAR) : INT_MAX;
	alt_comment_index = char_index(tmp, ALT_COMMENT_CHAR) > -1 ? char_index(tmp, ALT_COMMENT_CHAR) : INT_MAX;
	res = alt_comment_index >= comment_index ? comment_index : alt_comment_index;
	while (tmp[++i] && !IS_COMMENT_CHAR(tmp[i]))
	{
		if (IS_SPACE(tmp[i]))
			continue;
		else
		{
			tmp2 = ft_strsub(tmp, i, res - 1);
			str = ft_strtrim(tmp2);
			printf("Syntax Error[%d]: String <%s> has been found after %s ending quotes\n", line_counter, str, item);
			//free line
			ft_strdel(&tmp);
			ft_strdel(&tmp2);
			ft_strdel(&str);
			exit(0);
		}
	}
}

void extract_multiline_string(t_env *env, char *joinned_str, int item_length, char (*item_container)[item_length], char *item)
{
	int quotes_index;
	int line_counter2;
	char *newline_str;
	char *line;
	char *tmp;

	joinned_str = ft_strdup(joinned_str);
	line_counter2 = env->line_counter;
	while (get_next_line(env->src_file, &line) > 0)
	{
		line_counter2++;
		tmp = joinned_str;
		newline_str = ft_strjoin("\n", line);
		joinned_str = ft_strjoin(joinned_str, newline_str);
		ft_strdel(&newline_str);
		ft_strdel(&tmp);
		if ((quotes_index = char_index(joinned_str, '"')) >= 0)
		{
			check_characters_after_last_quotes(env, joinned_str + quotes_index + 1, item, line_counter2);
			joinned_str[quotes_index] = '\0';
			ft_strdel(&line);
			break;
		}
		ft_strdel(&line);
	}
	check_missing_last_quotes_error(env, item, quotes_index);
	env->line_counter = line_counter2;
	printf("%d\n", env->line_counter);
	check_string_length(env, ft_strlen(joinned_str), item_length, item);
	ft_strcpy(*item_container, joinned_str);
	ft_memdel((void **)&joinned_str);
}

void extract_signleline_string(t_env *env, char *str, int i, int item_length, char (*item_container)[item_length], char *item)
{
	int j;

	check_string_length(env, ft_strlen(str) - 2, item_length, item);
	j = i;
	++i;
	while (str[++j] && str[j] != '"')
		;
	ft_strncpy(*item_container, &str[i], j - i);
}

void content_not_found_error(char *item, t_env *env)
{
	printf("error [%d]: <%s> content not found\n", env->line_counter, item);
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
		content_not_found_error(item, env);
	if (ft_strequ(str + i, "\"\""))
	{
		(*item_container)[0] = '\0';
		return;
	}
	content_arr = str + i + 1;
	if ((last_quotes_index = char_index(content_arr, '"')) >= 0)
	{
		check_characters_after_last_quotes(env, content_arr + last_quotes_index + 1, item, env->line_counter);
		content_arr[last_quotes_index + 1] = '\0';
	}
	if (content_arr[ft_strlen(content_arr) - 1] != '"') // find another solution here
		extract_multiline_string(env, content_arr, item_length, item_container, item);
	else // single line in stirng name
		extract_signleline_string(env, str, i, item_length, item_container, item);
}

void ft_check_name_and_comment_existence(int checker, char *item)
{
	if (!checker)
	{
		printf("Error: Champion <%s> not found\n", item);
		// free the pointer to struct
		exit(0);
	}
}

int ft_empty_or_comment_line(char *str)
{
	return (!str[0] || IS_COMMENT_CHAR(str[0]));
}

int check_name_comment_flag(t_env *env)
{
	return (env->check_name && env->check_comment);
}

void ft_error_founded_before_item(char *str, t_env *env, char *item)
{

	printf("Error[%d]: <%s> has been founded before %s\n", env->line_counter, str, item);
	// free the pointer to struct
	exit(0);
}

void ft_command_not_found(char *trimed_line, t_env *env)
{
	printf("Syntax Error[%d]: Command <%s> not found\n", env->line_counter, trimed_line);
	// free line,...
	exit(0);
}
void organize_beginning_data(t_env *env)
{
	char *regular_line;
	char *trimed_line;
	int begin_name;
	int begin_comment;

	env->hdr.magic = ((COREWAR_EXEC_MAGIC & 0xff) << 24) |
					 (COREWAR_EXEC_MAGIC << 8 & 0xff0000) | (COREWAR_EXEC_MAGIC >> 8 & 0xff00);
	while (get_next_line(env->src_file, &regular_line) > 0)
	{
		env->line_counter += 1;
		trimed_line = ft_strtrim(regular_line);
		if (ft_empty_or_comment_line(trimed_line))
		{
			ft_strdel(&regular_line);
			ft_strdel(&trimed_line);
			continue;
		}
		if (trimed_line[0] == '.' && !str_begins_with(trimed_line, NAME_CMD_STRING) &&
			!str_begins_with(trimed_line, COMMENT_CMD_STRING))
			ft_command_not_found(trimed_line, env);
		// check ordinary lines
		if (str_begins_with(trimed_line, NAME_CMD_STRING))
		{
			set_champ_info(env, trimed_line, PROG_NAME_LENGTH, &env->hdr.prog_name, "name");
			env->check_name |= 1;
		}
		else if (str_begins_with(trimed_line, COMMENT_CMD_STRING))
		{
			set_champ_info(env, trimed_line, COMMENT_LENGTH, &env->hdr.comment, "comment");
			env->check_comment |= 1;
		}
		else
		{
			if (!env->check_name && env->check_comment)
				ft_error_founded_before_item(trimed_line, env, "name");
			else if (!env->check_comment && env->check_name)
				ft_error_founded_before_item(trimed_line, env, "comment");
			else if (!env->check_comment && !env->check_name)
				ft_error_founded_before_item(trimed_line, env, "name and comment");
		}
		if (check_name_comment_flag(env))
		{
			ft_strdel(&regular_line);
			ft_strdel(&regular_line);
			ft_strdel(&trimed_line);
			break;
		}
		ft_strdel(&regular_line);
		ft_strdel(&trimed_line);
	}
	// printf("env->hdr.prog_name = %s\n", env->hdr.prog_name); // DEL
	printf("env->hdr.comment = %s\n", env->hdr.comment); // DEL
	ft_check_name_and_comment_existence(env->check_name, "name");
	ft_check_name_and_comment_existence(env->check_comment, "comment");
}
/************************************print*******************************************/

void write_beginning_data(t_env *env)
{
	int null;

	null = 0;
	write(env->dst_file, &(env->hdr.magic), 4);
	write(env->dst_file, &(env->hdr.prog_name), PROG_NAME_LENGTH);
	write(env->dst_file, &null, 4);
	write(env->dst_file, &null, 4);							   /*temporaire dial executable size*/
	write(env->dst_file, &(env->hdr.comment), COMMENT_LENGTH); /* flheader dayrin CMNT_LEN+1 tanchof 3lach daroha */
	write(env->dst_file, &null, 4);
}
