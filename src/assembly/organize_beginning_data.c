/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_beginning_data.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:14:49 by anel-bou          #+#    #+#             */
/*   Updated: 2021/02/01 19:55:38 by ahel-men         ###   ########.fr       */
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

char *end_quotes_search(t_env *env, char *joinned_str)
{
	int res;
	int quotes_index;
	int newline_nbr;
	char *newline_str;
	char *line;
	char *tmp;

	newline_nbr = 0;
	while ((res = get_next_line(env->src_file, &line)) > 0)
	{
		tmp = joinned_str;
		newline_str = ft_strjoin("\n", line);
		joinned_str = ft_strjoin(joinned_str, newline_str);
		// ft_strdel(&tmp);

		if ((quotes_index = char_index(joinned_str, '"')) >= 0)
		{

			joinned_str[quotes_index] = '\0';

			break;
		}
		env->save_name_len += ft_strlen(joinned_str);
		// ft_strdel(&newline_str);
		// ft_strdel(&line);
		newline_nbr++;
	}
	if (quotes_index == -1)
		printf("string end quotes doesn't exist");
	if (ft_strlen(joinned_str) > PROG_NAME_LENGTH)
	{
		ft_putendl("The champion name exceed 128 character");
		// free the pointer to struct
		exit(0);
	}
	return joinned_str;
}

void set_champ_name(t_env *env, char *str, int len)
{
	int i;
	int j;
	char str_length;
	char *joinned_str;
	char *tmp; //test

	i = -1;
	while (str[++i] && str[i] != '"')
		;
	// name = ""
	if (ft_strequ(str + i, "\"\""))
		env->hdr.prog_name[0] = '\0';
	// name = ""

	// if (env->save_name_len > len)
	// {
	// 	ft_putendl("The champion name exceed 128 character");
	// 	// free the pointer to struct
	// 	exit(0);
	// }
	// multilines in stirng name
	joinned_str = str + i + 1;
	if (joinned_str[ft_strlen(joinned_str) - 1] != '"')
	{
		tmp = end_quotes_search(env, joinned_str); // strcopy to prog
		printf("tmp  = %s\n", tmp);
		printf("tmp len  = %d\n", ft_strlen(tmp)); 
		exit(0);
	}
	else // single line in stirng name
	{
		j = i;
		++i;
		while (str[++j] && str[j] != '"')
			;
		ft_strncpy(env->hdr.prog_name, &str[i], j - i);
		printf("prog  = %s\n", env->hdr.prog_name);
		exit(0);
	}
	env->check_name |= 1;
}

void set_champ_comment(t_env *env, char *str)
{
	int i;
	int j;

	i = -1;
	while (str[++i] && str[i] != '"')
		;
	j = i;
	++i;
	while (str[++j] && str[j] != '"')
		;
	ft_strncpy(env->hdr.comment, &str[i], j - i);
	env->check_comment |= 1;
}

void ft_check_name_and_comment_existence(int checker, char *item)
{
	if (!checker)
	{
		printf("checker = %d\n", checker);
		ft_putstr(item);
		ft_putendl(" doesn't exist");
		// free the pointer to struct
		exit(0);
	}
}

void organize_beginning_data(t_env *env)
{
	char *line;
	// check erro name & comment
	env->hdr.magic = ((COREWAR_EXEC_MAGIC & 0xff) << 24) |
					 (COREWAR_EXEC_MAGIC << 8 & 0xff0000) | (COREWAR_EXEC_MAGIC >> 8 & 0xff00);
	while (get_next_line(env->src_file, &line) > 0)
	{
		if (str_begins_with(line, NAME_CMD_STRING))
			set_champ_name(env, line, PROG_NAME_LENGTH);
		else if (str_begins_with(line, COMMENT_CMD_STRING))
		{
			set_champ_comment(env, line);
			break;
		}
	}
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
