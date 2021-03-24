/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 02:09:56 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/24 19:32:26 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		extract_multiline_string(t_env *env, int item_length,
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
		free_pointers(newline_str);
		ft_strdel(&tmp);
		if ((env->quotes_index = char_index(env->joinned_str, '"')) >= 0)
		{
			check_characters_after_last_quotes(env->joinned_str +
						env->quotes_index + 1, item, env->line_counter_tmp);
			env->joinned_str[env->quotes_index] = '\0';
			ft_strdel(&line);
			break ;
		}
		ft_strdel(&line);
	}
	store_string_item(env, item, item_length, item_container);
}

void		extract_signleline_string(t_env *env, int item_length,
								char (*item_container)[item_length], char *item)
{
	int j;

	check_string_length(env, ft_strlen(env->trimed_line) - 2,
						item_length, item);
	j = env->x;
	++env->x;
	while (env->trimed_line[++j] && env->trimed_line[j] != '"')
		;
	ft_strncpy(*item_container, &env->trimed_line[env->x], j - env->x);
}

void		is_not_name_or_comment(t_env *env, char *trimed_line,
															char *regular_line)
{
	if (!env->check_name && env->check_comment)
		ft_error_found_before_item(&trimed_line, &regular_line, env, "name");
	else if (!env->check_comment && env->check_name)
		ft_error_found_before_item(&trimed_line, &regular_line, env, "comment");
	else if (!env->check_comment && !env->check_name)
		ft_error_found_before_item(&trimed_line, &regular_line, env,
															"name and comment");
}

int			calculate_comment_index(char *str)
{
	int comment_index;
	int alt_comment_index;

	comment_index = char_index(str, COMMENT_CHAR) > -1 ?
										char_index(str, COMMENT_CHAR) : INT_MAX;
	alt_comment_index = char_index(str, ALT_COMMENT_CHAR) > -1 ?
									char_index(str, ALT_COMMENT_CHAR) : INT_MAX;
	return (alt_comment_index >= comment_index ?
											comment_index : alt_comment_index);
}

void		ft_header_operations(t_env *env, char *regular_line)
{
	if (str_begins_with(env->trimed_line, NAME_CMD_STRING))
	{
		set_champ_info(env, PROG_NAME_LENGTH, &env->hdr.prog_name, "name");
		env->check_name |= 1;
	}
	else if (str_begins_with(env->trimed_line, COMMENT_CMD_STRING))
	{
		set_champ_info(env, COMMENT_LENGTH, &env->hdr.comment, "comment");
		env->check_comment |= 1;
	}
	else
		is_not_name_or_comment(env, env->trimed_line, regular_line);
}
