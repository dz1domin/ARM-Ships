#include "Game.h"

extern Stack stack;
extern char receivedDataBuffer[16];
uint16_t wybranyKwadracikPlansza[2];
uint16_t wybranyKwadracikStatek[2];
uint16_t wybranyKwadracikOpcje[2];
char ustawione = 0;


void rysujStatki(Game* g)
{
	DrawBoard(5, 5, LCDBlack, LCDWhite);
	char statkowNieUstawionych = 0;
	for(int i=0;i<4;++i){
			statkowNieUstawionych += g->m_shipLeft[i];
		}
	char size = 10 - statkowNieUstawionych;
	
	
	for(int i=0;i<size;++i){
		for(int j=0;j<g->m_ourboard.m_ships[i].size; ++j){
			DrawSquare(5 + 15 * g->m_ourboard.m_ships[i].m_coords[j][0],5 + 15 * g->m_ourboard.m_ships[i].m_coords[j][1],LCDBlack,LCDMagenta);
		}
	}

}



void ustawStatek(Game *g, uint16_t x, uint16_t y, char zwrot, uint16_t maszty)
{
		int statkowNieUstawionych = 0;
		
		if(!g->m_shipLeft[maszty-1])
		{
			ShowMessage("Blad ustawiania");
			return;
		}
		
		for(int i=0;i<4;++i){
			statkowNieUstawionych += g->m_shipLeft[i];
		}
		int indexWstawienia = 10 - statkowNieUstawionych;
		
		//sprintf(buffer,"Statek x:%d y:%d z:%c m:%d\n",x,y,zwrot,maszty);
		//sendString(buffer);
		
		int16_t current_x = x;
		int16_t current_y = y;
		unsigned char potencjalnyStatek[4][2];
		for(int i=0;i<4;++i){
				potencjalnyStatek[i][0] = 99;
				potencjalnyStatek[i][1] = 99;
		}
		
		potencjalnyStatek[0][0] = x; potencjalnyStatek[0][1] = y;
		for(int i=1;i<maszty;++i){
				
				switch(zwrot){
					case '>':
						++current_x;
						break;
					case 'v':
						++current_y;
						break;
					case '^':
						--current_y;
						break;
					case '<':
						--current_x;
						break;
				}
				
				if(current_x < 0 || current_x > 9 || current_y < 0 || current_y > 9) 
				{
					ShowMessage("Blad ustawiania");
					return;
				}
				potencjalnyStatek[i][0] = current_x;
				potencjalnyStatek[i][1] = current_y;
				
				
			
				
				
		}
		for(int z = 0; z < maszty; ++z){
				for(int j=0;j<indexWstawienia;++j){
						for(int k=0;k<g->m_ourboard.m_ships[j].size; ++k){
								if(potencjalnyStatek[z][0] == g->m_ourboard.m_ships[j].m_coords[k][0] && potencjalnyStatek[z][1] == g->m_ourboard.m_ships[j].m_coords[k][1])
								{
									ShowMessage("Blad ustawiania");
									return;
								}
						}
				}
		}
	memcpy(&(g->m_ourboard.m_ships[indexWstawienia]),potencjalnyStatek,2*4);
	--(g->m_shipLeft[maszty-1]);
	--statkowNieUstawionych;
	g->m_ourboard.m_ships[indexWstawienia].size = maszty;
	
	
	
	if(!statkowNieUstawionych) ustawione = 1;
	ShowMessage("Ustawiono");
}



