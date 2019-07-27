#ifndef			MINESWEEPER_H
# define		MINESWEEPER_H

# include		<stdlib.h>
# include		<stdio.h>
# include		<X11/Xlib.h>

typedef			struct _MGame {
	int			width, height, mines, seen;
	char		**field;
}				MGame;

typedef			struct _XEnv {
	int			larg, haut, s;
	Display		*d;
	Window		w;
	GC			gc;
	XFontStruct	*fd;
	XEvent		e;
	XGCValues	gcv;
}				XEnv;


#endif