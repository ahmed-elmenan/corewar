/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:39:21 by anel-bou          #+#    #+#             */
/*   Updated: 2021/03/24 00:19:41 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		get_last_dot_index(char *s)
{
	int i;
	int j;

	i = 0;
	j = -1;
	while (s[i])
	{
		if (s[i] == '.')
			j = i;
		i++;
	}
	return (j);
}

char	*get_file_name(char *s)
{
	int		last_dot;
	char	*file_name;
	char	*tmp;

	file_name = NULL;
	last_dot = get_last_dot_index(s);
	tmp = ft_strsub(s, 0, get_last_dot_index(s));
	file_name = ft_strjoin(tmp, ".cor");
	ft_strdel(&tmp);
	return (file_name);
}

int		create_file(char *s, t_env *env)
{
	char *exec_name;

	exec_name = get_file_name(s);
	ft_putstr("Writing output program to ");
	ft_putstr(exec_name);
	ft_putendl(" ...");
	env->dst_file = open(exec_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_memdel((void **)&exec_name);
	return (0);
}