void obsluzDotyk(Game *g,uint16_t x, uint16_t y)
{
	
	char buffer[64];
	
	if(x > AllyXCoor && x < AllyXCoor + AllyWidth
		&& y > AllyYCoor && y < AllyYCoor + AllyHeight)
	{
		
		//sprintf(buffer,"Wlasna plansza x:%d y:%d\n\r",x,y);
		//sendString(buffer);
	
		uint16_t fixedX;
		uint16_t fixedY;
		
		if(wybranyKwadracikPlansza[0] && wybranyKwadracikPlansza[1]){
			fixedX = ((wybranyKwadracikPlansza[0] - AllyXCoor) / 15) % 10;
			fixedY = ((wybranyKwadracikPlansza[1] - AllyYCoor) / 15) % 10;
			DrawSquare(5 + 15 * fixedX, 5 + 15 * fixedY,LCDBlack,LCDWhite);
		}
		
		
		wybranyKwadracikPlansza[0] = x;
		wybranyKwadracikPlansza[1] = y;
		fixedX = ((x-AllyXCoor) / 15) % 10;
		fixedY = ((y-AllyYCoor) / 15) % 10;
		DrawSquare(5 + 15 * fixedX, 5 + 15 * fixedY,LCDBlack,LCDGreen);
		
		
	}
	else if(x >= StatkiX && x <= StatkiX + StatkiW && y >= JednoY && y <= CzteroY + StatkiH)
	{
		
		//sprintf(buffer,"Menu wyboru statku x:%d y:%d\n\r",x,y);
		//sendString(buffer);
		
		if(wybranyKwadracikStatek[0] && wybranyKwadracikStatek[1]){
				DrawBox(wybranyKwadracikStatek[0], wybranyKwadracikStatek[1],15,15,LCDBlack,LCDWhite);
		}
		
		wybranyKwadracikStatek[0] = 220;
		if(y >= JednoY && y <= JednoY + StatkiH){
				wybranyKwadracikStatek[1] = JednoY;
		}
		else if(y >= DwuY && y <= DwuY + StatkiH){
				wybranyKwadracikStatek[1] = DwuY;
		}
		else if(y >= TrzyY && y <= TrzyY + StatkiH){
				wybranyKwadracikStatek[1] = TrzyY;
		}
		else if(y >= CzteroY && y <= CzteroY + StatkiH){
				wybranyKwadracikStatek[1] = CzteroY;
		}
		
		DrawBox(wybranyKwadracikStatek[0], wybranyKwadracikStatek[1],15,15,LCDBlack,LCDBlue);

	}
	else if(y >= PrzyciskiStrzalkiY && y <= PrzyciskiStrzalkiY + PrzyciskH
		&& x >= PrzyciskLewoX && x <= PrzyciskDolX + PrzyciskW)
	{
			// poprawic koordynaty XD
			//sprintf(buffer,"Menu Przyciski ustawiania x:%d y:%d\n\r",x,y);
			//sendString(buffer);
		
			if(wybranyKwadracikOpcje[0] && wybranyKwadracikOpcje[1]){
				if(wybranyKwadracikOpcje[0] < PrzyciskLewoX + PrzyciskW) DrawButton("<",PrzyciskLewoX,285,LCDBlack,LCDWhite);
				else if(wybranyKwadracikOpcje[0] < PrzyciskGoraX + PrzyciskW) DrawButton("^",PrzyciskGoraX,285,LCDBlack,LCDWhite);
				else if(wybranyKwadracikOpcje[0] < PrzyciskPrawoX + PrzyciskW) DrawButton(">",PrzyciskPrawoX,285,LCDBlack,LCDWhite);
				else DrawButton("v",PrzyciskDolX,285,LCDBlack,LCDWhite);	
			}
			
			wybranyKwadracikOpcje[0] = x;
			wybranyKwadracikOpcje[1] = y;
			if(wybranyKwadracikOpcje[0] < PrzyciskLewoX + PrzyciskW)DrawButton("<",PrzyciskLewoX,285,LCDBlack,LCDPastelBlue);
			else if(wybranyKwadracikOpcje[0] < PrzyciskGoraX + PrzyciskW) DrawButton("^",PrzyciskGoraX,285,LCDBlack,LCDPastelBlue);
			else if(wybranyKwadracikOpcje[0] < PrzyciskPrawoX + PrzyciskW) DrawButton(">",PrzyciskPrawoX,285,LCDBlack,LCDPastelBlue);
			else DrawButton("v",PrzyciskDolX,285,LCDBlack,LCDPastelBlue);	
		
	}
	else if(x >= UstawX && x <= UstawX + UstawW && y >= UstawY && y <= UstawY + UstawH){
	

	

	if(wybranyKwadracikOpcje[0] && wybranyKwadracikOpcje[1] && wybranyKwadracikPlansza[0] && wybranyKwadracikPlansza[1]
		&& wybranyKwadracikStatek[0] && wybranyKwadracikStatek[1])
		{
			char zwrot;
			uint16_t maszty;
			
			
			if(wybranyKwadracikOpcje[0] < PrzyciskLewoX + PrzyciskW)
			{
				DrawButton("<",PrzyciskLewoX,285,LCDBlack,LCDWhite);
				zwrot = '<';
			}
			else if(wybranyKwadracikOpcje[0] < PrzyciskGoraX + PrzyciskW)
			{
				DrawButton("^",PrzyciskGoraX,285,LCDBlack,LCDWhite);
				zwrot = '^';
			}
			else if(wybranyKwadracikOpcje[0] < PrzyciskPrawoX + PrzyciskW) 
			{
				DrawButton(">",PrzyciskPrawoX,285,LCDBlack,LCDWhite);
				zwrot = '>';
			}
			else 
			{
				DrawButton("v",PrzyciskDolX,285,LCDBlack,LCDWhite);
				zwrot = 'v';
			}
			
			DrawBox(wybranyKwadracikStatek[0], wybranyKwadracikStatek[1],15,15,LCDBlack,LCDWhite);
			if(wybranyKwadracikStatek[1]  == JednoY) maszty = 1;
			else if(wybranyKwadracikStatek[1]  == DwuY) maszty = 2;
			else if(wybranyKwadracikStatek[1]  == TrzyY) maszty = 3;
			else if(wybranyKwadracikStatek[1]  == CzteroY) maszty = 4;
			
			uint16_t fixedX = ((wybranyKwadracikPlansza[0] - AllyXCoor) / 15) % 10;
			uint16_t fixedY = ((wybranyKwadracikPlansza[1] - AllyYCoor) / 15) % 10;
			DrawSquare(5 + 15 * fixedX, 5 + 15 * fixedY,LCDBlack,LCDWhite);
			
			
			
			ustawStatek(g,fixedX,fixedY,zwrot,maszty);
			rysujStatki(g);
			stack.current = 0;
			wybranyKwadracikPlansza[0] = 0; wybranyKwadracikPlansza[1] = 0;
			wybranyKwadracikStatek[0] = 0; wybranyKwadracikStatek[1] = 0;
			wybranyKwadracikOpcje[0] = 0; wybranyKwadracikOpcje[1] = 0;
		}	
	}
	else{
		sprintf(buffer,"Koordy niepasujace x:%d y:%d\n\r",x,y);
		sendString(buffer);
		
	}
}


