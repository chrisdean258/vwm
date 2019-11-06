#include <X11/keysym.h>
#include <X11/XKBlib.h>

#include "vwm.h"
#include "xeventhandler.h"

void buttonpress     (XEvent * e){LOG("buttonpress");}
void clientmessage   (XEvent * e){LOG("clientmessage");}
void configurerequest(XEvent * e){LOG("configurerequest");}
void configurenotify (XEvent * e){LOG("configurenotify");}
void destroynotify   (XEvent * e){LOG("destroynotify");}
void expose          (XEvent * e){LOG("expose");}
void focusin         (XEvent * e){LOG("focusin");}
void keypress(XEvent * e)
{
	KeySym keysym;
	XKeyEvent * ev;

	LOG("keypress");

	ev = &e->xkey;
	keysym = XkbKeycodeToKeysym(display, ev->keycode, 0, ev->state & ShiftMask ? 1 : 0);

	if(keysym == XK_q) running = 0;
}
void mappingnotify   (XEvent * e){LOG("mappingnotify");}
void maprequest      (XEvent * e){LOG("maprequest");}
void propertynotify  (XEvent * e){LOG("propertynotify");}
void unmapnotify     (XEvent * e){LOG("unmapnotify");}

