# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jludt <jludt@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/29 20:11:29 by vkuklys           #+#    #+#              #
#    Updated: 2021/10/12 10:08:33 by jludt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- MakeFile -*-

# Color codes
RESET   = \033[0m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
LFLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline
CPFLAGS = -I$$HOME/.brew/opt/readline/include

SRC=	src/main.c								\
		gnl/get_next_line.c						\
		src/builtins/echo.c						\
		src/builtins/env.c						\
		src/builtins/exit.c						\
		src/builtins/pwd.c						\
		src/helpers/counter.c					\
		src/helpers/free.c						\
		src/helpers/printer.c					\
		src/parser/argc.c						\
		src/parser/argv_utils.c					\
		src/parser/argv.c						\
		src/parser/validation.c					\
		src/pipes/check_pipes.c					\
		src/pipes/execute_compound_commands.c	\
		src/pipes/execute_single_command.c		\
		src/pipes/ft_split_pipe.c				\
		src/pipes/pipes_utils.c					\
		src/pipes/pipes_utils2.c				\
		src/pipes/trim_pipes.c					

OBJECTS = ./*.o
NAME_LIB = libft.a

#build everything
all: $(NAME)

#compile all files
$(NAME): LIB $(OBJECTS)
	@echo "$(YELLOW)\n       -> Building $(NAME) ...$(RESET)"
	@$(CC) $(LFLAGS) $(OBJECTS) $(NAME_LIB) -o $(NAME)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"
	@$(RM) $(OBJECTS)
	@$(RM) ./libft/$(OBJECTS)

$(OBJECTS):
	@$(CC) -c $(CFLAGS) $(CPFLAGS) $(SRC)

LIB:
	@make -C ./libft
	@cp ./libft/libft.a $(NAME_LIB)
	@rm ./libft/libft.a

#removes all *.o files
clean:
	@echo "$(BLUE)***   Deleting all objects from $(NAME)   ...   ***$(RESET)"	
	@$(RM) $(OBJECTS)
	@$(RM) ./libft/$(OBJECTS)

#removes all *.o files + executable
fclean: clean
	@echo "$(BLUE)***   Deleting executable file from $(NAME)   ...   ***$(RESET)"
	@$(RM) $(NAME) $(NAME_LIB)

#removes all *.o files + executable and rebuild everything
re: fclean all

PHONY: all clean fclean re