void init(Game* g)
{
	g->m_running = true;
	g->m_state = 0;
	g->m_command = 0;
	g->m_turn = 1;
	
	// init ekranu i ekranu dotykowego
	lcdConfiguration();
	init_ILI9325();
	touchpanelInit();
	
	// konfiguracja UART'a
	LPC_UART0->LCR = 3 | (1 << 7);
	LPC_UART0->DLL = 14;
	LPC_UART0->DLM = 0;
	LPC_UART0->LCR = 3;
	LPC_UART0->IER = 1;
	NVIC_EnableIRQ(UART0_IRQn);
	PIN_Configure(0, 2, 1, 0, 0);
	PIN_Configure(0, 3, 1, 0, 0);
	
	// konfiguracja przerwan pochodzacych od ekranu dotykowego
	LPC_GPIOINT->IO0IntEnF = 1 << 19;
	NVIC_EnableIRQ(EINT3_IRQn);
	ClearBoard();
	calibrate_lcd();
	
	// czyszczenie oraz rysowanie poczatkowego stanu ekranu
	ClearBoard();
	DrawBoard(5, 5, LCDBlack, LCDWhite);
	DrawBoard(5, 165, LCDBlack, LCDGinger);
	DrawBox(160,255,70,60,LCDBlack,LCDWhite);
	DrawButton("Ustaw",UstawX,UstawY,LCDBlack,LCDWhite);
	DrawButton("<",PrzyciskLewoX,PrzyciskiStrzalkiY,LCDBlack,LCDWhite);
	DrawButton("^",PrzyciskGoraX,PrzyciskiStrzalkiY,LCDBlack,LCDWhite);
	DrawButton(">",PrzyciskPrawoX,PrzyciskiStrzalkiY,LCDBlack,LCDWhite);
	DrawButton("v",PrzyciskDolX,PrzyciskiStrzalkiY,LCDBlack,LCDWhite);
	
	DrawString(" Jedno-",160,20,LCDBlack,LCDWhite);
	DrawString("   Dwu-",160,40,LCDBlack,LCDWhite);
	DrawString("  Trzy-",160,60,LCDBlack,LCDWhite);
	DrawString("Cztero-",160,80,LCDBlack,LCDWhite);
	DrawString("masztowiec",158,100,LCDBlack,LCDWhite);
	
	DrawBox(StatkiX,JednoY,15,15,LCDBlack,LCDWhite);
	DrawBox(StatkiX,DwuY,15,15,LCDBlack,LCDWhite);
	DrawBox(StatkiX,TrzyY,15,15,LCDBlack,LCDWhite);
	DrawBox(StatkiX,CzteroY,15,15,LCDBlack,LCDWhite);
	
	// okienko z komunikatami
	DrawBox(160,140,70,100,LCDBlack,LCDWhite);
	
	stack.current = 0;
	wybranyKwadracikPlansza[0] = 0; wybranyKwadracikPlansza[1] = 0;
	wybranyKwadracikStatek[0] = 0; wybranyKwadracikStatek[1] = 0;
	wybranyKwadracikOpcje[0] = 0; wybranyKwadracikOpcje[1] = 0;
	
	g->m_shipLeft[0] = 4;
	g->m_shipLeft[1] = 3;
	g->m_shipLeft[2] = 2;
	g->m_shipLeft[3] = 1;
	
	
	for(int i=0;i<10;++i){
			g->m_ourboard.m_ships->m_coords[i][0] = 99;
			g->m_ourboard.m_ships->m_coords[i][1] = 99;
	}
	
	unsigned short x,y;
	while(!ustawione){
	
		if(!empty(&stack)){
			pop(&stack,&x,&y);
			//sprintf(buffer,"X: %d Y: %d S: %d\n\n",x,y,stack.current);
			//sendString(buffer);
			obsluzDotyk(g,x,y);
		}
	}
	for(int i=0;i<10;++i) g->m_shoots[i] = 0;
	
	for(int i=0; i < 10; i++)
	{
		g->m_ourboard.m_ships[i].drown = 0;
		g->m_ourboard.m_ships[i].underwater = 0;
	}
	
	DrawBox(160,255,70,60,LCDBlack,LCDWhite);
	DrawButton("Strzal",170,260,LCDBlack,LCDWhite);
}

