#include "calibrate_lcd.h"

extern Stack stack;
unsigned char calibrating;
const unsigned int MAX_TRIES = 10;
int offset_x;
int offset_y;
unsigned short zero_x, zero_y;
unsigned short max_x, max_y;

void calibrate_lcd(){
	unsigned short hits_x[MAX_TRIES], hits_y[MAX_TRIES];
	
	
	calibrating = 1;
	char buffer1[32];
	// 0, 0 point
	ClearBoard();
	DrawBox(0, 0, 4, 4, LCDRed, LCDRed);
	sprintf(buffer1, "Kliknij kwadracik %d razy", MAX_TRIES);
	DrawString(buffer1, 10, 200, LCDBlack, LCDWhite);
	
	unsigned short tries = 0;

	while(tries < MAX_TRIES){
		if(!empty(&stack)) {
			char buffer[32];
			unsigned short x, y;
			pop(&stack, &x, &y);
			// sprintf(buffer,"calib x:%d y:%d tries:%d\n\r",x,y, tries);
			// sendString(buffer);
			
			hits_x[tries] = x;
			hits_y[tries] = y;
			
			tries++;
			
			sprintf(buffer1, "Kliknij kwadracik %d razy", MAX_TRIES - tries);
			DrawString(buffer1, 10, 200, LCDBlack, LCDWhite);
		}
	};
	
	qsort(hits_x, MAX_TRIES, sizeof(unsigned short), coord_cmp);
	qsort(hits_y, MAX_TRIES, sizeof(unsigned short), coord_cmp);
	
	zero_x = hits_x[MAX_TRIES / 2];
	zero_y = hits_y[MAX_TRIES / 2];
	
	//sprintf(buffer1, "ZEROX: %d ZEROY: %d\n\r", zero_x, zero_y);
	//sendString(buffer1);
	
	// max_x, 0 point
	ClearBoard();
	DrawBox(LCD_MAX_X - 5, 0, 4, 4, LCDRed, LCDRed);
	sprintf(buffer1, "Kliknij kwadracik %d razy", MAX_TRIES);
	DrawString(buffer1, 10, 200, LCDBlack, LCDWhite);
	
	tries = 0;

	while(tries < MAX_TRIES){
		if(!empty(&stack)) {
			char buffer[32];
			unsigned short x, y;
			pop(&stack, &x, &y);
			// sprintf(buffer,"calib x:%d y:%d tries:%d\n\r",x,y, tries);
			// sendString(buffer);
			
			hits_x[tries] = x;
			hits_y[tries] = y;
			
			tries++;
			
			sprintf(buffer1, "Kliknij kwadracik %d razy", MAX_TRIES - tries);
			DrawString(buffer1, 10, 200, LCDBlack, LCDWhite);
		}
	};
	
	qsort(hits_x, MAX_TRIES, sizeof(unsigned short), coord_cmp);
	qsort(hits_y, MAX_TRIES, sizeof(unsigned short), coord_cmp);
	
	max_x = hits_x[MAX_TRIES / 2];
	
	//sprintf(buffer1, "MAXX: %d\n\r", max_x);
	//sendString(buffer1);
	
	// 0, max_y point
	ClearBoard();
	DrawBox(0, LCD_MAX_Y - 4, 4, 4, LCDRed, LCDRed);
	sprintf(buffer1, "Kliknij kwadracik %d razy", MAX_TRIES);
	DrawString(buffer1, 10, 200, LCDBlack, LCDWhite);
	
	tries = 0;

	while(tries < MAX_TRIES){
		if(!empty(&stack)) {
			char buffer[32];
			unsigned short x, y;
			pop(&stack, &x, &y);
			// sprintf(buffer,"calib x:%d y:%d tries:%d\n\r",x,y, tries);
			// sendString(buffer);
			
			hits_x[tries] = x;
			hits_y[tries] = y;
			
			tries++;
			
			sprintf(buffer1, "Kliknij kwadracik %d razy", MAX_TRIES - tries);
			DrawString(buffer1, 10, 200, LCDBlack, LCDWhite);
		}
	};
	
	qsort(hits_x, MAX_TRIES, sizeof(unsigned short), coord_cmp);
	qsort(hits_y, MAX_TRIES, sizeof(unsigned short), coord_cmp);
	
	max_y = hits_y[MAX_TRIES / 2];
	
	//sprintf(buffer1, "MAXY: %d\n\r", max_y);
	//sendString(buffer1);
	
	calibrating = 0;
}

int coord_cmp (const void * a, const void * b)
{
    unsigned short _a = *(unsigned short*)a;
    unsigned short _b = *(unsigned short*)b;
    if(_a < _b) return -1;
    else if(_a == _b) return 0;
    else return 1;
}