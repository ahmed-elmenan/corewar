/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 02:58:33 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/19 17:51:32 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void    save_label_position(char *line, int current_bytes, t_env *env)
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
		printf("Error[%d]: Invalid instruction at <%s>\n", env->line_counter,
			str);
		ft_strdel(&str);
		ft_strdel(&env->save_op);
		exit(0);
	}
	env->label_already_checked = 1;
	ft_strdel(&str);
}
