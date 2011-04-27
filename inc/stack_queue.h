#ifndef STACK_QUEUE_H
#define STACK_QUEUE_H

typedef struct _sEle
{
	int	data;
}Element;

typedef struct _sStackNode StackNode,*StackPointer;
struct _sStackNode
{
	Element			item;
	StackPointer	next;
};

int stack_push(StackPointer* ptr, Element item);

int stack_pop(StackPointer* ptr, Element* item);

int stack_top(StackPointer* ptr, Element* item);

int stack_destroy(StackPointer* ptr);

int palindrome_check(void);


#endif
