#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

int stack_push(StackPointer* ptr, Element item)
{
	ret_val_if_fail(ptr != NULL, -1);
	StackPointer tmp = NULL;

	tmp = (StackPointer)malloc(sizeof(*tmp));
	ret_val_if_fail(tmp != NULL, -1);
	tmp->item = item;
	if((*ptr) == NULL)
	{
		(*ptr) = tmp;
		tmp->next = NULL;
	}
	else
	{
		tmp->next = (*ptr);
		(*ptr) = tmp;
	}
	
	return 0;
}

int stack_pop(StackPointer* ptr, Element* item)
{
	ret_val_if_fail(ptr != NULL && item != NULL, -1);
	StackPointer	tmp;

	if((*ptr) == NULL)
	{
		//DBG("stack is empty.\n");
		return 0;
	}
	tmp = (*ptr);
	*item  = tmp->item;
	(*ptr) = tmp->next;
	free(tmp);

	return 0;
}

int stack_top(StackPointer* ptr, Element* item)
{
	ret_val_if_fail(ptr != NULL && item != NULL, -1);

	if((*ptr) == NULL)
	{
		return -1;
	}
	*item = (*ptr)->item;

	return 0;
}

int stack_destroy(StackPointer* ptr)
{
	ret_val_if_fail(ptr != NULL, -1);
	StackPointer next;
	StackPointer current;
	
	current = (*ptr);
	while(current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	(*ptr) = NULL;

	return 0;
}

/*
 *Function:	Check whether an input string is parlindrome
 *In:		-
 *Out		-
 *Note:		-
 *LM:		2011-4-23
 */
int palindrome_check(void)
{
	StackPointer	ptr = NULL;
	char			buffer[1024];
	Element			item;
	int i;
	int str_len;

	printf("Input a string to check:\n");
	if(NULL != fgets(buffer, sizeof(buffer), stdin))	
	{
		str_len = strlen(buffer) - 1;		//delete the newline char
		for(i=0; i<str_len; i++)
		{
			if(ptr == NULL)
			{
				item.data = buffer[i];
				stack_push(&ptr, item);
			}
			else
			{
				if(ptr->item.data == (int)buffer[i])
				{
					stack_pop(&ptr, &item);
				}
			}
		}
		if(ptr == NULL)
		{
			printf("string  is parlindrome\n");
		}
		else
		{
			printf("string  is not parlindrome\n");
		}
	}
	stack_destroy(&ptr);

	return 0;
}
