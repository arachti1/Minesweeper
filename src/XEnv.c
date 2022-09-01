#include "XEnv.h"
#include "Minesweeper.h"

XEnv		*XEnvInit(int win_w, int win_h) {
	XEnv	*xenv;
	if (!((xenv = (XEnv *)malloc(sizeof(XEnv)))
		&& (xenv->d = XOpenDisplay(getenv("DISPLAY")))
		&& (xenv->w = XCreateSimpleWindow(xenv->d, XDefaultRootWindow(xenv->d), 0, 0, win_w, win_h, 2, BlackPixel(xenv->d, XDefaultScreen(xenv->d)), WhitePixel(xenv->d, XDefaultScreen(xenv->d))))
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

void		XDrawGameInit(MGame *game, XEnv *xenv) {
	for (int x = 0; x <= game->width; ++x)
		XDrawLine(xenv->d, xenv->w, xenv->gc, x * game->win_w / game->width, 0, x * game->win_w / game->width, game->win_h);
	for (int y = 0; y <= game->height; ++y) {
		XDrawLine(xenv->d, xenv->w, xenv->gc, 0, y * game->win_h / game->height, game->win_w, y * game->win_h / game->height);
		// for (int x = 0; x <= game->width; x++)
			// XDrawImage()

	}
}

int			XDrawImage(int x, int y, char *path, XEnv *xenv);

