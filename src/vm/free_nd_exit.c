/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nd_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 09:24:08 by aybouras          #+#    #+#             */
/*   Updated: 2021/03/27 18:13:20 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm_inc/cor.h"

void	free_vm(t_vm *vm)
{
	ft_memdel((void **)&vm->colosseum);
	close(vm->fd);
	exit(0);
}

void	free_nd_exit(t_vm *vm, char *msg)
{
	t_gladiator *gldtor_lst;
	t_gladiator *gldtor_tmp;
	t_cursor	*curs_lst;
	t_cursor	*curs_tmp;

	if (msg)
		ft_putendl_fd(msg, 2);
	gldtor_lst = vm->gladiators;
	curs_lst = vm->cursors;
	while (curs_lst)
	{
		if (gldtor_lst)
		{
			gldtor_tmp = gldtor_lst->next;
			ft_memdel((void **)&gldtor_lst);
			gldtor_lst = gldtor_tmp;
		}
		if (curs_lst)
		{
			curs_tmp = curs_lst->next;
			ft_memdel((void **)&curs_lst);
			curs_lst = curs_tmp;
		}
	}
	free_vm(vm);
}
