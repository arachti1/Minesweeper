#include "Minesweeper.h"
#include "XEnv.h"

int			main(int ac, const char *av[]) {

	MGame		*game;
	if (!(game = MGameInit(game, ac, av)))
		return (0);

	printf("okok\n");
	for (int j = 0; j < game->width; ++j)
		printf("%s\n", game->field[j]);

	XEnv		*xenv;
	if (!(xenv = XEnvInit(game->win_w, game->win_h)))
		return (0);
	Atom del_window = XInternAtom(xenv->d, "WM_DELETE_WINDOW", 0);
	XSetWMProtocols(xenv->d, xenv->w, &del_window, 1);

	XDrawGameInit(game, xenv);
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
				XDrawGameInit(game, xenv);
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