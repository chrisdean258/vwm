#include <X11/keysym.h>
#include <X11/Xlib.h>
#include "macros.h"
#include "xevents.h"
#include "vwm.h"

int running = 1;
static void (*handler[])(Display *, XEvent *) = {
	[ButtonPress] = buttonpress,
	[ClientMessage] = clientmessage,
	[ConfigureRequest] = configurerequest,
	[ConfigureNotify] = configurenotify,
	[DestroyNotify] = destroynotify,
	[Expose] = expose,
	[FocusIn] = focusin,
	[KeyPress] = keypress,
	[MappingNotify] = mappingnotify,
	[MapRequest] = maprequest,
	[PropertyNotify] = propertynotify,
	[UnmapNotify] = unmapnotify
};

int main()
{
	Display * dpy;
	Window root;
	XEvent ev;

	if(!(dpy = XOpenDisplay(0x0))) return 1;

	root = DefaultRootWindow(dpy);

	XGrabKeyboard(dpy, root, True, GrabModeAsync, GrabModeAsync, CurrentTime);

	while(running)
	{
		XNextEvent(dpy, &ev);
		if(handler[ev.type]) handler[ev.type](dpy, &ev);
	}

	return 0;
}


