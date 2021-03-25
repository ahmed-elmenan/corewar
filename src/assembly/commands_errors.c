/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:39:24 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/24 18:46:32 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	content_not_found_error(char *item, t_env *env)
{
	ft_printf("error [%d]: <%s> content not found\n", env->line_counter, item);
	exit(0);
}

void	ft_error_found_before_item(char **str, char **line,
								t_env *env, char *item)
{
	ft_printf("Error[%d]: <%s> has been found before %s\n",
			env->line_counter, *str, item);
	ft_strdel(str);
	ft_strdel(line);
	exit(0);
}

void	ft_command_not_found(char *trimed_line, char *regular_line, t_env *env)
{
	ft_printf("Syntax Error[%d]: Command <%s> not found\n",
			env->line_counter, trimed_line);
	ft_strdel(&trimed_line);
	ft_strdel(&regular_line);
	exit(0);
}

void	unknown_arg_error(t_env *env, char *trimed_str)
{
	ft_printf("Error[%d]: Passing unknown argument to operation <%s>\n",
		env->line_counter, env->found_op->op_name);
	ft_strdel(&trimed_str);
	exit(0);
}

void	arg_is_empty(t_env *env, int i)
{
	ft_printf("Error[%d]: Argument number %d is Empty",
				env->line_counter, i + 1);
	exit(0);
}
