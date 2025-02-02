##
## EPITECH PROJECT, 2022
## lib
## File description:
## Makefile
##

MAKEFLAGS += -silent
CC = gcc

VPATH += src/
VPATH += src/env_function
VPATH += src/sys_function
VPATH += src/cd_built_in
VPATH += src/parsing_input
VPATH += src/exit_function
VPATH += src/list
VPATH += src/init
VPATH += src/destroy
VPATH += src/manage_file
VPATH += src/input
VPATH += src/input/prompt_function
VPATH += src/built_in
VPATH += src/history
VPATH += src/!
VPATH += src/bonus

SRC += main.c
SRC += mysh.c
SRC += array_to_linkedlist.c
SRC += function_env.c
SRC += exec_sys_function.c
SRC += verify_env.c
SRC += free_env.c
SRC += cd_built_in.c
SRC += parsing_input.c
SRC += get_redirection.c
SRC += parsing_pipe.c
SRC += exit_function.c
SRC += list_manager.c
SRC += left_redirection.c
SRC += manage_array.c
SRC += init_sh.c
SRC += get_local_variable.c
SRC += open_read_file.c
SRC += open_write_file.c
SRC += free_var.c
SRC += alias.c
SRC += manage_local_variable.c
SRC += my_getline.c
SRC += copy_array.c
SRC += manage_string.c
SRC += create_dico.c
SRC += manage_input.c
SRC += autocompletion.c
SRC += delete_with_globbing.c
SRC += separators.c
SRC += cut_separators.c
SRC += my_str_to_word_pipe.c
SRC += manage_exec.c
SRC += check_local_var.c
SRC += echo/echo.c
SRC += echo/spe_char/fiveth.c
SRC += echo/spe_char/tenth.c
SRC += which_where.c
SRC += set_status_variable.c
SRC += set_prompt.c
SRC += prompt_function.c
SRC += set_prompt_att.c
SRC += prompt_color.c
SRC += history_print.c
SRC += init_history.c
SRC += take_history.c
SRC += clear_history.c
SRC += free_history.c
SRC += base.c
SRC += manage_command.c
SRC += exception.c
SRC += load_history.c
SRC += save_history.c
SRC += get_name_file.c
SRC += move_in_history.c
SRC += check_path.c
SRC += bonus.c

CFLAGS = -I include/ -Wall -Wextra

LDFLAGS = -L lib/ -lmy -lprint -lncurses

BUILD_DIR = build/

NAME = 42sh

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS += -g
endif

$(BUILD_DIR)%.o: %.c
	@mkdir -p $(@D)
	#@echo "  CC       $<      $@"
	#@echo "$(notdir $(CURDIR)): C '$<'"
	@$(CC) $(CFLAGS) -c $< -o $@

OBJ = $(SRC:%.c=$(BUILD_DIR)%.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C lib/my/
	make -C lib/my_printf/
	@ echo "$(BLUE)Compilation of $(NAME)...$(NC)"
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	@ echo "$(GREEN)$(NAME) created$(NC)"

clean: tests_clean
	make clean -C lib/my/
	make clean -C lib/my_printf/
	@ echo "$(RED)lib clean"
	rm -rf $(BUILD_DIR)
	rm -f $(OBJ)
	rm -f *~
	rm -f \#*\#
	rm -f vgcore.*
	rm -f test
	@ echo "$(RED)clean successful !"

fclean: clean tests_clean
	make fclean -C lib/my/
	make fclean -C lib/my_printf/
	rm -f $(NAME)
	@ echo "$(RED)fclean successful !$(NC)"

#tests_run: CFLAGS += -lcriterion --coverage
tests_run:	$(OBJ)
	$(CC) -o test_units $(filter-out build/main.o, $(OBJ))\
 	tests/test_env.c -I include/ $(LDFLAGS) $(CFLAGS)
	-./test_units

tests_clean:
	@ rm -f *.gcno
	@ rm -f *.gcda
	@ rm -f test_units

my_test: $(OBJ)
	@rm my_test
	$(CC) $(filter-out build/main.o, $(OBJ)) test.c -o my_test $(LDFLAGS)
	@ echo "$(GREEN)test created$(NC)"


re: 	fclean all

.PHONY: all clean fclean re .SILENT

BLUE = \033[1;34m
RED = \033[1;31m
GREEN = \033[1;32m
NC = \033[0m
