/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:46:23 by aybouras          #+#    #+#             */
/*   Updated: 2021/03/27 18:25:49 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm_inc/corewar.h"

void	free_2d(char **array, int len)
{
	int row;

	row = 0;
	if (array)
	{
		while (row < len)
		{
			ft_strdel(&array[row]);
			row++;
		}
		free(array);
		array = NULL;
	}
}

void	is_empty_body(t_env *env)
{
	if (!env->check_eof)
	{
		ft_printf("Syntax Error:File doesn't contain any label or operation\n");
		exit(0);
	}
}

void	is_newline_at_eof(t_env *env)
{
	if (env->ret == 2)
	{
		ft_printf("file doesn't end with a new line\n");
		exit(0);
	}
}

void	init_vars(t_env *env)
{
	env->check_eof = FALSE;
	env->flag = FALSE;
	env->current_bytes = 0;
	env->dt = env->data;
}
