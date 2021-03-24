/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_errors_checker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:43:22 by ahel-men          #+#    #+#             */
/*   Updated: 2021/03/24 19:24:49 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	check_string_length(t_env *env, int item_len, int max_len, char *item)
{
	if (item_len > max_len)
	{
		ft_printf("Error[%d]: The champion %s exceed %d character\n",
			env->line_counter, item, max_len);
		exit(0);
	}
}

void	check_missing_last_quotes_error(t_env *env, char *item,
										int quotes_index)
{
	if (quotes_index == -1)
	{
		ft_printf("syntax error[%d]: ", env->line_counter);
		ft_printf("Couldn't find the ending quotes of the %s string\n", item);
		exit(0);
	}
}

void	check_characters_after_last_quotes(char *str,
											char *item, int line_counter)
{
	int		i;
	int		res;
	char	*tmp;
	char	*tmp2;

	i = -1;
	tmp = ft_strtrim(str);
	res = calculate_comment_index(tmp);
	while (tmp[++i] && !is_comment_char(tmp[i]))
	{
		if (is_space(tmp[i]))
			continue;
		else
		{
			tmp2 = ft_strsub(tmp, i, res - 1);
			str = ft_strtrim(tmp2);
			ft_printf("Syntax Error[%d]: ", line_counter);
			ft_printf("String <%s> has been found after %s ending quotes\n",
					str, item);
			free_pointers(tmp);
			exit(0);
		}
	}
	ft_strdel(&tmp);
}

void	check_name_and_comment_existence(int checker, char *item)
{
	if (!checker)
	{
		ft_printf("Error: Champion <%s> not found\n",
				item);
		exit(0);
	}
}

int		check_name_comment_flag(t_env *env)
{
	return (env->check_name && env->check_comment);
}
