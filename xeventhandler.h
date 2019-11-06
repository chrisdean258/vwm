#ifndef VMW_X_EVENTS
#define VMW_X_EVENTS

#include <X11/Xlib.h>

typedef void (*xeventhandler)(XEvent * e);

void buttonpress     (XEvent * e);
void clientmessage   (XEvent * e);
void configurerequest(XEvent * e);
void configurenotify (XEvent * e);
void destroynotify   (XEvent * e);
void expose          (XEvent * e);
void focusin         (XEvent * e);
void keypress        (XEvent * e);
void mappingnotify   (XEvent * e);
void maprequest      (XEvent * e);
void propertynotify  (XEvent * e);
void unmapnotify     (XEvent * e);

extern Display * display;
#endif
