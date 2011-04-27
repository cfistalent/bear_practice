#ifndef POLYNOMIAL_LINK_H
#define POLYNOMIAL_LINK_H

typedef struct _sPolyNode PolyNode,*PolyLink;
struct _sPolyNode
{
	int			coef;
	int 		expond;
	PolyLink	link;
};

PolyLink avail_nodes_init(int size);

int avail_nodes_destroy(PolyLink* ptr);

PolyLink avail_nodes_get(PolyLink* ptr);

int avail_nodes_ret(PolyLink* ptr, PolyLink ret_ptr);

PolyLink poly_read(char* str, int len, PolyLink* avail);

int poly_destroy(PolyLink* ptr, PolyLink* avail);

int poly_print(PolyLink head);

int poly_test(void);


#endif
