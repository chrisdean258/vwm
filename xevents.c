#include <X11/keysym.h>

#include "vwm.h"
#include "xevents.h"

void buttonpress     (Display * display, XEvent * e){LOG("buttonpress");}
void clientmessage   (Display * display, XEvent * e){LOG("clientmessage");}
void configurerequest(Display * display, XEvent * e){LOG("configurerequest");}
void configurenotify (Display * display, XEvent * e){LOG("configurenotify");}
void destroynotify   (Display * display, XEvent * e){LOG("destroynotify");}
void expose          (Display * display, XEvent * e){LOG("expose");}
void focusin         (Display * display, XEvent * e){LOG("focusin");}
void keypress(Display * display, XEvent * e)
{
	KeySym keysym;
	XKeyEvent * ev;

	LOG("keypress");

	ev = &e->xkey;
	keysym = XKeycodeToKeysym(display, (KeyCode)ev->keycode, 0);

	if(keysym == XK_q) running = 0;
}
void mappingnotify   (Display * display, XEvent * e){LOG("mappingnotify");}
void maprequest      (Display * display, XEvent * e){LOG("maprequest");}
void propertynotify  (Display * display, XEvent * e){LOG("propertynotify");}
void unmapnotify     (Display * display, XEvent * e){LOG("unmapnotify");}

