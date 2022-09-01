#ifndef			MINESWEEPER_H
# define		MINESWEEPER_H

# include		<stdlib.h>
# include		<stdio.h>
# include		"libft.h"

typedef			struct _MGame {
	size_t		width, height, mines, seen;
	size_t		win_w, win_h;
	char		**field;
	char		**discover_field;
}				MGame;

MGame		*MGameInit(MGame *game, int ac, const char *av[]);

#endif