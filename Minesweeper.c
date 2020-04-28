#include "Minesweeper.h"

XEnv		*XEnvInit(MGame *game, XEnv *xenv) {
	if (!((xenv = (XEnv *)malloc(sizeof(XEnv)))
		&& (xenv->d = XOpenDisplay(getenv("DISPLAY")))
		&& (xenv->w = XCreateSimpleWindow(xenv->d, XDefaultRootWindow(xenv->d), 0, 0, game->win_w, game->win_h, 2, BlackPixel(xenv->d, XDefaultScreen(xenv->d)), WhitePixel(xenv->d, XDefaultScreen(xenv->d))))
		&& (xenv->fd = XLoadQueryFont(xenv->d, "fixed")) && (xenv->gcv.font = xenv->fd->fid)
		&& (xenv->gc = XCreateGC(xenv->d, xenv->w, GCFont | GCForeground, &(xenv->gcv))))) {
		printf("XERROR\n");
		return (NULL);
	}

	XSetForeground(xenv->d, xenv->gc, BlackPixel(xenv->d, XDefaultScreen(xenv->d)));
	XMapWindow(xenv->d, xenv->w);
	XRaiseWindow(xenv->d, xenv->w);

	return (xenv);
}

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

void		MDrawGame(MGame *game, XEnv *xenv) {
	for (int x = 0; x <= game->width; ++x)
		XDrawLine(xenv->d, xenv->w, xenv->gc, x * game->win_w / game->width, 0, x * game->win_w / game->width, game->win_h);
	for (int y = 0; y <= game->height; ++y)
		XDrawLine(xenv->d, xenv->w, xenv->gc, 0, y * game->win_h / game->height, game->win_w, y * game->win_h / game->height);
}

int			main(int ac, const char *av[]) {

	MGame		*game;
	if (!(game = MGameInit(game, ac, av)))
		return (0);

	printf("okok\n");
	for (int j = 0; j < game->width; ++j)
		printf("%s\n", game->field[j]);

	XEnv		*xenv;
	if (!(xenv = XEnvInit(game, xenv)))
		return (0);
	Atom del_window = XInternAtom(xenv->d, "WM_DELETE_WINDOW", 0);
	XSetWMProtocols(xenv->d, xenv->w, &del_window, 1);

	MDrawGame(game, xenv);
	XSelectInput(xenv->d, xenv->w, 16777215);
	XSelectInput(xenv->d, XDefaultRootWindow(xenv->d), FocusChangeMask);
	int i = 0;
	while (xenv->e.xkey.keycode != 9) {
		XNextEvent(xenv->d, &(xenv->e));
		i++;
		switch(xenv->e.type) {
			case ButtonPress: 
			case ButtonRelease:
				printf("%i(%s) : [ %lu %lu ]\n", xenv->e.xbutton.button, (xenv->e.xbutton.type == ButtonPress) ? "on" : "off", xenv->e.xbutton.x * game->width / game->win_w, xenv->e.xbutton.y * game->height / game->win_h);
				break;
			case KeyPress:
				printf("key = %i\n", xenv->e.xkey.keycode);
				break;
			case Expose:
				MDrawGame(game, xenv);
			case ClientMessage:
				goto exit;
		}
		printf("%i : %s [%i]\n", i, event_names[xenv->e.type], xenv->e.type);
	}
	exit:
	XDestroyWindow(xenv->d, xenv->w);
	XFreeGC(xenv->d, xenv->gc);
	XCloseDisplay(xenv->d);
	return (0);
}