/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 02:58:33 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/27 18:25:49 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm_inc/corewar.h"

void	save_label_position(char *line, int current_bytes, t_env *env)
{
	int i;
	int j;

	j = -1;
	while (is_space(line[++j]))
		;
	j != 0 ? --j : 0;
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

void	label_parsing(t_env *env, char *str, char *tmp)
{
	if (tmp[0] != LABEL_CHAR)
	{
		ft_printf("Error[%d]: Invalid instruction at <%s>\n", env->line_counter,
			str);
		ft_strdel(&str);
		ft_strdel(&env->save_op);
		exit(0);
	}
	env->label_already_checked = 1;
	ft_strdel(&str);
}

void	verify_single_label_in_line(t_env *env, char *trimed_line, int char_pos)
{
	char *label;

	env->check_eof = TRUE;
	env->label_already_checked = 1;
	label = ft_strsub(trimed_line, 0, char_pos);
	verify_label_chars(env, label);
	ft_strdel(&label);
}

void	check_duplicated_labels(t_env *env)
{
	t_label	*label_to_search;
	t_label	*lbl_to_cmp;
	int		founded;

	lbl_to_cmp = env->label;
	while (lbl_to_cmp)
	{
		founded = 0;
		label_to_search = env->label;
		while (label_to_search)
		{
			if (ft_strequ(label_to_search->label_name, lbl_to_cmp->label_name))
			{
				if (founded)
				{
					ft_printf("duplicated label founded\n");
					exit(0);
				}
				founded++;
			}
			label_to_search = label_to_search->next;
		}
		lbl_to_cmp = lbl_to_cmp->next;
	}
}

int		is_comment_at_end(int *comment_index, char *trimed_str)
{
	return ((*comment_index = char_index(trimed_str, COMMENT_CHAR)) >= 0 ||
				(*comment_index = char_index(trimed_str,
					ALT_COMMENT_CHAR)) >= 0);
}
