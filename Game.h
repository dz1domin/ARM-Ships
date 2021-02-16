#ifndef _GAME_H_
#define _GAME_H_

#include "Board.h"
#include "Renderer.h"
#include "PIN_LPC17xx.h"
#include "stack.h"
#include "interrupt_handler.h"
#include "calibrate_lcd.h"

// define'y dla pozycji przyciskow statkow
#define StatkiX 220
#define StatkiW 15
#define StatkiH 15
#define JednoY  22
#define DwuY    42
#define TrzyY   62
#define CzteroY 82
#define PiecioY 102

// pozycja ustaw
#define UstawX 170
#define UstawY 260
#define UstawW 44
#define UstawH 20

// przyciski
#define PrzyciskW 14
#define PrzyciskH 20
#define PrzyciskiStrzalkiY 285

#define PrzyciskLewoX  165
#define PrzyciskGoraX  180
#define PrzyciskPrawoX 195
#define PrzyciskDolX   210



typedef struct
{		
		Board m_ourboard;
		uint8_t m_shipLeft[4];
		uint8_t m_state;
		bool m_running;
		uint8_t m_command;
		bool m_turn;
		uint32_t m_shoots[10]; //nasze strzaly
} Game;

void init(Game* g);
void run(Game* g);
void handleTurn(Game* g, uint16_t *x, uint16_t* y, uint16_t *fixedX, uint16_t* fixedY);
void sendShot(uint16_t x, uint16_t y);
void checkForHit(Game* g,char* newMessage,uint16_t receivedX,uint16_t receivedY);
void drawShots(Game* g);
void checkForGameEnd(Game* g, char* buff);
#endif
