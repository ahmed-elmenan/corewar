/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:26:35 by anel-bou          #+#    #+#             */
/*   Updated: 2021/02/01 15:30:44 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int	open_file(char *s, t_env *env)
{
	if ((env->src_file = open(s, O_RDONLY)) == -1)
	{
		ft_putendl_fd("unable to open this file", 2);
		return (0);
	}
	return (1);
}

t_env	*allocate_variables(t_env *env)
{
	env = (t_env *)ft_memalloc(sizeof(t_env));
	env->data = (t_data *)ft_memalloc(sizeof(t_data));
	env->bgn_data = (char *)ft_memalloc(sizeof(char) * BGN_DATA);
	env->champion = (char *)ft_memalloc(sizeof(char) * CHAMP_MAX_SIZE);
	return (env);
}

int     main(int ac, char **av)
{
	t_env *env;
	t_env global_struct;

	char *p = "qwer.s";
	if (ac > 1 || 1)
	{
		ft_bzero(&global_struct, sizeof(t_env)); // zerowing ahel-men
		env = allocate_variables(&global_struct);
		if (!open_file(p, env))
			return (-1);
		organize_beginning_data(env);
		tokenize_data(env);
		/* is_input_correct() */
		translate_data_to_code(env);
		create_file(p, env);
		write_bytecode_in_file(env);
	}
	return (0);
}