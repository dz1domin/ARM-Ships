#include "stack.h"

void push(Stack* stack,unsigned short x,unsigned short y)
{
		if(stack->current < 5){
			stack->tasks[stack->current][0] = x;
			stack->tasks[stack->current][1] = y;
			++(stack->current);
		}
}

void pop(Stack* stack,unsigned short* x, unsigned short* y)
{
		if(stack->current){
			--stack->current;
			*x = stack->tasks[stack->current][0];
			*y = stack->tasks[stack->current][1];
		}
}

char empty(Stack* stack)
{
	return !stack->current;
}


Stack stack;
