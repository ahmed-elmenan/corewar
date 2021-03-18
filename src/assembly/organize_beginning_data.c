/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_beginning_data.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:14:49 by anel-bou          #+#    #+#             */
/*   Updated: 2021/03/18 17:11:57 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void			store_string_item(t_env *env, char *item,
	int item_length, char (*item_container)[item_length])
{
	check_missing_last_quotes_error(env, item, env->quotes_index);
	env->line_counter = env->line_counter_tmp;
	check_string_length(env, ft_strlen(env->joinned_str), item_length, item);
	ft_strcpy(*item_container, env->joinned_str);
	ft_memdel((void **)&env->joinned_str);
}

void			set_champ_info(t_env *env, int item_length,
			char (*item_container)[item_length], char *item)
{
	char	*content_arr;
	char	*tmp;
	int		last_quotes_index;

	env->i = -1;
	while (env->trimed_line[++env->i] && env->trimed_line[env->i] != '"')
		;
	if (env->i == ft_strlen(env->trimed_line))
		content_not_found_error(item, env);
	if (ft_strequ(env->trimed_line + env->i, "\"\"") &&
		((*item_container)[0] = '\0'))
		return ;
	env->joinned_str = env->trimed_line + env->i + 1;
	if ((last_quotes_index = char_index(env->joinned_str, '"')) >= 0)
	{
		check_characters_after_last_quotes(env,
						env->joinned_str + last_quotes_index + 1,
						item, env->line_counter);
		env->joinned_str[last_quotes_index + 1] = '\0';
	}
	if (env->joinned_str[ft_strlen(env->joinned_str) - 1] != '"')
		extract_multiline_string(env, item_length, item_container, item);
	else
		extract_signleline_string(env, item_length, item_container, item);
}

void			organize_beginning_data(t_env *env)
{
	char *regular_line;

	env->hdr.magic = (((COREWAR_EXEC_MAGIC & 0xff) << 24) |
					(COREWAR_EXEC_MAGIC << 8 & 0xff0000) |
					(COREWAR_EXEC_MAGIC >> 8 & 0xff00));
	while (get_next_line(env->src_file, &regular_line) > 0)
	{
		env->line_counter += 1;
		if (check_line(regular_line))
			continue ;
		env->trimed_line = ft_strtrim(regular_line);
		if (check_command(env->trimed_line))
			ft_command_not_found(env->trimed_line, regular_line, env);
		ft_header_operations(env, regular_line);
		if (check_name_comment_flag(env))
		{
			free_pointers(env->trimed_line, regular_line);
			break ;
		}
		free_pointers(env->trimed_line, regular_line);
	}
	check_name_and_comment_existence(env->check_name, "name");
	check_name_and_comment_existence(env->check_comment, "comment");
}

void			write_beginning_data(t_env *env)
{
	int null;

	null = 0;
	write(env->dst_file, &(env->hdr.magic), 4);
	write(env->dst_file, &(env->hdr.prog_name), PROG_NAME_LENGTH);
	write(env->dst_file, &null, 4);
	write(env->dst_file, &null, 4);
	write(env->dst_file, &(env->hdr.comment), COMMENT_LENGTH);
	write(env->dst_file, &null, 4);
}
