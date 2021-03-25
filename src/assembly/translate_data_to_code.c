/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_data_to_code.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:20:59 by anel-bou          #+#    #+#             */
/*   Updated: 2021/03/24 19:38:07 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

unsigned char	set_args_octet(char *line)
{
	unsigned char	oct;
	int				i;
	int				shf;
	int				first_arg;

	oct = 0;
	shf = 6;
	first_arg = get_operation_len(line);
	while (is_space(line[first_arg]))
		first_arg++;
	i = first_arg;
	while (line[i] && shf && !is_comment_char(line[i]))
	{
		if (i == first_arg || ((line[i - 1] == SEPARATOR_CHAR ||
						is_space(line[i - 1])) && is_arg_first_char(line, i)))
		{
			oct = oct | (get_current_argument_code(&line[i]) << shf);
			shf -= 2;
		}
		i++;
	}
	return (oct);
}

int				get_label_position(char *line, t_env *env)
{
	t_label	*lbl;
	int		i;

	i = -1;
	while (line[++i] && is_char_in_str(line[i], LABEL_CHARS))
		;
	lbl = env->label;
	while (lbl)
	{
		if (ft_strncmp(line, lbl->label_name, i) == 0 &&
			lbl->label_name[i] == 0)
			return (lbl->label_position);
		lbl = lbl->next;
	}
	ft_printf("Error: Passed label not found\n");
	exit(0);
	return (0);
}

unsigned int	get_argument_value(char *line, int i, t_data *data, t_env *env)
{
	unsigned int	value;
	int				label_pos;

	value = 0;
	if (line[i] == ':' || (line[i] == '%' && line[i + 1] == ':' && ++i))
	{
		i++;
		label_pos = get_label_position(&line[i], env);
		value = label_pos - data->current_octets;
	}
	else if (line[i] == 'r' || line[i] == '%' ||
										line[i] == '-' || ft_isdigit(line[i]))
	{
		if (line[i] == 'r' || line[i] == '%')
			i++;
		value = (unsigned int)ft_atoi(&line[i]);
	}
	return (value);
}

void			fill_node_by_operation(t_opr *opr, char *line,
													t_data *data, t_env *env)
{
	int		i;

	opr->enc_octet = 0;
	i = get_first_char_index(line);
	opr->opr_code = get_operation_code(&line[i]);
	if (is_args_octet_present(opr->opr_code))
		opr->enc_octet = set_args_octet(&line[i]);
	while (line[++i] && !is_space(line[i]) && line[i + 1] != '%')
		;
	while (line[++i] && is_space(line[i]))
		;
	opr->arg1 = get_argument_value(line, i, data, env);
	while (line[i] && line[i] != SEPARATOR_CHAR)
		i++;
	line[i] ? i++ : 0;
	while (line[i] && is_space(line[i]))
		i++;
	opr->arg2 = get_argument_value(line, i, data, env);
	while (line[i] && line[i] != SEPARATOR_CHAR)
		i++;
	line[i] ? i++ : 0;
	while (line[i] && is_space(line[i]))
		i++;
	opr->arg3 = get_argument_value(line, i, data, env);
}

void			translate_data_to_code(t_env *env)
{
	t_data	*data;
	t_opr	*opr;
	int		i;

	check_duplicated_labels(env);
	data = env->data;
	while (data)
	{
		i = 0;
		if (is_operation(data->line) ||
			(i = is_label_operation_in_same_line(data->line)))
		{
			opr = get_current_opr_node(env, opr);
			fill_node_by_operation(opr, &(data->line)[i], data, env);
		}
		data = data->next;
	}
}
