#ifndef __calibrate_lcd__
#define __calibrate_lcd__

#include "Renderer.h"
#include "stack.h"
#include "interrupt_handler.h"
#include <stdlib.h>

void calibrate_lcd(void);

int coord_cmp (const void * a, const void *);

#endif
