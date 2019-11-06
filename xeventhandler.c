#include <X11/keysym.h>
#include <X11/XKBlib.h>

#include "vwm.h"
#include "xeventhandler.h"

void buttonpress     (XEvent * e){HERE();}
void clientmessage   (XEvent * e){HERE();}
void configurerequest(XEvent * e){HERE();}
void configurenotify (XEvent * e){HERE();}
void destroynotify   (XEvent * e){HERE();}
void expose          (XEvent * e){HERE();}
void focusin         (XEvent * e){HERE();}

void keypress(XEvent * e)
{
	KeySym keysym;
	XKeyEvent * ev;
	char * c;

	ev = &e->xkey;
	keysym = XkbKeycodeToKeysym(display, ev->keycode, 0, ev->state & ShiftMask ? 1 : 0);

	if(keysym == XK_q) running = 0;
	if(keysym == XK_Escape) NormalMode();
	if(keysym == XK_i) InsertMode();
	if(keysym == XK_colon) CommandMode();

	c = XKeysymToString(keysym);
	LOG(c);
}

void mappingnotify   (XEvent * e){HERE();}
void maprequest      (XEvent * e){HERE();}
void propertynotify  (XEvent * e){HERE();}
void unmapnotify     (XEvent * e){HERE();}

