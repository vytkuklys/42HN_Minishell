# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jludt <jludt@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/11 12:13:12 by jludt             #+#    #+#              #
#    Updated: 2021/11/04 13:11:44 by jludt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME = minishell

# Color codes

RESET	= \033[0m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m

# Compiling flags
FLAGS = -Wall -Wextra -Werror
LFLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline
CPFLAGS = -I$$HOME/.brew/opt/readline/include

# Folders
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/

# Source files and object files
SRC_FILES = main.c process_cmd_line/process_cmd_line.c helpers/printer.c builtins/echo.c parser/argv_utils.c \
		helpers/free.c builtins/env.c parser/validation.c parser/argc.c helpers/counter.c parser/argv.c \
		builtins/exit.c init/init.c builtins/export.c builtins/unset.c parser/variables.c builtins/pwd.c \
		builtins/cd.c parser/validation_2.c pipes/check_pipes.c pipes/ft_split_pipe.c \
		pipes/execute_compound_commands.c pipes/execute_single_command.c pipes/pipes_utils.c \
		builtins/handle_builtin_cmd.c pipes/check_command.c redirections/check_redirections.c \
		redirections/update_argv.c pipes/execute_cmd.c helpers/status.c \
		pipes/handle_fds.c builtins/export_helper.c parser/variables_utils.c helpers/signals.c parser/update_argv.c \
		parser/update_argv_utils.c parser/update_argv_utils2.c redirections/handle_heredoc.c redirections/handle_redirections.c \
		parser/argv_utils2.c
OBJ_FILES = $(SRC_FILES:.c=.o)

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

# Libft linkers
LNK  = -L $(LIBFT_DIR) -lft 

# all rule
all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)builtins
	@mkdir -p $(OBJ_DIR)helpers
	@mkdir -p $(OBJ_DIR)init
	@mkdir -p $(OBJ_DIR)parser
	@mkdir -p $(OBJ_DIR)pipes
	@mkdir -p $(OBJ_DIR)process_cmd_line
	@mkdir -p $(OBJ_DIR)redirections
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc $(FLAGS) $(CPFLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Compiling
$(NAME): $(OBJ)
	@echo "$(YELLOW)\n      -> Building $(NAME) ...$(RESET)"
	@gcc $(OBJ) $(LFLAGS) $(LNK) -lm -o $(NAME)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"

# clean rule
clean:
	@echo "$(BLUE)***   Deleting all objects from $(NAME)   ...   ***$(RESET)"
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo

# fclean rule
fclean: clean
	@echo "$(BLUE)***   Deleting executable file from $(NAME)   ...   ***$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo

# re rule
re: fclean all

# phony
.PHONY: all clean fclean re