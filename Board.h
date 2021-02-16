#ifndef _BOARD_H_
#define _BOARD_H_
#include "Ship.h"

#define AllyXCoor 5
#define AllyYCoor 5
#define AllyWidth 155
#define AllyHeight 155

#define EnemyXCoor 5
#define EnemyYCoor 165
#define EnemyWidth 155
#define EnemyHeight 155

/*
00 - brak statku  - nie strzelony
01 - statek - nie strzelony
10 - brak statku - strzal
11 - statek - trafiony


jeden 4pola
dwa 3pola
trzy 2pola
cztery 1pole
*/



typedef struct
{
		Ship m_ships[10];	
} Board;

#endif
