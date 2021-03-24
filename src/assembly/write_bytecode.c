/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytecode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 15:26:06 by anel-bou          #+#    #+#             */
/*   Updated: 2021/03/24 19:39:00 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	write_file_size(t_env *env, unsigned int num)
{
	int size;
	int byte;

	size = 3;
	while (size >= 0)
	{
		byte = (unsigned char)((num & (0xff << (size * 8))) >> (size * 8));
		write(env->dst_file, &byte, 1);
		size--;
	}
}

void	write_octets(t_env *env, unsigned int num, int size)
{
	while (size >= 0)
	{
		env->champion[env->i] =
					(unsigned char)((num & (0xff << (size * 8))) >> (size * 8));
		size--;
		(env->i)++;
	}
}

int		get_arg_size(t_opr *opr, int shft)
{
	int arg_code;

	if (!opr->enc_octet)
		return (opr->opr_code == 0x1 ? 4 : 2);
	arg_code = (opr->enc_octet & (0b11 << shft)) >> shft;
	if (arg_code == 0b01)
		return (1);
	if (arg_code == 0b10)
		return (get_t_dir_size(opr->opr_code));
	if (arg_code == 0b11)
		return (2);
	return (0);
}

void	write_operation(t_env *env, t_opr *opr)
{
	write_octets(env, opr->opr_code, sizeof(opr->opr_code) - 1);
	if (is_args_octet_present(opr->opr_code))
		write_octets(env, opr->enc_octet, sizeof(opr->enc_octet) - 1);
	if (opr->enc_octet & 0b11000000 || !opr->enc_octet)
		write_octets(env, opr->arg1, get_arg_size(opr, 6) - 1);
	if (opr->enc_octet & 0b00110000)
		write_octets(env, opr->arg2, get_arg_size(opr, 4) - 1);
	if (opr->enc_octet & 0b00001100)
		write_octets(env, opr->arg3, get_arg_size(opr, 2) - 1);
}

void	write_bytecode_in_file(t_env *env)
{
	t_opr	*opr;

	write_beginning_data(env);
	opr = env->opr;
	while (opr)
	{
		write_operation(env, opr);
		opr = opr->next;
	}
	write(env->dst_file, env->champion, env->i);
	if (lseek(env->dst_file, 136, SEEK_SET) > 0)
		write_file_size(env, env->i);
}
