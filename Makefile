#include ~/bash_colors.sh
NAME=Minesweeper
CC=gcc
CFLAGS=-Wall -Wextra -Werror
# OFLAGS=-g3 -fsanitize=address
SRC:=$(wildcard src/**.c)
OBJ=$(SRC:.c=.o)
INCS= $(wildcard src/**.h)
LIB=Libft/libft.a
LFLAGS=-L Libft -I Libft/inc
GRPH_INCFLAGS = -I /usr/local/include -I Libft -I src/
GRPH_LIBFLAGS = -L /usr/local/lib -lX11

all: $(NAME)

$(NAME): $(SRC) $(INC) $(LIB) Makefile
	clear
	@$(CC) -o $(NAME) $(SRC) $(LIB) $(LFLAGS) $(GRPH_INCFLAGS) $(GRPH_LIBFLAGS)
	@echo "${_BOLD}${_GREEN}$(NAME) made"

Libft/Makefile:
	@git submodule update --init Libft
	
$(LIB): Libft/Makefile
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