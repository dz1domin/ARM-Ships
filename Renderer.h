#ifndef _RENDERER_H_
#define _RENDERER_H_


#include "LPC17xx.h"
#include "Open1768_LCD.h"
#include "LCD_ILI9325.h"
#include "Board_LED.h"                  // ::Board Support:LED
#include <stdio.h>
#include "asciiLib.h"
#include <string.h>
#include "TP_Open1768.h"

void DrawSquare(uint16_t x_start, uint16_t y_start, uint16_t color, uint16_t background_color);
void DrawBoard(uint16_t x_start, uint16_t y_start, uint16_t color, uint16_t background_color);
void DrawChar(const char c, uint16_t x_start, uint16_t y_start, uint16_t color, uint16_t background_color);
void DrawString(const char* str, uint16_t x_start, uint16_t y_start, uint16_t color, uint16_t background_color);
void DrawCoor(void);
void DrawPoint(uint16_t color);
void DrawButton(const char* napis,uint16_t x_start, uint16_t y_start,uint16_t color, uint16_t background_color);
void ClearBoard(void);
void DrawBox(uint16_t x_start, uint16_t y_start, uint16_t x_size, uint16_t y_size,uint16_t color, uint16_t background_color);
void ShowMessage(const char* message);

#endif
