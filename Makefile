NAME = asm
PRINTF_FILE = libftprintf.a

PRINTF_DIR = ./ft_printf
ASSEMBLY_DIR = ./src/assembly
INC_DIR = ./includes/
PRINTF_INC = $(PRINTF_DIR)/
OBJ_DIR = ./obj

LFLAG = 

PRINTF = $(PRINTF_DIR)/$(PRINTF_FILE)

HEADERS = $(INC_DIR)corewar.h $(INC_DIR)op.h 

ASSEMBLY_FILES = main.c utils.c check_line.c label_parsing.c operation_parsing.c header_parsing.c header_errors_checker.c commands_errors.c argument_errors.c numbers_errors.c op_and_label_checker.c ft_binary_search.c op.c organize_beginning_data.c tokenize_data.c translate_data_to_code.c analyze_line.c free_2d.c get_operation_info.c get_arguments_info.c create_file.c write_bytecode.c liberate_memory.c get_info.c

OBJ_ASSEMBLY = $(addprefix $(OBJ_DIR)/, $(ASSEMBLY_FILES:%.c=%.o))

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra 
INC = -I $(INC_DIR) -I $(PRINTF_INC)

all: $(NAME)

$(OBJ_DIR)/%.o: $(ASSEMBLY_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJ_ASSEMBLY)
	@make -C $(PRINTF_DIR)
	@$(CC) $(OBJ_ASSEMBLY) $(PRINTF) $(LFLAG) -o $(NAME)
	@echo "\033[1;34m--> asm files were created\033[1;34m"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(PRINTF_DIR) clean
	@echo "\033[1;34m--x asm object files were deleted\033[1;34m"

fclean: clean
	@rm -rf $(NAME)
	@make -C $(PRINTF_DIR) fclean
	@echo "\033[1;34m--x asm files were deleted\033[1;34m"

re: fclean all