# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julian <julian@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/29 20:11:29 by vkuklys           #+#    #+#              #
#    Updated: 2021/10/20 11:37:07 by julian           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- MakeFile -*-

# Color codes
RESET   = \033[0m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m

NAME=minishell
FLAGS=-Werror -Wextra -Wall
SRC= src/main.c src/process_cmd_line/process_cmd_line.c src/helpers/printer.c src/builtins/echo.c src/parser/argv_utils.c \
		src/helpers/free.c src/builtins/env.c src/parser/validation.c src/parser/argc.c src/helpers/counter.c src/parser/argv.c \
		src/builtins/exit.c	gnl/get_next_line.c src/init/init.c src/builtins/export.c src/builtins/unset.c src/parser/variables.c src/builtins/pwd.c \
		src/builtins/cd.c src/parser/validation_2.c src/builtins/history.c src/pipes/check_pipes.c src/pipes/ft_split_pipe.c \
		src/pipes/execute_compound_commands.c src/pipes/execute_single_command.c src/pipes/pipes_utils.c src/pipes/prepare_execution.c \
		src/builtins/handle_builtin_cmd.c src/redirections/heredoc.c src/redirections/output.c src/pipes/check_command.c \
		src/redirections/input.c src/redirections/append.c src/redirections/update_argv.c src/pipes/execute_cmd.c src/helpers/status.c \
		src/pipes/handle_fds.c
INCLUDES=libft/libft.a
LFLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline
CPFLAGS = -I$$HOME/.brew/opt/readline/include

all:
	@echo "$(YELLOW)\n       -> Building $(NAME) ...$(RESET)"
	@make -C libft/ bonus -s
	@gcc $(FLAGS) $(LFLAGS) $(CPFLAGS) $(SRC) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"

clean:
	@echo "$(BLUE)***   Deleting all objects from $(NAME)   ...   ***$(RESET)"
	@make -C libft/ clean -s

fclean: clean
	@echo "$(BLUE)***   Deleting executable file from $(NAME)   ...   ***$(RESET)"
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean -s

re: fclean all

PHONY: all clean fclean re