void run(Game* g)
{
  uint8_t won = 0;
	g->m_state = 1;
	uint16_t x,y,fixedX,fixedY;
	sendString("RDY;");
		
	if(g->m_turn){
		ShowMessage("Twoja tura");
	}
	else{
		ShowMessage("Tura przeciwnika");
	}
		
	while(true)
	{
		if(g->m_command)
		{
			if(!strcmp(receivedDataBuffer, "RDY;")){
				break;
			}
		}
	}
	
	while(g->m_running)
	{
	
		if(g->m_turn)
		{
			handleTurn(g,&x,&y,&fixedX,&fixedY);
		}
		if(g->m_command)
		{
			if(!strcmp(receivedDataBuffer,"WON;")){
					ShowMessage("Wygrales");
					g->m_running = 0;
					won = 1;
			}
			
			if(!strcmp(receivedDataBuffer,"HIT;")){
				 g->m_shoots[fixedY] |= (3 << (3*fixedX));
				 ShowMessage("Trafiony");
				 drawShots(g);
			}
			
			else if(!strcmp(receivedDataBuffer,"MISS;")){
				g->m_shoots[fixedY] |= (1 << (3*fixedX));
				ShowMessage("Pudlo");
				drawShots(g);
			
			}
			else if(!strcmp(receivedDataBuffer,"DROWN;")){
					g->m_shoots[fixedY] |= (7 << (3*fixedX));
					ShowMessage("Trafiony zatopiony");
					drawShots(g);
			}
			
			else if(!strncmp(receivedDataBuffer,"SHT",3)){
				
				uint16_t receivedX,receivedY;
				receivedX = receivedDataBuffer[3] - '0';
				receivedY = receivedDataBuffer[5] - '0';
				char newMessage[8];
				checkForHit(g,newMessage,receivedX,receivedY);
				sendString(newMessage);
				g->m_turn = true;
				ShowMessage("Twoja tura");
			}	
			g->m_command = false;
		}
		
	}
	if(!won)
		ShowMessage("Przegrales");
}

