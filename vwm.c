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

char * GetInputString()
{
	char * cmd[] = { "dmenu", "-b", "-p", ":", "-nb", "#000", "-nf", "#FFF", "-sf", "#FFF", "-sb", "#000", NULL };
	static char output[1024];
	int fds[2];
	int dummy;
	int len;

	if(pipe(fds) == -1) ELOG("pipe");

	XUngrabKeyboard(display, CurrentTime);
	XFlush(display);

	if(fork() == 0)
	{
		if(dup2(fds[1], 1) == -1)
		{
			ELOG("dup2");
			exit(1);
		}
		close(0);
		close(fds[0]);
		close(fds[1]);

		execvp(cmd[0], cmd);
		perror(cmd[0]);
		exit(1);
	}

	close(fds[1]);
	wait(&dummy);

	len = read(fds[0], output, 1023);
	close(fds[0]);
	output[len-1] = '\0';
	LOG(output);
	if (XGrabKeyboard(display, root, True, GrabModeAsync, GrabModeAsync, CurrentTime) != GrabSuccess)
		running = 0;
	return output;
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


