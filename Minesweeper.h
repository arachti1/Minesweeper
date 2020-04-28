#ifndef			MINESWEEPER_H
# define		MINESWEEPER_H

# include		<stdlib.h>
# include		<stdio.h>
# include		<X11/Xlib.h>
# include		"libft/inc/libft.h"

static char *event_names[] = {
   "",
   "",
   "KeyPress",
   "KeyRelease",
   "ButtonPress",
   "ButtonRelease",
   "MotionNotify",
   "EnterNotify",
   "LeaveNotify",
   "FocusIn",
   "FocusOut",
   "KeymapNotify",
   "Expose",
   "GraphicsExpose",
   "NoExpose",
   "VisibilityNotify",
   "CreateNotify",
   "DestroyNotify",
   "UnmapNotify",
   "MapNotify",
   "MapRequest",
   "ReparentNotify",
   "ConfigureNotify",
   "ConfigureRequest",
   "GravityNotify",
   "ResizeRequest",
   "CirculateNotify",
   "CirculateRequest",
   "PropertyNotify",
   "SelectionClear",
   "SelectionRequest",
   "SelectionNotify",
   "ColormapNotify",
   "ClientMessage",
   "MappingNotify"
};

typedef			struct _MGame {
	size_t		width, height, mines, seen;
	size_t		win_w, win_h;
	char		**field;
	char		**discover_field;
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