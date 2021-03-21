/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 03:00:02 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/21 14:59:20 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	error_reg_value_is_negative(t_env *env)
{
	printf("Error[%d]: Registery value is negative\n",
		env->line_counter);
	exit(0);
}

void	error_reg_value_not_digit(t_env *env)
{
	printf("Error[%d]: Registery value is not a digit\n",
		env->line_counter);
	exit(0);
}

void	error_value_contains_positive_sign(t_env *env, char *arg_type)
{
	printf("Error[%d]: %s value contains positive sign\n",
		env->line_counter, arg_type);
	exit(0);
}

void	error_overflow_or_underflow_int(t_env *env, char *arg_type)
{
	// printf("Error[%d]: %s value is bigger or less than int limits\n",
	// 	env->line_counter, arg_type);
	// exit(0);
}

void	handle_int_errors(t_env *env, char *arg, char *arg_type)
{
	if (ft_is_string_number(arg + 1))
		if (ft_atoll(arg + 1) == TRUE)
			error_overflow_or_underflow_int(env, arg_type);
}
