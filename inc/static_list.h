#ifndef STATIC_LIST_H
#define STATIC_LIST_H

typedef struct _Sele
{
	int data;
	int next;
}SEle,*PSEle;

PSEle sl_create(int size);
int sl_destroy(PSEle sl_head);
int sl_malloc(PSEle sl_head);
int sl_free(PSEle sl_head, int i);
int difference(void);

#endif
