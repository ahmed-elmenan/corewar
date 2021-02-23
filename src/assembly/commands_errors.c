/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 01:39:24 by ahel-men          #+#    #+#             */
/*   Updated: 2021/02/23 01:40:24 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	content_not_found_error(char *item, t_env *env)
{
	printf("error [%d]: <%s> content not found\n", env->line_counter, item);
	exit(0);
}

void	ft_error_found_before_item(char **str, char **line,
								t_env *env, char *item)
{
	printf("Error[%d]: <%s> has been found before %s\n",
			env->line_counter, *str, item);
	ft_strdel(str);
	ft_strdel(line);
	exit(0);
}

void	ft_command_not_found(char *trimed_line, char *regular_line, t_env *env)
{
	printf("Syntax Error[%d]: Command <%s> not found\n",
			env->line_counter, trimed_line);
	ft_strdel(&trimed_line);
	ft_strdel(&regular_line);
	exit(0);
}
