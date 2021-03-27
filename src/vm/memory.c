/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 09:36:29 by aybouras          #+#    #+#             */
/*   Updated: 2021/03/27 18:13:20 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm_inc/cor.h"

static void	dump_hex(unsigned char *memory)
{
	const char	*tab = "0123456789abcdef";
	int			i;

	i = 0;
	while (i < MAX_DUMP)
	{
		printf("%c", tab[memory[i] / 16]);
		printf("%c", tab[memory[i] % 16]);
		i < MAX_DUMP - 1 ? printf(" ") : 0;
		i++;
	}
	printf(" \n");
}

void		dump_arena(unsigned char *memory, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		i == 0 ? printf("0x0000 : ") : printf("%#.4x : ", i);
		dump_hex(memory + i);
		i += MAX_DUMP;
	}
}

int			addr_overlap(int addr)
{
	return ((MEM_SIZE + (addr)) % MEM_SIZE);
}

int			get_mem(unsigned char *mem, int addr, int oct)
{
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	while (i < oct)
	{
		ret = (ret << 8) + mem[addr_overlap(addr + i)];
		i++;
	}
	if (oct == 1)
		return ((char)ret);
	if (oct == 2)
		return ((short)ret);
	return (ret);
}

void		set_mem(unsigned char *mem, int addr, int val, int oct)
{
	int	i;

	i = 0;
	if (val < 0)
		val = ((long)1 << (oct * 8)) + (long)val;
	while (i < oct)
	{
		mem[addr_overlap(addr + i)] = val >> ((oct - i - 1) * 8);
		i++;
	}
}
