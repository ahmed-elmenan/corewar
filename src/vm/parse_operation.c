/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:01:45 by aybouras          #+#    #+#             */
/*   Updated: 2021/03/27 18:13:20 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm_inc/cor.h"

static int		get_tind(t_vm *vm, t_cursor *prc, int pc)
{
	int	addr;

	addr = get_mem(vm->colosseum, pc, 2);
	if (prc->cmp.code == 3)
		return (addr % IDX_MOD);
	if (op_tab[prc->cmp.code].mod)
		return (get_mem(vm->colosseum, prc->cur_addr + (addr % IDX_MOD), 4));
	else
		return (get_mem(vm->colosseum, prc->cur_addr + addr, 4));
}

static _Bool	get_reg(t_vm *vm, t_cursor *prc, int pc, int arg)
{
	static const int op_need_reg_addr1[] = {0, 0, 2, 3, 0, 0, 0, 0, 0,
													0, 0, 0, 0, 13, 0, 0, 0};
	static const int op_need_reg_addr2[] = {0, 0, 0, 0, 4, 5, 6, 7, 8,
													0, 10, 0, 0, 0, 14, 0, 0};

	pc = addr_overlap(pc);
	if (vm->colosseum[pc] > 16 || vm->colosseum[pc] < 1)
		return (0);
	if (op_need_reg_addr1[prc->cmp.code] && arg == 1)
		prc->cmp.arg[arg] = vm->colosseum[pc];
	else if (op_need_reg_addr2[prc->cmp.code] && arg == 2)
		prc->cmp.arg[arg] = vm->colosseum[pc];
	else
		prc->cmp.arg[arg] = prc->reg[vm->colosseum[pc]];
	return (1);
}

int				get_arg_helper(t_vm *vm, t_cursor *prc, int ac)
{
	int res;

	if (ac == T_DIR)
		res = get_tdir(vm, prc, prc->cur_addr + prc->cmp.step);
	if (ac == T_IND)
		res = get_tind(vm, prc, prc->cur_addr + prc->cmp.step);
	return (res);
}

static int		get_arg(t_vm *vm, t_cursor *prc, int code)
{
	int i;
	int ac;

	i = 0;
	prc->cmp.arg_code = vm->colosseum[addr_overlap(prc->cur_addr + 1)];
	while (i < op_tab[code].arg_num)
	{
		ac = (prc->cmp.arg_code >> (6 - i * 2) & 3);
		ac += ac == 3;
		if (op_tab[code].arg[i] & ac)
		{
			prc->cmp.arg[i] = get_arg_helper(vm, prc, ac);
			if (ac == T_REG && !get_reg(vm, prc, prc->cur_addr + prc->cmp.step,
											i))
				return (0);
		}
		else
			return (0);
		prc->cmp.step += ac != T_DIR ? 1 + (ac == T_IND) :
													op_tab[code].size_dir;
		i++;
	}
	return (1);
}

t_boolean		parse_operation(t_vm *vm, t_cursor *prc)
{
	if (!op_tab[prc->cmp.code].arg_code)
	{
		prc->cmp.step = 1 + op_tab[prc->cmp.code].size_dir;
		prc->cmp.arg[0] = get_mem(vm->colosseum, prc->cur_addr + 1,
									prc->cmp.step - 1);
		return (TRUE);
	}
	prc->cmp.step = 2;
	if (get_arg(vm, prc, prc->cmp.code))
		return (TRUE);
	return (FALSE);
}
