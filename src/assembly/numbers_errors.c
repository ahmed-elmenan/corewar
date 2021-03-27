/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 03:00:02 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/27 18:25:49 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm_inc/corewar.h"

void	error_reg_value_is_negative(t_env *env)
{
	ft_printf("Error[%d]: Registery value is negative\n",
		env->line_counter);
	exit(0);
}

void	error_reg_value_not_digit(t_env *env)
{
	ft_printf("Error[%d]: Registery value is not a digit\n",
		env->line_counter);
	exit(0);
}

void	error_value_contains_positive_sign(t_env *env, char *arg_type)
{
	ft_printf("Error[%d]: %s value contains positive sign\n",
		env->line_counter, arg_type);
	exit(0);
}

int		is_unknown_arg(char *str)
{
	return (str[0] != LABEL_CHAR && str[0] != DIRECT_CHAR &&
			str[0] != 'r' && !ft_is_string_number(str));
}
