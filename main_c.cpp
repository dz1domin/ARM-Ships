#include "LPC17xx.h"
#include "Open1768_LCD.h"
#include "LCD_ILI9325.h"
#include "Board_LED.h"                  // ::Board Support:LED
#include <stdio.h>
#include "asciiLib.h"
#include <string.h>
#include "TP_Open1768.h"


void DrawSquare(uint16_t x_start, uint16_t y_start, uint16_t color, uint16_t background_color)
{
	int y, x;
	for(y = 0; y < 15; y++)
	{	
		lcdSetCursor(x_start, y_start + y);
		lcdWriteReg(DATA_RAM, color);
		for(x = 0; x < 15; x++)
		{
			if(x == 0 || y == 0 || x == 14 || y == 14)
				lcdWriteData(color);
			else
				lcdWriteData(background_color);
		}
	}
}

void DrawBoard(uint16_t x_start, uint16_t y_start, uint16_t color, uint16_t background_color)
{
	uint16_t x_count, y_count;
	for(y_count = 0; y_count < 10; y_count++)
	{
		for(x_count = 0; x_count < 10; x_count++)
		{
			DrawSquare(x_start + x_count * 15, y_start + y_count * 15, color, background_color);
		}
	}
}

void DrawChar(const char c, uint16_t x_start, uint16_t y_start, uint16_t color, uint16_t background_color)
{
	uint16_t x, y;
	unsigned char bit;
	unsigned char ascii_char[16];
	GetASCIICode(0, ascii_char, c);
	for(y = 0; y < 16; y++)
	{	
		lcdSetCursor(x_start, y_start + y);
		lcdWriteReg(DATA_RAM, background_color);
		bit = 0;
		for(x = 0; x < 8; x++)
		{
			bit = ascii_char[y] & (1 << (7 - x));
			if(bit)
				lcdWriteData(color);
			else
				lcdWriteData(background_color);
		}
	}
}

void DrawString(const char* str, uint16_t x_start, uint16_t y_start, uint16_t color, uint16_t background_color)
{
	uint16_t x_count, y_count;
	for(y_count = 0; y_count < 10; y_count++)
	{
		for(x_count = 0; x_count < 20; x_count++)
		{
			DrawChar(str[x_count], x_start + x_count * 8, y_start + y_count * 16, color, background_color);
		}
	}
}

void DrawCoor()
{
	char str[16];
	int pos_x, pos_y;
	pos_x = pos_y = 0;
	str[0] = '\0';
	touchpanelGetXY(&pos_x, &pos_y);
	sprintf(str, "%4d", pos_x);
	DrawString(str, 0, 100, LCDBlack, LCDWhite);
	str[0] = '\0';
	sprintf(str, "%4d", pos_y);
	DrawString(str, 50, 100, LCDBlack, LCDWhite);
}

void DrawPoint(uint16_t color)
{
	int pos_x, pos_y;
	int wys_x, wys_y;
	pos_x = pos_y = 0;
	touchpanelGetXY(&pos_x, &pos_y);
	wys_x = (double)pos_y / 4095 * LCD_MAX_X;
	wys_y = (double)pos_x / 4095 * LCD_MAX_Y;
	lcdSetCursor((uint16_t)wys_x, (uint16_t)wys_y);
	lcdWriteReg(DATA_RAM, color);
} 

int main(int argc, char** argv)
{
	LED_Initialize();
	lcdConfiguration();
	init_ILI9325();
	touchpanelInit();
	
	DrawBoard(5, 5, LCDBlack, LCDWhite);
	DrawBoard(5, 165, LCDBlack, LCDGinger);
	/*
	while(1)
	{
		DrawCoor();
		DrawPoint(LCDBlack);
	}
	*/
	LED_Uninitialize();
}


