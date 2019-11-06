#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <stdio.h>
#include <string.h>

#include "macros.h"
#include "xeventhandler.h"
#include "vwm.h"

int running = 1;
Mode mode = Normal;
Display * display;
Window root;

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

char * GetInputString()
{
	XEvent ev;
	static char buff[1024];
	KeySym keysym;
	buff[0] = '\0';
	char * c;

	while(XCheckTypedEvent(display, MotionNotify, &ev))
	{
		keysym = XkbKeycodeToKeysym(display, ev->keycode, 0, ev->state & ShiftMask ? 1 : 0);
		c = XKeysymToString(keysym);
		strcat(buff, c);
	}
}

void NormalMode()
{
	if(mode == Normal) return;

	mode = Normal;
	LOG("Normal Mode Active");
	XGrabKeyboard(display, root, True, GrabModeAsync, GrabModeAsync, CurrentTime);
}

void InsertMode()
{
	if(mode == Insert) return;

	mode = Insert;
	LOG("Insert Mode Active");
	XUngrabKeyboard(display, CurrentTime);
	XGrabKey(display, XKeysymToKeycode(display, XK_Escape), 0, root, True, GrabModeAsync, GrabModeAsync);
}

void CommandMode()
{
	FILE * proc;
	char buff[1024];

	if(mode == Command) return;

	mode = Command;


	LOG("Command Mode Active");

	NormalMode();
}

int main()
{
	XEvent ev;

	if(!(display = XOpenDisplay(NULL))) return 1;
	root = DefaultRootWindow(display);

	CommandMode();

	XGrabKeyboard(display, root, True, GrabModeAsync, GrabModeAsync, CurrentTime);

	while(running)
	{
		XNextEvent(display, &ev);
		if(handler[ev.type]) handler[ev.type](&ev);
	}



	return 0;
}


