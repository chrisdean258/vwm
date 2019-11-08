#include <X11/keysym.h>
#include <X11/XKBlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

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

void grabkeyboard()
{
	struct timespec ts = { .tv_sec = 0, .tv_nsec = 1000000 };
	int i;

	for(i = 0; i < 1000; i++)
	{
		if(XGrabKeyboard(display, root, True, GrabModeAsync,
				GrabModeAsync, CurrentTime) == GrabSuccess)
			return;
		nanosleep(&ts, NULL);
	}
	DIE("cannot grab keyboard");
}

void ungrabkeyboard()
{
	XUngrabKeyboard(display, CurrentTime);
	XFlush(display);
}

void grabkey(KeySym keysym)
{
	XGrabKey(display, XKeysymToKeycode(display, keysym), 0, root, True,
		GrabModeAsync, GrabModeAsync);
}


char * GetInputString()
{
	char * cmd = "echo -n | dmenu -b -p : -nb '#000' -nf '#FFF' -sf '#FFF' -sb '#000'";
	static char output[1024];
	FILE * proc;

	ungrabkeyboard();
	proc = popen(cmd, "r");
	fgets(output, 1024, proc);
	output[MAX(strlen(output) - 1, 0)] = '\0';
	pclose(proc);
	grabkeyboard();

	return output;
}


void NormalMode()
{
	if(mode == Normal) return;

	mode = Normal;
	LOG("Normal Mode Active");
	grabkeyboard();
}

void InsertMode()
{
	if(mode == Insert) return;

	mode = Insert;
	LOG("Insert Mode Active");
	ungrabkeyboard();
	grabkey(XK_Escape);
}

void CommandMode()
{
	char * c;

	if(mode == Command) return;
	mode = Command;
	LOG("Command Mode Active");
	c = GetInputString();
	LOGF("Command Mode Command: %s", c);
	if(strcmp(c, "q") == 0) running = 0;
	NormalMode();
}

int main()
{
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
