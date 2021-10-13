# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/29 20:11:29 by vkuklys           #+#    #+#              #
#    Updated: 2021/10/13 03:38:38 by vkuklys          ###   ########.fr        #
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
SRC= src/main.c src/helpers/printer.c src/builtins/echo.c src/parser/argv_utils.c src/helpers/free.c src/builtins/env.c \
		src/parser/validation.c src/parser/argc.c src/helpers/counter.c src/parser/argv.c src/builtins/exit.c \
		gnl/get_next_line.c src/init/init.c src/builtins/export.c src/builtins/unset.c src/parser/variables.c src/builtins/pwd.c \
		src/builtins/cd.c src/parser/validation_2.c src/builtins/history.c
INCLUDES=libft/libft.a

all:
	@echo "$(YELLOW)\n       -> Building $(NAME) ...$(RESET)"
	@make -C libft/ bonus -s
	@gcc $(FLAGS) $(SRC) $(INCLUDES) -o $(NAME)
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
