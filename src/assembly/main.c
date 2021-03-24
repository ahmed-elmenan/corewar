/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:26:35 by anel-bou          #+#    #+#             */
/*   Updated: 2021/03/24 12:05:11 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int open_file(char *s, t_env *env)
{
	if ((env->src_file = open(s, O_RDONLY)) == -1)
	{
		ft_putendl_fd("unable to open this file", 2);
		return (0);
	}
	return (1);
}

void allocate_variables(t_env **env)
{
	(*env) = (t_env *)ft_memalloc(sizeof(t_env));
	(*env)->data = (t_data *)ft_memalloc(sizeof(t_data));
	(*env)->bgn_data = (char *)ft_memalloc(sizeof(char) * BGN_DATA);
	(*env)->champion = (char *)ft_memalloc(sizeof(char) * CHAMP_MAX_SIZE * 10);
}

int main(int ac, char **av)
{
	t_env *env;

	if (ac > 1)
	{
		if (av[1][ft_strlen(av[1]) - 1] != 's' || av[1][ft_strlen(av[1]) - 2] != '.')
		{
			printf("Error: The file <%s> is not a valid file it doesn't contain '.s' extension\n", av[1]);
			exit(0);
		}
		allocate_variables(&env);
		if (!open_file(av[ac - 1], env))
			return (-1);
		organize_beginning_data(env);
		tokenize_data(env);
		translate_data_to_code(env);
		create_file(av[ac - 1], env);
		write_bytecode_in_file(env);
		liberate_memory(env);
	}
	return (0);
}