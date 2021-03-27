/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:44:08 by aybouras          #+#    #+#             */
/*   Updated: 2021/03/27 18:23:40 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COR_H
# define COR_H

# include <stdlib.h>
# include "../op.h"
# include "../../ft_printf/ft_printf.h"
# include <fcntl.h>
# include <stdio.h> // ************* delete
# include <unistd.h>

# define FOUR_BYTES 4
# define MAX_DUMP 64

typedef enum			e_boolean
{
	FALSE,
	TRUE,
}						t_boolean;

typedef struct			s_gladiator
{
	int					id;
	char				*associated_file;
	char				prog_name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	char				exec_code[MEM_SIZE];
	u_int32_t			exec_code_size;
	int					last_live;
	int					lives;
	struct s_gladiator	*next;
}						t_gladiator;

typedef struct			s_op
{
	char				code;
	const char			*name;
	char				arg_num;
	char				arg[3];
	short				waiting_cycle;
	t_boolean			arg_code;
	t_boolean			carry;
	int					size_dir;
	int					mod;
	int					op_type;
}						t_op;

typedef struct			s_op_component
{
	int					code;
	unsigned char		arg_code;
	int					arg[4];
	int					step;
}						t_op_component;

t_op					op_tab[17];

typedef	struct			s_cursor
{
	int					id;
	u_int32_t			cur_addr;
	t_boolean			carry;
	int					op_code;
	int					wait_cycles;
	int					jump;
	int					reg[REG_NUMBER + 1];
	t_op_component		cmp;
	t_boolean			is_alive;
	struct s_cursor		*next;
}						t_cursor;

typedef struct			s_vm
{
	u_int8_t			*colosseum;
	t_gladiator			*gladiators;
	t_gladiator			*tail;
	int					nbr_of_gldtors;
	int					n_id;
	int					last_cursor_id;
	int					last_id_gld;
	t_gladiator			*the_conqueror;
	t_cursor			*cursors;
	int					cursors_counter;
	int					cycles;
	int					cycles_to_die;
	int					cycles_last_check;
	int					count_live_checks;
	int					lives_counter;
	int					dump;
	t_boolean			dump_flag;
	int					total_cycles;
	int					total_lives;
	int					fd;
	u_int32_t			expected_exec_size;
}						t_vm;

u_int32_t				little_to_big_endian(unsigned int x);
void					vm_init(t_vm *vm);
void					parse_args(int argc, char **argv, t_vm *vm);
void					get_player(t_vm *vm, t_gladiator *gldtor, int *n_id);
t_gladiator				*get_gldtor_by_id(t_gladiator *gldtor_lst, int id);
t_cursor				*init_cursor(t_vm *vm, int id, int mem_zone);
void					load_cursor(t_cursor **curs_list, t_cursor *new);
void					prepare_battleground(t_vm	*vm);
void					let_the_game_begin(t_vm *vm);
void					init_op_tab(t_op *op);
int						addr_overlap(int addr);
t_boolean				parse_operation(t_vm *vm, t_cursor *prc);
void					logical_op(t_cursor *prc, t_op_component *cmp);
void					fork_op(t_cursor *prc, t_op_component *cmp, t_vm *vm);
void					mem_op(t_cursor *prc, t_op_component *cmp, t_vm *vm);
int						live(t_vm *vm, t_cursor *prc);
void					set_carry(t_cursor *prc, t_op_component *cmp);
void					set_mem(unsigned char *mem, int addr, int val, int oct);
int						get_mem(unsigned char *mem, int addr, int oct);
void					dump_arena(unsigned char *memory, int size);
void					show_gladiators(t_gladiator *gldtors);
int						get_non_exist_id(t_gladiator *head);
void					set_op_code(t_cursor *prc, t_vm *vm);
int						get_op_size(t_cursor *prc);
void					parse_helper(t_vm *vm);
void					print_colosseum(t_vm *v);
void					free_nd_exit(t_vm *vm, char *msg);
t_cursor				*kill_cursor(t_vm *vm, t_cursor *this, t_cursor *prev);
int						get_tdir(t_vm *vm, t_cursor *prc, int pc);
void					parse_magic_header(t_vm *vm, t_gladiator *gldtor,
											u_int8_t *buffer);
void					parse_champ_name(t_vm *vm, t_gladiator *gldtor,
											u_int8_t *buffer);
void						parse_exec_code_size(t_vm *vm, t_gladiator *gldtor,
													u_int8_t *buffer);
void					parse_comment(t_vm *vm, t_gladiator *gldtor,
													u_int8_t *buffer);
void					parse_exec_code(t_vm *vm, t_gladiator *gldtor,
													u_int8_t *buffer);
int						ft_idx_mod(long n);
#endif
