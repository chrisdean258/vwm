#ifndef VWM_H
#define VWM_H

#include "macros.h"
#include <X11/Xlib.h>

typedef enum Mode { Normal, Insert, Command } Mode;

extern int running;
extern Mode mode;

extern void  NormalMode();
extern void  InsertMode();
extern void CommandMode();

#endif
