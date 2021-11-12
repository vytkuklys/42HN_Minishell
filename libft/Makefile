# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/14 12:26:14 by vkuklys           #+#    #+#              #
#    Updated: 2021/10/28 19:01:02 by vkuklys          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = ft_isalpha.c ft_isdigit.c ft_isascii.c ft_isprint.c ft_memset.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
ft_bzero.c ft_calloc.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_strdup.c \
ft_toupper.c ft_tolower.c ft_atoi.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_isalnum.c ft_puthexa_fd.c ft_pow.c ft_put_unsigned_int_fd.c \
ft_get_digit_count.c ft_get_min.c ft_free_2d_array.c ft_2d_strlen.c ft_strrstr.c ft_triple_strjoin.c ft_strcmp.c ft_strjoin2.c \
ft_strjoin_status.c ft_strtrim_free.c ft_substr_free.c get_next_line.c get_int_sum.c

OFILES = $(CFILES:.c=.o)

BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
ft_lstsize.c ft_lstprint.c

BONUSOFILES = $(BONUS:.c=.o)

all: libft.a

libft.a: $(CFILES) libft.h
	@gcc -Wall -Wextra -Werror -c $(CFILES)
	@ar -crs libft.a $(OFILES)

clean:
	@rm -f *.o

fclean: clean
	@rm -f *.a

re: fclean all

bonus: ${OFILES} $(BONUSOFILES)
	ar -crs libft.a ${OFILES} $(BONUSOFILES)

.PHONY: all clean fclean re bonus
