#include "Minesweeper.h"
#include "XEnv.h"

MGame			*MGameInit(MGame *game, int ac, const char *av[]) {
	if (ac != 4
		|| !(game = (MGame*)malloc(sizeof(MGame)))
		|| (game->width = atoi(av[1])) <= 0
		|| (game->height = atoi(av[2])) <= 0
		|| (game->mines = atoi(av[3])) >= game->width * game->height) {
		printf("./Minesweeper usage:	x_size y_size n_mines\n\t\t\t[    > 0    ] [< x * y]\n");
		return (NULL);
	}
	printf("%lu, %lu, %lu\n", game->win_w, game->win_h, game->mines);

	game->field = (char **)malloc(sizeof(char *) * game->width);
	game->discover_field = (char **)malloc(sizeof(char *) * game->width);
	for (int i = 0; i < game->width; ++i) {
		game->field[i] = (char *)malloc(sizeof(char) * game->height);
		game->discover_field[i] = (char *)malloc(sizeof(char) * game->height);
		for (int j = 0; j < game->height; ++j) {
			game->field[i][j] = '0';
			game->discover_field[i][j] = 0;
		}
	}
	long int x, y = 0;
	for (int i = 0; i < game->mines; ++i) {
		x = random() % game->width;
		y = random() % game->height;
		if (game->field[x][y] == '*') {
			i--;
			continue;
		}
		game->field[x][y] = '*';
		for (int sub_y = y - 1; sub_y <= y + 1; sub_y++) {
			for (int sub_x = x - 1; sub_x <= x + 1; sub_x++) {
				if (sub_x >= 0 && sub_x < game->width
					&& sub_y >= 0 && sub_y < game->height
					&& game->field[sub_x][sub_y] != '*')
					game->field[sub_x][sub_y] += 1;
			}
		}
	}
	game->win_w = ft_min(game->width * 50, 800);
	game->win_h = ft_min(game->height * 50, 800);
	return (game);
}
