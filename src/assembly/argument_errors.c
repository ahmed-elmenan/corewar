/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:34:08 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/24 18:46:22 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	error_passing_indirect(t_env *env, char *str)
{
	if (str[0] == LABEL_CHAR || ft_is_string_number(str))
	{
		ft_printf("Error[%d]: Passing indirect argument to <%s> operation\n",
			env->line_counter, env->found_op->op_name);
		exit(0);
	}
}

void	error_passing_direct(t_env *env, char c)
{
	if (c == DIRECT_CHAR)
	{
		ft_printf("Error[%d]: Passing direct argument to <%s> operation\n",
			env->line_counter, env->found_op->op_name);
		exit(0);
	}
}

void	error_passing_registry(t_env *env, char c)
{
	if (c == 'r')
	{
		ft_printf("Error[%d]: Passing registry argument to <%s> operation\n",
			env->line_counter, env->found_op->op_name);
		exit(0);
	}
}

void	error_big_reg_value(t_env *env)
{
	ft_printf("Error[%d]: Registery value is bigger than 16\n",
		env->line_counter);
	exit(0);
}

void	handle_number_error(t_env *env, char *arg, char *arg_type)
{
	if (arg[1] == '+')
		error_value_contains_positive_sign(env, arg_type);
}
