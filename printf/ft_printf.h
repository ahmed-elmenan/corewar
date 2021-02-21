/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:44:23 by ahel-men          #+#    #+#             */
/*   Updated: 2020/02/07 16:52:51 by ahel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include "libft/libft.h"
# include <float.h>

# define F_PLUS		1
# define F_MINUS	2
# define F_ZERO		4
# define F_NUMBER	8
# define F_HASH		16

# define LEN_H		1
# define LEN_HH		2
# define LEN_L		4
# define LEN_LL		8
# define LEN_LF		16
# define LEN_Z		32
# define LEN_J		64

typedef struct			s_list2
{
	char				cnv;
	int					flag;
	long long			width;
	int					is_nb;
	int					precision;
	int					clean;
	int					hex_sign;
	int					sign;
	struct s_list2		*next;

}						t_list2;

typedef struct			s_data
{
	char				res;
	char				cnv;
	char				*str;
	char				*p;
	va_list				args;
	unsigned long long	u;
	long long			d;
	int					count;
	int					print_count;
	int					length;
	int					ast_p;
	int					ast_w;
	int					ret;
	int					pass;
	int					check;
	int					space_d;
	int					inf;
	int					minus;
	int					none;
	int					len;
	int					i;
	int					j;
	int					y;
	int					is_cnv;
	long double			f;
}						t_data;

typedef struct			s_list3
{
	char				nb;
	struct s_list3		*next;

}						t_list3;

typedef struct			s_add
{
	int					carry;
	int					res;
	int					count;
	char				*str;
	char				*str1;
	char				*str2;
	int					nb1;
	int					nb2;
}						t_add;

typedef struct			s_mlp
{
	int					carry;
	int					product;
	int					sum;
	char				*result;
	int					j;
	int					i;
	int					curr_postion;
	int					len;
	int					count;
	int					len2;
	char				*tmp;
}						t_mlp;

typedef struct			s_ieee
{
	unsigned long		mantissa:63;
	unsigned int		int_part:1;
	unsigned int		exponent:15;
	unsigned int		sign:1;
}						t_ieee;

typedef	union			u_float
{
	long double			nb;
	t_ieee				ieee;
}						t_float;

typedef struct			s_calc
{
	int					bias;
	int					neg_sign;
	int					index;
	int					len;
	int					fract_part_len;
	char				*mantissa;
	char				*norm;
	char				*exp_power;
	char				*tmp;
	char				*res;
	char				*integer;
	int					p_pos;
}						t_calc;

t_list2					*ft_list_allocate(t_list2 **tmp,
							t_list2 **head, int *j);
void					ft_putstri(char *str, int i);
void					*ft_memseti(void *b, int c, size_t len, size_t i);
void					ft_detect_length_s(t_data *data);
void					ft_detect_length_u(t_data *data);
void					ft_decimal_to_binary(int n);
void					ft_print_list(t_list3 *list);
void					ft_capitalize(char *str);
void					ft_data_initializer(t_data *data);
void					ft_list_initializer(t_list2 *tmp, t_data *data);
void					ft_conversion_builder(t_list2 *tmp, t_data *data);
void					ft_detect_asterisk(t_list2 *tmp, t_data *data);
void					ft_print_no_type(const char *format, t_data *data);
void					ft_printf_process(t_list2 *tmp, t_data *data);
void					ft_param(t_list2 *tmp, t_data *data);
void					ft_detect_precision(t_list2 **list, char **tab,
							char *str, t_data *data);
void					ft_detect_plus(t_list2 **list, char *tab,
							char *str, t_data *data);
void					ft_detect_space_d(t_list2 **list,
							char *str, t_data *data);
void					ft_detect_hash(t_list2 **list, char *str,
							t_data *data, int x);
void					ft_detect_minus(t_list2 **list, char *tab,
							char *str, t_data *data);
void					ft_detect_width(t_list2 **list, char *tab,
							char *str, t_data *data);
void					ft_detect_negative_nb(t_list2 **list, char *tab,
							char *str, t_data *data);
void					ft_print_string(t_list2 **list,
							char *tab, t_data *data);
void					ft_ignore_sign(t_list2 **list, char *str,
							t_data *data, char **tab);
int						ft_strnstr2(const char *haystack, const char *needle,
							size_t len, int i);
char					*ft_convert(unsigned long long n, int s, int m);
char					*ft_detect_format(const char *format, int count,
							va_list lst, char ft);
char					*ft_handle_s_precision(t_list2 **list,
							char *str, t_data *data);
char					*ft_handle_zero_null_precision(t_list2 **list,
							t_data *data);
char					*ft_handle_nb_null_precision(t_list2 **list, char *str,
							t_data *data, char *str2);
char					*ft_handle_less_precision(t_list2 **list,
							t_data *data, char *p);
char					*ft_handle_greather_precision(t_list2 **list,
							t_data *data, char *p, char *str2);
char					*ft_handle_no_precision(t_list2 **list, char *str,
							t_data *data, char *p);
char					*ft_add_hexa_prefix(t_list2 **list,
							t_data *data, char *tab);
char					*ft_handle_null_precision(t_list2 **list, char *str,
							t_data *data, char *str2);
char					*ft_make_precision(t_list2 **list,
							char *str, t_data *data);
char					*ft_itoa_u(unsigned long long nb);
char					*ft_itoa2(long long n);
int						ft_make_str(t_list2 **list, char *str, t_data *data);
int						ft_make_hexa(t_list2 **list, t_data *data);
int						ft_make_number(t_list2 **list, t_data *data);
int						ft_hash_hexa_condition(t_list2 **list,
							t_data *data, char *tab);
int						ft_plus_flag_condition(t_list2 **list,
							char *str, char *tab);
int						ft_negative_nb_condition(t_list2 **list, char *str,
							t_data *data, char *tab);
int						ft_octal_sign_condition(t_list2 **list,
							char *str, t_data *data);
int						ft_plus_in_width_condition(t_list2 **list, char *str,
							t_data *data, char *tab);
int						ft_negative_sign_after_width(t_list2 **list,
							char *str, t_data *data);
int						ft_ng_sign_condition(t_list2 **list, char *str,
							t_data *data, char *tab);
int						ft_minus_flag_with_negative_nb_condition(t_list2 **list,
							char *str);
int						ft_stock_format(const char *format, t_list2 **list,
							int *i, t_data *data);
int						ft_error_cnv(const char *format, int i, t_data *data);
int						ft_zero_flag_condition(t_list2 **list);
int						ft_printf(const char *format, ...);
int						ft_listlen(t_list2 *list);
void					ft_listdel2(t_list2 **alst);
int						ft_intlen2(long long n);
int						ft_detect_conv(char c);
int						ft_power(int x, int p);
int						ft_short_short_length_detected(t_data *data, int *i);
int						ft_short_length_detected(t_data *data, int *i);
int						ft_long_long_length_detected(t_data *data, int *i);
int						ft_long_length_detected(t_data *data, int *i);
int						ft_check_pr(t_list2 **list, t_data *data);
int						ft_double_length_detected(t_data *data, int *i);
int						ft_size_t_detected(t_data *data, int *i);
int						ft_int_max_detected(t_data *data, int *i);
int						ft_size_t_length_detected(t_data *data, int *i);
int						ft_ignore_space(t_data *data, int *i);
char					ft_check_cnv(const char *format, int i, t_data *data);
void					ft_detect_modifier(char const *format, int *i,
							t_data *data);
void					ft_check_space_d(t_data *data, int *i);
int						ft_flag_search(char const *format,
							t_list2 **list, int *i);
void					ft_struct_init(t_list2 **list, t_data *data);
int						ft_get_length(const char *format, int i);
int						ft_define_precision(char const *format, t_list2 **list,
							int *i, t_data *data);
int						ft_place_index(int *i, t_data *data);
int						ft_define_width(char const *format,
							t_list2 **list, int *i);
int						detect_options(char c);
int						ft_detect_conv_pr(char c);
int						ft_detect_conv(char c);
char					*ft_adjust_numbers(char *tmp, char *arr);
char					*store_number_in_array(t_list3 *list, t_add *add);
char					*ft_make_addition(char *s1, char *s2);
void					ft_listdel(t_list3 **alst);
int						ft_list_len(t_list3 *list);
char					*ft_make_mulitiplication(char *num1,
							char *num2, int flag);
char					*ft_make_infinit_power(char *nb, int p, int flag);
int						ft_make_power(int nb, int p);
void					ft_detect_length_f(t_data *data);
int						ft_make_float(t_list2 **list, t_data *data);
char					*ft_build_float(t_list2 **list, t_data *data);
char					*ft_calculate_mantissa(unsigned long mantissa);
char					*ft_negative_power(int power, int flag);
char					*ft_float_addition(char *f1, char *f2);
int						ft_save_deciaml_point_index(char *str);
char					*ft_remove_decimal_point(char *str);
char					*ft_add_decimal_point(t_list2 **list,
							char *norm, int index);
int						ft_detect_decimal_point(char *str);
char					*ft_handle_nan(t_data *data);
void					ft_handle_foat_hash_flag(t_calc *calc);
void					ft_handle_foat_zero(t_calc *calc);
void					ft_handle_foat_nb(t_float flt, t_calc *calc);
void					ft_calc_mantissa(t_calc *calc, t_float flt);
void					ft_calculate_exponent(t_calc *calc);
void					ft_handle_decimal_point(t_calc *calc);
void					ft_build_number(t_calc *calc);
void					ft_handle_decimal_point(t_calc *calc);
char					*ft_build_string(char *res,
							int fract_part_len, long pr);
char					*ft_build_precision(char *res, int index,
							long pr, int fract_part_len);
int						ft_is_not_zero(char *norm, int len);
void					ft_build_rounding(t_calc *calc);
void					ft_calculate_exponent(t_calc *calc);
void					ft_handle_negative_sign(t_calc *calc);
void					ft_handle_precision_zero(t_calc *calc);
void					ft_build_number(t_calc *calc);
void					ft_calc_mantissa(t_calc *calc, t_float flt);
void					ft_struct_data_init(t_float flt, t_calc *calc, int pr);
char					*ft_build_float(t_list2 **list, t_data *data);
int						ft_hash_condition(t_list2 **list, t_data *data);
void					ft_make_rounding(t_calc *calc);
void					ft_make_point(t_list2 **list, t_calc *calc);
char					*ft_verify_nb(t_float flt,
							t_data *data, t_list2 **list);
int						ft_is_j_modifier(char const *format,
							int *i, t_data *data);
int						ft_is_z_modifier(char const *format,
							int *i, t_data *data);
int						ft_is_h_modifier(char const *format,
							int *i, t_data *data);
void					ft_make_operation2(char *man, t_add *add);
void					ft_handle_add(t_add	*add, char *man);
void					ft_store_nb(t_add	*add);
void					ft_store_string(t_add	*add, char *f1, char *f2);
char					*ft_man_allocate(t_add	*add);
void					ft_handle_special_cases(t_mlp	*mlp, char *num1,
						char *num2, int flag);
void					ft_find_curr_pos(char *num1, t_mlp	*mlp);
void					ft_struct_init3(char *num1, char *num2, t_mlp *mlp);
char					*ft_allocate_tab(int len);
int						ft_ignore_left_zero(char *str);
char					*ft_adjust_numbers1(char *tmp, char *arr);
int						ft_list_len(t_list3 *list);
void					ft_listdel(t_list3 **alst);

#endif
