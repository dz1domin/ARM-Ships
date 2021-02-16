#ifndef _interrupt_handlder_h
#define _interrupt_handlder_h

#include "Renderer.h"

void sendString(const char * str);

void EINT3_IRQHandler(void);

#endif
