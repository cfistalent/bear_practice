#ifndef __SORT_H
#define __SORT_H

#define SORT_NAME_SIZE 32

struct sort_alg
{
	struct sort_alg		*next;
	char				 sname[SORT_NAME_SIZE];
	int					 ascend;
	int (*sort)(int *buf, int len);
};

extern void sort_init(void);
extern int  sort_exec(int *buf, int len, char *name);
extern int sort_alg_test(void);

#endif
