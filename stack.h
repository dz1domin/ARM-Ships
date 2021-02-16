#ifndef _STACK_H_
#define _STACK_H_

typedef struct{
	
	unsigned short tasks[5][2];
	unsigned char current;
	
} Stack;

void push(Stack* stack,unsigned short x,unsigned short y);
void pop(Stack* stack,unsigned short* x, unsigned short* y);
char empty(Stack* stack);


#endif
