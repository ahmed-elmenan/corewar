ASM_NAME = asm
VM_NAME = corewar

PRINTF_FILE = libftprintf.a
PRINTF_DIR = ./ft_printf

ASSEMBLY_DIR = ./src/assembly
VM_DIR = ./src/vm

INC_DIR = ./includes/

PRINTF_INC = $(PRINTF_DIR)/

ASM_OBJ_DIR = ./asm_obj
VM_OBJ_DIR = ./vm_obj

PRINTF = $(PRINTF_DIR)/$(PRINTF_FILE)

ASM_HEADERS = $(INC_DIR)asm_inc/corewar.h $(INC_DIR)op.h 
VM_HEADERS = $(INC_DIR)vm_inc/cor.h $(INC_DIR)op.h

ASSEMBLY_FILES = analyze_line.c argument_errors.c check_line.c commands_errors.c create_file.c free_2d.c ft_binary_search.c get_arguments_info.c get_info.c get_operation_info.c header_errors_checker.c header_parsing.c label_parsing.c liberate_memory.c main.c numbers_errors.c op.c op_and_label_checker.c operation_parsing.c organize_beginning_data.c tokenize_data.c translate_data_to_code.c utils.c write_bytecode.c
VM_FILES = cursor_related.c free_nd_exit.c let_the_game_begin.c little_to_big_endian.c main.c memory.c op.c operations.c parse_operation.c parsing_related.c parsing_related_2.c player_related.c tools_related.c vm_related.c

OBJ_ASSEMBLY = $(addprefix $(ASM_OBJ_DIR)/, $(ASSEMBLY_FILES:%.c=%.o))
OBJ_VM = $(addprefix $(VM_OBJ_DIR)/, $(VM_FILES:%.c=%.o))

CC = gcc
CFLAGS = -Wall -Werror -Wextra 

ASM_INC = -I $(INC_DIR)asm_inc/corewar.h  -I $(INC_DIR)op.h  -I $(PRINTF_INC)
VM_INC  = -I $(INC_DIR)vm_inc/cor.h -I $(INC_DIR)op.h  -I $(PRINTF_INC)

all: lib $(VM_NAME) $(ASM_NAME) 

$(VM_OBJ_DIR)/%.o: $(VM_DIR)/%.c $(VM_HEADERS)
	@$(CC) $(CFLAGS) -c $(VM_INC) $< -o $@

$(ASM_OBJ_DIR)/%.o: $(ASSEMBLY_DIR)/%.c $(ASM_HEADERS)
	@$(CC) $(CFLAGS) -c $(ASM_INC) $< -o $@

$(ASM_OBJ_DIR):
	@mkdir $(ASM_OBJ_DIR)

$(VM_OBJ_DIR):
	@mkdir $(VM_OBJ_DIR)

$(ASM_NAME): $(ASM_OBJ_DIR) $(OBJ_ASSEMBLY)
	@$(CC) $(OBJ_ASSEMBLY) $(PRINTF) -o $(ASM_NAME)
	@echo "\033[1;34m--> asm files were created\033[1;34m"

$(VM_NAME): $(VM_OBJ_DIR) $(OBJ_VM)
	@$(CC) $(OBJ_VM) $(PRINTF) -o $(VM_NAME)
	@echo "\033[1;34m--> vm files were created\033[1;34m"

lib:
	@make -C $(PRINTF_DIR)

clean:
	@rm -rf $(ASM_OBJ_DIR)
	@rm -rf $(VM_OBJ_DIR)
	@make -C $(PRINTF_DIR) clean
	@echo "\033[1;34m--x asm object files were deleted\033[1;34m"
	@echo "\033[1;34m--x vm object files were deleted\033[1;34m"

fclean: clean
	@rm -rf $(ASM_NAME)
	@rm -rf $(VM_NAME)
	@make -C $(PRINTF_DIR) fclean
	@echo "\033[1;34m--x asm files were deleted\033[1;34m"
	@echo "\033[1;34m--x vm files were deleted\033[1;34m"

re: fclean all