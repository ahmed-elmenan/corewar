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

int calculate_comment_index(char *str)
{
	int comment_index;
	int alt_comment_index;

	comment_index = char_index(str, COMMENT_CHAR) > -1 ? char_index(str, COMMENT_CHAR) : INT_MAX;
	alt_comment_index = char_index(str, ALT_COMMENT_CHAR) > -1 ? char_index(str, ALT_COMMENT_CHAR) : INT_MAX;
	return (alt_comment_index >= comment_index ? comment_index : alt_comment_index);
}

void check_characters_after_last_quotes(t_env *env, char *str, char *item, int line_counter)
{
	int i;
	int res;
	char *tmp;
	char *tmp2;

	i = -1;
	tmp = ft_strtrim(str);
	res = calculate_comment_index(tmp);
	while (tmp[++i] && !IS_COMMENT_CHAR(tmp[i]))
	{
		if (IS_SPACE(tmp[i]))
			continue;
		else
		{
			tmp2 = ft_strsub(tmp, i, res - 1);
			str = ft_strtrim(tmp2);
			printf("Syntax Error[%d]: String <%s> has been found after %s ending quotes\n", line_counter, str, item);
			ft_strdel(&tmp);
			ft_strdel(&tmp2);
			ft_strdel(&str);
			exit(0);
		}
	}
	ft_strdel(&tmp);
}

void store_string_item(t_env *env, char *item, int item_length, char (*item_container)[item_length])
{
	check_missing_last_quotes_error(env, item, env->quotes_index);
	env->line_counter = env->line_counter_tmp;
	check_string_length(env, ft_strlen(env->joinned_str), item_length, item);
	ft_strcpy(*item_container, env->joinned_str);
	ft_memdel((void **)&env->joinned_str);
}

void extract_multiline_string(t_env *env, int item_length,
							  char (*item_container)[item_length], char *item)
{
	char *newline_str;
	char *line;
	char *tmp;

	env->joinned_str = ft_strdup(env->joinned_str);
	env->line_counter_tmp = env->line_counter;
	while (get_next_line(env->src_file, &line) > 0)
	{
		env->line_counter_tmp++;
		tmp = env->joinned_str;
		newline_str = ft_strjoin("\n", line);
		env->joinned_str = ft_strjoin(env->joinned_str, newline_str);
		ft_strdel(&newline_str);
		ft_strdel(&tmp);
		if ((env->quotes_index = char_index(env->joinned_str, '"')) >= 0)
		{
			check_characters_after_last_quotes(env, env->joinned_str + env->quotes_index + 1, item, env->line_counter_tmp);
			env->joinned_str[env->quotes_index] = '\0';
			ft_strdel(&line);
			break;
		}
		ft_strdel(&line);
	}
	store_string_item(env, item, item_length, item_container);
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
	env->joinned_str = str + i + 1;
	if ((last_quotes_index = char_index(env->joinned_str, '"')) >= 0)
	{
		check_characters_after_last_quotes(env, env->joinned_str + last_quotes_index + 1, item, env->line_counter);
		env->joinned_str[last_quotes_index + 1] = '\0';
	}
	if (env->joinned_str[ft_strlen(env->joinned_str) - 1] != '"') // find another solution here
		extract_multiline_string(env, item_length, item_container, item);
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

void ft_error_found_before_item(char **str, char **line, t_env *env, char *item)
{

	printf("Error[%d]: <%s> has been found before %s\n", env->line_counter, *str, item);
	ft_strdel(str);
	ft_strdel(line);
	// free the pointer to struct
	exit(0);
}

void ft_command_not_found(char *trimed_line, char *regular_line, t_env *env)
{
	printf("Syntax Error[%d]: Command <%s> not found\n", env->line_counter, trimed_line);
	ft_strdel(&trimed_line);
	ft_strdel(&regular_line);
	// free line,...
	exit(0);
}

void is_not_name_or_comment(t_env *env, char *trimed_line, char *regular_line)
{
	if (!env->check_name && env->check_comment)
		ft_error_found_before_item(&trimed_line, &regular_line, env, "name");
	else if (!env->check_comment && env->check_name)
		ft_error_found_before_item(&trimed_line, &regular_line, env, "comment");
	else if (!env->check_comment && !env->check_name)
		ft_error_found_before_item(&trimed_line, &regular_line, env, "name and comment");
}

void ft_header_operations(t_env *env, char *trimed_line, char *regular_line)
{
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
		is_not_name_or_comment(env, trimed_line, regular_line);
}

int check_line(char *trimed_line, char *regular_line)
{
	if (ft_empty_or_comment_line(trimed_line))
	{
		ft_strdel(&regular_line);
		ft_strdel(&trimed_line);
		return (1);
	}
	return (0);
}

void free_pointers(char *trimed_line, char *line)
{
	ft_strdel(&line);
	ft_strdel(&trimed_line);
}

int check_command(char *trimed_line)
{
	return (trimed_line[0] == '.' &&
			!str_begins_with(trimed_line, NAME_CMD_STRING) &&
			!str_begins_with(trimed_line, COMMENT_CMD_STRING));
}

unsigned int initialize_magic_header()
{
	return (((COREWAR_EXEC_MAGIC & 0xff) << 24) |
			(COREWAR_EXEC_MAGIC << 8 & 0xff0000) |
			(COREWAR_EXEC_MAGIC >> 8 & 0xff00));
}

void organize_beginning_data(t_env *env)
{
	char *regular_line;
	char *trimed_line;

	env->hdr.magic = initialize_magic_header();
	while (get_next_line(env->src_file, &regular_line) > 0)
	{
		env->line_counter += 1;
		trimed_line = ft_strtrim(regular_line);
		if (check_line(trimed_line, regular_line))
			continue;
		if (check_command(trimed_line))
			ft_command_not_found(trimed_line, regular_line, env);
		ft_header_operations(env, trimed_line, regular_line);
		if (check_name_comment_flag(env))
		{
			free_pointers(trimed_line, regular_line);
			break;
		}
		free_pointers(trimed_line, regular_line);
	}
	// printf("name = %s\n", env->hdr.prog_name);
	// printf("comment = %s\n", env->hdr.comment);
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
