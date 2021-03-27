/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_related.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:55:52 by aybouras          #+#    #+#             */
/*   Updated: 2021/03/27 18:13:20 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm_inc/cor.h"

void	vm_init(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
	if (!(vm->colosseum = (u_int8_t *)malloc(sizeof(u_int8_t) *
												(MEM_SIZE + 1))))
	{
		ft_putendl_fd("Failed to build the Colosseum", 2);
		exit(1);
	}
	ft_bzero(vm->colosseum, sizeof(vm->colosseum));
	init_op_tab(op_tab);
	vm->cycles = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->n_id = -1;
	vm->last_id_gld = 1;
	vm->dump_flag = FALSE;
	vm->the_conqueror = NULL;
	vm->cursors_counter = 0;
	vm->last_cursor_id = 1;
	vm->lives_counter = 0;
}

void	prepare_battleground(t_vm *vm)
{
	int			id;
	int			mem_zone;
	int			size;
	t_cursor	*cursor;

	id = 1;
	mem_zone = 0;
	size = MEM_SIZE / vm->nbr_of_gldtors;
	while (id <= vm->nbr_of_gldtors)
	{
		cursor = init_cursor(vm, id, mem_zone);
		load_cursor(&(vm->cursors), cursor);
		mem_zone += size;
		id++;
	}
}