void checkForHit(Game* g,char* newMessage,uint16_t receivedX,uint16_t receivedY)
{
		for(int i=0;i<10;++i){
		
			for(int j=0;j<g->m_ourboard.m_ships[i].size; ++j){
					if(g->m_ourboard.m_ships[i].m_coords[j][0] == receivedX && g->m_ourboard.m_ships[i].m_coords[j][1] == receivedY){	
							strcpy(newMessage,"HIT;");
							DrawSquare(5 + 15 * receivedX, 5 + 15 * receivedY,LCDBlack,LCDRed);
							g->m_ourboard.m_ships[i].drown |= 1 << j;
							switch (g->m_ourboard.m_ships[i].size)
							{
								case 1:
									if(g->m_ourboard.m_ships[i].drown == 1)
									{
										g->m_ourboard.m_ships[i].underwater = 1;
										strcpy(newMessage,"DROWN;");
									}
									break;
								case 2:
									if(g->m_ourboard.m_ships[i].drown == 3)
									{
										g->m_ourboard.m_ships[i].underwater = 1;
										strcpy(newMessage,"DROWN;");
									}
									break;
								case 3:
									if(g->m_ourboard.m_ships[i].drown == 7)
									{
										g->m_ourboard.m_ships[i].underwater = 1;
										strcpy(newMessage,"DROWN;");
									}
									break;
								case 4:
									if(g->m_ourboard.m_ships[i].drown == 15)
									{
										g->m_ourboard.m_ships[i].underwater = 1;
										strcpy(newMessage,"DROWN;");
									}
									break;
							}
							checkForGameEnd(g, newMessage);
							return;
					}
			}
		
		}
		DrawSquare(5 + 15 * receivedX, 5 + 15 * receivedY,LCDBlack,LCDGrey);
		strcpy(newMessage,"MISS;");
}

void handleTurn(Game* g, uint16_t *x, uint16_t* y, uint16_t *fixedXQ, uint16_t* fixedYQ)
{
	static uint16_t fixedX = 0;
	static uint16_t fixedY = 0;
	if(!empty(&stack))
	{
 
			pop(&stack,x,y);
			if(*x > EnemyXCoor && *x < EnemyXCoor + EnemyWidth
				&& *y > EnemyYCoor && *y < EnemyYCoor + EnemyHeight)
		{
	
		
		
			if(wybranyKwadracikPlansza[0] && wybranyKwadracikPlansza[1]){
				fixedX = ((wybranyKwadracikPlansza[0] - EnemyXCoor) / 15) % 10;
				fixedY = ((wybranyKwadracikPlansza[1] - EnemyYCoor) / 15) % 10;
				DrawSquare(5 + 15 * fixedX, 165 + 15 * fixedY,LCDBlack,LCDGinger);
			}
			
			
			wybranyKwadracikPlansza[0] = *x;
			wybranyKwadracikPlansza[1] = *y;
			fixedX = ((*x-EnemyXCoor) / 15) % 10;
			fixedY = ((*y-EnemyYCoor) / 15) % 10;
			DrawSquare(5 + 15 * fixedX, 165 + 15 * fixedY,LCDBlack,LCDCyan);
		
		
		}
		else if(*x >= UstawX && *x <= UstawX + UstawW && *y >= UstawY && *y <= UstawY + UstawH)
		{
			if(!(wybranyKwadracikPlansza[0] && wybranyKwadracikPlansza[1])) return;
			sendShot(fixedX, fixedY);
			g->m_turn = 0;
			DrawSquare(5 + 15 * fixedX, 165 + 15 * fixedY,LCDBlack,LCDGinger);
			wybranyKwadracikPlansza[0] = 0; wybranyKwadracikPlansza[1] = 0;
			*fixedXQ = fixedX;
			*fixedYQ = fixedY;
		}
	}
}

void sendShot(uint16_t x, uint16_t y)
{
	char buffer[16];
	sprintf(buffer, "SHT%d:%d;", x, y);
	sendString(buffer);
}

void drawShots(Game* g)
{
	uint32_t temp;
	uint16_t counter;
	
	for(uint32_t y=0;y<10;++y){
		for(uint32_t x=0;x<10;++x){
			counter = 0;
			temp = (1 << (3*x)) & (g->m_shoots[y]);
			if(temp) ++counter;
			temp = (1 << (3*x+1)) & (g->m_shoots[y]);
			if(temp) ++counter;
			
			//temp = 1 << (3*x+2) & g->m_shoots[y];
			//if(temp) ++counter;
			//czy zatopiony mozliwosc implementacji		
			if(counter == 1){
				DrawSquare(5 + 15 * x, 165 + 15 * y,LCDBlack,LCDGrey);
			}
			if(counter == 2){
				DrawSquare(5 + 15 * x, 165 + 15 * y,LCDBlack,LCDBlack);
			}
			//mozliwosc rozbudowy o zatopiony	
		}
	}
}

void checkForGameEnd(Game* g, char* buff)
{
	for(int i = 0; i < 10; i++)
	{
			if(!g->m_ourboard.m_ships[i].underwater)
				return;
	}
	g->m_running = 0;
	strcpy(buff, "WON;");
}
