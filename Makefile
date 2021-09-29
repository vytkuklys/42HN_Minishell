# -*- MakeFile -*-

NAME=minishell
FLAGS=-Werror -Wextra -Wall
SRC= src/main.c src/helpers/printer.c
INCLUDES=libft/libft.a

all: $(NAME_SERVER) $(NAME_CLIENT)
	@make -C libft/ bonus
	gcc $(FLAGS) $(SRC) $(INCLUDES) -o $(NAME)

clean:
	@make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all