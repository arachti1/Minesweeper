#ifndef			XENV_H
# define		XENV_H

#include	<X11/Xlib.h>
#include	"Minesweeper.h"

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

typedef			struct _XEnv {
	int			larg, haut, s;
	Display		*d;
	Window		w;
	GC			gc;
	XFontStruct	*fd;
	XEvent		e;
	XGCValues	gcv;
}				XEnv;

XEnv		*XEnvInit(int win_w, int win_h);
void		XDrawGameInit(MGame *game, XEnv *xenv);
int		XDrawImage(int x, int y, char *path, XEnv *xenv);


#endif