#include "Minesweeper.h"

int			MGameInit(MGame *game) {
	game->field = (char **)malloc(sizeof(char *) * game->width);
	for (int i = 0; i < game->width; ++i) {
		game->field[i] = (char *)malloc(sizeof(char) * game->height);
		for (int j = 0; j < game->height; ++j)
			game->field[i][j] = '0';
	}
	long int x, y = 0;
	for (int i = 0; i < game->mines; ++i) {
		x = random() % game->width;
		y = random() % game->height;
		if (game->field[x][y] == '*') {
			i--;
			continue;
		}
		printf("%li, %li\n", x, y);
		game->field[x][y] = '*';
		if (x > 0 && y > 0)
			game->field[x - 1][y - 1] = game->field[x - 1][y - 1] == '*' ? '*' : game->field[x - 1][y - 1] + 1;
		if (x > 0)
			game->field[x - 1][y] = game->field[x - 1][y] == '*' ? '*' : game->field[x - 1][y] + 1;
		if (x > 0 && y < game->height - 1)
			game->field[x - 1][y - 1] = game->field[x - 1][y - 1] == '*' ? '*' : game->field[x - 1][y - 1] + 1;
		if (y > 0)
			game->field[x][y - 1] = game->field[x][y - 1] == '*' ? '*' : game->field[x][y - 1] + 1;
		if (y < game->height - 1)
			game->field[x][y + 1] = game->field[x][y + 1] == '*' ? '*' : game->field[x][y + 1] + 1;
		if (x < game->width - 1 && y > 0) {
			game->field[x + 1][y - 1] = game->field[x + 1][y - 1] == '*' ? '*' : game->field[x + 1][y - 1] + 1;
		printf("ok\n");
		}
		if (x < game->width - 1)
			game->field[x + 1][y] = game->field[x + 1][y] == '*' ? '*' : game->field[x + 1][y] + 1;
		if (x < game->width - 1 && y < game->height - 1)
			game->field[x + 1][y + 1] = game->field[x + 1][y + 1] == '*' ? '*' : game->field[x + 1][y + 1] + 1;
		for (int j = 0; j < game->width; ++j)
			printf("%s\n", game->field[j]);
	}
	return (0);
}

int			main(int ac, char const *av[]) {

	MGame		*game;

	if (ac != 4
		|| !(game = (MGame*)malloc(sizeof(MGame)))
		|| (game->width = atoi(av[1])) <= 0
		|| (game->height = atoi(av[2])) <= 0
		|| (game->mines = atoi(av[3])) >= game->width * game->height / 2) {
		printf("./Minesweeper usage:	x_size y_size n_mines\n\t\t\t[    > 0    ] [< x*y / 2]");
		return (0);
	}
	printf("%i, %i, %i\n", game->width, game->height, game->mines);
	MGameInit(game);
	XEnv		*xenv;

	printf("okok\n");
	if (!(xenv = (XEnv *)malloc(sizeof(XEnv)))
		|| !(xenv->d = XOpenDisplay(getenv("DISPLAY")))
		|| !(xenv->w = XCreateSimpleWindow(xenv->d, RootWindow(xenv->d, XDefaultScreen(xenv->d)), 0, 0, game->width * 50, game->height * 50, 2, BlackPixel(xenv->d, XDefaultScreen(xenv->d)), WhitePixel(xenv->d, XDefaultScreen(xenv->d))))
		|| !(xenv->fd = XLoadQueryFont(xenv->d, "fixed")) || !(xenv->gcv.font = xenv->fd->fid)
		|| !(xenv->gc = XCreateGC(xenv->d, xenv->w, GCFont | GCForeground, &(xenv->gcv)))) {
		printf("XERROR\n");
		return (0);
	}
	XSetForeground(xenv->d, xenv->gc, BlackPixel(xenv->d, XDefaultScreen(xenv->d)));
	XMapWindow(xenv->d, xenv->w);
	XRaiseWindow(xenv->d, xenv->w);
	for (int x = 0; x <= game->width; ++x) {
		XDrawLine(xenv->d, xenv->w, xenv->gc, x * 50, 0, x * 50, game->height * 50);
	}
	for (int y = 0; y <= game->height; ++y) {
		XDrawLine(xenv->d, xenv->w, xenv->gc, 0, y * 50, game->width * 50, y * 50);
	}
	XSelectInput(xenv->d, xenv->w, KeyPressMask | ButtonPressMask);
	while (xenv->e.xkey.keycode != 9) {
		XNextEvent(xenv->d, &(xenv->e));
		switch(xenv->e.type) {
			case ButtonPress:
				printf("x, y = %i, %i\n", xenv->e.xbutton.x / 50, xenv->e.xbutton.y / 50);
				break;
			case KeyPress:
				printf("key = %i\n", xenv->e.xkey.keycode);
				break;
		}
	}
	XDestroyWindow(xenv->d, xenv->w);
	XFreeGC(xenv->d, xenv->gc);
	XCloseDisplay(xenv->d);
	return (0);
}