/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_related_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:40:25 by aybouras          #+#    #+#             */
/*   Updated: 2021/03/27 18:13:20 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm_inc/cor.h"

void	parse_magic_header(t_vm *vm, t_gladiator *gldtor, u_int8_t *buffer)
{
	if (read(vm->fd, buffer, 4) < 4)
	{
		ft_putstr_fd(gldtor->associated_file, 2);
		free_nd_exit(vm, " has an Invalid header.");
	}
	if (*(u_int32_t *)buffer != little_to_big_endian(COREWAR_EXEC_MAGIC))
	{
		ft_putstr_fd(gldtor->associated_file, 2);
		free_nd_exit(vm, " has an invalid magic Header.");
	}
}

void	parse_champ_name(t_vm *vm, t_gladiator *gldtor, u_int8_t *buffer)
{
	if (read(vm->fd, buffer, PROG_NAME_LENGTH) < PROG_NAME_LENGTH)
	{
		ft_putstr_fd(gldtor->associated_file, 2);
		free_nd_exit(vm, " has an Invalid PROG_NAME.");
	}
	ft_memcpy((void*)(gldtor->prog_name), buffer, PROG_NAME_LENGTH);
}

void	parse_exec_code_size(t_vm *vm, t_gladiator *gldtor, u_int8_t *buffer)
{
	if (read(vm->fd, buffer, FOUR_BYTES) < FOUR_BYTES)
	{
		ft_putstr_fd(gldtor->associated_file, 2);
		free_nd_exit(vm, " has an Invalid exec_code_size.");
	}
	vm->expected_exec_size = little_to_big_endian(*(unsigned int *)buffer);
}

void	parse_comment(t_vm *vm, t_gladiator *gldtor, u_int8_t *buffer)
{
	if (read(vm->fd, buffer, COMMENT_LENGTH) < COMMENT_LENGTH)
	{
		ft_putstr_fd(gldtor->associated_file, 2);
		free_nd_exit(vm, " has an Invalid COMMENT_LENGTH.");
	}
	ft_memcpy((void*)(gldtor->comment), buffer, COMMENT_LENGTH + 1);
}

void	parse_exec_code(t_vm *vm, t_gladiator *gldtor, u_int8_t *buffer)
{
	u_int32_t	size;

	if ((size = read(vm->fd, buffer, CHAMP_MAX_SIZE)) <= 0)
	{
		ft_putstr_fd(gldtor->associated_file, 2);
		free_nd_exit(vm, " is a champion without executable code");
	}
	if (size > CHAMP_MAX_SIZE)
		free_nd_exit(vm, " Executable code size exceed");
	if (size != vm->expected_exec_size)
	{
		ft_putstr_fd(gldtor->associated_file, 2);
		free_nd_exit(vm, " the expected code_size is diffirent !");
	}
	gldtor->exec_code_size = size;
	ft_memcpy(gldtor->exec_code, buffer, size);
}
