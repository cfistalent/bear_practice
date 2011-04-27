#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "static_list.h"

#define MAX_SIZE 100

/*
 *Function:	create static list,initialize it to backup state
 *In:		size		the size of the static list
 *Out:		PSEle		"NULL"if fail,else the header pointer of sl
 *Note:		-
 *LM:		2011-3-22
 */
PSEle sl_create(int size)
{
	ret_val_if_fail(size <= MAX_SIZE && size > 0, NULL);
	PSEle sl_head = NULL;
	int i;

	sl_head = (PSEle) malloc(size * sizeof(* sl_head));
	ret_val_if_fail(sl_head != NULL, NULL);
	for(i=0; i<(size-1); i++)
	{
		sl_head[i].next = i + 1;
	}
	sl_head[i].next = 0;

	return sl_head;
}

/*
 *Function:	delete a static list if it exist
 *In:		sl_head		header pointer of the sl
 *Out:		int			-1 if failed,else return 0
 *Note:		-
 *LM:		2011-3-22
 */
int sl_destroy(PSEle sl_head)
{
	ret_val_if_fail(sl_head != NULL, -1);
	
	free(sl_head);
	return 0;
}

int sl_malloc(PSEle sl_head)
{
	ret_val_if_fail(sl_head != NULL, 0);
	int ret_val = 0;

	if(sl_head[0].next != 0)
	{
		ret_val = sl_head[0].next;
		sl_head[0].next = sl_head[ret_val].next;
	}
	
	return ret_val;
}

int sl_free(PSEle sl_head, int i)
{
	ret_val_if_fail(sl_head != NULL && i >= 0, -1);

	sl_head[i].next = sl_head[0].next;
	sl_head[0].next = i;

	return 0;
}

int difference(void)
{
	int start,end,new,search,i;
	int m,n,k;
	PSEle sl_head = NULL;

	sl_head = sl_create(MAX_SIZE);
	ret_val_if_fail(sl_head != NULL, -1);

	printf("input number of A and B\n");
	scanf("%d",&m);
	scanf("%d",&n);

	start = sl_malloc(sl_head);
	end = start;
	sl_head[end].next = 0;

	printf("please input A\n");
	for(i=0; i<m; i++)
	{
		printf("number %d:",i+1);
		scanf("%d",&k);
		new = sl_malloc(sl_head);
		sl_head[new].data = k;
		sl_head[new].next = sl_head[end].next;
		sl_head[end].next = new; 
		end = new;
	}

	printf("please input B\n");
	for(i=0; i<n; i++)
	{
		printf("number %d:",i+1);
		scanf("%d",&k);
		search = sl_head[start].next;
		while(search != 0 && sl_head[search].data != k)
		{
			search = sl_head[search].next;
		}
		if(search == 0)
		{
			new = sl_malloc(sl_head);
			sl_head[new].data = k;
			sl_head[new].next = sl_head[end].next;
			sl_head[end].next = new; 
			end = new;
		}
		else
		{
			printf("data %d has one copy in A\n",k);
		}
	}

	printf("A - B U B - A is : ");
	search = sl_head[start].next;
	while(search)
	{
		printf("%d ",sl_head[search].data);
		search = sl_head[search].next;
	}
	printf("\n");

	sl_destroy(sl_head);

	return 0;
}

