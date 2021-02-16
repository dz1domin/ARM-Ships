#include "Renderer.h"

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
	
	uint8_t str_size = strlen(str);
	for(uint16_t i = 0; i < str_size; ++i)
	{
			DrawChar(str[i], x_start + i * 8, y_start, color, background_color);
	}
}

void DrawCoor()
{
	char str[16];
	int pos_x, pos_y;
	pos_x = pos_y = 0;
	str[0] = '\0';
	touchpanelGetXY(&pos_x, &pos_y);
	pos_x = pos_x / 4095. * LCD_MAX_X;
	pos_y = pos_y / 4095. * LCD_MAX_Y;
	sprintf(str, "%4d", pos_x);
	DrawString(str, 160, 150, LCDBlack, LCDWhite);
	str[0] = '\0';
	sprintf(str, "%4d", pos_y);
	DrawString(str, 190, 150, LCDBlack, LCDWhite);
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

void DrawButton(const char* napis,uint16_t x_start, uint16_t y_start,uint16_t color, uint16_t background_color)
{
	uint8_t y_size = 16 + 4;
	uint8_t str_size = strlen(napis);
	uint8_t x_size = 8 * str_size + 4;

	uint16_t y, x;
	for(y = 0; y < y_size; y++)
	{	
		lcdSetCursor(x_start, y_start + y);
		lcdWriteReg(DATA_RAM, color);
		for(x = 0; x < x_size; x++)
		{
			if(y == 0 || x == (x_size-1) || y == (y_size - 1))
				lcdWriteData(color);
			else
				lcdWriteData(background_color);
		}
	}
	
	for(uint16_t i = 0; i < str_size; ++i)
	{
			DrawChar(napis[i], x_start + 2 + i * 8, y_start + 2, color, background_color);
	}
}

void ClearBoard()
{
		lcdSetCursor(0,0);
		lcdWriteReg(DATA_RAM, LCDWhite);
		for(int y = 0; y < (320*240); y++) lcdWriteData(LCDWhite);
}

void DrawBox(uint16_t x_start, uint16_t y_start, uint16_t x_size, uint16_t y_size,uint16_t color, uint16_t background_color)
{
	for(uint16_t y = y_start; y < y_start + y_size; y++)
	{	
		lcdSetCursor(x_start, y);
		lcdWriteReg(DATA_RAM, color);
		for(uint16_t x = x_start; x < x_start + x_size; x++)
		{
			if(y == y_start || x == (x_start + x_size-1) || y == (y_start + y_size-1))
				lcdWriteData(color);
			else
				lcdWriteData(background_color);
		}
	}

}

void ShowMessage(const char* message)
{
	char buffer[9];
	int len = strlen(message);
	DrawBox(160,140,70,100,LCDBlack,LCDWhite);
	for(int i = 0; i <= len / 8; i++)
	{
		memcpy(buffer, message + i * 8, 8);
		buffer[8] = '\0';
		DrawString(buffer, 162, 142 + i * 16, LCDBlack, LCDWhite);
	}
}

