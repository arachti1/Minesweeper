#include ~/bash_colors.sh
NAME=Minesweeper
CC=gcc
CFLAGS=-Wall -Wextra -Werror
# OFLAGS=-g3 -fsanitize=address
SRC=Minesweeper.c
OBJ=$(SRC:.c=.o)
INC=Minesweeper.h
LIB=libft/libft.a
LFLAGS=-L libft
GRPH_INCFLAGS = -I/usr/local/include -I libft
GRPH_LIBFLAGS = -L/usr/local/lib -lX11 -lm

all: $(NAME)

$(NAME): $(SRC) $(INC) $(LIB) Makefile
	@$(CC) -o $(NAME) $(SRC) $(LIB) $(LFLAGS) $(GRPH_INCFLAGS) $(GRPH_LIBFLAGS)
	@echo "${_BOLD}${_GREEN}$(NAME) made"

$(LIB):
	@make -sC Libft
clean:
	@make -sC Libft clean
	@echo "${_BOLD}${_RED}$(NAME) clean"

fclean:
	@rm -rf $(NAME)
	@make -sC Libft fclean
	@echo "${_BOLD}${_UNDER}${_RED}$(NAME) full clean"

re: fclean all

.PHONY: clean fclean re