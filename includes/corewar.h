/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-bou <anel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:26:57 by anel-bou          #+#    #+#             */
/*   Updated: 2021/03/06 16:01:52 by anel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
#define COREWAR_H

#include "../libft/libft.h"
#include "op.h"
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
/***********************/
#include <stdio.h>

#define IS_SPACE(X) (X == ' ' || X == '\t')
#define IS_COMMENT_CHAR(X) (X == ALT_COMMENT_CHAR || X == COMMENT_CHAR)
#define BGN_DATA (4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4)
/* HEADER + NAME + NULL + EXEC_SZ + COMMENT + NULL */

typedef enum e_boolean
{
	FALSE,
	TRUE,
} t_boolean;

typedef struct s_op
{
	char *op_name;
	int arg_len;
	int arg[3];
	int op_code;
	int cycles_to_wait;
	char *description;
	int codage_octect;
	int size_t_dir;
} t_op;

extern t_op op_tab[17];

typedef struct s_data
{
	int current_octets;
	char *line;
	struct s_data *next;
} t_data;

typedef struct s_label
{
	char *label_name;
	int label_position;
	struct s_label *next;
} t_label;

typedef struct s_opr
{
	char *line;
	char opr_code;
	unsigned char enc_octet;

	unsigned int arg1;
	unsigned int arg2;
	unsigned int arg3;

	int opr_size;
	struct s_opr *next;

} t_opr;

typedef struct s_env
{
	header_t hdr;
	t_data *data;
	t_data *dt;
	t_label *label;
	t_label *lbl;
	t_opr *opr;
	char *bgn_data;
	char *champion;
	int src_file;
	int dst_file;
	int current_size;
	int i;
	int sup;
	// checking vars
	int			check_name;
	int			check_comment;
	int			label_already_checked;
	int			line_counter;
	int			line_counter_tmp;
	t_op		*found_op;
	char		*save_op;
	char		*sub_op;
	char		*joinned_str;
	int			quotes_index;
	char		*trimed_line;
	// checking vars
} t_env;

int get_operation_code(char *line);
int get_operation_len(char *line);
int get_first_char_index(char *str);
int get_current_argument_code(char *line);
int get_operation_size(char *line);
int get_all_arguments_size(char *line, int opr);
int get_this_arg_size(char *line, int i, int op);
int get_t_dir_size(int op);
int char_index(char *str, char c);

int is_operation(char *line);
int is_empty_line(char *line);
int is_label(char *str);
int is_arg_first_char(char *line, int i);
int is_input_correct(char *s);
int is_args_octet_present(int op);
int is_label_operation_in_same_line(char *line);
int ft_empty_or_comment_line(char *str);
int create_file(char *s, t_env *env);
int check_line(char *trimed_line, char *regular_line);
int check_name_comment_flag(t_env *env);
int calculate_comment_index(char *str);
int verify_label_chars(t_env *env, char *label);
int is_label_operation_in_same_line(char *line);
int ft_binary_search(char *tab, char c);
int ft_binary_search_2d(t_env *env, char *operation, t_op tab[16]);
int arr_len_2d(char **str);
int ft_is_string_number(char *str);
int char_index(char *str, char c);
int skip_white_spaces_and_arg_chars(char *str);
int ft_empty_or_comment_line(char *str);
int check_command(char *trimed_line);
int check_line(char *trimed_line, char *regular_line);
int calculate_comment_index(char *str);

t_boolean ft_atoll(const char *str);

void check_args_type(t_env *env, char **args);
void operation_parsing(t_env *env, int *is_op, char *op, int i);
void save_label_position(char *line, int current_bytes, t_env *env);
void label_parsing(t_env *env, char *str, char *tmp);
void verify_single_label_in_line(t_env *env, char *trimed_line, int char_pos);
void check_error_command(t_env *env, char *trimed_line, char *line);
void free_pointers(char *trimed_line, char *line);
void error_passing_indirect(t_env *env, char *str);
void error_reg_value_is_negative(t_env *env);
void error_reg_value_not_digit(t_env *env);
void error_value_contains_positive_sign(t_env *env, char *arg_type);
void error_overflow_or_underflow_int(t_env *env, char *arg_type);
void handle_int_errors(t_env *env, char *arg, char *arg_type);
void error_passing_direct(t_env *env, char c);
void error_passing_registry(t_env *env, char c);
void error_big_reg_value(t_env *env);
void handle_number_error(t_env *env, char *arg, char *arg_type);
void ft_check_args_len(t_env *env, int len);
void check_argument_value(t_env *env, char *trimed_str);
void check_passing_wrong_arg(t_env *env, char *trimed_str, int i);
void organize_beginning_data(t_env *env);
void tokenize_data(t_env *env);
void translate_data_to_code(t_env *env);
void write_beginning_data(t_env *env);
void write_bytecode_in_file(t_env *env);
void ft_command_not_found(char *trimed_line,
						  char *regular_line, t_env *env);
void check_if_operation_or_label(char *op, t_env *env);
void free_2d(char **array, int len);
void free_pointers(char *trimed_line, char *line);
void check_name_and_comment_existence(int checker, char *item);
void check_string_length(t_env *env, int item_len, int max_len,
						 char *item);
void check_missing_last_quotes_error(t_env *env, char *item,
									 int quotes_index);
void check_characters_after_last_quotes(t_env *env, char *str,
										char *item, int line_counter);
void ft_error_found_before_item(char **str, char **line,
								t_env *env, char *item);
void content_not_found_error(char *item, t_env *env);
void ft_command_not_found(char *trimed_line, char *regular_line,
						  t_env *env);
void extract_multiline_string(t_env *env, int item_length,
							  char (*item_container)[item_length], char *item);
void extract_signleline_string(t_env *env,
							   int item_length,
							   char (*item_container)[item_length],
							   char *item);
void is_not_name_or_comment(t_env *env, char *trimed_line,
							char *regular_line);
void store_string_item(t_env *env, char *item, int item_length,
					   char (*item_container)[item_length]);
void ft_header_operations(t_env *env, char *regular_line);
void set_champ_info(t_env *env, int item_length,
					char (*item_container)[item_length], char *item);
unsigned char set_args_octet(char *line);
char **ft_split_whitespaces(char *str);

void	liberate_memory(t_env *env);


#endif