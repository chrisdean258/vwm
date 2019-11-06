#include <X11/Xlib.h>
#include "macros.h"
#include "xeventhandler.h"
#include "vwm.h"

int running = 1;
Display * display;

static xeventhandler handler[] = {
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
	Window root;
	XEvent ev;

	if(!(display = XOpenDisplay(NULL))) return 1;

	root = DefaultRootWindow(display);

	XGrabKeyboard(display, root, True, GrabModeAsync, GrabModeAsync, CurrentTime);

	while(running)
	{
		XNextEvent(display, &ev);
		if(handler[ev.type]) handler[ev.type](&ev);
	}

	return 0;
}


