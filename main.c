#include "Game.h"
#include "interrupt_handler.h"
#include "stack.h"

Game game;
extern Stack stack; 


int main(int argc, char** argv)
{
	stack.current = 0;
	init(&game);
	run(&game);

}
