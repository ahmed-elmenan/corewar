/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_related.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:55:36 by aybouras          #+#    #+#             */
/*   Updated: 2021/03/27 18:13:20 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm_inc/cor.h"

t_gladiator	*get_gldtor_by_id(t_gladiator *gldtor_lst, int id)
{
	while (gldtor_lst)
	{
		if (gldtor_lst->id == id)
			return (gldtor_lst);
		gldtor_lst = gldtor_lst->next;
	}
	return (NULL);
}

void		check_null_bytes(t_vm *vm)
{
	unsigned char	b;
	int				i;

	i = 0;
	while (i < 4)
	{
		read(vm->fd, &b, 1);
		if (b)
			free_nd_exit(vm, "the four NULL-bytes are missing !");
		i++;
	}
}

void		open_cor_file(t_vm *vm, t_gladiator *gldtor)
{
	if ((vm->fd = open(gldtor->associated_file, O_RDONLY)) < 0)
	{
		ft_putstr_fd(gldtor->associated_file, 2);
		free_nd_exit(vm, " is an Invalid file.");
	}
}

void		get_player(t_vm *vm, t_gladiator *gldtor, int *n_id)
{
	u_int8_t	buffer[4096];

	gldtor->id = -1;
	open_cor_file(vm, gldtor);
	parse_magic_header(vm, gldtor, (u_int8_t *)buffer);
	parse_champ_name(vm, gldtor, (u_int8_t *)buffer);
	check_null_bytes(vm);
	parse_exec_code_size(vm, gldtor, (u_int8_t *)buffer);
	parse_comment(vm, gldtor, (u_int8_t *)buffer);
	check_null_bytes(vm);
	parse_exec_code(vm, gldtor, (u_int8_t *)buffer);
	if (*n_id > 0)
	{
		gldtor->id = *n_id;
		*n_id = -1;
	}
	close(vm->fd);
}
