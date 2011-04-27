#ifndef EXPRESS_VALUE_H
#define EXPRESS_VALUE_H

typedef enum _expr {lp=0,rp,plus,minus,multi,divi,op} expr_type;

typedef struct _sExpressElement
{
	expr_type	type;
	int			val;
}ExpEle;

#define DEFAULT_SIZE 20
#define IS_DIGIT(x) ((x >= '0') ? ((x <= '9') ? (0) : (-1)) : (-1))

ExpEle*	express_parse(char* str,int str_size, int* esize);

ExpEle* express_postfix(ExpEle* eptr, int len, int* out_len);

int express_value(ExpEle* eptr, int len, int* result);

int express_print(ExpEle* expr, int len);

int express_test(void);

#endif
