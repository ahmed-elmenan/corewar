/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 03:00:02 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/24 18:47:06 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

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
