/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 03:07:38 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/24 19:57:09 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	operation_parsing(t_env *env, int *is_op, char *op, int i)
{
	char	*args_tmp;
	char	**args;
	int		args_len;
	int		comment_index;

	*is_op = 1;
	args_tmp = op + i - 1;
	if ((comment_index = char_index(args_tmp, COMMENT_CHAR)) >= 0 ||
				(comment_index = char_index(args_tmp, ALT_COMMENT_CHAR)) >= 0)
		args_tmp[comment_index] = 0;
	if (args_tmp[ft_strlen(args_tmp) - 1] == SEPARATOR_CHAR)
	{
		ft_printf("Syntax Error[%d]: ", env->line_counter);
		ft_printf("Found separator at the end of the operation <%s>'s ",
				env->sub_op);
		ft_printf("arguments\n");
		exit(0);
	}
	args = ft_strsplit(args_tmp, SEPARATOR_CHAR);
	args_len = arr_len_2d(args);
	ft_check_args_len(env, args_len);
	check_args_type(env, args);
	free_2d(args, args_len);
	ft_strdel(&env->sub_op);
	ft_strdel(&env->save_op);
}

void	check_args_type(t_env *env, char **args)
{
	int		i;
	int		comment_index;
	char	*trimed_str;
	char	*tmp;

	i = -1;
	while (args[++i])
	{
		trimed_str = ft_strtrim(args[i]);
		if (!ft_strlen(trimed_str))
		{
			ft_printf("Error[%d]: Argument number %d is Empty",
													env->line_counter, i + 1);
			exit(0);
		}
		check_passing_wrong_arg(env, trimed_str, i);
		if (trimed_str[0] != LABEL_CHAR && trimed_str[0] != DIRECT_CHAR &&
			trimed_str[0] != 'r' && !ft_is_string_number(trimed_str))
		{
			ft_printf("Error[%d]: Passing unknown argument to operation <%s>\n",
					env->line_counter, env->found_op->op_name);
			ft_strdel(&trimed_str);
			exit(0);
		}
		if ((comment_index = char_index(trimed_str, COMMENT_CHAR)) >= 0 ||
				(comment_index = char_index(trimed_str, ALT_COMMENT_CHAR)) >= 0)
		{
			tmp = trimed_str;
			trimed_str[comment_index] = 0;
			trimed_str = ft_strtrim(trimed_str);
			ft_strdel(&tmp);
		}
		check_argument_value(env, trimed_str);
		ft_strdel(&trimed_str);
	}
}
