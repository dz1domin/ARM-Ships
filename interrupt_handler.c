#include "interrupt_handler.h"
#include "Board.h"
#include "Game.h"
#include "stack.h"
#include "calibrate_lcd.h"

extern unsigned char calibrating;
extern Stack stack;
extern Game game;
int counter = 0;
char receivedDataBuffer[16];
extern unsigned short zero_x, zero_y, max_x, max_y;
const unsigned int MAX_POINT_SAMPLES = 20;


// funkcja wysylajaca string przez interfejs UART plytki
void sendString(const char * str)
{
	while (*str != '\0')
	{
		if(LPC_UART0->LSR & (1 << 5))
		{
			LPC_UART0->THR = *str;
			str++;
		}
	}
}

// funkcja obslugi przerwan z ekranu dotykowego
void EINT3_IRQHandler()
{
	int pos_x,pos_y,wys_x,wys_y;
	char buffer[64];
	int hits_x[MAX_POINT_SAMPLES];
	int hits_y[MAX_POINT_SAMPLES];
	
	for(int i = 0; i < MAX_POINT_SAMPLES; i++) {
		touchpanelGetXY(&pos_x, &pos_y);
		hits_x[i] = pos_x;
		hits_y[i] = pos_y;
	}
	
	qsort(hits_x, MAX_POINT_SAMPLES, sizeof(int), coord_cmp);
	qsort(hits_y, MAX_POINT_SAMPLES, sizeof(int), coord_cmp);
	
	pos_x = hits_x[MAX_POINT_SAMPLES / 2];
	pos_y = hits_y[MAX_POINT_SAMPLES / 2];
	
	if(calibrating)
	{
		if(pos_y != 0) {
			push(&stack, (unsigned short)pos_y, (unsigned short)pos_x);
		}
	}
	else {
		// sprintf(buffer, "ZEROX: %d ZEROY: %d MAXX: %d, MAXY: %d\n\r", zero_x, zero_y, max_x, max_y);
		// sendString(buffer);
		wys_x = (double)(pos_y - zero_y) / (max_y - zero_y) * LCD_MAX_X;
		wys_y = (double)(pos_x - zero_x) / (max_x - zero_x) * LCD_MAX_Y;
		
		wys_x = wys_x > LCD_MAX_X ? LCD_MAX_X : wys_x;
		wys_x = wys_x < 0 ? 0 : wys_x;
		
		wys_y += 5; //MAGIC :^)) HEHE
		wys_y = wys_y > LCD_MAX_Y ? LCD_MAX_Y : wys_y;
		wys_y = wys_y < 0 ? 0 : wys_y;
		
		if(!(pos_x == 0 || pos_y == 0)){
			//sprintf(buffer,"lcd coor x:%4d y:%4d\n\r",wys_x,wys_y);
			//sendString(buffer);
			push(&stack,(unsigned short)wys_x,(unsigned short)wys_y);
		}
	}
	
	LPC_GPIOINT->IO0IntClr = 1 << 19;
}

// obsluga przerwania od UART0
void UART0_IRQHandler()
{
	char c = LPC_UART0->RBR;
	receivedDataBuffer[counter++] = c;
	if(c == ';')
	{
		receivedDataBuffer[counter] = '\0';
		counter = 0;
		game.m_command = 1;
		if(game.m_state == 0 && !strcmp(receivedDataBuffer, "RDY;"))
		{
			game.m_turn = 0;
		}
	}
	LPC_UART0->IIR;
}
