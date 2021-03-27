/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:35:05 by aybouras          #+#    #+#             */
/*   Updated: 2021/03/27 18:09:35 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm_inc/cor.h"

int			main(int ac, char **av)
{
	t_vm vm;

	vm_init(&vm);
	parse_args(ac, av, &vm);
	prepare_battleground(&vm);
	show_gladiators(vm.gladiators);
	let_the_game_begin(&vm);
	return (0);
}
