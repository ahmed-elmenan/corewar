/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:18:26 by anel-bou          #+#    #+#             */
/*   Updated: 2021/03/13 19:19:35 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int		is_empty_line(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '#')
			return (1);
		else if (line[i] != ' ' && line[i] != '\t')
			return (0);
	}
	return (1);
}

int		is_operation(char *line)
{
	int i;

	i = get_first_char_index(line);
	if (!get_operation_code(&line[i]))
		return (0);
	while (line[++i] && !is_space(line[i]))
		;
	if (line[i - 1] == LABEL_CHAR)
		return (0);
	return (1);
}

int		is_label(char *str)
{
	int i;
	int j;

	i = -1;
	while (str[++i] && str[i] != ':')
	{
		j = -1;
		while (LABEL_CHARS[++j] && str[i] != LABEL_CHARS[j])
			;
		if (LABEL_CHARS[j] == 0)
			return (0);
	}
	if (str[i] == 0 || i == 0)
		return (0);
	return (1);
}



/*
void	print_labels(t_env *env){t_label *l = env->label;printf("\n");while (l){printf("lblname=[%s]\tpos=[%d]\n", l->label_name, l->label_position);l = l->next;}}
void	print_data(t_env *env){t_data *d = env->data;printf("\n");while (d){printf("curr=[%d]\tline=[%s]\n", d->current_octets, d->line);d = d->next;}}
void	print_ops(t_env *env){t_opr *o;o = env->opr;while(o){printf("cod=%d [%s]\n", o->opr_code, o->line); o = o->next;}}

char *p = "vm_champs/champs/barriere.s";

// 	printf("____________________________________\n____________________________________\n");
// 	print_labels(env);
// 	print_data(env);
// 	print_ops(env);


// f='vm_champs/champs/toto' && make && ./asm $f.s && printf "\33c" &&  xxd $f.cor |pbcopy && rm -rf $f.cor
// ***********
// printf "\33c" && f='vm_champs/champs/toto' && ./vm_champs/asm $f.s &&  xxd $f.cor |pbcopy && rm -rf $f.cor



### FILE translate_data_to_code: FUNC: fill_node_by: (flekkkkkher ga33)

//	asp
//	opr->line = line;
//	opr->opr_size = get_operation_size(line);

*/