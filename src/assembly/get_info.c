/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 19:32:21 by anel-bou          #+#    #+#             */
/*   Updated: 2021/03/27 18:25:49 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm_inc/corewar.h"

t_opr	*get_current_opr_node(t_env *env, t_opr *opr)
{
	if (!env->opr)
	{
		env->opr = (t_opr *)ft_memalloc(sizeof(t_opr));
		return (env->opr);
	}
	opr->next = (t_opr *)ft_memalloc(sizeof(t_opr));
	return (opr->next);
}

int		is_args_octet_present(int op)
{
	return (op != 0x1 && op != 0x9 && op != 0xc && op != 0xf);
}

int		is_arg_first_char(char *line, int i)
{
	return (line[i] == 'r' || line[i] == '%' || line[i] == '-' ||
	(line[i] == ':' && line[i - 1] != '%') ||
	(line[i] >= '0' && line[i] <= '9'));
}

int		get_t_dir_size(int op)
{
	return ((op == 1 || op == 2 || op == 3 || op == 4 || op == 5 || op == 6
					|| op == 7 || op == 8 || op == 13 || op == 16) ? 4 : 2);
}
