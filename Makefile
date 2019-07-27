include ~/bash_colors.sh
NAME=Minesweeper
CC=gcc
CFLAGS=-Wall -Wextra -Werror
# OFLAGS=-g3 -fsanitize=address
SRC=Minesweeper.c
OBJ=$(SRC:.c=.o)
INC=Minesweeper.h
#LIB=libft/libft.a
#LFLAGS=-L libft -I libft
GRPH_INCFLAGS = -I/usr/local/include
GRPH_LIBFLAGS = -L/usr/local/lib -lgraphics -lX11 -lm

all: $(NAME)

$(NAME): $(SRC) $(INC) Makefile
	@$(CC) -o $(NAME) $(SRC) $(GRPH_INCFLAGS) $(GRPH_LIBFLAGS)
	@echo "${_BOLD}${_GREEN}$(NAME) made"

clean:
	@echo "${_BOLD}${_RED}$(NAME) clean"

fclean:
	@rm -rf $(NAME)
	@echo "${_BOLD}${_UNDER}${_RED}$(NAME) fclean" 

re: fclean all
