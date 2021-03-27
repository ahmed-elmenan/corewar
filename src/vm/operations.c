/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 12:06:37 by aybouras          #+#    #+#             */
/*   Updated: 2021/03/27 18:13:20 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm_inc/cor.h"

void	logical_op(t_cursor *prc, t_op_component *cmp)
{
	if (cmp->code == 4)
		prc->reg[cmp->arg[2]] = cmp->arg[0] + cmp->arg[1];
	else if (cmp->code == 5)
		prc->reg[cmp->arg[2]] = cmp->arg[0] - cmp->arg[1];
	else if (cmp->code == 6)
		prc->reg[cmp->arg[2]] = cmp->arg[0] & cmp->arg[1];
	else if (cmp->code == 7)
		prc->reg[cmp->arg[2]] = cmp->arg[0] | cmp->arg[1];
	else if (cmp->code == 8)
		prc->reg[cmp->arg[2]] = cmp->arg[0] ^ cmp->arg[1];
	else if (cmp->code == 9 && prc->carry)
		prc->cur_addr = (prc->cur_addr - 3) + (cmp->arg[0] % IDX_MOD);
}

void	fork_op(t_cursor *prc, t_op_component *cmp, t_vm *vm)
{
	t_cursor	*new;
	int			cur_addr;

	if (prc->cmp.code == 12)
		cur_addr = addr_overlap(prc->cur_addr + cmp->arg[0] % IDX_MOD);
	else
		cur_addr = addr_overlap(prc->cur_addr + cmp->arg[0]);
	if (!(new = (t_cursor *)malloc(sizeof(t_cursor))))
		free_nd_exit(vm, "Error while forking new cursor.");
	ft_memcpy(new, prc, sizeof(t_cursor));
	new->cur_addr = cur_addr;
	new->id = vm->last_cursor_id++;
	new->wait_cycles = 0;
	new->next = vm->cursors;
	vm->cursors = new;
	vm->cursors_counter++;
}

void	mem_op(t_cursor *prc, t_op_component *cmp, t_vm *vm)
{
	if (cmp->code == 3)
	{
		if ((cmp->arg_code >> 4 & 3) == REG_CODE)
			prc->reg[cmp->arg[1]] = cmp->arg[0];
		else
			set_mem(vm->colosseum, prc->cur_addr + cmp->arg[1], cmp->arg[0], 4);
	}
	if (cmp->code == 11)
		set_mem(vm->colosseum, prc->cur_addr + (cmp->arg[1] +
										cmp->arg[2]) % IDX_MOD, cmp->arg[0], 4);
	if (cmp->code == 2 || cmp->code == 13)
		prc->reg[cmp->arg[1]] = cmp->arg[0];
	if (cmp->code == 10)
	{
		prc->reg[cmp->arg[2]] = get_mem(vm->colosseum,
			ft_idx_mod((int)(prc->cur_addr + cmp->arg[0] + cmp->arg[1])), 4);
	}
	if (cmp->code == 14)
		prc->reg[cmp->arg[2]] = get_mem(vm->colosseum,
					prc->cur_addr + (cmp->arg[0] + cmp->arg[1]) % IDX_MOD, 4);
}

int		live(t_vm *vm, t_cursor *prc)
{
	t_gladiator *gladiator;

	vm->lives_counter++;
	prc->is_alive = TRUE;
	if (between(prc->cmp.arg[0], -4, -1))
	{
		gladiator = get_gldtor_by_id(vm->gladiators, prc->cmp.arg[0] * (-1));
		if (gladiator)
		{
			gladiator->last_live = vm->cycles + 1;
			gladiator->lives++;
			vm->the_conqueror = gladiator;
			vm->total_lives++;
		}
	}
	return (prc->cmp.arg[0]);
}

void	set_carry(t_cursor *prc, t_op_component *cmp)
{
	if (cmp->code == 2 || cmp->code == 3)
		prc->carry = prc->reg[cmp->arg[1]] == 0;
	else
		prc->carry = prc->reg[cmp->arg[2]] == 0;
}
