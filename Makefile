ifeq ($(HOSTTYPE),)
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif
NAME =			libft_malloc_$(HOSTTYPE).so
LINKNAME =		libft_malloc.so
SRCS_DIR =		./srcs/
INCLUDES_DIR =	./includes/
OBJ_DIR =		./obj/
LIBFT_DIR =		./libft/
LIBFT_NAME =	libft.a
SRCS =			metadata.c
OBJ =			$(SRCS:.c=.o)
LIBFT =			$(LIBFT_DIR)libft.a
CC =			clang
CFLAGS =		-Wall -Wextra -Werror -I $(INCLUDES_DIR) -I $(LIBFT_DIR)includes -c -o
LDFLAGS =		-L $(LIBFT_DIR) -lft -shared -o

all: $(OBJ_DIR) $(LIBFT_NAME) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT_NAME):
	make -C $(LIBFT_DIR) all

$(NAME): $(addprefix $(OBJ_DIR), $(OBJ))
	@rm -f $(LINKNAME)
	$(CC) $(LDFLAGS) $@ $^
	@ln -s $(NAME) $(LINKNAME)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) $@ $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
