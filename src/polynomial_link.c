#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

#define DEFAULT_AVAIL_NODES 20

/*
 *Function:	create available nodes array with specified size
 *In:		size		size of available arrays
 *Out:		PolyLink	pointer to available array
 *Note:		user should consider max usage
 *LM:		2011-4-25
 */
PolyLink avail_nodes_init(int size)
{
	PolyLink ptr = NULL;
	PolyLink nptr,tptr;
	int i,j;
	
	size = ((size <= 1) ? (DEFAULT_AVAIL_NODES) : (size));
	ptr = (PolyLink)malloc(sizeof(*ptr));
	if(ptr != NULL)
	{
		tptr = ptr;
		for(i = 1; i < size; i++)
		{
			nptr = (PolyLink)malloc(sizeof(*nptr));
			if(nptr == NULL)
			{
				break;
			}
			else
			{
				tptr->link = nptr;
				tptr = nptr;
			}
		}
		tptr->link = NULL;
	}

	return ptr;
}

/*
 *Function:	free available array
 *In:		ptr		pointer to the header pointer of available array
 *Out:		0
 *Note:		-
 *LM:		2011-4-25
 */
int avail_nodes_destroy(PolyLink* ptr)
{
	PolyLink tmp,start;
	
	start = (*ptr);
	while(start != NULL)
	{
		tmp = start->link;
		free(start);
		start = tmp;
	}
	*ptr = NULL;

	return 0;
}

/*
 *Function:	Get one node from available array
 *In:		ptr			pointer to available array
 *Out:		PolyLink	pointer to one node, NULL if fail
 *Note:		-
 *LM:		2011-4-25
 */
PolyLink avail_nodes_get(PolyLink* ptr)
{
	ret_val_if_fail(ptr != NULL, NULL);
	PolyLink tmp;

	if((*ptr) != NULL)
	{
		tmp = (*ptr);
		(*ptr) = tmp->link;
	}
	else
	{
		tmp = (PolyLink)malloc(sizeof(*tmp));
	}

	return tmp;
}

/*
 *Function:	return  one node to available array
 *In:		ptr			pointer to available array
 *Out:		PolyLink	pointer to one node, NULL if fail
 *Note:		-
 *LM:		2011-4-25
 */
int avail_nodes_ret(PolyLink* ptr, PolyLink ret_ptr)
{
	ret_val_if_fail(ptr != NULL && ret_ptr != NULL, -1);

	ret_ptr->link = (*ptr);
	(*ptr) = ret_ptr;

	return 0;
}

/*
 *Function:	parse polynomial from a string
 *In:		str			the string including a polynomial
 *			len			string length
 *			avail		available nodes array
 *Out:		PolyLink	pointer to the polynomial
 *Note:		the input string should be like " a^b c^d x^z",number before
 *			'^'means coefficient,after means expond
 *			polynomial is stored in the way of circule link with head node
 *LM:		2011-4-25
 */
PolyLink poly_read(char* str, int len, PolyLink* avail)
{
	ret_val_if_fail(str != NULL && len > 0, NULL);
	int i;
	int data;
	PolyLink head,ptr;

	head = NULL;
	ptr = NULL;
	head = avail_nodes_get(avail);
	ptr = head;
	if(head != NULL)
	{
		for(i = 0; i < len; i++)
		{
			if(str[i] != ' ')
			{
				data = 0;
				ptr->link = avail_nodes_get(avail);
				ptr = ptr->link;
				while((str[i] != ' ') && (str[i] != '\0'))
				{
					if(str[i] == '^')
					{
						ptr->coef = data;
						data = 0;
					}
					else
					{
						data = data * 10 + (str[i] - '0');
					}
					i++;
				}
				ptr->expond = data;
			}
		}
		ptr->link = head;
	}

	return head;
}

int poly_destroy(PolyLink* ptr, PolyLink* avail)
{
	ret_val_if_fail(ptr != NULL && avail != NULL, -1);	
	PolyLink trail, trace;

	if((*ptr) != NULL)
	{
		trace = (*ptr)->link;
		while(trace != (*ptr))
		{
			trail = trace->link;
			avail_nodes_ret(avail, trace);
			trace = trail;
		}
		avail_nodes_ret(avail, trace);

		(*ptr) = NULL;
	}

}

int poly_print(PolyLink head)
{
	ret_val_if_fail(head != NULL, -1);
	PolyLink trace;

	trace = head->link;
	while(trace->link != head)
	{
		printf("%dx^%d+",trace->coef, trace->expond);
		trace = trace->link;
	}
	printf("%dx^%d \n",trace->coef, trace->expond);

	return 0;
}

int poly_test(void)
{
	char		buffer[1024];
	int			buffer_len;
	PolyLink	avail;
	PolyLink	poly;

	avail = poly = NULL;

	printf("Input a polynomial:\n");
	fgets(buffer, sizeof(buffer), stdin);
	buffer_len = strlen(buffer);
	buffer_len--;
	buffer[buffer_len] = '\0';	//delete the newline

	avail = avail_nodes_init(0);
	if(avail != NULL)
	{
		poly = poly_read(buffer, buffer_len, &avail);
		poly_print(poly);

		poly_destroy(&poly, &avail);
		avail_nodes_destroy(&avail);
		
	}

	return 0;
}
