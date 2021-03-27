NAME	= libftprintf.a
CC		= gcc
CFLAGS	= -Werror -Wextra -Wall
SRCS	= ft_convert.c \
		  ft_intlen2.c \
          ft_itoa2.c   \
          ft_itoa_u.c  \
		  ft_memseti.c \
		  ft_printf.c  \
		  ft_putstri.c \
		  ft_stock_format.c \
		  ft_strnstr2.c \
		  ft_struct_initializer.c \
		  ft_printf_process.c \
		  ft_detect_options.c \
		  ft_handle_precision.c \
		  ft_handle_no_precision.c \
		  ft_detect_conditions.c \
		  ft_detect_conditions2.c \
		  ft_make_data_type.c \
		  ft_length_detected.c \
		  ft_confirm_options.c \
		  ft_stock_options.c \
		  ft_handle_errors.c \
		  ft_infinit_add.c \
		  ft_infinit_multiplication.c \
		  ft_infinit_power.c \
		  ft_float.c \
		  ft_calculate_mantissa.c \
		  ft_float_addition.c \
		  ft_save_deciaml_point_index.c \
		  ft_handle_float_nb.c \
		  ft_float_process.c \
		  ft_handle_mantissa.c \
		  ft_build_float.c \
		  ft_modifier_condition.c \
		  ft_store_add.c \
		  ft_mlp_func.c \
		  ft_add_func_extension.c \
		  ft_check_pr.c 

OBJECT	=	$(SRCS:.c=.o)

LFT		=	libft/libft.a

HEADERS = ft_printf.h

all : lib $(NAME)

$(OBJECT): %.o: %.c $(HEADERS)
	@$(CC) -g -c $(CFLAGS) -o $@ $<

lib:
	@make -C libft

$(NAME) : $(OBJECT) $(LFT)
	@cp $(LFT) .
	@mv libft.a $(NAME)
	@ar rc $(NAME) $(OBJECT)
	@ranlib $(NAME)
	@echo "\033[0;32m--> ft_printf files were created\033[0m"

clean :
	@make clean -C libft 
	@rm -rf $(OBJECT)
	@echo "\033[0;31m--x ft_printf object files were deleted\033[0m"

fclean : clean
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "\033[0;31m--x ft_printf files were deleted\033[0m"

re : fclean all
