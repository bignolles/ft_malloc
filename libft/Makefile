# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evignol <evignol@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/04 15:24:19 by evignol           #+#    #+#              #
#    Updated: 2016/02/19 11:24:02 by marene           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ft_memset.c			\
		ft_get_next_line.c	\
		ft_bzero.c			\
		ft_memcpy.c			\
		ft_memccpy.c		\
		ft_memmove.c		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_strlen.c			\
		ft_strdup.c			\
		ft_strcpy.c			\
		ft_strncpy.c		\
		ft_strcat.c			\
		ft_strncat.c		\
		ft_strlcat.c		\
		ft_strchr.c			\
		ft_strrchr.c		\
		ft_strstr.c			\
		ft_strnstr.c		\
		ft_strcmp.c			\
		ft_strncmp.c		\
		ft_atoi.c			\
		ft_isalpha.c		\
		ft_isdigit.c		\
		ft_isalnum.c		\
		ft_isascii.c		\
		ft_isprint.c		\
		ft_toupper.c		\
		ft_tolower.c		\
		ft_memalloc.c		\
		ft_memdel.c			\
		ft_strnew.c			\
		ft_strdel.c			\
		ft_strclr.c			\
		ft_striter.c		\
		ft_striteri.c		\
		ft_strmap.c			\
		ft_strmapi.c		\
		ft_strequ.c			\
		ft_strnequ.c		\
		ft_strsub.c			\
		ft_strjoin.c		\
		ft_strtrim.c		\
		ft_strsplit.c		\
		ft_itoa.c			\
		ft_putchar.c		\
		ft_putstr.c			\
		ft_putendl.c		\
		ft_putnbr.c			\
		ft_putunbr.c		\
		ft_putdbl.c			\
		ft_putchar_fd.c		\
		ft_putstr_fd.c		\
		ft_putendl_fd.c		\
		ft_putnbr_fd.c		\
		ft_lstnew.c			\
		ft_lstdelone.c		\
		ft_lstdel.c			\
		ft_lstadd.c			\
		ft_lstiter.c		\
		ft_realloc.c		\
		ft_putstr_color.c	\
		ft_pow.c			\
		ft_sqrt.c			\
		ft_atof.c			\
		ft_arccos.c			\
		ft_arcsin.c			\
		ft_arctan.c			\
		ft_cos.c			\
		ft_sin.c			\
		ft_lstmap.c			\
		ft_putnbr_long.c	\
		ft_puthex.c			\
		ft_fputhexa.c		\
		ft_ftostr.c			\
		ft_abs.c			\
		ft_freearr.c		\
		ft_fabs.c			\
		cbfree.c			\
		cbinit.c			\
		cbpopfront.c		\
		cbpushback.c		\
		ft_putaddr.c		\
		ft_putnbr_recursive.c\
		ft_putchar_hex.c\
		error.c

OBJ = $(SRC:.c=.o)

NAME = libft.a

.PHONY: all clean fclean re

all: $(NAME)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f libft.a

re: fclean all

$(NAME): $(OBJ)
	@ar rc libft.a $(OBJ)
	@ranlib libft.a
	@echo "\033[1;32mLibft done.\033[00m"

%.o: %.c
	@echo "\033[1;34mCompiling libft..\033[00m"
	@gcc $(SRC) -Wall -Werror -Wextra -g -I./includes/ -c $<
