/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:26:57 by anel-bou          #+#    #+#             */
/*   Updated: 2021/02/11 15:41:09 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef COREWAR_H
#define COREWAR_H

#include "../libft/libft.h"
#include "op.h"
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
/***********************/
#include <stdio.h>

#define IS_SPACE(X) (X == ' ' || X == '\t')
#define	IS_COMMENT_CHAR(X) (X == ALT_COMMENT_CHAR || X == COMMENT_CHAR)
#define	BGN_DATA (4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4)
/* HEADER + NAME + NULL + EXEC_SZ + COMMENT + NULL */
typedef struct s_op{
	char *op_name;
	int arg_len;
	int arg[3];
	int op_code;
	int cycles_to_wait;
	char *description;
	int codage_octect;
	int size_t_dir;
}				t_op; 

extern t_op    op_tab[17];

typedef struct	s_data
{
	int				current_octets;
	char			*line;
	struct s_data	*next;
}				t_data;

typedef struct s_label
{
	char			*label_name;
	int				label_position;
	struct s_label	*next;
}				t_label;

typedef struct		s_opr
{
	char	*line;
	char	opr_code;
	unsigned char	enc_octet;

	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;
	
	int		opr_size;
	struct s_opr	*next;

}				t_opr;

typedef struct	s_env
{
	header_t	hdr;
	t_data		*data;
	t_data		*dt;
	t_label		*label;
	t_label		*lbl;
	t_opr		*opr;
	char		*bgn_data;
	char		*champion;
	int			src_file;
	int			dst_file;
	int			current_size;
	int			i;

	int			sup;
	// checking vars
	int check_name;
	int check_comment;
	
	// checking vars
}				t_env;


int		get_operation_code(char *line);
int		get_operation_len(char *line);
int		get_first_char_index(char *str);
int		get_current_argument_code(char *line);
int		get_operation_size(char *line);
int		get_all_arguments_size(char *line, int opr);
int		get_this_arg_size(char *line, int i, int op);
int		get_t_dir_size(int op);
int		char_index(char *str, char c);

int		is_operation(char *line);
int		is_empty_line(char *line);
int		is_label(char *str);
int		is_arg_first_char(char *line, int i);
int     is_input_correct(char *s);
int		is_args_octet_present(int op);
int		is_label_operation_in_same_line(char *line);

unsigned char	set_args_octet(char *line);
int		create_file(char *s, t_env *env);
void    organize_beginning_data(t_env *env);
void	tokenize_data(t_env *env);
void	translate_data_to_code(t_env *env);
void	write_beginning_data(t_env *env);
void	write_bytecode_in_file(t_env *env);
void	ft_command_not_found(char *trimed_line);
void	check_if_operation(char *op);

char	**ft_split_whitespaces(char *str);


#endif  