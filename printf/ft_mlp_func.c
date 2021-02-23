/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlp_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 05:46:59 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 05:52:29 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_ignore_left_zero(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '0')
		i++;
	return (i);
}

char	*ft_allocate_tab(int len)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (len + 2));
	str = (char *)ft_memset((char *)str, '0', len);
	str[len] = '\0';
	str[len + 1] = '\0';
	return (str);
}

void	ft_struct_init3(char *num1, char *num2, t_mlp *mlp)
{
	mlp->count = 0;
	mlp->i = ft_strlen(num1);
	mlp->len2 = ft_strlen(num2);
	mlp->len = mlp->i + mlp->len2;
	mlp->result = ft_allocate_tab(mlp->len);
}

void	ft_handle_special_cases(t_mlp *mlp, char *num1, char *num2, int flag)
{
	mlp->i = 0;
	if (flag)
		mlp->i = ft_ignore_left_zero(mlp->result);
	else if (((num1[0] == '0' && num2[0] != '0') ||
				(num2[0] == '0' && num1[0] != '0')) && !flag)
		mlp->i++;
	else if (mlp->count == ft_strlen(num1) || mlp->count == ft_strlen(num2))
		mlp->i++;
	mlp->tmp = mlp->result;
	mlp->result = ft_strdup(mlp->result + mlp->i);
}

void	ft_find_curr_pos(char *num1, t_mlp *mlp)
{
	mlp->carry = 0;
	mlp->curr_postion = ft_strlen(mlp->result) - (ft_strlen(num1) - mlp->i);
	mlp->j = mlp->len2;
}
