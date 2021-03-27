/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_related.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:55:26 by aybouras          #+#    #+#             */
/*   Updated: 2021/03/27 18:13:20 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm_inc/cor.h"

void	parse_arg_dump(int *ac, int argc, char **argv, t_vm *vm)
{
	if (*ac + 1 <= argc)
	{
		if (!is_number(argv[*ac + 1]))
			free_nd_exit(vm, "Error: invalid parameter");
		vm->dump = ft_atoi(argv[*ac + 1]);
		vm->dump_flag = TRUE;
		if (vm->dump < 0)
			free_nd_exit(vm, "Error: invalid number");
		*ac = *ac + 1;
		return ;
	}
	free_nd_exit(vm, "Error: invalid parameters");
}

void	parse_arg_n(int *ac, int argc, char **argv, t_vm *vm)
{
	int			i;
	int			flag;
	t_gladiator	*gladiator;

	if (*ac + 2 < argc && (i = -1))
	{
		if (!ft_isdigit(argv[*ac + 1][0]) || !is_number(argv[*ac + 1]))
			free_nd_exit(vm, "Error: invalid parameters");
		vm->n_id = ft_atoi(argv[*ac + 1]);
		(vm->n_id > vm->last_id_gld) && (vm->last_id_gld = vm->n_id);
		gladiator = vm->gladiators;
		flag = 0;
		while (gladiator)
		{
			if (gladiator->id == vm->n_id)
				flag = 1;
			gladiator = gladiator->next;
		}
		if (!flag && ft_strlen(argv[(*ac)++ + 1]) <= 10 && vm->n_id > 0
					&& vm->n_id <= MAX_PLAYERS)
			return ;
	}
	free_nd_exit(vm, "Error: invalid parameters");
}

int		get_non_exist_id(t_gladiator *head)
{
	t_gladiator	*gldtor;
	int			id;

	id = 1;
	while (id <= MAX_PLAYERS)
	{
		gldtor = head;
		while (gldtor)
		{
			if (gldtor->id == id)
				break ;
			gldtor = gldtor->next;
		}
		if (!gldtor)
			return (id);
		id++;
	}
	return (-1);
}

void	parse_file(t_vm *vm, int ac, char **argv)
{
	t_gladiator *gldtor;

	vm->nbr_of_gldtors++;
	if (vm->nbr_of_gldtors > MAX_PLAYERS)
		free_nd_exit(vm, "Error: MAX_PLAYERS EXCEEDED");
	if (!(gldtor = (t_gladiator *)malloc(sizeof(t_gladiator))))
		free_nd_exit(vm, "Failed to build Gladiator.");
	ft_bzero(gldtor, sizeof(t_gladiator));
	gldtor->associated_file = argv[ac];
	get_player(vm, gldtor, &(vm->n_id));
	gldtor->next = NULL;
	if (!vm->gladiators)
	{
		vm->gladiators = gldtor;
		vm->tail = gldtor;
	}
	else
	{
		vm->tail->next = gldtor;
		vm->tail = gldtor;
	}
}

void	parse_args(int argc, char **argv, t_vm *vm)
{
	int			ac;
	char		*cor;

	ac = 1;
	vm->nbr_of_gldtors = 0;
	while (ac < argc)
	{
		if (!ft_strcmp("-dump", argv[ac]) || argv[ac][1] == 'd')
			parse_arg_dump(&ac, argc, argv, vm);
		else if ((cor = ft_strstr(argv[ac], ".cor"))
					&& cor != argv[ac] && !cor[4])
			parse_file(vm, ac, argv);
		else if (!ft_strcmp("-n", argv[ac]))
			parse_arg_n(&ac, argc, argv, vm);
		else
			free_nd_exit(vm, "Error: invalid parameters");
		ac++;
	}
	parse_helper(vm);
}
