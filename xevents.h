#ifndef VMW_X_EVENTS
#define VMW_X_EVENTS

#include <X11/Xlib.h>

void buttonpress     (Display * display, XEvent * e);
void clientmessage   (Display * display, XEvent * e);
void configurerequest(Display * display, XEvent * e);
void configurenotify (Display * display, XEvent * e);
void destroynotify   (Display * display, XEvent * e);
void expose          (Display * display, XEvent * e);
void focusin         (Display * display, XEvent * e);
void keypress        (Display * display, XEvent * e);
void mappingnotify   (Display * display, XEvent * e);
void maprequest      (Display * display, XEvent * e);
void propertynotify  (Display * display, XEvent * e);
void unmapnotify     (Display * display, XEvent * e);

#endif
