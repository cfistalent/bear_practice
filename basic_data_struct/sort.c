#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sort.h"
#include "utils.h"

struct sort_alg	g_alg_list;

inline void int_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a	= *b;
	*b	= tmp;
}

static int _do_bubble_sort(int *buf, int len, int up)
{
	int i,j;

	if(up != 0)	/* up sorting */
	{
		for(i = len-1; i > 0; i--)
		{
			for(j = 0; j < i; j++)
			{
				if(buf[j] > buf[j+1])
				{
					int_swap(buf+j, buf+j+1);
				}
			}
		}	
	}
	else
	{
		for(i = len-1; i > 0; i--)
		{
			for(j = 0; j < i; j++)
			{
				if(buf[j] < buf[j+1])
				{
					int_swap(buf+j, buf+j+1);
				}
			}
		}	
		
	}

	return 0;
}

static int bubble_sort_up(int *buf, int len)
{
	return _do_bubble_sort(buf, len, 1);
}

static int bubble_sort_down(int *buf, int len)
{
	return _do_bubble_sort(buf, len, 0);
}

struct sort_alg	bsort_u	= 
{
	.sname	= "bubble_sort_up",
	.sort	= bubble_sort_up,
	.ascend	= 1,
};

struct sort_alg	bsort_d	= 
{
	.sname	= "bubble_sort_down",
	.sort	= bubble_sort_down,
	.ascend	= 0,
};

int do_quick_sort_up(int *buf, int low, int high)
{
	int tmp;
	int i,j;

	if (high > low){
		i = low;
		j = high;
		tmp = buf[low];
		while (i < j){
			while((i < j) && (buf[j] >= tmp))
				j--;
			if (i < j){
				buf[i] = buf[j];
				i++;
			}
			while((i < j) && (buf[i] < tmp))
				i++;
			if (i < j){
				buf[j] = buf[i];
				j--;
			}
		}
		buf[i] = tmp;
		do_quick_sort_up(buf, low, i - 1);
		do_quick_sort_up(buf, i + 1, high);
	}
}

int do_quick_sort_down(int *buf, int low, int high)
{
	int tmp;
	int i,j;

	if (high > low){
		i = low;
		j = high;
		tmp = buf[low];
		while (i < j){
			while((i < j) && (buf[j] <= tmp))
				j--;
			if (i < j){
				buf[i] = buf[j];
				i++;
			}
			while((i < j) && (buf[i] > tmp))
				i++;
			if (i < j){
				buf[j] = buf[i];
				j--;
			}
		}
		buf[i] = tmp;
		do_quick_sort_down(buf, low, i - 1);
		do_quick_sort_down(buf, i + 1, high);
	}
}

int quick_sort_up(int *buf, int len)
{
	do_quick_sort_up(buf, 0, len - 1);
}

int quick_sort_down(int *buf, int len)
{
	do_quick_sort_down(buf, 0, len - 1);
}

struct sort_alg	qsort_u	= 
{
	.sname	= "quick_sort_up",
	.sort	= quick_sort_up,
	.ascend	= 1,
};

struct sort_alg	qsort_d	= 
{
	.sname	= "quick_sort_down",
	.sort	= quick_sort_down,
	.ascend	= 0,
};

static struct sort_alg *sort_alg_search(char *name)
{
	struct sort_alg	*cur;

	cur = g_alg_list.next;
	while(cur != NULL)
	{
		if (0 == strncmp(name, cur->sname, SORT_NAME_SIZE))
		{
			break;
		}
		cur = cur->next;
	}

	return cur;
}

static int sort_alg_register(struct sort_alg *alg)
{
	int ret = -1;

	if (NULL != alg)	
	{
		if (NULL == sort_alg_search(alg->sname))
		{
			alg->next			= g_alg_list.next;
			g_alg_list.next		= alg;
			ret = 0;
		}
	}

	return ret;
}

void sort_init(void)
{
	memset(&g_alg_list, 0, sizeof(g_alg_list));
	sort_alg_register(&bsort_u);
	sort_alg_register(&bsort_d);
	sort_alg_register(&qsort_u);
	sort_alg_register(&qsort_d);
}

int	sort_is_ascend(char *name)
{
	int				 ret;
	struct sort_alg	*alg;

	alg = sort_alg_search(name);
	if (alg != NULL){
		return (alg->ascend != 0);
	}
	return -1;	
}

int sort_exec(int *buf, int len, char *name)
{
	struct sort_alg	*alg;

	if ((NULL == buf) || (len < 1) || (NULL == name))
		return -1;
	
	alg = sort_alg_search(name);
	if (NULL == alg)
		return -1;

	return alg->sort(buf, len);
}

inline int do_sort_test(char *name, int *sbuf, int *buf, int len)
{
	int	ret;
	int	i;
	int	ascend;
	
	start_time_record();
	memcpy(sbuf, buf, sizeof(int) * len);
	ascend = sort_is_ascend(name);
	ret = sort_exec(sbuf, len, name);
	if (ret < 0){
		printf("%s execute fail.\n", name);
		return ret;
	}

	if (ascend){
		for (i=1; i<len; i++){
			if (sbuf[i] < sbuf[i-1]){
				printf("%s work incorret.\n", name);
				return -1;
			}
		}
		printf("%s work correct.\n", name);
	} else {
		for (i=1; i<len; i++){
			if (sbuf[i] > sbuf[i-1]){
				printf("%s work incorret.\n", name);
				return -1;
			}
		}
		printf("%s work correct.\n", name);
	}
	end_time_record();
	show_time(0);

	return 0;
}

/*
 *function	:	sort fuction test
 *in		:	func	function pointer to be tested
 *out		:	-
 *desc		:	get length from stdin, generate data from rand(),
 *				just test if it's working correctly.
 *history	:
 *		date	[2012-7-14]
 *		author	[bearchen]
 *		action	[move from origin project and modified its coding style]
 */
int sort_alg_test(void)
{
	int		 len	= 0;
	int		*buf	= NULL;
	int		*sbuf	= NULL;
	int		 ret	= 0;
	int		 i		= 0;

	while(1)
	{
		printf("input data length(10 to 32766) :\n");
		scanf("%d",&len);
		if((len < 327667) && (len > 9))
		{
			break;
		}
		printf("error input, try again.\n");
	}

	buf = (int*)malloc(sizeof(int) * len * 2);
	if(buf == NULL)
	{
		printf("memory alloc fail.\n");
		return -1;
	}
	sbuf = buf + len;
	srand((int)time(NULL));
	for(i=0; i<len; i++)
	{
		sbuf[i] = buf[i] = rand() % 32766;
	}
	
	sort_init();
	do_sort_test("bubble_sort_up", sbuf, buf, len);
	do_sort_test("bubble_sort_down", sbuf, buf, len);
	do_sort_test("quick_sort_up", sbuf, buf, len);
	do_sort_test("quick_sort_down", sbuf, buf, len);

free_buf:
	free(buf);
	return ret;
}
